#include "Pokemon.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//default constructor
Pokemon::Pokemon(){
	this->pokeId = 0;
	this->pokeName = " ";
	this->pokeLevel = 0;
	this->pokeType = " ";
	this->attPwr = 0;
	this->lifePts = 0;
	this->nextEvo = 0;
}
//set and get functions
int Pokemon::getpokeId() {
	return this->pokeId;
}
string Pokemon::getPokeName() {
	return this->pokeName;
}
int Pokemon::getPokeLevel() {
	return this->pokeLevel;
}
string Pokemon::getPokeType() {
	return this->pokeType;
}
int Pokemon::getAttPwr() {
	return this->attPwr;
}
int Pokemon::getLifePts() {
	return this->lifePts;
}
int Pokemon::getNextEvo() {
	return this->nextEvo;
}
//functions that accept integer(pokemon id) as parameter
void Pokemon::setData(int x){	
	//open pokemon data file
	ifstream pokeData;
	pokeData.open("D:\\Desktop\\c++2\\Pokemon Card Battle\\pokemon.txt", ios_base::in);
	
	int pId, pLv, pAtk, pLf, pEvo;
	string pName, pType;
	//read line from pokemon data file and store values on the attributes of pokemon object
	while (pokeData >> pId >> pName >> pLv >> pType >> pAtk >> pLf >> pEvo ) {
		if (pId == x) {
			this->pokeId = pId;
			this->pokeName = pName;
			this->pokeLevel = pLv;
			this->pokeType = pType;
			this->attPwr = pAtk;
			this->lifePts = pLf;
			this->nextEvo = pEvo;
		}
	}
	pokeData.close();
}

Pokemon::~Pokemon()
{
}
