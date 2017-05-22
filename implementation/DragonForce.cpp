#include <iostream>
#include <string>

#include "DragonForce.h"

using namespace std;

DragonForce dr;
string gPlayingAs;
char   playingAs_cstr[5] = {'\0'};
ushort gameYear;
ushort gameMonth;
ushort gameWeek;

ushort itemInventoryBuffer[256];

const char monarchFilename[8][5] = //used for finding out who the player's monarch is
{
    "Wein",
    "Gold",
    "Teir",
    "Mikh",
    "Rnha",
    "Leon",
    "Gong",
    "Juno"
};

ushort awardsLeft;

uchar  FsBuffer1[171]          = {'\0'};
uchar  officerOwner[171]       = {'\0'};
uchar  FsBuffer2[171]          = {'\0'};
uchar  levelBuffer[171]        = {'\0'};
uchar  classBuffer[171]        = {'\0'};
ushort locationNumBuff[171]    = {0};
uchar  troopTypeBuff[171]      = {'\0'};
uchar  currTroopCountBuff[171] = {'\0'};
uchar  nActionBuff[171]        = {'\0'};
uchar  bActionBuff[171]        = {'\0'};
uchar  livesBefSlainBuff[171]  = {'\0'};
uchar  currentHpBuffer[171]    = {'\0'};
uchar  maxHpBuffer[171]        = {'\0'};
uchar  currentMpBuffer[171]    = {'\0'};
uchar  maxMpBuffer[171]        = {'\0'};
uchar  strengthBuffer[171]     = {'\0'};
uchar  defpBuffer[171]         = {'\0'};
uchar  escChanceBuffer[171]    = {'\0'};
uchar  commandBuffer[171]      = {'\0'};
uchar  intellBuffer[171]       = {'\0'};
uchar  loyaltyBuffer[171]      = {'\0'};
uchar  equippedItemBuffer[171] = {'\0'};
ushort domesticStatusBuff[171] = {0};
ushort totalWinBuffer[171]     = {0};
ushort totalLossBuffer[171]    = {0};
ushort winsLastWeekBuffer[171] = {0};
ushort lossLastWeekBuffer[171] = {0};
uchar  soldCavaBuff[171]       = {'\0'};
uchar  mageSamuBuff[171]       = {'\0'};
uchar  archMonkBuff[171]       = {'\0'};
uchar  harpBeasBuff[171]       = {'\0'};
uchar  dragZombBuff[171]       = {'\0'};
ushort currExpBuffer[171]      = {0};
ushort newMeritsBuffer[171]    = {0};
ushort oldMeritsBuffer[171]    = {0};
ushort hospitalBuff[171]       = {0};
uchar  btlActionBuff[171]      = {'\0'};
uchar  moralBuff[171]          = {'\0'};
uchar  warlikeBuff[171]        = {'\0'};
ushort negoBuff[171]           = {0};
uchar  atkPlusBuff[171]        = {'\0'};
uchar  spellTierBuffer[171]    = {'\0'};
uchar  defPlusBuff[171]        = {'\0'};
ushort defSwordBuff[171]       = {0};
ushort defIceBuff[171]         = {0};
ushort defFireBuff[171]        = {0};
ushort defLightBuff[171]       = {0};
ushort defDarkBuff[171]        = {0};

uchar  castleOwnership[34]     = {'\0'};
ushort castleCurrentTroops[34] = {0};
ushort castleExperience[34]    = {0};
ushort castleLevel[34]         = {0};

int activeDivisions[171] = {0};

uchar  divisionStatus[171]       = {0};
uchar  activeArmies[171]         = {0};
uchar  divisionOrigin[171]       = {0};
uchar  divisionDestination[171]  = {0};
uchar  divisionPrevious[171]     = {0};
uchar  divisionNext[171]         = {0};
ushort divisionXcoordinate[171]  = {0};
ushort divisionYcoordinate[171]  = {0};

ushort divisionUnknown1Buff[171]  = {0};
ushort divisionUnknown2Buff[171]  = {0};
ushort divisionUnknown3Buff[171]  = {0};
ushort divisionUnknown4Buff[171]  = {0};
ushort divisionUnknown5Buff[171]  = {0};
ushort divisionUnknown6Buff[171]  = {0};
ushort divisionUnknown7Buff[171]  = {0};
ushort divisionUnknown8Buff[171]  = {0};
ushort divisionUnknown9Buff[171]  = {0};
ushort divisionUnknown10Buff[171] = {0};
ushort divisionUnknown11Buff[171] = {0};
ushort divisionUnknown12Buff[171] = {0};

const char generalsNameList[171][12] =
{
    "Wein",
    "Goldark",
    "Teiris",
    "Mikhal",
    "Reinhart",
    "Leon",
    "Gongos",
    "Junon",
    "Rudger",
    "Galam",
    "Nina",
    "Link",
    "Gaul(1)",
    "Kharhaz",
    "Scythe(1)",
    "Lyria",
    "Gulen",
    "Manoa",
    "Duran",
    "Reiner",
    "Zagat",
    "Jackal",
    "Shione",
    "Mistal",
    "Presto",
    "Sophie",
    "Tsugal",
    "Bardal",
    "Garyus",
    "Yanna",
    "Shaia",
    "Raizak",
    "Rygar",
    "Baghib",
    "Katt",
    "Yuni",
    "Ayrios",
    "Cinna",
    "Ortega",
    "Scar",
    "Hayate",
    "Shirox",
    "Vlad",
    "Ryskim",
    "Ogredd",
    "Taulus",
    "Saul",
    "Randolph",
    "Crawford",
    "Milishea",
    "Phylicia",
    "Katis",
    "Borgon",
    "Hilga",
    "Rock",
    "Lone",
    "Sierra(1)",
    "Scythe(2)",
    "Gaul(2)",
    "Katmando(1)",
    "Hikkis",
    "Cher",
    "Vangal",
    "Zado",
    "Golem",
    "Gustav",
    "Yuug",
    "Gunner",
    "Rykker",
    "Gasper",
    "Helm",
    "Tzuvan",
    "Faliel",
    "Diablo",
    "Silva",
    "Norse",
    "Kyoem(1)",
    "Kumonn",
    "Sliver",
    "Sayaka",
    "Dayn",
    "Kodiak",
    "Myria",
    "Wriph",
    "Gyzzdark",
    "Ryskim(2)",
    "Ramzal",
    "Kidd",
    "Uryll",
    "Ardor",
    "Gigg",
    "Santana",
    "Talon",
    "Aisha",
    "Bagril",
    "Viper",
    "Nelson",
    "Hagane",
    "Erin",
    "Mileen",
    "Laine",
    "Varshyl",
    "Nyvkall",
    "Piper",
    "Zanon",
    "Yuri",
    "Veltarna",
    "Grudar",
    "Bastion",
    "Paine",
    "Agonni",
    "Sierra(2)",
    "Atakin",
    "Gunter",
    "Gorudias",
    "Beykall",
    "Saharzad",
    "Phylla",
    "Marina",
    "Ruix",
    "Scythe(3)",
    "Gaul(3)",
    "Barat",
    "Neil",
    "Ramda",
    "Lokithus",
    "Madruk(1)",
    "Grog",
    "Razor",
    "Fynn",
    "Klaww",
    "Slytt",
    "Krystiss",
    "Dugglar",
    "Karakk",
    "Blakk",
    "Skugg",
    "Tazzax",
    "Graggel",
    "Paxx",
    "Madruk(2)",
    "Katmando(2)",
    "Mea",
    "Fiina",
    "Alex",
    "Farilis",
    "Kilrein",
    "Ishtar",
    "Hagar",
    "Raitt",
    "Gekai",
    "Shadow",
    "Kyoem(2)",
    "Slate",
    "Narrak",
    "Zatai",
    "Slythis",
    "Barrat",
    "Gator",
    "Livion",
    "Stegalt",
    "Kulien",
    "Fern",
    "Enya",
    "Gilette",
    "Voitt",
    "Rog",
    "Fyffer",
    "Sylphia",
    "Zakk",
    "Rufas",
};

const char classType[15][12] = 
{
    "none",
    "Soldier",
    "Knight",
    "Spirit User",
    "Magician",
    "Samurai",
    "Ninja",
    "Monk",
    "Priest",
    "Thief",
    "Beast",
    "?????",
    "Succubus",
    "Vampire",
    "Dragon",
};

const char troopType[11][9] = 
{
    "none",
    "Soldiers",
    "Cavalry",
    "Mages",
    "Samurai",
    "Archers",
    "Monks",
    "Harpies",
    "Beasts",
    "Dragons",
    "Zombies",
};

const char* genStatusArray[7][3] = 
{
    {"null", "null", "null"},
    {"Unknown-Ok", "null", "null"},
    {"Hidden", "null", "null"},
    {"Exists", "Division Leader", "Castle Leader"},
    {"Player Captive", "AI Captive", "Captive"},
    {"town captive", "not sure", "null"},
    {"Hospital", "null", "null"}
};

const char castlesNameList[35][9] =
{
    "Highland",
    "Fandaria",
    "Palemoon",
    "Izumo",
    "Tradnor",
    "Topaz",
    "Bozack",
    "Tristan",
    "Galfiel",
    "Daiden",
    "Stoic",
    "Bloodly",
    "Ginan",
    "Orvue",
    "Claystal",
    "Magicka",
    "Eternal",
    "Royal",
    "Danyan",
    "Stalwart",
    "Lightan",
    "Gasparl",
    "Roguewar",
    "Sardia",
    "Blazart",
    "Sophnyk",
    "Crystal",
    "Starfall",
    "Travan",
    "Nikeral",
    "Mikeral",
    "Estonia",
    "Ogrekeep",
    "Maryware",
    "None"
};

int locationCoordinates[113][2] =
{
    {173, 159}, //  0
    {62, 99},   //  1
    {210, 109}, //  2
    {71, 129},  //  3
    {122, 133}, //  4
    {134, 97},  //  5
    {102, 169}, //  6
    {160, 48},  //  7
    {159, 160}, //  8
    {169, 167}, //  9
    {72, 106},  // 10
    {52, 105},  // 11
    {62, 89},   // 12
    {198, 107}, // 13
    {188, 97},  // 14
    {151, 114}, // 15
    {78, 140},  // 16
    {77, 121},  // 17
    {133, 131}, // 18
    {116, 122}, // 19
    {118, 156}, // 20
    {146, 99},  // 21
    {117, 97},  // 22
    {81, 162},  // 23
    {170, 63},  // 24
    {146, 34},  // 25
    {172, 112}, // 26
    {163, 87},  // 27
    {158, 134}, // 28
    {100, 97},  // 29
    {101, 141}, // 30
    {88, 99},   // 31
    {138, 115}, // 32
    {146, 151}, // 33
    {149, 129}, // 34
    {85, 187},  // 35
    {231, 94},  // 36
    {177, 11},  // 37
    {103, 70},  // 38
    {22, 82},  // 39
    {215, 118},  // 40 - invalid point; using same coordinates as site 62
    {215, 118},  // 41 - invalid point; using same coordinates as site 62
    {141, 105},  // 42
    {147, 162},  // 43
    {134, 149},  // 44
    {134, 149},  // 45
    {125, 149},  // 46
    {116, 149},  // 47
    {98, 148},  // 48
    {104, 149},  // 49
    {128, 122},  // 50
    {130, 139},  // 51
    {116, 139},  // 52
    {111, 132},  // 53
    {144, 63},  // 54
    {166, 79},  // 55
    {89, 88},  // 56
    {84, 113},  // 57
    {166, 152},  // 58
    {186, 110},  // 59
    {189, 119},  // 60
    {202, 122},  // 61
    {215, 118},  // 62
    {218, 103},  // 63
    {202, 89},  // 64
    {211, 79},  // 65
    {228, 86},  // 66
    {161, 98},  // 67
    {175, 35},  // 68
    {145, 52},  // 69
    {142, 75},  // 70
    {141, 88},  // 71
    {129, 87},  // 72
    {124, 75},  // 73
    {117, 70},  // 74
    {95, 71},  // 75
    {88, 68},  // 76
    {77, 68},  // 77
    {74, 79},  // 78
    {87, 108},  // 79
    {110, 109},  // 80
    {131, 105},  // 81
    {72, 94},  // 82
    {52, 94},  // 83
    {62, 110},  // 84
    {30, 89},  // 85
    {44, 87},  // 86
    {34, 103},  // 87
    {42, 107},  // 88
    {38, 105},  // 89
    {57, 71},  // 90
    {159, 145},  // 91
    {162, 113},  // 92
    {139, 124},  // 93
    {137, 166},  // 94
    {89, 168},  // 95
    {89, 154},  // 96
    {100, 161},  // 97
    {88, 181},  // 98
    {58, 79},  // 99
    {40, 94},  // 100
    {38, 85},  // 101
    {174, 98},  // 102
    {150, 121},  // 103
    {80, 82},  // 104
    {166, 124},  // 105
    {170, 119},  // 106
    {81, 91},  // 107
    {76, 92},  // 108
    {86, 95},  // 109
    {35, 85},  // 110
    {108, 162},  // 111
    {128, 156},  // 112
};

const char locationList[114][26] =
{
    "Highland",                  //  0
    "Fandaria",                  //  1
    "Palemoon",                  //  2
    "Izumo",                     //  3
    "Tradnor",                   //  4
    "Topaz",                     //  5
    "Bozack",                    //  6
    "Tristan",                   //  7
    "Galfiel",                   //  8
    "Daiden",                    //  9
    "Stoic",                     // 10
    "Bloodly",                   // 11
    "Ginan",                     // 12
    "Orvue",                     // 13
    "Claystal",                  // 14
    "Magicka",                   // 15
    "Eternal",                   // 16
    "Royal",                     // 17
    "Danyan",                    // 18
    "Stalwart",                  // 19
    "Lightan",                   // 20
    "Gasparl",                   // 21
    "Roguewar",                  // 22
    "Sardia",                    // 23
    "Blazart",                   // 24
    "Sophnyk",                   // 25
    "Crystal",                   // 26
    "Starfall",                  // 27
    "Travan",                    // 28
    "Nikeral",                   // 29
    "Mikeral",                   // 30
    "Estonia",                   // 31
    "Ogrekeep",                  // 32
    "Maryware",                  // 33
    "Vlad Tower",                // 34
    "South Shrine",              // 35
    "East Shrine",               // 36  231,94
    "Snow Shrine",               // 37  177,11
    "Shadow Tower",              // 38  103,70
    "Ruinledge",                 // 39  22,82
    "Southeast Ocean",           // 40           INVALID - the AI won't go there
    "Southeast Ocean",           // 41           INVALID - the AI won't go there
    "pnt-se.Topaz",              // 42  141,105
    "twn1-w.Galfiel",            // 43  147,162
    "twn-w.Maryware",            // 44  134,149
    "twn-nw.Lightan",            // 45  109,149
    "twn-ne.Lightan",            // 46  125,149
    "pnt-n.Lightan",             // 47  116,149
    "HayateTown",                // 48  98,148
    "pnt-e.HayateTown",          // 49  104,149
    "twn-e.Stalwart",            // 50  128,122
    "twn-sw.Danyan",             // 51  130,139
    "twn-e.Mikeral",             // 52  116,139
    "twn-sw.Stalwart",           // 53  111,132
    "pnt2-s.Sophnyk",            // 54  144,63
    "twn-n.Starfall",            // 55  166,79
    "pnt.nw.Nikeral",            // 56  89,88
    "pnt-ne.Royal",              // 57  84,113
    "pnt-nw.Highland",           // 58  166,152
    "twn-e.Crystal",             // 59  186,110
    "pnt-s.twn-e.Crystal",       // 60  189,119
    "twn-se.Orvue",              // 61  202,122
    "pnt-se.Palemoon",           // 62  215,118
    "pnt-ne.Palemoon",           // 63  218,103
    "twn-ne.Claystal",           // 64  202,89
    "pnt2-nw.East Shrine",       // 65  211,79
    "pnt1-nw.East Shrine",       // 66  228,86
    "twn-s.Starfall",            // 67  161,98
    "pnt-ne.Tristan",            // 68  175,35
    "pnt1-s.Sophnyk",            // 69  145,52
    "twn-s.Sophnyk",             // 70  142,75
    "pnt-ne.Topaz",              // 71  141,88
    "pnt-nw.Topaz",              // 72  129,87
    "twn-e.Shadow Tower",        // 73  124,75
    "pnt-e.Shadow Tower",        // 74  117,70
    "pnt1-w.Shadow Tower",       // 75  95,71
    "pnt2-w.Shadow Tower",       // 76  88,68
    "twn-w.Shadow Tower",        // 77  77,68
    "pnt-sw.twn-w.Shadow Tower", // 78  74,79
    "pnt-s.Estonia",             // 79  87,108
    "twn-nw.Stalwart",           // 80  110,109
    "twn-s.Topaz",               // 81  131,105
    "twn-n.Stoic",               // 82  72,94
    "twn-n.Bloodly",             // 83  52,94
    "twn-s.Fandaria",            // 84  62,110
    "twn-se.Ruinledge",          // 85  30,89
    "twn-w.Ginan",               // 86  44,87
    "pnt-s.Ruinledge Town",      // 87  34,103
    "pnt-sw.Bloodly",            // 88  42,107
    "twn-sw.Bloodly",            // 89  38,105
    "twn-n.Ginan",               // 90  57,71
    "twn-s.Travan",              // 91  159,145
    "pnt-w.Crystal",             // 92  162,113
    "twn-s.Ogrekeep",            // 93  139,124
    "twn2-w.Galfiel",            // 94  137,166
    "pnt-w.Bozack",              // 95  89,168
    "pnt-ne.Sardia",             // 96  89,154
    "pnt-nw.Bozack",             // 97  100,161
    "pnt-ne.South Shrine",       // 98  88, 181
    "pnt-n.Ginan",               // 99  58,79
    "pnt-se.Ruinledge Town",     // 100  40,94
    "pnt-w.twn-w.Ginan",         // 101  38,85
    "pnt-w.Claystal",            // 102  174,98
    "Bastion's Town",            // 103  150,121
    "twn-nw.Nikeral",            // 104  80,82
    "twn-ne.Travan",             // 105  166,124
    "pnt-s.Crystal",             // 106  170,119
    "pnt2-nw.Estonia",           // 107  81,91
    "pnt-ne.twn-n.Stoic",        // 108  76,92
    "pnt1-nw.Estonia",           // 109  86,95
    "pnt.ne-Ruinledge Town",     // 110  35,85
    "pnt-ne.Bozack",             // 111  108,162
    "pnt-e.Lightan",             // 112  128,156
    "Player's Monarch",
};

const char itemList[73][18] = 
{
    "none",
    "Mars Blade",
    "Soul Buster",
    "Psycho Sword",
    "Gaia Sword",
    "Eclisis",
    "Murasame Sword",
    "Kusanagi Blade",
    "Moonbeam Sword",
    "Phantom Sword",
    "Moon God Sword",
    "Kamui Blade",
    "Dark Axe",
    "Thunder Axe",
    "Igneous Axe",
    "Earth Axe",
    "Javelin",
    "Battle Spear",
    "Rune Lance",
    "Magical Lance",
    "Beast Claw",
    "Wicked Claw",
    "Dark Claw",
    "StarDragon Sword",
    "StarDragon Armlet",
    "StarDragon Cane",
    "Divine Shield",
    "Sacrifice Shield",
    "Shogun Armor",
    "Gauze Armor",
    "Battle Armor",
    "Valhart's Charm",
    "Dragon's Eye",
    "Goddess Tear",
    "Astea's Ring",
    "True Ring",
    "Ambition Ring",
    "Emerald",
    "Jeweled Rod",
    "Miracle Rod",
    "Tempest",
    "Death Claw",
    "Wisdom Armlet",
    "Sage Bracelet",
    "Wisdom Armlet",
    "Sun Bracelet",
    "Moon Cane",
    "Stargem Sword",
    "Ruined Treasure",
    "Ruined Treasure",
    "Ruined Treasure",
    "Strategy Runes",
    "Ancient Runes",
    "Virtuous Runes",
    "Astea's Herb",
    "Dragon Crest",
    "Soldier Crest",
    "Honor Crest",
    "Arrow Crest",
    "Magic Crest",
    "Samurai Crest",
    "Cleric Crest",
    "Flying Crest",
    "Spirit Crest",
    "Savage Crest",
    "Dragon Statue",
    "Astea's Statue",
    "Faith Coin",
    "Bravery Coin",
    "Honor Coin",
    "Rotted Treasure",
    "Rotted Treasure",
    "Rotted Treasure",
};

/*  Division Status
   
   00 - doesn't exist
   02 - think
   03 - speed
   04 - move
   08 - run move
   09 - wait
   10 - rest
   12 - victory
   14 - ghost
   15 - ghost out
   23 - escape move
   25 - attack rest
   26 - attack move
   27 - leave
*/
const char shidanStatus[28][14] = 
{
    "doesn't exist",
    "unknown",
    "think",
    "speed",
    "move",
    "unknown",
    "unknown",
    "unknown",
    "run move",
    "wait",
    "rest",
    "unknown",
    "victory",
    "unknown",
    "ghost",
    "ghost out",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "escape rest",
    "escape move",
    "unknown",
    "attack rest",
    "attack move",
    "leave"
};

DragonForce::DragonForce(const DragonForce& rhsDF)
: fr(rhsDF.fr),
  fw(rhsDF.fw)
{
    int i;
    int j;

    drFileName = rhsDF.drFileName;
    playingAs  = rhsDF.playingAs;

    for(i = 0; i < 171; i++)
    {
        genArr[i] = rhsDF.genArr[i];
        divArr[i] = rhsDF.divArr[i];
    }

    for(i = 0; i < 34; i++)
        casArr[i] = rhsDF.casArr[i];

    for(int i = 0; i < 8; i++)
        kingdoms[i] = rhsDF.kingdoms[i];

    j = rhsDF.capHolder.numHeld;
    for(int i = 0; i < j; i++)
        capHolder.holdArea[i] = rhsDF.capHolder.holdArea[i];

    for(i = 0; i < rhsDF.itemInv.numItems; i++)
        itemInv.items[i] = rhsDF.itemInv.items[i];
    itemInv.numItems = rhsDF.itemInv.numItems;
}


DragonForce& DragonForce::operator=(const DragonForce& rhsDF)
{
    int i;
    int j;

    if(this == &rhsDF)
        return *this;

    drFileName = rhsDF.drFileName;
    playingAs  = rhsDF.playingAs;

    fr = rhsDF.fr;
    fw = rhsDF.fw;

    for(i = 0; i < 171; i++)
    {
        genArr[i] = rhsDF.genArr[i];
        divArr[i] = rhsDF.divArr[i];
    }

    for(i = 0; i < 34; i++)
        casArr[i] = rhsDF.casArr[i];

    for(int i = 0; i < 8; i++)
        kingdoms[i] = rhsDF.kingdoms[i];

    j = rhsDF.capHolder.numHeld;
    for(int i = 0; i < j; i++)
        capHolder.holdArea[i] = rhsDF.capHolder.holdArea[i];

    for(i = 0; i < rhsDF.itemInv.numItems; i++)
        itemInv.items[i] = rhsDF.itemInv.items[i];
    itemInv.numItems = rhsDF.itemInv.numItems;

    return *this;
}

void DragonForce::setMonarch(void)
{
    playingAs = fr.findPlayingAs();
    genArr[playingAs].isPlayer = 1;
    
    return;
}

void DragonForce::initGenerals(void)
{
    for(int i = 0; i < 171; i++)
        genArr[i] = General(i);

    return;
}

void DragonForce::initCastles(void)
{
    int location = 0;
    int genIndex = -1;

    for(int j = 0; j < 171; j++) //filling the castles with generals & captives
    {
        location = genArr[j].location;
        genIndex = genArr[j].listIndex;
        if((genArr[j].fixedLocation) && (location < 34))
        {
            if(genArr[j].fieldStatus1 == 3)
            {
                casArr[location].addGeneral_init(genIndex);
                if(genArr[j].fieldStatus2 == 2)
                    casArr[location].setLeader(genIndex);
            }
            if(genArr[j].fieldStatus1 == 4)
                casArr[location].addCaptive_init(genIndex);
        }
    }
    
    for(int i = 0; i < 34; i++) //setting the other castle information
    {
        casArr[i].setCastleNum(i);
        casArr[i].setRuler(castleOwnership[i]);
        casArr[i].setExperience(castleExperience[i]);
        casArr[i].setCastleName(castlesNameList[i]);
        casArr[i].setLevel((castleExperience[i] > 0) ?
            (castleLevel[i] = castleExperience[i] / 1200 + 1) :
            (castleLevel[i] = 0));
        castleLevel[i] == 0 ?
            (casArr[i].setTroopCount(0)) :
            (casArr[i].setTroopCount(castleCurrentTroops[i])); //this part necessary to fix level 0 castles; i.e. magicka
        casArr[i].setMaxTroops((casArr[i].level + 5) * 10);
        casArr[i].setExpNext(casArr[i].level * 1200);
        casArr[i].setXCoordinate(locationCoordinates[i][0]);
        casArr[i].setYCoordinate(locationCoordinates[i][1]);
    }
    if((genArr[playingAs].fieldStatus1 == 3) && (genArr[playingAs].fieldStatus2 == 2))
        casArr[genArr[playingAs].location].setHasMonarch(true);

    return;
}

void DragonForce::initDivisions(void)
{
    int division = 0;
    int genIndex = -1;

    for(int i = 0; i < 171; i++)
    {
        division = genArr[i].location;
        genIndex = genArr[i].listIndex;
        if(!genArr[i].fixedLocation)
        {
            if(genArr[i].fieldStatus1 == 3)
            {
                divArr[division].addMember_init(genIndex);
                if(genArr[i].fieldStatus2 == 1)
                    divArr[division].setLeader(genIndex);
            }
            if(genArr[i].fieldStatus1 == 4)
                divArr[division].addCaptive_init(genIndex);

            if(genArr[i].isPlayer)
                divArr[division].setHasPlayer(true);

            divArr[division].setRuler(officerOwner[i]);
            divArr[division].setStatus(divisionStatus[division]);
            divArr[division].setDivNum(division);
            divArr[division].setOrigin(divisionOrigin[division]);
            divArr[division].setGoal(divisionDestination[division]);
            divArr[division].setPrev(divisionPrevious[division]);
            divArr[division].setNext(divisionNext[division]);
            divArr[division].setXCoordinate(divisionXcoordinate[division] / 8);  //can also do a right shift by 3 for this line and the next, but viewing assembly output shows 
            divArr[division].setYCoordinate(divisionYcoordinate[division] / 8);  //that my compiler is already optimizing a right shift of 3 in place of the division by 8
        }
    }

    findActiveDiv();
    for(int i = 0; i < 171; i++)
    {
        if(activeDivisions[i])
            for(int j = 0; j < divArr[i].numMembers; j++)
                divArr[i].troopCount += genArr[divArr[i].members[j]].currentTroopCount;
    }

    return;
}

void DragonForce::initItemInv(void)
{
    for(int i = 0; i < 256; i++)
    {
        if(itemInventoryBuffer[i])
        {
            itemInv.items[i] = itemInventoryBuffer[i];
            itemInv.numItems++;        
        }
        else
            i = 256;
    }

    return;
}

void DragonForce::initKingdoms(void)
{
    for(int i = 0; i < 8; i++) //making sure everything is 0
    {
        kingdoms[i].numCastles    = 0;
        kingdoms[i].numCaptives   = 0;
        kingdoms[i].numGenerals   = 0;
        kingdoms[i].kingdomWins   = 0;
        kingdoms[i].kingdomLosses = 0;
        
        for(int j = 0; j < 34; j++)
            kingdoms[i].ownedCastles[j] = 171;

        for(int j = 0; j < 171; j++)
        {
            kingdoms[i].ownedGenerals[j] = 0;
            kingdoms[i].ownedCaptives[j] = 0;
        }
    }

    for(int i = 0; i < 8; i++)
    {
        kingdoms[i].kingdomName  = castlesNameList[i];
        kingdoms[i].kingdomRuler = generalsNameList[i];
    }

    int casOwner = 0;
    int casCount = 0;
    for(int i = 0; i < 34; i++)  //who owns which castles
    {
        casOwner = castleOwnership[i];
        if(casOwner < 8)
        {
            casCount = kingdoms[casOwner].numCastles;
            kingdoms[casOwner].ownedCastles[casCount] = i;
            kingdoms[casOwner].numCastles++;
        }
    }

    int genOwner = 0;
    int genCount = 0;
    for(int i = 0; i < 171; i++) //which generals in which kingdoms
    {
        genOwner = officerOwner[i];
        if(genOwner < 8)
        {
            if(genArr[i].fieldStatus1 == 3) //if a general in this kingdom
            {
                genCount = kingdoms[genOwner].numGenerals;
                kingdoms[genOwner].ownedGenerals[genCount] = i;
                kingdoms[genOwner].numGenerals++;
                kingdoms[genOwner].kingdomWins   += genArr[i].newWins;
                kingdoms[genOwner].kingdomLosses += genArr[i].newLosses;
            }
            if(genArr[i].fieldStatus1 == 4) //if captive of this kingdom
            {
                genCount = kingdoms[genOwner].numCaptives;
                kingdoms[genOwner].ownedCaptives[genCount] = i;
                kingdoms[genOwner].numCaptives++;
            }
        }
    }

    return;
}

void DragonForce::findActiveDiv(void)
{
    for(int i = 0; i < 171; i++)
    {
        if(!(genArr[i].fixedLocation))               //if the general's location isn't fixed, they are marching
            activeDivisions[locationNumBuff[i]] = 1; //ex: if their location is 5, division number 5 is marked active
    }

    return;
}

void DragonForce::findNewRulers(const int oldRuler)
{
    for(int i = 0; i < 34; i++)
        if(casArr[i].ruler == oldRuler)
            casArr[i].changeRuler(casArr[i].generals[0]);

    return;
}

void DragonForce::addItemsInv(const int* const items, const int count)
{
    int numItems = itemInv.numItems;

    if(count > 0)
    {
        for(int i = 0; (i < count) && (numItems < 256); i++)
        {
            itemInv.items[numItems] = items[i];
            numItems++;
        }

        itemInv.numItems = numItems;
        g_insertionSort((int*)itemInv.items, itemInv.numItems);

        for(int i = 0; i < 256; i++)
            itemInventoryBuffer[i] = itemInv.items[i];
    }

    return;
}

void DragonForce::delItemsInv(const int* const items, const int count)
{
    for(int i = 0; i < count; i++)
        itemInv.items[items[i]] = 171;

    g_insertionSort(itemInv.items, itemInv.numItems);
    itemInv.numItems -= count;

    for(int i = 0; i < itemInv.numItems; i++)
        itemInventoryBuffer[i] = itemInv.items[i];

    for(int i = itemInv.numItems; i < 256; i++)
        itemInventoryBuffer[i] = 0;

    return;
}

////////////////////////////////////////////////////////////////////////////////
//
// GLOBALS
//
////////////////////////////////////////////////////////////////////////////////
ushort g_packByte(ushort highNibble, ushort lowNibble)
{
    return lowNibble | (highNibble << 4);
}

ushort g_rotateLeft(ushort num, const int bits)
{
    return ((num << bits) | num >> ((sizeof(num) * 8) - bits));
}

void g_insertionSort( int* const arr, const int size ) //standard insertion sort
{
    int temp;
    int located; //used as bool
    int elementMover;
    int lastElement;

    temp         = 0;
    located      = 0;
    elementMover = 0;
    lastElement  = size - 1;

    for(int current = 1; current <= lastElement; current++)
    {
        located = 0;
        temp = arr[current];
        for(elementMover = current - 1; elementMover >= 0 && !located;)
            if(temp < arr[elementMover])
            {
                arr[elementMover + 1] = arr[elementMover];
                elementMover--;
            }
            else
                located = 1;
        arr[elementMover + 1] = temp;
    }

    return;
}
