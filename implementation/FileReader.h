#ifndef FILEREADER_H
#define FILEREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

class FileReader
{
public:
    fstream fpSavegame;
    string savefileName;

    FileReader (void) : savefileName("") {}
    FileReader (char filename[]) :  savefileName(filename) {}
    ~FileReader(void) {}

    FileReader(const FileReader& rhsFR);
    FileReader& operator=(const FileReader& rhsFR);

    int  openFileForRead  (void);
    void closeFile        (void);
    void readFile         (void);

    int findPlayingAs (void);

    int  checkFileSize     (void);
    void readGameInfo      (void);
    void readGeneralsInfo  (void);
    void readCastlesInfo   (void);
    void readDivisionsInfo (void);

    void fixTwoByteGeneralsArrays  (void);
    void fixTwoByteCastlesArrays   (void);
    void fixTwoByteDivisionsArrays (void);
    
};

#endif
