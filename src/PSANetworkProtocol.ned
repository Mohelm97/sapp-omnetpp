package networkpaper;

import inet.networklayer.contract.INetworkProtocol;
import inet.networklayer.common.InterfaceTable;
module PSANetworkProtocol like INetworkProtocol
{
    parameters:
        int hcMaxSubscribe;
        int hcMaxPublish;
        int subCleanTimeout = default(40);
        string interfaceTableModule = default(absPath("^.^.interfaceTable"));
        @display("i=block/switch");
        @class(PSANetworkProtocol);
    gates:
        input transportIn;
        output transportOut;
        input queueIn;
        output queueOut;
}
