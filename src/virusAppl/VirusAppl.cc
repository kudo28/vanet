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

/*      int seed = 1;
        srand(seed);
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        if (simTime() > 20 && simTime() < 30) {
            patcher = true;
            vvm->setWsmData("cure");
            findHost()->getDisplayString().updateWith("r=30,green");
        }
        else if (simTime() > 30 && simTime() < 40) {
            infected = true;
            vvm->setWsmData("virus");
            findHost()->getDisplayString().updateWith("r=30,red");
        }
        else {
            infected = false;
            findHost()->getDisplayString().updateWith("r=30,green");
        }*/

        if (simTime() > 10 && simTime() < 14) {
            infected = true;
            patcher = false;
            vvm->setWsmData("virus");
            findHost()->getDisplayString().updateWith("r=30,red");
        }
        else {
            infected = false;
            patcher = true;
            vvm->setWsmData("cure");
            findHost()->getDisplayString().updateWith("r=30,green");
        }

        scheduleAt(simTime() + 2 + uniform(0.01,0.2), vvm->dup());
    }
}


void VirusAppl::onWSM(WaveShortMessage* wsm) {
    if (V2VMessage* vvm = dynamic_cast<V2VMessage*>(wsm)) {
        Coord::Coordinate myPosition = traciVehicle->getPosition();
        int distance = myPosition.distance(vvm->getSenderPosition());

        if (distance < par("commRadius")) {

            switch(vvm.getPayloadType()) {
            case(VIRUS) :
                infected = true;
                findHost()->getDisplayString().updateWith("r=30,red");
                break;
            case(PATCH) :
                infected = false;
                findHost()->getDisplayString().updateWith("r=30,green");
                break;
            case(STANDARD) :
                //TODO: handle regular traffic update
                break;
            }

            int typeToSend;
            if (patcher) {
                typeToSend = PATCH;
            }
            else if (infected) {
                typeToSend = VIRUS;
            }
            else {
                typeToSend = STANDARD;
            }

            vvm->setSerial(3);
            vvm->setSenderAddress(myId);
            vvm->setSenderPosition(myPosition);
            vvm->setPayloadType(typeToSend);
            scheduleAt(simTime() + 2 + uniform(0.01,0.2), vvm->dup());
        }
    }
}


void VirusAppl::handleSelfMsg(cMessage* msg) {
//    BaseWaveApplLayer::handleSelfMsg(msg);
    V2VMessage* vvm = new V2VMessage();
    populateWSM(vvm);
    if (infected) {
        vvm->setWsmData("virus");
    }
//    else if (patcher) {
    else {
        vvm->setWsmData("cure");
    }
    if (simTime() > 25) {
        sendDown(vvm->dup());
    }
    double interval = 1.0;
    scheduleAt(simTime() + interval, vvm->dup());
    //this method is for self messages (mostly timers)
    //it is important to call the BaseWaveApplLayer function for BSM and WSM transmission

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
