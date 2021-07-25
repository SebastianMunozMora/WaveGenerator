#include "./TimeStamp.cpp"
#include "math.h"
#include <vector>

using namespace std;

class SineWave: public TimeStamp {

	vector <float> createWave(float A, float f, float ph) {
		TimeStamp timeStamp;
		vector <float> stamp = timeStamp.getTimeStamp();
		const int size = stamp.size();

		sineWave[size];

		for (int i = 0; i < size; i++) {
			sineWave.push_back(A * sin(2 * M_PI * f * stamp[i] + ph));
		}

		return sineWave;
	}

	vector <float> sineWave;

	public:
		SineWave(float amplitude = 1,float frequency = 1000,float phase = 0) {
			vector <float> sineWave = createWave(amplitude, frequency, phase);
		}
		vector <float> getWave() {
			return sineWave;
		}
};
