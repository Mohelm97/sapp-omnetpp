#include "PSASinkApp.h"
#include "../PSANetworkProtocol.h"
#include "../packets/PSAMessage_m.h"

Define_Module(PSASinkApp);

void PSASinkApp::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        topic = par("topic").stringValue();
        subTimeout = par("subTimeout").intValue();
        operationalState = State::OPERATING;
        const std::string name = getParentModule()->getFullName();
        const std::string messageName = name + "_" + topic + "_SUB";
        auto subPacket = new Packet(messageName.c_str());
        auto subChunk = makeShared<PSAMessage>();
        subChunk->setTopic(topic);
        subChunk->setType(PSAMessageType::Subscription);
        subPacket->insertAtFront(subChunk);
        scheduleAt(0, subPacket);
        WATCH(recivedMessages);
    } else if (stage == INITSTAGE_APPLICATION_LAYER) {
        registerProtocol(PSANetworkProtocol::dataProtocol, gate("socketOut"), gate("socketIn"));
    }
}

void PSASinkApp::handleMessageWhenUp(cMessage *msg) {
    EV_INFO << "PSASink::handleMessageWhenUp MESSAGE: " << msg << endl;
    if (msg->isSelfMessage()){
        auto& tags = check_and_cast<ITaggedObject *>(msg)->getTags();
        tags.addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&PSANetworkProtocol::protocol);
        send(msg, gate("socketOut"));
        scheduleAfter(subTimeout, msg->dup());
    } else {
        EV_INFO << "RECIVED MESSAGE: " << msg << endl;
        auto packet = dynamic_cast<Packet *>(msg);
        auto messageChunk = packet->peekAtFront<PSAMessage>();
        if (messageChunk->getType() == PSAMessageType::Publication) {
            recivedMessages++;
            EV_INFO << "RECIVED PUBLISH MESSAGE TOPIC: " << messageChunk->getTopic() << " FROM: " << messageChunk->getSourceNodeName() << endl;
        }
        delete msg;
    }
}
void PSASinkApp::finish() {
    EV_INFO << getParentModule()->getFullName() << " Number of Received Messages on " << topic << ": " << recivedMessages << endl;
}
