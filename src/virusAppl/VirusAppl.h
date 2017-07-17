#ifndef _VIRUSAPPL_H_
#define _VIRUSAPPL_H_

#include <omnetpp.h>
//#include "ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/base/utils/Coord.h"
#include "statistics/StatisticsCollector.h"
#include "messages/V2VMessage_m.h"

using namespace omnetpp;

enum SIR_STATE {
    SUSCEPTIBLE = 0,
    INFECTED = 1,
    RECOVERED = 2
};

class VirusAppl : public BaseWaveApplLayer {
    public:
        virtual void initialize(int stage);
        virtual void finish();

    private:
        cMessage* timerMessage;
        SIR_STATE state;
        StatisticsCollector* stats;

        void infect();
        void patch();
        void regenPatch();
    protected:
        TraCIMobility* traci;
    protected:
        virtual void onWSM(WaveShortMessage* wsm);
        virtual void handleSelfMsg(cMessage* msg);
        virtual void handlePositionUpdate(cObject* obj);
};

#endif
