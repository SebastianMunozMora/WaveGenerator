#include <iostream>
#include <vector>

using namespace std;

const int DEFAULT_FREQUENCY = 44100;
const int DEFAULT_DURATION = 1;

class TimeStamp {
	void createStamp(int sampleSize) {
		for (int i = 0; i < sampleSize; i++) {
			timeStamp.push_back((float)i / mySamplingFrequency);
		}
	}
	public:
		vector <float> timeStamp;
		int mySamplingFrequency;
		TimeStamp(int samplingFrequency = DEFAULT_FREQUENCY,
						int duration = DEFAULT_DURATION) {
			mySamplingFrequency = samplingFrequency;
			int sampleSize = samplingFrequency * duration;
			createStamp(sampleSize);
		}
		vector <float> getTimeStamp() {
			return timeStamp;
		}
};
