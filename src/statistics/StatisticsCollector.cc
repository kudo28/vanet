// StatisticsCollector.cc
#include "StatisticsCollector.h"

Define_Module(StatisticsCollector);

void StatisticsCollector::initialize() {
    numInfected = 0;
    numVehicles = 0;
    numInfectedSignal = registerSignal("numInfectedSignal");
    numVehiclesSignal = registerSignal("numVehiclesSignal");
}

void StatisticsCollector::handleMessage(cMessage *msg) {}

void StatisticsCollector::incrNumInfected() {
    Enter_Method_Silent();
    numInfected++;
    emit(numInfectedSignal, numInfected);
}

void StatisticsCollector::decrNumInfected() {
    Enter_Method_Silent();
    numInfected--;
    emit(numInfectedSignal, numInfected);
}

void StatisticsCollector::incrNumVehicles() {
    Enter_Method_Silent();
    numVehicles++;
    emit(numVehiclesSignal, numVehicles);
}

void StatisticsCollector::decrNumVehicles() {
    Enter_Method_Silent();
    numVehicles--;
    emit(numVehiclesSignal, numVehicles);
}

void StatisticsCollector::finish() {

}
