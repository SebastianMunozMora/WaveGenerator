#include <iostream>
#include <stdio.h>
#include <string>
#include <charconv>
#include <cmath>
#include <vector>
#include "Sine.cpp"
#include "FileManager.cpp"

using namespace std;

int main () {
	SineWave mySine(0.5, 200);
	vector <float> sineWave = mySine.getWave();
	const int currentSampleRate = mySine.getSamplingRate();
	const int currentDuration = mySine.getDuration();
	FileManager fs("loFreq", currentSampleRate, 1, sineWave, 16);

	cout << "mySine: " << currentSampleRate << endl;
	cout << "mySine: " << currentDuration << endl;

	return 0;
}
