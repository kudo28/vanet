#ifndef _VIRUSAPPL_H_
#define _VIRUSAPPL_H_

#include <omnetpp.h>
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/base/utils/Coord.h"
#include "statistics/StatisticsCollector.h"
#include "messages/V2VMessage_m.h"

using namespace omnetpp;

class VirusAppl : public BaseWaveApplLayer {
    public:
        virtual void initialize(int stage);
        virtual void finish();

    private:
        bool infected;
        bool patcher;
        bool sentMessage;
        StatisticsCollector *stats;

        void infect(V2VMessage* vvm);
        void patch(V2VMessage* vvm);
        void regenPatch(V2VMessage* vvm);
    protected:
        TraCIMobility* traci;
    protected:
        virtual void onWSM(WaveShortMessage* wsm);
        virtual void handleSelfMsg(cMessage* msg);
        virtual void handlePositionUpdate(cObject* obj);
};

#endif

