#include "PSANetworkProtocol.h"
#include "packets/PSAMessage_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/Simsignals.h"
#include "inet/common/stlutils.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
Define_Module(PSANetworkProtocol);

void PSANetworkProtocol::initialize(int stage)
{
    NetworkProtocolBase::initialize(stage);
    if (stage == inet::INITSTAGE_LOCAL) {
        PSANetworkProtocol::nonceCounter = 0;
        if (ProtocolGroup::getEthertypeProtocolGroup()->findProtocol(getProtocol().getId()) == nullptr) {
            ProtocolGroup::getEthertypeProtocolGroup()->addProtocol(getProtocol().getId(), &getProtocol());
        }
        hcMaxSubscribe = par("hcMaxSubscribe");
        hcMaxPublish = par("hcMaxPublish");
        subCleanTimeout = par("subCleanTimeout");
        nodeName = getParentModule()->getParentModule()->getFullName();
        WATCH_VECTOR(localTopics);
        WATCH_MAP(subscriptionTable);
        scheduleAfter(1, new cMessage());
   }
}

void PSANetworkProtocol::handleMessage(cMessage *msg)
{
    NetworkProtocolBase::handleMessageWhenUp(msg);
    delete msg;
}

void PSANetworkProtocol::handleSelfMessage(cMessage *msg)
{
    // Timer Message;
    scheduleAfter(1, new cMessage());
    for(auto& [key, list] : subscriptionTable) {
        for (auto it = list.begin(); it != list.end(); ) {
           it->timer++;
           if (it->timer >= 40) {
               it = list.erase(it);
           } else {
               ++it;
           }
       }
    }
}

void PSANetworkProtocol::handleUpperPacket(Packet *packet)
{
    auto chunk = packet->removeAtFront<PSAMessage>();
    int hcMax = hcMaxPublish;
    if (chunk->getType() == PSAMessageType::Subscription) {
        localTopics.push_back(chunk->getTopic());
        hcMax = hcMaxSubscribe;
    }
    chunk->setSourceNodeName(nodeName);
    chunk->setNonce(++nonceCounter);
    packet->insertAtFront(chunk);
    std::string topic = chunk->getTopic();

    if (chunk->getHopCount() + 1 < hcMax) {
        broadcastPacket(packet);
    } else if (subscriptionTable.find(topic) != subscriptionTable.end()) {
        std::list<PSASubscriptionEntry> subList = subscriptionTable[topic];
        for (auto entry : subList) {
            sendDownTo(packet, entry.nextHop);
        }
    }
    seenMessages.emplace_back(nonceCounter);
}

void PSANetworkProtocol::handleLowerPacket(Packet *packet)
{
    auto chunk = packet->peekAtFront<PSAMessage>();
    if (contains(seenMessages, chunk->getNonce())) return;
    seenMessages.emplace_back(chunk->getNonce());
    PSAMessageType type = chunk->getType();
    bool handled = false;
    switch (type) {
        case PSAMessageType::Publication:
            handled = handleLowerPublish(packet);
            break;
        case PSAMessageType::Subscription:
            handled = handleLowerSubscribe(packet);
            break;
        case PSAMessageType::Acking:
            handled = handleLowerAcking(packet);
            break;
    }
    if (!handled) {
       PacketDropDetails details;
       details.setReason(PacketDropReason::HOP_LIMIT_REACHED);
       emit(packetDroppedSignal, packet, &details);
   }
}

bool PSANetworkProtocol::handleLowerSubscribe (Packet *packet)
{
    auto chunk = packet->peekAtFront<PSAMessage>();
    inet::MacAddress nextHop = packet->getTag<inet::MacAddressInd>()->getSrcAddress();
    auto sourceNodeName = chunk->getSourceNodeName();
    std::string topic = chunk->getTopic();

    std::list<PSASubscriptionEntry>& subscribers = subscriptionTable[topic];
    bool found = false;
    for (const auto& entry : subscribers) {
        if (entry.sourceNodeName == sourceNodeName && entry.nextHop == nextHop) {
            EV_INFO << "Subscription already exists: Topic=" << topic << ", Node=" << sourceNodeName << ", NextHop=" << nextHop << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        subscribers.emplace_back(chunk->getTopic(), chunk->getSourceNodeName(), nextHop);
        EV_INFO << "Adding subscription: Topic=" << topic << ", Node=" << sourceNodeName << ", NextHop=" << nextHop << endl;
    }

    if (chunk->getHopCount() + 1 < hcMaxSubscribe) {
        broadcastPacket(packet);
    }
    return true;
}

bool PSANetworkProtocol::handleLowerPublish (Packet *packet)
{
    bool handled = false;
    auto chunk = packet->peekAtFront<PSAMessage>();
    std::string topic = chunk->getTopic();
    if (contains(localTopics, topic)) {
        auto packetDup = packet->dup();
        packetDup->clearTags();
        packetDup->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&getDataProtocol());
        packetDup->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&getDataProtocol());
        packetDup->addTagIfAbsent<L3AddressInd>(); // Just add L3Address because sendUp requires it!
        sendUp(packetDup);
        if (chunk->getNeedAcking())
            sendAcking(packet);
        handled = true;
    }

    if (chunk->getHopCount() + 1 < hcMaxPublish) {
        broadcastPacket(packet);
        handled = true;
    } else if (chunk->getHopCount() + 1 < hcMaxPublish + hcMaxSubscribe && subscriptionTable.find(topic) != subscriptionTable.end()) {
        std::list<PSASubscriptionEntry> subList = subscriptionTable[topic];
        for (auto entry : subList) {
            sendDownTo(packet, entry.nextHop);
        }
        handled = true;
    }
    return handled;
}

bool PSANetworkProtocol::handleLowerAcking(Packet *packet)
{
    auto chunk = packet->removeAtFront<PSAMessage>();
    if (chunk->getPathHopsArraySize() == 0) {
        EV_INFO << "handleLowerAcking::" << nodeName << " Acking for me!" << endl;
        return true;
    }
    auto nextHop = chunk->getPathHops(chunk->getPathHopsArraySize() - 1);
    chunk->setPathHopsArraySize(chunk->getPathHopsArraySize() - 1);
    packet->insertAtFront(chunk);
    sendDownTo(packet, nextHop);
    return true;
}

void PSANetworkProtocol::broadcastPacket(Packet *packet)
{
    sendDownTo(packet, MacAddress::BROADCAST_ADDRESS);
}

void PSANetworkProtocol::sendDownTo(Packet *packet, MacAddress dest)
{
    auto newPacket = new Packet(packet->getName());
    auto chunk = makeShared<PSAMessage>(*packet->peekAtFront<PSAMessage>());
    if (chunk->getNeedAcking() && packet->hasTag<inet::MacAddressInd>()) {
        inet::MacAddress srcHop = packet->getTag<inet::MacAddressInd>()->getSrcAddress();
        chunk->appendPathHops(srcHop);
    }
    chunk->setHopCount(chunk->getHopCount() + 1);
    newPacket->insertAtFront(chunk);
    auto& tags = newPacket->getTags();
    tags.addTagIfAbsent<MacAddressReq>()->setDestAddress(dest);
    tags.addTagIfAbsent<PacketProtocolTag>()->setProtocol(&getProtocol());
    sendDown(newPacket);
}

void PSANetworkProtocol::sendAcking(Packet *packet)
{
    auto chunk = packet->peekAtFront<PSAMessage>();
    if (!chunk->getNeedAcking() || !packet->hasTag<inet::MacAddressInd>()) {
        throw cRuntimeError("sendAcking(): Packet doesn't request acking or doesn't have a source!");
    }
    inet::MacAddress srcHop = packet->getTag<inet::MacAddressInd>()->getSrcAddress();
    std::string messageName =  (std::string) packet->getName() + "_ACK";
    Packet *ackingPacket = new Packet(messageName.c_str());
    auto ackingChunk = makeShared<PSAMessage>();
    ackingChunk->setType(PSAMessageType::Acking);
    ackingChunk->setSourceNodeName(nodeName);
    ackingChunk->setNonce(++nonceCounter);
    for(size_t i=0; i < chunk->getPathHopsArraySize();i++)
        ackingChunk->appendPathHops(chunk->getPathHops(i));
    ackingPacket->insertAtFront(ackingChunk);
    sendDownTo(ackingPacket, srcHop);
    delete ackingPacket;
}

void PSANetworkProtocol::finish()
{

}

// Define protocol and data protocol (Transport layer)

int PSANetworkProtocol::nonceCounter = 0;
const Protocol PSANetworkProtocol::protocol = Protocol("psa", "Pub/Sub Acking", inet::Protocol::NetworkLayer);
const Protocol PSANetworkProtocol::dataProtocol = Protocol("psa_data", "Pub/Sub Acking Data", inet::Protocol::TransportLayer);
const Protocol& PSANetworkProtocol::getProtocol() const { return PSANetworkProtocol::protocol; }
const Protocol& PSANetworkProtocol::getDataProtocol() const { return PSANetworkProtocol::dataProtocol; }

//
std::ostream& operator<<(std::ostream& os, const std::list<PSASubscriptionEntry>& entries) {
    os << "[";
    for (auto it = entries.begin(); it != entries.end(); ++it) {
        os << *it; // Use the overloaded operator<< for PSASubscriptionEntry
        if (std::next(it) != entries.end()) {
            os << ", \n"; // Add a separator for entries
        }
    }
    os << "]";
    return os;
}
