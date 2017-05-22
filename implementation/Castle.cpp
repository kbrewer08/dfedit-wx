#include "DragonForce.h"

Castle::Castle(void)
{
    castleNum      = -1;
    ruler          = -1;
    leader         = -1;
    numGenerals    = 0;
    numCaptives    = 0;

    for(int i = 0; i < 10; i++)
        generals[i] = -1;
    for(int i = 0; i < 171; i++)
        captives[i] = -1;

    xCoordinate    = 0;
    yCoordinate    = 0;
    hasPlayerRuler = false;
    level          = 0;
    troopCount     = 0;
    maxTroops      = 0;
    experience     = 0;
    expNext        = 0;
    needsUpdate    = false;
    castleName = "";
}

Castle::Castle(const Castle& rhsCas)
{
    castleNum      = rhsCas.castleNum;
    ruler          = rhsCas.ruler;
    leader         = rhsCas.leader;
    numGenerals    = rhsCas.numGenerals;
    numCaptives    = rhsCas.numCaptives;

    for(int i = 0; i < 10; i++)
        generals[i] = rhsCas.generals[i];
    for(int i = 0; i < 171; i++)
        captives[i] = rhsCas.captives[i];
    
    xCoordinate    = rhsCas.xCoordinate;
    yCoordinate    = rhsCas.yCoordinate;
    hasPlayerRuler = rhsCas.hasPlayerRuler;
    level          = rhsCas.level;
    troopCount     = rhsCas.troopCount;
    maxTroops      = rhsCas.maxTroops;
    experience     = rhsCas.experience;
    expNext        = rhsCas.expNext;
    needsUpdate    = rhsCas.needsUpdate;
    castleName     = rhsCas.castleName;
}

Castle& Castle::operator=(const Castle& rhsCas)
{
    if(this == &rhsCas)
        return *this;
    
    castleNum      = rhsCas.castleNum;
    ruler          = rhsCas.ruler;
    leader         = rhsCas.leader;
    numGenerals    = rhsCas.numGenerals;
    numCaptives    = rhsCas.numCaptives;

    for(int i = 0; i < 10; i++)
        generals[i] = rhsCas.generals[i];
    for(int i = 0; i < 171; i++)
        captives[i] = rhsCas.captives[i];
    
    xCoordinate    = rhsCas.xCoordinate;
    yCoordinate    = rhsCas.yCoordinate;
    hasPlayerRuler = rhsCas.hasPlayerRuler;
    level          = rhsCas.level;
    troopCount     = rhsCas.troopCount;
    maxTroops      = rhsCas.maxTroops;
    experience     = rhsCas.experience;
    expNext        = rhsCas.expNext;
    needsUpdate    = rhsCas.needsUpdate;
    castleName     = rhsCas.castleName;

    return *this;
}

ostream& operator<<(ostream& os, const Castle& rhsCas)
{
    os << rhsCas.castleName << endl;
    os << "Ruler: " << generalsNameList[rhsCas.ruler] << endl;
    os << "Leader: " << generalsNameList[rhsCas.leader] << endl;
    os << ' ' << rhsCas.numGenerals << ' ' << rhsCas.numCaptives;
    os << ' ' << rhsCas.xCoordinate << ',' << rhsCas.yCoordinate;
    os << ' ' << rhsCas.level << ' ' << rhsCas.experience;
    os << ' ' << rhsCas.troopCount << endl;
    for(int i = 0; i < rhsCas.numGenerals; i++)
        os << generalsNameList[rhsCas.generals[i]] << ' ';

    return os;
}

int Castle::addGeneral_init(const int genIndex)
{
    int success = 0;

    if(!isCastleFull())
    {
        generals[numGenerals] = genIndex;
        numGenerals++;
        success = 1;
    }

    return success;
}

int Castle::addCaptive_init(const int genIndex)
{
    captives[numCaptives] = genIndex;
    numCaptives++;

    return 1;
}

void Castle::setCastleEmpty(void)
{
    leader         = -1;
    ruler          = -1;
    troopCount     = 0;
    hasPlayerRuler = 0;
    dr.fw.writeOneElementToFile(CASTLE_OWNERSHIP, 1, 171, castleNum);
    castleOwnership[castleNum] = 171;
    dr.fw.writeOneElementToFile(CASTLE_CURR_TROOPS, 2, 0, castleNum);
    castleCurrentTroops[castleNum] = 0;

    needsUpdate = true;

    return;
}

void Castle::removeCaptive(const int genIndex)
{
    int i = 0;

    while(captives[i] != genIndex) //find captive's spot in array
        i++;

    if(i == 170)
        captives[170] = -1;
    else
        for(; i < numCaptives; i++) //move everyone else over; i.e. delete a captive
            captives[i] = captives[i + 1];
    numCaptives--;

    dr.genArr[genIndex].hide();

    needsUpdate = true;

    return;
}

/*           changeLeader

   0 - Can't change leader if castle's ruler is in castle
   1 - leader change was ok
*/
int Castle::changeLeader(const int genIndex)
{
    int newLeader = -1;

    if(leader == ruler)
        return 0; //denied - castle's ruler is present, so they must be leader

    //find the new leader in the array and get their internal general ID
    newLeader = dr.genArr[generals[genIndex]].listIndex;

    //demoting the current leader
    dr.genArr[leader].setStatus(3,0);

    //promote new leader
    leader = newLeader;
    dr.genArr[newLeader].setStatus(3,2);

    needsUpdate = true;

    return 1;
}

int Castle::adjustTroops(const int newTroops)
{
    if(newTroops > maxTroops)
        return 0;

    troopCount = newTroops;
    castleCurrentTroops[castleNum] = troopCount;
    dr.fw.writeOneElementToFile(CASTLE_CURR_TROOPS, 2, troopCount, castleNum);

    needsUpdate = true;

    return 1;
}

int Castle::adjustLevel(const int newLevel)
{
    if(newLevel == 0)
    return 0; //can't set castle to level 0

    level                  = newLevel;
    levelBuffer[castleNum] = newLevel;

    experience                  = (level - 1) * 1200;
    expNext                     = level * 1200;
    castleExperience[castleNum] = experience;
    dr.fw.writeOneElementToFile(CASTLE_EXPERIENCE, 2, experience, castleNum);

    maxTroops = (level + 5) * 10;
    if(troopCount > maxTroops)
    {
        troopCount                     = maxTroops;
        castleCurrentTroops[castleNum] = troopCount;
        dr.fw.writeOneElementToFile(CASTLE_CURR_TROOPS, 2, troopCount, castleNum);
    }

    needsUpdate = true;

    return 1;
}

/*           changeRuler

   0 - Can't change ruler if player monarch is in castle
   1 - change was ok; monarch was changed and new monarch wasn't already in castle
   2 - new monarch was in castle, so they had to be promoted to leader;
       therefore need to change leader combobox too
*/
int Castle::changeRuler(const int genIndex)
{
    bool   newRulerPresent;
    string newRuler;

    newRulerPresent = false;

    if((leader == dr.playingAs) && (leader != genIndex)) //if the player's monarch is in this castle
        return 0;                                        //then you can't change the ruler
    else
        if((leader == dr.playingAs) && (leader == genIndex)) //if trying to change ruler to the player's monarch when
            return 1;                                        //they are already here, just return success right away

    newRuler = generalsNameList[genIndex];

    for(int i = 0; i < numGenerals; i++)//own the generals, if any
        dr.genArr[generals[i]].setOwner(genIndex);

    for(int i = 0; i < numCaptives; i++)//own the captives, if any
    {
        dr.genArr[captives[i]].setOwner(genIndex);
        if(dr.playingAs == genIndex)
            dr.genArr[captives[i]].setStatus(4,0);
        else
            dr.genArr[captives[i]].setStatus(4,1);
    }

    if(numGenerals) //only take ownership of castle if someone is in it
    {
        ruler = genIndex;
        castleOwnership[castleNum] = genIndex;
        dr.fw.writeOneElementToFile(CASTLE_OWNERSHIP, 1, genIndex, castleNum);
    }

    for(int i = 0; i < numGenerals; i++)
        if(generals[i] == genIndex)
            newRulerPresent = true;

    if(newRulerPresent) //if the new ruler of this castle is also present in this castle
    {                   //then make them the leader
        //demote old leader
        dr.genArr[leader].setStatus(3,0);
        //update data to reflect new leader
        dr.genArr[genIndex].setStatus(3,2);
        leader = genIndex;

        return 2;
    }

    needsUpdate = true;

    return 1;
}

int Castle::findRulerIndex(void)
{
    int rulerIndex = -1;

    if(leader == ruler) //castle has ruler
        for(int i = 0; i < numGenerals; i++)
            if(generals[i] == ruler)
                rulerIndex = i;

    return rulerIndex;
}

bool Castle::addMultiGenFromList(int* const genBuff, const int genCount) // *********************************************** CHECKED - SEEMS OK
{
    int  gCount     = genCount;
    int  genDeleted = 0;
    bool needRuler = false;
    bool gensAdded = false;

    if(isCastleFull())
        return false;

    if(!gCount)
        return false;

    if(!numGenerals) //if occupying an empty castle
        needRuler = true;

/* outer loop goes through genBuff, inner loop goes through castle::generals.
   Any general found in genBuff that is also found in castle::generals is
   removed from genBuff. 171 is used as the removal value, since no general goes
   above 170. Running the insertion sort will put all of the 171s in the back; 
   updating gCount afterward makes sure the 171s are never reached.
*/
    for(int i = 0; i < gCount; i++)
        for(int j = 0; j < numGenerals; j++)
            if(genBuff[i] == generals[j])
            {
                genBuff[i] = 171;
                genDeleted++;
                j = numGenerals;
            }
    g_insertionSort(genBuff, gCount);
    gCount -= genDeleted;
    if(!gCount)
        return false;

    int genAdder = 0;
    int gen      = -1;
    while((genAdder < gCount) && (numGenerals < 10))
    {
        gen = genBuff[genAdder];
        dr.genArr[gen].changeLocation(1, 3, castleNum);
        genAdder++;
        gensAdded = true;
    }
     g_insertionSort(generals, numGenerals); //after adding generals, sort list

    if(needRuler)
        changeRuler(generals[0]);

    return gensAdded;
}

bool Castle::delMultiGenFromList(int* const genBuff, const int genCount)  // ********************************************** CHECKED - SEEMS OK
{
    int  gCount      = genCount;
    int  oldRuler    = ruler;
    bool needRuler   = false;
    bool needLeader  = false;
    bool gensDeleted = false;

    if(!gCount)
        return false;

    //prepare generals buffer by swapping the generic array index number that
    //Windows fills genBuff with, with the ID# of the general in the specified
    //position in the listbox
    for(int i = 0; i < gCount; i++)
        genBuff[i] = generals[genBuff[i]];

    for(int i = 0; i < gCount; i++) //if player monarch is in genBuff, remove it
        if(genBuff[i] == dr.playingAs)
        {
            for(int j = i; j < gCount - 1; j++)
                genBuff[j] = genBuff[j + 1];
            gCount--;
            i = gCount; //we're done here, break the loop
            if(!gCount) //player monarch was the only general in genBuff
                return false;
        }

    for(int i = 0; i < gCount; i++)
    {
        if(ruler == genBuff[i])
        {
            needRuler = true; //ruler is being deleted, find another one later
            i = gCount; //if deleting ruler, we obviously don't need to check for leader
        }
        if(leader == genBuff[i]) //leader is being deleted, find another one later
        {
            needLeader = true;
            i = gCount;
        }
    }

    for(int i = 0; i < gCount; i++) //delete the selected generals from castle
    {
        dr.genArr[genBuff[i]].changeLocation(1, 3, 62); //hide general
        gensDeleted = true;
    }

    if(needRuler) //if deleting ruler, all their other castles need new rulers
        dr.findNewRulers(oldRuler);

    if(numGenerals && needRuler)
    {
        changeRuler(generals[0]);

        leader = generals[0];
        dr.genArr[leader].setStatus(3,2);
        needLeader = false;
    }

    if(numGenerals && needLeader)
    {
        leader = generals[0];
        dr.genArr[leader].setStatus(3,2);
    }

    if(!numGenerals) //if no one left in castle, clean castle up as needed
    {
        setCastleEmpty();
        moveCaptivesToHold(); //castle is empty and has captives, hide captives
    }

    return gensDeleted;
}

bool Castle::addMultiCapFromList(int* const capBuff, const int capCount)  // ********************************************** CHECKED - OK
{
    int  cCount        = capCount;
    int  capsDeleted   = 0;
    bool captivesAdded = false;

    for(int i = 0; i < cCount; i++) //if player monarch is in capBuff, remove it
        if(capBuff[i] == dr.playingAs)
        {
            for(int j = i; j < cCount - 1; j++)
                capBuff[j] = capBuff[j + 1];
            cCount--;
            i = cCount; //we're done here, break the loop
            if(!cCount) //player monarch was the only general in genBuff
                return false;
        }

    //remove castle generals from incoming-captives buffer; that behavior will
    //be handled through a different function and UI button
    for(int i = 0; i < cCount; i++)
        for(int j = 0; j < numGenerals; j++)
            if(capBuff[i] == generals[j])
            {
                capBuff[i] = 171;
                capsDeleted++;
                j = numGenerals;
            }
    g_insertionSort(capBuff, cCount);
    cCount -= capsDeleted;
    if(!cCount)
        return false;

    capsDeleted = 0;
    //remove castle captives from incoming-captives buffer
    for(int i = 0; i < cCount; i++)
        for(int j = 0; j < numCaptives; j++)
            if(capBuff[i] == captives[j])
            {
                capBuff[i] = 171;
                capsDeleted++;
                j = numCaptives;
            }
    g_insertionSort(capBuff, cCount);
    cCount -= capsDeleted;
    if(!cCount)
        return false;

    int capAdder = 0;
    int gen      = -1;
    while((capAdder < cCount) && (numCaptives < 171))
    {
        gen = capBuff[capAdder];
        dr.genArr[gen].changeLocation(1, 4, castleNum);
        capAdder++;
        captivesAdded = true;
    }
     g_insertionSort(captives, numCaptives); //after adding captives, sort list

    return captivesAdded;
}

bool Castle::delMultiCapFromList(int* const capBuff, const int capCount)  // ********************************************** CHECKED - OK
{
    int  cCount          = capCount;
    bool captivesDeleted = false;

    if(!cCount)
        return false;

    //prepare captives buffer by swapping the generic array index number that
    //Windows fills genBuff with, with the ID# of the captive in the specified
    //position in the listbox
    for(int i = 0; i < cCount; i++)
        capBuff[i] = captives[capBuff[i]];

    for(int i = 0; i < cCount; i++)
    {
        dr.genArr[capBuff[i]].changeLocation(1, 3, 62);
        captivesDeleted = true;
    }

    return captivesDeleted;
}

/*           fromGenToCap

  -1 - Need at least 1 general; can't have castle with captives, but no generals
   0 - no generals were selected for demotion to captive
   1 - operation completed successfully
*/
int Castle::fromGenToCap(int* const genBuff, const int genCount)  // ********************************************** CHECKED - SEEMS OK
{
    int  gCount     = genCount;
    int  success    = 0;
    int  oldRuler   = ruler;
    bool needRuler  = false;
    bool needLeader = false;

    if(gCount == numGenerals)
        return -1;

    //prepare generals buffer by swapping the generic array index number that
    //Windows fills genBuff with, with the ID# of the general in the specified
    //position in the listbox
    for(int i = 0; i < gCount; i++)
        genBuff[i] = generals[genBuff[i]];

    for(int i = 0; i < gCount; i++) //if player monarch is in genBuff, remove it
        if(genBuff[i] == dr.playingAs)
        {
            for(int j = i; j < gCount - 1; j++)
                genBuff[j] = genBuff[j + 1];
            gCount--;
            i = gCount; //we're done here, break the loop
        }

    if(!gCount) //no generals to demote
        return 0;

    for(int i = 0; i < gCount; i++)
    {
        if(ruler == genBuff[i])
        {
            needRuler = true; //ruler is being deleted, find another one later
            i = gCount; //if deleting ruler, we obviously don't need to check for leader
        }
        if(leader == genBuff[i]) //leader is being deleted, find another one later
        {
            needLeader = true;
            i = gCount;
        }
    }

    for(int i = 0; i < gCount; i++)
    {
        removeGeneral_a(genBuff[i]);
        addCaptive_a(genBuff[i]);
        success = 1;
    }

    g_insertionSort(captives, numCaptives);

    if(needRuler)
    {
        ruler  = generals[0];
        changeRuler(generals[0]);

        leader = generals[0];
        dr.genArr[leader].setStatus(3,2);
        needLeader = false;

        dr.findNewRulers(oldRuler);
    }

    if(needLeader)
    {
        leader = generals[0];
        dr.genArr[leader].setStatus(3,2);
    }

    return success;
}

bool Castle::fromCapToGen(int* const capBuff, const int capCount)// ********************************************** CHECKED - SEEMS OK
{
    int  cCount         = capCount;
    bool capsPromoted   = false;

    if(!cCount)
        return false;

    //prepare captives buffer by swapping the generic array index number that
    //Windows fills capBuff with, with the ID# of the captive in the specified
    //position in the listbox
    for(int i = 0; i < cCount; i++)
        capBuff[i] = captives[capBuff[i]];

    for(int i = 0; (i < cCount) && (numGenerals < 10); i++)
    {
        removeCaptive(capBuff[i]);
        addGeneral_a(capBuff[i]);
        capsPromoted = true;
    }

    g_insertionSort(generals, numGenerals);

    return capsPromoted;
}

void Castle::removeGeneral_a(const int genIndex)
{
    int i = 0;

    while(generals[i] != genIndex) //find general's spot in array
        i++;

    if(i == 9) //if general #10 is being removed, just overwrite their position
        generals[9] = -1;
    else
        for(; i < numGenerals; i++) //move everyone else over; i.e. delete a general
            generals[i] = generals[i + 1];
    numGenerals--;

    //hide the general being removed
    dr.genArr[genIndex].hide();

    if(!numGenerals) //if castle is empty now
    {
        setCastleEmpty();
        moveCaptivesToHold();
    }

    else //someone is still in the castle, so change leader if necessary
    {
        if(genIndex == dr.playingAs)
        {
            setHasMonarch(false);
            moveCaptivesToHold();
        }

        if(leader == genIndex)
        {
            leader = generals[0];
            dr.genArr[leader].setStatus(3,2);
        }
    }

    needsUpdate = true;

    return;
}

void Castle::addGeneral_a(const int genIndex)
{
    int genTroops = dr.genArr[genIndex].troopMedals[dr.genArr[genIndex].troopIndex] * 10;

    if(!numGenerals)  //castle was empty, needs a ruler and leader;
    {                 //used after already initialized
        generals[0] = genIndex;
        numGenerals++;
        dr.genArr[genIndex].setTroopCount(genTroops);

        leader = genIndex;
        dr.genArr[genIndex].setStatus(3,2); //first general in castle, make
        dr.genArr[genIndex].setLocation(1, castleNum);
        
        ruler = officerOwner[dr.genArr[genIndex].listIndex];
        castleOwnership[castleNum] = ruler;
        dr.fw.writeOneElementToFile(CASTLE_OWNERSHIP, 1, ruler, castleNum);
    }
    else
        if(!isCastleFull())
        {
            generals[numGenerals] = genIndex; //add new general to castle
            numGenerals++;
            dr.genArr[genIndex].setTroopCount(genTroops);

            if(dr.playingAs == genIndex) //if player monarch is coming here,
            {                            //make sure they own and rule everything
                dr.genArr[genIndex].setStatus(3,2);
                changeRuler(genIndex);
                dr.genArr[genIndex].setLocation(1, castleNum);
            }
            else //otherwise, make sure the new general is owned by the castle's
            {    //owner and that their status is not still leader from old castle
                if((ruler == genIndex) && (leader != genIndex)) //incoming general is ruler, but not leader yet
                {
                    dr.genArr[leader].setStatus(3,0);

                    leader = genIndex;
                    dr.genArr[genIndex].setStatus(3,2);
                }
                else
                {
                    dr.genArr[genIndex].setStatus(3,0);
                    dr.genArr[genIndex].setOwner(ruler);
                    dr.genArr[genIndex].setLocation(1, castleNum);
                }
            }
            g_insertionSort(generals, numGenerals);
        }

        needsUpdate = true;

return;
}

int Castle::addCaptive_a(const int genIndex)
{
    if(dr.playingAs == genIndex) //fail, player monarch can't be captive
        return 0;

    captives[numCaptives] = genIndex;
    numCaptives++;

    dr.genArr[genIndex].setOwner(ruler);
    dr.genArr[genIndex].setLocation(1, castleNum);
    dr.genArr[genIndex].setTroopCount(0);

    if(dr.playingAs == ruler)
        dr.genArr[genIndex].setStatus(4,0);
    else
        dr.genArr[genIndex].setStatus(4,1);

    needsUpdate = true;

    return 1;
}

void Castle::moveCaptivesToHold(void)
{
    if(!numCaptives)
        return;

    for(int i = 0; i < numCaptives; i++)
    {
        dr.genArr[captives[i]].hide(); //set hidden status to captive

        dr.capHolder.holdArea[i] = captives[i]; //move them to captive hold area
        dr.capHolder.numHeld++;

        captives[i] = -1;
    }
    numCaptives = 0;

    needsUpdate = true;

    return;
}

void Castle::cleanCaptiveHolder(void)
{
    //if any captives are in limbo, take possession of them
    if(dr.capHolder.numHeld)
    {
        for(int i = numCaptives, j = 0; j < dr.capHolder.numHeld; j++, i++)
        {
            captives[i] = dr.capHolder.holdArea[j]; //take captive from hold area
            dr.capHolder.holdArea[j] = -1;          //set hold area array spot to empty
            numCaptives++;
            dr.genArr[captives[i]].setOwner(ruler); //set captive owner to castle owner
            dr.genArr[captives[i]].setLocation(1, castleNum); //set their location to this castle
            if(ruler == dr.playingAs)
                dr.genArr[captives[i]].setStatus(4,0); //captive of player
            else
                dr.genArr[captives[i]].setStatus(4,1); //captive of AI
        }
        dr.capHolder.numHeld = 0; //captive array now clear
        g_insertionSort(captives, numCaptives); //sort the castle captives array
    }

    needsUpdate = true;

    return;
}
