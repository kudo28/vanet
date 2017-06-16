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
        WaveShortMessage* wsm = new WaveShortMessage();
        populateWSM(wsm);
        wsm->setSenderAddress(myId);
        wsm->setSerial(3);

/*      int seed = 1;
        srand(seed);
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        if (simTime() > 20 && simTime() < 30) {
            patcher = true;
            wsm->setWsmData("cure");
            findHost()->getDisplayString().updateWith("r=30,green");
        }
        else if (simTime() > 30 && simTime() < 40) {
            infected = true;
            wsm->setWsmData("virus");
            findHost()->getDisplayString().updateWith("r=30,red");
        }
        else {
            infected = false;
            findHost()->getDisplayString().updateWith("r=30,green");
        }*/

        if (simTime() > 10 && simTime() < 14) {
            infected = true;
            patcher = false;
            wsm->setWsmData("virus");
            findHost()->getDisplayString().updateWith("r=30,red");
        }
        else {
            infected = false;
            patcher = true;
            wsm->setWsmData("cure");
            findHost()->getDisplayString().updateWith("r=30,green");
        }

        scheduleAt(simTime() + 2 + uniform(0.01,0.2), wsm->dup());
    }
}

void VirusAppl::finish() {
    BaseWaveApplLayer::finish();
    //statistics recording goes here

}

void VirusAppl::onBSM(BasicSafetyMessage* bsm) {
    //Your application has received a beacon message from another car or RSU
    //code for handling the message goes here

}

void VirusAppl::onWSM(WaveShortMessage* wsm) {
    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
    if ( strcmp(wsm->getWsmData(), "virus") == 0 ) {
        infected = true;
        findHost()->getDisplayString().updateWith("r=30,red");
    }
//    if ( strcmp(wsm->getWsmData(), "cure") == 0 ) {
//        infected = false;
//        findHost()->getDisplayString().updateWith("r=30,green");
//    }
}

void VirusAppl::onWSA(WaveServiceAdvertisement* wsa) {
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void VirusAppl::handleSelfMsg(cMessage* msg) {
//    BaseWaveApplLayer::handleSelfMsg(msg);
    WaveShortMessage* wsm = new WaveShortMessage();
    populateWSM(wsm);
    if (infected) {
        wsm->setWsmData("virus");
    }
//    else if (patcher) {
    else {
        wsm->setWsmData("cure");
    }
    if (simTime() > 25) {
        sendDown(wsm->dup());
    }
    double interval = 1.0;
    scheduleAt(simTime() + interval, wsm->dup());
    //this method is for self messages (mostly timers)
    //it is important to call the BaseWaveApplLayer function for BSM and WSM transmission

}

void VirusAppl::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class

}
