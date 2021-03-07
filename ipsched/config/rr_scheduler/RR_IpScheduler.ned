package ipsched.config.rr_scheduler;

import ipsched.User;
import ipsched.Sink;

network RR_IpScheduler
{
    parameters:
        // the number of users in each priority category
        int nrtLpUsersNo;
        int nrtHpUsersNo;
        int rtLpUsersNo;
        int rtHpUsersNo;
        
        // display properties
        @display("bgb=617,386");
    // end:parameters

    submodules:
        // the IP Scheduler is composed of three parts: the users, the packet handler, and the sink
        // the users are represented as an array, with one array for each priority type
        nrtLpUsers[nrtLpUsersNo]: User {

            @display("p=106,65;i=block/users");
        }
        nrtHpUsers[nrtHpUsersNo]: User {

            @display("p=106,147;i=block/users");
        }
        rtLpUsers[rtLpUsersNo]: User {

            @display("i=block/users;p=106,225");
        }
        rtHpUsers[rtHpUsersNo]: User {

            @display("i=block/users;p=106,308");
        }
        
        // the packet handler contains the queues and the scheduler, and controls the flow of the packets
        packetHandler: RR_PacketHandler {

            @display("p=394,186;i=abstract/dispatcher");
        }
        
        // the sink is where the packets end up, and is where the statistics-collection takes place
        sink: Sink {

            @display("i=block/sink;p=572,186");
        }
    // end:submodules

    connections:
        // connect each user to its corresponding queue in the packet handler
        for i=0..nrtLpUsersNo - 1 {
            nrtLpUsers[i].out --> packetHandler.nrtLp_in++;
        }
        for i=0..nrtHpUsersNo - 1 {
            nrtHpUsers[i].out --> packetHandler.nrtHp_in++;
        }
        for i=0..rtLpUsersNo - 1 {
            rtLpUsers[i].out --> packetHandler.rtLp_in++;
        }
        for i=0..rtHpUsersNo - 1 {
            rtHpUsers[i].out --> packetHandler.rtHp_in++;
        }
        
        // the output of the packet handler to the sink, so the packets end up there
        packetHandler.out --> sink.in;
    // end:connections
}