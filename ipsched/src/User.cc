#include "ipsched/src/User.h"

Define_Module(User);

void User::initialize()
{
    readyToSendMessage = new cMessage("RTS");

    scheduleAt(
        simTime() + SimTime(par("packetGenerationDelay").doubleValue(),
                            SIMTIME_US)
                        .trunc(SIMTIME_US),
        readyToSendMessage);
}

void User::handleMessage(cMessage *msg)
{
    if (msg == readyToSendMessage)
    {
        IpPacket *ipPacket = generateIpPacket();
        send(ipPacket, "out");

        scheduleAt(
            simTime() + SimTime(par("packetGenerationDelay").doubleValue(),
                                SIMTIME_US)
                            .trunc(SIMTIME_US),
            readyToSendMessage);

        EV << getName() << ":\tsent message";
    }
}

IpPacket *User::generateIpPacket()
{
    IpPacket *ipPacket;

    if(!strcmp(getName(), "nrtLpUsers"))
    {
        ipPacket = new IpPacket("NRT_LP_IP_PACKET");
    }
    else if(!strcmp(getName(), "nrtHpUsers"))
    {
        ipPacket = new IpPacket("NRT_HP_IP_PACKET");
    }
    else if(!strcmp(getName(), "rtLpUsers"))
    {
        ipPacket = new IpPacket("RT_LP_IP_PACKET");
    }
    else if(!strcmp(getName(), "rtHpUsers"))
    {
        ipPacket = new IpPacket("RT_HP_IP_PACKET");
    }

    ipPacket->setByteLength(par("ipPacketSize").intValue());

    EV << getName() << ":\tgenerated packet of " << ipPacket->getByteLength()
       << " bytes\n";

    return ipPacket;
}
