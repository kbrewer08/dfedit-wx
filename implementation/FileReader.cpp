#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>

#include "DragonForce.h"

using namespace std;

FileReader::FileReader(const FileReader& rhsFR)
: savefileName(rhsFR.savefileName)
{
}

FileReader& FileReader::operator=(const FileReader& rhsFR)
{
    if(this == &rhsFR)
        return *this;

    savefileName = rhsFR.savefileName;

    return *this;
}

int FileReader::openFileForRead(void)
{
    fpSavegame.open(savefileName.c_str(), fstream::in | fstream::binary);

    return fpSavegame.good();
}

void FileReader::closeFile(void)
{
    if(fpSavegame.is_open())
        fpSavegame.close();

    return;
}

int FileReader::checkFileSize(void)
{
    long fileSize = 0;

    if(!fpSavegame.is_open())
        openFileForRead();

    fpSavegame.seekg(0, fstream::end);
    fileSize = fpSavegame.tellg();
    fpSavegame.seekg(0, fstream::beg);

    closeFile();

    return fileSize == 18160;
}

void FileReader::readFile(void)
{
    if(!fpSavegame.is_open())
        openFileForRead();

    readGameInfo();
    readGeneralsInfo();
    readCastlesInfo();
    readDivisionsInfo();

    closeFile();

    return;
}

int FileReader::findPlayingAs(void) //need to call this somewhere after file is open
{
    int i;
    int done;

    done = 0;

    if(!fpSavegame.is_open())
        openFileForRead();

    for(i = 0; (i < 8) && !done; i++)
        if(strstr(monarchFilename[i], gPlayingAs.c_str()))
            done = 1;

    i--;

    return i;
}

void FileReader::readGameInfo(void)
{
    fpSavegame.seekg(PLAYING_AS);
    fpSavegame.read(playingAs_cstr, 4);
    gPlayingAs = playingAs_cstr;

/*
    fseek(savegameIn, GAME_MONTH, SEEK_SET);
    fread(&gameMonth, 2, 1, savegameIn);

    fseek(savegameIn, GAME_WEEK, SEEK_SET);
    fread(&gameWeek, 2, 1, savegameIn);

    fseek(savegameIn, GAME_YEAR, SEEK_SET);
    fread(&gameYear, 2, 1, savegameIn);
*/
    fpSavegame.seekg(ITEM_INVENTORY);
    fpSavegame.read(reinterpret_cast<char*>(itemInventoryBuffer), 512);
/*
    fseek(savegameIn, AWARDS_LEFT, SEEK_SET);
    fread(&awardsLeft, 2, 1, savegameIn);

    gameYear   = g_rotateLeft(gameYear, 8);
    gameMonth  = g_rotateLeft(gameMonth, 8);
    gameWeek   = g_rotateLeft(gameWeek, 8);
    awardsLeft = g_rotateLeft(awardsLeft, 8);
*/
    for(int i = 0; i < 256; i++)
        itemInventoryBuffer[i] = g_rotateLeft(itemInventoryBuffer[i], 8);

    return;
}

void FileReader::readGeneralsInfo(void)
{
    fpSavegame.seekg(FIELD_STATUS_1);
    fpSavegame.read(reinterpret_cast<char*>(FsBuffer1), 171);

    fpSavegame.seekg(GEN_OFFICER_OWNERSHIP);
    fpSavegame.read(reinterpret_cast<char*>(officerOwner), 171);

    fpSavegame.seekg(FIELD_STATUS_2);
    fpSavegame.read(reinterpret_cast<char*>(FsBuffer2), 171);

    fpSavegame.seekg(GEN_LEVEL);
    fpSavegame.read(reinterpret_cast<char*>(levelBuffer), 171);

    fpSavegame.seekg(GEN_CLASS);
    fpSavegame.read(reinterpret_cast<char*>(classBuffer), 171);

    fpSavegame.seekg(GEN_LOCATION);
    fpSavegame.read(reinterpret_cast<char*>(locationNumBuff), 342);

    fpSavegame.seekg(GEN_TROOP_TYPE);
    fpSavegame.read(reinterpret_cast<char*>(troopTypeBuff), 171);

    fpSavegame.seekg(GEN_CURR_TROOP_COUNT);
    fpSavegame.read(reinterpret_cast<char*>(currTroopCountBuff), 171);

    fpSavegame.seekg(GEN_N_ACTION);
    fpSavegame.read(reinterpret_cast<char*>(nActionBuff), 171);

    fpSavegame.seekg(GEN_B_ACTION);
    fpSavegame.read(reinterpret_cast<char*>(bActionBuff), 171);

    fpSavegame.seekg(GEN_LIVES_BEF_SLAIN);
    fpSavegame.read(reinterpret_cast<char*>(livesBefSlainBuff), 171);

    fpSavegame.seekg(GEN_LIVES_BEF_SLAIN);
    fpSavegame.read(reinterpret_cast<char*>(livesBefSlainBuff), 171);

    fpSavegame.seekg(GEN_CURRENT_HP);
    fpSavegame.read(reinterpret_cast<char*>(currentHpBuffer), 171);

    fpSavegame.seekg(GEN_MAX_HP);
    fpSavegame.read(reinterpret_cast<char*>(maxHpBuffer), 171);

    fpSavegame.seekg(GEN_CURRENT_MP);
    fpSavegame.read(reinterpret_cast<char*>(currentMpBuffer), 171);

    fpSavegame.seekg(GEN_MAX_MP);
    fpSavegame.read(reinterpret_cast<char*>(maxMpBuffer), 171);

    fpSavegame.seekg(GEN_STRENGTH);
    fpSavegame.read(reinterpret_cast<char*>(strengthBuffer), 171);

    fpSavegame.seekg(GEN_DEFP);
    fpSavegame.read(reinterpret_cast<char*>(defpBuffer), 171);

    fpSavegame.seekg(GEN_ESCAPE_CHANCE);
    fpSavegame.read(reinterpret_cast<char*>(escChanceBuffer), 171);

    fpSavegame.seekg(GEN_COMMAND);
    fpSavegame.read(reinterpret_cast<char*>(commandBuffer), 171);

    fpSavegame.seekg(GEN_INTELLIGENCE);
    fpSavegame.read(reinterpret_cast<char*>(intellBuffer), 171);

    fpSavegame.seekg(GEN_LOYALTY);
    fpSavegame.read(reinterpret_cast<char*>(loyaltyBuffer), 171);

    fpSavegame.seekg(GEN_EQUIPPED_ITEM);
    fpSavegame.read(reinterpret_cast<char*>(equippedItemBuffer), 171);

    fpSavegame.seekg(GEN_DOMESTICS_STATUS);
    fpSavegame.read(reinterpret_cast<char*>(domesticStatusBuff), 342);

    fpSavegame.seekg(GEN_TOTAL_WINS);
    fpSavegame.read(reinterpret_cast<char*>(totalWinBuffer), 342);

    fpSavegame.seekg(GEN_TOTAL_LOSSES);
    fpSavegame.read(reinterpret_cast<char*>(totalLossBuffer), 342);

    fpSavegame.seekg(GEN_WINS_LAST_WEEK);
    fpSavegame.read(reinterpret_cast<char*>(winsLastWeekBuffer), 342);

    fpSavegame.seekg(GEN_LOSSES_LAST_WEEK);
    fpSavegame.read(reinterpret_cast<char*>(lossLastWeekBuffer), 342);

    fpSavegame.seekg(GEN_SOLD_AND_CAVA);
    fpSavegame.read(reinterpret_cast<char*>(soldCavaBuff), 171);

    fpSavegame.seekg(GEN_MAGE_AND_SAMU);
    fpSavegame.read(reinterpret_cast<char*>(mageSamuBuff), 171);

    fpSavegame.seekg(GEN_ARCH_AND_MONK);
    fpSavegame.read(reinterpret_cast<char*>(archMonkBuff), 171);

    fpSavegame.seekg(GEN_HARP_AND_BEAS);
    fpSavegame.read(reinterpret_cast<char*>(harpBeasBuff), 171);

    fpSavegame.seekg(GEN_DRAG_AND_ZOMB);
    fpSavegame.read(reinterpret_cast<char*>(dragZombBuff), 171);

    fpSavegame.seekg(GEN_CURR_EXP);
    fpSavegame.read(reinterpret_cast<char*>(currExpBuffer), 342);

    fpSavegame.seekg(GEN_NEW_MERITS);
    fpSavegame.read(reinterpret_cast<char*>(newMeritsBuffer), 342);

    fpSavegame.seekg(GEN_OLD_MERITS);
    fpSavegame.read(reinterpret_cast<char*>(oldMeritsBuffer), 342);

    fpSavegame.seekg(GEN_HOSPITAL);
    fpSavegame.read(reinterpret_cast<char*>(hospitalBuff), 342);

    fpSavegame.seekg(GEN_BTL_ACTION);
    fpSavegame.read(reinterpret_cast<char*>(btlActionBuff), 171);

    fpSavegame.seekg(GEN_MORAL);
    fpSavegame.read(reinterpret_cast<char*>(moralBuff), 171);

    fpSavegame.seekg(GEN_WARLIKE);
    fpSavegame.read(reinterpret_cast<char*>(warlikeBuff), 171);

    fpSavegame.seekg(GEN_NEGO);
    fpSavegame.read(reinterpret_cast<char*>(negoBuff), 342);

    fpSavegame.seekg(GEN_ATK_PLUS);
    fpSavegame.read(reinterpret_cast<char*>(atkPlusBuff), 171);

    fpSavegame.seekg(GEN_SPELL_TIER);
    fpSavegame.read(reinterpret_cast<char*>(spellTierBuffer), 171);

    fpSavegame.seekg(GEN_DEF_PLUS);
    fpSavegame.read(reinterpret_cast<char*>(defPlusBuff), 171);

    fpSavegame.seekg(GEN_DEF_SWORD);
    fpSavegame.read(reinterpret_cast<char*>(defSwordBuff), 342);

    fpSavegame.seekg(GEN_DEF_ICE);
    fpSavegame.read(reinterpret_cast<char*>(defIceBuff), 342);

    fpSavegame.seekg(GEN_DEF_FIRE);
    fpSavegame.read(reinterpret_cast<char*>(defFireBuff), 342);

    fpSavegame.seekg(GEN_DEF_LIGHT);
    fpSavegame.read(reinterpret_cast<char*>(defLightBuff), 342);

    fpSavegame.seekg(GEN_DEF_DARK);
    fpSavegame.read(reinterpret_cast<char*>(defDarkBuff), 342);

    fixTwoByteGeneralsArrays();

    return;
}

void FileReader::readCastlesInfo(void)
{
    fpSavegame.seekg(CASTLE_OWNERSHIP);
    fpSavegame.read(reinterpret_cast<char*>(castleOwnership), 34);

    fpSavegame.seekg(CASTLE_CURR_TROOPS);
    fpSavegame.read(reinterpret_cast<char*>(castleCurrentTroops), 68);

    fpSavegame.seekg(CASTLE_EXPERIENCE);
    fpSavegame.read(reinterpret_cast<char*>(castleExperience), 68);

    fixTwoByteCastlesArrays();

    return;
}

void FileReader::readDivisionsInfo(void)
{
    fpSavegame.seekg(DIVISION_STATUS);
    fpSavegame.read(reinterpret_cast<char*>(divisionStatus), 171);

    fpSavegame.seekg(DIVISION_LIST);
    fpSavegame.read(reinterpret_cast<char*>(activeArmies), 171);

    fpSavegame.seekg(DIVISION_ORIGIN);
    fpSavegame.read(reinterpret_cast<char*>(divisionOrigin), 171);

    fpSavegame.seekg(DIVISION_DESTINATION);
    fpSavegame.read(reinterpret_cast<char*>(divisionDestination), 171);

    fpSavegame.seekg(DIVISION_PREVIOUS);
    fpSavegame.read(reinterpret_cast<char*>(divisionPrevious), 171);

    fpSavegame.seekg(DIVISION_NEXT);
    fpSavegame.read(reinterpret_cast<char*>(divisionNext), 171);

    fpSavegame.seekg(DIVISION_X_COORD);
    fpSavegame.read(reinterpret_cast<char*>(divisionXcoordinate), 342);

    fpSavegame.seekg(DIVISION_Y_COORD);
    fpSavegame.read(reinterpret_cast<char*>(divisionYcoordinate), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_1);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown1Buff), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_2);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown2Buff), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_3);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown3Buff), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_4);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown4Buff), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_5);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown5Buff), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_6);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown6Buff), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_7);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown7Buff), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_8);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown8Buff), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_9);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown9Buff), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_A);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown10Buff), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_B);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown11Buff), 342);

    fpSavegame.seekg(DIVISION_UNKNOWN_C);
    fpSavegame.read(reinterpret_cast<char*>(divisionUnknown12Buff), 342);

    fixTwoByteDivisionsArrays();
    
    return;
}

void FileReader::fixTwoByteGeneralsArrays(void)
{
    for(int i = 0; i < 171; i++)
    {
        currExpBuffer[i]      = g_rotateLeft(currExpBuffer[i], 8);
        totalWinBuffer[i]     = g_rotateLeft(totalWinBuffer[i], 8);
        totalLossBuffer[i]    = g_rotateLeft(totalLossBuffer[i], 8);
        winsLastWeekBuffer[i] = g_rotateLeft(winsLastWeekBuffer[i], 8);
        lossLastWeekBuffer[i] = g_rotateLeft(lossLastWeekBuffer[i], 8);
        newMeritsBuffer[i]    = g_rotateLeft(newMeritsBuffer[i], 8);
        oldMeritsBuffer[i]    = g_rotateLeft(oldMeritsBuffer[i], 8);
        hospitalBuff[i]       = g_rotateLeft(hospitalBuff[i], 8);
        negoBuff[i]           = g_rotateLeft(negoBuff[i], 8);
        locationNumBuff[i]    = g_rotateLeft(locationNumBuff[i], 8);
        domesticStatusBuff[i] = g_rotateLeft(domesticStatusBuff[i], 8);
        defSwordBuff[i]       = g_rotateLeft(defSwordBuff[i], 8);
        defIceBuff[i]         = g_rotateLeft(defIceBuff[i], 8);
        defFireBuff[i]        = g_rotateLeft(defFireBuff[i], 8);
        defLightBuff[i]       = g_rotateLeft(defLightBuff[i], 8);
        defDarkBuff[i]        = g_rotateLeft(defDarkBuff[i], 8);
    }
    
    return;
}

void FileReader::fixTwoByteCastlesArrays(void)
{
    for(int i = 0; i < 34; i++)
    {
        castleCurrentTroops[i] = g_rotateLeft(castleCurrentTroops[i], 8);
        castleExperience[i]    = g_rotateLeft(castleExperience[i], 8);
    }
        
    return;
}

void FileReader::fixTwoByteDivisionsArrays (void)
{
    for(int i = 0; i < 171; i++)
    {
        divisionXcoordinate[i]   = g_rotateLeft(divisionXcoordinate[i], 8);
        divisionYcoordinate[i]   = g_rotateLeft(divisionYcoordinate[i], 8);
        divisionUnknown1Buff[i]  = g_rotateLeft(divisionUnknown1Buff[i], 8);
        divisionUnknown2Buff[i]  = g_rotateLeft(divisionUnknown2Buff[i], 8);
        divisionUnknown3Buff[i]  = g_rotateLeft(divisionUnknown3Buff[i], 8);
        divisionUnknown4Buff[i]  = g_rotateLeft(divisionUnknown4Buff[i], 8);
        divisionUnknown5Buff[i]  = g_rotateLeft(divisionUnknown5Buff[i], 8);
        divisionUnknown6Buff[i]  = g_rotateLeft(divisionUnknown6Buff[i], 8);
        divisionUnknown7Buff[i]  = g_rotateLeft(divisionUnknown7Buff[i], 8);
        divisionUnknown8Buff[i]  = g_rotateLeft(divisionUnknown8Buff[i], 8);
        divisionUnknown9Buff[i]  = g_rotateLeft(divisionUnknown9Buff[i], 8);
        divisionUnknown10Buff[i] = g_rotateLeft(divisionUnknown10Buff[i], 8);
        divisionUnknown11Buff[i] = g_rotateLeft(divisionUnknown11Buff[i], 8);
        divisionUnknown12Buff[i] = g_rotateLeft(divisionUnknown12Buff[i], 8);
    }

    return;
}
