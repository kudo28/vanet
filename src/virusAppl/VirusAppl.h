#ifndef _VIRUSAPPL_H_
#define _VIRUSAPPL_H_

#include <omnetpp.h>
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/base/utils/Coord.h"
#include "statistics/StatisticsCollector.h"

using namespace omnetpp;

class VirusAppl : public BaseWaveApplLayer {
    public:
        virtual void initialize(int stage);
        virtual void finish();
    private:
        bool infected;
        bool patcher;
        bool sentMessage;
        simsignal_t numInfectedSignal;
        simsignal_t fracInfectedSignal;
        static long numInfected;
        static double fracInfected;
        StatisticsCollector *stats;
    protected:
        TraCIMobility* traci;
    protected:
        virtual void onWSM(WaveShortMessage* wsm);
        virtual void handleSelfMsg(cMessage* msg);
        virtual void handlePositionUpdate(cObject* obj);
};

long VirusAppl::numInfected = 0;
double VirusAppl::fracInfected = 0;

#endif

