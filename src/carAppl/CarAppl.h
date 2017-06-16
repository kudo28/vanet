#ifndef CARAPPL_H_
#define CARAPPL_H_

#include <map>
#include "veins/base/modules/BaseApplLayer.h"
#include "veins/modules/utility/Consts80211p.h"
#include "veins/modules/messages/WaveShortMessage_m.h"
#include "veins/base/connectionManager/ChannelAccess.h"
#include "veins/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h"
#include "messages/Car2XMessage_m.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"

using Veins::TraCIMobility;
using Veins::TraCICommandInterface;
using Veins::AnnotationManager;

#ifndef DBG
#define DBG EV
#endif
//#define DBG std::cerr << "[" << simTime().raw() << "] " << getParentModule()->getFullPath() << " "

class CarAppl : public BaseApplLayer {

	public:
		~CarAppl();
		virtual void initialize(int stage);
		virtual void finish();

		virtual  void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details);

		enum CarApplMessageKinds {
			SOME_EVT
		};

	protected:

		static const simsignalwrap_t mobilityStateChangedSignal;
		static const simsignalwrap_t parkingStateChangedSignal;

		/** @brief handle messages from below */
		virtual void handleLowerMsg(cMessage* msg);
		/** @brief handle self messages */
		virtual void handleSelfMsg(cMessage* msg);
		/** @brief handle new position information */
		virtual void handlePositionUpdate(cObject* obj);

		virtual void handleParkingUpdate(cObject* obj);

	protected:
		int packetLength;
		int packetPriority;

		Coord curPosition;
		int myId;
		bool isParking;
		bool sendWhileParking;

		WaveAppToMac1609_4Interface* myMac;
		TraCIMobility* mobility;
		TraCICommandInterface* traci;
		TraCICommandInterface::Vehicle* traciVehicle;
		AnnotationManager* annotations;

		std::set<unsigned long> forwardedMessages;
};

#endif /* CARAPPL_H_ */
