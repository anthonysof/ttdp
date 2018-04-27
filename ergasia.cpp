#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <iterator>  //to remove
#include <algorithm>	//to remove
#include "List.h"
#include <vector>
using namespace std;

class POI {
private:
	int id;
	double x, y;
	int d;
	int s;
	int open[7];
	int close[7];
	bool selected;

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
		selected = false;
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

	void selectPoi(){
		selected = true;
	}
	bool getSelected(){
		return selected;
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


std::ostream& operator<<(std::ostream& os, POI& p)
{
	os<<"Id: "<<p.getId()<<"\tScore: "<<p.getScore()<<endl;
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

int calculateScore(int M ,List<POI> d[])
{
	POI temp;
	int score = 0;
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<d[i].length(); j++)
		{
			d[i].findElem(j,temp);
			score += temp.getScore();
		}
	}
	return score;
}



double calculateOf(POI start, POI end, POI between){
	double of = pow(between.getScore(),2)/(calculateDistance(start,between)+between.getDuration()+calculateDistance(between,end)-calculateDistance(start,end));
	return of;
}

double timeAddition(POI start, POI end, POI between)
{
	return calculateDistance(start,between)+between.getDuration()+calculateDistance(between,end)-calculateDistance(start,end);
	
}

bool validateTime(double currentTime, double endOfTour)		//to remove
{
	return (currentTime<endOfTour);
}



int main(int argc, char* argv[]) {
	int epan = atoi(argv[1]); //FIX ME
	double pie = atof(argv[2]);
	string filename = argv[3];
	int K, M, SD, N, id;
	double x, y;
	int d, s, open, close;
	int opena[7];
	int closea[7];
	string NWLN = "\n";
	string garbagecan;

	ifstream inFile(argv[3]);

	inFile >> K >> M >> SD >> N;
	inFile.ignore(256,'\n');
	inFile >> id >> x >> y >> d >> s >> open >> close;
	POI * hotel = new POI(id, x, y, open, close);
	POI pois[N];
	List<POI> dromologia[M];
	double currentTime[M]; 
	for(int i=0; i<M; i++){ 
		dromologia[i].insertStart(*hotel);
		dromologia[i].insertEnd(*hotel);
		currentTime[i] = hotel->getOpenTime(SD);
	}
	
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


	int SD_ = SD;
	int maxScore = 0;
	List<POI> finalDromologia[M];
	
cout<<"Arxi tou tour "<<currentTime[0]<<endl;
	
for(int r = 0; r < epan; r++)
{
	for (int i=1; i < N; i++){
		bool found = false;
		for(int m=0; m < M; m++){
			if(dromologia[m].search(pois[i])!=-1 and pois[i].getSelected()){
				found = true;

				break;
			}
		}
		if(found)
		{
			//cout<<"GEIA SOU VREEEE"<<endl;
			continue;
		}
		double maxOf = 0;
		int savedM, savedJ;
		double savedTime;
		SD = SD_;
		for(int m=0; m < M; m++){
			int list_sz = dromologia[m].length();
			for (int j=1; j < list_sz; j++){
				if(j+1 >= list_sz and j != 1){
					break;
				}
				POI start, end;
				dromologia[m].findElem(j-1, start);
				dromologia[m].findElem(j, end);
				double currentTimeTemp = currentTime[m] + timeAddition(start, end, pois[i]);
				if(currentTimeTemp <= end.getCloseTime(SD) and currentTimeTemp + calculateDistance(end, *hotel) <= hotel->getCloseTime(SD)){
					bool outOfTime = false;
					for(int y=j+1; y < list_sz; y++){
						POI next;
						dromologia[m].findElem(y, next);
						if(currentTimeTemp > next.getCloseTime(SD)){
							outOfTime = true;
							break;
						}
					}
					if (!outOfTime){
						double of = calculateOf(start, end, pois[i]);
						if (maxOf <= of){
							maxOf = of;
							savedJ = j;
							savedM = m;
							savedTime = currentTimeTemp;
						}
					}
				}
			}
			SD++;
			if (SD > 6){
				SD = 0;
			}
		}
		if (maxOf > 0){
			dromologia[savedM].insertPos(pois[i], savedJ);			
			pois[i].selectPoi();
			currentTime[savedM] = savedTime;
			cout<<"Inserted: "<<pois[i]<<" in: "<<savedM<<" at pos: "<<savedJ<<endl;

			//cout<<currentTime[savedM]<<endl;
			//cout << currentTime[savedM] << endl;
			//cout << "Last Closing time: " << pois[i].getCloseTime(SD)<<" of pos " << j << " with ID: " << pois[i].getId() << endl;
		}
	}
	int totalScore = calculateScore(M,dromologia);
	if (maxScore<totalScore)									
	{
		//cout<<"*********ASTERISK*****MPHKA***************"<<endl;
		maxScore = totalScore;
		copy(dromologia, dromologia+M, finalDromologia);
		
	}
	// for (int i=0; i<M; i++){
	// 	dromologia[i]->print();
	// }
	
	//--INSERT RITUAL TO APPEASE THE MACHINE SPIRIT HERE--
	// The soul of the Machine God surrounds thee.
	// The power of the Machine God invests thee.
	// The hate of the Machine God drives thee.
	// The Machine God endows thee with life.
	// COMPILE! (and dont print garbage)
	if(r == epan-1)
		break;
	for(int i=0; i<M; i++)
	{
		int list_sz = dromologia[i].length();
		int randomIndex = rand() % (list_sz -2) + 1;
		int deletionCount = (list_sz-2) * pie;
//		int counter = 0;
		int j = randomIndex;

			for(int counter = 0; counter < deletionCount; counter++)
			{
				POI temp,start,end;
				dromologia[i].findElem(randomIndex, temp);
				if(temp == *hotel);
				{
					randomIndex = 1;
					dromologia[i].findElem(randomIndex, temp);
				}
				dromologia[i].findElem(randomIndex-1,start);
				dromologia[i].findElem(randomIndex+1,end);
				
				dromologia[i].deletePos(temp, randomIndex);
				cout<<"Deleted: "<<temp<<"From drom: "<<i<<endl;
				currentTime[i] -= timeAddition(start, end, temp);
			}
			
					cout<<currentTime[i]<<" remaining now"<<endl;
		}

	// for(int i=0; i<M; i++){ 
	// 	currentTime[i] = hotel->getOpenTime(SD);
	// }
}

	cout<<"----------_FINAL_-----------"<<endl;
	for (int i=0; i<M; i++){
		cout<<"\nDromologio No: "<<i+1<<endl;
		finalDromologia[i].print();
		cout<<"me xrono: "<<currentTime[i]<<endl;
		cout<<"End of tour is: "<<hotel->getCloseTime(SD)<<endl;
		SD++;
			if (SD > 6){
				SD = 0;
			}
	}
	cout<<"Max score pou vrika: "<<maxScore<<endl;
	cout<<"Score final: "<<calculateScore(M,finalDromologia)<<endl;

	
	//delete hotel;
	return 0;


}
