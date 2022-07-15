#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

int main()
{
	//Initializing a ton of values
	srand((unsigned)time(0));
	int turn, card, i, x, y, hand[6] = { -1, -1, -1, -1, -1, -1 };
	int Exceed, Circular, Normal, Sigma, Special, HT, Veiler, Equation, Mining, SW, Nabla;
	bool combo, smallworld, searchers, mining, circular;
	double c;

	//Checking to see if player would have 5 or 6 cards in hand
	cout << "Going first or second? ";
	cin >> turn;
	while (turn != 1 and turn != 2) {
		cout << "Going first or second (1 or 2)? ";
		cin >> turn;
	}
	if (turn == 1) {
		y = 5;
	}
	else {
		y = 6;
	}

	//Initializes decklist; first array was to test something, second array is the important one
	string deck[2][40] = { {"Exceed", "Exceed", "Circular", "Circular", "Circular", "Diameter", "Diameter", "Diameter", "Sigma", "Sigma", "Nabla", "Nabla", "Subtraction", "Subtraction", "Subtraction",
		"Addition", "Addition", "Addition",	"Multiplication", "Ash", "Ash", "Ash", "Belle", "Belle", "Belle", "Crow", "Crow", "Crow", "Veiler", "Veiler", "Veiler", "Equation", "Mining", "Mining",
		"Mining", "SW", "SW", "SW", "Called", "Superfactorial"}, {"Exceed", "Exceed", "Circular", "Circular", "Circular", "Normal", "Normal", "Normal", "Sigma", "Sigma", "Nabla", "Nabla", "Special",
		"Special", "Special", "Special", "Special", "Special", "Normal", "HT", "HT", "HT", "HT", "HT", "HT", "HT", "HT", "HT", "Veiler", "Veiler", "Veiler", "Equation", "Mining", "Mining", "Mining",
		"SW", "SW", "SW", "Brick", "Brick"} };

	int a, b = 0, d = 0, e = 0, g = 0, r = 0;
	for (a = 0; a < 100000; a++) { //Start of the program to re-do it all a number of times
		for (i = 0; i < y; i++) { //Drawing cards
			card = 0 + (rand() % 39);
			hand[i] = card;
			if (i != 0) {
				for (x = 0; x != i; x++) {
					while (hand[i] == hand[x]) {
						//cout << "Card #" << i << " is equal to card #" << x << ". Rerolling... " << deck[0][card] << " " << deck[1][card] << " " << card << endl;
						card = 0 + (rand() % 39);
						hand[i] = card;
					}
				}
			}
			//cout << deck[0][hand[i]] /*<< " " << deck[1][hand[i]] << " " << card*/ << endl;
		}

		Exceed = 0;
		Circular = 0;
		Normal = 0;
		Sigma = 0;
		Special = 0;
		HT = 0;
		Veiler = 0;
		Equation = 0;
		Mining = 0;
		SW = 0;
		Nabla = 0;
		for (i = 0; i < y; i++) { //Count which cards we have in hand
			if (deck[1][hand[i]] == "Exceed") {
				Exceed++;
			}
			if (deck[1][hand[i]] == "Circular") {
				Circular++;
			}
			if (deck[1][hand[i]] == "Normal") {
				Normal++;
			}
			if (deck[1][hand[i]] == "Sigma") {
				Sigma++;
			}
			if (deck[1][hand[i]] == "Special") {
				Special++;
			}
			if (deck[1][hand[i]] == "HT") {
				HT++;
			}
			if (deck[1][hand[i]] == "Veiler") {
				Veiler++;
			}
			if (deck[1][hand[i]] == "Equation") {
				Equation++;
			}
			if (deck[1][hand[i]] == "Mining") {
				Mining++;
			}
			if (deck[1][hand[i]] == "SW") {
				SW++;
			}
			if (deck[1][hand[i]] == "Nabla") {
				Nabla++;
			}
		}

		//cout << Exceed << endl << Circular << endl << Normal << endl << Sigma << endl << Special << endl << HT << endl << Veiler << endl << Equation << endl << Mining << endl << SW << endl;
		combo = false;
		smallworld = false;
		searchers = false;
		mining = false;
		circular = false;

		//Checking if we have a combo up, or if we unbrick with Mining/SW
		if ((Special + Sigma) >= 2) {
			combo = true;
		}
		if ((Special + Sigma) >= 1 && Normal >= 1) {
			combo = true;
		}
		if ((Special + Normal + Sigma + Nabla) >= 1 && Exceed == 1) {
			combo = true;
		}
		if (Circular >= 1) {
			combo = true;
			circular = true;
		}
		if ((Nabla) >= 1 && Equation == 1) {
			combo = true;
		}
		if (SW >= 1 && HT >= 1 && Veiler != 3 && (Normal + Special + Sigma + Nabla) == 0 && combo == false && Mining == 0) {
			combo = true;
			smallworld = true;
		}
		if (SW >= 1 && (Normal + Special + Sigma + Nabla) >= 1 && Exceed <= 1 && combo == false && Mining == 0) {
			combo = true;
			smallworld = true;
			circular = true;
		}
		if (Mining >= 1 && smallworld == false && combo == false) {
			combo = true;
			mining = true;
			circular = true;
		}
		if (SW >= 1 && Mining >= 1 && smallworld == true) {
			searchers = true;
			smallworld = false;
			combo = true;
			circular = true;
		}
		
		//Adding 1 to a certain number if we have combo
		if (combo == true) {
			//cout << "\nYou've got full or some part of combo.\n";
			b++;
			if (smallworld == true) {
				d++;
			}
			if (mining == true) {
				e++;
			}
			if (searchers == true) {
				g++;
			}
			if (circular == true) {
				r++;
			}
		}
		else {
			//cout << "\nYou're bricked, buddy.\n";
		}
	}

	//Calculates percentages
	c = (double(b) / double(a)) * 100;
	double f = (double(d) / double(a)) * 100;
	double t = (double(e) / double(a)) * 100;
	double u = (double(g) / double(a)) * 100;
	double circ = (double(r) / double(a)) * 100;

	//Prints results
	cout << "You were able to combo " << b << " out of " << a << " ("<< c << "%) times with no interruptions.\n";
	cout << "You unbricked your hand using Small World " << d << " times, or " << f << "% of the time.\n";
	cout << "You unbricked your hand using Cynet Mining " << e << " times, or " << t << "% of the time.\n";
	cout << "You unbricked with Small World and Cynet Mining at the same time " << g << " times, or " << u << "% of the time.\n";
	cout << "Your starter (whether by searching or having it in hand) was Circular " << r << " times, or " << circ << "% of the time.\n";

	system("pause");
	return 0;
}

/*2 specials
normal + special
any mathmech + exceed
circular
cynet mining
small world + any handtrap thats not E veiler
small world + any mathmech name
any mathmech (not sigma) + equation*/