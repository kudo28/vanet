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
    MyBaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        // Initializing state variables
        cModule *grandParent = this->getParentModule()->getParentModule();
        cModule *mod = grandParent->getSubmodule("statisticsCollector");
        stats = check_and_cast<StatisticsCollector *>(mod);

        traci = TraCIMobilityAccess().get(getParentModule());
        timerMessage = new cMessage;

        float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        bool shouldInfect = simTime() > (double) par("infectStart") &&
                            simTime() < (double) par("infectStop")  &&
                            r1        < (double) par("infectRate");

        bool shouldPatch = simTime() > (double) par("patchStart") &&
                           simTime() < (double) par("patchStop")  &&
                           r2        < (double) par("patchRate")  &&
                           (par("patchingOn") || par("regenPatchingOn"));

        if (shouldInfect) {
            this->infect();
        }
        else if (shouldPatch) {
            this->patch();
        }
        else {
            state = SUSCEPTIBLE;
            findHost()->getDisplayString().updateWith("r=30,green");
        }

        // Send self-message to trigger the messaging process
        scheduleAt(simTime() + uniform(0.01,2), timerMessage);
        stats->incrNumVehicles();
    }
}


void VirusAppl::onWSM(WaveShortMessage* wsm) {
    if (V2VMessage* vvm = dynamic_cast<V2VMessage*>(wsm)) {
        double distance = curPosition.distance(vvm->getSenderPosition());
//        printf("D: %f\n", distance);
        if (distance < (double) par("commRadius")) {
            switch(vvm->getPayloadType()) {
            case(VIRUS) :
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
                break;
            }
            drop(vvm);
        }
    }
}


void VirusAppl::infect() {
    stats->incrNumInfected();
    state = INFECTED;
    findHost()->getDisplayString().updateWith("r=30,red");
}


void VirusAppl::patch() {
    if (state == INFECTED) {
        stats->decrNumInfected();
    }
    state = RECOVERED;
    findHost()->getDisplayString().updateWith("r=30,green");
}


void VirusAppl::regenPatch() {
    if (state == INFECTED) {
        stats->decrNumInfected();
    }
    state = RECOVERED;
    findHost()->getDisplayString().updateWith("r=30,green");
    // TODO: Add regenerative patching functionality
}


void VirusAppl::handleSelfMsg(cMessage* msg) {
    if (simTime() > (double) par("commStart")) {
        V2VMessage* vvm = new V2VMessage();
        populateWSM(vvm);
        vvm->setSenderPosition(curPosition);
        if (state == INFECTED) {
            vvm->setPayloadType(VIRUS);
        }
        else if (state == RECOVERED) {
            vvm->setPayloadType(PATCH);
        }
        else {
            vvm->setPayloadType(TRAFFIC_UPDATE);
        }
        sendDown(vvm->dup());
        drop(vvm);
        delete(vvm);
    }
    if (timerMessage != NULL && timerMessage->isScheduled()) {
        cancelEvent(timerMessage);
    }
    scheduleAt(simTime() + (double) par("commInterval"), timerMessage);
}


void VirusAppl::handlePositionUpdate(cObject* obj) {
    MyBaseWaveApplLayer::handlePositionUpdate(obj);
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class
}


void VirusAppl::finish() {
    MyBaseWaveApplLayer::finish();
    cancelAndDelete(timerMessage);
    if(state == INFECTED) {
        stats->decrNumInfected();
    }
    stats->decrNumVehicles();
}
