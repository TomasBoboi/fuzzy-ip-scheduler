#include "RoundRobinScheduler.h"

#include "ipsched/src/Queue.h"

Define_Module(RoundRobinScheduler);

RoundRobinScheduler::RoundRobinScheduler()
{
    readyToScheduleMessage = nullptr;
}

RoundRobinScheduler::~RoundRobinScheduler()
{
    cancelAndDelete(readyToScheduleMessage);
}

void RoundRobinScheduler::initialize()
{
    lastServed_nrtLp = simTime();
    lastServed_nrtHp = simTime();
    lastServed_rtLp = simTime();
    lastServed_rtHp = simTime();

    readyToScheduleMessage = new cMessage("RTSch");

    scheduleAt(simTime(), readyToScheduleMessage);
}

void RoundRobinScheduler::handleMessage(cMessage *msg)
{
    if (msg == readyToScheduleMessage)
    {
        simtime_t times[4] = {lastServed_nrtLp, lastServed_nrtHp,
                lastServed_rtLp, lastServed_rtHp};
        sortTimes(times);
        bool sent = false;

        for(int i = 0; i < 4 && !sent; i++)
        {
            if (times[i] == lastServed_nrtLp)
            {
                if (getQueueLength("nrtLpQueue") > 0)
                {
                    send(new cMessage("schedulerMessage"), "nrtLpQueueControl_out");
                    sent = true;
                }
                lastServed_nrtLp = simTime();
            }
            else if (times[i] == lastServed_nrtHp)
            {
                if (getQueueLength("nrtHpQueue") > 0)
                {
                    send(new cMessage("schedulerMessage"), "nrtHpQueueControl_out");
                    sent = true;
                }
                lastServed_nrtHp = simTime();
            }
            else if (times[i] == lastServed_rtLp)
            {
                if (getQueueLength("rtLpQueue") > 0)
                {
                    send(new cMessage("schedulerMessage"), "rtLpQueueControl_out");
                    sent = true;
                }
                lastServed_rtLp = simTime();
            }
            else if (times[i] == lastServed_rtHp)
            {
                if (getQueueLength("rtHpQueue") > 0)
                {
                    send(new cMessage("schedulerMessage"), "rtHpQueueControl_out");
                    sent = true;
                }
                lastServed_rtHp = simTime();
            }
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

void RoundRobinScheduler::sortTimes(simtime_t times[4])
{
    bool sw;
    int i;
    simtime_t aux;

    do{
        sw = false;
        for(i = 0; i < 3; i++)
            if(times[i] > times[i+1])
            {
                aux = times[i];
                times[i] = times[i+1];
                times[i+1] = aux;
                sw = true;
            }
    }while(sw);
}

int RoundRobinScheduler::getQueueLength(const char *queueName)
{
    int queueLength;

    Queue *queue = check_and_cast<Queue *>(
        getParentModule()->getSubmodule(queueName));
    queueLength = queue->getQueueLength();

    EV << queue->getName() << " length: " << queueLength << "\n";

    return queueLength;
}
