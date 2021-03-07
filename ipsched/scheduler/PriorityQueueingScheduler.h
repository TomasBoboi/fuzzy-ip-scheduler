#ifndef __IPSCHEDULER_PRIORITYQUEUEINGSCHEDULER_H_
#define __IPSCHEDULER_PRIORITYQUEUEINGSCHEDULER_H_

#include <omnetpp.h>

using namespace omnetpp;

class PriorityQueueingScheduler : public cSimpleModule
{
public:
    PriorityQueueingScheduler();
    ~PriorityQueueingScheduler();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual int getQueueLength(const char *name);

private:
    cMessage *readyToScheduleMessage;
};
#endif
