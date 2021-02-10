#include <iostream>
using namespace std;

class Pokedex {
public:
	Pokedex(int x);
	void myPokedex();
	bool checkMyDex(int x[]);
	bool checkMyDex(int x);
	void saveData();
	void evolvePokemon(int x);
	~Pokedex();

private:
	int deckNo;
	int myDex[5];
};

