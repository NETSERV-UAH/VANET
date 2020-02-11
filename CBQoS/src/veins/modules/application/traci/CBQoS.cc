//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
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
#include "src/veins/modules/application/traci/CBQoS.h"
#include "src/veins/modules/phy/PhyLayer80211pCBQoS.h"

//EXTRA END

using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;

const simsignalwrap_t CBQoS::parkingStateChangedSignal = simsignalwrap_t(TRACI_SIGNAL_PARKING_CHANGE_NAME);

Define_Module(CBQoS);

CBQoS::CBQoS(){
    mobility = nullptr;
    traci = nullptr;
    traciVehicle = nullptr;
    annotations = nullptr;
    neighborTable = nullptr;
}

void CBQoS::initialize(int stage) {
	BaseWaveApplLayer::initialize(stage);
	if (stage == 0) {
		mobility = TraCIMobilityAccess().get(getParentModule());
		traci = mobility->getCommandInterface();
		traciVehicle = mobility->getVehicleCommandInterface();
		annotations = AnnotationManagerAccess().getIfExists();
		ASSERT(annotations);

		sentMessage = false;
		lastDroveAt = simTime();
		findHost()->subscribe(parkingStateChangedSignal, this);
		isParking = false;
		sendWhileParking = par("sendWhileParking").boolValue();

		//EXTRA BEGIN
		neighborTable = check_and_cast<NeighborTable*>(this->getParentModule()->getSubmodule("neighborTable"));

		helloInterval = par("helloInterval");
		sendHelloTimer = new cMessage("HELLO_MESSAGE", SEND_HELLO_TIMER);
        scheduleAt(simTime() + helloInterval, sendHelloTimer);

		//EXTRA END
	}
}

//EXTRA BEGIN
void CBQoS::handleSelfMsg(cMessage* msg){
    if (msg->getKind() == SEND_HELLO_TIMER){
        sendHelloMessage();
        scheduleAt(simTime() + helloInterval, sendHelloTimer);

    }
}

void CBQoS::sendHelloMessage(){
    cModule * phyModule = this->getParentModule()->getSubmodule("nic")->getSubmodule("phy80211p");
    PhyLayer80211pCBQoS * myPhy = check_and_cast<PhyLayer80211pCBQoS *>(phyModule);
    double calculatedIdleTime = ((simTime().dbl() - myPhy->getMyStartTime()) - myPhy->getMyBusyTime()) / (simTime().dbl() - myPhy->getMyStartTime());
    EV << "Calculated IdleTime is " << calculatedIdleTime << endl;

    HelloMessage* helloMessage = new HelloMessage("Hello Message");
    helloMessage->setVehicleId(myApplAddr());
    helloMessage->setMessageId(1);
    helloMessage->setIdleTime(calculatedIdleTime);
    helloMessage->setDegree(mobility->getAngleRad()); //helloMessage->setDegree(neighborTable->getNumberOfNeighbors());
    helloMessage->setRole(1);
    helloMessage->setAverageSpeed(mobility->getSpeed());
    helloMessage->setGpsPosition(curPosition);
    helloMessage->setCreationTime(simTime());
    helloMessage->setQosValue(1);
    helloMessage->setClusterHeadId(1);

    WaveShortMessage* wsm =  new WaveShortMessage("data");
    wsm->addBitLength(headerLength);
    //wsm->addBitLength(lengthBits);
    wsm->setPsid(0);
    //wsm->setPriority(priority);
    wsm->setWsmVersion(1);
    wsm->setTimestamp(simTime());
    wsm->setSenderAddress(myId);
    wsm->setRecipientAddress(-1);
    wsm->setSenderPos(curPosition);
    //wsm->setSerial(serial);

    t_channel channel = dataOnSch ? type_SCH : type_CCH;
    switch (channel) {
        case type_SCH: wsm->setChannelNumber(Channels::SCH1); break; //will be rewritten at Mac1609_4 to actual Service Channel. This is just so no controlInfo is needed
        case type_CCH: wsm->setChannelNumber(Channels::CCH); break;
    }

    wsm->encapsulate(helloMessage);
    DBG << "Creating a Hello Message at " << wsm->getTimestamp() << " to be sent." << std::endl;
    sendWSM(wsm);
}
//EXTRA END

void CBQoS::sendMessage(std::string blockedRoadId) {
	sentMessage = true;

	t_channel channel = dataOnSch ? type_SCH : type_CCH;
	WaveShortMessage* wsm = prepareWSM("data", dataLengthBits, channel, dataPriority, -1,2);
	wsm->setWsmData(blockedRoadId.c_str());
	sendWSM(wsm);
}
void CBQoS::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) {
	Enter_Method_Silent();
	if (signalID == mobilityStateChangedSignal) {
		handlePositionUpdate(obj);
	}
	else if (signalID == parkingStateChangedSignal) {
		handleParkingUpdate(obj);
	}
}

void CBQoS::onBeacon(WaveShortMessage* wsm) {
}

void CBQoS::onData(WaveShortMessage* wsm) {
/*  findHost()->getDisplayString().updateWith("r=16,green");
    annotations->scheduleErase(1, annotations->drawLine(wsm->getSenderPos(), mobility->getPositionAt(simTime()), "blue"));

    if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(wsm->getWsmData(), 9999);
    if (!sentMessage) sendMessage(wsm->getWsmData());
*/
    cPacket* decapsulatedPacket = wsm->decapsulate();
    if (dynamic_cast<HelloMessage *>(decapsulatedPacket)){
        HelloMessage* helloMessage = dynamic_cast<HelloMessage *>(decapsulatedPacket);
        EV << "A new Hello received from vehicle ID " << helloMessage->getVehicleId() << " / sender address " << wsm->getSenderAddress() << endl;
        handleIncomingHello(helloMessage);
    }
    delete decapsulatedPacket;
    //delete wsm;

}

//EXTRA BEGIN
void CBQoS::handleIncomingHello(HelloMessage* helloMessage){
    int vehicleId = helloMessage->getVehicleId();
    int messageId = helloMessage->getMessageId();
    simtime_t idleTime = helloMessage->getIdleTime();
    double degree = helloMessage->getDegree();
    double role = helloMessage->getRole();
    double averageSpeed = helloMessage->getAverageSpeed();
    Coord gpsPosition = helloMessage->getGpsPosition();
    simtime_t creationTime = helloMessage->getCreationTime();
    double qosValue = helloMessage->getQosValue();
    int clusterHeadId = helloMessage->getClusterHeadId();
    double direction = 1;

    //Calculating the Link Expiration Time (LET) parameter according to Equation 9
    double v1 = mobility->getSpeed();
    double v2 = averageSpeed;
    double tetta1 = mobility->getAngleRad();
    double tetta2 = degree;
    double x1 = curPosition.x; //x1 = mobility->getCurrentPosition().x;
    double y1 = curPosition.y; //y1 = mobility->getCurrentPosition().y;
    double x2 = gpsPosition.x;
    double y2 = gpsPosition.y;
    double a,b,c,d;
    a = v1 * cos(tetta1) - v2 * cos(tetta2);
    b = x1 - x2;
    c = v1 * sin(tetta1) - v2 * sin(tetta2);
    d = y1 - y2;
    double l = sqrt(pow(d,2) * (pow(a,2) + pow(c,2)) - pow(a*d - b*c,2) - (a*b + c*d)) / (pow(a,2) + pow(c,2));
    EV << "L = " << l << ", tetta1 = " << tetta1 << ", cos(tetta1) = " << cos(tetta1) << ", tetta2 = " << tetta2 << ", cos(tetta2) = " << cos(tetta2) << ", a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << endl;

    double bw = 1;
    double d_ = 1;
    double j = 1;
    double speedDifference = 1;
    neighborTable->updateTable(vehicleId, messageId, idleTime, degree, role, averageSpeed, gpsPosition, creationTime, qosValue, clusterHeadId, direction, l, bw, d_, j, speedDifference);
}
//EXTRA END
void CBQoS::handleParkingUpdate(cObject* obj) {
	isParking = mobility->getParkingState();
	if (sendWhileParking == false) {
		if (isParking == true) {
			(FindModule<BaseConnectionManager*>::findGlobalModule())->unregisterNic(this->getParentModule()->getSubmodule("nic"));
		}
		else {
			Coord pos = mobility->getCurrentPosition();
			(FindModule<BaseConnectionManager*>::findGlobalModule())->registerNic(this->getParentModule()->getSubmodule("nic"), (ChannelAccess*) this->getParentModule()->getSubmodule("nic")->getSubmodule("phy80211p"), &pos);
		}
	}
}
void CBQoS::handlePositionUpdate(cObject* obj) {
	BaseWaveApplLayer::handlePositionUpdate(obj);

	// stopped for for at least 10s?
	if (mobility->getSpeed() < 1) {
		if (simTime() - lastDroveAt >= 10) {
			findHost()->getDisplayString().updateWith("r=16,red");
			if (!sentMessage) sendMessage(mobility->getRoadId());
		}
	}
	else {
		lastDroveAt = simTime();
	}
}

void CBQoS::sendWSM(WaveShortMessage* wsm) {
	if (isParking && !sendWhileParking) return;
	sendDelayedDown(wsm,individualOffset);
}

void CBQoS::finish(){
    BaseApplLayer::finish();

    if (sendHelloTimer->isScheduled()) {
        cancelAndDelete(sendHelloTimer);
    }
    else {
        delete sendHelloTimer;
    }
}

CBQoS::~CBQoS(){

}
