#include "DragonForce.h"

Division::Division(void)
{
    ruler          = -1;
    leader         = -1;
    status         = 0;
    divNum         = -1;
    hasPlayerRuler = false;
    troopCount     = 0;
    numMembers     = 0;
    numCaptives    = 0;

    for(int i = 0; i < 5; i++)
        members[i] = -1;
    for(int j = 0; j < 171; j++)
        captives[j] = -1;
    
    origin         = 0;
    goal           = 0;
    prev           = 0;
    next           = 0;
    xCoordinate    = 0;
    yCoordinate    = 0;
}

Division& Division::operator=(const Division& rhsDiv)
{
    if(this == &rhsDiv)
        return *this;

    ruler          = rhsDiv.ruler;
    leader         = rhsDiv.leader;
    status         = rhsDiv.status;
    divNum         = rhsDiv.divNum;
    hasPlayerRuler = rhsDiv.hasPlayerRuler;
    troopCount     = rhsDiv.troopCount;
    numMembers     = rhsDiv.numMembers;
    numCaptives    = rhsDiv.numCaptives;
    
    for(int i = 0; i < 5; i++)
        members[i] = rhsDiv.members[i];
    for(int j = 0; j < 171; j++)
        captives[j] = rhsDiv.captives[j];

    origin      = rhsDiv.origin;
    goal        = rhsDiv.goal;
    prev        = rhsDiv.prev;
    next        = rhsDiv.next;
    xCoordinate = rhsDiv.xCoordinate;
    yCoordinate = rhsDiv.yCoordinate;

    return *this;
}

ostream& operator<<(ostream& os, const Division& rhsDiv)
{
    os << "Division #" << rhsDiv.divNum << endl;
    os << "     Ruler: " << generalsNameList[rhsDiv.ruler] << endl;
    os << "     Leader: " << generalsNameList[rhsDiv.leader] << endl;
    os << "     Status: " << shidanStatus[rhsDiv.status] << endl << "     ";
    os << rhsDiv.numMembers << ' ' << rhsDiv.numCaptives << ' ';
    os << rhsDiv.troopCount << endl << "     ";
    for(int i = 0; i < rhsDiv.numMembers; i++)
        os << generalsNameList[rhsDiv.members[i]] << ' ';
    os << endl;

    return os;
}

bool Division::addMember_init(const int genIndex)
{
    bool success = false;

    if(!isDivisionFull())
    {
        members[numMembers] = genIndex;
        numMembers++;
        success = true;
    }

    return success;
}

void Division::addCaptive_init(const int genIndex)
{
    captives[numCaptives] = genIndex;
    numCaptives++;

    return;
}

void Division::removeCaptive(const int genIndex)
{
    int i = 0;

    while(captives[i] != genIndex) //find captive's spot in array
        i++;

    if(i == 170) //if the captive being moved is the last one, no need to shift everyone, just delete last one
        captives[170] = -1;
    else
        for(; i < numCaptives; i++) //move everyone else over; i.e. delete a captive
            captives[i] = captives[i + 1];
    numCaptives--;

    //hide the captive being removed
    dr.genArr[genIndex].hide();

    return;
}

int Division::findRulerIndex(void)
{
    int rulerIndex = -1;

    if(leader == ruler) //division has ruler
        for(int i = 0; i < numMembers; i++)
            if(members[i] == ruler)
                rulerIndex = i;

    return rulerIndex;
}

/*           changeRuler

   0 - Can't change ruler if player monarch is in division
   1 - change was ok; monarch was changed and new monarch wasn't already in division
   2 - new monarch was in division, so they had to be promoted to leader;
       therefore need to change leader combobox too
*/
int Division::changeRuler(const int rulerIndex)
{
    bool   newRulerPresent;
    string newRuler;

    newRulerPresent = false;

    if((leader == dr.playingAs) && (leader != rulerIndex)) //if the player's monarch is in this division
        return 0;                                          //then you can't change the ruler
    else
        if((leader == dr.playingAs) && (leader == rulerIndex)) //if trying to change ruler to the player's monarch when
            return 1;                                          //they are already here, just return success right away

    newRuler = generalsNameList[rulerIndex];

    for(int i = 0; i < numMembers; i++)//own the generals, if any
        dr.genArr[members[i]].setOwner(rulerIndex);

    for(int i = 0; i < numCaptives; i++)//own the captives, if any
        dr.genArr[captives[i]].setOwner(rulerIndex);

    ruler = rulerIndex;

    for(int i = 0; i < numMembers; i++)
        if(members[i] == rulerIndex)
            newRulerPresent = true;

    if(newRulerPresent) //if the new ruler of this division is also present in
    {                   //this division, then make them the leader
        //demote old leader
        dr.genArr[leader].setStatus(3,0);
        //update data to reflect new leader
        dr.genArr[rulerIndex].setStatus(3,1);
        leader = rulerIndex;

        return 2;
    }

    return 1;
}

/*           changeLeader

   0 - Can't change leader if division's ruler is present
   1 - leader change was ok
*/
int Division::changeLeader(const int leaderIndex)
{
    int newLeader = -1;

    if(leader == ruler)
        return 0; //denied - division's ruler is present, so they must be leader

    //find the new leader in the array and get their internal general ID
    newLeader = dr.genArr[members[leaderIndex]].listIndex;

    //demoting the current leader
    dr.genArr[leader].setStatus(3,0);

    //promote new leader
    leader = newLeader;
    dr.genArr[newLeader].setStatus(3,1);

    return 1;
}

void Division::changeStatus(const int newStatus) //  ******************************************************** ACCOUNT FOR DIVISION STATUS OF "DOESN'T EXIST"
{
    if(newStatus == 0)
        moveMembersToCastle();
    else
    {
        status = newStatus;
        divisionStatus[divNum] = newStatus;
        dr.fw.writeOneElementToFile(DIVISION_STATUS, 1, newStatus, divNum);
    }

    return;
}

void Division::changeGoal(const int newGoal)
{
    (newGoal == 113) ? setNewGoal(255) : setNewGoal(newGoal);

    return;
}

void Division::setNewGoal(const int newGoal)
{
    goal = newGoal;
    divisionDestination[divNum] = newGoal;
    dr.fw.writeOneElementToFile(DIVISION_DESTINATION, 1, newGoal, divNum);

    return;
}

bool Division::addMultiGenFromList(int* const genBuff, const int genCount)
{
    int  gCount     = genCount;
    int  genDeleted = 0;
    bool gensAdded  = false;

    if(!gCount)
        return false;

/* outer loop goes through genBuff, inner loop goes through division::members.
   Any general found in genBuff that is also found in division::members is
   removed from genBuff. 171 is used as the removal value, since no general goes
   above 170. Running the insertion sort will put all of the 171s in the back; 
   updating gCount afterward makes sure the 171s are never reached.
*/
    for(int i = 0; i < gCount; i++)
        for(int j = 0; j < numMembers; j++)
            if(genBuff[i] == members[j])
            {
                genBuff[i] = 171;
                genDeleted++;
                j = numMembers;
            }
    g_insertionSort(genBuff, gCount);
    gCount -= genDeleted;
    if(!gCount)
        return false;

    int genAdder =  0;
    int gen      = -1;
    while((genAdder < gCount) && (numMembers < 5))
    {
        gen = genBuff[genAdder];
        dr.genArr[gen].changeLocation(0, 3, divNum);
        genAdder++;
        gensAdded = true;
    }
     g_insertionSort(members, numMembers); //after adding members, sort list

    return gensAdded;
}

bool Division::delMultiGenFromList(int* const genBuff, const int genCount)
{
    int  gCount      = genCount;
    bool needLeader  = false;
    bool gensDeleted = false;

    if(!gCount)
        return false;

    //prepare members buffer by swapping the generic array index number that
    //Windows fills genBuff with, with the ID# of the general in the specified
    //position in the listbox
    for(int i = 0; i < gCount; i++)
        genBuff[i] = members[genBuff[i]];

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
        if(leader == genBuff[i]) //leader is being deleted, find another one later
        {
            needLeader = true;
            i = gCount;
        }
    }

    for(int i = 0; i < gCount; i++) //delete the selected members from division
    {
        dr.genArr[genBuff[i]].changeLocation(1, 3, 62); //hide general
        gensDeleted = true;
    }

    if(numMembers && needLeader)
    {
        leader = members[0];
        dr.genArr[leader].setStatus(3,1);
    }

    if(!numMembers) //if no one left in division, clean division up as needed
        setDivisionEmpty();

    return gensDeleted;
}

bool Division::addMultiCapFromList(int* const capBuff, const int capCount)
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

    //remove division members from incoming-captives buffer; that behavior will
    //be handled through a different function and UI button
    for(int i = 0; i < cCount; i++)
        for(int j = 0; j < numMembers; j++)
            if(capBuff[i] == members[j])
            {
                capBuff[i] = 171;
                capsDeleted++;
                j = numMembers;
            }
    g_insertionSort(capBuff, cCount);
    cCount -= capsDeleted;
    if(!cCount)
        return false;

    capsDeleted = 0;
    //remove division captives from incoming-captives buffer
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
        dr.genArr[gen].changeLocation(0, 4, divNum);
        capAdder++;
        captivesAdded = true;
    }
     g_insertionSort(captives, numCaptives); //after adding captives, sort list

    return captivesAdded;
}

bool Division::delMultiCapFromList(int* const capBuff, const int capCount)
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

int Division::fromGenToCap(int* const genBuff, const int genCount)
{
    int  gCount     = genCount;
    int  success    = 0;
    int  oldRuler   = ruler;
    bool needRuler  = false;
    bool needLeader = false;

    if(gCount == numMembers)
        return -1;

    //prepare genBuff buffer by swapping the generic array index number that
    //Windows fills genBuff with, with the ID# of the general in the specified
    //position in the listbox
    for(int i = 0; i < gCount; i++)
        genBuff[i] = members[genBuff[i]];

    for(int i = 0; i < gCount; i++) //if player monarch is in genBuff, remove it
        if(genBuff[i] == dr.playingAs)
        {
            for(int j = i; j < gCount - 1; j++)
                genBuff[j] = genBuff[j + 1];
            gCount--;
            i = gCount; //we're done here, break the loop
        }

    if(!gCount) //no members to demote
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
        removeMember_a(genBuff[i]);
        addCaptive_a(genBuff[i]);
        success = 1;
    }

    g_insertionSort(captives, numCaptives);

    if(needRuler)
    {
        ruler  = members[0];
        changeRuler(members[0]);

        leader = members[0];
        dr.genArr[leader].setStatus(3,2);
        needLeader = false;

        dr.findNewRulers(oldRuler);
    }

    if(needLeader)
    {
        leader = members[0];
        dr.genArr[leader].setStatus(3,2);
    }

    return success;
}

bool Division::fromCapToGen(int* const capBuff, const int capCount)
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

    for(int i = 0; (i < cCount) && (numMembers < 5); i++)
    {
        removeCaptive(capBuff[i]);
        addMember_a(capBuff[i]);
        capsPromoted = true;
    }

    g_insertionSort(members, numMembers);

    return capsPromoted;
}

void Division::removeMember_a(const int genIndex)
{
    int i = 0;

    while(members[i] != genIndex) //find general's spot in array
        i++;

    if(i == 4)
        members[4] = -1;
    else
        for(; i < numMembers; i++) //move everyone else over; i.e. delete a general
            members[i] = members[i + 1];
    numMembers--;

    //hide the general being removed
    dr.genArr[genIndex].hide();

    troopCount -= dr.genArr[genIndex].currentTroopCount;

    if(!numMembers) //if division is empty now
        setDivisionEmpty();
    else //someone is still in the division, so change leader if necessary
    {
        if(genIndex == dr.playingAs)
        {
            setHasPlayer( false);
            moveCaptivesToHold();
        }

        if(leader == genIndex)
        {
            leader = members[0];
            dr.genArr[leader].setStatus(3,1);

            activeArmies[divNum] = members[0];
            dr.fw.writeOneElementToFile(DIVISION_LIST, 1, members[0], divNum);
        }
    }

    return;
}

void Division::addMember_a(const int genIndex)
{
    int genTroops = dr.genArr[genIndex].troopMedals[dr.genArr[genIndex].troopIndex] * 10;

    if(!isDivisionFull())
    {
        members[numMembers] = genIndex; //add new general to division
        numMembers++;
        dr.genArr[genIndex].setTroopCount(genTroops);

        if(dr.playingAs == genIndex) //if player monarch is coming here,
        {                            //make sure they own and rule everything
            changeRuler(genIndex);
            dr.genArr[genIndex].setStatus(3,1);
            dr.genArr[genIndex].setLocation(0, divNum);
        }
        else //otherwise, make sure the new general is owned by the division's
        {    //owner and that their status is not still leader from old division
            dr.genArr[genIndex].setStatus(3,0);
            dr.genArr[genIndex].setOwner(ruler);
            dr.genArr[genIndex].setLocation(0, divNum);
        }
        troopCount += dr.genArr[genIndex].currentTroopCount;
        g_insertionSort(members, numMembers);
    }

    return;
}

void Division::addCaptive_a(const int genIndex)
{
    if(dr.playingAs == genIndex) //fail, player monarch can't be captive
        return;

    captives[numCaptives] = genIndex;
    numCaptives++;

    dr.genArr[genIndex].setOwner(ruler);
    dr.genArr[genIndex].setLocation(0, divNum);
    dr.genArr[genIndex].setTroopCount(0);

    if(dr.playingAs == ruler)
        dr.genArr[genIndex].setStatus(4,0);
    else
        dr.genArr[genIndex].setStatus(4,1);

    return;
}

void Division::moveCaptivesToHold(void)
{
    for(int i = 0; i < numCaptives; i++)
    {
        dr.genArr[captives[i]].hide(); //hide captive

        dr.capHolder.holdArea[i] = captives[i]; //move them to captive hold area
        dr.capHolder.numHeld++;

        captives[i] = -1;
    }
    numCaptives = 0;

    return;
}

void Division::cleanCaptiveHolder(void)
{
    //if any captives are in limbo, take possession of them
    if(dr.capHolder.numHeld)
    {
        for(int i = numCaptives, j = 0; j < dr.capHolder.numHeld; j++, i++)
        {
            captives[i] = dr.capHolder.holdArea[j];
            dr.capHolder.holdArea[j] = -1;
            numCaptives++;
            dr.genArr[captives[i]].setOwner(ruler);
            dr.genArr[captives[i]].setLocation(0, divNum);
            if(ruler == dr.playingAs)
                dr.genArr[captives[i]].setStatus(4,0); //captive owned by player
            else
                dr.genArr[captives[i]].setStatus(4,1); //captive owned by AI
        }
        dr.capHolder.numHeld = 0;
        g_insertionSort(captives, numCaptives);
    }

    return;
}

void Division::setDivisionEmpty(void)
{
    leader = -1;
    ruler  = -1;
    status = 0;
    troopCount = 0;
    hasPlayerRuler = 0;
    dr.fw.writeOneElementToFile(DIVISION_STATUS, 1, 0, divNum);
    activeDivisions[divNum] = 0;
    divisionStatus[divNum] = 0;
    moveCaptivesToHold();

    return;
}

void Division::moveMembersToCastle(void) //disband division by moving generals to a castle owned by the same ruler.
{                                        //If no castle is found, the generals are hidden. Captives follow generals, either way.
    int i   = 0;
    int gen = -1;

    if(numMembers)
    {
        for(i = 0; (i < 34) && numMembers; i++)
        {
            if(ruler == dr.casArr[i].ruler)
            {
                while(numMembers && !dr.casArr[i].isCastleFull())
                {
                    gen = members[0]; //always do member index zero, because removing a general automatically re-sorts generals array
                    removeMember_a(gen);
                    dr.casArr[i].addGeneral_a(gen);
                }
                if(!numMembers)
                    dr.casArr[i].cleanCaptiveHolder();
            }
        }
        if((i == 34) && numMembers)
            while(numMembers)
                removeMember_a(members[0]);
    }

    return;
}

void Division::setDivisionCoords(const int locNum)
{
    const ushort x = locationCoordinates[locNum][0];
    const ushort y = locationCoordinates[locNum][1];


    xCoordinate = x;
    divisionXcoordinate[divNum] =  x << 3;
    dr.fw.writeOneElementToFile(DIVISION_X_COORD, 2, x << 3, divNum);


    yCoordinate = y;
    divisionYcoordinate[divNum] =  y << 3;
    dr.fw.writeOneElementToFile(DIVISION_Y_COORD, 2, y << 3, divNum);

    prev = locNum;
    divisionPrevious[divNum] = locNum;
    dr.fw.writeOneElementToFile(DIVISION_PREVIOUS, 1, locNum, divNum);

    next = locNum;
    divisionNext[divNum] = locNum;
    dr.fw.writeOneElementToFile(DIVISION_NEXT, 1, locNum, divNum);

    changeStatus(10); // "rest"

    return;
}
