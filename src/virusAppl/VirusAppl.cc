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
        sentMessage = false;
        V2VMessage* vvm = new V2VMessage();
        populateWSM(vvm);
        vvm->setSenderAddress(myId);
        vvm->setSerial(3);

        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        bool shouldInfect = simTime() > (double) par("infectStart") &&
                            simTime() < (double) par("infectStop")  &&
                            r         < (double) par("infectRate");

        bool shouldPatch = simTime() > (double) par("patchStart") &&
                           simTime() < (double) par("patchStop")  &&
                           r         < (double) par("patchRate")  &&
                           par("patchingOn");

        if (shouldInfect) {
            infected = true;
            patcher = false;
            findHost()->getDisplayString().updateWith("r=30,red");
            vvm->setPayloadType(VIRUS);
        }
        else if (shouldPatch) {
            infected = false;
            patcher = true;
            findHost()->getDisplayString().updateWith("r=30,green");
            if (par("regenPatchingOn")) {
                vvm->setPayloadType(REGEN_PATCH);
            }
            else {
                vvm->setPayloadType(PATCH);
            }
        }
        else {
            infected = false;
            patcher = false;
            vvm->setPayloadType(TRAFFIC_UPDATE);
            findHost()->getDisplayString().updateWith("r=30,green");
        }

        // Send self-message to trigger the messaging process
        scheduleAt(simTime() + 2 + uniform(0.01,0.2), vvm->dup());
    }
}


void VirusAppl::onWSM(WaveShortMessage* wsm) {
    if (V2VMessage* vvm = dynamic_cast<V2VMessage*>(wsm)) {
        Coord::Coord myPosition = mobility->getCurrentPosition();
        double distance = myPosition.distance(vvm->getSenderPosition());
        PayloadType typeToSend;

        if (distance < (double)par("commRadius")) {

            switch(vvm->getPayloadType()) {
            case(VIRUS) :
                if (!patcher) {
                    infected = true;
                    findHost()->getDisplayString().updateWith("r=30,red");
                }
                break;
            case(PATCH) :
                infected = false;
                findHost()->getDisplayString().updateWith("r=30,green");
                break;
            case(REGEN_PATCH) :
                infected = false;
                patcher = true;
                findHost()->getDisplayString().updateWith("r=30,green");
                break;
            case(TRAFFIC_UPDATE) :
                //TODO: handle regular traffic update
                break;
            }

            if (patcher) {
                if (par("regenPatchingOn")) {
                    typeToSend = REGEN_PATCH;
                }
                else {
                    typeToSend = PATCH;
                }
            }
            else if (infected) {
                typeToSend = VIRUS;
            }
            else {
                typeToSend = TRAFFIC_UPDATE;
            }

            if (!sentMessage) {
                sentMessage = true;
                vvm->setSerial(3);
                vvm->setSenderAddress(myId);
                vvm->setSenderPosition(myPosition);
                vvm->setPayloadType(typeToSend);
                scheduleAt(simTime() + 2 + uniform(0.01,0.2), vvm->dup());
            }
        }
    }
}


void VirusAppl::handleSelfMsg(cMessage* msg) {
    BaseWaveApplLayer::handleSelfMsg(msg);
    if (V2VMessage* vvm = dynamic_cast<V2VMessage*>(msg)) {
        populateWSM(vvm);
        if (simTime() > (double) par("commStart")) {
            sendDown(vvm->dup());
        }
        scheduleAt(simTime() + (double) par("commInterval"), vvm->dup());
    }
}

void VirusAppl::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class

}

void VirusAppl::finish() {
    BaseWaveApplLayer::finish();
    //statistics recording goes here

}
