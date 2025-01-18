#include "PSASourceApp.h"
#include "../packets/PSAMessage_m.h"
#include "../PSANetworkProtocol.h"
Define_Module(PSASourceApp);

void PSASourceApp::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        topic = par("topic").stringValue();
        delay = par("delay").doubleValue();
        rate = par("rate").doubleValue();
        needAcking = par("needAcking").boolValue();

        operationalState = State::OPERATING;
        const std::string name = getParentModule()->getFullName();
        const std::string messageName = name + "_" + topic + "_PUB";
        auto pubPacket = new Packet(messageName.c_str());
        auto pubChunk = makeShared<PSAMessage>();
        pubChunk->setTopic(topic);
        pubChunk->setType(PSAMessageType::Publication);
        pubChunk->setNeedAcking(needAcking);
        pubPacket->insertAtFront(pubChunk);
        scheduleAt(delay, pubPacket);
    }
}

void PSASourceApp::handleMessageWhenUp(inet::cMessage *msg) {
    if (msg->isSelfMessage()){
        PSANetworkProtocol::totalSentMessages++;
        PSANetworkProtocol::totalSentMessagesToSubs += PSANetworkProtocol::topicSubscripers[topic];
        if (rate != 0)
            scheduleAfter(1/rate, msg->dup());
        auto& tags = check_and_cast<inet::ITaggedObject *>(msg)->getTags();
        tags.addTagIfAbsent<inet::DispatchProtocolReq>()->setProtocol(&PSANetworkProtocol::protocol);
        send(msg, gate("socketOut"));
    } else {
        EV_INFO << "Message Received in PSASource!" << *msg << inet::endl;
    }
}
