#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

class POI {

public:
	int id;
	double x, y;
	int d;
	int s;
	int open[6];
	int close[6];

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

struct node {
	POI point;
	node *prev;
	node *next;
};

class LinkedList {
private:
	node *head, *tail;
public:
	double time;
	LinkedList(POI hotel){
		head = hotel;
		tail = hotel;
		time = 0;
	}

	void insert_position(int pos, POI value)
{
	node *pre = new node;
	node *cur = new node;
	node *temp = new node;
	cur = head;
	for(int i=1; i<pos; i++)
	{
		pre = cur;
		cur = cur->next;
	}
	temp->point = value;
	pre->next = temp;
	temp->next = cur;
}
} 

double calculateDistance(POI start, POI end){
	double distance;
	distance = pow((end.x-start.x),2)+pow((end.y - start.y),2);
	return sqrt(distance);
}

int compare_ofs(double of1, double of2){
	if(of1 > of2) return 1;
	else if(of1<of2) return -1;
}



double calculateOf(POI start, POI end, POI between){
	of = pow(between.s,2)/(calculateDistance(start,between)+between.d+calculateDistance(between,end)-calculateDistance(start,end));
	return of;
}


int main() {
	ifstream inFile;
	int K;
	int M;
	int SD;
	int N;
	int id;
	double x;
	double y;
	int d;
	int s;
	int open;
	int close;
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
	

	cout << K << endl;
	cout << M << endl;
	cout << SD << endl;
	cout << N << endl;
	cout << x << endl;
	cout << y << endl;
	cout << open << endl;
	cout << close << endl;
	cout << hotel->close[0]<<endl;
	cout << hotel->open[0]<<endl;
	cout << "A POI RE!!!"<<endl;
	cout << pois[3].x<<endl;
	cout << pois[3].y<<endl;
	cout << pois[1].s<<endl;
	cout << calculateDistance(*hotel,pois[2])<<endl;


	delete hotel;
	return 0;


}