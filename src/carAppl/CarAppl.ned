package grid.carAppl;
import org.car2x.veins.base.modules.IBaseApplLayer;

simple CarAppl like IBaseApplLayer
{
    parameters:
        
        bool debug = default(false); //whether to print debug output
        int headerLength = default(88bit) @unit("bit"); // length of the application message header (in bits)
        int packetLength = default(1024bit) @unit("bit"); //packet length of the application
        int packetPriority = default(3); // priority: 3=AC_VO, 2=AC_VI, 1=AC_BE, 0=AC_BK
        
        bool sendWhileParking  = default(false); //send messages when the car is parked

    gates:
        input lowerLayerIn; // from mac layer
        output lowerLayerOut; // to mac layer
        input lowerControlIn;
        output lowerControlOut;
}
