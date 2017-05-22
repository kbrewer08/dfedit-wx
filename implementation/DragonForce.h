#ifndef DRAGONFORCE_H
#define DRAGONFORCE_H

class DragonForce;
typedef unsigned short ushort;
typedef unsigned char uchar;

#ifndef UNICODE
#define UNICODE
#endif
/*
#ifndef _UNICODE
#define _UNICODE
#endif
*/
#include <cstdio>
#include <cstdlib>
#include <string>

#include "General.h"
#include "Castle.h"
#include "Division.h"
#include "FileReader.h"
#include "FileWriter.h"

#define FILE_00 "DR_FORCE_00.bin"
#define FILE_01 "DR_FORCE_01.bin"
#define FILE_02 "DR_FORCE_02.bin"
#define FILE_03 "DR_FORCE_03.bin"
#define FILE_04 "DR_FORCE_04.bin"

//Save file offset table

#define PLAYING_AS 0x0              // seems to max out at 6 bytes for the name.
#define GAME_YEAR 0x30              // two bytes. the current "year" in the game, starting from 1.
#define GAME_MONTH 0x32             // two bytes. the current "month" in the game, starting from 1.
#define GAME_WEEK 0x34              // two bytes. the current "week" in the game, starting from 1.

#define AWARDS_LEFT 0x44F0          // this is where the number of awards you have to give out is stored, two bytes. max is 999

#define FIELD_STATUS_1 0x3C         //   3C to   E6, one byte each.  (   60 to   230)
#define GEN_OFFICER_OWNERSHIP 0xE8  //   E8 to  192, one byte each.  (  232 to   402)
#define FIELD_STATUS_2 0x194        //  194 to  23E, one byte each.  (  404 to   574)
#define GEN_LEVEL 0x240             //  240 to  2EA, one byte each.  (  576 to   746) max 50
#define GEN_CLASS 0x2EC             //  2EC to  396, one byte each.  (  748 to   918)
#define GEN_LOCATION 0x398          //  398 to  4ED, two bytes each. (  920 to  1261)
#define GEN_TROOP_TYPE 0x4EE        //  4EE to  598, one byte each.  ( 1262 to  1432)
#define GEN_CURR_TROOP_COUNT 0x59A  //  59A to  644, one byte each.  ( 1434 to  1604)
#define GEN_N_ACTION 0x646          //  646 to  6F0, one byte each.  ( 1606 to  1776) ???
#define GEN_B_ACTION 0x6F2          //  6F2 to  79C, one byte each.  ( 1778 to  1948) ???
#define GEN_LIVES_BEF_SLAIN 0x79E   //  79E to  848, one byte each.  ( 1950 to  2120)
#define GEN_CURRENT_HP 0x84A        //  84A to  8F4, one byte each.  ( 2122 to  2292)
#define GEN_MAX_HP 0x8F6            //  8F6 to  9A0, one byte each.  ( 2294 to  2464)
#define GEN_CURRENT_MP 0x9A2        //  9A2 to  A4C, one byte each.  ( 2466 to  2636)
#define GEN_MAX_MP 0xA4E            //  A4E to  AF8, one byte each.  ( 2638 to  2808)
#define GEN_STRENGTH 0xAFA          //  AFA to  BA4, one byte each.  ( 2810 to  2980)
#define GEN_DEFP 0xBA6              //  BA6 to  C50, one byte each.  ( 2982 to  3152)
#define GEN_ESCAPE_CHANCE 0xC52     //  C52 to  CFC, one byte each.  ( 3154 to  3324)
#define GEN_COMMAND 0xCFE           //  CFE to  DA8, one byte each.  ( 3326 to  3496)
#define GEN_INTELLIGENCE 0xDAA      //  DAA to  E54, one byte each.  ( 3498 to  3668)
#define GEN_LOYALTY 0xE56           //  E56 to  F00, one byte each.  ( 3670 to  3840)
#define GEN_EQUIPPED_ITEM 0xF02     //  F02 to  FAC, one byte each.  ( 3842 to  4012)
#define GEN_DOMESTICS_STATUS 0xFAE  //  FAE to 1102, two bytes each. ( 4014 to  4354)
/* This has multiple uses: 
   uppper half of upper byte - recent award: 15 if no, 7 if yes.
   lower half of upper byte  - search/fortify status: bit 3 is 1 = can still do, 0 = already done
   lower byte                - this is the "Face" value
*/

#define GEN_TOTAL_WINS 0x1104       // 1104 to 1258, two bytes each. ( 4356 to  4696)
#define GEN_TOTAL_LOSSES 0x125A     // 125A to 13AE, two bytes each. ( 4698 to  5038)
#define GEN_WINS_LAST_WEEK 0x13B0   // 13B0 to 1504, two bytes each. ( 5040 to  5380)
#define GEN_LOSSES_LAST_WEEK 0x1506 // 1506 to 165A, two bytes each. ( 5382 to  5722)
#define GEN_SOLD_AND_CAVA 0x165C    // 165C to 1706, one byte each.  ( 5724 to  5894)
#define GEN_MAGE_AND_SAMU 0x1708    // 1708 to 17B2, one byte each.  ( 5896 to  6066)
#define GEN_ARCH_AND_MONK 0x17B4    // 17B4 to 185E, one byte each.  ( 6068 to  6238)
#define GEN_HARP_AND_BEAS 0x1860    // 1860 to 190A, one byte each.  ( 6240 to  6410)
#define GEN_DRAG_AND_ZOMB 0x190C    // 190C to 19B6, one byte each.  ( 6412 to  6582)
#define GEN_CURR_EXP 0x19B8         // 19B8 to 1B0C, two bytes each. ( 6584 to  6924) max is whatever level 50 is. Max value in game is 65535 (0xFFFF)
#define GEN_NEW_MERITS 0x1B0E       // 1B0E to 1C62, two bytes each. ( 6926 to  7266)
#define GEN_OLD_MERITS 0x1C64       // 1C64 to 1DB8, two bytes each. ( 7268 to  7608)
#define GEN_HOSPITAL 0x1DBA         // 1DBA to 1F0E, two bytes each. ( 7610 to  7950)
#define GEN_BTL_ACTION 0x1F10       // 1F10 to 1FBA, one byte each.  ( 7952 to  8122) ???
#define GEN_MORAL 0x1FBC            // 1FBC to 2066, one byte each.  ( 8124 to  8294) ???
#define GEN_WARLIKE 0x2068          // 2068 to 2112, one byte each.  ( 8296 to  8466) ???
#define GEN_NEGO 0x2114             // 2114 to 2268, two bytes each. ( 8468 to  8808) ???
#define GEN_ATK_PLUS 0x226A         // 226A to 2314, one byte each.  ( 8810 to  8980) ???
#define GEN_SPELL_TIER 0x2316       // 2316 to 23C0, one byte each.  ( 8982 to  9152)
#define GEN_DEF_PLUS 0x23C2         // 23C2 to 246C, one byte each.  ( 9154 to  9324) ???
#define GEN_DEF_SWORD 0x246E        // 246E to 25C2, two bytes each. ( 9326 to  9666)
#define GEN_DEF_ICE 0x25C4          // 25C4 to 2718, two bytes each. ( 9668 to 10008)
#define GEN_DEF_FIRE 0x271A         // 271A to 286E, two bytes each. (10010 to 10350)
#define GEN_DEF_LIGHT 0x2870        // 2870 to 29C4, two bytes each. (10352 to 10692)
#define GEN_DEF_DARK 0x29C6         // 29C6 to 2B1A, two bytes each. (10694 to 11034)

#define DIVISION_STATUS 0x2B1C      // 2B1C to 2BC6, one byte each.  (11036 to 11206)
#define DIVISION_ORIGIN 0x2BC8      // 2BC8 to 2BE0, one byte each.  (11208 to 11232)
#define DIVISION_DESTINATION 0x2C74 // 2C74 to 2C8C, one byte each.  (11380 to 11404)
#define DIVISION_PREVIOUS 0x2D20    // 2D20 to 2D38, one byte each.  (11552 to 11576)
#define DIVISION_NEXT 0x2DCC        // 2DCC to 2DE4, one byte each.  (11724 to 11748)
#define DIVISION_LIST 0x2E78        // 2E78 to 2E90, one byte each.  (11896 to 11920)
#define DIVISION_X_COORD 0x2F24     // 2F24 to 2F54, two bytes each. (12068 to 12116)
#define DIVISION_Y_COORD 0x307A     // 307A to 30AA, two bytes each. (12410 to 12458)
#define DIVISION_UNKNOWN_1 0x31D0   // 31D0
#define DIVISION_UNKNOWN_2 0x3326   // 3326
#define DIVISION_UNKNOWN_3 0x347C   // 347C
#define DIVISION_UNKNOWN_4 0x35D2   // 35D2
#define DIVISION_UNKNOWN_5 0x3728   // 3728
#define DIVISION_UNKNOWN_6 0x387E   // 387E
#define DIVISION_UNKNOWN_7 0x39D4   // 39D4
#define DIVISION_UNKNOWN_8 0x3B2A   // 3B2A
#define DIVISION_UNKNOWN_9 0x3C80   // 3C80
#define DIVISION_UNKNOWN_A 0x3DD6   // 3DD6
#define DIVISION_UNKNOWN_B 0x3F2C   // 3F2C
#define DIVISION_UNKNOWN_C 0x4082   // 4082

#define CASTLE_OWNERSHIP 0x41D8     // 41D8 to 41F9, one byte each.  (16856 to 16889)
#define CASTLE_EXPERIENCE 0x4200    // 4200 to 4242, two bytes each. (16896 to 16962)
#define CASTLE_CURR_TROOPS 0x4250   // 4250 to 4292, two bytes each. (16972 to 17042)
#define ITEM_INVENTORY 0x42F0       // 42F0 to 44EF, two bytes each. (17136 to 17647)

using namespace std;

extern string gPlayingAs;
extern char   playingAs_cstr[5];
extern ushort gameYear;
extern ushort gameMonth;
extern ushort gameWeek;

extern ushort itemInventoryBuffer[256];

extern const char monarchFilename[8][5];

extern ushort awardsLeft;

extern const char  generalsNameList[171][12];
extern const char  classType[15][12];
extern const char  troopType[11][9];
extern const char* genStatusArray[7][3];
extern const char  castlesNameList[35][9];
extern       int   locationCoordinates[113][2];
extern const char  locationList[114][26];
extern const char  itemList[73][18];
extern const char  shidanStatus[28][14];

extern uchar  FsBuffer1[171];
extern uchar  officerOwner[171];
extern uchar  FsBuffer2[171];
extern uchar  levelBuffer[171];
extern uchar  classBuffer[171];
extern ushort locationNumBuff[171];
extern uchar  troopTypeBuff[171];
extern uchar  currTroopCountBuff[171];
extern uchar  nActionBuff[171];
extern uchar  bActionBuff[171];
extern uchar  livesBefSlainBuff[171];
extern uchar  currentHpBuffer[171];
extern uchar  maxHpBuffer[171];
extern uchar  currentMpBuffer[171];
extern uchar  maxMpBuffer[171];
extern uchar  strengthBuffer[171];
extern uchar  defpBuffer[171];
extern uchar  escChanceBuffer[171];
extern uchar  commandBuffer[171];
extern uchar  intellBuffer[171];
extern uchar  loyaltyBuffer[171];
extern uchar  equippedItemBuffer[171];
extern ushort domesticStatusBuff[171];
extern ushort totalWinBuffer[171];
extern ushort totalLossBuffer[171];
extern ushort winsLastWeekBuffer[171];
extern ushort lossLastWeekBuffer[171];
extern uchar  soldCavaBuff[171];
extern uchar  mageSamuBuff[171];
extern uchar  archMonkBuff[171];
extern uchar  harpBeasBuff[171];
extern uchar  dragZombBuff[171];
extern ushort currExpBuffer[171];
extern ushort newMeritsBuffer[171];
extern ushort oldMeritsBuffer[171];
extern ushort hospitalBuff[171];
extern uchar  btlActionBuff[171];
extern uchar  moralBuff[171];
extern uchar  warlikeBuff[171];
extern ushort negoBuff[171];
extern uchar  atkPlusBuff[171];
extern uchar  spellTierBuffer[171];
extern uchar  defPlusBuff[171];
extern ushort defSwordBuff[171];
extern ushort defIceBuff[171];
extern ushort defFireBuff[171];
extern ushort defLightBuff[171];
extern ushort defDarkBuff[171];

extern uchar  castleOwnership[34];
extern ushort castleCurrentTroops[34];
extern ushort castleExperience[34];
extern ushort castleLevel[34];

extern int activeDivisions[171];

extern uchar  divisionStatus[171];
extern uchar  activeArmies[171];
extern uchar  divisionOrigin[171];
extern uchar  divisionDestination[171];
extern uchar  divisionPrevious[171];
extern uchar  divisionNext[171];
extern ushort divisionXcoordinate[171];
extern ushort divisionYcoordinate[171];

extern ushort divisionUnknown1Buff[171];
extern ushort divisionUnknown2Buff[171];
extern ushort divisionUnknown3Buff[171];
extern ushort divisionUnknown4Buff[171];
extern ushort divisionUnknown5Buff[171];
extern ushort divisionUnknown6Buff[171];
extern ushort divisionUnknown7Buff[171];
extern ushort divisionUnknown8Buff[171];
extern ushort divisionUnknown9Buff[171];
extern ushort divisionUnknown10Buff[171];
extern ushort divisionUnknown11Buff[171];
extern ushort divisionUnknown12Buff[171];

typedef struct
{
    int holdArea[171];
    int numHeld;
} CAPTIVE_HOLDER;

typedef struct //for kingdoms status information
{
    string kingdomName;
    string kingdomRuler;
    int    numCastles;
    int    numGenerals;
    int    numCaptives;
    int    ownedCastles[34];
    int    ownedGenerals[171];
    int    ownedCaptives[171];
    int    kingdomWins;
    int    kingdomLosses;
} KINGDOM;

typedef struct //for Item Inventory
{
    int items[256];
    int numItems;
} ITEM_INVENT;

////////////////////////////////////////////////////////////////////////////////
//
// DragonForce class declaration
//
////////////////////////////////////////////////////////////////////////////////

class DragonForce
{
public:
    string drFileName;
    int playingAs;

    FileReader fr;
    FileWriter fw;

    General  genArr[171];
    Castle   casArr[34];
    Division divArr[171];
    KINGDOM  kingdoms[8];
    
    ITEM_INVENT itemInv;

    CAPTIVE_HOLDER capHolder;
    
    DragonForce (void) : drFileName(""), playingAs(-1), genArr(), casArr(), divArr(), kingdoms(), itemInv(), capHolder() {}
    DragonForce (char savefileName[]) : drFileName(savefileName), fr(savefileName) {}
    ~DragonForce(void) {}

    DragonForce(const DragonForce& rhsDF);
    DragonForce& operator=(const DragonForce& rhsDF);

    void setMonarch    (void);
    void initGenerals  (void);
    void initCastles   (void);
    void initDivisions (void);
    void initItemInv   (void);
    void initKingdoms  (void);
    void findActiveDiv (void);
    void findNewRulers (const int oldRuler);
    void addItemsInv   (const int* const items, const int count);
    void delItemsInv   (const int* const items, const int count);
};

extern DragonForce dr;

////////////////////////////////////////////////////////////////////////////////
//
// Global Program Functions
//
////////////////////////////////////////////////////////////////////////////////

void g_insertionSort( int* const arr, const int size );

ushort g_packByte   (ushort highNibble, ushort lowNibble);
ushort g_rotateLeft (ushort num, const int bits); // listing 12 at this link for endian-independent code http://www.ibm.com/developerworks/aix/library/au-endianc/

#endif
