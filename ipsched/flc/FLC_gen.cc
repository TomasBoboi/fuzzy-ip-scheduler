#include "FLC_gen.h"

Define_Module(GeneratorFLC);

using namespace omnetpp;

void GeneratorFLC::initialize()
{
    flc_time = 1;

    sendMessageEvent = new cMessage("sendMessageEvent");
    scheduleAt(0, sendMessageEvent);
}

void GeneratorFLC::handleMessage(cMessage *msg)
{
    ASSERT(msg == sendMessageEvent);
    EV << " START FLC\n";
    
    send(new cMessage("start_flc"), "out");
    scheduleAt(simTime() + flc_time, sendMessageEvent);
}