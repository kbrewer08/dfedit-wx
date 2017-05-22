#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

class FileWriter
{
public:
    fstream fpSavegame;
    string savefileName;

    FileWriter (void) {}
    FileWriter (char filename[]) :  savefileName(filename) {}
    ~FileWriter(void) {}

    FileWriter(const FileWriter& rhsFW);
    FileWriter& operator=(const FileWriter& rhsFW);

    int  openFileForWrite (void);
    void closeFile        (void);

    int writeOneElementToFile (int address, int bytes, ushort newValue, int index);
    int writeGenOwner         (ushort newOwner, int index);
    int writeInventoryToFile  (void);

};

#endif
