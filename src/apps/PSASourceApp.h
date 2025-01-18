#ifndef __NETWORKPAPER_PSASOURCEAPP_H_
#define __NETWORKPAPER_PSASOURCEAPP_H_

#include <omnetpp.h>
#include "inet/applications/base/ApplicationBase.h"

using namespace inet;

class PSASourceApp : public ApplicationBase
{
  protected:
    const char* topic;
    double delay;
    double rate;
    bool needAcking;

    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(inet::cMessage *msg) override;

    virtual void handleStartOperation(inet::LifecycleOperation *operation) override {}
    virtual void handleStopOperation(inet::LifecycleOperation *operation) override {}
    virtual void handleCrashOperation(inet::LifecycleOperation *operation) override {}
};

#endif
