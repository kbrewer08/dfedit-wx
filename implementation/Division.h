#ifndef DIVISION_H
#define DIVISION_H

#include <iostream>
#include <string>

#include "DragonForce.h"

using namespace std;

class Division
{
public:
    
    int  ruler;
    int  leader;
    int  status;
    int  divNum;
    bool hasPlayerRuler;
    int  numMembers;
    int  numCaptives;
    int  troopCount;
    int  members[5];
    int  captives[171];
    int  origin;
    int  goal;
    int  prev;
    int  next;
    int  xCoordinate;
    int  yCoordinate;

    Division  (void);
    ~Division (void) {}

    Division(const Division& rhsDiv);
    Division& operator=(const Division& rhsDiv);

    friend ostream& operator<<(ostream& os, const Division& rhsDiv);

    bool addMember_init  (const int genIndex);
    void addCaptive_init (const int genIndex);
    void removeCaptive   (const int genIndex);

    bool isDivisionFull (void) {return numMembers == 5;}

    void setRuler       (const int i)  {ruler = i; return;}
    void setLeader      (const int i)  {leader = i; return;}
    void setStatus      (const int i)  {status = i; return;}
    void setDivNum      (const int i)  {divNum = i; return;}
    void setHasPlayer   (const bool i) {hasPlayerRuler = i; return;}
    void setTroopCount  (const int i)  {troopCount = i; return;}
    void setOrigin      (const int i)  {origin = i; return;}
    void setGoal        (const int i)  {goal = i; return;}
    void setPrev        (const int i)  {prev = i; return;}
    void setNext        (const int i)  {next = i; return;}
    void setXCoordinate (const int i)  {xCoordinate = i; return;}
    void setYCoordinate (const int i)  {yCoordinate = i; return;}

    int  findRulerIndex (void);
    int  changeRuler    (const int rulerIndex);
    int  changeLeader   (const int leaderIndex);
    void changeStatus   (const int newStatus);
    void changeGoal     (const int newGoal);
    void setNewGoal     (const int newGoal);

    bool addMultiGenFromList (int* const genBuff, const int genCount);
    bool delMultiGenFromList (int* const genBuff, const int genCount);
    bool addMultiCapFromList (int* const capBuff, const int capCount);
    bool delMultiCapFromList (int* const capBuff, const int capCount);
    int  fromGenToCap        (int* const genBuff, const int genCount);
    bool fromCapToGen        (int* const capBuff, const int capCount);

    void removeMember_a      (const int genIndex);
    void addMember_a         (const int genIndex);
    void addCaptive_a        (const int genIndex);
    void moveCaptivesToHold  (void);
    void cleanCaptiveHolder  (void);
    void setDivisionEmpty    (void);
    void moveMembersToCastle (void);
    void setDivisionCoords   (const int locNum);
};

#endif
