package ipsched;

simple Queue
{
    parameters:
        // the rate at which the queues log their lengths, in microseconds
        int queueLengthLoggingRate;
        // signals for each of the queue's lengths
        @signal[nrtLpQueueLength](type="long");
        @statistic[nrtLpQueueLength](title="NRT_LP Queue Length"; source="nrtLpQueueLength"; record=vector,stats);
        @signal[nrtHpQueueLength](type="long");
        @statistic[nrtHpQueueLength](title="NRT_HP Queue Length"; source="nrtHpQueueLength"; record=vector,stats);
        @signal[rtLpQueueLength](type="long");
        @statistic[rtLpQueueLength](title="RT_LP Queue Length"; source="rtLpQueueLength"; record=vector,stats);
        @signal[rtHpQueueLength](type="long");
        @statistic[rtHpQueueLength](title="RT_HP Queue Length"; source="rtHpQueueLength"; record=vector,stats);
    // end:parameters
    
    gates:
        // input gates from the users of a certain category
        input in[];
        // input gate from the scheduler, to control the sending of the IP packets
        input schedulerControl_in;
        // main output gate, to send the packets from the queue to the scheduler
        output out;
    // end:gates
}
