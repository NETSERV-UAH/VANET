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

#include "src/veins/modules/phy/PhyLayer80211pCBQoS.h"
#include "src/veins/modules/phy/Decider80211pCBQoS.h"

Define_Module(PhyLayer80211pCBQoS);

Decider* PhyLayer80211pCBQoS::initializeDecider80211p(ParameterMap& params) {
    double centerFreq = params["centerFrequency"];
    Decider80211pCBQoS* dec = new Decider80211pCBQoS(this, sensitivity, ccaThreshold, allowTxDuringRx, centerFreq, findHost()->getIndex(), collectCollisionStatistics, coreDebug);
    dec->setPath(getParentModule()->getFullPath());
    return dec;
}

double PhyLayer80211pCBQoS::getMyBusyTime(){
    Decider80211pCBQoS* dec = dynamic_cast<Decider80211pCBQoS*>(decider);
    return dec->getMyBusyTime();
}

double PhyLayer80211pCBQoS::getMyStartTime(){
    Decider80211pCBQoS* dec = dynamic_cast<Decider80211pCBQoS*>(decider);
    return dec->getMyStartTime();
}

