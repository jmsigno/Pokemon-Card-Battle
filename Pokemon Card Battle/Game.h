class Game
{
public:
	Game();
	int mainMenu();
	int helpMenu();
	int battleResult();
	void printLogo();
	void help();
	void rankInfo();
	void viewPokedex();
	void battle(int list[]);
	~Game();

private:
	int *playerScore;
	int *cpuScore;
};
