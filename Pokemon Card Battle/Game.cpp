#include <iostream>
#include <fstream>
#include <iomanip>
#include "Game.h"
#include "Pokemon.h"

using namespace std;
//default contructor, prints out logo and welcome board
//initialize scoreboard
Game::Game()
{
	this->playerScore = new (nothrow) int;
	this->cpuScore = new (nothrow) int;
	
	*playerScore = 0;
	*cpuScore = 0;
	//note to self: cout pokemon logo here
}
//read and print logo from logo file
void Game::printLogo(){
	ifstream logo;
	string line;
	logo.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\logo.txt", ios_base::in);
	if (logo.is_open()) {
		while (logo.good()) {
			getline(logo, line);
			cout << line << endl;
		}
	}
	cout << endl << endl;
	logo.close();
}
//displays main Menu, return selection(int)
int Game::mainMenu() {
	int x = 0;
	cout << endl;
	cout << "/ - - - - - - - - - MAIN MENU - - - - - - - - - /" << endl;
	cout << "/                                               /" << endl;
	cout << "/   1. New Player | 2. Login | 3. Quit Game     /" << endl;
	cout << "/                                               /" << endl;
	cout << "/ - - - - - - - - - - - - - - - - - - - - - - - /" << endl << endl;
	cout << "Enter Selection: ";
	cin >> x;

	//Custom esxemption handling, when user input random characters
	while(!cin.good()){
		cout << endl << "[ERROR]Wrong input! Try again..." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Enter Selection: ";
		cin >> x;
	}
	cout << endl;
	return x;
}
//function that accepts and return integer user input as selection
int Game::helpMenu() {
	int x;
	cout << endl;
	cout << "/ - - - - - - - - - - - - -  - HELP MENU - - - - - - -  - - - - - - - - /" << endl;
	cout << "/                                                                       /" << endl;
	cout << "/ 1. How To Play | 2. Ranking | 3. Pokedex | 4. Back to My Dashboard    /" << endl;
	cout << "/                                                                       /" << endl;
	cout << "/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /" << endl;
	cout << "Enter Selection: ";
	cin >> x;
	//Custom esxemption handling, when user input random characters
	while (!cin.good()) {
		cout << endl << "[ERROR]Wrong input! Try again..." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Enter Selection: ";
		cin >> x;
	}
	return x;
}
//function fro printing out help information from help file
void Game::help() {
	ifstream help;
	string line;
	help.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\help.txt", ios_base::in);
	if (help.is_open()) {
		while (help.good()) {
			getline(help, line);
			cout << line << endl;
		}
	}
	cout << endl << endl;
	help.close();
}
//function that reads pokemon file and prints each line from the file to the screen
void Game::viewPokedex() {
	ifstream pokeData;
	pokeData.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\pokemon.txt", ios_base::in);

	int pId, pLv, pAtk, pLf, pEvo;
	string pName, pType;
	//read line from pokemon data file and store values on the attributes of pokemon object
	cout << endl;
	cout << "/ - - - - - - - - - - - - - - - - - - - - P O K E D E X - - - - - - - - - - - - - - - - - - - - - /" << endl << endl;
	cout << "No.\t" << "Name\t\t\t" << "Level\t" << "Type\t\t" << "Attack Pts\t" << "Life Pts\t" << "Next Evolution(ID)" << endl;
	//read from the file and print each line to the screen via loop
	while (pokeData >> pId >> pName >> pLv >> pType >> pAtk >> pLf >> pEvo) {
		cout << pId << "\t" << pName << "    \t\t" << pLv << "\t" << pType << "     \t" << pAtk << "\t\t" << pLf << "\t\t" << pEvo << endl;
	}
	cout << endl;
	cout << "/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /" << endl << endl;
	pokeData.close();
}
//function to print ranking information
void Game::rankInfo() {
	cout << endl;
	cout << "/ - - - - - - RANKING INFORMATION - - - - - - - - -/" << endl;
	cout << "/                                                  /" << endl;
	cout << "/ Rank         Points                              /" << endl;
	cout << "/                                                  /" << endl;
	cout << "/ Legendary    100pts                              /" << endl;
	cout << "/ Grandmaster  60pts                               /" << endl;
	cout << "/ Master       30pts                               /" << endl;
	cout << "/ Trainer      10pts                               /" << endl;
	cout << "/ Novice       0pts                                /" << endl;
	cout << "/                                                  /" << endl;
	cout << "/ How to rank: Gain +10 Points by winning battles. /" << endl;
	cout << "/ Note: -5 Points for losing a battle.             /" << endl;
	cout << "/ - - - - - - - - - - - - - - - - - - - - - - - - -/" << endl;
	cout << endl;
}

//This is the main battle function, accepts array of integer(pokemon Ids) as parameter
//Compositions: battle function calls Pokemon class
void Game::battle(int iChoseU[]) {
	
	//manually set the 3 pokemon for cpu for demo purposes only, I can use random generated if needed.
	int cpuDefaultPokemon[3] = { 23, 109, 52 };
	Pokemon playerPokemon[3];
	Pokemon cpuPokemon[3];
	
	//set all 3 Pokemon object data for players and prints pokemon
	cout << endl << "You Chose: " << endl;
	for (int i = 0; i < 3; i++) {
		playerPokemon[i].setData(iChoseU[i]);
		cout << playerPokemon[i].getPokeName() << endl;
	}
	//set all 3 Pokemon object data for cpus and prints pokemon
	cout << endl << "CPU Chose: " << endl;
	for (int i = 0; i < 3; i++) {
		cpuPokemon[i].setData(cpuDefaultPokemon[i]);
		cout << cpuPokemon[i].getPokeName() << endl;
	}

	cout << endl <<"Ready for battle...." << endl;
	system("pause");
	//initialize scoreboard
	int pscore = 0;
	int cscore = 0;

	//main battle
	for (int i = 0; i < 3; i++) {
		//set attack power and life points of each pokemon
		int pAtk = playerPokemon[i].getAttPwr();
		int pHp = playerPokemon[i].getLifePts();
		int cAtk = cpuPokemon[i].getAttPwr();
		int cHp = cpuPokemon[i].getLifePts();
		
		//attack power is deducted to the opponet life points, if one lifepoints reaches 0, battle terminated
		//dispay battle progess
		cout << endl;
		while (pHp > 0 && cHp > 0) {
			cHp = cHp - pAtk;
			cout << playerPokemon[i].getPokeName() << " Attacks " << cpuPokemon[i].getPokeName() << " with " << playerPokemon[i].getAttPwr() << " damage..." << endl << endl;
			pHp = pHp - cAtk;
			cout << cpuPokemon[i].getPokeName() << " Attacks " << playerPokemon[i].getPokeName() << " with " << cpuPokemon[i].getAttPwr() << " damage..." << endl << endl;
		}

		cout << endl;
		//compares both pokemons life points, larger hp wins
		if (pHp > cHp) {
			//player's pokemon win, display message
			cout << cpuPokemon[i].getPokeName() << " Retired!" << endl;
			cout << playerPokemon[i].getPokeName() << " Wins!" << endl << endl;
			pscore++;
		}
		else {
			//cpu pokemon win, display message
			cout << playerPokemon[i].getPokeName() << " Retired!" << endl;
			cout << cpuPokemon[i].getPokeName() << " Wins!" << endl << endl;
			cscore++;
		}
		
		system("pause");
	}

	//update scoreboard
	*playerScore = pscore;
	*cpuScore = cscore;
}
//fuctions for determining the battle result
int Game::battleResult() {
	if (*playerScore > *cpuScore) {
		//player wins
		return 1;
	}
	else if (*playerScore < *cpuScore) {
		//cpu wins
		return -1;
	}
	//tie
	return 0;
}

Game::~Game()
{
	delete playerScore;
	delete cpuScore;
	cout << endl << endl << "[SYSTEM]Game object deleted..." << endl << endl;
}
