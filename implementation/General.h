#ifndef GENERAL_H
#define GENERAL_H

#include <iostream>
#include <string>

#include "DragonForce.h"

using namespace std;

class General
{
public:
    int    listIndex;
    int    isPlayer;
    string name;
    string owner;
    int    fieldStatus1;
    int    fieldStatus2;
    int    level;
    int    classType;
    int    fixedLocation; //true/false 1/0
    int    location;
    int    troopIndex;
    string troopType;
    int    currentTroopCount;
    int    nAction;
    int    bAction;
    int    livesLeft;
    int    currentHP;
    int    maxHP;
    int    currentMP;
    int    maxMP;
    int    strength;
    int    defp;
    int    escapeChance;
    int    command;
    int    intelligence;
    int    loyalty;
    int    equippedItem;
    int    portrait;
    int    naisei;
    int    domesticsMedal; //status for if they were given a medal this week
    int    domesticsSF;    //status for searched or fortified this week
    int    newWins;
    int    newLosses;
    int    oldWins;
    int    oldLosses;
    ushort soldierCavalry;
    ushort mageSamurai;
    ushort archerMonk;
    ushort harpyBeast;
    ushort dragonZombie;
    int    currentExp;
    int    newMerits;
    int    oldMerits;
    int    hospital;
    int    btlAction;
    int    moral;
    int    warlike;
    int    nego;
    int    atkPlus;
    int    spellTier;
    int    defPlus;
    int    defSword;
    int    defIce;
    int    defFire;
    int    defLight;
    int    defDark;
    ushort troopMedals[11];
    bool   needsUpdate;

//Constructors, Destructors
    General  (void) {}
    General  (int i);
    ~General (void) {}
    
    General(const General& rhsGen);
    General& operator=(const General& rhsGen);

    string getLocation (void);
    string getStatus   (void);
    string getClass    (void);
    string getOwner    (void);

    int isPlayerMonarch(void) const {return isPlayer;}
    
    int  editOneByteStat        (const int min, const int max, const int newStat, const int fileOffset, int* stat, uchar* statBuffer);
    int  editTwoByteStat        (const int min, const int max, const int newStat, const int fileOffset, int* stat, ushort* statBuffer);
    int  editMedals             (ushort newMedalCount, int troopTypeToChange, ushort* packedMedalToChange, int nibbleToChange, int highNibble, int lowNibble, int fileOffset);
    int  changeGenTroopType     (const ushort newGenTroopType);
    int  changeGenOwner         (const int newOwner);

    int  setSearchFortifyStatus (const bool setNaisei);
    void setStatus              (const int fs1, const int fs2);
    void setLocation            (const int locType, const int newLoc);
    void setOwner               (const int newOwner);
    void setTroopCount          (const int newTroopCount);
    int  changeLocation         (const int destLocType, const int destStatusType, const int newLoc);
    void hide                   (void);
};

#endif
