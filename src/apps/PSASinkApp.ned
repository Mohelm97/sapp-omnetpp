package networkpaper.apps;

import inet.applications.contract.IApp;
simple PSASinkApp like IApp
{
    parameters:
        string topic;
        int subTimeout = default(30);
    gates:
        input socketIn;
        output socketOut;
}