#include <fstream>
#include <string>
#include <math.h>
#include <cstdlib>
#include "List.h"
#include "POI.h"

//printing POIs
ostream& operator<<(ostream& os, POI& p)
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
	string garbage;
	
	//Diavasma arxeiou, arxikopoihsh antikeimenwn POI kai eisagogi tous se pinaka megethous N
	ifstream inFile(argv[3]);

	inFile >> K >> M >> SD >> N;
	inFile.ignore(256,'\n');
	inFile >> id >> x >> y >> d >> s >> open >> close;
	POI * hotel = new POI(id, x, y, open, close);
	POI pois[N];
	List<POI> dromologia[M];
	double currentTime[M]; 
	//topothetisi hotel stin arxi kai telos ton dromologion
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
cout<<"Start of tour: "<<currentTime[0]<<endl;
	
for(int r = 0; r < epan; r++)
{
	for (int i=1; i < N; i++)
	{
		bool found = false;			//yparxei to pois[i] se ena apo ta tria dromologia?
		for(int m=0; m < M; m++)
		{
			if(dromologia[m].search(pois[i])!=-1)
			{
				found = true;

				break;
			}
		}
		if(found or pois[i].getOpenTime(SD) == pois[i].getCloseTime(SD)) //ean nai h an einai kleisto sinexise sto epomeno
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
				dromologia[m].findElem(j-1, start); //pairno to stoixio stin 8esi j-1 tis listas
				dromologia[m].findElem(j, end); //to stoixio j
				double currentTimeTemp = currentTime[m] + timeAddition(start, end, pois[i]); //ypologizo ton xrono pou 8a mou pros8esei
				//elegxo arxika ean o xronos pou exw stin tin apostasi aytou pou
				//tha prostheso einai mikroteros apo to kleisimo tou ksenodoxiou (end of tour)
				if(currentTimeTemp + calculateDistance(end, *hotel) <= hotel->getCloseTime(SD)) 
				{
					bool outOfTime = false;
					//elegxos ean gia ta epomena aksio8eata tou dromologiou
					//o xronos pou proste8ike den ftanei na ta episkeftoume
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
						//an den exei ginei anefikti h episkepsi twn epomenwn
						//vrisko to ofelos se ayti tin 8esi
						//kai elegxo an einai megalitero apo to maxOf
						double of = calculateOf(start, end, pois[i]);
						if (maxOf <= of)
						{
							//an einai tote kratao tin thesi, to dromologio
							//kai ton xrono pou tha exw meta tin prosthiki tou
							maxOf = of;
							savedJ = j;
							savedM = m;
							savedTime = currentTimeTemp;
						}
					}
				}
			}
			//ayksano tin mera
			SD++;
			if (SD > 6)
			{
				//an einai meta apo 6 (kiriaki), ginetai 0 (deytera)
				SD = 0;
			}
		}
		//exontas elegksei tis 8eseis olwn twn dromologiwn giayto to aksiotheato
		//elegxo oti sigoura exei allaksei to maxOf apo tin arxiki tou timi
		if (maxOf > 0)
		{
			//kano enan teleytaio elegxo ean o xronos sto sigkekrimeno dromologio
			//stin sigkekrimeni thesi meta tin prosthiki tou aksiotheatou pou eksetazo
			//einai megaliteros h isws apo to kleisimo tou epomenou
			POI temp;
			dromologia[savedM].findElem(savedJ, temp);
			if(savedTime >= temp.getCloseTime(SD))
			{
				//ean nai den tha ginei prosthiki 
				continue;
			}
			//alliws prostheto to aksiotheato sto dromologio
			//kai rithmizo analogws ton xrono tou
			dromologia[savedM].insertPos(pois[i], savedJ);			
			currentTime[savedM] = savedTime;
			// cout<<"Inserted: "<<pois[i]<<" in: "<<savedM<<" at pos: "<<savedJ<<endl;
			// cout << "Last Closing time: " << pois[i].getCloseTime(SD)<<" of pos " << savedJ << " with ID: " << pois[i].getId() << endl;
			// cout<<currentTime[savedM]<<endl;
			//cout << currentTime[savedM] << endl;
		}
	}
	//exontas eite gemisei ta dromologia, eite eksantlisei ta aksiotheata
	//proxoraw sto na ypologiso to score twn dromologiwn
	int totalScore = calculateScore(M,dromologia);
	if (maxScore<totalScore)									
	{
		//ean einai megalitero tou maxScore to kratao
		//kai kratao ta dromologia sta finalDromologia
		maxScore = totalScore;
		for (int i=0; i<M; i++)		
		{							
			finalDromologia[i] = dromologia[i];
		}  													
	}

	//stin teleytaia epanalipsi den thelo tis diagrafes pou akolou8oun
	if(r == epan-1)
		break;
	//diagrafes
	//gia kathe dromologio
	for(int i=0; i<M; i++)
	{
		//list_sz megethos dromologiou
		int list_sz = dromologia[i].length();
		//tixaio aksiotheato tou dromologiou
		int randomIndex = rand() % (list_sz -2) + 1;
		//posa tha diagrapso
		int deletionCount = (list_sz-2) * pie;
		int j = randomIndex;

			for(int counter = 0; counter < deletionCount; counter++)
			{
				POI temp,start,end;
				dromologia[i].findElem(randomIndex, temp);
				//ean ftasei sto ksenodoxio
				//sinexise na diagrafeis pera apo ayto
				//diladi thesi 1 tis listas
				if(temp == *hotel);
				{
					randomIndex = 1;
					dromologia[i].findElem(randomIndex, temp);
				}
				dromologia[i].findElem(randomIndex-1,start);
				dromologia[i].findElem(randomIndex+1,end);
				
				dromologia[i].deletePos(temp, randomIndex);
				//cout<<"Deleted: "<<temp<<"From drom: "<<i<<endl;
				//afairesi kai tis antistoixis prosthikis xronou 
				//pou tha edine to diegrameno dromologio
				currentTime[i] -= timeAddition(start, end, temp);
			}
			
					//cout<<currentTime[i]<<" remaining now"<<endl;
	}
}

//-------FINAL RESULTS------
	cout<<"----------FINAL-----------"<<endl;
	for (int i=0; i<M; i++){
		cout<<"\nDromologio No: "<<i+1<<endl;
		finalDromologia[i].print();
		cout<<"End of tour: "<<currentTime[i]<<endl;
		cout<<"Score: "<<calculateScore(finalDromologia[i])<<endl;
		cout<<"Hotel closes at: "<<hotel->getCloseTime(SD)<<endl;
		SD++;
			if (SD > 6){
				SD = 0;
			}
	}
	cout<<"\nScore: "<<maxScore<<endl;
	cout<<"Score: "<<calculateScore(M,finalDromologia)<<endl;

	
	delete hotel;
	return 0;


}
