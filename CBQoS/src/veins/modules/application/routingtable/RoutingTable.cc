/*
 * Copyright (C) 2018 Elisa Rojas(1), Hedayat Hosseini(2), Carles Gomez(3);
 *                    (1) GIST, University of Alcala, Spain.
 *                    (2) CEIT, Amirkabir University of Technology (Tehran Polytechnic), Iran.
 *                    (3) UPC, Castelldefels, Spain.
 *                    OMNeT++ 5.2.1 & INET 3.6.3
 *                    Implementation of Parent Table for RPL
 *                    Developed in OMNeT++ 5.2.1 & INET 3.6.3
*/
/*
 * Copyright (C) 2020 Elisa Rojas(1), Hedayat Hosseini(2), Mehrnoush Naeini(3);
 *                    (1) GIST, University of Alcala, Spain.
 *                    (2) CEIT, Amirkabir University of Technology (Tehran Polytechnic), Iran.
 *                    (3) @Mehrnoush: Inja benevis
 *                    Implementation of routing table for CBQoS VANET routing protocol
 *                    Developed in OMNeT++ 5 & VEINs4.4
 * Main paper:
 * Lakas, A., Fekair, M.E.A., Korichi, A. and Lagraa, N., 2019.
 * A multiconstrained QoS-compliant routing scheme for highway-based vehicular networks.
 * Wireless Communications and Mobile Computing, 2019.
 */
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "src/veins/modules/application/routingtable/RoutingTable.h"

//#include <map>
#include <vector>
#include <math.h>


Define_Module(RoutingTable);

std::ostream& operator<<(std::ostream& os, const RoutingTable::RouteEntry& entry)
{
    os << "{Path ID=" << entry.pathId << ", Scout ID=" << entry.scoutId << ", Dest=" << entry.dest << ", CH Dest=" << entry.chDest << ", CH Next=" << entry.chNext << ", QoS.ABE+=" << entry.qos.abePlus << ", QoS.Delay=" << entry.qos.delay << ", QoS.Jitter=" << entry.qos.jitter << ", QoS.LET=" << entry.qos.let << ", QoS.Alpha=" << entry.qos.alpha << ", QoS.Beta=" << entry.qos.beta << ", QoS.Gamma=" << entry.qos.gamma << ", QoS.Delta=" << entry.qos.delta << ", QoS.Val=" << entry.qos.val << ", Hop Count=" << entry.hopCount << ", TTL=" << entry.ttl << "}";
    return os;
}

RoutingTable::RoutingTable()
{
    maxRoutes = -1; //Unlimited
}

void RoutingTable::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if(stage == 0){
        maxRoutes = par("maxRoutes");

        WATCH_VECTOR(routingTable);
    }

}

void RoutingTable::handleMessage(cMessage *)
{
    throw cRuntimeError("RoutingTable::handleMessage: This module doesn't process messages");
}

int RoutingTable::getNumberOfRoutes() const
{
    return routingTable.size();
}


/*
 * Add a new Entry to routingTable.
 * -1 if not added. 0 if it is new. 1 if it is updated.
 */

bool RoutingTable::updateTable(int pathId, int scoutId, int dest, int chDest, int chNext, const QoS &qos, int hopCount, int ttl)
{
    Enter_Method("RoutingTable::updateTable()");

    for (unsigned int i = 0; i < routingTable.size(); i++){
        if (dest == routingTable.at(i).dest){
            // Update existing entry
            RouteEntry entry = routingTable.at(i);
            EV << "Updating entry in Routing Table, old entry=> " << entry << endl; //Path ID:"  << entry.pathId << " Scout ID: " << entry.scoutId << " Dest: " << entry.dest << " CH Dest: " << entry.chDest << " CH Next: " << entry.chNext << "\n";
            entry.pathId = pathId;
            entry.scoutId = scoutId;
            entry.chDest = chDest;
            entry.chNext = chNext;
            entry.qos = qos;
            entry.hopCount = hopCount;
            entry.ttl = ttl;
            return 1;
        }
    }

    if ((maxRoutes != -1) && (getNumberOfRoutes() == maxRoutes)){ //If there is not a room,
        return -1;
    }
    routingTable.push_back(RouteEntry(pathId, scoutId, dest, chDest, chNext, qos, hopCount, ttl));
    EV << "A new entry was added to the Routing Table: " << RouteEntry(pathId, scoutId, dest, chDest, chNext, qos, hopCount, ttl) << "\n";
    return 0;
}
/*
const RoutingTable::RouteEntry *RoutingTable::getRouteEntry(int dest) const
{
    if (routingTable.size() == 0)
        return nullptr;

    for (unsigned int i = 0; i < routingTable.size(); i++) {
        if (routingTable.at(i).dest == dest) {
            return &routingTable.at(i);
        }
    }
    return nullptr;
}
*/
void RoutingTable::printState() const
{
    EV << endl << "Routing Table" << endl;
    for (unsigned int i = 0; i < routingTable.size(); i++){
        EV << routingTable.at(i) << endl;
    }
}

void RoutingTable::clearTable()
{
    routingTable.clear();
}

RoutingTable::~RoutingTable()
{
    clearTable();
}
