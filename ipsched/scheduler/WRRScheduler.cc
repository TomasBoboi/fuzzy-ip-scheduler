#include "WRRScheduler.h"

#include "ipsched/src/Queue.h"

Define_Module(WRRScheduler);

WRRScheduler::WRRScheduler() {
    readyToScheduleMessage = nullptr;
}

WRRScheduler::~WRRScheduler() {
    cancelAndDelete(readyToScheduleMessage);
}

void WRRScheduler::parseWeights(const char *weightsAsString) {
    sscanf(weightsAsString, "%d %d %d %d", (userWeights), (userWeights + 1),
            (userWeights + 2), (userWeights + 3));
}

void WRRScheduler::initialize() {
    parseWeights(par("userWeights"));

    lastServed_nrtLp = simTime();
    lastServed_nrtHp = simTime();
    lastServed_rtLp = simTime();
    lastServed_rtHp = simTime();

    readyToScheduleMessage = new cMessage("RTSch");
    scheduleAt(simTime(), readyToScheduleMessage);
}

void WRRScheduler::handleMessage(cMessage *msg) {
    if (msg == readyToScheduleMessage) {
        bool sent = false;

        simtime_t lastServedWeightedDelta_nrtLp = (simTime() - lastServed_nrtLp)
                * userWeights[0];
        simtime_t lastServedWeightedDelta_nrtHp = (simTime() - lastServed_nrtHp)
                * userWeights[1];
        simtime_t lastServedWeightedDelta_rtLp = (simTime() - lastServed_rtLp)
                * userWeights[2];
        simtime_t lastServedWeightedDelta_rtHp = (simTime() - lastServed_rtHp)
                * userWeights[3];

        simtime_t times[4] = { lastServedWeightedDelta_nrtLp,
                lastServedWeightedDelta_nrtHp, lastServedWeightedDelta_rtLp,
                lastServedWeightedDelta_rtHp };
        sortTimes(times);

        for(int i = 0; i < 4 && !sent; i ++)
        {
            if (times[i] == lastServedWeightedDelta_nrtLp) {
                if (getQueueLength("nrtLpQueue") > 0) {
                    send(new cMessage("schedulerMessage"), "nrtLpQueueControl_out");
                    sent = true;
                }
                lastServed_nrtLp = simTime();
            } else if (times[i] == lastServedWeightedDelta_nrtHp) {
                if (getQueueLength("nrtHpQueue") > 0) {
                    send(new cMessage("schedulerMessage"), "nrtHpQueueControl_out");
                    sent = true;
                }
                lastServed_nrtHp = simTime();
            } else if (times[i] == lastServedWeightedDelta_rtLp) {
                if (getQueueLength("rtLpQueue") > 0) {
                    send(new cMessage("schedulerMessage"), "rtLpQueueControl_out");
                    sent = true;
                }
                lastServed_rtLp = simTime();
            } else if (times[i] == lastServedWeightedDelta_rtHp) {
                if (getQueueLength("rtHpQueue") > 0) {
                    send(new cMessage("schedulerMessage"), "rtHpQueueControl_out");
                    sent = true;
                }
                lastServed_rtHp = simTime();
            }
        }

        if (!sent) {
            scheduleAt(
                    simTime()
                            + SimTime(
                                    par("packetGenerationDelay").doubleValue(),
                                    SIMTIME_US).trunc(SIMTIME_US),
                    readyToScheduleMessage);
        }
    } else {
        send(msg, "out");

        scheduleAt(
                gate("out")->getTransmissionChannel()->getTransmissionFinishTime(),
                readyToScheduleMessage);
    }
}

void WRRScheduler::sortTimes(simtime_t times[4]) {
    bool sw;
    int i;
    simtime_t aux;

    do {
        sw = false;
        for (i = 0; i < 3; i++)
            if (times[i] < times[i + 1]) {
                aux = times[i];
                times[i] = times[i + 1];
                times[i + 1] = aux;
                sw = true;
            }
    } while (sw);
}

int WRRScheduler::getQueueLength(const char *queueName) {
    int queueLength;

    Queue *queue = check_and_cast<Queue*>(
            getParentModule()->getSubmodule(queueName));
    queueLength = queue->getQueueLength();

    EV << queue->getName() << " length: " << queueLength << "\n";

    return queueLength;
}
