#ifndef __NETWORKPAPER_PSANETWORKPROTOCOL_H_
#define __NETWORKPAPER_PSANETWORKPROTOCOL_H_

#include <omnetpp.h>
#include "inet/networklayer/base/NetworkProtocolBase.h"

using namespace inet;


struct PSASubscriptionEntry {
    std::string topic;
    std::string sourceNodeName;
    inet::MacAddress nextHop;
    uint32_t timer;

    PSASubscriptionEntry() : timer(0), topic(""), sourceNodeName(""), nextHop(inet::MacAddress::UNSPECIFIED_ADDRESS) {}
    PSASubscriptionEntry(const std::string& topic, const std::string& sourceNodeName, const inet::MacAddress& nextHop)
        : timer(0), topic(topic), sourceNodeName(sourceNodeName), nextHop(nextHop) {}
    friend std::ostream& operator<<(std::ostream& os, const PSASubscriptionEntry& entry) {
        os << "Topic: " << entry.topic
           << ", Source Node: " << entry.sourceNodeName
           << ", Next Hop: " << entry.nextHop
           << ", Timer: " << entry.timer;
        return os;
    }
};

class PSANetworkProtocol : public NetworkProtocolBase
{
  protected:
    int hcMaxSubscribe;
    int hcMaxPublish;
    int subCleanTimeout;
    const char* nodeName;

    std::vector<uint32_t> seenMessages;

    std::map<std::string, std::list<PSASubscriptionEntry>> subscriptionTable;
    std::vector<std::string> localTopics;

    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void handleUpperPacket(Packet *packet) override;
    virtual void handleLowerPacket(Packet *packet) override;
    virtual void handleSelfMessage(cMessage *message) override;
    bool handleLowerPublish(Packet *packet);
    bool handleLowerSubscribe(Packet *packet);
    bool handleLowerAcking(Packet *packet);
    void sendDownTo(Packet *packet, MacAddress dest);
    void broadcastPacket(Packet *packet);
    void sendAcking(Packet *packet);
    virtual void finish() override;
    virtual const Protocol& getProtocol() const override;
    virtual const Protocol& getDataProtocol() const;

    virtual void handleStartOperation(LifecycleOperation *operation) override {};
    virtual void handleStopOperation(LifecycleOperation *operation) override {};
    virtual void handleCrashOperation(LifecycleOperation *operation) override {};

  public:
    static int boradcastsCounter;
    static int subBroadcastsCounter;
    static int pubBroadcastsCounter;
    static int totalSentMessages;
    static int totalSentMessagesToSubs;
    static int totalReceivedMessages;
    static int totalAckingRecived;
    static std::map<std::string, int> topicSubscripers;

    static const Protocol protocol;
    static const Protocol dataProtocol;
    static int nonceCounter; // Just for simulation!
};

#endif
