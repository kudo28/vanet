// Messaging does work

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

#include "MyAppl.h"

Define_Module(MyAppl);

void MyAppl::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);

    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
        if (myId % 5 == 0) {
            infected = true;
        }
        else {
            infected = false;
        }
    }
}

void MyAppl::onWSM(WaveShortMessage* wsm) {

    if ( strcmp(wsm->getWsmData(), "virus") == 0 ) {
        infected = true;
    }

    if (!sentMessage) {
        sentMessage = true;
        //repeat the received traffic update once in 2 seconds plus some random delay
        wsm->setSenderAddress(myId);
        wsm->setSerial(3);
        if (infected) {
            wsm->setWsmData("virus");
        }
        else {
            wsm->setWsmData("");
        }
        scheduleAt(simTime() + 2 + uniform(0.01,0.2), wsm->dup());
    }
}

void MyAppl::handleSelfMsg(cMessage* msg) {
    if (WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg)) {
        //send this message on the service channel until the counter is 3 or higher.
        //this code only runs when channel switching is enabled

        if ( strcmp(wsm->getWsmData(), "virus") == 0 ) {
            infected = true;
        }
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() +1);
        if (wsm->getSerial() >= 3) {
            //stop service advertisements
            stopService();
            delete(wsm);
        }
        else {
            scheduleAt(simTime()+1, wsm);
        }
    }
    else {
        BaseWaveApplLayer::handleSelfMsg(msg);
    }
}

void MyAppl::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);
    if (infected) {
        findHost()->getDisplayString().updateWith("r=30,red");
    }
    else {
        findHost()->getDisplayString().updateWith("r=30,green");
    }

    if (simTime() - lastDroveAt >= 2 && sentMessage == false) {
        sentMessage = true;
        WaveShortMessage* wsm = new WaveShortMessage();
        populateWSM(wsm);
        wsm->setWsmData("virus");
        if (dataOnSch) {
            startService(Channels::SCH2, 42, "Traffic Information Service");
            //started service and server advertising, schedule message to self to send later
            scheduleAt(computeAsynchronousSendingTime(1,type_SCH),wsm);
        }
        else {
            //send right away on CCH, because channel switching is disabled
            sendDown(wsm);
        }
    }
}

