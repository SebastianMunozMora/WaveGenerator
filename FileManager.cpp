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
    int subChunk2Size;

    void writeByte(ofstream &file, int value, int size) {
        file.write(reinterpret_cast<char *> (&value), size);
    }

    void writeAudioData(ofstream &file, vector<float> data) {
        for(auto sample: data){
            int sampleInt = (short int) (sample * 32767);
            writeByte(file, sampleInt, 2);
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
            writeByte(file, 1, 2);
            writeByte(file, numChannels, 2);
            writeByte(file, samplingFrequency, 4);
            writeByte(file, byteRate, 4);
            writeByte(file, blockAlign, 2);
            writeByte(file, bitsPerSample, 2);
            file << "data";
            file << "----";
            writeAudioData(file, data);
            int end = file.tellp();
            file.seekp(40);
            subChunk2Size = end - 44;
            cout << subChunk2Size << endl;
            writeByte(file, subChunk2Size, 4);
            file.seekp(4);
            chunkSize = 36 + subChunk2Size;
            cout << chunkSize << endl;
            writeByte(file, chunkSize, 4);
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
            subChunk2Size = samplingFrequency * 2 * bitsPerSample / 8;

        createWavHeaderFile(fileName, samplingFrequency, bitsPerSample, numChannels, data);
    }
};
