// StatisticsCollector.cc
#include "StatisticsCollector.h"

Define_Module(StatisticsCollector);

void StatisticsCollector::initialize() {
    numInfected = 0;
    numVehicles = 0;
    numSent = 0;
    numReceived = 0;
    fracInfected = 0;
    pdr = 0;
    fracInfectedSignal = registerSignal("fracInfectedSignal");
    sigPdr = registerSignal("sigPdr");
    emit(fracInfectedSignal, fracInfected);
    emit(sigPdr, pdr);
}

void StatisticsCollector::handleMessage(cMessage *msg) {}

void StatisticsCollector::incrNumInfected() {
    Enter_Method_Silent();
    numInfected++;
    updateFracInfected();
}

void StatisticsCollector::decrNumInfected() {
    Enter_Method_Silent();
    numInfected--;
    updateFracInfected();
}

void StatisticsCollector::incrNumVehicles() {
    Enter_Method_Silent();
    numVehicles++;
    updateFracInfected();
}

void StatisticsCollector::decrNumVehicles() {
    Enter_Method_Silent();
    numVehicles--;
    updateFracInfected();
}

void StatisticsCollector::updateFracInfected() {
    fracInfected = (double) numInfected / (double) numVehicles;
    emit(fracInfectedSignal, fracInfected);
}

int StatisticsCollector::getNumInfected() {
    return numInfected;
}

double StatisticsCollector::getFracInfected() {
    return fracInfected;
}

void StatisticsCollector::incrNumSent() {
    Enter_Method_Silent();
    numSent++;
    updatePdr();
}

void StatisticsCollector::incrNumReceived() {
    Enter_Method_Silent();
    numReceived++;
    updatePdr();
}

void StatisticsCollector::updatePdr() {
    pdr = (double) numReceived / (double) numSent;
    emit(sigPdr, pdr);
}

void StatisticsCollector::finish() {
}
