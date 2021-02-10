#include <iostream>
#include <string>
#include <fstream>
#include "Player.h"
using namespace std;

//default constructor, initializes attributes 
Player::Player(){
	cout << endl;
	cout << "[SYSTEM]New Player Object Created!" << endl << endl;
	this->username = " ";
	this->deckNo = 0;
	this->rp = 0;
	this->ep = 0;
}
//set object data from a file, accepts username
void Player::setData(string u) {
	ifstream playerData;
	playerData.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\player.txt", ios_base::in);
	string a;
	int x, y, z;
	//browse all lines and compare (string a) with the username(u) parameter
	while (playerData >> a >> x >> y >> z) {
		//if match, set a new data for the player
		if (a.compare(u) == 0) {
			this->username = a;
			this->deckNo = x;
			this->rp = y;
			this->ep = z;
		}
	}
	playerData.close();
}
//below are the fuction  to access the player data
string Player::getName() {
	return this->username;
}
int Player::getDeckNo() {
	return this->deckNo;
}
int Player::getRp() {
	return this->rp;
}
int Player::getEp() {
	return this->ep;
}
//players dashboard that displays player data and game menu
//this funtion returns integer selection
int Player::dashboard() {
	int x;
	string *rank;
	rank = new (nothrow) string;
	
	//set the ranking of a player
	if (this->rp < 10) {
		*rank = "Novice";
	}
	else if (this->rp >= 10 && this->rp < 30) {
		*rank = "Trainer";
	}
	else if (this->rp >= 30 && this->rp < 60) {
		*rank = "Master";
	}
	else if (this->rp >= 60 && this->rp < 100) {
		*rank = "Grandmaster";
	}
	else {
		*rank = "Legendary";
	}

	//displays Dashboard Menu and players current data
	cout << "/- - - - - - - - - - - - - - - - MY DASHBOARD - - - - - - -  - - - - - - - - - -/" << endl;
	cout << "/  Name: "<< this->username << "\t\t\t\t\t\t\t\t\t/" << endl;
	cout << "/  Rank: " << *rank << "\t\t\t\t\t\t\t\t/" << endl;
	cout << "/  Pokedex ID: " << this->deckNo << "\t\t\t\t\t\t\t\t/" << endl;
	cout << "/  Rank Points(RP): " << this->rp << " | " << "Evolution Points(EP):" << this->ep << "\t\t\t\t/"<< endl;
	cout << "/                                                                               /" << endl;
	cout << "/  1. Battle Mode | 2. Evolve Pokemon | 3. My Pokedex | 4. Help | 5. Logout     /" << endl;
	cout << "/                                                                               /" << endl;
	cout << "/- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -/" << endl;
	cout << endl << "Enter Selection: ";
	cin >> x;

	//Custom exception handling for wrong user input
	while (!cin.good()) {
		cout << endl << "[ERROR]Wrong input! Try again..." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Enter Selection: ";
		cin >> x;
	}

	delete rank;
	return x;
}
//function for deducting evolution points after a successful evolution
void Player::deductEp() {
	this->ep = this->ep - 5;
	cout << "5 Evolution points deducted..." << endl << endl;
}
//fuction for setting the reward after a successful battle execution
void Player::getReward(int x) {
	//WIN - reward
	if (x > 0) {
		this->rp = this->rp + 10;
		this->ep = this->ep + 10;
		cout << endl;
		cout << "YOU WIN THE BATTLE!" << endl;
		cout << "You Gained 10 rank points..." << endl;
		cout << "You Gained 5 evolution points..." << endl << endl;
	}
	//LOSE - reward
	else if (x < 0) {
		this->rp = this->rp - 5;
		cout << endl;
		cout << "YOU LOSE THE BATTLE!" << endl;
		cout << "5 Points deducted from your rank points..." << endl << endl;
	}
}
//fuction for saving player data to file  
void Player::saveData() {
	ifstream readPData;
	ofstream saveTmpPData;
	//open and read from current filename
	readPData.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\player.txt", ios_base::in);
	//create a temporary file
	saveTmpPData.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\playertmp.txt", ios_base::app);

	string a;
	int x, y, z;

	if (readPData.is_open()) {
		//read from the current file and get values
		while (readPData >> a >> x >> y >> z) {
			//if username found in this line, write the data in the temporary file
			if (a.compare(this->username) == 0) {
				saveTmpPData << this->username << ' ' << this->deckNo << ' ' << this->rp  << ' ' << this->ep << "\n";
			}
			else {
				//if user name not fine in this line, write the same data/line to the temporary file 
				saveTmpPData << a << ' ' << x << ' ' << y << ' ' << z << "\n";
			}
		}
		//close both files;
		readPData.close();
		saveTmpPData.close();
		//delete the current player data file
		remove("D:\\Desktop\\c++2\\Pokemon Card Battle\\player.txt");
		//rename the temporary file with the deleted player data filename
		rename("D:\\Desktop\\c++2\\Pokemon Card Battle\\playertmp.txt", "D:\\Desktop\\c++2\\Pokemon Card Battle\\player.txt");
	}
	else {
		cout << endl << "[ERROR]Player Data file is missing..." << endl;
	}
}
Player::~Player()
{
	cout << endl << "[SYSTEM]Player object deleted..." << endl << endl;
}
