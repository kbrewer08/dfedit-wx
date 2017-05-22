#include "DragonForce.h"

General::General(int i)
{
    listIndex         = i;
    isPlayer          = (listIndex == dr.playingAs) ? 1 : 0;
    name              = generalsNameList[i];
    owner             = generalsNameList[officerOwner[i]];
    fieldStatus1      = FsBuffer1[i];
    fieldStatus2      = FsBuffer2[i];
    level             = levelBuffer[i] + 1;
    classType         = classBuffer[i];
    if((locationNumBuff[i] >> 15) & 1)
        fixedLocation = 1; //meaning, they're not in an army
    else
        fixedLocation = 0; //they are part of an army
    location          = locationNumBuff[i] & 0x00FF; //only the low byte is important here
    troopIndex        = troopTypeBuff[i];
    troopType         = troopType[troopTypeBuff[i]];
    currentTroopCount = currTroopCountBuff[i];
    nAction           = nActionBuff[i];
    bAction           = bActionBuff[i];
    livesLeft         = livesBefSlainBuff[i];
    currentHP         = currentHpBuffer[i];
    maxHP             = maxHpBuffer[i];
    currentMP         = currentMpBuffer[i];
    maxMP             = maxMpBuffer[i];
    strength          = strengthBuffer[i];
    defp              = defpBuffer[i];
    escapeChance      = escChanceBuffer[i];
    command           = commandBuffer[i];
    intelligence      = intellBuffer[i];
    loyalty           = loyaltyBuffer[i];
    equippedItem      = equippedItemBuffer[i];
    portrait          = domesticStatusBuff[i] & 0x00FF;
    naisei            = domesticStatusBuff[i] >> 8;
    domesticsMedal    = (domesticStatusBuff[i] >> 12) & 0xF;
    domesticsSF       = (domesticStatusBuff[i] >> 8) & 0x0F;
    newWins           = totalWinBuffer[i];
    newLosses         = totalLossBuffer[i];
    oldWins           = winsLastWeekBuffer[i];
    oldLosses         = lossLastWeekBuffer[i];
    soldierCavalry    = soldCavaBuff[i];
    mageSamurai       = mageSamuBuff[i];
    archerMonk        = archMonkBuff[i];
    harpyBeast        = harpBeasBuff[i];
    dragonZombie      = dragZombBuff[i];
    currentExp        = currExpBuffer[i];
    newMerits         = newMeritsBuffer[i];
    oldMerits         = oldMeritsBuffer[i];
    hospital          = hospitalBuff[i];
    btlAction         = btlActionBuff[i];
    moral             = moralBuff[i];
    warlike           = warlikeBuff[i];
    nego              = negoBuff[i];
    atkPlus           = atkPlusBuff[i];
    spellTier         = spellTierBuffer[i];
    defPlus           = defPlusBuff[i];
    defSword          = defSwordBuff[i];
    defIce            = defIceBuff[i];
    defFire           = defFireBuff[i];
    defLight          = defLightBuff[i];
    defDark           = defDarkBuff[i];

    troopMedals[0]  = 0;
    troopMedals[1]  = soldierCavalry >> 4;
    troopMedals[2]  = soldierCavalry & 0x0F;
    troopMedals[3]  = mageSamurai >> 4;
    troopMedals[4]  = mageSamurai & 0x0F;
    troopMedals[5]  = archerMonk >> 4;
    troopMedals[6]  = archerMonk & 0x0F;
    troopMedals[7]  = harpyBeast >> 4;
    troopMedals[8]  = harpyBeast & 0x0F;
    troopMedals[9]  = dragonZombie >> 4;
    troopMedals[10] = dragonZombie & 0x0F;
    
    for(int j = 0; j < 11; j++)
        if(troopMedals[j] > 10)
            troopMedals[j] = 0;

    needsUpdate = false;
}

General::General(const General& rhsGen)
{
    listIndex         = rhsGen.listIndex;
    isPlayer          = rhsGen.isPlayer;
    name              = rhsGen.name;
    owner             = rhsGen.owner;
    fieldStatus1      = rhsGen.fieldStatus1;
    fieldStatus2      = rhsGen.fieldStatus2;
    level             = rhsGen.level;
    classType         = rhsGen.classType;
    fixedLocation     = rhsGen.fixedLocation;
    location          = rhsGen.location;
    troopIndex        = rhsGen.troopIndex;
    troopType         = rhsGen.troopType;
    currentTroopCount = rhsGen.currentTroopCount;
    nAction           = rhsGen.nAction;
    bAction           = rhsGen.bAction;
    livesLeft         = rhsGen.livesLeft;
    currentHP         = rhsGen.currentHP;
    maxHP             = rhsGen.maxHP;
    currentMP         = rhsGen.currentMP;
    maxMP             = rhsGen.maxMP;
    strength          = rhsGen.strength;
    defp              = rhsGen.defp;
    escapeChance      = rhsGen.escapeChance;
    command           = rhsGen.command;
    intelligence      = rhsGen.intelligence;
    loyalty           = rhsGen.loyalty;
    equippedItem      = rhsGen.equippedItem;
    portrait          = rhsGen.portrait;
    naisei            = rhsGen.naisei;
    domesticsMedal    = rhsGen.domesticsMedal;
    domesticsSF       = rhsGen.domesticsSF;
    newWins           = rhsGen.newWins;
    newLosses         = rhsGen.newLosses;
    oldWins           = rhsGen.oldWins;
    oldLosses         = rhsGen.oldLosses;
    soldierCavalry    = rhsGen.soldierCavalry;
    mageSamurai       = rhsGen.mageSamurai;
    archerMonk        = rhsGen.archerMonk;
    harpyBeast        = rhsGen.harpyBeast;
    dragonZombie      = rhsGen.dragonZombie;
    currentExp        = rhsGen.currentExp;
    newMerits         = rhsGen.newMerits;
    oldMerits         = rhsGen.oldMerits;
    hospital          = rhsGen.hospital;
    btlAction         = rhsGen.btlAction;
    moral             = rhsGen.moral;
    warlike           = rhsGen.warlike;
    nego              = rhsGen.nego;
    atkPlus           = rhsGen.atkPlus;
    spellTier         = rhsGen.spellTier;
    defPlus           = rhsGen.defPlus;
    defSword          = rhsGen.defSword;
    defIce            = rhsGen.defIce;
    defFire           = rhsGen.defFire;
    defLight          = rhsGen.defLight;
    defDark           = rhsGen.defDark;

    for(int i = 0; i < 11; i++)
        troopMedals[i] = rhsGen.troopMedals[i];

    needsUpdate = rhsGen.needsUpdate;
}

General& General::operator=(const General& rhsGen)
{
    if(this == &rhsGen)
        return *this;

    listIndex         = rhsGen.listIndex;
    isPlayer          = rhsGen.isPlayer;
    name              = rhsGen.name;
    owner             = rhsGen.owner;
    fieldStatus1      = rhsGen.fieldStatus1;
    fieldStatus2      = rhsGen.fieldStatus2;
    level             = rhsGen.level;
    classType         = rhsGen.classType;
    fixedLocation     = rhsGen.fixedLocation;
    location          = rhsGen.location;
    troopIndex        = rhsGen.troopIndex;
    troopType         = rhsGen.troopType;
    currentTroopCount = rhsGen.currentTroopCount;
    nAction           = rhsGen.nAction;
    bAction           = rhsGen.bAction;
    livesLeft         = rhsGen.livesLeft;
    currentHP         = rhsGen.currentHP;
    maxHP             = rhsGen.maxHP;
    currentMP         = rhsGen.currentMP;
    maxMP             = rhsGen.maxMP;
    strength          = rhsGen.strength;
    defp              = rhsGen.defp;
    escapeChance      = rhsGen.escapeChance;
    command           = rhsGen.command;
    intelligence      = rhsGen.intelligence;
    loyalty           = rhsGen.loyalty;
    equippedItem      = rhsGen.equippedItem;
    portrait          = rhsGen.portrait;
    naisei            = rhsGen.naisei;
    domesticsMedal    = rhsGen.domesticsMedal;
    domesticsSF       = rhsGen.domesticsSF;
    newWins           = rhsGen.newWins;
    newLosses         = rhsGen.newLosses;
    oldWins           = rhsGen.oldWins;
    oldLosses         = rhsGen.oldLosses;
    soldierCavalry    = rhsGen.soldierCavalry;
    mageSamurai       = rhsGen.mageSamurai;
    archerMonk        = rhsGen.archerMonk;
    harpyBeast        = rhsGen.harpyBeast;
    dragonZombie      = rhsGen.dragonZombie;
    currentExp        = rhsGen.currentExp;
    newMerits         = rhsGen.newMerits;
    oldMerits         = rhsGen.oldMerits;
    hospital          = rhsGen.hospital;
    btlAction         = rhsGen.btlAction;
    moral             = rhsGen.moral;
    warlike           = rhsGen.warlike;
    nego              = rhsGen.nego;
    atkPlus           = rhsGen.atkPlus;
    spellTier         = rhsGen.spellTier;
    defPlus           = rhsGen.defPlus;
    defSword          = rhsGen.defSword;
    defIce            = rhsGen.defIce;
    defFire           = rhsGen.defFire;
    defLight          = rhsGen.defLight;
    defDark           = rhsGen.defDark;

    for(int i = 0; i < 11; i++)
        troopMedals[i] = rhsGen.troopMedals[i];

    needsUpdate = rhsGen.needsUpdate;

    return *this;
}

int General::changeGenOwner(const int newOwner)
{
    if(!isPlayer){
        if(dr.fw.writeGenOwner(newOwner, listIndex)){
            officerOwner[listIndex] = newOwner;
            return 1;
        } else {
            return 0;
        }
    } else {
        return -1;
    }

    return 0;
}

int General::editOneByteStat(const int min, const int max, const int newStat, const int fileOffset, int* stat, uchar* statBuffer)
{
    int ns      = newStat;
    int success = 0;

    if(ns < min || ns > max)
        success = -1;
    else
    {
        if(dr.fw.writeOneElementToFile(fileOffset, 1, ns, listIndex))
        {
            if(statBuffer == levelBuffer) //I forget why this is necessary, need to investigate ---> UPDATE; apparently because I subtract by one in the function call for some reason...
                ns++;
            *stat = ns;
            statBuffer[listIndex] = (uchar)ns;
            success = 1;
        }
        else
            success = -2;
    }

    return success;
}

int General::editTwoByteStat(const int min, const int max, const int newStat, const int fileOffset, int* stat, ushort* statBuffer)
{
    int success = 0;

    if(newStat < min || newStat > max)
        success = -1;
    else
    {
        if(dr.fw.writeOneElementToFile(fileOffset, 2, newStat, listIndex))
        {
            *stat = newStat;
            statBuffer[listIndex] = (ushort)newStat;
            success = 1;
        }
        else
            success = -2;
    }

    return success;
}

int General::editMedals(ushort newMedalCount, int troopTypeToChange, ushort* packedMedalToChange, int nibbleToChange, int highNibble, int lowNibble, int fileOffset)
{
    int success;
    ushort newPackedMedalByte; //this is what ultimately gets written to the file. It stores two pieces of information in one byte.

    success            = 0;
    newPackedMedalByte = 0;

//if the new medal count is lower than the old one, and this is the current troop type, the current troops need to be adjusted to what the new max is. 
    if((troopIndex == troopTypeToChange) && 
       (newMedalCount < troopMedals[troopTypeToChange]) && 
       (currentTroopCount > newMedalCount * 10))
    {
        setTroopCount(newMedalCount * 10);
    }

//0 means no medals, i.e. non-existent. Game represents this as F, rather than 0. 
    if((nibbleToChange == 1) && highNibble == 0) //1 for low byte
        highNibble = 15;
    if((nibbleToChange == 2) && lowNibble == 0) //2 for low byte
        lowNibble = 15;

//packing two pieces of information into one byte
    if(nibbleToChange == 1)
        newPackedMedalByte = g_packByte(highNibble, newMedalCount);
    if(nibbleToChange == 2)
        newPackedMedalByte = g_packByte(newMedalCount, lowNibble);
//if the medals are set to zero, pack -1 (hex F) into that portion of the byte, since that's what the game uses for "non-existent"
    if(!newMedalCount)
    {
        newMedalCount = 15;
        if(nibbleToChange == 1)
            newPackedMedalByte = g_packByte(highNibble, newMedalCount);
        if(nibbleToChange == 2)
            newPackedMedalByte = g_packByte(newMedalCount, lowNibble);
        newMedalCount = 0;
    //if these are the currently selected troops, and medals are set to none, change current troop type to none
        if(troopIndex == troopTypeToChange)
        {
            dr.fw.writeOneElementToFile(GEN_TROOP_TYPE, 1, 0, listIndex);
            troopType = troopType[0];
            troopIndex = 0;
            troopTypeBuff[listIndex] = 0;
        }
    }
//finally, write the new value to the file and update the appropriate arrays.
    if(dr.fw.writeOneElementToFile(fileOffset, 1, newPackedMedalByte, listIndex))
    {
        *packedMedalToChange = newPackedMedalByte;
        troopMedals[troopTypeToChange] = newMedalCount;
        success = 1;
    }

    return success;
}

int General::changeGenTroopType(const ushort newGenTroopType)
{
    int success;
    int oldTroopType;

    success = 0;
    oldTroopType = troopIndex;

    if(newGenTroopType && (!(troopMedals[newGenTroopType])))//first condition makes sure you can set troop type to none when it obviously always has 0 medals
        return -1;
    
    if(troopMedals[newGenTroopType] < troopMedals[oldTroopType])
    {
        setTroopCount(troopMedals[newGenTroopType] * 10);
        success = 1;
    }

    if(dr.fw.writeOneElementToFile(GEN_TROOP_TYPE, 1, newGenTroopType, listIndex))
    {
        troopIndex               = newGenTroopType;
        troopTypeBuff[listIndex] = newGenTroopType;
        success                  = 1;
    }

    return success;
}

int General::setSearchFortifyStatus(const bool setNaisei)
{
    ushort newNaisei = 0;

    if(setNaisei) //they can't search or fortify this week
    {
        newNaisei   = naisei | 0x08;
        naisei      = newNaisei;
        domesticsSF = 0x8;
        domesticStatusBuff[listIndex] = (newNaisei << 8) | ((domesticStatusBuff[listIndex] & 0x00FF));
    }
    else //they can search or fortify again this week
    {
        newNaisei   = naisei & 0xF0;
        naisei      = newNaisei;
        domesticsSF = 0x0;
        domesticStatusBuff[listIndex] = (newNaisei << 8) | ((domesticStatusBuff[listIndex] & 0x00FF));
    }

    dr.fw.writeOneElementToFile(GEN_DOMESTICS_STATUS, 2, domesticStatusBuff[listIndex], listIndex);

    return 1;
}

void General::setStatus(const int fs1, const int fs2)
{
    fieldStatus1 = fs1;
    fieldStatus2 = fs2;

    FsBuffer1[listIndex] = fs1;
    FsBuffer2[listIndex] = fs2;

    dr.fw.writeOneElementToFile(FIELD_STATUS_1, 1, fs1, listIndex);
    dr.fw.writeOneElementToFile(FIELD_STATUS_2, 1, fs2, listIndex);

    return;
}

void General::setLocation(const int locType, const int newLoc)
{
    ushort locForFile = 0;

    if(locType == 1)
    {
        fixedLocation = 1;
        locForFile    = 0x8000 | newLoc;
    }
    if(!locType)
    {
        fixedLocation = 0;
        locForFile    = 0x00FF & newLoc;
    }

    location                   = newLoc;
    locationNumBuff[listIndex] = locForFile;
    dr.fw.writeOneElementToFile(GEN_LOCATION, 2, locForFile, listIndex);

    needsUpdate = true;

    return;
}

void General::setOwner(const int newOwner)
{
    owner                   = generalsNameList[newOwner];
    officerOwner[listIndex] = newOwner;
    dr.fw.writeOneElementToFile(GEN_OFFICER_OWNERSHIP, 1, newOwner, listIndex);

    needsUpdate = true;

    return;
}

void General::setTroopCount(const int newTroopCount)
{
    currentTroopCount             = newTroopCount;
    currTroopCountBuff[listIndex] = newTroopCount;
    dr.fw.writeOneElementToFile(GEN_CURR_TROOP_COUNT, 1, newTroopCount, listIndex);

    needsUpdate = true;

    return;
}

/*
   RETURN:  1 == success
            0 == error; location full
           -2 == error; trying to hide monarch
           -3 == error; can't make player monarch a captive
*/
int General::changeLocation(const int destLocType, const int destStatusType, const int newLoc)
{
    if((destStatusType == fieldStatus1) && (fixedLocation == destLocType) && (location == newLoc))
        return 1; //if trying to move to the same location that they are already in, with same status, just return.

    if(dr.playingAs == listIndex)
    {
        if((destLocType == 1) && ((newLoc < 0) || (newLoc > 33)))
            return -2; //fail, can't hide monarch
        if(destStatusType == 4)
            return -3; //fail, player monarch can't be captive
    }

    if(destLocType && (destStatusType == 3) && (newLoc < 34)) //if new location is full; fail. Otherwise, general will be hidden,
    {                                                         //due to being removed from old loc and not added to new loc
        if(dr.casArr[newLoc].isCastleFull())
            return 0;
    }
    else
        if(!destLocType && (destStatusType == 3))
            if(dr.divArr[newLoc].isDivisionFull())
                return 0;

//remove the general from castle or division
    if(fixedLocation) //currently in a castle, or hidden
    {
        if((location >= 0) && (location <= 33)) //this is for a castle, since hidden general is already prepared
        {
            if(fieldStatus1 == 3) //if they're a general
                dr.casArr[location].removeGeneral_a(listIndex);
            if(fieldStatus1 == 4) //if they're a captive
                dr.casArr[location].removeCaptive(listIndex);
        }
    }
    else //currently in a division
    {
        if(fieldStatus1 == 3) //if they're a general
            dr.divArr[location].removeMember_a(listIndex);
        if(fieldStatus1 == 4) //if they're a captive
            dr.divArr[location].removeCaptive(listIndex);
    }

//now add the general to their new location
    if(destLocType == 1) //going to a castle
    {
        if((newLoc >= 0) && (newLoc <= 33)) //if going to a castle
            {
                if(destStatusType == 3)
                    dr.casArr[newLoc].addGeneral_a(listIndex); //add general to castle
                else //destStatusType == 4
                    dr.casArr[newLoc].addCaptive_a(listIndex); //add captive to castle
                dr.casArr[newLoc].cleanCaptiveHolder();    //check and clean captive hold area
            }
        else //else general is being hidden
        {
            //captives are already hidden, just clean up the Hold Area
            for(int i = 0; i < dr.capHolder.numHeld; i++)
                dr.capHolder.holdArea[i] = -1;
            dr.capHolder.numHeld = 0;
        }
    }
    else //going to a division
    {
        if(destStatusType == 3)
            dr.divArr[newLoc].addMember_a(listIndex); //add general to division
        else  //destStatusType == 4
            dr.divArr[newLoc].addCaptive_a(listIndex); //add captive to division
        dr.divArr[newLoc].cleanCaptiveHolder();   //check captive hold area
    }

    needsUpdate = true;

    return 1;
}

void General::hide(void)
{
    setOwner(listIndex); //set owner to self
    setStatus(1,0);      //set status to unknown-ok
    setLocation(1, 62);  //hide them
    if(currentTroopCount)
        setTroopCount(0);

    needsUpdate = true;

    return;
}
