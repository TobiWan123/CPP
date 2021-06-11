#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {

	const int pers = 23;
	int day[pers];

	srand((unsigned int)time(NULL)); // For real random numbers

	for (int i = 0; i < pers; i++) {
		day[i] = 1 + rand() % 365;
	}

	int j = 0;
	int treffer = 0;
	int size = 100000;

	while (j < size) {
		for (int i = 0; i < pers; i++) {
			for (int k = i+1; k < pers; k++) {
				if (day[i] == day[k]) {
					treffer++;
				}
			}
		}

		for (int i = 0; i < pers; i++) {
			day[i] = 1 + rand() % 365;
		}

		j++;
	}

	float w = (float) treffer / (float) size;

	std::cout << "Anzahl der Treffer: " << treffer << " in " << size << " Versuchen." << std::endl;
	std::cout.precision(5);
	std::cout << "Wahrscheinlichkeit beträgt: " << w;
}
