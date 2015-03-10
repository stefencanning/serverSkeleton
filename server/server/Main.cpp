
#include <iostream>
#include <math.h>
#include "networking.h"
#include <fstream>
#include <thread>
#include <string>
#include <stdlib.h>
#include "PacketStream.h"

using namespace std; 

//Screen dimension constants
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 700;
//The window we'll be rendering to
float speed = 400;
//The window renderer
bool loadMedia();
//Portal
bool upMove=false,downMove=false,leftMove=false,rightMove=false;

bool initGameTime = true;
int GameTime = 0;
float playerAccumalatedTime = 0;
int amountOfTicksSinceLaunch = 0;

//Starts up SDL and creates window
bool init();
//Closes the SDL window
void close();
//Updates the game while players are playing.
void GameUpdate();
//Update the menu checking whether the player hits host or join
void MenuUpdate();
//Presents a screen and allows players to enter in a host and port
void JoinUpdate();
//Presents the lobby screen showing all the players currently in the game.
void LobbyUpdate();
//Presents the victory screen showing all the players time accumalated and who did the best.
void VictoryUpdate();

vector<clock_t> updateTimer = vector<clock_t>();
networking network = networking();
Net* n;
//Portal

//vector<float*> playerTimes = vector<float*>();


bool init();
bool loadMedia();
void GameRecieveLoop();
void updateLoop();
void close();
void recieveArrayLoop();
void LobbyRecieveLoop();
void VictoryRecieveLoop();
const int mazeSizeX = 52;
const int mazeSizeY = 28;
char* msg;
char* recieved;
bool quit;
enum GameState{Menu, Game, Lobby, Join,Victory};
GameState curState;
string hostIP;
string portIP;
bool host;
string* curString;
clock_t mainTime = clock();
bool deadReckoning = false;


char* doit()
{
    char ac[80];
    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
        cerr << "Error " << WSAGetLastError() <<
                " when getting local host name." << endl;
        return NULL;
    }
    cout << "Host name is " << ac << "." << endl;

    struct hostent *phe = gethostbyname(ac);
    if (phe == 0) {
        cerr << "Yow! Bad host lookup." << endl;
        return NULL;
    }
	int i;
    for ( i= 0; phe->h_addr_list[i] != 0; ++i) {
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        cout << "Address " << i << ": " << inet_ntoa(addr) << endl;
    }
    
    struct in_addr addr;
    memcpy(&addr, phe->h_addr_list[i-1], sizeof(struct in_addr));
	cout <<inet_ntoa(addr) << endl;
    return inet_ntoa(addr);
}

int main()
{
	quit = false;
	hostIP = "";
	portIP = "";
	host = false;
	quit = false;
	curState = GameState::Menu;
	//curState = GameState::Victory;
	int xPos = 0;
	int yPos = 0;
	
	msg = new char();


		//*
		//ifstream myfile ("C:/config.txt");

		
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		return 255;
	}

	char* retval = doit();

	WSACleanup();
	time_t t =time(0);
	srand(t);
	n = new Net();
	network = networking(retval,n);

	while(!quit) //While a player has not quit the game -- Game Loop
	{
		PacketStream pStream;
		string IP;
		string ident;
		string type;
		//pStream.fromCharArray(network.recieveCharArray());
		char* recievedCon = network.recieveCharArray();
		if(recievedCon[0]!='\0')
		{
			//memcpy(test, recievedCon, strlen(recievedCon));
			pStream.fromCharArray(recievedCon);
			pStream.readString(IP);
			pStream.readString(type);
			//std::string recievedstr = recievedCon;
			if(type.compare("connection")==0)
			{
				pStream.readString(ident);
				bool found = false;
				for(int i = 0; i < network.ips.size();i++)
				{
					if(IP.compare(network.ips.at(i))==0)
					{
						found = true;
					}
				}
				if(!found)
				{
					char* cstr = new char[IP.length() + 1];
					strcpy(cstr, IP.c_str());
					network.ips.push_back(cstr);
					cout<<"connection: "<<recievedCon<<endl;
					network.send("welcome to the game");
				}
			}
			else
			{
				network.send(recievedCon,IP);
			}
		}
		delete recievedCon;
	}
	return 0;
}

void MenuUpdate()
{
	//Declare button positions
}

void JoinUpdate()
{	
}

void LobbyUpdate() //<<P2P
{
}

void VictoryUpdate()
{
}



void GameUpdate()
{
}


bool init()
{
	return 0;
}

bool loadMedia()
{
	return 0;
}

void close()
{
}

void updateLoop() //<<state based updates
{  
}
void recieveArrayLoop()
{
}

void GameRecieveLoop()
{
}


void LobbyRecieveLoop()
{
}

void VictoryRecieveLoop()
{	
}
