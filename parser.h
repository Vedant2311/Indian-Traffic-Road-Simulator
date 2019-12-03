//#include <stdio.h> 
#include <string>
using namespace std;

//void simulation(int& n, int& Total_Time, int& vehicles_on_road, int** PosX, int** PosY, int** carInd, string Vehicle_Length[50], string Vehicle_Width[50], int& runningTime);

void simulation(int& n, int& Total_Time, int& vehicles_on_road, int PosX[100][500], int PosY[100][500], int carInd[100][500], string Vehicle_Length[50], string Vehicle_Width[50], int& runningTime, int& road_length,int& road_width, int& road_zebra_width, int& road_signal_position, int signal[100], bool  isTilted[100][500], int start_end[100][500], int is_rickshaw[500]);

