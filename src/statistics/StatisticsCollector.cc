// StatisticsCollector.cc
#include "StatisticsCollector.h"

Define_Module(StatisticsCollector);

void StatisticsCollector::initialize() {
    numInfected = 0;
    numVehicles = 0;
    numOkay = 0;
    numError = 0;
    fracInfected = 0;
    errorRate = 0;
    fracInfectedSignal = registerSignal("fracInfectedSignal");
    sigErrorRate = registerSignal("sigErrorRate");
    sigNumOkay = registerSignal("sigNumOkay");
    sigNumError = registerSignal("sigNumError");
    emit(fracInfectedSignal, fracInfected);
    emit(sigErrorRate, errorRate);
    emit(sigNumOkay, numOkay);
    emit(sigNumError, numError);
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

void StatisticsCollector::incrNumOkay() {
    Enter_Method_Silent();
    numOkay++;
    updateErrorRate();
}

void StatisticsCollector::incrNumError() {
    Enter_Method_Silent();
    numError++;
    updateErrorRate();
}

void StatisticsCollector::updateErrorRate() {
    errorRate = (double) numOkay / (double) (numError+numOkay);
    emit(sigErrorRate, errorRate);
    emit(sigNumOkay, numOkay);
    emit(sigNumError, numError);
}

void StatisticsCollector::finish() {
}
