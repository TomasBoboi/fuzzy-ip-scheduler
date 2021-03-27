#ifndef _FLC_GEN_H_
#define _FLC_GEN_H_

#include <omnetpp.h>

using namespace omnetpp;

class GeneratorFLC : public cSimpleModule
{
    private:
        cMessage *sendMessageEvent;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

#endif
