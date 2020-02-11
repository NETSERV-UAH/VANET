//
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

#ifndef DECIDER80211pCBQOS_H_
#define DECIDER80211pCBQOS_H_

#include "veins/modules/phy/Decider80211p.h"

class Decider80211pCBQoS: public Decider80211p {

public:
    Decider80211pCBQoS(DeciderToPhyInterface* phy, double sensitivity, double ccaThreshold, bool allowTxDuringRx, double centerFrequency, int myIndex = -1, bool collectCollisionStatistics = false, bool debug = false)
    : Decider80211p(phy, sensitivity, ccaThreshold, allowTxDuringRx, centerFrequency, myIndex, collectCollisionStatistics, debug)
    {}

    //PhyLayer80211p must access the variables for calculating the Idle time in the application (CBQoS.cc)
	double getMyBusyTime();
	double getMyStartTime();

};

#endif /* DECIDER80211pCBQOS_H_ */
