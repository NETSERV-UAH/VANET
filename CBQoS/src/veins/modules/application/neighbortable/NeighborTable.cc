/*
 * Copyright (C) 2018 Elisa Rojas(1), Hedayat Hosseini(2);
 *                    (1) GIST, University of Alcala, Spain.
 *                    (2) CEIT, Amirkabir University of Technology (Tehran Polytechnic), Iran.
 *                    OMNeT++ 5.2.1 & INET 3.6.3
 *                    Implementation of parent table for RPL
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

#include "src/veins/modules/application/neighbortable/NeighborTable.h"

//#include <map>
#include <vector>
#include <math.h>


Define_Module(NeighborTable);

std::ostream& operator<<(std::ostream& os, const NeighborTable::NeighborEntry& entry)
{
    os << "{vehicleId = " << entry.vehicleId << ", messageId = " << entry.messageId << ", idleTime = " << entry.idleTime
            << ", degree = " << entry.degree << ", role = " << entry.role << ", averageSpeed = " << entry.averageSpeed
            << ", gpsPosition = " << entry.gpsPosition << ", creationTime = " << entry.creationTime << ", qosValue = "
            << entry.qosValue << ", clusterHeadId = " << entry.clusterHeadId << ", speedDifference = " << entry.speedDifference
            << ", nbReceivedHello = " << entry.nbReceivedHello << ", direction = " << entry.direction << ", l = " << entry.l
            << ", bw = " << entry.bw << ", d = " << entry.d << ", j = " << entry.j << ", speedDifference = " << entry.speedDifference << "}";
    return os;
}

NeighborTable::NeighborTable()
{
    maxNeighbors = -1; //Unlimited
}

void NeighborTable::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if(stage == 0){
        maxNeighbors = par("maxNeighbors");

        WATCH_VECTOR(neighborTable);
    }

}

void NeighborTable::handleMessage(cMessage *)
{
    throw cRuntimeError("RoutingTable::handleMessage: This module doesn't process messages");
}

int NeighborTable::getNumberOfNeighbors() const
{
    return neighborTable.size();
}


/*
 * Add a new Entry to routingTable.
 * -1 if not added. 0 if it is new. 1 if it is updated.
 */

bool NeighborTable::updateTable(int vehicleId, int messageId, simtime_t idleTime, double degree, double role, double averageSpeed, Coord gpsPosition, simtime_t creationTime, double qosValue, int clusterHeadId, double direction, double l, double bw, double d, double j, double speedDifference)
{
    Enter_Method("NeighborTable::updateTable()");

    for (unsigned int i = 0; i < neighborTable.size(); i++){
        if (neighborTable.at(i).vehicleId == vehicleId){
            // Update the existing entry
            NeighborEntry entry = neighborTable.at(i);
            EV << "Updating entry in Routing Table, old entry=> " << entry << endl; //Path ID:"  << entry.pathId << " Scout ID: " << entry.scoutId << " Dest: " << entry.dest << " CH Dest: " << entry.chDest << " CH Next: " << entry.chNext << "\n";
            entry.vehicleId = vehicleId;
            entry.messageId = messageId;
            entry.idleTime = idleTime;
            entry.degree = degree;
            entry.role = role;
            entry.averageSpeed = averageSpeed;
            entry.gpsPosition = gpsPosition;
            entry.creationTime = creationTime;
            entry.qosValue = qosValue;
            entry.clusterHeadId = clusterHeadId;
            entry.nbReceivedHello++;
            entry.direction = direction;
            entry.l = l;
            entry.bw = bw;
            entry.d = d;
            entry.j = j;
            entry.speedDifference = speedDifference;
            return 1;
        }
    }

    if ((maxNeighbors != -1) && (getNumberOfNeighbors() == maxNeighbors)){ //If there is not a room,
        return -1;
    }
    //Adding a new entry
    int nbReceivedHello = 1;
    neighborTable.push_back(NeighborEntry(vehicleId, messageId, idleTime, degree, role, averageSpeed, gpsPosition, creationTime, qosValue, clusterHeadId, nbReceivedHello, direction, l, bw, d, j, speedDifference));
    EV << "A new entry was added to the NeighborsTable: " << NeighborEntry(vehicleId, messageId, idleTime, degree, role, averageSpeed, gpsPosition, creationTime, qosValue, clusterHeadId, nbReceivedHello, direction, l, bw, d, j, speedDifference) << endl;
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
void NeighborTable::printState() const
{
    EV << endl << "NeighborTable" << endl;
    for (unsigned int i = 0; i < neighborTable.size(); i++){
        EV << neighborTable.at(i) << endl;
    }
}

void NeighborTable::clearTable()
{
    neighborTable.clear();
}

NeighborTable::~NeighborTable()
{
    clearTable();
}
