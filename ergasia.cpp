#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "List.h"
using namespace std;

class POI {
private:
	int id;
	double x, y;
	int d;
	int s;
	int open[6];
	int close[6];

public:
	

	 void POIinitilize(int vn,double xcoord,double ycoord,int dur,int score, int opent[], int closet[]){
		this->id = vn;
		this->x = xcoord;
		this->y = ycoord;
		this->d = dur;
		this->s = score;
		for (int i = 0; i < 6; i++){
			this->open[i] = opent[i];
			this->close[i] = closet[i];
		}
	}
	double getCoordinates(char d){
		if(d == 'x'){
			return this->x;
		}
		else{
			return this->y;
		}
	}
	int getDuration() {
		return this->d;
	}
	int getScore() {
		return this->s;
	}
	int getOpenTime(int day){
		for(int j=0;j<6;j++){
			if(day==j){
				return this->open[j];
			}
		}
	}
	int getCloseTime(int day){
		for(int j=0;j<6;j++){
			if(day==j){
				return this->close[j];
			}
		}
	}
	int getId(){
		return this->id;
	}



	POI() { }
	//hotel constructor
	 POI(int vn,double xcoord,double ycoord, int opent, int closet){
		id = vn;
		x = xcoord;
		y = ycoord;
		for (int i = 0; i < 6; i++){
			open[i] = opent;
			close[i] = closet;
		}
	}

};

std::ostream& operator<<(std::ostream& os, POI& p)
{
	os<<"\nId: "<<p.getId()<<" Score: "<<p.getScore()<<endl;
	return os;
}

double calculateDistance(POI start, POI end){
	double distance;
	double endx = end.getCoordinates('x');
	double endy = end.getCoordinates('y');
	double startx = start.getCoordinates('x');
	double starty = start.getCoordinates('y');
	distance = pow((endx-startx),2)+pow((endy - starty),2);
	return sqrt(distance);
}

int compare_ofs(double of1, double of2){
	if(of1 > of2) return 1;
	else if(of1<of2) return -1;
}



double calculateOf(POI start, POI end, POI between){
	double of = pow(between.getScore(),2)/(calculateDistance(start,between)+between.getDuration()+calculateDistance(between,end)-calculateDistance(start,end));
	return of;
}


int main() {
	ifstream inFile;
	int K, M, SD, N, id;
	double x, y;
	int d, s, open, close;
	int opena[7];
	int closea[7];
	string NWLN = "\n";
	string garbagecan;

	inFile.open("t101.txt");

	inFile >> K >> M >> SD >> N;
	inFile.ignore(256,'\n');
	inFile >> id >> x >> y >> d >> s >> open >> close;
	POI * hotel = new POI(id, x, y, open, close);
	POI pois[N+1];
	List<POI> listapoi;
	
	
	int counter = 0;
	while(!inFile.eof()){
		inFile >> id >> x >> y >> d >> s;
		inFile >> garbagecan;
		for(int i = 0; i<7; i++){
			inFile >> open;
			opena[i] = open;
			inFile >> close;
			closea[i] = close;
		}
		pois[id].POIinitilize(id,x,y,d,s,opena,closea);
		inFile.ignore(256,'\n');
		counter++;
	}


	inFile.close();
	
	listapoi.insertStart(pois[1]);
	listapoi.insertPos(pois[2],1);
	listapoi.insertPos(pois[3],2);
	listapoi.print();
	
	cout << "----------------" <<endl;
	cout<< pois[3] << endl;
	cout << K << endl;
	cout << M << endl;
	cout << SD << endl;
	cout << N << endl;
	cout << x << endl;
	cout << y << endl;
	cout << open << endl;
	cout << close << endl;
	cout << "A POI RE!!!"<<endl;
	cout << pois[3].getCoordinates('x')<<" "<<pois[3].getCoordinates('y')<<endl;
	cout << pois[3].getDuration()<<endl;
	cout << pois[3].getScore()<<endl;
	cout << calculateOf(pois[3],pois[1],pois[2])<<endl;
	cout << calculateDistance(*hotel,pois[2])<<endl;


	delete hotel;
	return 0;


}
