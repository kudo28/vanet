cplusplus {{
	#include "veins/modules/messages/WaveShortMessage_m.h"
}}
class WaveShortMessage;
class noncobject Coord;

packet Car2XMessage extends WaveShortMessage {
    
    simtime_t creationTime;
    Coord originPosition;
    int hops;
    unsigned long unique_id;
    bool monitorMsg = false;
    double maxTravelledDistance = 0;
    bool virus = false;
}