#include "Pokedex.h"
#include <iostream>
#include <fstream>
#include "Pokemon.h"
using namespace std;

//default contructor instantly intialize attributes from deck data file
Pokedex::Pokedex(int a){
	//initialize deckNo
	this->deckNo = a;
	ifstream deck;
	int *x, *s1, *s2, *s3, *s4, *s5;

	x = new (nothrow) int;
	s1 = new (nothrow) int;
	s2 = new (nothrow) int;
	s3 = new (nothrow) int;
	s4 = new (nothrow) int;
	s5 = new (nothrow) int;

	//read deck data file and initialize in every index with data 
	deck.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\deck.txt", ios_base::in);
	if (deck.is_open()) {
		while (deck >> *x >> *s1 >> *s2 >> *s3 >> *s4 >> *s5) {
			if (*x == deckNo) {
				this->myDex[0] = *s1;
				this->myDex[1] = *s2;
				this->myDex[2] = *s3;
				this->myDex[3] = *s4;
				this->myDex[4] = *s5;
			}
		}
	}
	else
	{
		cout << "Deck file is missing!" << endl;
	}
	deck.close();
	delete x, s1, s2, s3, s4, s5;
}
//functions that prints out player's pokemon list 
void Pokedex::myPokedex(){
	Pokemon myPokemon[5];
	cout << "/- - - - - - - - - - - MY POKEDEX - - - - - - - - - - - - - -/" << endl;
	cout << endl;
	for (int i = 0; i < 5; i++) {
		myPokemon[i].setData(myDex[i]);
		cout << "No:\t\t" << myPokemon[i].getpokeId() << endl;
		cout << "Pokemon:\t" << myPokemon[i].getPokeName() << endl;
		cout << "AtkPwr:\t\t" << myPokemon[i].getAttPwr() << endl;
		cout << "Life:\t\t" << myPokemon[i].getLifePts() << endl;
		cout << "Type:\t\t" << myPokemon[i].getPokeType() << endl << endl;
	}
	cout << "/- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /" << endl << endl;
}
//function overload: takes an array of integer as parameter
bool Pokedex::checkMyDex(int x[]) {
	int tmp[5];
	int ctr = 0;
	//transfer data to temp array
	for (int i = 0; i < 5; i++) {
		tmp[i] = myDex[i];
	}
	// compare the 3 inputs from the list, if equal then input is correct, ctr means good,
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (x[i] == tmp[j] && x[i] != 0) {
				//if match, set the value to 0 to exclude the finished ones
				tmp[j] = 0;
				ctr++;
			}
		}
	}

	//if ctr = 3, means 3 inputs are good, else one or all of the inputs are invalid
	if (ctr == 3) {
		return true;
	}
	else {
		return false;
	}
}

//function overloading: this takes an integer as parameter
bool Pokedex::checkMyDex(int x) {
	//checks user slot if full
	bool isNotFull = false;
	for (int i = 0; i < 5; i++) {
		if (myDex[i] == 0) {
			isNotFull = true;
			break;
		}
		else {
			isNotFull = false;
		}
	}
	//check if selected pokemon id number is valid or existed in the list
	bool isValid = false;
	for (int i = 0; i < 5; i++) {
		if (x == myDex[i]) {
			isValid = true;
			break;
		}
		else {
			isValid = false;
		}
	}

	Pokemon myPokemon;
	myPokemon.setData(x);
	
	//check if the next evolution already in the list
	bool isNotExist = true;
	for (int i = 0; i < 5; i++) {
		if (myPokemon.getNextEvo() == myDex[i]) {
			isNotExist = false;
			break;
		}
		else {
			isNotExist = true;
		}
	}
	//if 3 conditions are met, return this true and ready for evolution
	if (isNotFull == true && isValid == true && isNotExist == true) {
		return true;
	}
	else {
		return false;
	}
}
//fuction for pokemon evolution takes only one pokemon id
void Pokedex::evolvePokemon(int x) {
	//create pokemon object
	Pokemon myPokemon, evolution;
	//set object data of the pokemon to be evolve
	myPokemon.setData(x);
	//set object data of the new pokemon(evolution)
	evolution.setData(myPokemon.getNextEvo());

	//check if the next evo is not 0, NOTE: 0 value for next evolution means, no/more evolution required
	if (myPokemon.getNextEvo() != 0) {
		for (int i = 0; i < 5; i++) {
			//check slot if 0, NOTE: 0 means, available slot in the pokedex
			if (myDex[i] == 0) {
				//store the ID of the new pokemon
				myDex[i] = evolution.getpokeId();
				cout << evolution.getpokeId() << ": " << evolution.getPokeName() << " added to your pokedex" << endl << endl;
				break;
			}
		}
	}
	else
	{
		cout << "Pokemon not found or can't be evolve anymore" << endl << endl;
	}
}

//fuction for saving data in deck data file
void Pokedex::saveData() {
	ifstream readDeck;
	ofstream saveDeck;
	//open deck data file
	readDeck.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\deck.txt", ios_base::in);
	//create and open temporary file
	saveDeck.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\decktmp.txt", ios_base::app);

	int i, s1, s2, s3, s4, s5;
	if (readDeck.is_open()) {
		//read each line via loop
		while (readDeck >> i >> s1 >> s2 >> s3 >> s4 >> s5) {
			//compare deckNO from the 1st string on the line
			if (this->deckNo == i) {
				//if match, write data on the temporary file
				saveDeck << i << ' ' << this->myDex[0] << ' ' << this->myDex[1] << ' ' << this->myDex[2] << ' ' << this->myDex[3] << ' ' << this->myDex[4] << "\n";
			}
			else {
				//if not match, write the same data on the temporary file
				saveDeck << i << ' ' << s1 << ' ' << s2 << ' ' << s3 << ' ' << s4 << ' ' << s5 << "\n";
			}
		}
		//close all files opened
		readDeck.close();
		saveDeck.close();
		//delete original file
		remove("D:\\Desktop\\c++2\\Pokemon Card Battle\\deck.txt");
		//rename temporary file with original file name
		rename("D:\\Desktop\\c++2\\Pokemon Card Battle\\decktmp.txt", "D:\\Desktop\\c++2\\Pokemon Card Battle\\deck.txt");
	}
	else {
		cout << "Deck file is missing" << endl;
	}
}

Pokedex::~Pokedex()
{
}
