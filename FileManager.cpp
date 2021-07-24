#include <iostream>
#include <fstream>
#include <byteswap.h>
#include <string.h>

using namespace std;

void writeByte(ofstream &file, int value, int size) {
    file.write(reinterpret_cast<const char *> (&value), size);
}

class FileManager {

    int byteRate;
    short int blockAlign;
    int chunkSize;
    int subChunk1Size;
    int subChunk2Size;

    void writeAudioData(ofstream file, float data) {

    }

    ofstream createWavHeaderFile(string fileName,
                                int samplingFrequency,
                                int bitsPerSample,
                                int numChannels) {
        ofstream file;
        file.open(fileName+".wav", ios::binary);
        if(file.is_open()) {
            file << "RIFF";
            file << "----";
            file << "WAVE";

            file << "fmt ";
            writeByte(file, __bswap_32(16), 4);
            writeByte(file, __bswap_16(1), 2);
            writeByte(file, __bswap_16(2), 2);
            writeByte(file, __bswap_32(44100), 4);
            writeByte(file, __bswap_32(byteRate), 4);
            writeByte(file, __bswap_32(blockAlign), 4);
            writeByte(file, __bswap_32(bitsPerSample), 4);
            file << "data";
            file << "----";

            file.close();
        }

        return file;
    }


    public:
    FileManager(string fileName,int samplingFrequency, int numChannels,
        float data, int bitsPerSample ) {
            byteRate = samplingFrequency * numChannels * bitsPerSample / 8;
            blockAlign = numChannels * bitsPerSample / 8;
            chunkSize = 0;
            subChunk1Size = __bswap_32(16);
            subChunk2Size = samplingFrequency * 2 * bitsPerSample / 8;

        createWavHeaderFile(fileName, samplingFrequency, bitsPerSample, numChannels);
    }
};
