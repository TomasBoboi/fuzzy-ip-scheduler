#ifndef __IPSCHEDULER_WRRSCHEDULER_H_
#define __IPSCHEDULER_WRRSCHEDULER_H_

#include <omnetpp.h>

using namespace omnetpp;

class WRRFLCScheduler : public cSimpleModule
{
public:
    WRRFLCScheduler();
    ~WRRFLCScheduler();

    virtual int  getWeight(int index);
    virtual void setWeight(int newWeight, int index);

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual int getQueueLength(const char *name);
    virtual void sortTimes(simtime_t times[4]);
    virtual void parseWeights(const char *weightsAsString);

private:
    cMessage *readyToScheduleMessage;

    simtime_t lastServed_nrtLp;
    simtime_t lastServed_nrtHp;
    simtime_t lastServed_rtLp;
    simtime_t lastServed_rtHp;

    int userWeights[4];
};

#endif
