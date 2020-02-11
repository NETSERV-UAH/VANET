//
// Copyright (C) 2008 Christoph Sommer <christoph.sommer@informatik.uni-erlangen.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// Copyright (C) 2020 Elisa Rojas(1), Hedayat Hosseini(2), Mehrnoush Naeini(3);
//                    (1) GIST, University of Alcala, Spain.
//                    (2) CEIT, Amirkabir University of Technology (Tehran Polytechnic), Iran.
//                    (2) @Mehrnoush: Inja benevisin
//                    Implementation of routing table for CBQoS VANET routing protocol
//					  Developed in OMNeT++ 5 & VEINs4.4
//Main paper:
//Lakas, A., Fekair, M.E.A., Korichi, A. and Lagraa, N., 2019.
//A multiconstrained QoS-compliant routing scheme for highway-based vehicular networks.
//Wireless Communications and Mobile Computing, 2019.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

//EXTRA BEGIN
//package org.car2x.veins.nodes;
package cbqos.src.veins.nodes;

import cbqos.src.veins.modules.application.contract.IRoutingTable;
import cbqos.src.veins.modules.application.routingtable.RoutingTable;
import cbqos.src.veins.modules.application.neighbortable.NeighborTable;
import cbqos.src.veins.modules.application.membertable.MemberTable;
import cbqos.src.veins.modules.application.mprtable.MPRTable;
//EXTRA END
import org.car2x.veins.base.modules.*;

//EXTRA BEGIN
//import org.car2x.veins.modules.nic.Nic80211p;
import cbqos.src.veins.modules.nic.Nic80211pCBQoS;

//module Car
module CBQoSCar
{
    parameters:
        string applType; //type of the application layer
        //EXTRA BEGIN
        //string nicType = default("Nic80211p"); // type of network interface card
        string nicType = default("Nic80211pCBQoS"); // type of network interface card
        //EXTRA END
        string veinsmobilityType; //type of the mobility module
        //EXTRA BEGIN
        string routingTableType = default("RoutingTable");
      //  string neighborTableType = default("NeighborTable");
        //EXTRA END
    gates:
        input veinsradioIn; // gate for sendDirect
    submodules:
        appl: <applType> like org.car2x.veins.base.modules.IBaseApplLayer {
            parameters:
                @display("p=60,36");
        }

        nic: <nicType> like org.car2x.veins.modules.nic.INic80211p {
            parameters:
                @display("p=60,174");
        }

        veinsmobility: <veinsmobilityType> like org.car2x.veins.base.modules.IMobility {
            parameters:
                @display("p=167,174;i=block/table2");
        }

        //EXTRA BEGIN
        routingTable: <routingTableType> like IRoutingTable {
            parameters:
                @display("p=167,36");
        }

        neighborTable: NeighborTable {//<neighborTableType> {
            parameters:
                @display("p=264,36");
        }

        memberTable: MemberTable {//<memberTableType> {
            parameters:
                @display("p=264,174");
        }

        mprTable: MPRTable {//<mprTableType> {
            parameters:
                @display("p=264,107");
        }
		//EXTRA END

    connections:
        nic.upperLayerOut --> appl.lowerLayerIn;
        nic.upperLayerIn <-- appl.lowerLayerOut;
        nic.upperControlOut --> appl.lowerControlIn;
        nic.upperControlIn <-- appl.lowerControlOut;

        veinsradioIn --> nic.radioIn;

}
