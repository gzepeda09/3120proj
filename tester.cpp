#include <iostream>
#include <cstring>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

//struct for City
struct city {
    int infpass;
    int population;
};

//---Air Travel Variables---//
//List of cities
string flights[18] = {"San Francisco","Los Angeles","Phoenix","Las Vegas",
                      "Houston","Miami","New York City","Atlanta","Portland",
                      "Seattle","Chicago","Nashville","Boston","Philedelphia",
                      "Detroit","Milwaukee","Salt Lake City","Kansas City"};

double citypop[18] = {3318000.0,12488000.0,4652000.0,2839000.0,6603000.0,6215000.0,
                   18867000.0,5100000.0,2197000.0,3489000.0,8901000.0,1294000.0,
                   4327000.0,5756000.0,3521000.0,1448000.0,1192000.0,1711000.0};

string flight_path[14] = {};
string current_city = "";

//Needed to locate the next city
int location = 0;

//Each city's connections --Adjacency List
string NoCal[6] = {"Los Angeles", "Phoenix", "Las Vegas",
                   "Portland", "Seattle", "Salt Lake City"};
string SoCal[10] = {"San Francisco","Phoenix","Las Vegas","Houston",
                    "Miami","New York City","Atlanta","Portland","Chicago",
                    "Nashville"};
string Arizona[5] = {"San Francisco","Los Angeles","Las Vegas","Houston",
                     "Salt Lake City"};
string Nevada[7] = {"San Francisco","Los Angeles","Phoenix","Houston",
                    "Miami","New York City","Atlanta"};
string Texas[11] = {"Los Angeles","Phoenix","Las Vegas","Miami",
                    "New York City","Atlanta","Chicago","Nashville",
                    "Philedelphia","Salt Lake City","Kansas City"};
string Florida[10] = {"Los Angeles","Phoenix","Las Vegas","Houston",
                      "New York City","Atlanta","Chicago","Philedelphia",
                      "Milwaukee","Kansas City"};
string NewYork[11] = {"Los Angeles","Las Vegas","Houston",
                      "Miami","Atlanta","Chicago","Nashville",
                      "Boston","Philedelphia","Detroit","Milwaukee"};
string Georgia[6] = {"Los Angeles","Las Vegas","Houston","Miami",
                     "New York City","Philedelphia"};
string Oregon[4] = {"San Francisco","Los Angeles","Seattle","Salt Lake City"};
string Washington[3] = {"San Francisco","Portland","Salt Lake City"};
string Illinois[4] = {"Los Angeles","Houston","Miami","New York City"};
string Tennessee[4] = {"Los Angeles","Houston","New York City","Philedelphia"};
string NewEngland[2] = {"New York City","Detroit"};
string Pennsyl[6] = {"Houston","Miami","New York City","Atlanta",
                     "Nashville","Detroit"};
string Michigan[3] = {"New York City","Boston","Philedelphia"};
string Wisconsin[2] = {"Miami","New York City"};
string Utah[6] = {"San Francisco","Phoenix","Houston","Portland",
                  "Seattle","Kansas City"};
string Missouri[3] = {"Houston","New York City","Salt Lake City"};



//Match location with proper city
void match(string n){
  int i = 0;
  while (i < 18 && flights[i] != n){
    i++;
  }
  if(i >= 18){
    cout << "Didn't Find it" << endl;
  }
  location = i;
}

//Add a city to the flight path
void add_path(){
  int i = 0;
  while (i < 14 && flight_path[i] != ""){
    i++;
  }
  flight_path[i] = current_city;
}

//Show the cities in the flight path
void show_path(){
    int size = sizeof(flight_path)/sizeof(string);
  for (int i = 0; i<size; i++)
  {
    if(flight_path[i] != ""){
      cout << flight_path[i] << " " << "|" << " ";
    }
   if(flight_path[i] == ""){
      cout << flight_path[i];
    }
  }
  cout << "\n";
}

//Random number generator based on weighted edges
void rand_weight(int a){
  int length = a;
  int value = rand() % length;
  location = value;
  //cout << current_city << " ||| " << length << endl;
}

/*
//Random number generator based on weighted edges
void rand_weight(int * a){
  int value = rand() % 100;
  int length = (int)sizeof(a)/sizeof(int);
  for(int i = 0; i < length + 1; i++){
    if(value < a[i]){
      location = i;
      //cout << location;
      return;
    }
    value -= a[i];
  }
  cout << "Something very wrong is afoot!!! " << endl;
}
*/

//Determines the initial passengers that are infected
int infected = 0;
int Ipassengers[18];
double Total[2];
void sick_pilot(double x){
double infection_rate = x;
double nIR = (1 - infection_rate);
int passengers = (320 + rand() % 69);
int expected = passengers * infection_rate;
int variance = expected * nIR;
int lbound = (expected - variance);
int ipassengers = (lbound + rand() % (2*variance));
infected = ipassengers;
}

void sick_pilot1(double x){            
double infection_rate = x;
double nIR = (1 - infection_rate);
int passengers = (320 + rand() % 69)/2;                   //half capacity flights
int expected = passengers * infection_rate;
int variance = expected * nIR;
int lbound = (expected - variance);
int ipassengers = (lbound + rand() % (2*variance));
infected = ipassengers;
}


//Starting city for the flight path
void start_point(double x){
  int size = sizeof(flights)/sizeof(string);
  location = (rand() % size);
  sick_pilot(x);
  current_city = flights[location];
  add_path();
}

void start_point1(double x){           //half capacity solution
  int size = sizeof(flights)/sizeof(string);
  location = (rand() % size);
  sick_pilot1(x);
  current_city = flights[location];
  add_path();
}


//Next city for the flight path
void next_city(double x){
    switch(location)
    {
    case 0:
        {
        int weights[6]= {30,10,20,15,15,10};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[0] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = NoCal[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 1:
        {
        int weights[10]= {8,5,12,15,15,20,12,3,5,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[1] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = SoCal[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 2:
        {
        int weights[5] = {15,30,20,30,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[2] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Arizona[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 3:
        {
        int weights[7] = {10,25,10,15,12,20,8};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[3] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Nevada[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 4:
        {
        int weights[11] = {15,6,10,15,15,10,4,10,5,5,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[4] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Texas[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 5:
        {
        int weights[10] = {15,5,15,15,20,10,5,5,5,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[5] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Florida[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 6:
        {
        int weights[11] = {15,10,15,10,10,7,10,7,6,5,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[6] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = NewYork[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 7:
        {
        int weights[6]={15,15,20,15,30,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[7] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Georgia[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 8:
        {
        int weights[4] = {30,20,30,20};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[8] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Oregon[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 9:
        {
        int weights[3] = {50,30,20};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[9] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Washington[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 10:
        {
        int weights[4] = {20,30,20,30};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[10] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Illinois[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 11:
        {
        int weights[4] = {15,35,35,15};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[11] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Tennessee[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 12:
        {
        int weights[2] = {65,35};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[12] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = NewEngland[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 13:
        {
        int weights[6] = {20,15,30,20,10,5}; 
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[13] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Pennsyl[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 14:
        {
        int weights[3] = {50,20,30};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[14] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Michigan[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 15:
        {
        int weights[2] = {40,60};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[15] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Wisconsin[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 16:
        {
        int weights[6] = {20,10,30,15,15,10};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[16] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Utah[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 17:
        {
        int weights[3] = {40,40,20};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[17] += infected;
        sick_pilot(x);
        rand_weight(length);
        string next = Missouri[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    default:
		{
    	cout << "Should't see this message" << endl;
    	break;
		}
    }
  
}

void next_city1(double x){               //half capacity solution
    switch(location)
    {
    case 0:
        {
        int weights[6]= {30,10,20,15,15,10};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[0] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = NoCal[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 1:
        {
        int weights[10]= {8,5,12,15,15,20,12,3,5,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[1] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = SoCal[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 2:
        {
        int weights[5] = {15,30,20,30,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[2] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Arizona[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 3:
        {
        int weights[7] = {10,25,10,15,12,20,8};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[3] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Nevada[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 4:
        {
        int weights[11] = {15,6,10,15,15,10,4,10,5,5,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[4] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Texas[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 5:
        {
        int weights[10] = {15,5,15,15,20,10,5,5,5,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[5] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Florida[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 6:
        {
        int weights[11] = {15,10,15,10,10,7,10,7,6,5,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[6] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = NewYork[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 7:
        {
        int weights[6]={15,15,20,15,30,5};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[7] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Georgia[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 8:
        {
        int weights[4] = {30,20,30,20};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[8] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Oregon[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 9:
        {
        int weights[3] = {50,30,20};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[9] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Washington[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 10:
        {
        int weights[4] = {20,30,20,30};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[10] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Illinois[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 11:
        {
        int weights[4] = {15,35,35,15};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[11] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Tennessee[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 12:
        {
        int weights[2] = {65,35};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[12] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = NewEngland[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 13:
        {
        int weights[6] = {20,15,30,20,10,5}; 
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[13] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Pennsyl[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 14:
        {
        int weights[3] = {50,20,30};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[14] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Michigan[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 15:
        {
        int weights[2] = {40,60};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[15] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Wisconsin[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 16:
        {
        int weights[6] = {20,10,30,15,15,10};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[16] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Utah[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    case 17:
        {
        int weights[3] = {40,40,20};
        int length = sizeof(weights)/sizeof(int);
        Ipassengers[17] += infected;
        sick_pilot1(x);
        rand_weight(length);
        string next = Missouri[location];
        match(next);
        current_city = flights[location];
        add_path();
        break;
        }
    default:
		{
    	cout << "Should't see this message" << endl;
    	break;
		}
    }
}


void summation(){
  for(int i = 0; i < 18; i++){
    Total[1] += citypop[i];
  }
  for(int i = 0; i < 18; i++){
    Total[0] += Ipassengers[i];
  }
}


//-----------------------------------SIR Model-----------------------------------------//
//SIR Variables
double maximum = 0.0;
double Infected[100];
double Susceptible[100];
double Recovery[100];
double Results[100][10];

//Max Value: Returns the maximum value stored in an array
void MaxValue(double a[]){
  for(int i = 0; i < 100; i++)
  {
    if(maximum < a[i]){
      maximum = a[i];
    }
  }
}

//b- infection rate y- recovery rate c- location position for results
void SIR_model(double a[], double b, double y, int c){ 
  double dt = 1.0;             //time step
  double beta = b;             // infection rate
  double yamma = y;            //recovery rate
  double glove = 0.0;          //catch

  Infected[0] = a[0]/a[1];
  Susceptible[0] = 1.0 - Infected[0];
  Recovery[0] = 0;

  for(int i = 0; i < 100; i++){
    Susceptible[i+1] = Susceptible[i] - beta*(Susceptible[i]*Infected[i])*dt;
    Infected[i+1] = Infected[i] + (beta*Susceptible[i]*Infected[i] - yamma*Infected[i])*dt;
    Recovery[i+1] = Recovery[i] + (yamma*Infected[i])*dt;
    
    glove =  Infected[i];
    Results[i][c] = glove;
  }
  
  cout << Infected[0] << endl;
  MaxValue(Infected);
}
//--------------------------------------------------------------------------------------//

void clear(){
  for(int i = 0; i < 18; i++){
    Ipassengers[i] = 0;
  }
  for(int i = 0; i < 2; i++){
    Total[i] = 0;
  }
  for(int i = 0; i < 14; i++){
    flight_path[i] = "";
  }
  maximum = 0.0;
}

//Sends the results of 10 SIR trials to a CSV file
void DataPoint(string a){
  ofstream myfile;
  myfile.open(a);
  myfile << "0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.99" << endl; 
  for(int i = 0; i<100; i++){
    myfile << Results[i][0] << "," << Results[i][1] << "," << Results[i][2] << "," 
    << Results[i][3] << "," << Results[i][4] << "," << Results[i][5]
    << "," << Results[i][6] << "," << Results[i][7] << "," << Results[i][8] << "," << Results[i][9] << endl;
  }
  myfile.close();
}


int main()
{
    srand(time(NULL));
    double saver = 0.0;

    cout << "Recovery takes one week" << endl;

    start_point(0.1);
    for (int i = 0; i < 13; i++){
        next_city(0.10);
    }
    cout << "The Flight Path is: " << endl;
    show_path();
    summation();
    cout << "Total initial infected" << endl;
    cout << Total[0] << endl;
    cout << "Total population" << endl;
    cout << Total[1] << endl;
    SIR_model(Total, 0.10, (1.0/7.0), 0);

    cout << "Max individuals infected when infection rate is 0.10" << endl;
    cout << (maximum * Total[1]) << "//" <<maximum << endl;
    clear();

    saver = Results[0][0];

    start_point(0.20);
    for (int i = 0; i < 13; i++){
        next_city(0.20);
    }
    cout << "The Flight Path is: " << endl;
    show_path();
    summation();
    cout << "Total initial infected" << endl;
    cout << Total[0] << endl;
    cout << "Total population" << endl;
    cout << Total[1] << endl;
    SIR_model(Total, 0.20, (1.0/7.0), 1);

    cout << "Max individuals infected when infection rate is 0.20" << endl;
    cout << (maximum * Total[1]) << "//" <<maximum << endl;
    clear();


    start_point(0.30);
    for (int i = 0; i < 13; i++){
        next_city(0.30);
    }
    cout << "The Flight Path is: " << endl;
    show_path();
    summation();
    cout << "Total initial infected" << endl;
    cout << Total[0] << endl;
    cout << "Total population" << endl;
    cout << Total[1] << endl;
    SIR_model(Total, 0.30, (1.0/7.0), 2);

    cout << "Max individuals infected when infection rate is 0.30" << endl;
    cout << (maximum * Total[1]) << "//" <<maximum << endl;
    clear();


    start_point(0.40);
    for (int i = 0; i < 13; i++){
        next_city(0.40);
    }
    cout << "The Flight Path is: " << endl;
    show_path();
    summation();
    cout << "Total initial infected" << endl;
    cout << Total[0] << endl;
    cout << "Total population" << endl;
    cout << Total[1] << endl;
    SIR_model(Total, 0.40, (1.0/7.0), 3);

    cout << "Max individuals infected when infection rate is 0.40" << endl;
    cout << (maximum * Total[1]) << "//" <<maximum << endl;
    clear();


    start_point(0.50);
    for (int i = 0; i < 13; i++){
        next_city(0.50);
    }
    cout << "The Flight Path is: " << endl;
    show_path();
    summation();
    cout << "Total initial infected" << endl;
    cout << Total[0] << endl;
    cout << "Total population" << endl;
    cout << Total[1] << endl;
    SIR_model(Total, 0.50, (1.0/7.0), 4);

    cout << "Max individuals infected when infection rate is 0.50" << endl;
    cout << (maximum * Total[1]) << "//" <<maximum << endl;
    clear();


    start_point(0.60);
    for (int i = 0; i < 13; i++){
        next_city(0.60);
    }
    cout << "The Flight Path is: " << endl;
    show_path();
    summation();
    cout << "Total initial infected" << endl;
    cout << Total[0] << endl;
    cout << "Total population" << endl;
    cout << Total[1] << endl;
    SIR_model(Total, 0.60, (1.0/7.0), 5);

    cout << "Max individuals infected when infection rate is 0.60" << endl;
    cout << (maximum * Total[1]) << "//" <<maximum << endl;
    clear();


    start_point(0.70);
    for (int i = 0; i < 13; i++){
        next_city(0.70);
    }
    cout << "The Flight Path is: " << endl;
    show_path();
    summation();
    cout << "Total initial infected" << endl;
    cout << Total[0] << endl;
    cout << "Total population" << endl;
    cout << Total[1] << endl;
    SIR_model(Total, 0.70, (1.0/7.0), 6);

    cout << "Max individuals infected when infection rate is 0.70" << endl;
    cout << (maximum * Total[1]) << "//" <<maximum << endl;
    clear();


    start_point(0.80);
    for (int i = 0; i < 13; i++){
        next_city(0.80);
    }
    cout << "The Flight Path is: " << endl;
    show_path();
    summation();
    cout << "Total initial infected" << endl;
    cout << Total[0] << endl;
    cout << "Total population" << endl;
    cout << Total[1] << endl;
    SIR_model(Total, 0.80, (1.0/7.0), 7);

    cout << "Max individuals infected when infection rate is 0.80" << endl;
    cout << (maximum * Total[1]) << "//" <<maximum << endl;
    clear();


    start_point(0.90);
    for (int i = 0; i < 13; i++){
        next_city(0.90);
    }
    cout << "The Flight Path is: " << endl;
    show_path();
    summation();
    cout << "Total initial infected" << endl;
    cout << Total[0] << endl;
    cout << "Total population" << endl;
    cout << Total[1] << endl;
    SIR_model(Total, 0.90, (1.0/7.0), 8);

    cout << "Max individuals infected when infection rate is 0.90" << endl;
    cout << (maximum * Total[1]) << "//" <<maximum << endl;
    clear();


    start_point(0.99);
    for (int i = 0; i < 13; i++){
        next_city(0.99);
    }
    cout << "The Flight Path is: " << endl;
    show_path();
    summation();
    cout << "Total initial infected" << endl;
    cout << Total[0] << endl;
    cout << "Total population" << endl;
    cout << Total[1] << endl;
    SIR_model(Total, 0.99, (1.0/7.0), 9);

    cout << "Max individuals infected when infection rate is 0.99" << endl;
    cout << (maximum * Total[1]) << "//" <<maximum << endl;
    clear();

    Results[0][0] = saver;

    DataPoint("infect.csv");




    //--------------------------------------------------------------------------------------------------------------//
    /*

    cout << "Half Capacity" << endl;

    start_point1(0.1);
    for (int i = 0; i < 13; i++){
        next_city1(0.10);
    }
    cout << "The Flight Path is: " << endl;
    show_path();
    summation();
    cout << "Total initial infected" << endl;
    cout << Total[0] << endl;
    cout << "Total population" << endl;
    cout << Total[1] << endl;
    SIR_model(Total, 0.10, (1.0/7.0), 0);

    cout << "Max individuals infected when infection rate is 0.10" << endl;
    cout << (maximum * Total[1]) << "//" <<maximum << endl;

    */

    return 0;
}