#include "FLC_gen.h"

Define_Module(GeneratorFLC);

void GeneratorFLC::initialize()
{
    sendMessageEvent = new cMessage("sendMessageEvent");
    scheduleAt(simTime(), sendMessageEvent);
}

void GeneratorFLC::handleMessage(cMessage *msg)
{
    ASSERT(msg == sendMessageEvent);
    send(new cMessage("start_flc"), "out");
    scheduleAt(simTime() + par("flc_time"), sendMessageEvent);
}
