#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <random>
using namespace std;

// Cards are now represented as numbers over strings
#define CIRC			0
#define SIGMA			1
#define ADD				2
#define SUB				3
#define DIA				4
#define NABLA			5
#define MULTI			6
#define EXCEED			7
#define BALLORD			8
#define EQUATION		9
#define SUPERFAC		10
#define MINING			11
#define SMALLWORLD		12
#define BRIDGABLE_HT	13
#define VEILER			14	// spefically tracked as the HT Small World Bridge
#define NON_COMBO		15	// Things such as Called By

int main()
{
	//Initializing a ton of values
	// Unlike using rand() from cstdlib and %, this can guarantee a uniform distribution instead of slightly prioritizing smaller values
	default_random_engine rng;
	uniform_int_distribution<int> randomFromDeck(0, 39);

	int turn = 0, handsToDraw = 0, card, i, x, y, hand[6] = { -1 };
	//int numExceed, numCircular, numNormal, numSigma, numSpecial, numHT, numVeiler, numEquation, numMining, numSW, numNabla;
	int numNormal, numSpecial, numSpecNorm;
	int handCards[16] = { 0 };
	bool combo, smallworld, mining, circular;
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
	int deck[40] = {CIRC, CIRC, CIRC, EXCEED, EXCEED, SIGMA, SIGMA, NABLA, NABLA, ADD, ADD, ADD, SUB, SUB, SUB,
					DIA, DIA, DIA, MULTI, EQUATION, MINING, MINING, MINING, SMALLWORLD, SMALLWORLD, SMALLWORLD, NON_COMBO, NON_COMBO,
					BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT, BRIDGABLE_HT,
					VEILER, VEILER, VEILER};
	long long outOfDeckBitMask;

	int a = 0, b = 0, d = 0, e = 0, r = 0;
	
	// Record this point in time as the beginning of the sim
	struct timespec timeStart, timeEnd;
	timespec_get(&timeStart, TIME_UTC);
	
	for (a; a < handsToDraw; a++) { //Start of the program to re-do it all a number of times
		outOfDeckBitMask = 0;
		for (int j = 0; j < 16; j++)
			handCards[j] = 0;

		for (i = 0; i < y; i++) { //Drawing cards
			hand[i] = randomFromDeck(rng);
			//cout << outOfDeckBitMask << "&" << (1 << hand[i]) << "=" << (outOfDeckBitMask & (1 << hand[i])) << endl;
			if ((outOfDeckBitMask & (1 << hand[i])) == 0) {
				outOfDeckBitMask |= (1 << hand[i]);
				handCards[deck[hand[i]]]++;
			} else {
				i--; // Redo the random attempt
			}
		}

		combo = false;
		smallworld = false;
		mining = false;
		circular = false;

		//Checking if we have a combo up, or if we unbrick with Mining/SW
		numSpecial = handCards[SIGMA] + handCards[ADD] + handCards[SUB];
		numNormal = handCards[NABLA] + handCards[DIA] + handCards[MULTI];
		numSpecNorm = numSpecial + numNormal;

		if (handCards[CIRC] >= 1) {
			combo = true;
			circular = true;
		} else if (numSpecial >= 2) {
			combo = true;
		} else if (numSpecial >= 1 && numNormal >= 1) {
			combo = true;
		} else if (numSpecNorm >= 1 && handCards[EXCEED] == 1) {
			combo = true;
		} else if (handCards[NABLA] >= 1 && handCards[EQUATION] >= 1) {
			combo = true;
		} else if (handCards[SMALLWORLD] >= 1 && handCards[BRIDGABLE_HT] >= 1 && handCards[VEILER] != 3 && numSpecNorm == 0) {
			combo = true;
			smallworld = true;
			circular = true;
		} else if (handCards[SMALLWORLD] >= 1 && numSpecNorm >= 1 && handCards[EXCEED] <= 1) {
			combo = true;
			smallworld = true;
			circular = true;
		} else if (handCards[MINING] >= 1) {
			combo = true;
			mining = true;
			circular = true;
		}
		
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
	double circ = (double(r) / double(a)) * 100;

	//Prints results
	cout << "The simulation took " << nanoDiff << " nanoseconds to complete.\n";
	cout << "You were able to combo " << b << " out of " << a << " ("<< c << "%) times with no interruptions.\n";
	cout << "You unbricked your hand using Small World " << d << " times, or " << f << "% of the time.\n";
	cout << "You unbricked your hand using Cynet Mining " << e << " times, or " << t << "% of the time.\n";
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
