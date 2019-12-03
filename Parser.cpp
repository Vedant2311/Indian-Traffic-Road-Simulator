#include <bits/stdc++.h> 
#include <string> 
#include<fstream>
#include <chrono>
#include <thread>
#include <unistd.h>


using namespace std;

void updateLane (int** laneCarIndex, int carLaneNumber, int carLaneIndex){
	
	int temp = laneCarIndex[carLaneNumber][carLaneIndex];
	
	laneCarIndex[carLaneNumber][carLaneIndex] = laneCarIndex[carLaneNumber][carLaneIndex-1];
	laneCarIndex[carLaneNumber][carLaneIndex-1] = temp;
	
}

int findLaneNumber(int index, int** laneCarIndex, int lanes){
	
	int i=0;


	for(i=0; i< lanes; i++){
		
		int j=0;
		
		for(; j<10; j++){
			
			if(laneCarIndex[i][j] == index) break;
			
		}
		
		if(laneCarIndex[i][j] == index) break;
			
	}
	if(i==lanes) {cout<< "The Vehicle is not present anywhere"; return -1;}
	
	return i;
	
}

int findLaneIndex(int index, int** laneCarIndex, int lanes){
	
	
	int i=0;
	int j =0;
	for(i=0; i< lanes; i++){
		
		for(j=0; j<10; j++){

			if(laneCarIndex[i][j] == index) break;
			
		}
		//cout<<laneCarIndex[i][j]<<endl;
		if(j<10) {if(laneCarIndex[i][j] == index) break;}
	}
	 
	if(j==10) {cout<< "The Vehicle is not present anywhere"; return -1;}
	
	return j;
	
}


int findIndexOfStr(string* Vehicle, string VehicleInside, int len){
		
		int i=0;
		
		for(; i<len; i++){
			
			string tempVeh = Vehicle[i];
		   // cout<<tempVeh<<endl;
			if(strcmp(VehicleInside.c_str(), tempVeh.c_str())==0) break;
		
		}
		
		if(i==len) {
			//cout<< "Vehicle "<< VehicleInside <<endl;;
		//	cerr << "Invalid Call" << '\n';  
			return 0;
			
		}
		
		return i;
	}


int topLeftX(int posX, int posY, string* Vehicle, string VehicleInside, int len, string* Vehicle_Length){
		
		int index = findIndexOfStr(Vehicle,VehicleInside,len);
		
		//cout<<index<<endl;
		return (posX - atoi(Vehicle_Length[index].c_str()) +1);
		
	}


// COMMENT: position of the top left point
int topLeftY(int posX, int posY,  string* Vehicle, string VehicleInside, int len,string* Vehicle_Width){
	
		int index = findIndexOfStr(Vehicle,VehicleInside,len);
		
		
		return (posY - atoi(Vehicle_Width[index].c_str()) +1);
		
		
	}

int findFirstAhead(int** laneCarIndex, int carLaneNumber, int* PosX, int* PosY, string* Vehicle, string* VehicleInside, int len, string* Vehicle_Length, int carLaneIndex, int index) {

	if (carLaneIndex == 0) { return -1; }
	int i = 0;
	for (; i < carLaneIndex; i++) {

		if (laneCarIndex[carLaneNumber][i] == 0) break;

		else if ((topLeftX(PosX[(laneCarIndex[carLaneNumber][i])], PosY[(laneCarIndex[carLaneNumber][i])], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][i])], len, Vehicle_Length)) >= PosX[index]) continue;
		else break;
	}


	if (i == 0) { return -1; }
	else {

		return (laneCarIndex[carLaneNumber][i - 1]);

	}

}


bool aboutToCollide(int** laneCarIndex, int index, int carLaneNumber, int carLaneIndex, int* Vf, int* A, int* PosX, int* PosY, int len, string* Vehicle, string* VehicleInside, string* Vehicle_Length){

	//cout << "reached here " << index << endl;
	
	if(carLaneIndex==0) return false;
	else{
		
		int topLeft = topLeftX(PosX[(laneCarIndex[carLaneNumber][carLaneIndex-1])], PosY[(laneCarIndex[carLaneNumber][carLaneIndex-1])], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length);
		
	  //	cout << (topLeft - PosX[index]) << " for index " << index << endl;
		
		if((topLeft - PosX[index]) <=4){
			
			return true;
		}
		
		else{
			
			return false;
		}
	}
		
	
}

int smallestAhead(int P, int pos, int* PosX, int** laneCarIndex){
	
	int j = 0;
	
	for(; j<10; j++){
		
		if(laneCarIndex[P][j]==0) break;	
		else{
			
			if(PosX[(laneCarIndex[P][j])] >= pos) continue;
			else break;
		}
		
	}
	
	if(j==0){
		
		return -1;
		
	}
	
	else {
		return (laneCarIndex[P][j-1]);
		
	}
	
	
}


int largestBehind(int P, int pos, int* PosX, int** laneCarIndex){
	
	int j = 0;
	
	for(; j<10; j++){
		
		if(laneCarIndex[P][j]==0) break;	
		else{
			
			if(PosX[(laneCarIndex[P][j])] >= pos) continue;
			else break;
		}
		
	}
	
	if((j==10) || (laneCarIndex[P][j] == 0)){
		
		return -1;
		
	}
	
	else {
		return (laneCarIndex[P][j]);
		
	}
	
	
}


int isAnyNearby0(int P, int pos, int* PosX, int** laneCarIndex, int Road_Length, string* VehicleInside, int index, string* Vehicle, string* Vehicle_Length, int len){
	
	int temp = 0;	// 0 means that there is Empty space. So NO for nearby!
	
	int SmallestAhead = smallestAhead(P,pos,PosX, laneCarIndex);
	int LargestBehind = largestBehind(P,pos,PosX, laneCarIndex);

	int ans[2];   // 0 for Vehicle Index to be constrained; 1 for the constrain
	
	if((SmallestAhead==-1) && (LargestBehind==-1)) 
	{
		ans[1] = -1;	// The whole road is Empty. Easy to overtake.
		ans[0] = -1;	// No Vehicle to be constrained
			//cout << "ENDs hre 0: " << index << endl;	  
		return ans[0];
	}	
	else if(LargestBehind==-1){		// There is no one behind this Vehicle
	//	cout << "smallestAhead 1: " << SmallestAhead <<  "  "<< index << endl;	  
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[SmallestAhead],len)].c_str());
	//	cout << "Vehicle size " << vehSize << " of index" << index << endl;	
		
		if(PosX[SmallestAhead] - pos <= vehSize+1) {
			ans[0] = -1;   // No use of constraint
			ans[1] = 1; 	//There is no space in this lane
			 	
	//	cout << "ENDs hre 1: " << index << endl;	  
			return ans[0];
		}
		else {
			
			ans[0] = -1;	// Still no constraints since there is no Vehicle behind it
			ans[1] = 0;		// Overtake but with constraints 
			//cout << "ENDs hre 1: " << index << endl;	  
			return ans[0];
		}
		
	}
	
	else if(SmallestAhead==-1){		// There is no one Ahead this Vehicle
		
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[index],len)].c_str());

		if(-PosX[LargestBehind] + pos <= vehSize + 5) { 	
		
			ans[1] = 1;	//There is no space in this lane ('5' is randomly deffined.)
			ans[0] = -1; 	// No use of constraint
		//cout << "ENDs hre 2: " << index << endl;	  
			return ans[0];
			
		}
		else {

			ans[0] = LargestBehind;	// The Vehicle Behind it will now be constrained
			ans[1] = 0;		// Overtake but with constraints 
			//cout << "ENDs hre 2: " << index << endl;	  
			return ans[0];
	
			
			
		}
		
	}
	
	else{		// There is a vehicle ahead as well as a Vehicle Behind.
		
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[index],len)].c_str());
		int vehSize1 = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[SmallestAhead],len)].c_str());

		
		if((-PosX[LargestBehind] + pos <= vehSize + 5) || (PosX[SmallestAhead] - pos <= vehSize1 + 1)){
			
			ans[1] = 1;	//There is no space in this lane ('5' is randomly deffined.)
			ans[0] = -1; 	// No use of constraint
			//cout << "ENDs hre 3: " << index << endl;	  
			return ans[0];
			
			
		}
		
		else{
			
			ans[0] = LargestBehind;	// The Vehicle Behind it will now be constrained
			ans[1] = 0;		// Overtake but with constraints 
		//	cout << "ENDs hre 3: " << index << endl;	  
			return ans[0];
	
			
		}
		
	}
	
}

int isAnyNearby1(int P, int pos, int* PosX, int** laneCarIndex, int Road_Length, string* VehicleInside, int index, string* Vehicle, string* Vehicle_Length, int len){
	
	int temp = 0;	// 0 means that there is Empty space. So NO for nearby!
	
	int SmallestAhead = smallestAhead(P,pos,PosX, laneCarIndex);
	int LargestBehind = largestBehind(P,pos,PosX, laneCarIndex);

	int ans[2];   // 0 for Vehicle Index to be constrained; 1 for the constrain
	
	if((SmallestAhead==-1) && (LargestBehind==-1)) 
	{
		ans[1] = -1;	// The whole road is Empty. Easy to overtake.
		ans[0] = -1;	// No Vehicle to be constrained
			//cout << "ENDs hre 0: " << index << endl;	  
		return ans[1];
	}	
	else if(LargestBehind==-1){		// There is no one behind this Vehicle
	//	cout << "smallestAhead 1: " << SmallestAhead <<  "  "<< index << endl;	  
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[SmallestAhead],len)].c_str());

		
		if(PosX[SmallestAhead] - pos <= vehSize + 1) {
			
			ans[1] = 1; 	//There is no space in this lane
			ans[0] = -1; 	// No use of constraint
		//cout << "ENDs hre 11: " << index << endl;	  
			return ans[1];
		}
		else {
			
			ans[0] = -1;	// Still no constraints since there is no Vehicle behind it
			ans[1] = 0;		// Overtake but with constraints 
			//cout << "ENDs hre 11: " << index << endl;	  
			return ans[1];
		}
		
	}
	
	else if(SmallestAhead==-1){		// There is no one Ahead this Vehicle
		
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[index],len)].c_str());

		if(-PosX[LargestBehind] + pos <= vehSize + 5) { 	
		
			ans[1] = 1;	//There is no space in this lane ('5' is randomly deffined.)
			ans[0] = -1; 	// No use of constraint
		//cout << "ENDs hre 2: " << index << endl;	  
			return ans[1];
			
		}
		else {

			ans[0] = LargestBehind;	// The Vehicle Behind it will now be constrained
			ans[1] = 0;		// Overtake but with constraints 
			//cout << "ENDs hre 2: " << index << endl;	  
			return ans[1];
	
			
			
		}
		
	}
	
	else{		// There is a vehicle ahead as well as a Vehicle Behind.
		
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[index],len)].c_str());
		int vehSize1 = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[SmallestAhead],len)].c_str());

		
		if((-PosX[LargestBehind] + pos <= vehSize + 5) || (PosX[SmallestAhead] - pos <= vehSize1+1)){
			
			ans[1] = 1;	//There is no space in this lane ('5' is randomly deffined.)
			ans[0] = -1; 	// No use of constraint
			//cout << "ENDs hre 3: " << index << endl;	  
			return ans[1];
			
			
		}
		
		else{
			
			ans[0] = LargestBehind;	// The Vehicle Behind it will now be constrained
			ans[1] = 0;		// Overtake but with constraints 
		//	cout << "ENDs hre 3: " << index << endl;	  
			return ans[1];
	
			
		}
		
	}
	
}



int findEmptyNeighbour0(int** laneCarIndex, int carLaneNumber, int lanes, int index, int* PosX, int Road_Length, string* VehicleInside, string* Vehicle, string* Vehicle_Length, int len){
	
	int P1,P2 = -1;
	int ans[3];	// 0 -> LaneNumber, 1 -> Vehicle to be constrained, 2 -> Constraint level
	
	if(carLaneNumber==0) {
		
		P2 =1;
		int pos1 = PosX[index];
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P2;
		ans[1] = temp0;
		ans[2] = temp1;
		return ans[0];
	
	}
	
	else if(carLaneNumber==lanes-1) {
		
		
		P1 = lanes-2;
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P1;
		ans[1] = temp0;
		ans[2] = temp1;
		
		return ans[0];
	
	
	
	}
	else{
		
		P1 = carLaneNumber-1; 
		P2 = carLaneNumber+1;
		
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    
		
		if(temp1==1){
			
			int temp10 =  isAnyNearby0(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			int temp11 =  isAnyNearby1(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			
			
			if(temp11==1){
				
				
				// Random impossible values to set the constraint that no overtaking is possible
				ans[0] = lanes;
				ans[1] = 0;
				ans[2] = 1;
				
				return ans[0];
			} 
			
			else{
				
				ans[0] = P1;
				ans[1] = temp10;
				ans[2] = temp11;
				
				return ans[0];
				
			}
			
		}
		
		else{
			
			ans[0] = P2;
			ans[1] = temp0;	
			ans[2] = temp1;
			return ans[0];
	
			
		
		}
	
	}
	
	
	
	
	
	
}

int findEmptyNeighbour1(int** laneCarIndex, int carLaneNumber, int lanes, int index, int* PosX, int Road_Length, string* VehicleInside, string* Vehicle, string* Vehicle_Length, int len){
	
	int P1,P2 = -1;
	int ans[3];	// 0 -> LaneNumber, 1 -> Vehicle to be constrained, 2 -> Constraint level
	
	if(carLaneNumber==0) {
		
		P2 =1;
		int pos1 = PosX[index];
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P2;
		ans[1] = temp0;
		ans[2] = temp1;
		return ans[1];
	
	}
	else if(carLaneNumber==lanes-1) {
		
		
		P1 = lanes-2;
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P1;
		ans[1] = temp0;
		ans[2] = temp1;
		
		return ans[1];
	
	
	
	}
	else{
		
		P1 = carLaneNumber-1; 
		P2 = carLaneNumber+1;
		
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    
		
		if(temp1==1){
			
			int temp10 =  isAnyNearby0(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			int temp11 =  isAnyNearby1(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			
			
			if(temp11==1){
				
				
				// Random impossible values to set the constraint that no overtaking is possible
				ans[0] = lanes;
				ans[1] = 0;
				ans[2] = 1;
				
				return ans[1];
			} 
			
			else{
				
				ans[0] = P1;
				ans[1] = temp10;
				ans[2] = temp11;
				
				return ans[1];
				
			}
			
		}
		
		else{
			
			ans[0] = P2;
			ans[1] = temp0;	
			ans[2] = temp1;
			return ans[1];
	
			
		
		}
	
	}
	
	
	
	
	
	
}

int findEmptyNeighbour2(int** laneCarIndex, int carLaneNumber, int lanes, int index, int* PosX, int Road_Length, string* VehicleInside, string* Vehicle, string* Vehicle_Length, int len){
	
	int P1,P2 = -1;
	int ans[3];	// 0 -> LaneNumber, 1 -> Vehicle to be constrained, 2 -> Constraint level
	
	if(carLaneNumber==0) {
		
		P2 =1;
		int pos1 = PosX[index];
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P2;
		ans[1] = temp0;
		ans[2] = temp1;
		return ans[2];
	
	}
	else if(carLaneNumber==lanes-1) {
		
		
		P1 = lanes-2;
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P1;
		ans[1] = temp0;
		ans[2] = temp1;
		
		return ans[2];
	
	
	
	}
	else{
		
		P1 = carLaneNumber-1; 
		P2 = carLaneNumber+1;
		
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    
		
		if(temp1==1){
			
			int temp10 =  isAnyNearby0(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			int temp11 =  isAnyNearby1(P1, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			
			
			if(temp11==1){
				
				
				// Random impossible values to set the constraint that no overtaking is possible
				ans[0] = lanes;
				ans[1] = 0;
				ans[2] = 1;
				
				return ans[2];
			} 
			
			else{
				
				ans[0] = P1;
				ans[1] = temp10;
				ans[2] = temp11;
				
				return ans[2];
				
			}
			
		}
		
		else{
			
			ans[0] = P2;
			ans[1] = temp0;	
			ans[2] = temp1;
			return ans[2];
		
		}
	
	}
	
}



void addInLayer(int** laneCarIndex, int lanes, int changingLane, int index, int* PosX){
	
	//cout << "HAallo " << endl;
	
	int i=0;
	
	for(; i<10; i++){
		
		if(laneCarIndex[changingLane][i]==0) break;
		else{
			
			int val = PosX[(laneCarIndex[changingLane][i])];
			
			if(val < PosX[index]) break;
			
			
		}
	}
	
	//cout << "Position to be added " << i << endl;
	
	if(i<10){
		
		for(int j=9 ; j>i ;j--){
			
			
				laneCarIndex[changingLane][j] = laneCarIndex[changingLane][j-1];
				//cout << laneCarIndex[changingLane][j] << " ";
		
			
		}
		
		laneCarIndex[changingLane][i] = index;
		
	}
	
	return;
}

void removeFromLayer(int** laneCarIndex, int lanes, int carLaneNumber, int carLaneIndex, int index, int PosX){
	
	for(int i=carLaneIndex; i<10; i++){
		
		if(laneCarIndex[carLaneNumber][i]==0) break;
		else{
			
			laneCarIndex[carLaneNumber][i] = laneCarIndex[carLaneNumber][i+1];
			
		}
		
	}
	
	
	return;
}


bool presentInMany(int** laneCarIndex, int index, int lanes) {

	bool temp = false;

	for (int i = 0; i < lanes; i++) {
	
		for (int j = 0; j < 10; j++) {
		
			if (laneCarIndex[i][j] == index) {
			
				if (!temp) temp = true;
				else return true;
			}
		}
	
	}
	return false;
}



// COMMENT: Kinematics and constraints!
int positionUpdate(int index, int* V, int* Vf, int* A, int* Ret, int* LaneChange, char*** Road, int t, int* Start_Time, int* PosX, int* PosY, char* ColorInside, string* VehicleInside, bool RG, int** laneCarIndex, int** laneInfo, int lanes, int Road_Length, int Road_Width, string* Vehicle, string* Vehicle_Length, string* Vehicle_Width, int len, bool* isOvertaking, string* Vehicle_LaneChange, int* overtakeLayer, int vehAmount, string* Default, int* laneStopPosition, bool* isTilted, int trafficJam[][100],int start_end[500]) {

	if (ColorInside[index] != ' ') {

		if (RG) {

			int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);

			if ((!isOvertaking[index]) && (!isTilted[index]) )   {

				if (carLaneIndex < trafficJam[carLaneNumber][t]) {

					if ((carLaneNumber == lanes) || (carLaneIndex == 10)) return -1;

					bool collision = aboutToCollide(laneCarIndex, index, carLaneNumber, carLaneIndex, Vf, A, PosX, PosY, len, Vehicle, VehicleInside, Vehicle_Length);

					if (collision == false) {


						
						if ((V[index] == 0 || Vf[index] == 0)) { Start_Time[index] = t - 1;  V[index] = 1; }

						int X = PosX[index] + V[index] + (((A[index])*(2 * (t - Start_Time[index]) - 1)) / 10);;

						int Y = PosY[index];
						PosX[index] = X;
						PosY[index] = Y;
						Vf[index] = V[index] + A[index] * (t - Start_Time[index]);
					}

					else {

						int end, start;

						start = carLaneNumber * (Road_Width / lanes);
						end = start + (Road_Width / lanes) - 1;
							//	cout << "Reached here " << ColorInside[index] << endl;

						//0 -> LaneNumber, 1 -> Vehicle to be constrained, 2 -> Constraint level

						int neighbour[3];

						neighbour[0] = findEmptyNeighbour0(laneCarIndex, carLaneNumber, lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint
						neighbour[1] = findEmptyNeighbour1(laneCarIndex, carLaneNumber, lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint
						neighbour[2] = findEmptyNeighbour2(laneCarIndex, carLaneNumber, lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint

						if ((PosX[index] < 0) || (neighbour[2] == 1)) {

							if((VehicleInside[index] == "Scooter") || (VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") ){
								//cout << "Reached here Bike: " << ColorInside[index] << endl;
								
							}

							if(PosX[index] == PosX[laneCarIndex[carLaneNumber][carLaneIndex-1]]){
							
							// Do nothing. Stable boi
							
							}

							else if (((VehicleInside[index] != "Cycle") && (VehicleInside[index] != "Scooter") && (VehicleInside[index] != "Bike")) || (PosX[index] < 0)) {

								if ((VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]] == "Cycle") || (VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]] == "Bike") || (VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]] == "Scooter")) {

									if (!((PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] == start) || (PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] == end))) {
										Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect

										PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
									}

									else if(((PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] == start) && (PosY[index] == end)) || ((PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] == end) && (PosY[index] == end-1))) {

										if ((V[index] == 0 || Vf[index] == 0)) { Start_Time[index] = t - 1;  V[index] = 1; }

										int X = PosX[index] + V[index] + (((A[index])*(2 * (t - Start_Time[index]) - 1)) / 10);

										int Y = PosY[index];
										PosX[index] = X;
										PosY[index] = Y;
										Vf[index] = V[index] + A[index] * (t - Start_Time[index]);

										
									}
									
									else{
										
										Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
	
	
										PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;

										
									}
								}

								else {
									Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
	
	
									PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;


								}

							}

							else {



								if (!((PosY[index] - PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] >= 1) || (topLeftY(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Width) > PosY[index]))) {

									Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect

									PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
								}

								else {

									if ((V[index] == 0 || Vf[index] == 0)) { Start_Time[index] = t - 1;  V[index] = 1; }

									int X = PosX[index] + V[index] + (((A[index])*(2 * (t - Start_Time[index]) - 1)) / 10);;

									int Y = PosY[index];
									PosX[index] = X;
									PosY[index] = Y;
									Vf[index] = V[index] + A[index] * (t - Start_Time[index]);

									if (PosX[index] >= PosX[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]) {

										updateLane(laneCarIndex, carLaneNumber, carLaneIndex);

									}

								}

							}

						}

						else if ((neighbour[2] == -1) || (neighbour[2] == 0)) {

							// No constrain

							int changingLane = neighbour[0];
							isOvertaking[index] = true;
							overtakeLayer[index] = changingLane;

							if (carLaneNumber < changingLane) {

								// Goes down now

								LaneChange[index] = atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str());
								PosY[index] = PosY[index] + LaneChange[index];

								if(carLaneIndex!=0){
									Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect

									PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
								}
								
								else{
								
									PosX[index] = PosX[index] +2;
								}

								int laneEnd = changingLane * (Road_Width / lanes);

								if ((topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width)) >= laneEnd) {

									PosY[index] = laneEnd + atoi(Vehicle_Width[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str()) - 1;
									isOvertaking[index] = false;
									LaneChange[index] = 0;
									overtakeLayer[index] = -1;
									addInLayer(laneCarIndex, lanes, changingLane, index, PosX);
									V[index] = 1;
									removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
								}

							}


							else {

								LaneChange[index] = -atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str());
								PosY[index] = PosY[index] + LaneChange[index];

								if(carLaneIndex!=0){
									Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect

									PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
								}
								
								else{
									PosX[index] = PosX[index] + 2;
								}

								int laneEnd;

								if (changingLane == lanes - 1) {

									laneEnd = Road_Width - 1;
								}

								else laneEnd = changingLane * (Road_Width / lanes) + (Road_Width / lanes) - 1;


								if (PosY[index] <= laneEnd) {
									PosY[index] = laneEnd;
									isOvertaking[index] = false;
									LaneChange[index] = 0;
									overtakeLayer[index] = -1;
									addInLayer(laneCarIndex, lanes, changingLane, index, PosX);
									V[index] = 1;
									removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
								}



							}


						}



					}

					// Show the updates on the corresponding road.	

					int rightBottomX = PosX[index];
					int rightBottomY = PosY[index];

					int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Length);
					int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width);




					if ((rightBottomX > 0) && (leftTopX < Road_Length)) {
						for (int j = max(0, leftTopX); j <= (min(Road_Length, rightBottomX)); j++) {

							for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {

								Road[t][i][j] = ColorInside[index];


							}

							//cout << endl;
						}

						int zeroLine = min(Road_Length, PosX[index]) + (vehAmount - Road_Length - 1) + 1;
						int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
						int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
						for (int i = zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--) { laneInfo[carLaneNumber][i] = 1; }


					}

					else if (leftTopX >= Road_Length) {

						ColorInside[index] = ' ';
						int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
						int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);

						removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
					}

					else {

						// Do nothing
					}
					
					
					return 0;
				}

				else {
					
					if(topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex-1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex-1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex-1]], len, Vehicle_Length) - PosX[index] >= 3){
						
						PosX[index] = PosX[index] + 1;
						for(int j=t+1; j<100; j++) {trafficJam[carLaneNumber][j] = 1000;}
					}
					
					
					int rightBottomX = PosX[index];
					int rightBottomY = PosY[index];

					int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Length);
					int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width);

					for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {
					
						for (int j = leftTopX; j <= rightBottomX; j++) {
							Road[t][i][j] = ColorInside[index];
						}
					
					}
					
				}
			
			}

			else if (!isTilted[index]) {

				if (carLaneIndex < trafficJam[carLaneNumber][t]) {

					int changingLane = overtakeLayer[index];
					int SmallestAhead3 = smallestAhead(changingLane, PosX[index], PosX, laneCarIndex);

					if (carLaneNumber < changingLane) {

						// Goes down now

						LaneChange[index] = atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];

						if(carLaneIndex !=0){
							Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect

							PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
						}
						
						else if((SmallestAhead3!=-1) &&(topLeftX(PosX[SmallestAhead3], PosY[SmallestAhead3], Vehicle, VehicleInside[SmallestAhead3], len, Vehicle_Length) - (PosX[index] + Vf[index])<= 2)){
						
						PosX[index] = topLeftX(PosX[SmallestAhead3], PosY[SmallestAhead3], Vehicle, VehicleInside[SmallestAhead3], len, Vehicle_Length) -2;
						
						}
						
						else{
							PosX[index] = PosX[index] + 2;
						}

						int laneEnd = changingLane * (Road_Width / lanes);

						if ((topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width)) >= laneEnd) {
							PosY[index] = laneEnd + atoi(Vehicle_Width[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str()) - 1;
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							overtakeLayer[index] = -1;
							addInLayer(laneCarIndex, lanes, changingLane, index, PosX);
							V[index] = 1;
							removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
						}

					}

					else {

						LaneChange[index] = -atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						if(carLaneIndex!=0){
							Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
							
							PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
						}
						
						else if((SmallestAhead3!=-1) && (topLeftX(PosX[SmallestAhead3], PosY[SmallestAhead3], Vehicle, VehicleInside[SmallestAhead3], len, Vehicle_Length) - (PosX[index] + Vf[index])<= 2)){
						
						PosX[index] = topLeftX(PosX[SmallestAhead3], PosY[SmallestAhead3], Vehicle, VehicleInside[SmallestAhead3], len, Vehicle_Length) -2;
						
						}
						
						else{
						
							PosX[index] = PosX[index] + 2;
						}


						int laneEnd;

						if (changingLane == lanes - 1) {

							laneEnd = Road_Width - 1;
						}

						else laneEnd = changingLane * (Road_Width / lanes) + (Road_Width / lanes) - 1;


						if (PosY[index] <= laneEnd) {
							PosY[index] = laneEnd;
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							overtakeLayer[index] = -1;
							addInLayer(laneCarIndex, lanes, changingLane, index, PosX);
							V[index] = 1;
							removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
						}



					}


					int rightBottomX = PosX[index];
					int rightBottomY = PosY[index];

					int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Length);
					int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width);

					if ((rightBottomX > 0) && (leftTopX < Road_Length)) {
						for (int j = max(0, leftTopX); j <= (min(Road_Length, rightBottomX)); j++) {

							for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {

								Road[t][i][j] = ColorInside[index];


							}

							//cout << endl;
						}

						int zeroLine = min(Road_Length, PosX[index]) + (vehAmount - Road_Length - 1) + 1;
						int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
						int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
						for (int i = zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--) { laneInfo[carLaneNumber][i] = 1; }


					}

					else if (leftTopX >= Road_Length) {

						ColorInside[index] = ' ';
						int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
						int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);

						removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
					}

					else {

						// Do nothing
					}


					return 0;
				}

				else {
				
					if(topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex-1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex-1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex-1]], len, Vehicle_Length) - PosX[index] >= 3){
						
						PosX[index] = PosX[index] + 1;
						for(int j=t+1; j<100; j++) {trafficJam[carLaneNumber][j] = 1000;}
					}
					
				
					int rightBottomX = PosX[index];
					int rightBottomY = PosY[index];

					int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Length);
					int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width);

					for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {

						for (int j = leftTopX; j <= rightBottomX; j++) {
							Road[t][i][j] = ColorInside[index];
						}

					}

				}

			}

			else {

				

				if (((VehicleInside[index] != "Cycle") && (VehicleInside[index] != "Scooter") && (VehicleInside[index] != "Bike") && (VehicleInside[index] == "Motor_Rickshaw")) || (PosX[index] < 0))	return -1;  // Error!
				else if(VehicleInside[index] != "Motor_Rickshaw") {

					int end, start;

					start = carLaneNumber * (Road_Width / lanes);
					end = start + (Road_Width / lanes) - 1;

					int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
					int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);

					int tempPos = PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]];

					if (((PosY[index] == end) || (PosY[index] == start)) && (PosX[index] != tempPos)) {

						


						if (PosY[index] == start) {
							start_end[index] = 1;
							Road[t][PosY[index]+2][PosX[index] ] = ColorInside[index];
							Road[t][PosY[index]+2][PosX[index]+1 ] = ColorInside[index];
							Road[t][PosY[index]+2 +1][PosX[index] ] = ColorInside[index];
						}

						else {
							start_end[index] = 0;
							Road[t][PosY[index]+2][PosX[index] ] = ColorInside[index];
							Road[t][PosY[index]+2][PosX[index]+1 ] = ColorInside[index];
							Road[t][PosY[index]+2 -1][PosX[index] ] = ColorInside[index];
						}

						PosX[index] = tempPos;

					}

					else {

						isTilted[index] = false;

						for (int p = PosX[index]; p >= PosX[index] - 2; p--) {
							Road[t][PosY[index]+2][p] = ColorInside[index];
						}

						 updateLane(laneCarIndex, carLaneNumber, carLaneIndex);
					}

				}

				else {
				
					if (presentInMany(laneCarIndex, index, lanes)) {

						int carLaneNumber2 = carLaneNumber + 1;
						int carLaneIndex2 = -1;

						int z = 0;
						for (; z < 10; z++) { 
							if (laneCarIndex[carLaneNumber2][z] == index) {
							
								carLaneIndex2 = z;
								break;
							}
						
						}
					
						if (z==10) return 0;

						int end, start;


						start = carLaneNumber * (Road_Width / lanes);
						end = start + (Road_Width / lanes) - 1;

						if ((carLaneIndex == 0) && (carLaneIndex2==0)) {
						
							PosX[index] = PosX[laneCarIndex[carLaneNumber][carLaneIndex+1]] + 3;
							PosY[index] = end;

							

							for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = 1000; }
							for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber2][j] = 1000; }
							
							isTilted[index] = false;
							removeFromLayer(laneCarIndex,lanes,carLaneNumber2,carLaneIndex2,index, PosX[index]);

							for (int a = PosY[index] - 1 + 2; a <= PosY[index] + 2;  a++ ) {
								for (int b = PosX[index] - 1; b <= PosX[index]; b++) {
									Road[t][a][b] = ColorInside[index];
								}
							
							}
						
						}

						else if((carLaneIndex!=0) && (carLaneIndex2 != 0)) {
						
							if (topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex-1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Length) - PosX[index] >= 2) {
							
								PosY[index] = end;
								PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Length) - 1;

								removeFromLayer(laneCarIndex, lanes, carLaneNumber2, carLaneIndex2, index, PosX[index]);
								isTilted[index] = false;

								for (int a = PosY[index] - 1 + 2; a <= PosY[index] + 2; a++) {
									for (int b = PosX[index] - 1; b <= PosX[index]; b++) {
										Road[t][a][b] = ColorInside[index];
									}

								}

								for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = 1000; }
								for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber2][j] = 1000; }
							}

							else {

								for (int a = PosY[index] - 1 + 2; a <= PosY[index] + 2; a++) {
									for (int b = PosX[index] - 1; b <= PosX[index]; b++) {
										Road[t][a][b] = ColorInside[index];
									}

								}
							
							}
						
						}

						else return -1;
					}

					else {
					
						if (topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Length) - PosX[index] >= 2) {
							
							int end, start;


							start = carLaneNumber * (Road_Width / lanes);
							end = start + (Road_Width / lanes) - 1;

							PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Length) - 1;
							PosY[index] = end;

							isTilted[index] = false;
							for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = 1000; }

							for (int a = PosY[index] - 1 + 2; a <= PosY[index] + 2; a++) {
								for (int b = PosX[index] - 1; b <= PosX[index]; b++) {
									Road[t][a][b] = ColorInside[index];
								}

							}
						
						}

						else {
						
							Road[t][PosY[index] + 2][PosX[index]] = ColorInside[index];
							Road[t][PosY[index] + 2][PosX[index]-1] = ColorInside[index];
							Road[t][PosY[index] + 2][PosX[index]+1] = ColorInside[index];
							Road[t][PosY[index] + 2 + 1][PosX[index]] = ColorInside[index];
							Road[t][PosY[index] + 2 -1][PosX[index]] = ColorInside[index];
						
						}
					
					}

				}
			}

			return 0;
		}


		else {
			bool already_ahead = false;
			int Road_Signal_Position = atoi(Default[6].c_str());
			
			if ((!isOvertaking[index]) && (!isTilted[index])) {

				bool flag = false;
				bool update = true;
				

				
				int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
				int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);

				if ((carLaneNumber == lanes) || (carLaneIndex == 10)) return -1;

				bool collision = aboutToCollide(laneCarIndex, index, carLaneNumber, carLaneIndex, Vf, A, PosX, PosY, len, Vehicle, VehicleInside, Vehicle_Length);

				if (collision == false) {

					if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter")))) already_ahead = true;

					int X = PosX[index] + V[index] + (((A[index])*(2 * (t - Start_Time[index]) - 1))*(1 / 2));

					int Y = PosY[index];

					PosX[index] = X;
					PosY[index] = Y;
					Vf[index] = V[index] + A[index] * (t - Start_Time[index]);
				}

				else {

					int end, start;


					start = carLaneNumber * (Road_Width / lanes);
					end = start + (Road_Width / lanes) - 1;

					
					int neighbour[3];

					neighbour[2] = findEmptyNeighbour2(laneCarIndex, carLaneNumber, lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint
					neighbour[1] = findEmptyNeighbour1(laneCarIndex, carLaneNumber, lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint
					neighbour[0] = findEmptyNeighbour0(laneCarIndex, carLaneNumber, lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint


					if((Vf[laneCarIndex[carLaneNumber][carLaneIndex-1]] == 0)  && (VehicleInside[index] != "Scooter") && (VehicleInside[index] != "Motor_Rickshaw") && (VehicleInside[index] != "Bike") && (VehicleInside[index] != "Cycle")){
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
						PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
					}

					else if ((PosX[index] < 0) || (neighbour[2] == 1)) {

						if(PosX[index] == PosX[laneCarIndex[carLaneNumber][carLaneIndex-1]]){
							
							// Do nothing. Stable boi
							
						}

						else if (((VehicleInside[index] != "Cycle") && (VehicleInside[index] != "Scooter") &&(VehicleInside[index] != "Bike") && (VehicleInside[index] != "Motor_Rickshaw")) || (PosX[index] <0)) {

							

							if((VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex-1]] == "Cycle") || (VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex-1]] == "Bike") || (VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex-1]] == "Scooter")){
								
								if(!(( PosY[laneCarIndex[carLaneNumber][carLaneIndex-1]] == start ) || (PosY[laneCarIndex[carLaneNumber][carLaneIndex-1]] == end))){
									Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
									if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter")))) already_ahead = true;
									PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
								}
								
								else{
									    //cout << "is Here "<< ColorInside[index] << endl;
								//		if ((V[index] == 0 || Vf[index] == 0)) { Start_Time[index] = t - 1;  V[index] = 1; }
//										if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter")))) already_ahead = true; 
//										int X = PosX[index] + V[index] + (((A[index])*(2 * (t - Start_Time[index]) - 1)) / 10);
//
//										int Y = PosY[index];
//										PosX[index] = X;
//										PosY[index] = Y;
//										Vf[index] = V[index] + A[index] * (t - Start_Time[index]);

										Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
	
	
									PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
									}
							}
							
							else{
									Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
									if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter")))) already_ahead = true;
									PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
								
								
							}
						
							

						}

						else if(VehicleInside[index] != "Motor_Rickshaw") {

							
							if (!((PosY[index] - PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] >= 1) || (topLeftY(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Width) > PosY[index]))) {
								
								if (Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])] !=0) {
									
									Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect

									if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
									PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
								}

								else {
								
									update = false;
									isTilted[index] = true;

									int tempPos = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Length);
									if (PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] == start) {
									
										// Hardcoded the size to 3



										Road[t][PosY[index]+2][tempPos -1] = ColorInside[index];
										Road[t][PosY[index]+2][tempPos - 2] = ColorInside[index];
										Road[t][PosY[index] + 1 + 2][tempPos - 1] = ColorInside[index];
										 
										 if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
										 
										PosX[index] = tempPos - 1;
										PosY[index] = end;
										

									}

									else {
									
										Road[t][PosY[index]+2][tempPos - 1] = ColorInside[index];
										Road[t][PosY[index]+2][tempPos - 2] = ColorInside[index];
										Road[t][PosY[index] - 1 + 2][tempPos - 1] = ColorInside[index];

										if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;

										PosX[index] = tempPos - 1;
										PosY[index] = start;

										
									}

									laneStopPosition[carLaneNumber] = PosX[index];

								}
							}


							else {
								
								flag = true;
								if ((V[index] == 0 || Vf[index] == 0)) { Start_Time[index] = t - 1;  V[index] = 1; }

								if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;

								int X = PosX[index] + V[index] + (((A[index])*(2 * (t - Start_Time[index]) - 1)) / 10);;

								int Y = PosY[index];
								PosX[index] = X;
								PosY[index] = Y;
								Vf[index] = V[index] + A[index] * (t - Start_Time[index]);

								if (PosX[index] >= PosX[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]) {

									 updateLane(laneCarIndex, carLaneNumber, carLaneIndex);

								}


							}


						}

						else {
						
							int end, start;


							start = carLaneNumber * (Road_Width / lanes);
							end = start + (Road_Width / lanes) - 1;

							int P1, P2 = -1;
							int SmallestAhead1 = -1;
							int SmallestAhead2 = -1;

							int LargestBehind1 = -1;
							int LargestBehind2 = -1;

							if (carLaneNumber == 0) {
							
								P1 = 1;
								SmallestAhead1 = smallestAhead(P1, PosX[index], PosX, laneCarIndex);
								LargestBehind1 = largestBehind(P1, PosX[index], PosX, laneCarIndex);
							}

							else if (carLaneNumber == lanes-1) {
								P2 = lanes - 2;
								SmallestAhead2 = smallestAhead(P2, PosX[index], PosX, laneCarIndex);
								LargestBehind2 = largestBehind(P2, PosX[index], PosX, laneCarIndex);
							}

							else {
								
								P1 = carLaneNumber + 1;
								P2 = carLaneNumber - 1;
								SmallestAhead1 = smallestAhead(P1, PosX[index], PosX, laneCarIndex);
								SmallestAhead2 = smallestAhead(P2, PosX[index], PosX, laneCarIndex);

								LargestBehind1 = largestBehind(P1, PosX[index], PosX, laneCarIndex);
								LargestBehind2 = largestBehind(P2, PosX[index], PosX, laneCarIndex);
							}

							
							if ((LargestBehind1 != -1) && (LargestBehind2 != -1)) {
							
								Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect

								if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
								PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
							}

							else if (LargestBehind1 != -1) {
								
								if ((P2 == -1) || (Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])] !=0)){
									Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
									if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
									PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
								}

								else {
								
									if (-PosY[SmallestAhead2] + (topLeftY(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Width)) >=3) {
									
										if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter")))) already_ahead = true;
										PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length);
										
										PosY[index] = topLeftY(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Width) - 1;

										for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = carLaneIndex; }
										

										

										if (topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width) < start) {
											
											isTilted[index] = true;
											addInLayer(laneCarIndex, lanes, P2, index, PosX);

											int carLaneIndex_temp = -1;

											for (int j = 0; j < 10; j++) {
												if (laneCarIndex[P2][j] == index) {
												
													carLaneIndex = j;
													break;
												}
											}

											for (int j = t + 1; j < 100; j++) { trafficJam[P2][j] = carLaneIndex_temp; }

										}

									}

									else {
										
										if ((topLeftX(PosX[SmallestAhead2],PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length))==(topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Length))) {
											update = false;
											isTilted[index] = true;
											
											laneStopPosition[carLaneNumber] = (topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length)) - 2;
											laneStopPosition[P2] = (topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length)) - 2;

											Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex-1]]+1+2][topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length)] = ColorInside[index];
											Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2][topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length)-1] = ColorInside[index];
											Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2][topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length)-2] = ColorInside[index];
											Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2 -1][topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length)-1] = ColorInside[index];
											Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2 + 1][topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length) -1] = ColorInside[index];

											for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = carLaneIndex; }
											int carLaneNumber_temp = findLaneNumber(SmallestAhead2, laneCarIndex, lanes);
											int carLaneIndex_temp = findLaneIndex(SmallestAhead2,laneCarIndex, lanes);


											PosX[index] = topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length) - 1;
											PosY[index] = PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1;

											for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber_temp][j] = carLaneIndex_temp + 1; }

											Vf[index] = 0;
											A[index] = 0;
											V[index] = 0;
											Start_Time[index] = t;
										}

										else {
											Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
											if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
											PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
										}
									
									}
								}
							
							}

							else if (LargestBehind2 != -1) {
								
								if ((P1 == -1) || (Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])] != 0)) {
									Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
									if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
									PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
								}
							
								else {
								
									if (-PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + (topLeftY(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Width)) >= 3) {

										if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
										PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length);
										PosY[index] = PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1+ (2 -1);  // Hard coded the width of the rickshaw

										for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = carLaneIndex; }

										if (PosY[index] > end) {

											isTilted[index] = true;
											addInLayer(laneCarIndex, lanes, P1, index, PosX);

											int carLaneIndex_temp = -1;

											for (int j = 0; j < 10; j++) {
												if (laneCarIndex[P1][j] == index) {

													carLaneIndex = j;
													break;
												}
											}

											for (int j = t + 1; j < 100; j++) { trafficJam[P1][j] = carLaneIndex_temp; }
										}

									}

									else {
										
										if ((topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length)) == (topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Length))) {
											update = false;
											isTilted[index] = true;

											laneStopPosition[carLaneNumber] = (topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length)) - 2;
											laneStopPosition[P1] = (topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length)) - 2;

											Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2][topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length)] = ColorInside[index];
											Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2][topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length) - 1] = ColorInside[index];
											Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2][topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length) - 2] = ColorInside[index];
											Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2 - 1][topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length) - 1] = ColorInside[index];
											Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2 + 1][topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length) - 1] = ColorInside[index];

											for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = carLaneIndex; }
											int carLaneNumber_temp = findLaneNumber(SmallestAhead1, laneCarIndex, lanes);
											int carLaneIndex_temp = findLaneIndex(SmallestAhead1, laneCarIndex, lanes);

											PosX[index] = topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length) - 1;
											PosY[index] = PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1;

											for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber_temp][j] = carLaneIndex_temp + 1; }

											Vf[index] = 0;
											A[index] = 0;
											V[index] = 0;
											Start_Time[index] = t;
										}

										else {
											Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
											if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
											PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
										}

									}
								
								}

							}
						
							else {
							
								if (SmallestAhead1 == -1) {
								
									if ((P2 == -1) || (Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])] != 0)) {
										Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
										if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
										PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
									}

									else {

										if (-PosY[SmallestAhead2] + (topLeftY(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Width)) >= 2) {

											if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
											PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length);
											PosY[index] = topLeftY(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Width) - 1;

											for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = carLaneIndex; }

											if (topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width) < start) {

												isTilted[index] = true;
												addInLayer(laneCarIndex, lanes, P2, index, PosX);

												int carLaneIndex_temp = -1;

												for (int j = 0; j < 10; j++) {
													if (laneCarIndex[P2][j] == index) {

														carLaneIndex = j;
														break;
													}
												}

												for (int j = t + 1; j < 100; j++) { trafficJam[P2][j] = carLaneIndex_temp; }
											}

										}

										else {
											
											if ((topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length)) == (topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Length))) {
												update = false;
												isTilted[index] = true;

												laneStopPosition[carLaneNumber] = (topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length)) - 2;
												laneStopPosition[P2] = (topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length)) - 2;

												Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2][topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length)] = ColorInside[index];
												Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2][topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length) - 1] = ColorInside[index];
												Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2][topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length) - 2] = ColorInside[index];
												Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2 - 1][topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length) - 1] = ColorInside[index];
												Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2 + 1][topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length) - 1] = ColorInside[index];

												PosX[index] = topLeftX(PosX[SmallestAhead2], PosY[SmallestAhead2], Vehicle, VehicleInside[SmallestAhead2], len, Vehicle_Length) - 1;
												PosY[index] = PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1;

												for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = carLaneIndex; }
												int carLaneNumber_temp = findLaneNumber(SmallestAhead2, laneCarIndex, lanes);
												int carLaneIndex_temp = findLaneIndex(SmallestAhead2, laneCarIndex, lanes);


												for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber_temp][j] = carLaneIndex_temp + 1; }

												Vf[index] = 0;
												A[index] = 0;
												V[index] = 0;
												Start_Time[index] = t;
											}

											else {
												Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
												if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
												PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
											}
										}
									}

								}

								else {
								
									if ((P1 == -1) || (Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])] != 0)) {
										Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
										if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
										PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
									}

									else {

										if (-PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + (topLeftY(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Width)) >= 3) {

											if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
											PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length);
											PosY[index] = PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + (2 - 1);  // Hard coded the width of the rickshaw

											for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = carLaneIndex; }

											if (PosY[index] > end) {

												isTilted[index]= true;
												addInLayer(laneCarIndex, lanes, P1, index, PosX);

												int carLaneIndex_temp = -1;

												for (int j = 0; j < 10; j++) {
													if (laneCarIndex[P1][j] == index) {

														carLaneIndex = j;
														break;
													}
												}

												for (int j = t + 1; j < 100; j++) { trafficJam[P1][j] = carLaneIndex_temp; }
												
											}

										}

										else {
												
											if ((topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length)) == (topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Length))) {
												update = false;
												isTilted[index] = true;

												laneStopPosition[carLaneNumber] = (topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length)) - 2;
												laneStopPosition[P1] = (topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length)) - 2;

												Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2][topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length)] = ColorInside[index];
												Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2][topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length) - 1] = ColorInside[index];
												Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2][topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length) - 2] = ColorInside[index];
												Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2 - 1][topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length) - 1] = ColorInside[index];
												Road[t][PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1 + 2 + 1][topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length) - 1] = ColorInside[index];

												for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = carLaneIndex; }
												int carLaneNumber_temp = findLaneNumber(SmallestAhead1, laneCarIndex, lanes);
												int carLaneIndex_temp = findLaneIndex(SmallestAhead1, laneCarIndex, lanes);

												PosX[index] = topLeftX(PosX[SmallestAhead1], PosY[SmallestAhead1], Vehicle, VehicleInside[SmallestAhead1], len, Vehicle_Length) - 1;
												PosY[index] = PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]] + 1;

												for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber_temp][j] = carLaneIndex_temp + 1; }

												Vf[index] = 0;
												A[index] = 0;
												V[index] = 0;
												Start_Time[index] = t;
											}

											else {
												Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
												if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
												PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
											}

										}

									}

								}
								
							}
							
						}
					}

				

					else if ((neighbour[2] == -1) || (neighbour[2] == 0)) {

						// No constrain

						int changingLane = neighbour[0];
						isOvertaking[index] = true;
						overtakeLayer[index] = changingLane;

						if (carLaneNumber < changingLane) {

							// Goes down now

							LaneChange[index] = atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str());
							PosY[index] = PosY[index] + LaneChange[index];

							if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
							
							if(carLaneIndex !=0){
								Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
						
								PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
							}
							
							else{
								PosX[index] = PosX[index] + 2;
							}

							int laneEnd = changingLane * (Road_Width / lanes);

							if ((topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width)) >= laneEnd) {
								PosY[index] = laneEnd + atoi(Vehicle_Width[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str()) - 1;
								isOvertaking[index] = false;
								LaneChange[index] = 0;
								overtakeLayer[index] = -1;
								addInLayer(laneCarIndex, lanes, changingLane, index, PosX);
								V[index] = 1;
								removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
							}

						}

						else {

							LaneChange[index] = -atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str());
							PosY[index] = PosY[index] + LaneChange[index];

							if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
	
							if(carLaneIndex !=0){
								Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
						
								PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
							}
							
							else{
							
								PosX[index] = PosX[index] +2;
							}

							int laneEnd;

							if (changingLane == lanes - 1) {

								laneEnd = Road_Width - 1;
							}

							else laneEnd = changingLane * (Road_Width / lanes) + (Road_Width / lanes) - 1;


							if (PosY[index] <= laneEnd) {

								PosY[index] = laneEnd;
								isOvertaking[index] = false;
								LaneChange[index] = 0;
								overtakeLayer[index] = -1;
								addInLayer(laneCarIndex, lanes, changingLane, index, PosX);
								V[index] = 1;
								removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
							}



						}


					}



				}


				carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);

				int signalStop;

				if (flag) {

					int tempoCar = findFirstAhead(laneCarIndex, carLaneNumber, PosX, PosY, Vehicle, VehicleInside, len, Vehicle_Length, carLaneIndex, index);

					if (tempoCar == -1) {
						signalStop = Road_Signal_Position - 1;

					}
					else {
						signalStop = topLeftX(PosX[tempoCar], PosY[tempoCar], Vehicle, VehicleInside[tempoCar], len, Vehicle_Length);;
					}

				}

				else signalStop = laneStopPosition[carLaneNumber];

				if(signalStop>Road_Signal_Position) signalStop= Road_Signal_Position;
				

				if (update) {

					int rightBottomX = PosX[index];
					int rightBottomY = PosY[index];

					int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Length);
					int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width);

					if(!already_ahead){
						if (rightBottomX < 0) {}

						else if (leftTopX < Road_Length) {



							if (leftTopX >= signalStop - 1) {

							for (int j = max(0, leftTopX); j <= (min(Road_Length, rightBottomX)); j++) {

								for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {

									Road[t][i][j] = ColorInside[index];

								}
							}

							int zeroLine = min(Road_Length, PosX[index]) + (vehAmount - Road_Length - 1) + 1;
							int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
							int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
							for (int i = zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--) { laneInfo[carLaneNumber][i] = 1; }



						}
	
							else if (rightBottomX >= signalStop - 1) {

							rightBottomX = signalStop - 1;
							PosX[index] = signalStop - 1;
							A[index] = 1;
							leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Length);

							for (int j = max(0, leftTopX); j <= (min(Road_Length, rightBottomX)); j++) {

								for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {

									Road[t][i][j] = ColorInside[index];


								}

							}

							int zeroLine = min(Road_Length, PosX[index]) + (vehAmount - Road_Length - 1) + 1;
							int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
							int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
							for (int i = zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--) { laneInfo[carLaneNumber][i] = 1; }

							laneStopPosition[carLaneNumber] = leftTopX - 1;
							Vf[index] = 0;
							V[index] = 0;
							Start_Time[index] = t;
						}
	
							else {

							for (int j = max(0, leftTopX); j <= (min(Road_Length, rightBottomX)); j++) {

								for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {

									Road[t][i][j] = ColorInside[index];

								}
							}

							int zeroLine = min(Road_Length, PosX[index]) + (vehAmount - Road_Length - 1) + 1;
							int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
							int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
							for (int i = zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--) { laneInfo[carLaneNumber][i] = 1; }



						}

					}

						else {

						ColorInside[index] = ' ';
						int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
						int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);

						removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
						}
					}
					
					else{
						
						for (int j = max(0, leftTopX); j <= (min(Road_Length, rightBottomX)); j++) {

								for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {

									Road[t][i][j] = ColorInside[index];

								}
							}

							int zeroLine = min(Road_Length, PosX[index]) + (vehAmount - Road_Length - 1) + 1;
							int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
							int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
							for (int i = zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--) { laneInfo[carLaneNumber][i] = 1; }

						
					}
				
				}


				return 0;

			}

			else if(!isTilted[index]) {


				int changingLane = overtakeLayer[index];
				int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
				int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);

				int signalStop = laneStopPosition[carLaneNumber];
				
				int SmallestAhead3 = smallestAhead(changingLane, PosX[index], PosX, laneCarIndex);

				if(signalStop>Road_Signal_Position) signalStop= Road_Signal_Position;
				
				if (carLaneNumber < changingLane) {

					// Goes down now

					LaneChange[index] = atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str());
					PosY[index] = PosY[index] + LaneChange[index];

					if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
					
					if(carLaneIndex !=0){				
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
					
						PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
					}
					
					else if((SmallestAhead3 !=-1) && (topLeftX(PosX[SmallestAhead3], PosY[SmallestAhead3], Vehicle, VehicleInside[SmallestAhead3], len, Vehicle_Length) - (PosX[index] + Vf[index])<= 2)){
						
						PosX[index] = topLeftX(PosX[SmallestAhead3], PosY[SmallestAhead3], Vehicle, VehicleInside[SmallestAhead3], len, Vehicle_Length) -2;
						
					}
					
					else{
						PosX[index] = PosX[index] +2;
					}

					int laneEnd = changingLane * (Road_Width / lanes);

					if ((topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width)) >= laneEnd) {


						PosY[index] = laneEnd + atoi(Vehicle_Width[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str()) - 1;

						//							cout << " POs y is " << PosY[index] << endl;

						isOvertaking[index] = false;
						LaneChange[index] = 0;
						overtakeLayer[index] = -1;


						addInLayer(laneCarIndex, lanes, changingLane, index, PosX);
						removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
						V[index] = 1;
					}



				}

				else {

					LaneChange[index] = -atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle, VehicleInside[index], len))].c_str());
					PosY[index] = PosY[index] + LaneChange[index];
					

					if((PosX[index] > Road_Signal_Position) || ((PosX[index] > Road_Signal_Position + 3) && ((VehicleInside[index] == "Cycle") || (VehicleInside[index] == "Bike") || (VehicleInside[index] == "Scooter"))))  already_ahead = true;
	
					if(carLaneIndex!=0){
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex - 1])]; // Retardation effect
					
						PosX[index] = topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex - 1])], len, Vehicle_Length) - 2;
					}

					else if( (SmallestAhead3 !=-1) && (topLeftX(PosX[SmallestAhead3], PosY[SmallestAhead3], Vehicle, VehicleInside[SmallestAhead3], len, Vehicle_Length) - (PosX[index] + Vf[index])<= 2)){
						
						PosX[index] = topLeftX(PosX[SmallestAhead3], PosY[SmallestAhead3], Vehicle, VehicleInside[SmallestAhead3], len, Vehicle_Length) -2;
						
					}	
						
					else{
						PosX[index] = PosX[index] + 2;
					}

					int laneEnd;

					if (changingLane == lanes - 1) {

						laneEnd = Road_Width - 1;
					}

					else laneEnd = changingLane * (Road_Width / lanes) + (Road_Width / lanes) - 1;


					if (PosY[index] <= laneEnd) {
						PosY[index] = laneEnd;
						isOvertaking[index] = false;
						LaneChange[index] = 0;
						overtakeLayer[index] = -1;
						addInLayer(laneCarIndex, lanes, changingLane, index, PosX);
						V[index] = 1;
						removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
					}



				}

//				cout << "Reached here for overtaking: " << ColorInside[index] << endl;

				int rightBottomX = PosX[index];
				int rightBottomY = PosY[index];

				int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Length);
				int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Width);

				if(!already_ahead){

					if (rightBottomX < 0) {}

					else if (leftTopX < Road_Length) {



					if (leftTopX >= signalStop - 1) {

						for (int j = max(0, leftTopX); j <= (min(Road_Length, rightBottomX)); j++) {

							for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {

								Road[t][i][j] = ColorInside[index];
								//		cout << i << " , " << j << " for index " << index << endl;

							}
							//		cout << endl;
						}

						int zeroLine = min(Road_Length, PosX[index]) + (vehAmount - Road_Length - 1) + 1;
						int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
						int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
						for (int i = zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--) { laneInfo[carLaneNumber][i] = 1; }

					}

					else if (rightBottomX >= signalStop - 1) {

						rightBottomX = signalStop - 1;
						PosX[index] = signalStop - 1;
						A[index] = 1;
						leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index], len, Vehicle_Length);

						for (int j = max(0, leftTopX); j <= (min(Road_Length, rightBottomX)); j++) {

							for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {

								Road[t][i][j] = ColorInside[index];
								//		cout << i << " , " << j << " for index " << index << endl;

							}
							//		cout << endl;
						}

						int zeroLine = min(Road_Length, PosX[index]) + (vehAmount - Road_Length - 1) + 1;
						int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
						int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
						for (int i = zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--) { laneInfo[carLaneNumber][i] = 1; }

						laneStopPosition[carLaneNumber] = leftTopX - 1;
						Vf[index] = 0;
						V[index] = 0;
						Start_Time[index] = t;
					}

					else {

						for (int j = max(0, leftTopX); j <= (min(Road_Length, rightBottomX)); j++) {

							for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {

								Road[t][i][j] = ColorInside[index];
								//			cout << i << " , " << j << " for index " << index << endl;

							}
							//		cout << endl;
						}

						int zeroLine = min(Road_Length, PosX[index]) + (vehAmount - Road_Length - 1) + 1;
						int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
						int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
						for (int i = zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--) { laneInfo[carLaneNumber][i] = 1; }



					}

				}

					else {

					ColorInside[index] = ' ';
					int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
					int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);

					removeFromLayer(laneCarIndex, lanes, carLaneNumber, carLaneIndex, index, PosX[index]);
				}

				}
				
				else{
					
					for (int j = max(0, leftTopX); j <= (min(Road_Length, rightBottomX)); j++) {

								for (int i = leftTopY + 2; i <= rightBottomY + 2; i++) {

									Road[t][i][j] = ColorInside[index];

								}
							}

							int zeroLine = min(Road_Length, PosX[index]) + (vehAmount - Road_Length - 1) + 1;
							int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
							int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
							for (int i = zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--) { laneInfo[carLaneNumber][i] = 1; }

					
				}
				
				return 0;

			}

			else {

				int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
				int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);


				if (((VehicleInside[index] != "Cycle") && (VehicleInside[index] != "Scooter") && (VehicleInside[index] != "Bike") && (VehicleInside[index] != "Motor_Rickshaw")) || (PosX[index] < 0))	return -1;  // Error!
				else if (VehicleInside[index] != "Motor_Rickshaw"){
				
					int end, start;

					start = carLaneNumber * (Road_Width / lanes);
					end = start + (Road_Width / lanes) - 1;

					int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
					int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);

					int tempPos = PosX[laneCarIndex[carLaneNumber][carLaneIndex-1]];

					if (((PosY[index] == end) ||  (PosY[index] == start)) && (PosX[index] != tempPos)) {
					
						
						

						if (PosY[index] == start) {
							start_end[index] = 1; 
							Road[t][PosY[index]+2][PosX[index]+1] = ColorInside[index];
							Road[t][PosY[index]+2][PosX[index]] = ColorInside[index];
							Road[t][PosY[index]+2 + 1][PosX[index]] = ColorInside[index];
						}

						else {
							start_end[index] = 0;
							Road[t][PosY[index]+2][PosX[index]+1] = ColorInside[index];
							Road[t][PosY[index]+2][PosX[index]] = ColorInside[index];
							Road[t][PosY[index]+2 - 1][PosX[index]] = ColorInside[index];
							
						}

						PosX[index] = tempPos;
						
					}

					else {
					
						isTilted[index] = false;

						for (int p = PosX[index]; p >= PosX[index] - 2; p--) {
							Road[t][PosY[index]+2][p] = ColorInside[index];
						}
					
						 updateLane(laneCarIndex, carLaneNumber, carLaneIndex);
					}
				
				}
				
				else {
				
					if (presentInMany(laneCarIndex, index, lanes)) {
					
						int carLaneNumber2 = carLaneNumber + 1;
						int carLaneIndex2;

						int z=0;

						for (; z < 10; z++) {
							if (laneCarIndex[carLaneNumber2][z] == index) {
								carLaneIndex2 = z;
								break;
							}
						}

						if (z == 10) return 0;

						if ((carLaneIndex != 0) && (carLaneIndex2 != 0)) {
							if (PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]] > PosX[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]]) {
								
								if ((-(PosY[laneCarIndex[carLaneNumber][carLaneIndex-1]]) + (topLeftY(PosX[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]],PosY[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]] , len, Vehicle_Width)))>=3) {
									PosX[index] = PosX[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]];
									updateLane(laneCarIndex, carLaneNumber2, carLaneIndex2);
									for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber2][j] = carLaneIndex2-1; }
								}


								else {
									PosX[index] = max(topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Length), topLeftX(PosX[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]], PosY[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]], len, Vehicle_Length)) - 1;
									Start_Time[index] = t;
								}
							}

							else {
								
								bool change = true;

								if ((-(PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]]) + (topLeftY(PosX[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]], PosY[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]], len, Vehicle_Width))) >= 3) {

									PosX[index] = PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]];
									 updateLane(laneCarIndex, carLaneNumber, carLaneIndex);
									 for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber][j] = carLaneIndex - 1; }

								}

								else {
									PosX[index] = max(topLeftX(PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]], PosY[laneCarIndex[carLaneNumber][carLaneIndex - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber][carLaneIndex - 1]], len, Vehicle_Length), topLeftX(PosX[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]], PosY[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]], Vehicle, VehicleInside[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]], len, Vehicle_Length)) - 1;
									change = false;
									Start_Time[index] = t;
								}

								if ((PosX[laneCarIndex[carLaneNumber][carLaneIndex - 1]] == PosX[laneCarIndex[carLaneNumber2][carLaneIndex2 - 1]]) && (change)) {
									updateLane(laneCarIndex, carLaneNumber2, carLaneIndex2);
									for (int j = t + 1; j < 100; j++) { trafficJam[carLaneNumber2][j] = carLaneIndex2-1; }
								}
							}
						}

						else {
							// Do nothing						
						}

						for (int a = PosY[index] + 2; a >= PosY[index] + 1; a-- ) {
						
							for (int b = PosX[index]; b >= PosX[index] - 1; b--) {
								
								Road[t][a][b] = ColorInside[index];
							
							}
						
						}

					}

					else {
					
						Start_Time[index] = t;

						
						Road[t][PosY[index] + 2][PosX[index]] = ColorInside[index];
						Road[t][PosY[index] + 2][PosX[index] + 1] = ColorInside[index];
						Road[t][PosY[index] + 2][PosX[index] -1] = ColorInside[index];
						Road[t][PosY[index] + 2 + 1][PosX[index]] = ColorInside[index];
						Road[t][PosY[index] + 2 -1][PosX[index]] = ColorInside[index];
					
					}
				
				}
			}

			return 0;
		}

	}
   
	else {return 0;} 		 
	 
 }


//COMMENT: Updating the Road as per the proper mathematics	
void makeBasicRoad(char*** Road ,int t,int Start_Time,bool RG,int Road_Width,int Road_Length,string* Default){
	//cout<<"red \n";

		if(!RG){ 	//RED
			//cout<<"red \n";
				string str1;
			     str1=std::to_string(t);
				string str2;
			     str2=std::to_string((atoi(Default[3].c_str()) - (t%(atoi(Default[3].c_str())))));
			//		cout << str2 << endl;

				string timeStr;

				timeStr+="TIME ";
				timeStr+=str1;
				timeStr+=" LEFT ";
				timeStr+=str2;
				timeStr+=' ';

				int timeStr_len = timeStr.length();
	
				int Road_Signal_Position = atoi(Default[6].c_str());
	
				for(int i=0; i<timeStr_len; i++){
		
					Road[t][0][i+1] = timeStr[i];
		
					}

				Road[t][0][0] = ' ';
				for(int k=timeStr_len; k< Road_Length; k++){

						Road[t][0][k] = ' ';

				}	
	
			for (int i=1; i<Road_Width + 3 ; i++){
		
		
		
				for(int j=0; j<Road_Length; j++){
			
					if (i==1) Road[t][i][j] = '-';
					else if (i==Road_Width+2) Road[t][i][j] = '-';
					
					else    if((j==Road_Signal_Position) || (j==Road_Signal_Position + atoi(Default[5].c_str()))) Road[t][i][j] = '|';
					else Road[t][i][j] =' '; 
			
				}
		
		
			}
		}
		
		else{
			
			//cout << "green" << endl;

			     string str1;
			     str1=std::to_string(t);
					string str2;				 
					 str2=std::to_string((atoi(Default[3].c_str()) - (t%(atoi(Default[3].c_str())))));
				

				string timeStr;

				timeStr.append("TIME ");
				timeStr.append(str1);
				timeStr.append(" LEFT ");
				timeStr.append(str2);
				timeStr.append(" ");
	
				//cout << timeStr << endl;

				int timeStr_len = timeStr.length();
		//cout << timeStr_len << endl;
				for(int i=0; i<timeStr_len; i++){
		//cout << t<< endl;
					Road[t][0][i+1] = timeStr[i];
					//cout<<i<<endl;
					}
//cout << "yo"<< endl;
						Road[t][0][0] = ' ';
				for(int k=timeStr_len; k< Road_Length; k++){

						Road[t][0][k] = ' ';

				}	
	


							int Road_Signal_Position = atoi(Default[6].c_str());

				//cout << Road_Signal_Position << endl;
			for (int i=1; i<Road_Width + 3 ; i++){
		
				//cout << i << endl;
		
				for(int j=0; j<Road_Length; j++){

				//	cout << j << endl;
			
					if (i==1) Road[t][i][j] = '-';
			

					else if (i==Road_Width+2) Road[t][i][j] = '-';
					else Road[t][i][j] =' '; 
			
				}
		
		
			}
			
			
		}
	
	
	
}




int findLane(int** laneInfo, int lanes, int vehAmount, int Road_Length){
	
	int ZeroLine = vehAmount - Road_Length - 1; 
	
	int randomLane = rand()%lanes ;
	
	int tempLane = randomLane;
	
	int counter = 1;
	
	while(laneInfo[tempLane][ZeroLine] != 0){
		
		
		
		tempLane = tempLane + 1;
		counter = counter + 1;
		
		if(tempLane == lanes) tempLane=0;
		
		
		if(counter == lanes) {
			
			ZeroLine = ZeroLine -1;
			counter = 1;
			tempLane = randomLane;
		}
		//cout<<"zeroline "<<ZeroLine<<endl;
		if(ZeroLine<0) {cout << "Too many vehicles initiated at once! Please change the configuration file 1"; return -1;}
		
		
	}
	
	return tempLane;
	
}

int findZeroLine(int** laneInfo, int lanes, int vehAmount, int Road_Length)
{
	int ZeroLine = vehAmount - Road_Length - 1; 
	
	
	int randomLane = rand()%lanes ;
	
	int tempLane = randomLane;
	
	int counter = 1;
	
	while(laneInfo[tempLane][ZeroLine] != 0){
		
		
		
		tempLane = tempLane + 1;
		counter = counter + 1;
		
		if(tempLane == lanes) tempLane=0;
		
		
		if(counter == lanes) {
			
			ZeroLine = ZeroLine -1;
			counter = 1;
			tempLane = randomLane;
		}
		//cout<<"zeroline2 "<<ZeroLine<<endl;
		if(ZeroLine<0) {cout << "Too many vehicles initiated at once! Please change the configuration file 2"; return -1;}
		
		
	}
	
	return ZeroLine;
	
	
}


int findEmptyIndex(int randomLane, int** laneCarIndex){
	
	int ans=0;
	while((laneCarIndex[randomLane][ans]!=0) && (ans<10)){ans++; }
	
	if(ans==10) cout << "Too many Vehicles are there in the same lane. OVERLOAD! "<<ans<<endl;
	
	return ans;
}
	
int findRandomInLane(int randomLane, int lanes, char*** Road, int Road_Width, int PosX,  string* Vehicle, string VehicleInside, int len, string* Vehicle_Width){
	
	if(randomLane==lanes-1) {
		
		int end = Road_Width - 1;
		int start = randomLane* (Road_Width/lanes);

		return end;
		
	}
	
	else{
		
		int start = randomLane * (Road_Width/lanes);
		int end = start + (Road_Width/lanes) -1;
		
		return end;
		
	}
	
	
}
	
	
	
int Initiate (int index, char*** Road, char* ColorInside, string* VehicleInside, int layer, int** laneInfo, int lanes, int vehAmount, int* PosX, int* PosY, int Road_Width, int Road_Length, int len, string* Vehicle,int* Vel, int* Vf,int* Acc, int* Retard, int* LaneChange, int** laneCarIndex, string* Vehicle_MaxSpeed, string* Vehicle_Acceleration,string* Vehicle_Break,string* Vehicle_LaneChange, string* Vehicle_Length, string* Vehicle_Width,int flag){

  if(strcmp("Human", VehicleInside[index].c_str()) != 0)		// NOT a human
	{	
 		int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		
		int randomLane = findLane(laneInfo,lanes,vehAmount, Road_Length);
		int zeroLine = findZeroLine(laneInfo, lanes, vehAmount, Road_Length);
		
		if(randomLane == -1) return -1;
		//cout<<"61\n";
		//cout<<"61 "<<(atoi(Vehicle_MaxSpeed[VehIndex].c_str()))<<endl;
		int RandomlyGenVel = (rand() % (atoi(Vehicle_MaxSpeed[VehIndex].c_str()))) + 1;
		int RandomlyGenAcc = (rand() % (atoi(Vehicle_Acceleration[VehIndex].c_str()))) + 1;
		int RandomlyGenLC = (rand() % (atoi(Vehicle_LaneChange[VehIndex].c_str()))) + 1;			//lane change
		int RandomlyGenRet = (rand() % (atoi(Vehicle_Break[VehIndex].c_str()))) + 1;
		
		if(flag==1)
		{Vel[index] = RandomlyGenVel;
		Acc[index] = RandomlyGenAcc;}
		else {Vel[index] = 0;
		Acc[index] = 0;}

		Retard[index] = RandomlyGenRet;
		LaneChange[index] = RandomlyGenLC;
		Vf[index] = RandomlyGenVel;
		//cout<<"62 \n";
		for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[randomLane][i] = 1;}	//Occupied
		//cout<<"6s \n";
		if(flag==1)
		{	PosX[index] = zeroLine - (vehAmount - Road_Length - 1) -1;}
		PosY[index] = findRandomInLane(randomLane, lanes, Road, Road_Width, PosX[index], Vehicle, VehicleInside[index], len, Vehicle_Width);
//		cout<<"65s \n";
	    int emptyIndex = findEmptyIndex(randomLane, laneCarIndex);
		
		if (emptyIndex==10) return -1;
		//cout<<"63 \n";
		laneCarIndex[randomLane][emptyIndex] = index;
		
    	return zeroLine;
		
	}
	
   else{
	   
	   // TO DO: Humans
	   
   }
}



	
	
// COMMENT: Just to see if there's nothing on the road or not
	
bool isEmpty(char*** Road, int length, int width, int time){
		
			
		
		for(int i=0; i<length; i++){
			
			for(int j=2; j<width+1; j++){
				
				if(Road[time][j][i]!=' ') return false;
			}
			
		}
		
		return true;
	}

// COMMENT: To print the contents of the road as per the time scale. While checking the code, please add a timestep for this after the END.
	
void printArray (char*** Road, int Road_Length, int Road_Width, int t){
		
		for(int i=0; i<Road_Width + 3; i++){
			
			for(int j=0; j< Road_Length;j++){
				
				cout << Road[t][i][j];
				
			}
			
			cout << '\n';
			
		}
		
		
	}


void simulation(int& n, int& Total_Time, int& vehicles_on_road, int PosX[100][500], int PosY[100][500], int carInd[100][500], string Vehicle_Length[50], string Vehicle_Width[50], int& runningTime, int& road_length,int& road_width, int& road_zebra_width, int& road_signal_position, int signal[100], bool  isTilted[100][500],int start_end[100][500],int is_rickshaw[500])
{
	string Default[11]; 
    // string Road_Id;0
    // string Road_Length;1
    // string Road_Width;  2
    // string Road_Signal;3
    // string Road_Yellow;4
    // string Road_Zebra_Width; 5
    // string Road_Signal_Position;6
    // string Default_LaneChange;7
    // string Default_Acceleration;8
    // string Total_Time;9
    // string Total_Vehicles_on_road;10 .
    
    int count =0;
	//cout<<"1"<<endl;
	// COMMENT: Variables for the code
	
	bool justAfterStart = false; 	//COMMENT
	bool RG = false;		//COMMENT: false for Red and true for Green
	int Start_Time = 0; //COMMENT

	int t = 0;		//COMMENT

	
	
	ifstream inFile;
	inFile.open("otherConfig.txt");

//cout<<"114"<<endl;
//cout<<"111"<<endl;
	
	if (!inFile.is_open()) 
	{
		cout<<"file doesn't open 1"<<endl;
		return  ;
	}
//cout<<"7 \n";
	int value;
	string word;
	//this loop reads all the default values
	while((inFile >> word) && count<11)
	{
		while(word[0] == '#') //always define a comment between 2 #
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}

		
		inFile>>word;
		if(word=="=")
		{
			inFile>>word;
			Default[count] = word;
		//cout<<word<<endl;
			count++;
		}
	}

//cout<<"ss \n";
	//COMMENT - Instead of total vehicles as part of default I have read it separately as NumbVehicles
	//read the number of types of vehicles to be used 
	//int n=0;
		//cout<<"hi1 \n";
	//inFile>>word;
	Total_Time = atoi(Default[9].c_str());

	//cout<<Total_Time<<"yo"<<endl;
	//return;
	while(word[0] == '#')
	{
		inFile>>word;
		while(word!="#")
			inFile>>word;
		inFile>>word;
	}
			//cout<<"hi2 \n";

	//cout<<"hi \n";
	inFile>>word;
	//cout<<word<<endl;
	inFile>>n;
	
	// ERROR: Correct this........ Anyways it's a better generic form to use 'n' for the number of type of Vehicles available. But I also need the total Number of Vehicles as I stated in the whatsapp chat. So add one accordingly.

   // COMMENT I m changing the value of n to fit the given problem
	n=9;

//cout<<"2"<<endl;
	
	string Vehicle[n];
    //string Vehicle_Length[n];
    //string Vehicle_Width[n];
    string Vehicle_MaxSpeed[n];
    string Vehicle_Acceleration[n];
    string Vehicle_Break[n];
    string Vehicle_LaneChange[n];

    count=0;
    string word1, word2;

    //loop to read all the n types of vehicles
    while((inFile >> word) && count<n)
	{
		//cout<<word<<endl;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}

		if(word == "Vehicle_Type")
		{
			inFile>>word;
				if(word=="=")
				{
					inFile>>word;
					Vehicle[count] = word;
		//cout<<word<<endl;
				}
		}
		else {cout<<"Error in defining vehicles \n"; return;}

		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		
		//cout<<word1<<endl;
		inFile>>word2;
		if(word1=="Vehicle_Length" && word2=="=")
		{
			inFile>>word;
			Vehicle_Length[count] = word;
		

		//cout<<"Vehicle_Length "<<word<<endl;
		}
		else {cout<<"Error in defining vehicles "<<count<<endl; return;}

		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		inFile>>word2;
		if(word1=="Vehicle_Width" && word2=="=")
		{
			inFile>>word;
			Vehicle_Width[count] = word;
		//cout<<"Vehicle_Width "<<word<<endl;
		}
		else {cout<<"Error in defining vehicles "<<count<<endl; return;}

		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		inFile>>word2;
		if(word1=="Vehicle_MaxSpeed" && word2=="=")
		{
			inFile>>word;
			Vehicle_MaxSpeed[count] = word;
		//	cout<<"Vehicle_MaxSpeed "<<word<<endl;

		}
		else {cout<<"Error in defining vehicles "<<count<<endl; return;}

		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		inFile>>word2;
		if(word1=="Vehicle_Acceleration" && word2=="=")
		{
			inFile>>word;
			Vehicle_Acceleration[count] = word;
			//	cout<<"Vehicle_Acceleration "<<word<<endl;

		}
		else {cout<<"Error in defining vehicles "<<count<<endl; return;}
	
		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		inFile>>word2;
		if(word1=="Vehicle_Break" && word2=="=")
		{
			inFile>>word;
			Vehicle_Break[count] = word;
				//	cout<<"Vehicle_Break "<<word<<endl;

		}
		else {cout<<"Error in defining vehicles "<<count<<endl; return;}

		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		inFile>>word2;
		if(word1=="Vehicle_LaneChange" && word2=="=")
		{
			inFile>>word;
			Vehicle_LaneChange[count] = word;
	//	cout<<"Vehicle_LaneChange "<<word<<endl;
		}
		else {cout<<"Error in defining vehicles  "<<count<<endl; return;}

		count++;
	}

	//now the next token should be START
	//inFile>>word;
	while(word[0] == '#')
	{
		inFile>>word;
		while(word!="#")
			inFile>>word;
		inFile>>word;
	}
	if(word!="START")
	{
		cout<<"START expected "<<endl; return;
	}

		ofstream myfile;
		  myfile.open ("opengl.txt");
		  myfile<<"Vehicle_Length \n";
		    for(int i=0; i<n; i++)
  				myfile << atoi(Vehicle_Length[i].c_str())<<endl;;
		  
		  myfile<<"Vehicle_Width \n";
		    for(int i=0; i<n; i++)
  				myfile << atoi(Vehicle_Width[i].c_str())<<endl;;
    // COMMENT: "Start" code...
	
     int Road_Length = atoi(Default[1].c_str());
	int Road_Width = atoi(Default[2].c_str());
	//int Total_Time = atoi(Default[9].c_str());
	
	int Road_Signal_Position = atoi(Default[6].c_str());
	
   if(Road_Signal_Position > Road_Length)  {cout<< "Representational ERROR. Please change the width, length, or the Duration"; return; } 
	
	
	//cout<<"3"<<endl;
	
	// COMMENT: Defining the default road: FOR RED LIGHT
	
	char ***Road;
	//cout<<"total time "<<Total_Time<<endl;
	Road = (char***)malloc(sizeof(char**)*Total_Time);
	for(int i =0; i<Total_Time; i++)
	{
		Road[i] = (char**)malloc(sizeof(char*)*Road_Length);
	}

	for(int i =0; i<Total_Time; i++)
	{
		for(int j =0; j<Road_Length; j++)
			Road[i][j] = (char*)malloc(sizeof(char)*(Road_Width+3));
	}


	
	// COMMENT : Something like this
	
	
	// TIME 5 LEFT 25
	//----------------
	//         |   |  
	//         |   |
	//         |   |
	//----------------

				string str1;
   
			    str1=std::to_string((atoi(Default[9].c_str())));
				 
				string str2;
			     str2=std::to_string((atoi(Default[3].c_str())));
						

				string timeStr;

				timeStr.append("TIME ");
				timeStr.append(str1);
				timeStr.append(" LEFT ");
				timeStr.append(str2);
				timeStr.append(" ");

			//	cout << timeStr << "||||||||||||||||||||||||||||||||||||||||||| \n";
		//		cout << Default[1] << '\n';

/////////////////////////////////////////////////////////////////////				////////////////////////////////////////////////////////////////////////////
  

	if(timeStr.length() > Road_Length) { cout << "Representational ERROR. Please change the width, length, or the Duration";  return; }
	
    
    	 justAfterStart = true;
		//cout<<"7 \n";												  	//The vehicles inside the Road
	 // cout<<(atoi(Default[10].c_str())+1);
	  char *ColorInside;
	  ColorInside = (char*)malloc(sizeof(char)*(atoi(Default[10].c_str())+1));
	  int Colorsize = atoi(Default[10].c_str())+1;
	
		for(int i=0; i<Colorsize; i++){
			ColorInside[i] = ' ';
		}
	  
	  bool isOvertaking[atoi(Default[10].c_str())+1];	//For the Overtaking state

		for(int i=0; i<Colorsize; i++){
			isOvertaking[i] = false;
		}
	
	int shreya = atoi(Default[10].c_str())+1;
	  int PositX[atoi(Default[10].c_str())+1];  //Bottom right corner of the Vehicle
	  for(int i=0; i<shreya; i++)
	  	PositX[i] = -1000;
	  int PositY[atoi(Default[10].c_str())+1];  //Bottom right corner of the Vehicle
	  	for(int i=0; i<shreya; i++)
	  	PositY[i] = -1000;
      int Vel[atoi(Default[10].c_str())+1];
	  int Vf[atoi(Default[10].c_str())+1];
	  


	  int overtakeLayer[atoi(Default[10].c_str())+1];
  
	  for(int i=0; i<Colorsize; i++){
		  overtakeLayer[i] = -1;
	  }
	  
	  int *Acc;
	  Acc = (int*)malloc(sizeof(int)*(atoi(Default[10].c_str())+1));
	  int *Retard;
	  Retard = (int*)malloc(sizeof(int)*(atoi(Default[10].c_str())+1));
	  int *LaneChange;
	  LaneChange= (int*)malloc(sizeof(int)*(atoi(Default[10].c_str())+1));

	  

	 // bool* isTilted;
	  //isTilted = (bool*)malloc(sizeof(bool)*(atoi(Default[10].c_str()) + 1));
	for(int t=0; t<100; t++){
		for (int i = 0; i < Colorsize; i++) {
		  isTilted[t][i] = false;
	  }
	}

	  for(int i=0; i<Colorsize; i++){
			LaneChange[i] = 0;
		}
	  
	  
	  string VehicleInside[atoi(Default[10].c_str()) + 1];
	  
	  for(int i=0; i< Colorsize; i++){

	  		VehicleInside[i] = " ";

	  }

//cout<<"4"<<endl;
	
	  int carIndex=1;
	  
	  // For the lane system
	  
	  int lanes = (Road_Width%4 == 0)? (Road_Width/4) : -1;
	  
	  if (lanes == -1) {
	  
		  cout << "Road Width not divisble by 4" << endl;
		  return;
	  
	  }

	  int vehAmount = floor(1.5 * Road_Length);
	 
	  int **laneInfo;
	  laneInfo = (int**)malloc(sizeof(int*)*lanes);
	  for(int i=0 ; i<lanes; i++)
	  {
	  	laneInfo[i] = (int*)malloc(sizeof(int)*(vehAmount+1));
	  }
	  
	  for(int i =0; i < lanes; i++){
		  for(int j =0; j< vehAmount+1; j++){
			  laneInfo[i][j] = 0;
		  }
	  }
	  
	 
	  int **laneCarIndex;  // assuming that only 10 cars at max in a lane.
	  laneCarIndex= (int**)malloc(sizeof(int*)*lanes);

	  for(int i=0;i<lanes; i++)
	  {
	  	laneCarIndex[i] = (int*)malloc(sizeof(int)*10);
	  }
	  for(int i =0; i < lanes; i++){
		  for(int j =0; j< 10; j++){
			  laneCarIndex[i][j] = 0;
		  }
	  }

	  /*int **trafficJam;
	  trafficJam = (int**)malloc(sizeof(int*)*lanes);
	  for (int i = 0; i<lanes; i++)
	  {
		  trafficJam[i] = (int*)malloc(sizeof(int) * 100);
	  }*/
	int trafficJam[lanes][100];
	
	  for (int i = 0; i < lanes; i++) {
		  for (int j = 0; j< 100; j++) {
			  trafficJam[i][j] = 1000;
		  }
	  }

	  int laneStopPosition[lanes];
	  int flag=0;
      for(int i=0; i<lanes; i++){
		  
		  laneStopPosition[i] = atoi(Default[6].c_str());
		  //cout << laneStopPosition[i] <<
	  }	  
	   
	 
     //next token should define signal state
	inFile>>word;
	while(word[0] == '#')
	{
		inFile>>word;
		while(word!="#")
			inFile>>word;
		inFile>>word;
	}

	while(word != "Signal")
	{
	
		VehicleInside[carIndex] = word;
		if(word=="Motor_Rickshaw") is_rickshaw[carIndex] = 1;
				else is_rickshaw[carIndex] =0;	
		inFile>>word;
		ColorInside[carIndex] = word[0];
		//cout<<"66 \n";
		inFile>>word;
		PositX[carIndex] = atoi(Default[6].c_str())-2;
		//cout<<"66 \n";
	//	cout << " Car index is " << carIndex << endl;
		int layer= Initiate(carIndex, Road, ColorInside, VehicleInside, layer, laneInfo, lanes, vehAmount, PositX, PositY, Road_Width, Road_Length,n, Vehicle,  Vel,Vf, Acc, Retard, LaneChange, laneCarIndex, Vehicle_MaxSpeed, Vehicle_Acceleration, Vehicle_Break, Vehicle_LaneChange, Vehicle_Length, Vehicle_Width,flag);
		/*cout<<"posx "<<PositX[carIndex]<<endl;
		cout<<"posy "<<PositY[carIndex]<<endl;*/
		
		carIndex++;			
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
	}

	if(word!="Signal")
	{
		cout<<"Signal expected "<<endl; return;
	}
	inFile>>word; 
	//cout<<word;
	 flag =1;
	if(word!="GREEN" && word!="RED")
		{
		cout<<"wrong signal "<<endl; return;
	}
	string signal_state = word;
	int int_Start_Time;
	inFile>>word;
	while(word[0] == '#')
	{
		inFile>>word;
		while(word!="#")
			inFile>>word;
		inFile>>word;
	}
	if(word =="Start_Time")
	{
		inFile>>word;
		inFile>>value;
		int_Start_Time = value;
	}
	else int_Start_Time = 0;
//cout<<int_Start_Time<<endl;

	// For storing the start time
	  int startTime[atoi(Default[10].c_str())+1];
	  
	  for(int i=0; i<Colorsize; i++){
			startTime[i] = int_Start_Time;
		}
	
		t = int_Start_Time;
    // COMMENT: CODE initialization for RED and GREEN... 
   
    if(signal_state=="RED"){
		
		 RG = false;
	}
   
    else{
		RG = true;
	}
   
	
	inFile>>word;
	while(word != "END")
	{
		//i++;
		while(word!="Pass" && word!="END")
		{
			while(word[0] == '#')
				{
					inFile>>word;
					while(word[word.length()-1]!='#')
						inFile>>word;
					inFile>>word;
				}
			//c[count][i][0] = word;  //stores the type of vehicle
			
			if(carIndex > atoi(Default[10].c_str())){ cout<< "Improper value of maximum number of cars inside. Please check the configuration file"; return;}
			
			else{
			VehicleInside[carIndex] =  word;  //COMMENT
				if(word=="Motor_Rickshaw") is_rickshaw[carIndex] = 1;
				else is_rickshaw[carIndex] =0;
			
			//cout<<word<<" "<<carIndex<<endl;
			inFile>>word;
			
			//c[count][i][1] = word;  //stores the colour of it
		
		     ColorInside[carIndex] = word[0];   //COMMENT: Add the first character of 'word' instead of 'G'
			//	cout<<ColorInside[carIndex] <<endl;;
		      // call
				//cout<<carIndex<<endl;;
				startTime[carIndex] = t;
		     int layer= Initiate(carIndex, Road, ColorInside, VehicleInside, layer, laneInfo, lanes, vehAmount, PositX, PositY, Road_Width, Road_Length,n, Vehicle,  Vel,Vf, Acc, Retard, LaneChange, laneCarIndex, Vehicle_MaxSpeed, Vehicle_Acceleration, Vehicle_Break, Vehicle_LaneChange, Vehicle_Length, Vehicle_Width,flag);
		/*	  cout<<"posx "<<PositX[carIndex]<<endl;
		cout<<"posy "<<PositY[carIndex]<<endl;
		*/

		     	//cout << PositX[carIndex ] << endl;

			   if(layer==-1) {return;}
			  
			   carIndex++;
			
		//	i++;
			inFile>>word;
			while(word[0] == '#')
				{
					inFile>>word;
					while(word[word.length()-1]!='#')
						inFile>>word;
					inFile>>word;
				}
			//cout<<"word "<<word<<endl;
			}
		
		
		}

		  
		if(word!="END")	//PASS reached
			{inFile>>value;
			//cout<<value<<endl;
				int tempCheck;

			int passingTime;
			passingTime = value;
			
			//cout<<value<<endl;
			for(int i=0; i<passingTime;i++){
			
	        makeBasicRoad(Road,t, int_Start_Time, RG, Road_Width, Road_Length,Default);
			
               // cout << "time is " << t << endl;
				for(int p=0; p< lanes; p++){
					
					for(int j=0; j<10; j++){
					
					  if (laneCarIndex[p][j] == 0) break;
					
					 int temp = -1;
					
				 	if(j<9) temp = laneCarIndex[p][j+1];
				
					if (VehicleInside[laneCarIndex[p][j]] == " ") break;		
				    
					tempCheck = positionUpdate(laneCarIndex[p][j],Vel,Vf, Acc,Retard,LaneChange,Road,t, startTime,PositX, PositY , ColorInside, VehicleInside, RG,laneCarIndex, laneInfo, lanes, Road_Length, Road_Width, Vehicle, Vehicle_Length, Vehicle_Width, n, isOvertaking, Vehicle_LaneChange, overtakeLayer, vehAmount, Default, laneStopPosition, isTilted[t-int_Start_Time+1], trafficJam, start_end[t-int_Start_Time+1]);
					if(tempCheck==-1) { return; }
					/*PosX[t][carIndex] = PositX[carIndex];
						cout<<"PositX "<<PositX[laneCarIndex[p][j]];
						PosY[t][carIndex] = PositY[carIndex];
												cout<<"PositY "<<PosY[t][carIndex];
*/
					 if((j<9) && (laneCarIndex[p][j] == temp)) j= j-1;
					
					}
				}
				
		
				for(int a=0; a<lanes; a++){
				//cout << "Lane Number: " << a << " "; 
					for(int b=0; b<10; b++){
						//cout   << " " << ColorInside[laneCarIndex[a][b]];
					}
					cout << '\n';
				}
				
                 printArray(Road, Road_Length, Road_Width, t);
					cout << '\n';

						std::this_thread::sleep_for(std::chrono::milliseconds(500));
				for(int i=1; i<shreya; i++)
				{
				//	cout<<"int_Start_Time "<<int_Start_Time<<endl;
					PosX[t-int_Start_Time][i] = PositX[i];
					PosY[t-int_Start_Time][i] = PositY[i];
				//	cout<<"i= "<<i<<" time "<<t-int_Start_Time<<" x= "<< PositX[i] <<" y= "<<PositY[i]<<endl;
						
					carInd[t-int_Start_Time][i] = findIndexOfStr(Vehicle, VehicleInside[i],n);
				}
				 signal[t-int_Start_Time] = RG;
				
				/*		for(int i=1; i<shreya+1; i++)
							{
								PosX[t-int_Start_Time][i]= PositX[i];
								cout<<"pX"<<PosX[t-int_Start_Time][i]<<endl;
							}
							for(int i=1; i<shreya+1; i++)
							{
								
								PosY[t-int_Start_Time][i]= PositY[i];
							}
							
							for(int i=1; i<shreya; i++)
							{
								carInd[t-int_Start_Time][i] = findIndexOfStr(Vehicle, VehicleInside[i],n);
							
								cout<<i<<endl;
							}
							// if(signal_state == "RED")
							// signal[t-int_Start_Time] = 0;
							 signal[t-int_Start_Time] = RG;
				
					 */
//cout<<"77"<<endl;
	
				t=t+1;
				
				if(t%(atoi(Default[3].c_str()))==0) RG = !RG;
				//cout<<RG<<endl;
				if(t>=Total_Time) {cout<< "Improper timings!" <<'\n'; return;}
				
			}
		
			if(word=="END") break;
			inFile>>word;
			//cout<<word<<endl;
		}
		runningTime = t-int_Start_Time-1;
	}

  // COMMENT: Terminated while loop. SO EOF reached.
		//xRG=true;
		if(RG){				//COMMENT: The signal is green when stopped and so all the vehicles must be allowed to clear the road OR until there's a RED light

							int tempCheck;

			// call
//cout<<"hi \n";
				while((!isEmpty(Road,Road_Length,Road_Width, t)) &&  (RG)){
					
						// call
	                        makeBasicRoad(Road,t, int_Start_Time, RG, Road_Width, Road_Length, Default);

					
					 		for(int p=0; p< lanes; p++){
					
								for(int j=0; j<10; j++){
								
									if (laneCarIndex[p][j]==0) break;
									
									 int temp = -1;
									
									 if (j<9) temp = laneCarIndex[p][j+1];
									
									 if (VehicleInside[laneCarIndex[p][j]] == " ") break;
									
									tempCheck = positionUpdate(laneCarIndex[p][j],Vel,Vf, Acc,Retard,LaneChange,Road,t, startTime,PositX, PositY , ColorInside, VehicleInside, RG,laneCarIndex, laneInfo, lanes, Road_Length, Road_Width, Vehicle, Vehicle_Length, Vehicle_Width, n, isOvertaking, Vehicle_LaneChange, overtakeLayer, vehAmount, Default, laneStopPosition, isTilted[t-int_Start_Time+1], trafficJam, start_end[t-int_Start_Time+1]);
									if(tempCheck==-1) return;
				/*	PosX[t][carIndex] = PositX[carIndex];
						cout<<"PositX "<<PosX[t][carIndex];
						PosY[t][carIndex] = PositY[carIndex];
												cout<<"PositY "<<PosY[t][carIndex]; */
									 if((j<9) && (laneCarIndex[p][j] == temp)) j= j-1;
								}
							}
				
							 printArray(Road, Road_Length, Road_Width, t);
							cout << '\n';
					
						for(int a=0; a<lanes; a++){
				
						//	cout << "Lane Number: " << a ; 
					for(int b=0; b<10; b++){
						//cout  << ColorInside[laneCarIndex[a][b]];
					}
					cout << '\n';
				}
			
					for(int i=1; i<shreya; i++)
						{
							//cout<<"int_Start_Time "<<int_Start_Time<<endl;
							PosX[t-int_Start_Time][i] = PositX[i];
							PosY[t-int_Start_Time][i] = PositY[i];
					//	cout<<"i= "<<i<<" time "<<t-int_Start_Time<<" x= "<< PositX[i] <<" y= "<<PositY[i]<<endl;
							//	cout<<"positY "<<PositY[i];
							carInd[t-int_Start_Time][i] = findIndexOfStr(Vehicle, VehicleInside[i],n);
						}
						 signal[t-int_Start_Time] = RG;
				
							
							std::this_thread::sleep_for(std::chrono::milliseconds(500));
							
							
					/*	
							for(int i=1; i<shreya+1; i++)
							{
								
								PosX[t-int_Start_Time][i]= PositX[i];
							}
							for(int i=1; i<shreya+1; i++)
							{
								PosY[t-int_Start_Time][i]= PositY[i];
							}
						
							for(int i=1; i<shreya+1; i++)
							{
								carInd[t-int_Start_Time][i] = findIndexOfStr(Vehicle, VehicleInside[i],n);
						
							}
							// if(signal_state == "RED")
							// signal[t-int_Start_Time] = 0;
							signal[t-int_Start_Time] = RG;
							
					*/

							t=t+1;
				
							if(t%(atoi(Default[3].c_str()))==0) RG = !RG;
		
							if(t>=Total_Time) {cout<< "Improper timings!" <<'\n'; return;}
					
				}
				
			myfile.close();
			runningTime = t-int_Start_Time-1;
		}
		
		//cout << "END";
		road_length = atoi(Default[1].c_str());
		road_width = atoi(Default[2].c_str());
		road_zebra_width = atoi(Default[5].c_str());

road_signal_position = atoi(Default[6].c_str());
n = shreya;
signal = 0;
    return;

}

