/*
 * StatisticsCollector.h
 *
 *  Created on: Jun 25, 2017
 *      Author: Jacob
 */

#ifndef STATISTICS_STATISTICSCOLLECTOR_H_
#define STATISTICS_STATISTICSCOLLECTOR_H_

#include <omnetpp.h>

using namespace omnetpp;

class StatisticsCollector: public cSimpleModule {
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void finish();
    private:
        int numInfected;
        int numVehicles;
        int numError;
        int numOkay;
        double fracInfected;
        double pdr;
        simsignal_t sigPdr;
        simsignal_t sigNumOkay;
        simsignal_t sigNumError;
        simsignal_t fracInfectedSignal;
        void updateFracInfected();
        void updateErrorRate();
    public:
        void incrNumInfected();
        void decrNumInfected();
        void incrNumVehicles();
        void decrNumVehicles();
        void incrNumOkay();
        void incrNumError();
        int getNumInfected();
        double getFracInfected();
};

#endif /* STATISTICS_STATISTICSCOLLECTOR_H_ */
