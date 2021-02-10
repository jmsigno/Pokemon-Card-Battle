#include <string>
using namespace std;
class User{
public:
	User();
	~User();
	bool checkUid(string uid);
	void registration(string uid, string pw);
	bool login();
	string getID();

private:
	string username;
	string password;
};
