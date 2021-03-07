#ifndef __IPSCHEDULER_SINK_H_
#define __IPSCHEDULER_SINK_H_

#include <omnetpp.h>

using namespace omnetpp;

class Sink : public cSimpleModule
{
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

private:
    simsignal_t packetLifetimeSignal_nrtLp;
    simsignal_t packetLifetimeSignal_nrtHp;
    simsignal_t packetLifetimeSignal_rtLp;
    simsignal_t packetLifetimeSignal_rtHp;
    simsignal_t numberOfPacketsSignal;
};

#endif
