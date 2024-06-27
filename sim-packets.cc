#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("PacketSimulatorVPIFO");

void scheduleClientApp()

int main(int argc, char* argv[]) {
    CommandLine cmd;
    cmd.Parse(argc, argv);

    // Create spine-leaf topology

    // Create servers and switches
    NodeContainer servers, leafSwitches, spineSwitches;
    servers.Create(144);
    leafSwitches.Create(9);
    spineSwitches.Create(4);

    // Link leaf switches to corresponding server
    PointToPointHelper accessLinks;
    accessLinks.SetDeviceAttribute("DataRate", StringValue("4Gbps"));

    for (uint32_t i=0; i < servers.GetN(); i++) {
        // Each switch gets 16 servers
        accessLinks.Install(servers.Get(i), leafSwitches.Get(i % leafSwitches.GetN()))
    }

    // Link leaf switches to spine switches
    PointToPointHelper switchLinks;
    switchLinks.SetDeviceAttributes("DataRate", StringValue("10Gbps"));

    for (uint32_t i=0; i < leafSwitches.GetN(); i++) {
        for (uint32_t j=0; j < spineSwitches.GetN(); j++) {
            // One link per two types of switches
            switchLinks.Install(
                leafSwitches.Get(i),   
                spineSwitches.Get(j)
            );
        }
    }

    // Create tenants and tenant groups

    


    // Run and destroy simulator
    Simulator::Run();
    Simulator::Destroy();
}