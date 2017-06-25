# vanet
You'll need a working installation of Veins [1] in order to run these simulations. This in turn relies on having the traffic simulator Sumo [2] as well as the network simulator OMNeT++ [3] installed (including the INET Framework).

To set up this OMNeT++ project:
1. Open the OMNeT++ main directory and start the mingwenv.cmd terminal window.
2. In mingwenv, CD into the OMNeT++ main directory and launch the OMNeT++ IDE with the command 'omnetpp'.
3. Create a OMNeT++ project using File->Import...->General->Existing Projects into Workspace->Next->Select root directory->'Name of directory'->Finish.
4. Right-click on the newly created project in the Project Explorer, click Properties->Project References, and check inet and veins before clicking OK.
5. Right-click on the project and click Build Project to generate executables.
6. In mingwenv, CD into the Veins main directory and enter the command 'sumo-launchd.py -vv'. This establishes a TCP connection between Sumo and OMNeT++.
7. Update the file path in the Sumo launchd files appropriately.
8. In the OMNeT++ IDE, launch the simulation by right-clicking on the .ini file and clicking Run As->OMNeT++ Simulation.

Links:

[1] http://veins.car2x.org/

[2] http://sumo.dlr.de/wiki/Simulation_of_Urban_MObility_-_Wiki

[3] https://omnetpp.org/