package networkpaper.simulations.Simple;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.AdhocHost;
import inet.physicallayer.wireless.unitdisk.UnitDiskRadioMedium;
import inet.visualizer.canvas.integrated.IntegratedCanvasVisualizer;
import inet.visualizer.contract.IIntegratedVisualizer;
import networkpaper.PSADevice;

network Simple
{
    parameters:
        int hcMaxSubscribe;
        int hcMaxPublish;
        **.hcMaxSubscribe = this.hcMaxSubscribe;
        **.hcMaxPublish = this.hcMaxPublish;
    submodules:
        visualizer: IntegratedCanvasVisualizer {
            parameters:
                @display("p=100,300;is=s");
        }
        radioMedium: UnitDiskRadioMedium {
            parameters:
                @display("p=100,200;is=s");
        }
        host_0: PSADevice {
            parameters:
                @display("p=200,100");
        }
        host_1: PSADevice {
            parameters:
                @display("p=400,100");
        }
        host_2: PSADevice {
            parameters:
                @display("p=600,100");
        }
        host_3: PSADevice {
            parameters:
                @display("p=800,100");
        }
        host_4: PSADevice {
            parameters:
                @display("p=1000,100");
        }
        host_5: PSADevice {
            parameters:
                @display("p=1200,100");
        }

        host_6: PSADevice {
            parameters:
                @display("p=200,300");
        }
        host_7: PSADevice {
            parameters:
                @display("p=400,300");
        }
        host_8: PSADevice {
            parameters:
                @display("p=600,300");
        }
        host_9: PSADevice {
            parameters:
                @display("p=800,300");
        }
        host_10: PSADevice {
            parameters:
                @display("p=1000,300");
        }
        host_11: PSADevice {
            parameters:
                @display("p=1200,300");
        }

        host_12: PSADevice {
            parameters:
                @display("p=200,500");
        }
        host_13: PSADevice {
            parameters:
                @display("p=400,500");
        }
        host_14: PSADevice {
            parameters:
                @display("p=600,500");
        }
        host_15: PSADevice {
            parameters:
                @display("p=800,500");
        }
        host_16: PSADevice {
            parameters:
                @display("p=1000,500");
        }
        host_17: PSADevice {
            parameters:
                @display("p=1200,500");
        }
}
