/*
 * Statistics.h
 */

#ifndef STATISTICS_STATISTICS_H_
#define STATISTICS_STATISTICS_H_

#include <omnetpp.h>

using namespace omnetpp;

class Statistics: public cSimpleModule {
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void finish();
        int numInfected;
    public:
        void recordNum(simtime_t numInfected);
};


#endif /* STATISTICS_STATISTICS_H_ */
