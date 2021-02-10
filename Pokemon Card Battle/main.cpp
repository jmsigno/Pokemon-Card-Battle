#include <iostream>
#include "Player.h"
#include "User.h"
#include "Game.h"
#include "Pokedex.h"

using namespace std;


int main() {
	//create a game object
	Game game;
	//calls the Game member printLogo() function to print the logo
	game.printLogo();
	//create a User object
	User user;
	//initialize x with return value of Game member mainMenu()
	int x = game.mainMenu();
	string uid, pw;
	while (x != 3) {
		switch (x)
		{
		case 1:
			//get user inputs for registration
			cout << "enter username: ";
			cin >> uid;
			cout << "enter password: ";
			cin >> pw;
			//calles checkID() to verify if username existed or not in the database, true if valid
			if (user.checkUid(uid) == true) {
				//if not exist, calls User member registration() function
				user.registration(uid, pw);
			}
			else {
				//if exist, print error message
				cout << endl;
				cout << "[ERROR]Username already taken!" << endl << endl;
			}
			break;
		case 2:
			//verify user login details by calling the User member login() function 
			if (user.login() == true) {
				//if login details exist in the database, Player object will be created
				Player player;
				//sets the Player object data by using the User object data with getID() function
				player.setData(user.getID());
				//initializes the while loop trigger
				int y = player.dashboard();
				while (y != 5) {
					//creat a Poke dex object by accepting player member getDeckNo() function as parameter
					Pokedex pokedex(player.getDeckNo());
					switch (y) 
					{
					case 1:
						//calls myPokedex() to print all pokemon available in the player dex
						pokedex.myPokedex();
						int iChoseU[3];
						cout << "Choose 3 pokemon" << endl;
						//get player Pokemon ID input 3 times, 
						for (int i = 0; i < 3; i++) {
							cout << "Enter your chosen Pokemon no:  ";
							cin >> iChoseU[i];
							//Custom exeption handling, when user input random characters
							while (!cin.good()) {
								cout << endl << "[ERROR]Wrong input! Pokemon No..." << endl;
								cin.clear();
								cin.ignore(INT_MAX, '\n');
								cout << "Enter your chosen Pokemon no:  ";
								cin >> iChoseU[i];
							}
						}
						//check the array of selection if exists in the dex
						if (pokedex.checkMyDex(iChoseU) == true) {
							//if condtions met, calls Game member battle() to start the rounds
							game.battle(iChoseU);
							//after battle, calls Player member getReward() fuction accepting Game member battleResult() fuction as parameter
							player.getReward(game.battleResult());
							//call Player member saveData() fuction to save new data of the player
							player.saveData();
							system("pause");
						}
						else {
							cout << "[ERROR]Invalid Selection! Exiting battle..." << endl << endl;
							system("pause");
						}
						break;
					case 2:
						//calls myPokedex() to print all pokemon available in the player dex
						pokedex.myPokedex();
						int choice;
						//ask for player pokemon selection
						cout << "Select Pokemon Id to evolve: ";
						cin >> choice;
						while (!cin.good()) {
							cout << endl << "[ERROR]Wrong input! Pokemon No..." << endl;
							cin.clear();
							cin.ignore(INT_MAX, '\n');
							cout << "Enter your chosen Pokemon no:  ";
							cin >> choice;
						}
						//check the selection if exists in the dex, able to evolve, already evolved and deck slot avaialability
						if (pokedex.checkMyDex(choice) == true && player.getEp() >= 5 ) {
							//if true calls the Pokedex member evolvePokemon() accepting the user input as parameter
							pokedex.evolvePokemon(choice);
							//calls Pokedex saveData()member to save data
							pokedex.saveData();
							//call player member deductEp from the player data
							player.deductEp();
							system("pause");
						}
						else {
							//if wrong input prints error message
							cout << endl << "Pokemon Not found or No evolution reqired or Pokedex is full." << endl << endl;
							system("pause");
						}
						break;
					case 3:
						//calls myPokedex() to print all pokemon available in the player dex
						cout << endl;
						pokedex.myPokedex();
						system("pause");
						break;
					case 4:
						//intialize loop trigger
						int z = game.helpMenu();
						while (z != 4) {
							switch (z)
							{
							case 1:
								//prints help information from help file
								game.help();
								system("pause");
								break;
							case 2:
								//prints ranking information from rank file
								game.rankInfo();
								system("pause");
								break;
							case 3:
								//list all pokemon in the screen
								game.viewPokedex();
								system("pause");
								break;
							}
							z = game.helpMenu();
						}
						break;
					}
					y = player.dashboard();
				}
			}
			else {
				//if username and password does not match with from the database, prints error message
				cout << endl;
				cout << "[ERROR]Invalid user name or password." << endl << endl;
			}
			break;
		}
		x = game.mainMenu();
	}

	system("pause");
}