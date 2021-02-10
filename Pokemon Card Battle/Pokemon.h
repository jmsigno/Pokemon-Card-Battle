#include <string>
#include <iostream>
using namespace std;
class Pokemon {
public:
	Pokemon();
	~Pokemon();
	void setData(int x);
	int getpokeId();
	string getPokeName();
	int getPokeLevel();
	string getPokeType();
	int getAttPwr();
	int getLifePts();
	int getNextEvo();

private:
	int pokeId;
	string pokeName;
	int pokeLevel;
	string pokeType;
	int attPwr;
	int lifePts;
	int nextEvo;

};

