cplusplus {{
	#include "veins/modules/messages/WaveShortMessage_m.h"
}}
class WaveShortMessage;
class noncobject Coord;

enum PayloadType
{
   TRAFFIC_UPDATE = 0;
   VIRUS = 1;
   PATCH = 2;
   REGEN_PATCH = 3;
};

packet V2VMessage extends WaveShortMessage {
    simtime_t creationTime;
    Coord senderPosition;
    int hops;
    int payloadType @enum(PayloadType);
}