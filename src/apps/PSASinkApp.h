#ifndef __NETWORKPAPER_PSASINKAPP_H_
#define __NETWORKPAPER_PSASINKAPP_H_

#include <omnetpp.h>
#include "inet/applications/base/ApplicationBase.h"

using namespace inet;

class PSASinkApp : public ApplicationBase
{
  protected:
    int recivedMessages = 0;
    const char* topic;
    int subTimeout = 0;

    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;
    virtual void handleStartOperation(LifecycleOperation *operation) override {};
    virtual void handleStopOperation(LifecycleOperation *operation) override {};
    virtual void handleCrashOperation(LifecycleOperation *operation) override {};
};

#endif
