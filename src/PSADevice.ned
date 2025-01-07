package networkpaper;

import inet.node.inet.AdhocHost;
module PSADevice extends AdhocHost
{
    parameters:
        @display("i=device/laptop");
        hasIpv4 = false;
        hasUdp = false;
        hasTcp = false;
        generic.typename = "PSANetworkLayer";
        hasGn = true;
}

