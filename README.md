# vanet
You'll need a working installation of Veins [1] in order to run these simulations. This in turn relies on having the traffic simulator Sumo [2] as well as the network simulator Omnet++ [3] installed (including the INET Framework).

Setting up this Omnet++ project:
1. Open the Omnet++ main directory and start the mingwenv.cmd terminal window.
2. In mingwenv, CD into the Omnet++ main directory and launch the Omnet++ IDE with the command 'omnetpp'.
3. Create a Omnet++ project using File->Import...->General->Existing Projects into Workspace->Next->Select root directory->'Name of directory'->Finish.
4. Right-click on the newly created project in the Project Explorer, click Properties->Project References, and check inet and veins before clicking OK.
5. Right-click on the project and click Build Project to generate executables.
6. In mingwenv, CD into the Veins main directory run the command 'sumo-launchd.py -vv'. This establishes a TCP connection between Sumo and Omnet++.
7. In the Omnet++ IDE, launch the simulation by right-clicking on the .ini file and clicking Run As->Omnet++ Simulation.

Links:

[1] http://veins.car2x.org/

[2] http://sumo.dlr.de/wiki/Simulation_of_Urban_MObility_-_Wiki

[3] https://omnetpp.org/
