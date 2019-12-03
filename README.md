# Traffic-Road-Simulator

This is a program for a simulation of a typical reckless Indian road. These simulations can be used for various kind of road-safety studies. Here, the vehicles on the road, their sizes, speeds, the width of the road etc. are user defined. This simulation exhibits various behaviours like Vehicles changing lanes to overtake, bikes moving in a zig zag way to overtake, rickshaws getting stuck due to their reckless behaviour of trying to just go ahead without considering the space available and thus causing a traffic jam behind them, some vehicles skipping the red signals etc. These are some of the most commonly observed traffic patterns in India and so this model would be useful for studying the behaviour of an **Indian** road. The important details for this are as follows:

1. The configuration file is **otherConfig.txt**
2. The contents of the configuration file are read and processed by the code: **Parser.cpp**
3. The information about the configuration file is given as:
    * The variable Road_Id is just defined to index a road for the simulation number.
    * The variable Road_Length and Road_Width are just the dimensions, Road_Signal_Position is the position of the traffic signal and Road_Zebra_Width is the width of the corresponding traffic signal. 
    * The variable Road_Yellow was initially thought to describe a yellow signal for the traffic signals, but it wasn’t implemented as well because of the ordinary traffic signals being only in Red and Green in most of the Indian citites.
    * Road_Signal is the total duration of a single traffic light
    * Default_LaneChange and Default_Acceleration are the default values chosen for the Vehicles
    * End_Time is the maximum time till which this simulation should run. The “Pass” times can not exceed this limit.
    * Total_vehicles_on_road is the variable indicating the maximum number of vehicles that can be called in the simulation
    * Total_Vehicles is the total type of Vehicles introduced in the simulation
    * The various ‘Vehicle_Type’s are defined subsequently and given the corresponding maximum values as appropriate.
    * The variable START indicates that all the Vehicles have been defined and so, it’s time to start the simulation now.
    * Signal RED or Signal GREEN defines the initial traffic signal
    * Start_Time is the initial time for the corresponding traffic signal. And this simulation is allowed to go only till the “End_Time”.
    * ‘Pass n’ defines that the vehicles initiated above that word are to be run into the simulation for ‘n’ seconds.
    * END means that the simulation should stop now, and the code waits for the signal to be RED again, so that the entire system comes to a stop finally!	
    * The traffic signals are changed by the code itself and they don’t need to be mentioned repeatedly!
    * The comments in this file should start and end by a ‘#’ symbol
    * All the Vehicle types have to be defined before the START signal
    * All the Vehicles defined between the ‘Start_time’and a ‘Pass’ or between two ‘Pass’ are initiated simultaneously and will run into the simulation after the corresponding Pass signal. These vehicles are initiated behind the starting line of the road. (This line indicates that these vehicles are coming in the viewed section of the road). While the Vehicles defined before the ‘SIGNAL X’ are the ones which are already initiated just at the zebra crossing. This feature is for representational purposes. (The rickshaw getting into an angle or the bike moving zig-zag to get the farthest it can get)
    * There is also a constraint for the Road_Length for Representational purposes.
    * Also, Road_Signal_Position can not be greater than Road_Length
    * The parameters defined for each Vehicle type are:
        * Vehicle_Length
        * Vehicle_Width
        * Vehicle_MaxSpeed
        * Vehicle_Acceleration
        * Vehicle_Break
        * Vehicle_LaneChange
     * Some constraints defined in our implementation are
        * To maintain some fairness in the structure of the road, we have decided to implement the Road such that it’s width is only a multiple of 4
        * The Dimensions of Motor Rickshaw are to be fixed as “2 * 2”
        * The Dimensions of Bike, Cycle etc. are fixed as “3 * 1”
