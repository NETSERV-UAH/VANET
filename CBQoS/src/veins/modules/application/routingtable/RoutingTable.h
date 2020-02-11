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

#ifndef CBQOS_VEINS_MODULES_APPLICATION_ROUTINGTABLE_ROUTINGTABLE_H_
#define CBQOS_VEINS_MODULES_APPLICATION_ROUTINGTABLE_ROUTINGTABLE_H_

#include "veins/base/utils/MiXiMDefs.h"

/**
 * This module handles the mapping between next cluster head and destination cluster head. See the NED definition for details.
 */
class RoutingTable : public cSimpleModule
{
  protected:
    int maxRoutes; //-1 means the unlimited value

    struct QoS_Struct{
        double abePlus;
        double delay;
        double jitter;
        double let;
        double alpha;
        double beta;
        double gamma;
        double delta;
        double val;

        QoS_Struct() {}
        QoS_Struct(double abePlus, double delay, double jitter, double let, double alpha, double beta, double gamma, double delta, double val) :
            abePlus (abePlus), delay (delay), jitter (jitter), let (let), alpha (alpha), beta (beta), gamma (gamma), delta (delta), val (val) {}
        QoS_Struct(const struct QoS_Struct& qos2) :
            abePlus (qos2.abePlus), delay (qos2.delay), jitter (qos2.jitter), let (qos2.let), alpha (qos2.alpha), beta (qos2.beta), gamma (qos2.gamma), delta (qos2.delta), val (qos2.val) {}
    };

    typedef struct QoS_Struct QoS;

    struct RouteEntry
    {
        int pathId;
        int scoutId;
        int dest;
        int chDest;
        int chNext;
        QoS qos;
        int hopCount;
        int ttl;

        RouteEntry() {}
        RouteEntry(int pathId, int scoutId, int dest, int chDest, int chNext, const QoS& qos, int hopCount, int ttl) :
            pathId(pathId), scoutId(scoutId), dest(dest), chDest(chDest), chNext(chNext), qos(qos), hopCount(hopCount), ttl(ttl) {}
        //RouteEntry(const RouteEntry& entry) :
        //pathId(entry.pathId), scoutId(entry.scoutId), dest(entry.dest), chDest(entry.chDest), chNext(entry.chNext), qos(entry.qos), hopCount(entry.hopCount), ttl(entry.ttl) {}
    };

    friend std::ostream& operator<<(std::ostream& os, const RouteEntry& entry);

    //typedef struct RouteEntry RouteEntryType;
    //typedef std::vector<RouteEntry> Table;

    typedef std::vector<RouteEntry> Table;
    Table routingTable;


  protected:

    virtual int numInitStages() const override { return 1; }

    virtual void initialize(int stage) override;

    virtual void handleMessage(cMessage *msg) override;

  public:

    RoutingTable();

    ~RoutingTable();

  // Table management

protected:

    //virtual const RouteEntry *getRouteEntry(int dest) const;
    //const QoS *getQos(int dest) const;

  public:

    virtual int getNumberOfRoutes() const;

    virtual bool updateTable(int pathId, int scoutId, int dest, int chDest, int chNext, const QoS &qos, int hopCount, int ttl);

    virtual void printState() const;

    virtual void clearTable();

};


#endif // ifndef CBQOS_VEINS_MODULES_APPLICATION_ROUTINGTABLE_ROUTINGTABLE_H_

