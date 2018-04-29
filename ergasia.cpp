#include <fstream>
#include <string>
#include <math.h>
#include <cstdlib>
#include "List.h"
#include "POI.h"

//printing POIs
ostream& operator<<(std::ostream& os, POI& p)
{
	os<<"Id: "<<p.getId()<<" Score: "<<p.getScore()<<endl;
	return os;
}

//returns the distance between starting point and ending point
double calculateDistance(POI start, POI end){
	double distance;
	double endx = end.getCoordinates('x');
	double endy = end.getCoordinates('y');
	double startx = start.getCoordinates('x');
	double starty = start.getCoordinates('y');
	distance = pow((endx-startx),2)+pow((endy - starty),2);
	return sqrt(distance);
}

//returns the total score of all trips in array of trips
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
//returns the total score of a trip
int calculateScore(List<POI> trip)
{
	POI temp;
	int score = 0;
	for(int i=0; i<trip.length(); i++)
	{
		trip.findElem(i,temp);
		score += temp.getScore();
	}
	return score;
}

//returns Οφ ratio according to type
double calculateOf(POI start, POI end, POI between){
	double of = pow(between.getScore(),2)/(calculateDistance(start,between)+between.getDuration()+calculateDistance(between,end)-calculateDistance(start,end));
	return of;
}

//returns time added to the trip if POI between was inserted in between of Start and End
double timeAddition(POI start, POI end, POI between)
{
	return calculateDistance(start,between)+between.getDuration()+calculateDistance(between,end)-calculateDistance(start,end);
	
}



//---------MAIN----------
int main(int argc, char* argv[]) {

//-----METAVLITES KAI DIAVASMA APO TEST INSTANCE-----
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

	ofstream tempResultsWrite;
	ifstream tempResultsRead;
	
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
	while(!inFile.eof())
	{
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
	
	//----ALGORITHMOS----
cout<<"Arxi tou tour "<<currentTime[0]<<endl;
	
for(int r = 0; r < epan; r++)
{
	for (int i=1; i < N; i++)
	{
		bool found = false;
		for(int m=0; m < M; m++)
		{
			if(dromologia[m].search(pois[i])!=-1)
			{
				found = true;

				break;
			}
		}
		if(found or pois[i].getOpenTime(SD) == pois[i].getCloseTime(SD))
		{
			continue;
		}
		double maxOf = 0;
		int savedM, savedJ;
		double savedTime;
		SD = SD_;
		for(int m=0; m < M; m++)
		{
			int list_sz = dromologia[m].length();
			for (int j=1; j < list_sz; j++)
			{
				if(j+1 >= list_sz and j != 1)
				{
					break;
				}
				POI start, end;
				dromologia[m].findElem(j-1, start);
				dromologia[m].findElem(j, end);
				double currentTimeTemp = currentTime[m] + timeAddition(start, end, pois[i]);
				if(currentTimeTemp + calculateDistance(end, *hotel) <= hotel->getCloseTime(SD))
				{
					bool outOfTime = false;
					for(int y=j+1; y < list_sz; y++)
					{
						POI next;
						dromologia[m].findElem(y, next);
						if(currentTimeTemp > next.getCloseTime(SD))
						{
							outOfTime = true;
							break;
						}
					}
					if (!outOfTime)
					{
						double of = calculateOf(start, end, pois[i]);
						if (maxOf <= of)
						{
							maxOf = of;
							savedJ = j;
							savedM = m;
							savedTime = currentTimeTemp;
						}
					}
				}
			}
			SD++;
			if (SD > 6)
			{
				SD = 0;
			}
		}
		if (maxOf > 0)
		{
			POI temp;
			dromologia[savedM].findElem(savedJ, temp);
			if(savedTime >= temp.getCloseTime(SD))
			{
				continue;
			}
			dromologia[savedM].insertPos(pois[i], savedJ);			
			currentTime[savedM] = savedTime;
			// cout<<"Inserted: "<<pois[i]<<" in: "<<savedM<<" at pos: "<<savedJ<<endl;
			// cout << "Last Closing time: " << pois[i].getCloseTime(SD)<<" of pos " << savedJ << " with ID: " << pois[i].getId() << endl;
			// cout<<currentTime[savedM]<<endl;
			//cout << currentTime[savedM] << endl;
		}
	}
	int totalScore = calculateScore(M,dromologia);
	if (maxScore<totalScore)									
	{
		maxScore = totalScore;
		for (int i=0; i<M; i++)		//arxiki idea xrisimopoiontas copy cstor kai = operator tis listas
		{							//distixws den doulevei opote akolouthei to workaround
			finalDromologia[i] = dromologia[i];
		}  													
		// tempResultsWrite.open("tempresults.txt", std::fstream::out);
		// for (int i=0; i<M; i++)
		// {
		// tempResultsWrite<<"\nDromologio No: "<<i+1<<endl;
		// dromologia[i].print(tempResultsWrite);
		// tempResultsWrite<<"me xrono: "<<currentTime[i]<<endl;
		// tempResultsWrite<<"End of tour is: "<<hotel->getCloseTime(SD)<<endl;
		// SD++;
		// 	if (SD > 6)
		// 		SD = 0;
			
		// }
		// tempResultsWrite.close();
	}

	//stin teleytaia epanalipsi den thelo tis diagrafes pou akolou8oun
	if(r == epan-1)
		break;
	//diagrafes
	for(int i=0; i<M; i++)
	{
		int list_sz = dromologia[i].length();
		int randomIndex = rand() % (list_sz -2) + 1;
		int deletionCount = (list_sz-2) * pie;
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
				//cout<<"Deleted: "<<temp<<"From drom: "<<i<<endl;
				currentTime[i] -= timeAddition(start, end, temp);
			}
			
					//cout<<currentTime[i]<<" remaining now"<<endl;
	}
}

	cout<<"----------FINAL-----------"<<endl;
	for (int i=0; i<M; i++){
		cout<<"\nDromologio No: "<<i+1<<endl;
		finalDromologia[i].print();
		cout<<"me xrono: "<<currentTime[i]<<endl;
		cout<<"kai score: "<<calculateScore(finalDromologia[i])<<endl;
		cout<<"End of tour is: "<<hotel->getCloseTime(SD)<<endl;
		SD++;
			if (SD > 6){
				SD = 0;
			}
	}
	// tempResultsRead.open("tempresults.txt");
	// string getcontent;
	// while(getline(tempResultsRead,getcontent))
	// {
	// 	cout<<getcontent<<endl;
	// }
	cout<<"\nScore: "<<maxScore<<endl;
	cout<<"Score: "<<calculateScore(M,finalDromologia)<<endl;

	remove("tempresults.txt");
	delete hotel;
	return 0;


}
