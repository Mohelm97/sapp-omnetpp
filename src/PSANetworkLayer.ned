package networkpaper;

import inet.networklayer.contract.INetworkLayer;

module PSANetworkLayer like INetworkLayer
{
    parameters:
        @display("i=block/fork;bgb=381,190");
    gates:
        input transportIn;
        output transportOut;
        input ifIn;
        output ifOut;
    submodules:
        np: PSANetworkProtocol {
            parameters:
                @display("p=191,105;q=queue");
        }
    connections:
        transportIn --> { @display("m=n"); } --> np.transportIn;
        np.transportOut --> { @display("m=n"); } --> transportOut;
        
        ifIn --> np.queueIn;
        np.queueOut --> ifOut;
}