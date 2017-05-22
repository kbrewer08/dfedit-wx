#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "DragonForce.h"

using namespace std;

FileWriter::FileWriter(const FileWriter& rhsFW)
: savefileName(rhsFW.savefileName)
{
}

FileWriter& FileWriter::operator=(const FileWriter& rhsFW)
{
    if(this == &rhsFW)
        return *this;

    savefileName = rhsFW.savefileName;

    return *this;
}

int FileWriter::openFileForWrite(void)
{
    fpSavegame.open(savefileName.c_str(), fstream::in | fstream::out | fstream::binary);

    return fpSavegame.good();
}

void FileWriter::closeFile(void)
{
    if(fpSavegame.is_open())
        fpSavegame.close();

    return;
}

int FileWriter::writeOneElementToFile(int address, int bytes, ushort newValue, int index)
{
    int isGood = 0;
    
    if(bytes == 2)
        newValue = g_rotateLeft(newValue, 8); //convert to big endian if necessary
    
    if(!fpSavegame.is_open())
        openFileForWrite();

    fpSavegame.seekg(address + (index * bytes));
    fpSavegame.write(reinterpret_cast<char*>(&newValue), bytes);

    if(fpSavegame.good())
        isGood = 1;

    closeFile();

    return isGood;
}

int FileWriter::writeGenOwner(ushort newOwner, int index)
{
    int isGood = 0;

    if(!fpSavegame.is_open())
        openFileForWrite();

    fpSavegame.seekg(GEN_OFFICER_OWNERSHIP + index);
    fpSavegame.write(reinterpret_cast<char*>(&newOwner), 1);

    if(fpSavegame.good())
        isGood = 1;

    closeFile();

    return isGood;
}

int FileWriter::writeInventoryToFile(void)
{
    int isGood = 0;

    if(!fpSavegame.is_open())
        openFileForWrite();

    for(int i = 0; i < 256; i++)
        itemInventoryBuffer[i] = g_rotateLeft(itemInventoryBuffer[i], 8);

    fpSavegame.seekg(ITEM_INVENTORY);
    fpSavegame.write(reinterpret_cast<char*>(itemInventoryBuffer), 512);

    if(fpSavegame.good())
        isGood = 1;

    closeFile();

    return isGood;
}
