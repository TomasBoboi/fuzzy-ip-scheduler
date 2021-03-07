#include "ipsched/src/Sink.h"

Define_Module(Sink);

void Sink::initialize()
{
    packetLifetimeSignal_nrtLp = registerSignal("packetLifetime_nrtLp");
    packetLifetimeSignal_nrtHp = registerSignal("packetLifetime_nrtHp");
    packetLifetimeSignal_rtLp = registerSignal("packetLifetime_rtLp");
    packetLifetimeSignal_rtHp = registerSignal("packetLifetime_rtHp");

    numberOfPacketsSignal = registerSignal("numberOfPacketsSignal");
}

void Sink::handleMessage(cMessage *msg)
{
    simtime_t packetLifetime = simTime() - msg->getCreationTime();
    packetLifetime = packetLifetime.inUnit(SIMTIME_US);
    long numberOfPackets = 1;

    EV << "SINK: received " << msg->getName() << " from " << msg->getSenderModule()->getName() << "\n";
    EV << "      packet lifetime: "
       << packetLifetime.inUnit(SimTimeUnit::SIMTIME_US) << "us\n";

    if(!strcmp(msg->getName(), "NRT_LP_IP_PACKET"))
    {
        emit(packetLifetimeSignal_nrtLp, packetLifetime);
    }
    else if(!strcmp(msg->getName(), "NRT_HP_IP_PACKET"))
    {
        emit(packetLifetimeSignal_nrtHp, packetLifetime);
    }
    else if(!strcmp(msg->getName(), "RT_LP_IP_PACKET"))
    {
        emit(packetLifetimeSignal_rtLp, packetLifetime);
    }
    else if(!strcmp(msg->getName(), "RT_HP_IP_PACKET"))
    {
        emit(packetLifetimeSignal_rtHp, packetLifetime);
    }

    emit(numberOfPacketsSignal, numberOfPackets);

    delete msg;
    EV << "      deleted successfully\n";
}
