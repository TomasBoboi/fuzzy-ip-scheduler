simple Sink
{
    parameters:
        // we collect statistics about the packets
        // packet lifetime (average packet delayfrom user to sink)
        @signal[packetLifetime_nrtLp](type="simtime_t");
        @statistic[packetLifetime_nrtLp](title="NRT_LP IP Packet lifetime"; unit=us; record=vector,mean,min,max);
        
        @signal[packetLifetime_nrtHp](type="simtime_t");
        @statistic[packetLifetime_nrtHp](title="NRT_HP IP Packet lifetime"; unit=us; record=vector,mean,min,max);
        
        @signal[packetLifetime_rtLp](type="simtime_t");
        @statistic[packetLifetime_rtLp](title="RT_LP IP Packet lifetime"; unit=us; record=vector,mean,min,max);
        
        @signal[packetLifetime_rtHp](type="simtime_t");
        @statistic[packetLifetime_rtHp](title="RT_HP IP Packet lifetime"; unit=us; record=vector,mean,min,max);
    // end:parameters

    gates:
        // main input, where the packets enter
        input in;
    // end:gates
}
