//
// Modified by Jacob Hultman, June 2017
//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
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

#include "VirusAppl.h"
#include "V2VMessage_m.h"
#include <cstdlib>

Define_Module(VirusAppl);

void VirusAppl::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        // Initializing pointers
        cModule *grandParent = this->getParentModule()->getParentModule();
        cModule *mod = grandParent->getSubmodule("statisticsCollector");
        stats = check_and_cast<StatisticsCollector *>(mod);
        traci = TraCIMobilityAccess().get(getParentModule());

        // Initializing message
        sentMessage = false;

        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        bool shouldInfect = simTime() > (double) par("infectStart") &&
                            simTime() < (double) par("infectStop")  &&
                            r         < (double) par("infectRate");

        bool shouldPatch = simTime() > (double) par("patchStart") &&
                           simTime() < (double) par("patchStop")  &&
                           r         < (double) par("patchRate")  &&
                           (par("patchingOn") || par("regenPatchingOn"));

        if (shouldInfect) {
            infect();
        }
        else if (shouldPatch) {
            patch();
        }
        else {
            state = SUSCEPTIBLE;
            findHost()->getDisplayString().updateWith("r=30,green");
        }

        // Send self-message to trigger the messaging process
        scheduleAt(simTime() + uniform(0.01,0.2), new cMessage);
        stats->incrNumVehicles();
    }
}


void VirusAppl::onWSM(WaveShortMessage* wsm) {
    if (V2VMessage* vvm = dynamic_cast<V2VMessage*>(wsm)) {
        double distance = curPosition.distance(vvm->getSenderPosition());
        if (distance < (double) par("commRadius")) {
            switch(vvm->getPayloadType()) {
            case(VIRUS) :
                printf("Virus\n");
                if (state == SUSCEPTIBLE) {
                    infect();
                }
                break;
            case(PATCH) :
                patch();
                break;
            case(REGEN_PATCH) :
                regenPatch();
                break;
            case(TRAFFIC_UPDATE) :
                //TODO: handle regular traffic update
                printf("Traffic update\n");
                break;
            }

            if (!sentMessage) {
                sentMessage = true;
                vvm->setSerial(3);
                vvm->setSenderAddress(myId);
                scheduleAt(simTime() + (double) par("commInterval") + uniform(0.01,0.2), vvm->dup());
            }
            drop(vvm);
            delete(vvm);
        }
    }
}


void VirusAppl::infect() {
    if (state != INFECTED) {
        stats->incrNumInfected();
    }
    state = INFECTED;
    findHost()->getDisplayString().updateWith("r=30,red");
}


void VirusAppl::patch() {
    if (state != RECOVERED) {
        stats->decrNumInfected();
    }
    state = RECOVERED;
    findHost()->getDisplayString().updateWith("r=30,green");
}


void VirusAppl::regenPatch() {
    state = RECOVERED;
    stats->decrNumInfected();
    findHost()->getDisplayString().updateWith("r=30,green");
    // TODO: Add regenerative patching functionality
}


void VirusAppl::handleSelfMsg(cMessage* msg) {
//    BaseWaveApplLayer::handleSelfMsg(msg);
    V2VMessage* vvm = new V2VMessage();
    populateWSM(vvm);
    vvm->setSenderPosition(curPosition);
    if (state == INFECTED) {
        vvm->setPayloadType(VIRUS);
    }
    else {
        vvm->setPayloadType(TRAFFIC_UPDATE);
    }
    if (simTime() > (double) par("commStart")) {
        sendDown(vvm->dup());
    }
    scheduleAt(simTime() + (double) par("commInterval"), new cMessage);
    drop(vvm);
    delete(vvm);
}


void VirusAppl::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class
}


void VirusAppl::finish() {
    BaseWaveApplLayer::finish();
    if(state == INFECTED) {
        stats->decrNumInfected();
    }
    stats->decrNumVehicles();
}
