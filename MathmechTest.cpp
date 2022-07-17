#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

// Cards are now represented as numbers over strings
#define NON_COMBO		0		// Things such as Called By
#define CIRCULAR	 	1
#define SIGMA 			2
#define ADD_SUB 		4
#define NORMAL			8
#define NABLA 			24 		// (16 + NORMAL)
#define EXCEED 			32
#define MINING 			64
#define SMALLWORLD 		128
#define BRIDGABLE_HT 	256
#define EQUATION 		512
#define VEILER			1024	// spefically tracked as the HT Small World Bridge

int main()
{
	//Initializing a ton of values
	srand((unsigned)time(0));
	int turn = 0, handsToDraw = 0, card, i, x, y, handMask, hand[6] = { -1, -1, -1, -1, -1, -1 };
	int numExceed, numCircular, numNormal, numSigma, numSpecial, numHT, numVeiler, numEquation, numMining, numSW, numNabla;
	bool combo, smallworld, searchers, mining, circular;
	double c;

	//Checking to see if player would have 5 or 6 cards in hand
	while (turn != 1 and turn != 2) {
		cout << "Going first or second (1 or 2)? ";
		cin >> turn;
	}
	y = turn + 4;
	
	// Set the number of simulations to run
	while (handsToDraw <= 0) {
		cout << "Number of hands to simulate: ";
		cin >> handsToDraw;
	}

	//Initializes decklist; first array was to test something, second array is the important one
	// string deck[2][40] = { {"Exceed", "Exceed", "Circular", "Circular", "Circular", "Diameter", "Diameter", "Diameter", "Sigma", "Sigma", "Nabla", "Nabla", "Subtraction", "Subtraction", "Subtraction",
	// 	"Addition", "Addition", "Addition",	"Multiplication", "Ash", "Ash", "Ash", "Belle", "Belle", "Belle", "Crow", "Crow", "Crow", "Veiler", "Veiler", "Veiler", "Equation", "Mining", "Mining",
	// 	"Mining", "SW", "SW", "SW", "Called", "Superfactorial"}, {"Exceed", "Exceed", "Circular", "Circular", "Circular", "Normal", "Normal", "Normal", "Sigma", "Sigma", "Nabla", "Nabla", "Special",
	// 	"Special", "Special", "Special", "Special", "Special", "Normal", "HT", "HT", "HT", "HT", "HT", "HT", "HT", "HT", "HT", "Veiler", "Veiler", "Veiler", "Equation", "Mining", "Mining", "Mining",
	// 	"SW", "SW", "SW", "Brick", "Brick"} };
	int deck[40] = {CIRCULAR, CIRCULAR, CIRCULAR, EXCEED, EXCEED, SIGMA, SIGMA, NABLA, NABLA, ADD_SUB, ADD_SUB, ADD_SUB, ADD_SUB, ADD_SUB, ADD_SUB,
					NORMAL, NORMAL, NORMAL, NORMAL, EQUATION, MINING, MINING, MINING, SMALLWORLD, SMALLWORLD, SMALLWORLD, NON_COMBO, NON_COMBO,
					BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT,
					VEILER, VEILER, VEILER};

	int a = 0, b = 0, d = 0, e = 0, g = 0, r = 0;
	
	// Record this point in time as the beginning of the sim
	struct timespec timeStart, timeEnd;
	timespec_get(&timeStart, TIME_UTC);
	
	for (a; a < handsToDraw; a++) { //Start of the program to re-do it all a number of times
		handMask = 0;
		numSpecial = 0;
		numExceed = 0;
		numVeiler = 0;
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

			handMask = handMask | deck[hand[i]];
			//cout << deck[0][hand[i]] /*<< " " << deck[1][hand[i]] << " " << card*/ << endl;

			if (deck[hand[i]] == SIGMA || deck[hand[i]] == ADD_SUB) {
				numSpecial++;	
		 	} else if (deck[hand[i]] == EXCEED) {
				numExceed++;	
		 	} else if (deck[hand[i]] == VEILER) {
				numVeiler++;
			}
		}
		//cout << handMask << " " << numSpecial << " " << numExceed << " " << endl;

		// numExceed = 0;
		// numCircular = 0;
		// numNormal = 0;
		// numSigma = 0;
		// numSpecial = 0;
		// numHT = 0;
		// numVeiler = 0;
		// numEquation = 0;
		// numMining = 0;
		// numSW = 0;
		// numNabla = 0;
		// for (i = 0; i < y; i++) { //Count which cards we have in hand
		// 	if (deck[1][hand[i] == "Exceed") {
		// 		numExceed++;
		// 	}
		// 	if (deck[1][hand[i]] == "Circular") {
		// 		numCircular++;
		// 	}
		// 	if (deck[1][hand[i]] == "Normal") {
		// 		numNormal++;
		// 	}
		// 	if (deck[1][hand[i]] == "Sigma") {
		// 		numSigma++;
		// 	}
		// 	if (deck[1][hand[i]] == "Special") {
		// 		numSpecial++;
		// 	}
		// 	if (deck[1][hand[i]] == "HT") {
		// 		numHT++;
		// 	}
		// 	if (deck[1][hand[i]] == "Veiler") {
		// 		numVeiler++;
		// 	}
		// 	if (deck[1][hand[i]] == "Equation") {
		// 		numEquation++;
		// 	}
		// 	if (deck[1][hand[i]] == "Mining") {
		// 		numMining++;
		// 	}
		// 	if (deck[1][hand[i]] == "SW") {
		// 		numSW++;
		// 	}
		// 	if (deck[1][hand[i]] == "Nabla") {
		// 		numNabla++;
		// 	}
		// }		

		//cout << numExceed << endl << numCircular << endl << Normal << endl << Sigma << endl << Special << endl << HT << endl << Veiler << endl << Equation << endl << Mining << endl << SW << endl;
		combo = false;
		smallworld = false;
		searchers = false;
		mining = false;
		circular = false;

		//Checking if we have a combo up, or if we unbrick with Mining/SW
		if ((handMask & CIRCULAR) == CIRCULAR) {
			combo = true;
			circular = true;
		} else if (numSpecial >= 2) {
			combo = true;
		} else if ((handMask & (NORMAL | SIGMA | ADD_SUB)) > NORMAL) {
			combo = true;
		} else if ((handMask & (NABLA | SIGMA | ADD_SUB)) > 0 && numExceed == 1) {
			combo = true;
		} else if ((handMask & (NABLA | EQUATION)) == (NABLA | EQUATION)) {
			combo = true;
		} else if ((handMask & (SMALLWORLD | BRIDGABLE_HT)) == (SMALLWORLD | BRIDGABLE_HT) && numVeiler != 3) {
			combo = true;
			smallworld = true;
			circular = true;
		} else if ((handMask & (SMALLWORLD | NABLA | SIGMA | ADD_SUB)) > SMALLWORLD && numExceed <= 1) {
			combo = true;
			smallworld = true;
			circular = true;
		} else if ((handMask & MINING) == MINING) {
			combo = true;
			mining = true;
			circular = true;
		}
		// if ((numSpecial + numSigma) >= 2) {
		// 	combo = true;
		// }
		// if ((numSpecial + numSigma) >= 1 && numNormal >= 1) {
		// 	combo = true;
		// }
		// if ((numSpecial + numNormal + numSigma + numNabla) >= 1 && numExceed == 1) {
		// 	combo = true;
		// }
		// if (numCircular >= 1) {
		// 	combo = true;
		// 	circular = true;
		// }
		// if ((numNabla) >= 1 && numEquation == 1) {
		// 	combo = true;
		// }
		// if (numSW >= 1 && numHT >= 1 && numVeiler != 3 && (numNormal + numSpecial + numSigma + numNabla) == 0 && combo == false && numMining == 0) {
		// 	combo = true;
		// 	smallworld = true;
		//	circular = true;
		// }
		// if (numSW >= 1 && (numNormal + numSpecial + numSigma + numNabla) >= 1 && numExceed <= 1 && combo == false && numMining == 0) {
		// 	combo = true;
		// 	smallworld = true;
		// 	circular = true;
		// }
		// if (numMining >= 1 && smallworld == false && combo == false) {
		// 	combo = true;
		// 	mining = true;
		// 	circular = true;
		// }
		// if (numSW >= 1 && numMining >= 1 && smallworld == true) {
		// 	searchers = true;
		// 	smallworld = false;
		// 	combo = true;
		// 	circular = true;
		// }
		
		//Adding 1 to a certain number if we have combo
		if (combo) {
			//cout << "\nYou've got full or some part of combo.\n";
			b++;
			if (circular) {
				r++;
				if (smallworld) {
					d++;
				}
				if (mining) {
					e++;
				}
			}
		}
		// else {
		// 	//cout << "\nYou're bricked, buddy.\n";
		// }
	}

	// Record this point in time as the ending of the sim
	timespec_get(&timeEnd, TIME_UTC);
	
	// Calculate time difference
	intmax_t secDiff = (intmax_t)timeEnd.tv_sec - (intmax_t)timeStart.tv_sec;
	long long nanoDiff = (1000000000 * secDiff) + (timeEnd.tv_nsec - timeStart.tv_nsec);

	//Calculates percentages
	c = (double(b) / double(a)) * 100;
	double f = (double(d) / double(a)) * 100;
	double t = (double(e) / double(a)) * 100;
	double u = (double(g) / double(a)) * 100;
	double circ = (double(r) / double(a)) * 100;

	//Prints results
	cout << "The simulation took " << nanoDiff << " nanoseconds to complete.\n";
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
nabla + equation*/
