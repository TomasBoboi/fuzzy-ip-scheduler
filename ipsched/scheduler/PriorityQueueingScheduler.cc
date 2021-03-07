#include "PriorityQueueingScheduler.h"

#include "ipsched/src/Queue.h"

Define_Module(PriorityQueueingScheduler);

PriorityQueueingScheduler::PriorityQueueingScheduler()
{
    readyToScheduleMessage = nullptr;
}

PriorityQueueingScheduler::~PriorityQueueingScheduler()
{
    cancelAndDelete(readyToScheduleMessage);
}

void PriorityQueueingScheduler::initialize()
{
    readyToScheduleMessage = new cMessage("RTSch");

    scheduleAt(simTime(), readyToScheduleMessage);
}

void PriorityQueueingScheduler::handleMessage(cMessage *msg)
{
    if (msg == readyToScheduleMessage)
    {
        bool sent = false;

        if (getQueueLength("rtHpQueue") > 0)
        {
            send(new cMessage("schedulerMessage"), "rtHpQueueControl_out");
            sent = true;
        }
        else if (getQueueLength("rtLpQueue") > 0)
        {
            send(new cMessage("schedulerMessage"), "rtLpQueueControl_out");
            sent = true;
        }
        else if (getQueueLength("nrtHpQueue") > 0)
        {
            send(new cMessage("schedulerMessage"), "nrtHpQueueControl_out");
            sent = true;
        }
        else if (getQueueLength("nrtLpQueue") > 0)
        {
            send(new cMessage("schedulerMessage"), "nrtLpQueueControl_out");
            sent = true;
        }

        if (!sent)
        {
            scheduleAt(
                simTime() + SimTime(par("packetGenerationDelay").doubleValue(),
                                    SIMTIME_US)
                                .trunc(SIMTIME_US),
                readyToScheduleMessage);
        }
    }
    else
    {
        send(msg, "out");

        scheduleAt(
            gate("out")->getTransmissionChannel()->getTransmissionFinishTime(),
            readyToScheduleMessage);
    }
}

int PriorityQueueingScheduler::getQueueLength(const char *queueName)
{
    int queueLength;

    Queue *queue = check_and_cast<Queue *>(
        getParentModule()->getSubmodule(queueName));
    queueLength = queue->getQueueLength();

    EV << queue->getName() << " length: " << queueLength << "\n";

    return queueLength;
}
