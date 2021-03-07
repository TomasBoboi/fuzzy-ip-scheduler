package ipsched.scheduler;

simple WRRScheduler
{
    parameters:
        // the users' weights, represented as a string
        string userWeights;
        // the user's packet generation delay, so the scheduler knows the incoming speed of the packets
        double packetGenerationDelay @unit(us);
    // end:parameters
    gates:
        // input gates, from the four different priority queues
        input in[];
        
        // output control gates, which control each queue independently
        output nrtLpQueueControl_out;
        output nrtHpQueueControl_out;
        output rtLpQueueControl_out;
        output rtHpQueueControl_out;
        
        // main output gate, to send the packets to the sink
        output out;
    // end:gates
}
