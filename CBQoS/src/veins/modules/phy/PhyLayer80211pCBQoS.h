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

#ifndef PHYLAYER80211PCBQOS_H_
#define PHYLAYER80211PCBQOS_H_

#include "veins/modules/phy/PhyLayer80211p.h"

class PhyLayer80211pCBQoS : public PhyLayer80211p

{
protected:
    /**
     * @brief Initializes a new Decider80211 from the passed parameter map.
     */
    virtual Decider* initializeDecider80211p(ParameterMap& params) override;

public:
    //the application (CBQoS.cc) must access decider variables for calculating the Idle time
    double getMyBusyTime();
    double getMyStartTime();
};

#endif /* PHYLAYER80211PCBQOS_H_ */
