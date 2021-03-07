package ipsched.config.wrr_scheduler;

import ipsched.Queue;
import ipsched.scheduler.WRRScheduler;

module WRR_PacketHandler
{
    parameters:
        // the number of users in each priority class */
        int nrtLpUsersNo;
        int nrtHpUsersNo;
        int rtLpUsersNo;
        int rtHpUsersNo;
        
        // the datarate with which the packets are transmitted to the sink
        double ipChannelDatarate @unit(Mbps);
    // end:parameters

    gates:
        // input gates for each queue, in all four priority classes
        input nrtLp_in[];
        input nrtHp_in[];
        input rtLp_in[];
        input rtHp_in[];
        
        // main output gate, to send the packets to the sink
        output out;
    // end:gates

    types:
        // the channel through which the data packets are transmitted
        channel PacketChannel extends ned.DatarateChannel
        {
            datarate = ipChannelDatarate;
        }
    // end:types

    submodules:
        // the packet handler contains two modules: the scheduler and the queues
        scheduler: WRRScheduler {
            @display("i=block/dispatch;p=249,192");
        }
        
        // there are four queues, one for each priority class
        nrtLpQueue: Queue {
            parameters:
                @display("i=block/queue;p=96,303");
        }
        nrtHpQueue: Queue {
            parameters:
                @display("i=block/queue;p=96,231");
        }
        rtLpQueue: Queue {
            parameters:
                @display("i=block/queue;p=96,153");
        }
        rtHpQueue: Queue {
            parameters:
                @display("i=block/queue;p=96,73");
        }
    // end:submodules

    connections:
        // connect each user to its corresponding queue
        for i=0..nrtLpUsersNo - 1 {
            nrtLp_in[i] --> nrtLpQueue.in++;
        }
        for i=0..nrtHpUsersNo - 1 {
            nrtHp_in[i] --> nrtHpQueue.in++;
        }
        for i=0..rtLpUsersNo - 1 {
            rtLp_in[i] --> rtLpQueue.in++;
        }
        for i=0..rtHpUsersNo - 1 {
            rtHp_in[i] --> rtHpQueue.in++;
        }
        
        // connect each queue to the scheduler
        nrtLpQueue.out --> scheduler.in++;
        nrtHpQueue.out --> scheduler.in++;
        rtLpQueue.out --> scheduler.in++;
        rtHpQueue.out --> scheduler.in++;
        
        // connect the scheduler's control lines to the queues, to control the flow of the packets
        scheduler.nrtLpQueueControl_out --> nrtLpQueue.schedulerControl_in;
        scheduler.nrtHpQueueControl_out --> nrtHpQueue.schedulerControl_in;
        scheduler.rtLpQueueControl_out --> rtLpQueue.schedulerControl_in;
        scheduler.rtHpQueueControl_out --> rtHpQueue.schedulerControl_in;
        
        // connect the main output gate,, via the packet channel, to send the packets to the sink
        scheduler.out --> PacketChannel --> out;
    // end:connections
}