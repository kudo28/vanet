// StatisticsCollector.cc
#include "StatisticsCollector.h"

Define_Module(StatisticsCollector);

void StatisticsCollector::initialize() {
    numInfected = 0;
    numVehicles = 0;
    fracInfected = 0;
    fracInfectedSignal = registerSignal("fracInfectedSignal");
    emit(fracInfectedSignal, fracInfected);
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

void StatisticsCollector::finish() {
}
