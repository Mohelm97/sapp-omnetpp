package networkpaper.apps;

import inet.applications.contract.IApp;
simple PSASourceApp like IApp
{
    parameters:
        string topic;
        double delay = default(0.1);
        double rate = default(0);
        bool needAcking = default(false);
    gates:
        input socketIn;
        output socketOut;
}