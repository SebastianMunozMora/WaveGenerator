#include <iostream>
#include <stdio.h>
#include <string>
#include <charconv>
#include <cmath>
#include <vector>
#include "Sine.cpp"

using namespace std;

int main () {
	SineWave mySine(2, 1000);
	vector <float> sineWave = mySine.getWave();

	cout << "mySine: " << sineWave[100] << endl;

	return 0;
}
