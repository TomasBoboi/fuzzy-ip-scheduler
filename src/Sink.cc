#include "src/Sink.h"

Define_Module(Sink);

void Sink::initialize()
{
    packetLifetimeSignal_nrtLp = registerSignal("packetLifetime_nrtLp");
    packetLifetimeSignal_nrtHp = registerSignal("packetLifetime_nrtHp");
    packetLifetimeSignal_rtLp = registerSignal("packetLifetime_rtLp");
    packetLifetimeSignal_rtHp = registerSignal("packetLifetime_rtHp");

    packetCount_nrtLp = 0;
    packetDelay_nrtLp = 0;
    averageDelay_nrtLp = 0.0;

    packetCount_nrtHp = 0;
    packetDelay_nrtHp = 0;
    averageDelay_nrtHp = 0.0;

    packetCount_rtLp = 0;
    packetDelay_rtLp = 0;
    averageDelay_rtLp = 0.0;

    packetCount_rtHp = 0;
    packetDelay_rtHp = 0;
    averageDelay_rtHp = 0.0;
}

void Sink::handleMessage(cMessage *msg)
{
    simtime_t packetLifetime = simTime().inUnit(SIMTIME_US) - msg->getCreationTime().inUnit(SIMTIME_US);

    EV << "SINK: received " << msg->getName() << " from " << msg->getSenderModule()->getName() << "\n";
    EV << "      packet lifetime: "
       << packetLifetime.inUnit(SimTimeUnit::SIMTIME_US) << "us\n";

    if(!strcmp(msg->getName(), "NRT_LP_IP_PACKET"))
    {
        packetCount_nrtLp++;
        packetDelay_nrtLp += (unsigned long long)(packetLifetime.dbl());
        averageDelay_nrtLp = packetDelay_nrtLp / packetCount_nrtLp;

        emit(packetLifetimeSignal_nrtLp, averageDelay_nrtLp);
    }
    else if(!strcmp(msg->getName(), "NRT_HP_IP_PACKET"))
    {
        packetCount_nrtHp++;
        packetDelay_nrtHp += (unsigned long long)(packetLifetime.dbl());
        averageDelay_nrtHp = packetDelay_nrtHp / packetCount_nrtHp;

        emit(packetLifetimeSignal_nrtHp, averageDelay_nrtHp);
    }
    else if(!strcmp(msg->getName(), "RT_LP_IP_PACKET"))
    {
        packetCount_rtLp++;
        packetDelay_rtLp += (unsigned long long)(packetLifetime.dbl());
        averageDelay_rtLp = packetDelay_rtLp / packetCount_rtLp;

        emit(packetLifetimeSignal_rtLp, averageDelay_rtLp);
    }
    else if(!strcmp(msg->getName(), "RT_HP_IP_PACKET"))
    {
        packetCount_rtHp++;
        packetDelay_rtHp += (unsigned long long)(packetLifetime.dbl());
        averageDelay_rtHp = packetDelay_rtHp / packetCount_rtHp;

        emit(packetLifetimeSignal_rtHp, averageDelay_rtHp);
    }

    delete msg;
    EV << "      deleted successfully\n";
}

int Sink::getAverageDelay_rtHp()
{
    return averageDelay_rtHp;
}
