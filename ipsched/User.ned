package ipsched;

simple User
{
    parameters:
        // the size of an IP packet, which the user generates
        int ipPacketSize @unit(B);
        
        // the delay with which the users generate packets
        double packetGenerationDelay @unit(us);
    // end:parameters

    gates:
        // the main output gate, where the packets are sent to the packet handler
        output out;
    // end:gates
}
