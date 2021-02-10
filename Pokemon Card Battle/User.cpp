#include <iostream>
#include <fstream>
#include "User.h"
using namespace std;
//default constructor
User::User()
{
	this->username = " ";
	this->password = " ";
	cout << "[SYSTEM]New user object created..." << endl << endl;
}
//function to check the new username from the file, returns true if not exist, else false.
bool User::checkUid(string uid) {
	ifstream userData;
	userData.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\users.txt", ios_base::in);
	string a, b;
	while (userData >> a >> b) {
		if (a.compare(uid) == 0) {
			userData.close();
			return false;
		}
	}
	return true;
	userData.close();
}

//registration fuction, called when user select new player option
//this function creates and initial user, player, deck, data.
void User::registration(string uid, string pw) {
	ofstream user;
	ofstream player;
	ofstream deck;
	ifstream deckCount;
	int *newDeckCount;

	//open all database to read and write data
	user.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\users.txt", ios_base::app);
	player.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\player.txt", ios_base::app);
	deck.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\deck.txt", ios_base::app);
	deckCount.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\deckCount.txt", ios_base::in);

	newDeckCount = new (nothrow) int;
	
	//get the latest deck count from the deck file
	if (deckCount.is_open()) {
		deckCount >> *newDeckCount;
	}
	else {
		cout << "deck.txt is missing." << endl;
	}

	deckCount.close();

	ofstream setDeckCount;
	setDeckCount.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\deckCount.txt", ios_base::trunc);
	
	//update deck count by adding 1 for every successful registration
	//deck count serves as deck No/Id
	setDeckCount << *newDeckCount + 1;
	//store new user data in user file
	user << uid << ' ' << pw << "\n";
	//initialize and store new player data in the player file
	player << uid << ' ' << *newDeckCount + 1 << ' ' << 10 << ' ' << 10 << "\n";
	//initialize new player pokedex with the default 3 pokemon and 2 evolution slots
	deck << *newDeckCount + 1 << ' ' << 1 << ' ' << 4 << ' ' << 7 << ' ' << 0 << ' ' << 0 << "\n";
	
	//close all data files
	setDeckCount.close();
	user.close();
	player.close();
	deck.close();

	delete newDeckCount;
	cout << endl;
	cout << "New user data created. You can now login in..." << endl << endl;
}
//this fuction returns true if username and password matches, false otherwise
bool User::login() {
	//open user file data for reading
	ifstream userInfo;
	userInfo.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\users.txt", ios_base::in);
	string a, b, uid, pw;
	bool isMatch = false;
	//get player username and password
	cout << "enter username: ";
	cin >> a;
	cout << "enter password: ";
	cin >> b;
	//compare input from the user data files
	while (userInfo >> uid >> pw) {
		//if match, set user object data, returns true
		if (a.compare(uid) == 0 && b.compare(pw) == 0){
			username = uid;
			password = pw;
			isMatch = true;
			userInfo.close();
			return isMatch;
		}
	}
	userInfo.close();
	//returns false if no match found
	return isMatch;
}
//fuction to get username
string User::getID() {
	return username;
}

User::~User()
{
	cout << endl << "[SYSTEM]Game Object Deleted" << endl << endl;
}

