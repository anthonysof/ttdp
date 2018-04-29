#include <iostream>
using namespace std;
#pragma once

class POI {
private:
	int id;
	double x, y;
	int d;
	int s;
	int open[7];
	int close[7];

public:
	
	 void POIinitilize(int vn,double xcoord,double ycoord,int dur,int score, int opent[], int closet[]){
		this->id = vn;
		this->x = xcoord;
		this->y = ycoord;
		this->d = dur;
		this->s = score;
		for (int i = 0; i < 7; i++){
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
		for(int j=0;j<7;j++){
			if(day==j){
				return this->open[j];
			}
		}
	}
	int getCloseTime(int day){
		for(int j=0;j<7;j++){
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
		for (int i = 0; i < 7; i++){
			open[i] = opent;
			close[i] = closet;
		}
	}
	bool operator==(const POI& rhs) const
{
	return id == rhs.id;
}
	bool operator!=(const POI& rhs) const
{
	return id != rhs.id;
}
};
