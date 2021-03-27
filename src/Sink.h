#ifndef __IPSCHEDULER_SINK_H_
#define __IPSCHEDULER_SINK_H_

#include <omnetpp.h>

using namespace omnetpp;

class Sink : public cSimpleModule
{
public:
    virtual int getAverageDelay_rtHp();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

private:
    simsignal_t packetLifetimeSignal_nrtLp;
    simsignal_t packetLifetimeSignal_nrtHp;
    simsignal_t packetLifetimeSignal_rtLp;
    simsignal_t packetLifetimeSignal_rtHp;
    simsignal_t numberOfPacketsSignal;

    long packetCount_nrtLp;
    unsigned long long packetDelay_nrtLp;
    int averageDelay_nrtLp;

    long packetCount_nrtHp;
    unsigned long long packetDelay_nrtHp;
    int averageDelay_nrtHp;

    long packetCount_rtLp;
    unsigned long long packetDelay_rtLp;
    int averageDelay_rtLp;

    long packetCount_rtHp;
    unsigned long long packetDelay_rtHp;
    int averageDelay_rtHp;
};

#endif
