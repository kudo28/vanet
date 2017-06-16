// Messaging doesn't work

#include "CarAppl.h"

const simsignalwrap_t CarAppl::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);
const simsignalwrap_t CarAppl::parkingStateChangedSignal = simsignalwrap_t(TRACI_SIGNAL_PARKING_CHANGE_NAME);

using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;

Define_Module(CarAppl);

void CarAppl::initialize(int stage) {
	BaseApplLayer::initialize(stage);

	if (stage==0) {
		myMac = FindModule<WaveAppToMac1609_4Interface*>::findSubModule(
		            getParentModule());
		assert(myMac);
		mobility = TraCIMobilityAccess().get(getParentModule());
		traci = mobility->getCommandInterface();
		traciVehicle = mobility->getVehicleCommandInterface();
		annotations = AnnotationManagerAccess().getIfExists();
		ASSERT(annotations);

		myId = getParentModule()->getIndex();
		headerLength = par("headerLength");
		packetLength = par("packetLength");
		packetPriority = par("packetPriority");

		sendWhileParking = par("sendWhileParking").boolValue();

		findHost()->subscribe(mobilityStateChangedSignal, this);
		findHost()->subscribe(parkingStateChangedSignal, this);
		isParking = false;
	}

}

void CarAppl::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) {
	Enter_Method_Silent();
	if (signalID == mobilityStateChangedSignal) {
		handlePositionUpdate(obj);
	}
	else if (signalID == parkingStateChangedSignal) {
        handleParkingUpdate(obj);
    }
}

void CarAppl::handlePositionUpdate(cObject* obj) {
	ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
	curPosition = mobility->getCurrentPosition();
}

void CarAppl::handleParkingUpdate(cObject* obj) {
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

void CarAppl::handleLowerMsg(cMessage* msg) {

	if (Car2XMessage* wsm = dynamic_cast<Car2XMessage*>(msg)) {
		//std::cerr << "car: received a Car2XMessage" << std::endl;
		if(forwardedMessages.find(wsm->getUnique_id()) == forwardedMessages.end()) {
		    forwardedMessages.insert(wsm->getUnique_id());

		    // change the color of this vehicle
		    if(wsm->getMonitorMsg()) {
		        mobility->getVehicleCommandInterface()->setColor(Veins::TraCIColor::fromTkColor("yellow"));
		    }

		    double alreadyTravelledDistance = wsm->getMaxTravelledDistance();
		    double newTravelledDistance = wsm->getOriginPosition().distance(curPosition);
		    if(newTravelledDistance > alreadyTravelledDistance) {
		        wsm->setMaxTravelledDistance(newTravelledDistance);
		    }

//		    // record msgdistance statistic for the message where the monitorFlag is set
//		    if(wsm->getMonitorMsg()) {
//		        emit(sig_msgdistance, wsm->getMaxTravelledDistance());
//		    }

		    // FIXME using an artificial delay
		    simtime_t artificial_delay = uniform(0.0, 1.0);
		    wsm->setHops(wsm->getHops()+1);

		    sendDelayedDown(wsm, artificial_delay);

		} else {
		    delete(wsm);
		}
	}
	else {
		DBG << "unknown message (" << wsm->getName() << ")  received\n";
		delete(msg);
	}
}

void CarAppl::handleSelfMsg(cMessage* msg) {
	switch (msg->getKind()) {
		case SOME_EVT: {

			break;
		}
		default: {
			if (msg)
				DBG << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
			break;
		}
	}
}

void CarAppl::finish() {

	findHost()->unsubscribe(mobilityStateChangedSignal, this);
	findHost()->unsubscribe(parkingStateChangedSignal, this);

}

CarAppl::~CarAppl() {

}
