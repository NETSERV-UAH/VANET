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

#include "src/veins/modules/application/mprtable/MPRTable.h"

//#include <map>
#include <vector>
#include <math.h>


Define_Module(MPRTable);

std::ostream& operator<<(std::ostream& os, const MPRTable::MPREntry& entry)
{
    os << "{ID=" << entry.id << ", CHId=" << entry.CHId << ", CHN=" << entry.CHNext << "}";
    return os;
}

MPRTable::MPRTable()
{
    maxMPRs = -1; //Unlimited
}

void MPRTable::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if(stage == 0){
        maxMPRs = par("maxMPRs");

        WATCH_VECTOR(mprTable);
    }

}

void MPRTable::handleMessage(cMessage *)
{
    throw cRuntimeError("MPRTable::handleMessage: This module doesn't process messages");
}

int MPRTable::getNumberOfMPRs() const
{
    return mprTable.size();
}


/*
 * Add a new Entry to routingTable.
 * -1 if not added. 0 if it is new. 1 if it is updated.
 */

bool MPRTable::updateTable(int id, int CHId, int CHNext)
{
    Enter_Method("MPRTable::updateTable()");

    for (unsigned int i = 0; i < mprTable.size(); i++){
        if (id == mprTable.at(i).id){
            // Update existing entry
            MPREntry entry = mprTable.at(i);
            EV << "Updating entry in MPR Table, old entry=> " << entry << endl; //Path ID:"  << entry.pathId << " Scout ID: " << entry.scoutId << " Dest: " << entry.dest << " CH Dest: " << entry.chDest << " CH Next: " << entry.chNext << "\n";
            entry.id = id;
            entry.CHId = CHId;
            entry.CHNext = CHNext;
            return 1;
        }
    }

    if ((maxMPRs != -1) && (getNumberOfMPRs() == maxMPRs)){ //If there is not a room,
        return -1;
    }
    mprTable.push_back(MPREntry(id, CHId, CHNext));
    EV << "A new entry was added to the MPRsTable: " << MPREntry(id, CHId, CHNext) << "\n";
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
void MPRTable::printState() const
{
    EV << endl << "MPRTable" << endl;
    for (unsigned int i = 0; i < mprTable.size(); i++){
        EV << mprTable.at(i) << endl;
    }
}

void MPRTable::clearTable()
{
    mprTable.clear();
}

MPRTable::~MPRTable()
{
    clearTable();
}
