#include <iostream>
#include <fstream>
#include <byteswap.h>
#include <string.h>
#include <vector>

using namespace std;

class FileManager {

    int byteRate;
    short int blockAlign;
    int chunkSize;
    int subChunk1Size;
    int subChunk2Size;

    void writeByte(ofstream &file, int value, int size) {
        file.write(reinterpret_cast<const char *> (&value), size);
    }

    void writeAudioData(ofstream &file, vector<float> data) {
        for(auto sample: data){
            writeByte(file, __bswap_16(sample), 2);
        }
    }

    ofstream createWavHeaderFile(string &fileName,
                                int samplingFrequency,
                                int bitsPerSample,
                                int numChannels,
                                vector<float> data) {
        ofstream file;
        file.open(fileName+".wav", ios::binary);
        if(file.is_open()) {
            file << "RIFF";
            file << "----";
            file << "WAVE";

            file << "fmt ";
            writeByte(file, 16, 4);
            writeByte(file, __bswap_16(1), 2);
            writeByte(file, __bswap_16(numChannels), 2);
            writeByte(file, __bswap_32(samplingFrequency), 4);
            writeByte(file, __bswap_32(byteRate), 4);
            writeByte(file, __bswap_32(blockAlign), 2);
            writeByte(file, __bswap_32(bitsPerSample), 2);
            file << "data";
            file << "----";
            writeAudioData(file, data);
            int end = file.tellp();
            file.seekp(40);
            subChunk2Size = end - 44;
            cout << subChunk2Size << endl;
            writeByte(file, __bswap_32(subChunk2Size), 4);
            file.seekp(4);
            chunkSize = 36 + subChunk2Size;
            cout << chunkSize << endl;
            writeByte(file, __bswap_32(chunkSize), 4);
            file.close();
        }

        return file;
    }


    public:
    FileManager(string fileName,int samplingFrequency, int numChannels,
        vector<float> data, int bitsPerSample ) {
            byteRate = samplingFrequency * numChannels * bitsPerSample / 8;
            blockAlign = numChannels * bitsPerSample / 8;
            chunkSize = 0;
            subChunk1Size = __bswap_32(16);
            subChunk2Size = samplingFrequency * 2 * bitsPerSample / 8;

        createWavHeaderFile(fileName, samplingFrequency, bitsPerSample, numChannels, data);
    }
};

/*int main () {
    vector<float> data = {0.1,0.2,0.3,0.1};
    FileManager fm("hello", 44100, 2, data, 16);
}*/