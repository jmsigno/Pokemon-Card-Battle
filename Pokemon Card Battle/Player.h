#include <string>
using namespace std;

class Player
{
public:
	Player();
	void setData(string u);
	int dashboard();
	void getReward(int x);
	void deductEp();
	void saveData();
	string getName();
	int getDeckNo();
	int getRp();
	int getEp();
	~Player();

private:
	string username;
	int deckNo;
	int rp;
	int ep;

};
/*Authors Comment:
Basically class declaration, with access modifiers, attributes declarations
*/