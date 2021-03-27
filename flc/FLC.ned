package flc;

simple FLC
{
    parameters: 
        xml config = xmldoc("FLC_conf.xml");
        int wantedDelay;

    gates:
        input in;
}