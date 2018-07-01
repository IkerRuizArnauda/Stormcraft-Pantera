#include "stdafx.h"
#include "RealmServer.h"
#include "Globals.h"
#include "Creature.h"
#include "CreatureTemplate.h"
#include "ItemTemplate.h"
#include "SpawnPoint.h"
#include "LootTable.h"
#include "Zone.h"
#include "PathGroup.h"
#include "ChatManager.h"
#include "DataBuffer.h"
#include "Debug.h"
#include "Guild.h"
#include "antidebuggers.h"
#include "Corpse.h"
#include "GameObjectTemplate.h"
#include "NPCText.h"
#include "Mail.h"
#include "Quest.h"
#include "TrainerTemplate.h"
#include "ConsoleDlg.h"
#include "dbc_structs.h"
#include "Graveyards.h"

#define SHLocations Graveyards

#define FORCE_PKTLOG // HACK HACK HACK

// all gravyards as of 1.12 from the worldsafeloc dbc
_Graveyard Graveyards[NUM_GRAVEYARDS]=
{
	{ {-9115.0f, 423.0f, 96.0f}, 0}, // Stormwind
	{ {-9271.0f, -2305.0f, 71.0f}, 0}, // Redridge Mountains
	{ {-10774.2626953f, -1189.671875f, 33.1494255066f}, 0}, // Duskwood, Darkshire
	{ {-10546.9003906f, 1197.23999023f, 31.7262992859f}, 0}, // Westfall, Sentinel Hill
	{ {-5687.0f, -515.0f, 398.0f}, 0}, // Dun Morogh
	{ {-5351.22900391f, -2881.58227539f, 340.942352295f}, 0}, // Loch Modan, Thelsamar
	{ {-3289.1237793f, -2435.99121094f, 18.5965900421f}, 0}, // Wetlands, Crossroads
	{ {-6289.91113281f, -3493.10791016f, 251.482772827f}, 0}, // Badlands, Graveyard NE 
	{ {-592.60144043f, -2523.49243164f, 91.7880325317f}, 1}, // The Barrens, The Crossroads
	{ {-1443.48803711f, 1973.36962891f, 85.4907150269f}, 1}, // Desolace, Ghost Walker Post
	{ {233.457992554f, -4793.72998047f, 10.1880998611f}, 1}, // Durotar, Razor Hill
	{ {1357.09997559f, -4412.00976563f, 28.3840999603f}, 1}, // Durotar, Orgrimmar
	{ {-2944.55639648f, -153.215026855f, 65.786026001f}, 1}, // Mulgore, Red Cloud Mesa
	{ {6739.18994141f, 209.992599487f, 23.2845611572f}, 1}, // Darkshore, Auberdine
	{ {-11110.3769531f, -1833.24072266f, 71.8641967773f}, 0}, // Deadwind Pass, Morgan's Plot
	{ {-4656.0f, -1765.0f, -41.0f}, 1}, // Thousand Needles, The Great Lift
	{ {-661.528442383f, -485.309020996f, 385.887908936f}, 37}, // Plains of Snow - Horde Start
	{ {-6432.25634766f, -278.292114258f, 3.79410505295f}, 1}, // Silithus, Valor's Rest
	{ {-2175.18969727f, -342.026916504f, -5.51232481003f}, 1}, // Mulgore, Bloodhoof Village
	{ {10054.2998047f, 2117.12011719f, 1329.63000488f}, 1}, // Teldrassil, Darnassus
	{ {9701.25488281f, 945.620422363f, 1291.35510254f}, 1}, // Teldrassil, Dolanaar
	{ {2633.41113281f, -629.735168457f, 107.581253052f}, 1}, // Ashenvale, Astranaar
	{ {10384.8095703f, 811.531188965f, 1317.53820801f}, 1}, // Teldrassil, Aldrassil
	{ {1882.93994141f, 1629.10998535f, 94.4175033569f}, 0}, // Tirisfal Glades, Deathknell
	{ {1822.60998535f, 214.673995972f, 60.1402015686f}, 0}, // Tirisfal Glades, Undercity
	{ {516.194335938f, 1589.80664062f, 127.544937134f}, 0}, // Silverpine Forest, The Sepulcher
	{ {-18.6776809692f, -981.171447754f, 55.8376693726f}, 0}, // Hillsbrad Foothills, Tarren Mill
	{ {-1472.28942871f, -2617.95874023f, 49.2765197754f}, 0}, // Arathi Highlands
	{ {-6164.22607422f, 336.321136475f, 399.793365479f}, 0}, // Dun Morogh, Anvilmar
	{ {-5680.04443359f, -518.920471191f, 396.27432251f}, 0}, // Dun Morogh, Kharanos
	{ {-5049.45019531f, -809.697021484f, 495.12701416f}, 0}, // Dun Morogh, Ironforge
	{ {-6805.0f, -2287.18994141f, 280.75201416f}, 0}, // Badlands, Kargath
	{ {-9403.24511719f, -2037.6920166f, 58.3687400818f}, 0}, // Redridge Mountains, Lakeshire
	{ {-8935.32519531f, -188.646270752f, 80.4164657593f}, 0}, // Elwynn Forest, Northshire
	{ {-9339.45605469f, 171.408447266f, 61.5618095398f}, 0}, // Elwynn Forest, Goldshire
	{ {-9151.98046875f, 410.944000244f, 92.6966018677f}, 0}, // Elwynn Forest, Stormwind
	{ {-10567.8134766f, -3377.203125f, 22.2532196045f}, 0}, // Swamp of Sorrows, Stonard
	{ {-14284.9619141f, 288.447174072f, 32.3320388794f}, 0}, // Stranglethorn Vale, Booty Bay
	{ {8706.0f, 965.0f, 13.2700004578f}, 1}, // Teldrassil, Rut'theran Village
	{ {-732.799377441f, -592.501953125f, 22.6630458832f}, 0}, // Hillsbrad Foothills, Southshore
	{ {-157.409194946f, 31.2062721252f, 77.0505981445f}, 30}, // Alterac Valley, Snowfall Graveyard (Mid)
	{ {-3525.70605469f, -4315.45507813f, 6.99560689926f}, 1}, // Dustwallow Marsh, Theramore Isle
	{ {-7190.94921875f, -3944.65234375f, 9.22739124298f}, 1}, // Tanaris, Gadgetzan
	{ {-2517.75f, -1972.64001465f, 91.7837982178f}, 1}, // The Barrens, Camp Taurajo
	{ {-1081.40002441f, -3478.67993164f, 63.6066017151f}, 1}, // The Barrens, Ratchet
	{ {-448.188598633f, -1027.86303711f, 430.724334717f}, 37}, // Plains of Snow - Alliance Start
	{ {2348.66992188f, 492.027008057f, 33.3665008545f}, 0}, // Tirisfal Glades, Brill
	{ {-4596.40429688f, 3229.43432617f, 8.99376392365f}, 1}, // Feralas, Feathermoon Stronghold
	{ {-4439.96679688f, 370.153442383f, 51.356552124f}, 1}, // Feralas, Camp Mojache
	{ {-5530.28271484f, -3459.2800293f, -45.7443695068f}, 1}, // Thousand Needles, Shimmering Flats
	{ {323.512634277f, -2227.19580078f, 137.617462158f}, 0}, // The Hinterlands, Aerie Peak
	{ {2681.05786133f, -4009.75390625f, 107.848632813f}, 1}, // Azshara, Talrendis Point
	{ {-10846.5742188f, -2949.48779297f, 13.2272319794f}, 0}, // Blasted Lands, Dreadmaul Hold
	{ {-11542.5595703f, -228.636505127f, 27.8427429199f}, 0}, // Stranglethorn Vale, Northern Stranglethorn
	{ {898.260986328f, 434.529998779f, 65.727897644f}, 1}, // Stonetalon Mountains, Webwinder Path
	{ {2604.52001953f, -543.390014648f, 88.9996032715f}, 0}, // Tirisfal Glades, Faol's Rest
	{ {3806.53955078f, -1600.29138184f, 218.831237793f}, 1}, // Felwood, Morlos'Aran
	{ {-7205.56494141f, -2436.67431641f, -218.160964966f}, 1}, // Un'Goro Crater, The Marshlands
	{ {4291.28271484f, 96.9557266235f, 43.0752563477f}, 1}, // Darkshore, Twilight Vale
	{ {-3347.7199707f, -856.713012695f, 1.05955004692f}, 0}, // Wetlands, Baradin Bay
	{ {908.323303223f, -1520.28613281f, 55.0371780396f}, 0}, // Western Plaguelands, Chillwind Camp
	{ {2116.78979492f, -5287.33691406f, 81.1320419312f}, 0}, // Eastern Plaguelands, Light's Hope Chapel
	{ {6875.75976563f, -4661.54003906f, 701.093994141f}, 1}, // Winterspring, Everlook
	{ {2421.72363281f, -2953.61889648f, 123.473457336f}, 1}, // Ashenvale, Kargathia
	{ {16310.3251953f, 16268.9394531f, 69.444442749f}, 451}, // Programmer Isle
	{ {16223.8232422f, 16278.5732422f, 20.8912754059f}, 451}, // Programmer Isle
	{ {1750.34350586f, -669.789855957f, 44.5698432922f}, 0}, // Western Plaguelands, Bulwark
	{ {16310.3251953f, 16268.9394531f, 69.444442749f}, 1}, // GM Island
	{ {2942.76000977f, -6037.12988281f, 5.16996002197f}, 1}, // Azshara, Southridge Beach
	{ {-818.556640625f, -619.254882813f, 54.038898468f}, 30}, // Alterac Valley, Horde Safe
	{ {873.00177002f, -491.283630371f, 96.5419311523f}, 30}, // Alterac Valley, Alliance Safe
	{ {908.323303223f, -1520.28613281f, 55.0371780396f}, 0}, // TEST for GM Client Only - Do Not Bug
	{ {4788.77978516f, -6845.0f, 89.7901000977f}, 1}, // Azshara, Legash Encampment
	{ {-3127.68994141f, -3046.93994141f, 33.8312988281f}, 1}, // Dustwallow Marsh, Brackenwall Village
	{ {-7490.45019531f, -2132.62011719f, 142.186004639f}, 0}, // Burning Steppes, Flame Crest
	{ {7426.0f, -2809.0f, 464.0f}, 1}, // Moonglade
	{ {1392.0f, -3701.0f, 77.0f}, 0}, // Eastern Plaguelands, Darrowshire
	{ {5935.47021484f, -1217.75f, 383.20199585f}, 1}, // Felwood, Irontree Woods
	{ {-6450.60986328f, -1113.51000977f, 308.022003174f}, 0}, // Searing Gorge, Thorium Point
	{ {-778.0f, -4985.0f, 19.0f}, 1}, // Durotar, Sen'jin Village
	{ {16614.8105469f, 16662.9785156f, 21.34217453f}, 451}, // Programmer Isle, Bucklers Cemetery 2
	{ {16620.7402344f, 16622.7011719f, 21.3382472992f}, 451}, // Programmer Isle, Bucklers Cemetery 1
	{ {16619.5195313f, 16577.4550781f, 43.9017753601f}, 451}, // Programmer Isle, Bucklers Cemetery 3
	{ {676.0f, -374.0f, 30.0f}, 30}, // Alterac Valley, Stormpike Graveyard (Hi)
	{ {-1090.47680664f, -253.308670044f, 57.6723709106f}, 30}, // Alterac Valley, Frostwolf Graveyard (Lo)
	{ {-634.634887695f, -4296.03369141f, 40.525428772f}, 1}, // Durotar, Valley of Trials
	{ {73.417755127f, -496.433105469f, 48.731918335f}, 30}, // Alterac Valley, PvP Alliance Choke Graveyard (A-choke)
	{ {-531.217834473f, -405.231384277f, 49.5513763428f}, 30}, // Alterac Valley, PvP Horde Choke Graveyard (H-choke)
	{ {-1496.06506348f, -333.338409424f, 101.134803772f}, 30}, // Alterac Valley, Frostwolf Relief Hut (H-base)
	{ {643.0f, 44.0f, 69.740196228f}, 30}, // Alterac Valley, Stormpike Aid Station (A-base)
	{ {1523.81152344f, 1481.75756836f, 352.007598877f}, 489}, // Warsong Gulch - Alliance Enter Loc
	{ {933.331481934f, 1433.72399902f, 345.535675049f}, 489}, // Warsong Gulch - Horde Enter Loc
	{ {1415.32995605f, 1554.79003906f, 343.156005859f}, 489}, // Warsong Gulch - Alliance Rez Loc
	{ {1029.14001465f, 1387.48999023f, 340.835998535f}, 489}, // Warsong Gulch - Horde Rez Loc
	{ {-291.0f, -4374.0f, 107.0f}, 0}, // The Hinterlands, The Overlook Cliffs
	{ {1035.27001953f, -2104.2800293f, 122.944999695f}, 1}, // Warsong Gulch - Horde Exit Loc
	{ {1459.17004395f, -1858.67004395f, 124.762001038f}, 1}, // Warsong Gulch - Alliance Exit Loc
	{ {101.143997192f, -184.934005737f, 127.34400177f}, 0}, // Alterac Valley, Alliance Exit
	{ {536.494995117f, -1085.7199707f, 106.269996643f}, 0}, // Alterac Valley, Horde Exit
	{ {-4590.40869141f, 1632.08068848f, 93.9738311768f}, 1}, // Feralas, Dire Maul
	{ {1177.7800293f, -4464.24023438f, 21.3539009094f}, 1}, // Durotar, Northern Durotar
	{ {-981.916992188f, -74.6464996338f, 20.126499176f}, 1}, // Mulgore, Thunder Bluff
	{ {-5165.52001953f, -874.664001465f, 507.177001953f}, 0}, // Dun Morogh, Gates of Ironforge
	{ {1780.10998535f, 221.761001587f, 59.6169013977f}, 0}, // Tirisfal Glades, Ruins of Lordaeron
	{ {-9552.45996094f, -1374.05004883f, 51.2332000732f}, 0}, // Elwynn Forest, Eastvale Logging Camp
	{ {1236.89001465f, -2411.98999023f, 60.6800003052f}, 0}, // Western Plaguelands, Caer Darrow
	{ {684.013977051f, 681.219970703f, -12.9159002304f}, 529}, // Arathi Basin - Horde Entrance
	{ {1313.90002441f, 1310.73999023f, -9.010430336f}, 529}, // Arathi Basin - Alliance Entrance
	{ {-831.880981445f, -3518.52001953f, 72.4831008911f}, 0}, // Arathi Basin - Horde Exit
	{ {-1215.58996582f, -2531.75f, 21.6734008789f}, 0}, // Arathi Basin - Alliance Exit
	{ {834.726379395f, 784.97869873f, -57.081943512f}, 529}, // Arathi Basin - Graveyard, H-Mid (Farm)
	{ {1016.58831787f, 955.184692383f, -42.8286933899f}, 529}, // Arathi Basin - Graveyard, Mid (Blacksmith)
	{ {1201.86950684f, 1163.13061523f, -56.2859687805f}, 529}, // Arathi Basin - Graveyard, A-Mid (Stables)
	{ {1211.52368164f, 781.556945801f, -82.7095108032f}, 529}, // Arathi Basin - Graveyard, ALT-N (Gold Mine)
	{ {772.75567627f, 1213.11376953f, 15.7973918915f}, 529}, // Arathi Basin - Graveyard, ALT-S (Lumber Mill)
	{ {1354.69995117f, 1270.27001953f, -11.1290998459f}, 529}, // Arathi Basin - Graveyard, A-Base (Trollbane Hall)
	{ {713.710021973f, 638.364013672f, -10.5999002457f}, 529}, // Arathi Basin - Graveyard, H-Base (Defiler's Den)
	{ {2647.55004883f, -4014.38989258f, 105.93800354f}, 0}, // Eastern Plaguelands, Blackwood Lake
	{ {-6831.31738281f, 891.437316895f, 33.866268158f}, 1}, // Silithus, Cenarion Hold
	{ {-10606.7998047f, 294.04800415f, 31.800699234f}, 0} // Duskwood, Ravenhill
};

_Graveyard GetGraveyard(_Location Loc, unsigned long Continent)
{
	_Graveyard Graveyard={0,0,0};
	float bestdist=1e30f; //closest graveyard so far
	float curdist=0; //current distance

	for (int i=0; i<NUM_GRAVEYARDS; i++)
	{
		if (Graveyards[i].Continent == Continent)
		{
			curdist = CRegionManager::Distance(Loc,Graveyards[i].Loc); //two dimensional distance
			if (curdist < bestdist) //if this distance is closer...
			{
				Graveyard = Graveyards[i];
				bestdist = curdist;
			}
		}
	}
	return Graveyard;
}

char *OpcodeNames[]={
	"MSG_NULL_ACTION",
	"CMSG_BOOTME",
	"CMSG_DBLOOKUP",
	"SMSG_DBLOOKUP",
	"CMSG_QUERY_OBJECT_POSITION",
	"SMSG_QUERY_OBJECT_POSITION",
	"CMSG_QUERY_OBJECT_ROTATION",
	"SMSG_QUERY_OBJECT_ROTATION",
	"CMSG_WORLD_TELEPORT",
	"CMSG_TELEPORT_TO_UNIT",
	"CMSG_ZONE_MAP",
	"SMSG_ZONE_MAP",
	"CMSG_DEBUG_CHANGECELLZONE",
	"CMSG_EMBLAZON_TABARD_OBSOLETE",
	"CMSG_UNEMBLAZON_TABARD_OBSOLETE",
	"CMSG_RECHARGE",
	"CMSG_LEARN_SPELL",
	"CMSG_CREATEMONSTER",
	"CMSG_DESTROYMONSTER",
	"CMSG_CREATEITEM",
	"CMSG_CREATEGAMEOBJECT",
	"CMSG_MAKEMONSTERATTACKME",
	"CMSG_MAKEMONSTERATTACKGUID",
	"CMSG_ENABLEDEBUGCOMBATLOGGING_OBSOLETE",
	"CMSG_FORCEACTION",
	"CMSG_FORCEACTIONONOTHER",
	"CMSG_FORCEACTIONSHOW",
	"SMSG_FORCEACTIONSHOW",
	"SMSG_ATTACKERSTATEUPDATEDEBUGINFO_OBSOLETE",
	"SMSG_DEBUGINFOSPELL_OBSOLETE",
	"SMSG_DEBUGINFOSPELLMISS_OBSOLETE",
	"SMSG_DEBUG_PLAYER_RANGE_OBSOLETE",
	"CMSG_UNDRESSPLAYER",
	"CMSG_BEASTMASTER",
	"CMSG_GODMODE",
	"SMSG_GODMODE",
	"CMSG_CHEAT_SETMONEY",
	"CMSG_LEVEL_CHEAT",
	"CMSG_PET_LEVEL_CHEAT",
	"CMSG_LEVELUP_CHEAT_OBSOLETE",
	"CMSG_COOLDOWN_CHEAT",
	"CMSG_USE_SKILL_CHEAT",
	"CMSG_FLAG_QUEST",
	"CMSG_FLAG_QUEST_FINISH",
	"CMSG_CLEAR_QUEST",
	"CMSG_SEND_EVENT",
	"CMSG_DEBUG_AISTATE",
	"SMSG_DEBUG_AISTATE",
	"CMSG_DISABLE_PVP_CHEAT",
	"CMSG_ADVANCE_SPAWN_TIME",
	"CMSG_PVP_PORT_OBSOLETE",
	"CMSG_AUTH_SRP6_BEGIN",
	"CMSG_AUTH_SRP6_PROOF",
	"CMSG_AUTH_SRP6_RECODE",
	"CMSG_CHAR_CREATE",
	"CMSG_CHAR_ENUM",
	"CMSG_CHAR_DELETE",
	"SMSG_AUTH_SRP6_RESPONSE",
	"SMSG_CHAR_CREATE",
	"SMSG_CHAR_ENUM",
	"SMSG_CHAR_DELETE",
	"CMSG_PLAYER_LOGIN",
	"SMSG_NEW_WORLD",
	"SMSG_TRANSFER_PENDING",
	"SMSG_TRANSFER_ABORTED",
	"SMSG_CHARACTER_LOGIN_FAILED",
	"SMSG_LOGIN_SETTIMESPEED",
	"SMSG_GAMETIME_UPDATE",
	"CMSG_GAMETIME_SET",
	"SMSG_GAMETIME_SET",
	"CMSG_GAMESPEED_SET",
	"SMSG_GAMESPEED_SET",
	"CMSG_SERVERTIME",
	"SMSG_SERVERTIME",
	"CMSG_PLAYER_LOGOUT",
	"CMSG_LOGOUT_REQUEST",
	"SMSG_LOGOUT_RESPONSE",
	"SMSG_LOGOUT_COMPLETE",
	"CMSG_LOGOUT_CANCEL",
	"SMSG_LOGOUT_CANCEL_ACK",
	"CMSG_NAME_QUERY",
	"SMSG_NAME_QUERY_RESPONSE",
	"CMSG_PET_NAME_QUERY",
	"SMSG_PET_NAME_QUERY_RESPONSE",
	"CMSG_GUILD_QUERY",
	"SMSG_GUILD_QUERY_RESPONSE",
	"CMSG_ITEM_QUERY_SINGLE",
	"CMSG_ITEM_QUERY_MULTIPLE",
	"SMSG_ITEM_QUERY_SINGLE_RESPONSE",
	"SMSG_ITEM_QUERY_MULTIPLE_RESPONSE",
	"CMSG_PAGE_TEXT_QUERY",
	"SMSG_PAGE_TEXT_QUERY_RESPONSE",
	"CMSG_QUEST_QUERY",
	"SMSG_QUEST_QUERY_RESPONSE",
	"CMSG_GAMEOBJECT_QUERY",
	"SMSG_GAMEOBJECT_QUERY_RESPONSE",
	"CMSG_CREATURE_QUERY",
	"SMSG_CREATURE_QUERY_RESPONSE",
	"CMSG_WHO",
	"SMSG_WHO",
	"CMSG_WHOIS",
	"SMSG_WHOIS",
	"CMSG_FRIEND_LIST",
	"SMSG_FRIEND_LIST",
	"SMSG_FRIEND_STATUS",
	"CMSG_ADD_FRIEND",
	"CMSG_DEL_FRIEND",
	"SMSG_IGNORE_LIST",
	"CMSG_ADD_IGNORE",
	"CMSG_DEL_IGNORE",
	"CMSG_GROUP_INVITE",
	"SMSG_GROUP_INVITE",
	"CMSG_GROUP_CANCEL",
	"SMSG_GROUP_CANCEL",
	"CMSG_GROUP_ACCEPT",
	"CMSG_GROUP_DECLINE",
	"SMSG_GROUP_DECLINE",
	"CMSG_GROUP_UNINVITE",
	"CMSG_GROUP_UNINVITE_GUID",
	"SMSG_GROUP_UNINVITE",
	"CMSG_GROUP_SET_LEADER",
	"SMSG_GROUP_SET_LEADER",
	"CMSG_LOOT_METHOD",
	"CMSG_GROUP_DISBAND",
	"SMSG_GROUP_DESTROYED",
	"SMSG_GROUP_LIST",
	"SMSG_PARTY_MEMBER_STATS",
	"SMSG_PARTY_COMMAND_RESULT",
	"UMSG_UPDATE_GROUP_MEMBERS",
	"CMSG_GUILD_CREATE",
	"CMSG_GUILD_INVITE",
	"SMSG_GUILD_INVITE",
	"CMSG_GUILD_ACCEPT",
	"CMSG_GUILD_DECLINE",
	"SMSG_GUILD_DECLINE",
	"CMSG_GUILD_INFO",
	"SMSG_GUILD_INFO",
	"CMSG_GUILD_ROSTER",
	"SMSG_GUILD_ROSTER",
	"CMSG_GUILD_PROMOTE",
	"CMSG_GUILD_DEMOTE",
	"CMSG_GUILD_LEAVE",
	"CMSG_GUILD_REMOVE",
	"CMSG_GUILD_DISBAND",
	"CMSG_GUILD_LEADER",
	"CMSG_GUILD_MOTD",
	"SMSG_GUILD_EVENT",
	"SMSG_GUILD_COMMAND_RESULT",
	"UMSG_UPDATE_GUILD",
	"CMSG_MESSAGECHAT",
	"SMSG_MESSAGECHAT",
	"CMSG_JOIN_CHANNEL",
	"CMSG_LEAVE_CHANNEL",
	"SMSG_CHANNEL_NOTIFY",
	"CMSG_CHANNEL_LIST",
	"SMSG_CHANNEL_LIST",
	"CMSG_CHANNEL_PASSWORD",
	"CMSG_CHANNEL_SET_OWNER",
	"CMSG_CHANNEL_OWNER",
	"CMSG_CHANNEL_MODERATOR",
	"CMSG_CHANNEL_UNMODERATOR",
	"CMSG_CHANNEL_MUTE",
	"CMSG_CHANNEL_UNMUTE",
	"CMSG_CHANNEL_INVITE",
	"CMSG_CHANNEL_KICK",
	"CMSG_CHANNEL_BAN",
	"CMSG_CHANNEL_UNBAN",
	"CMSG_CHANNEL_ANNOUNCEMENTS",
	"CMSG_CHANNEL_MODERATE",
	"SMSG_UPDATE_OBJECT",
	"SMSG_DESTROY_OBJECT",
	"CMSG_USE_ITEM",
	"CMSG_OPEN_ITEM",
	"CMSG_READ_ITEM",
	"SMSG_READ_ITEM_OK",
	"SMSG_READ_ITEM_FAILED",
	"SMSG_ITEM_COOLDOWN",
	"CMSG_GAMEOBJ_USE",
	"CMSG_GAMEOBJ_CHAIR_USE_OBSOLETE",
	"SMSG_GAMEOBJECT_CUSTOM_ANIM",
	"CMSG_AREATRIGGER",
	"MSG_MOVE_START_FORWARD",
	"MSG_MOVE_START_BACKWARD",
	"MSG_MOVE_STOP",
	"MSG_MOVE_START_STRAFE_LEFT",
	"MSG_MOVE_START_STRAFE_RIGHT",
	"MSG_MOVE_STOP_STRAFE",
	"MSG_MOVE_JUMP",
	"MSG_MOVE_START_TURN_LEFT",
	"MSG_MOVE_START_TURN_RIGHT",
	"MSG_MOVE_STOP_TURN",
	"MSG_MOVE_START_PITCH_UP",
	"MSG_MOVE_START_PITCH_DOWN",
	"MSG_MOVE_STOP_PITCH",
	"MSG_MOVE_SET_RUN_MODE",
	"MSG_MOVE_SET_WALK_MODE",
	"MSG_MOVE_TOGGLE_LOGGING",
	"MSG_MOVE_TELEPORT",
	"MSG_MOVE_TELEPORT_CHEAT",
	"MSG_MOVE_TELEPORT_ACK",
	"MSG_MOVE_TOGGLE_FALL_LOGGING",
	"MSG_MOVE_FALL_LAND",
	"MSG_MOVE_START_SWIM",
	"MSG_MOVE_STOP_SWIM",
	"MSG_MOVE_SET_RUN_SPEED_CHEAT",
	"MSG_MOVE_SET_RUN_SPEED",
	"MSG_MOVE_SET_RUN_BACK_SPEED_CHEAT",
	"MSG_MOVE_SET_RUN_BACK_SPEED",
	"MSG_MOVE_SET_WALK_SPEED_CHEAT",
	"MSG_MOVE_SET_WALK_SPEED",
	"MSG_MOVE_SET_SWIM_SPEED_CHEAT",
	"MSG_MOVE_SET_SWIM_SPEED",
	"MSG_MOVE_SET_SWIM_BACK_SPEED_CHEAT",
	"MSG_MOVE_SET_SWIM_BACK_SPEED",
	"MSG_MOVE_SET_ALL_SPEED_CHEAT",
	"MSG_MOVE_SET_TURN_RATE_CHEAT",
	"MSG_MOVE_SET_TURN_RATE",
	"MSG_MOVE_TOGGLE_COLLISION_CHEAT",
	"MSG_MOVE_SET_FACING",
	"MSG_MOVE_SET_PITCH",
	"MSG_MOVE_WORLDPORT_ACK",
	"SMSG_MONSTER_MOVE",
	"SMSG_MOVE_WATER_WALK",
	"SMSG_MOVE_LAND_WALK",
	"MSG_MOVE_SET_RAW_POSITION_ACK",
	"CMSG_MOVE_SET_RAW_POSITION",
	"SMSG_FORCE_RUN_SPEED_CHANGE",
	"CMSG_FORCE_RUN_SPEED_CHANGE_ACK",
	"SMSG_FORCE_RUN_BACK_SPEED_CHANGE",
	"CMSG_FORCE_RUN_BACK_SPEED_CHANGE_ACK",
	"SMSG_FORCE_SWIM_SPEED_CHANGE",
	"CMSG_FORCE_SWIM_SPEED_CHANGE_ACK",
	"SMSG_FORCE_MOVE_ROOT",
	"CMSG_FORCE_MOVE_ROOT_ACK",
	"SMSG_FORCE_MOVE_UNROOT",
	"CMSG_FORCE_MOVE_UNROOT_ACK",
	"MSG_MOVE_ROOT",
	"MSG_MOVE_UNROOT",
	"MSG_MOVE_HEARTBEAT",
	"SMSG_MOVE_KNOCK_BACK",
	"CMSG_MOVE_KNOCK_BACK_ACK",
	"MSG_MOVE_KNOCK_BACK",
	"SMSG_MOVE_FEATHER_FALL",
	"SMSG_MOVE_NORMAL_FALL",
	"SMSG_MOVE_SET_HOVER",
	"SMSG_MOVE_UNSET_HOVER",
	"CMSG_MOVE_HOVER_ACK",
	"MSG_MOVE_HOVER",
	"CMSG_TRIGGER_CINEMATIC_CHEAT",
	"CMSG_OPENING_CINEMATIC",
	"SMSG_TRIGGER_CINEMATIC",
	"CMSG_NEXT_CINEMATIC_CAMERA",
	"CMSG_COMPLETE_CINEMATIC",
	"SMSG_TUTORIAL_FLAGS",
	"CMSG_TUTORIAL_FLAG",
	"CMSG_TUTORIAL_CLEAR",
	"CMSG_TUTORIAL_RESET",
	"CMSG_STANDSTATECHANGE",
	"CMSG_EMOTE",
	"SMSG_EMOTE",
	"CMSG_TEXT_EMOTE",
	"SMSG_TEXT_EMOTE",
	"CMSG_AUTOEQUIP_GROUND_ITEM",
	"CMSG_AUTOSTORE_GROUND_ITEM",
	"CMSG_AUTOSTORE_LOOT_ITEM",
	"CMSG_STORE_LOOT_IN_SLOT",
	"CMSG_AUTOEQUIP_ITEM",
	"CMSG_AUTOSTORE_BAG_ITEM",
	"CMSG_SWAP_ITEM",
	"CMSG_SWAP_INV_ITEM",
	"CMSG_SPLIT_ITEM",
	"CMSG_PICKUP_ITEM",
	"CMSG_DROP_ITEM",
	"CMSG_DESTROYITEM",
	"SMSG_INVENTORY_CHANGE_FAILURE",
	"SMSG_OPEN_CONTAINER",
	"CMSG_INSPECT",
	"SMSG_INSPECT",
	"CMSG_INITIATE_TRADE",
	"CMSG_BEGIN_TRADE",
	"CMSG_BUSY_TRADE",
	"CMSG_IGNORE_TRADE",
	"CMSG_ACCEPT_TRADE",
	"CMSG_UNACCEPT_TRADE",
	"CMSG_CANCEL_TRADE",
	"CMSG_SET_TRADE_ITEM",
	"CMSG_CLEAR_TRADE_ITEM",
	"CMSG_SET_TRADE_GOLD",
	"SMSG_TRADE_STATUS",
	"SMSG_TRADE_STATUS_EXTENDED",
	"SMSG_INITIALIZE_FACTIONS",
	"SMSG_SET_FACTION_VISIBLE",
	"SMSG_SET_FACTION_STANDING",
	"CMSG_SET_FACTION_ATWAR",
	"CMSG_SET_FACTION_CHEAT",
	"SMSG_SET_PROFICIENCY",
	"CMSG_SET_ACTION_BUTTON",
	"SMSG_ACTION_BUTTONS",
	"SMSG_INITIAL_SPELLS",
	"SMSG_LEARNED_SPELL",
	"SMSG_SUPERCEDED_SPELL",
	"CMSG_NEW_SPELL_SLOT",
	"CMSG_CAST_SPELL",
	"CMSG_CANCEL_CAST",
	"SMSG_CAST_RESULT",
	"SMSG_SPELL_START",
	"SMSG_SPELL_GO",
	"SMSG_SPELL_FAILURE",
	"SMSG_SPELL_COOLDOWN",
	"SMSG_COOLDOWN_EVENT",
	"CMSG_CANCEL_AURA",
	"SMSG_UPDATE_AURA_DURATION",
	"SMSG_PET_CAST_FAILED",
	"MSG_CHANNEL_START",
	"MSG_CHANNEL_UPDATE",
	"CMSG_CANCEL_CHANNELLING",
	"SMSG_AI_REACTION",
	"CMSG_SET_SELECTION",
	"CMSG_SET_TARGET",
	"CMSG_UNUSED",
	"CMSG_UNUSED2",
	"CMSG_ATTACKSWING",
	"CMSG_ATTACKSTOP",
	"SMSG_ATTACKSTART",
	"SMSG_ATTACKSTOP",
	"SMSG_ATTACKSWING_NOTINRANGE",
	"SMSG_ATTACKSWING_BADFACING",
	"SMSG_ATTACKSWING_NOTSTANDING",
	"SMSG_ATTACKSWING_DEADTARGET",
	"SMSG_ATTACKSWING_CANT_ATTACK",
	"SMSG_ATTACKERSTATEUPDATE",
	"SMSG_VICTIMSTATEUPDATE_OBSOLETE",
	"SMSG_DAMAGE_DONE_OBSOLETE",
	"SMSG_DAMAGE_TAKEN_OBSOLETE",
	"SMSG_CANCEL_COMBAT",
	"SMSG_PLAYER_COMBAT_XP_GAIN_OBSOLETE",
	"SMSG_HEALSPELL_ON_PLAYER_OBSOLETE",
	"SMSG_HEALSPELL_ON_PLAYERS_PET_OBSOLETE",
	"CMSG_SHEATHE_OBSOLETE",
	"CMSG_SAVE_PLAYER",
	"CMSG_SETDEATHBINDPOINT",
	"SMSG_BINDPOINTUPDATE",
	"CMSG_GETDEATHBINDZONE",
	"SMSG_BINDZONEREPLY",
	"SMSG_PLAYERBOUND",
	"SMSG_DEATH_NOTIFY_OBSOLETE",
	"CMSG_REPOP_REQUEST",
	"SMSG_RESURRECT_REQUEST",
	"CMSG_RESURRECT_RESPONSE",
	"CMSG_LOOT",
	"CMSG_LOOT_MONEY",
	"CMSG_LOOT_RELEASE",
	"SMSG_LOOT_RESPONSE",
	"SMSG_LOOT_RELEASE_RESPONSE",
	"SMSG_LOOT_REMOVED",
	"SMSG_LOOT_MONEY_NOTIFY",
	"SMSG_LOOT_ITEM_NOTIFY",
	"SMSG_LOOT_CLEAR_MONEY",
	"SMSG_ITEM_PUSH_RESULT",
	"SMSG_DUEL_REQUESTED",
	"SMSG_DUEL_OUTOFBOUNDS",
	"SMSG_DUEL_INBOUNDS",
	"SMSG_DUEL_COMPLETE",
	"SMSG_DUEL_WINNER",
	"CMSG_DUEL_ACCEPTED",
	"CMSG_DUEL_CANCELLED",
	"SMSG_MOUNTRESULT",
	"SMSG_DISMOUNTRESULT",
	"SMSG_PUREMOUNT_CANCELLED_OBSOLETE",
	"CMSG_MOUNTSPECIAL_ANIM",
	"SMSG_MOUNTSPECIAL_ANIM",
	"SMSG_PET_TAME_FAILURE",
	"CMSG_PET_SET_ACTION",
	"CMSG_PET_ACTION",
	"CMSG_PET_ABANDON",
	"CMSG_PET_RENAME",
	"SMSG_PET_NAME_INVALID",
	"SMSG_PET_SPELLS",
	"CMSG_PET_CAST_SPELL_OBSOLETE",
	"CMSG_GOSSIP_HELLO",
	"CMSG_GOSSIP_SELECT_OPTION",
	"SMSG_GOSSIP_MESSAGE",
	"SMSG_GOSSIP_COMPLETE",
	"CMSG_NPC_TEXT_QUERY",
	"SMSG_NPC_TEXT_UPDATE",
	"SMSG_NPC_WONT_TALK",
	"CMSG_QUESTGIVER_STATUS_QUERY",
	"SMSG_QUESTGIVER_STATUS",
	"CMSG_QUESTGIVER_HELLO",
	"SMSG_QUESTGIVER_QUEST_LIST",
	"CMSG_QUESTGIVER_QUERY_QUEST",
	"CMSG_QUESTGIVER_QUEST_AUTOLAUNCH",
	"SMSG_QUESTGIVER_QUEST_DETAILS",
	"CMSG_QUESTGIVER_ACCEPT_QUEST",
	"CMSG_QUESTGIVER_COMPLETE_QUEST",
	"SMSG_QUESTGIVER_REQUEST_ITEMS",
	"CMSG_QUESTGIVER_REQUEST_REWARD",
	"SMSG_QUESTGIVER_OFFER_REWARD",
	"CMSG_QUESTGIVER_CHOOSE_REWARD",
	"SMSG_QUESTGIVER_QUEST_INVALID",
	"CMSG_QUESTGIVER_CANCEL",
	"SMSG_QUESTGIVER_QUEST_COMPLETE",
	"SMSG_QUESTGIVER_QUEST_FAILED",
	"CMSG_QUESTLOG_SWAP_QUEST",
	"CMSG_QUESTLOG_REMOVE_QUEST",
	"SMSG_QUESTLOG_FULL",
	"SMSG_QUESTUPDATE_FAILED",
	"SMSG_QUESTUPDATE_FAILEDTIMER",
	"SMSG_QUESTUPDATE_COMPLETE",
	"SMSG_QUESTUPDATE_ADD_KILL",
	"SMSG_QUESTUPDATE_ADD_ITEM",
	"CMSG_QUEST_CONFIRM_ACCEPT",
	"SMSG_QUEST_CONFIRM_ACCEPT",
	"CMSG_PUSHQUESTTOPARTY",
	"CMSG_LIST_INVENTORY",
	"SMSG_LIST_INVENTORY",
	"CMSG_SELL_ITEM",
	"SMSG_SELL_ITEM",
	"CMSG_BUY_ITEM",
	"CMSG_BUY_ITEM_IN_SLOT",
	"SMSG_BUY_ITEM",
	"SMSG_BUY_FAILED",
	"CMSG_TAXICLEARALLNODES",
	"CMSG_TAXIENABLEALLNODES",
	"CMSG_TAXISHOWNODES",
	"SMSG_SHOWTAXINODES",
	"CMSG_TAXINODE_STATUS_QUERY",
	"SMSG_TAXINODE_STATUS",
	"CMSG_TAXIQUERYAVAILABLENODES",
	"CMSG_ACTIVATETAXI",
	"SMSG_ACTIVATETAXIREPLY",
	"SMSG_NEW_TAXI_PATH",
	"CMSG_TRAINER_LIST",
	"SMSG_TRAINER_LIST",
	"CMSG_TRAINER_BUY_SPELL",
	"SMSG_TRAINER_BUY_SUCCEEDED",
	"SMSG_TRAINER_BUY_FAILED",
	"CMSG_BINDER_ACTIVATE",
	"SMSG_PLAYERBINDERROR",
	"CMSG_BANKER_ACTIVATE",
	"SMSG_SHOW_BANK",
	"CMSG_BUY_BANK_SLOT",
	"SMSG_BUY_BANK_SLOT_RESULT",
	"CMSG_PETITION_SHOWLIST",
	"SMSG_PETITION_SHOWLIST",
	"CMSG_PETITION_BUY",
	"CMSG_PETITION_SHOW_SIGNATURES",
	"SMSG_PETITION_SHOW_SIGNATURES",
	"CMSG_PETITION_SIGN",
	"SMSG_PETITION_SIGN_RESULTS",
	"MSG_PETITION_DECLINE",
	"CMSG_OFFER_PETITION",
	"CMSG_TURN_IN_PETITION",
	"SMSG_TURN_IN_PETITION_RESULTS",
	"CMSG_PETITION_QUERY",
	"SMSG_PETITION_QUERY_RESPONSE",
	"SMSG_FISH_NOT_HOOKED",
	"SMSG_FISH_ESCAPED",
	"CMSG_BUG",
	"SMSG_NOTIFICATION",
	"CMSG_PLAYED_TIME",
	"SMSG_PLAYED_TIME",
	"CMSG_QUERY_TIME",
	"SMSG_QUERY_TIME_RESPONSE",
	"SMSG_LOG_XPGAIN",
	"MSG_SPLIT_MONEY",
	"CMSG_RECLAIM_CORPSE",
	"CMSG_WRAP_ITEM",
	"SMSG_LEVELUP_INFO",
	"MSG_MINIMAP_PING",
	"SMSG_RESISTLOG",
	"SMSG_ENCHANTMENTLOG",
	"CMSG_SET_SKILL_CHEAT",
	"SMSG_START_MIRROR_TIMER",
	"SMSG_PAUSE_MIRROR_TIMER",
	"SMSG_STOP_MIRROR_TIMER",
	"CMSG_PING",
	"SMSG_PONG",
	"SMSG_CLEAR_COOLDOWN",
	"SMSG_GAMEOBJECT_PAGETEXT",
	"CMSG_SETSHEATHED",
	"SMSG_COOLDOWN_CHEAT",
	"SMSG_SPELL_DELAYED",
	"CMSG_PLAYER_MACRO_OBSOLETE",
	"SMSG_PLAYER_MACRO_OBSOLETE",
	"CMSG_GHOST",
	"CMSG_GM_INVIS",
	"CMSG_SCREENSHOT",
	"MSG_GM_BIND_OTHER",
	"MSG_GM_SUMMON",
	"SMSG_ITEM_TIME_UPDATE",
	"SMSG_ITEM_ENCHANT_TIME_UPDATE",
	"SMSG_AUTH_CHALLENGE",
	"CMSG_AUTH_SESSION",
	"SMSG_AUTH_RESPONSE",
	"MSG_GM_SHOWLABEL",
	"MSG_ADD_DYNAMIC_TARGET",
	"MSG_SAVE_GUILD_EMBLEM",
	"MSG_TABARDVENDOR_ACTIVATE",
	"SMSG_PLAY_SPELL_VISUAL",
	"CMSG_ZONEUPDATE",
	"SMSG_PARTYKILLLOG",
	"SMSG_COMPRESSED_UPDATE_OBJECT",
	"SMSG_OBSOLETE",
	"SMSG_EXPLORATION_EXPERIENCE",
	"CMSG_GM_SET_SECURITY_GROUP",
	"CMSG_GM_NUKE",
	"MSG_RANDOM_ROLL",
	"SMSG_ENVIRONMENTALDAMAGELOG",
	"CMSG_RWHOIS",
	"SMSG_RWHOIS",
	"MSG_LOOKING_FOR_GROUP",
	"CMSG_SET_LOOKING_FOR_GROUP",
	"CMSG_UNLEARN_SPELL",
	"CMSG_UNLEARN_SKILL",
	"SMSG_REMOVED_SPELL",
	"CMSG_DECHARGE",
	"CMSG_GMTICKET_CREATE",
	"SMSG_GMTICKET_CREATE",
	"CMSG_GMTICKET_UPDATETEXT",
	"SMSG_GMTICKET_UPDATETEXT",
	"SMSG_ACCOUNT_DATA_MD5",
	"CMSG_REQUEST_ACCOUNT_DATA",
	"CMSG_UPDATE_ACCOUNT_DATA",
	"SMSG_UPDATE_ACCOUNT_DATA",
	"SMSG_CLEAR_FAR_SIGHT_IMMEDIATE",
	"SMSG_POWERGAINLOG_OBSOLETE",
	"CMSG_GM_TEACH",
	"CMSG_GM_CREATE_ITEM_TARGET",
	"CMSG_GMTICKET_GETTICKET",
	"SMSG_GMTICKET_GETTICKET",
	"CMSG_UNLEARN_TALENTS",
	"SMSG_GAMEOBJECT_SPAWN_ANIM",
	"SMSG_GAMEOBJECT_DESPAWN_ANIM",
	"MSG_CORPSE_QUERY",
	"CMSG_GMTICKET_DELETETICKET",
	"SMSG_GMTICKET_DELETETICKET",
	"SMSG_CHAT_WRONG_FACTION",
	"CMSG_GMTICKET_SYSTEMSTATUS",
	"SMSG_GMTICKET_SYSTEMSTATUS",
	"CMSG_SPIRIT_HEALER_ACTIVATE",
	"CMSG_SET_STAT_CHEAT",
	"SMSG_SET_REST_START",
	"CMSG_SKILL_BUY_STEP",
	"CMSG_SKILL_BUY_RANK",
	"CMSG_XP_CHEAT",
	"SMSG_SPIRIT_HEALER_CONFIRM",
	"CMSG_CHARACTER_POINT_CHEAT",
	"SMSG_GOSSIP_POI",
	"CMSG_CHAT_IGNORED",
	"CMSG_GM_VISION",
	"CMSG_SERVER_COMMAND",
	"CMSG_GM_SILENCE",
	"CMSG_GM_REVEALTO",
	"CMSG_GM_RESURRECT",
	"CMSG_GM_SUMMONMOB",
	"CMSG_GM_MOVECORPSE",
	"CMSG_GM_FREEZE",
	"CMSG_GM_UBERINVIS",
	"CMSG_GM_REQUEST_PLAYER_INFO",
	"SMSG_GM_PLAYER_INFO",
	"CMSG_GUILD_RANK",
	"CMSG_GUILD_ADD_RANK",
	"CMSG_GUILD_DEL_RANK",
	"CMSG_GUILD_SET_PUBLIC_NOTE",
	"CMSG_GUILD_SET_OFFICER_NOTE",
	"SMSG_LOGIN_VERIFY_WORLD",
	"CMSG_CLEAR_EXPLORATION",
	"CMSG_SEND_MAIL",
	"SMSG_SEND_MAIL_RESULT",
	"CMSG_GET_MAIL_LIST",
	"SMSG_MAIL_LIST_RESULT",
	"CMSG_BATTLEFIELD_LIST",
	"SMSG_BATTLEFIELD_LIST",
	"CMSG_BATTLEFIELD_JOIN",
	"SMSG_BATTLEFIELD_WIN",
	"SMSG_BATTLEFIELD_LOSE",
	"CMSG_TAXICLEARNODE",
	"CMSG_TAXIENABLENODE",
	"CMSG_ITEM_TEXT_QUERY",
	"SMSG_ITEM_TEXT_QUERY_RESPONSE",
	"CMSG_MAIL_TAKE_MONEY",
	"CMSG_MAIL_TAKE_ITEM",
	"CMSG_MAIL_MARK_AS_READ",
	"CMSG_MAIL_RETURN_TO_SENDER",
	"CMSG_MAIL_DELETE",
	"CMSG_MAIL_CREATE_TEXT_ITEM",
	"SMSG_SPELLLOGMISS",
	"SMSG_SPELLLOGEXECUTE",
	"SMSG_DEBUGAURAPROC",
	"SMSG_PERIODICAURALOG",
	"SMSG_SPELLDAMAGESHIELD",
	"SMSG_SPELLNONMELEEDAMAGELOG",
	"CMSG_LEARN_TALENT",
	"SMSG_RESURRECT_FAILED",
	"CMSG_TOGGLE_PVP",
	"SMSG_ZONE_UNDER_ATTACK",
	"MSG_AUCTION_HELLO",
	"CMSG_AUCTION_SELL_ITEM",
	"CMSG_AUCTION_REMOVE_ITEM",
	"CMSG_AUCTION_LIST_ITEMS",
	"CMSG_AUCTION_LIST_OWNER_ITEMS",
	"CMSG_AUCTION_PLACE_BID",
	"SMSG_AUCTION_COMMAND_RESULT",
	"SMSG_AUCTION_LIST_RESULT",
	"SMSG_AUCTION_OWNER_LIST_RESULT",
	"SMSG_AUCTION_BIDDER_NOTIFICATION",
	"SMSG_AUCTION_OWNER_NOTIFICATION",
	"SMSG_PROCRESIST",
	"SMSG_STANDSTATE_CHANGE_FAILURE",
	"SMSG_DISPEL_FAILED",
	"SMSG_SPELLORDAMAGE_IMMUNE",
	"CMSG_AUCTION_LIST_BIDDER_ITEMS",
	"SMSG_AUCTION_BIDDER_LIST_RESULT",
	"SMSG_SET_FLAT_SPELL_MODIFIER",
	"SMSG_SET_PCT_SPELL_MODIFIER",
	"CMSG_SET_AMMO",
	"SMSG_CORPSE_RECLAIM_DELAY",
	"CMSG_SET_ACTIVE_MOVER",
	"CMSG_PET_CANCEL_AURA",
	"CMSG_PLAYER_AI_CHEAT",
	"CMSG_CANCEL_AUTO_REPEAT_SPELL",
	"MSG_GM_ACCOUNT_ONLINE",
	"MSG_LIST_STABLED_PETS",
	"CMSG_STABLE_PET",
	"CMSG_UNSTABLE_PET",
	"CMSG_BUY_STABLE_SLOT",
	"SMSG_STABLE_RESULT",
	"CMSG_STABLE_REVIVE_PET",
	"CMSG_STABLE_SWAP_PET",
	"MSG_QUEST_PUSH_RESULT",
	"SMSG_PLAY_MUSIC",
	"SMSG_PLAY_OBJECT_SOUND",
	"CMSG_REQUEST_PET_INFO",
	"CMSG_FAR_SIGHT",
	"SMSG_SPELLDISPELLOG",
	"SMSG_DAMAGE_CALC_LOG",
	"CMSG_ENABLE_DAMAGE_LOG",
	"CMSG_GROUP_CHANGE_SUB_GROUP",
	"SMSG_RAID_MEMBER_STATS",
	"CMSG_GROUP_SWAP_SUB_GROUP",
	"CMSG_RESET_FACTION_CHEAT",
	"CMSG_AUTOSTORE_BANK_ITEM",
	"CMSG_AUTOBANK_ITEM",
	"MSG_QUERY_NEXT_MAIL_TIME",
	"SMSG_RECEIVED_MAIL",
	"SMSG_RAID_GROUP_ONLY",
	"CMSG_SET_DURABILITY_CHEAT",
	"CMSG_SET_PVP_RANK_CHEAT",
	"CMSG_ADD_PVP_MEDAL_CHEAT",
	"CMSG_DEL_PVP_MEDAL_CHEAT",
	"CMSG_SET_PVP_TITLE",
	"SMSG_PVP_CREDIT",
	"SMSG_AUCTION_REMOVED_NOTIFICATION",
	"CMSG_GROUP_RAID_CONVERT",
	"CMSG_GROUP_ASSISTANT_LEADER",
	"CMSG_BUYBACK_ITEM",
	"SMSG_SERVER_MESSAGE",
	"CMSG_MEETINGSTONE_JOIN",
	"CMSG_MEETINGSTONE_LEAVE",
	"CMSG_MEETINGSTONE_CHEAT",
	"SMSG_MEETINGSTONE_SETQUEUE",
	"CMSG_MEETINGSTONE_INFO",
	"SMSG_MEETINGSTONE_COMPLETE",
	"SMSG_MEETINGSTONE_IN_PROGRESS",
	"SMSG_MEETINGSTONE_MEMBER_ADDED",
	"CMSG_GMTICKETSYSTEM_TOGGLE",
	"CMSG_CANCEL_GROWTH_AURA",
	"SMSG_CANCEL_AUTO_REPEAT",
	"SMSG_STANDSTATE_CHANGE_ACK",
	"SMSG_LOOT_ALL_PASSED",
	"SMSG_LOOT_ROLL_WON",
	"CMSG_LOOT_ROLL",
	"SMSG_LOOT_START_ROLL",
	"SMSG_LOOT_ROLL",
	"CMSG_LOOT_MASTER_GIVE",
	"SMSG_LOOT_MASTER_LIST",
	"SMSG_SET_FORCED_REACTIONS",
	"SMSG_SPELL_FAILED_OTHER",
	"SMSG_GAMEOBJECT_RESET_STATE",
	"CMSG_REPAIR_ITEM",
	"SMSG_CHAT_PLAYER_NOT_FOUND",
	"MSG_TALENT_WIPE_CONFIRM",
	"SMSG_SUMMON_REQUEST",
	"CMSG_SUMMON_RESPONSE",
	"MSG_MOVE_TOGGLE_GRAVITY_CHEAT",
	"SMSG_MONSTER_MOVE_TRANSPORT",
	"SMSG_PET_BROKEN",
	"MSG_MOVE_FEATHER_FALL",
	"MSG_MOVE_WATER_WALK",
	"CMSG_SERVER_BROADCAST",
	"CMSG_SELF_RES",
	"SMSG_FEIGN_DEATH_RESISTED",
	"CMSG_RUN_SCRIPT",
	"SMSG_SCRIPT_MESSAGE",
	"SMSG_DUEL_COUNTDOWN",
	"SMSG_AREA_TRIGGER_MESSAGE",
	"CMSG_TOGGLE_HELM",
	"CMSG_TOGGLE_CLOAK",
	"SMSG_SPELL_REFLECTED",
	"SMSG_PLAYER_SKINNED",
	"SMSG_DURABILITY_DAMAGE_DEATH",
	"CMSG_SET_EXPLORATION",
	"CMSG_SET_ACTIONBAR_TOGGLES",
	"UMSG_DELETE_GUILD_CHARTER",
	"MSG_PETITION_RENAME",
	"SMSG_INIT_WORLD_STATES",
	"SMSG_UPDATE_WORLD_STATE",
	"CMSG_ITEM_NAME_QUERY",
	"SMSG_ITEM_NAME_QUERY_RESPONSE",
	"SMSG_PET_ACTION_FEEDBACK",
	"UNK_0x02C7",
	"UNK_0x02C8",
	"UNK_0x02C9",
	"UNK_0x02CA",
	"UNK_0x02CB",
	"UNK_0x02CC",
	"CMSG_REQUEST_RAID_INFO",
	"CMSG_MOVE_TIME_SKIPPED",
	"UNK_0x02CF",
	"UNK_0x02D0",
	"UNK_0x02D1",
	"UNK_0x02D2",
	"CMSG_BATTLEFIELD_STATUS",
	"UNK_0x02D4",
	"UNK_0x02D5",
	"UNK_0x02D6",
	"UNK_0x02D7",
	"UNK_0x02D8",
	"UNK_0x02D9",
	"UNK_0x02DA",
	"UNK_0x02DB",
	"UNK_0x02DC",
	"UNK_0x02DD",
	"UNK_0x02DE",
	"UNK_0x02DF",
	"UNK_0x02E0",
	"UNK_0x02E1",
	"UNK_0x02E2",
	"UNK_0x02E3",
	"UNK_0x02E4",
	"UNK_0x02E5",
	"UNK_0x02E6",
	"UNK_0x02E7",
	"UNK_0x02E8",
	"UNK_0x02E9",
	"UNK_0x02EA",
	"MSG_BINDPOINT_CONFIRM",
	"UNK_0x02EC",
	"UNK_0x02ED",
	"UNK_0x02EE",
	"SMSG_ADDON_INFO",
	"UNK_0x02F0",
	"UNK_0x02F1",
	"NUM_MSG_TYPES",
	"UNK_0x02F3",
	"UNK_0x02F4",
	"UNK_0x02F5",
	"UNK_0x02F6",
	"UNK_0x02F7",
	"UNK_0x02F8",
	"UNK_0x02F9",
	"UNK_0x02FA",
	"UNK_0x02FB",
	"UNK_0x02FC",
	"UNK_0x02FD",
	"UNK_0x02FE",
	"UNK_0x02FF",
	"UNK_0x0300",
	"UNK_0x0301",
	"UNK_0x0302",
	"UNK_0x0303",
	"UNK_0x0304",
	"UNK_0x0305",
	"UNK_0x0306",
	"UNK_0x0307",
	"UNK_0x0308",
	"UNK_0x0309",
	"UNK_0x030A",
	"UNK_0x030B",
	"UNK_0x030C",
	"UNK_0x030D",
	"UNK_0x030E",
	"UNK_0x030F",
	"UNK_0x0310"
};

#ifndef WIN32
void pipesignal(int param)
{
	RealmServer.pTempClient->socket.Close();
	signal(SIGPIPE,pipesignal);
}
#endif
const unsigned long seed = server_seed;
extern bool LoadAccount(char *name, CClient *pClient, bool createflag = true);

void touppercase(char *data) {
	int len = strlen(data);
	for (int i=0; i<len; i++) {
		data[i] = toupper(data[i]);
	}
}

fMessageHandler LoginMessageHandlers[MSG_HANDLERS] = {0};
fMessageHandler GameMessageHandlers[MSG_HANDLERS] = {0};
THREAD WINAPI RealmServerThreadFunction( LPVOID pParam )
{
	InstallMessageHandlers(LoginMessageHandlers);
	InstallGameMessageHandlers(GameMessageHandlers);

	CThread *pThread=(CThread*)pParam;
	CLock L(&pThread->Threading,true);
	pThread->bThreading=true;
	pThread->ThreadReady=true;
	CRealmServer *pServer=(CRealmServer*)pThread->Info;
#ifndef WIN32
	signal(SIGPIPE,pipesignal);
#endif
	pServer->ThreadState=0;
	//char Buffer[20480];
	CClient *nextclient=new CClient;
	time_t LastMasterHeartbeat=0;
	TCPSocket Redirect;
	TCPSocket LoginSocket;
	Addr From;
	time_t now=time(0);
	int updatecounter=0;
	int updatequeuecounter=0;
	int ServerState=0;
	// seed random number generator for this thread
	srand(time(0));
	CDataBuffer *pRecvBuffer = new CDataBuffer(20480);
	char *Buffer = pRecvBuffer->Buffer();
	//unsigned int msgID = 0;
	CDebug logfile;
	logfile.Initialize("PktLog.txt");

	while(!pThread->CloseThread)
	{
		DETECT_DEBUG
			int LastState=ServerState;

		now=time(0);
		// handle each client individually
		if(!RealmServer.ActiveRegionsCreatureMove.empty())
		{
			CRegion *pNextRegion=RealmServer.ActiveRegionsCreatureMove.front();
			RealmServer.ActiveRegionsCreatureMove.pop();
			if(pNextRegion)
			{
				//alright, center one we keep checking for, outside ones we force move to keep movement real
				for (int i = 0 ; i < 3 ; i++)
					for (int j = 0 ; j < 3 ; j++)
					{
						if (CRegion *pRegion=pNextRegion->Adjacent[i][j])
						{
							if(i==1 && j==1)
							{
								if(pRegion->RegionWanderCreatures(now,false))
									RealmServer.ActiveRegionsCreatureMove.push(pNextRegion);
							}
							else
								pRegion->RegionWanderCreatures(now,true);
						}
					}
			}
		}

#ifdef WIN32
		updatecounter++;
		if(updatecounter>150)
		{
			updatecounter=0;
			char temp[80];
			if(pServer->ServerQueue.size()) sprintf(temp,"%i playing, %i queued",pServer->nClients,pServer->ServerQueue.size());
			else sprintf(temp,"%i playing",pServer->nClients);
			if(dlg && !pThread->CloseThread) dlg->Txt_Clients.SetWindowText(temp);
		}
#endif
		for (unsigned long i = 0 ; i < pServer->Clients.Size ; i++)
		{
			if (CClient *client=pServer->Clients[i])
			{
				// disconnected?
				if (!client->socket.isConnected() || client->DestroyMe)
				{
					for(unsigned long k = 0;k<pServer->ServerQueue.size();k++)
					{
						if(pServer->ServerQueue[k]==client)
						{
							pServer->ServerQueue.erase(pServer->ServerQueue.begin()+k);
							pServer->nClients++; //err...yeah, we need to increment then decrement
						}
					}
					// delete and whatnot
					pServer->Clients[i]=0;
					client->CompleteLogout();
					//don't worry, this client is being deleted in a sec anyway
					//therefore OutPacket won't do anything :D
					//doing this to ensure that cleanup is properly done, otherwise we could have problems!
					delete client;
					pServer->nClients--;
					continue;
				}
				// outgoing data new
				while (!client->Outgoing.Empty() && client->DataPending.Size<1024)
				{
					_OutData data=client->Outgoing.Peek();
					int AddSize=data.Size;
					if (AddSize+client->DataPending.Size>=0x3F000)
					{
						break;
					}
#if defined(_DEBUG) || defined(FORCE_PKTLOG)
					char tempop[128];
					if(data.Size)
					{
						unsigned short op=*((unsigned short*)&data.buffer[2]);
						if(op<=NUM_MSG_TYPES && op!=SMSG_MONSTER_MOVE) // no more monster moving messages; flood!
						{
							sprintf(tempop,"Data to Send: Opcode %04X (%s)",op,OpcodeNames[op]);
							logfile.LogBuffer(&data.buffer[4],data.Size-4,tempop);
						}
					}
#endif
					client->Crypter.EncryptSend((unsigned char*)data.buffer,4);
					memcpy(&client->DataPending.buffer[client->DataPending.Size],data.buffer,AddSize);
					client->DataPending.Size+=AddSize;
					free(data.buffer);
					client->Outgoing.Pop();
				}
				if (client->DataPending.Size)
				{
					pServer->pTempClient=client;
					//					if (SendSize>1024)
					//						SendSize=1024;
					pServer->ThreadState=1;
					int sent=client->socket.Send(client->DataPending.buffer,client->DataPending.Size);
					pServer->ThreadState=2;
					if (sent>0)
					{
						pServer->ThreadState=3;
						if (sent>(int)pServer->MaxSent)
							pServer->MaxSent=(unsigned long)sent;

						client->DataPending.Size-=sent;
						memmove(client->DataPending.buffer,&client->DataPending.buffer[sent],client->DataPending.Size);
						pServer->ThreadState=4;
					}
				}
				/*
				if (client->DestroyMe)
				{
				pServer->Clients[i]=0;
				delete client;
				pServer->nClients--;
				continue;
				}
				*/
				// incoming data?
				pServer->ThreadState=5;
				for (int n = 0 ; n < 6 ; n++)
				{
					int isize=client->socket.isData();
					if (isize>0 || (client->NextLength==0 && client->NextOpCode))
					{
						if (!client->NextLength && !client->NextOpCode)
						{
							if (isize>=6) //get the header now
							{
								char inhdr[6];
								client->LastIncoming=now;
								client->socket.Receive(inhdr,6);
								client->Crypter.DecryptRecv((unsigned char *)inhdr,6);
								memcpy(&client->NextLength,&inhdr[0],2);
								memcpy(&client->NextOpCode,&inhdr[2],4);
								client->NextLength=htons(client->NextLength)-4;
								//logfile.LogBuffer((char*)&client->NextOpCode,4,"NextOpCode");
							}
						}
						else
							if (isize>=client->NextLength)
							{
								client->LastIncoming=now;
								isize = client->socket.Receive(Buffer,client->NextLength);
#if defined(_DEBUG) || defined(FORCE_PKTLOG)
								if(client->NextOpCode<=NUM_MSG_TYPES)
								{
									char tempop[128];
									sprintf(tempop,"Incoming: Opcode %04X (%s)",client->NextOpCode,OpcodeNames[client->NextOpCode]);
									logfile.LogBuffer(Buffer,isize,tempop);
								}
#endif
								pServer->ThreadState=6;
								pRecvBuffer->Position(0);

								if (client->NextOpCode<MSG_HANDLERS && client->MessageHandlers[client->NextOpCode])
									client->MessageHandlers[client->NextOpCode](client, client->NextOpCode, *pRecvBuffer);
								else // not just for debugging!
								{
									char temptoprint[128];
									sprintf(temptoprint,"Unhandled opcode %04X: %s",client->NextOpCode,(client->NextOpCode<=NUM_MSG_TYPES?OpcodeNames[client->NextOpCode]:"UNKNOWN"));
									Debug.LogBuffer(Buffer,isize,temptoprint);
								}

								pServer->ThreadState=7;
								//client->ProcessIncomingData(Data);
								client->NextLength=0;
								client->NextOpCode=0;
							}
					}
					else
						break;
				}
				if (difftime(now,client->LastIncoming)>180.0f)
				{
					client->DestroyMe=true;
				}
			}
		}
		if(pServer->ServerQueue.size()>0 && pServer->nClients<Settings.max_connections) //we can let someone in!
		{
			CClient *queuedguy=pServer->ServerQueue[0];
			pServer->ServerQueue.erase(pServer->ServerQueue.begin());
			if(queuedguy && !queuedguy->DestroyMe)
			{
				queuedguy->OutPacket(SMSG_AUTH_RESPONSE,"\x0c\xcf\xd2\x07\x00\x00",6); //you're in!
				pServer->nClients++; //we now have one more, sir.
			}
		}
		updatequeuecounter++;
		if(updatequeuecounter>100)
		{
			int counter=0;
			updatequeuecounter=0;
			for(unsigned long i = 0;i<pServer->ServerQueue.size();i++) //update the poor other queued peons
			{
				if(!pServer->ServerQueue[i]) continue;
				counter++;
				CPacket pkg;
				pkg.Reset(SMSG_AUTH_RESPONSE);
				pkg << (char)0x1B; //You Are (still) Queued!
				//1B 73 2C 00 00 00 00 00 00 00 61 00 00 00
				pkg << (long)0x00002C73; //what is this? miscellaneous garbage
				pkg << (char)0x00;
				pkg << (long)0;
				pkg << (long)counter;
				pServer->ServerQueue[i]->Send(&pkg);
			}
		}
		/*if (pServer->RedirectListener.Accept(Redirect))
		{
		char Out[256];
		long clientip=Redirect.GetClientIP();
		sprintf(Out,"%s:%i",pServer->IPAddr,Settings.Port_Realm);
		Redirect.Send(Out,strlen(Out)+1);
		Redirect.Close();
		}*/
		/*
		if (pServer->LoginListener.Accept(LoginSocket))
		{
		char user[256];
		char pass[256];
		Sleep(500);
		LoginSocket.Receive(Buffer,1);
		unsigned int userlen = Buffer[0];
		LoginSocket.Receive(user,userlen);
		user[userlen] =0;
		LoginSocket.Receive(Buffer,1);
		unsigned int passlen = Buffer[0];
		LoginSocket.Receive(pass,passlen);
		pass[passlen] = 0;
		char Out[1];
		if (ValidateUser(&LoginSocket,user,pass))
		Out[0] = 1;
		else
		Out[0] = 0;
		LoginSocket.Send(Out,1);
		LoginSocket.Close();
		}
		*/
		if (pServer->MasterList.isData())
		{
			int len=pServer->MasterList.RecvFrom(Buffer,2048,From);
			pServer->MasterList.SendTo(Buffer,len,From);
		}

		pServer->ThreadState=8;
		pServer->ThreadState=9;
		ServerState=0;
		if (pServer->Listener.Accept(nextclient->socket))
		{
			pServer->ThreadState=10;
			nextclient->SendAuthChallenge(seed); //transmit the seed data
			nextclient->LastIncoming=now;
			pServer->Clients+=nextclient;
			nextclient = new CClient;
			pServer->nClients++;
			if (pServer->nClients>pServer->nMaxClients)
			{
				pServer->nMaxClients=pServer->nClients;
			}
		}

		pServer->ThreadState=11;
		if (difftime(now,LastMasterHeartbeat)>60.0f || ServerState!=LastState)
		{
			LastMasterHeartbeat=now;
			pServer->UpdateMasterLists(ServerState);
		}

		pServer->ThreadState=12;
		EventManager.ProcessReadyEvents();
		pServer->ThreadState=13;

		Sleep(5); // 200 per second
	}
	// OK, cleanup time. Make sure everyone logs out safely to retain anything important, then quit.
	for (unsigned long i = 0 ; i < pServer->Clients.Size ; i++)
	{
		if (CClient *client=pServer->Clients[i])
		{
			// delete and whatnot
			pServer->Clients[i]=0;
			client->CompleteLogout();
			//don't worry, this client is being deleted in a sec anyway
			//therefore OutPacket won't do anything :D
			//doing this to ensure that cleanup is properly done, otherwise we could have problems!
			delete client;
		}
	}
	if (difftime(now,LastMasterHeartbeat)<140.0f)
	{
		pServer->UpdateMasterLists(-1);
	}

	if (nextclient)
		delete nextclient;
	while(!RealmServer.ActiveRegionsCreatureMove.empty()) RealmServer.ActiveRegionsCreatureMove.pop();
	pServer->Clients.Cleanup();
	pServer->nClients=0;
	pThread->bThreading=false;
	delete pRecvBuffer;
	return 0;
}


CRealmServer::CRealmServer(void):Clients(10),MasterLists(10)
{
	MaxSent=0;
	nMaxClients=0;
	nClients=0;
	strcpy(Name,"Localhost Server");
	strcpy(IPAddr,"127.0.0.1");
}

CRealmServer::~CRealmServer(void)
{
	RealmThread.EndThread();
	// Clients are cleaned up by thread
	MasterLists.Cleanup();
}

bool DoAccountNames(ObjectStorage &Storage, unsigned long ID)
{
	string name=((AccountData*)Storage.Data)->Name;
	MakeLower(name);
	DataManager.AccountNames[name]=ID;
	CAccount *pAccount;
	DataManager.RetrieveObject((CWoWObject **)&pAccount,OBJ_ACCOUNT,ID); //force cache
	return true;
}

bool DoPlayerNames(ObjectStorage &Storage, unsigned long ID)
{
	string name=((PlayerData*)Storage.Data)->Name;
	MakeLower(name);
	DataManager.PlayerNames[name]=ID;
	CPlayer *pPlayer;
	DataManager.RetrieveObject((CWoWObject **)&pPlayer,OBJ_PLAYER,ID); //force cache
	return true;
}

bool LoadCreatures(unsigned long ID)
{
	CCreature *pCreature;
	if(DataManager.RetrieveObject((CWoWObject **)&pCreature,OBJ_CREATURE,ID)) //force cache
		RegionManager.ObjectNew(*pCreature, pCreature->Data.Continent, pCreature->Data.Loc.X, pCreature->Data.Loc.Y);
	return true;
}

bool LoadGO(unsigned long ID)
{
	CGameObject *pObject;
	if(DataManager.RetrieveObject((CWoWObject **)&pObject,OBJ_GAMEOBJECT,ID)) //force cache
		RegionManager.ObjectNew(*pObject, pObject->Data.Continent, pObject->Data.Loc.X, pObject->Data.Loc.Y);
	return true;
}

bool DoCreatureTemplateNames(ObjectStorage &Storage, unsigned long ID)
{
	string name=((CreatureTemplateData*)Storage.Data)->Name;
	MakeLower(name);
	DataManager.CreatureTemplateNames[name]=ID;
	CCreatureTemplate *pTemplate;
	DataManager.RetrieveObject((CWoWObject **)&pTemplate,OBJ_CREATURETEMPLATE,ID); //force cache
	return true;
}

bool PreCacheNPCTexts(unsigned long ID)
{
	CNPCText *pText;
	DataManager.RetrieveObject((CWoWObject **)&pText,OBJ_NPCTEXT,ID);
	return true;
}

bool PreCachePageTexts(unsigned long ID)
{
	CPageText *pText;
	DataManager.RetrieveObject((CWoWObject **)&pText,OBJ_PAGETEXT,ID);
	return true;
}

bool LoadMails(unsigned long ID)
{
	CMail *pMail;
	if(!DataManager.RetrieveObject((CWoWObject **)&pMail,OBJ_MAIL,ID)) return true;
	CPlayer *pPlayer;
	if(!DataManager.RetrieveObject((CWoWObject **)&pPlayer,OBJ_PLAYER,pMail->Data.Recipient)) return true;
	pPlayer->Mails.push_back(pMail);
	pMail->EventsEligible=true; // all mails should be eligible anyway...
	EventManager.AddEvent(*pMail,3600000,EVENT_MAIL_EXPIRE_CHECK,0,0);
	return true;
}

bool InitSpawnPoints(unsigned long ID)
{
	CSpawnPoint *pPoint;
	if (DataManager.RetrieveObject((CWoWObject**)&pPoint,OBJ_SPAWNPOINT,ID))
	{
		// does it have a creature spawned?
		if (pPoint->Data.Creature)
		{
			CCreature *pCreature;
			if (DataManager.RetrieveObject((CWoWObject**)&pCreature,OBJ_CREATURE,ID))
			{
				// reset it to normal state
				pCreature->Data.CurrentStats=pCreature->pTemplate->Data.NormalStats;
				// and let it appear
				RegionManager.ObjectNew(*pCreature,pCreature->Data.Continent,pCreature->Data.Loc.X,pCreature->Data.Loc.Y);
				return true;
			}
		}
		pPoint->Data.Creature=0;
		pPoint->Spawn();
	}
	return true;
}

bool InitPathGroups(unsigned long ID)
{
	CPathGroup *pGroup;
	if (DataManager.RetrieveObject((CWoWObject**)&pGroup,OBJ_PATHGROUP,ID))
	{
		// TODO: populate some temporary map of every point. the data stored by the map
		// will be a linked list for every point x y and z on a particular continent.
		// once the linked list is complete, iterate through the entire map. for each list
		// that has more nodes than just the head, generate pairs of connected groups.
		// once this is complete, free the map.
	}
	return true;
}

bool InitQuestInfos(unsigned long ID)
{
	CQuestInfo *pQuest;
	if (!DataManager.RetrieveObject((CWoWObject**)&pQuest,OBJ_QUESTINFO,ID))
		return true; // it's a lie, but otherwise Enum stops processing
	// 	Debug.Logf("Failed to load quest %d", ID);
	// DataManager.QuestIDs[pQuest->Data.questid] = ID;

	return true;
}

bool InitGuilds(unsigned long ID)
{
	CGuild *pGuild=new CGuild;
	if (Storage.RetrieveObject(*pGuild,ID))
	{
		DataManager.NewObject(*pGuild);
	}
	return true;
}

void CRealmServer::InitSkillLines()
{
	int skillinecount;
	int i = 0;
	unsigned long skillline;
	unsigned long spell;

	skillinecount = DBCManager.SkillLineAbility.rowcount();	// row count

	while (i < skillinecount)
	{
		skillline = DBCManager.SkillLineAbility.getIntValueNoKey(i, 1);
		spell = DBCManager.SkillLineAbility.getIntValueNoKey(i, 2);

		RealmServer.SkillLines[spell] = skillline;
		i++;
		SetProgressBar(i,skillinecount,"Initializing Skill Lines...");
	}
}

void CRealmServer::LoadTaxiData()
{
	unsigned long count = 0;

	for ( int a = 1; a < DBCManager.TaxiNodes.rowcount() ; a++ )
	{
		TaxiNodesRec TX;
		_Location Loc;

		if(!DBCManager.TaxiNodes.fetchRow( a, &TX )) continue;

		CTaxiMob::Mask[(a-1) >> 5] |= 1<<((a-1)&31); // precompute the unchanging mask

		Loc.X = TX.X;
		Loc.Y = TX.Y;
		Loc.Z = TX.Z;

		CTaxiMob *pCreature = RealmServer.GenerateTaxiMob(20, "The Traveler", TX.ContinentID, Loc, 0);

		if ( pCreature )
		{
			//			pCreature->Data.FactionTemplate = 3;
			//			pCreature->Data.NPCType = 8;
			//			pCreature->Data.DamageMin = 1;
			//			pCreature->Data.DamageMax = 2;
			//			pCreature->Data.Size = 1;
			//			pCreature->Data.Level = 100;
			//			pCreature->Data.NormalStats.HitPoints = 10;
			pCreature->Data.CurrentStats.HitPoints = 10;
			//			pCreature->Data.CurrentStats.Mana = 10;
			//			pCreature->Data.NormalStats.Mana = 10;
			//			pCreature->Data.Exp = 10;
			pCreature->nodeid = TX.ID;

			RegionManager.ObjectNew(*pCreature, pCreature->Data.Continent, pCreature->Data.Loc.X, pCreature->Data.Loc.Y);

			count++;
		}
	}

	if ( count > 0 )
		Debug.Logf("%d of %d Taxi Nodes Loaded.", count, DBCManager.TaxiNodes.rowcount()-1);
	else
		Debug.Log("Error Loading Taxi Nodes.");
}

bool DoGOTemplateInit(unsigned long ID)
{
	CGameObjectTemplate *pTemplate;
	if (!DataManager.RetrieveObject((CWoWObject**)&pTemplate, OBJ_GAMEOBJECTTEMPLATE, ID))
		return false;
	string name=pTemplate->Data.Name;
	DataManager.GameObjectEntries[name] = ID;
	return true;
}

bool InitAreaTriggerTable()
{
	unsigned long ID;
	AreaTrigger at;

	FILE *f = fopen("data/AreaTriggers.dat", STORAGE_READ);
	if(f == NULL)
		return false;
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f,0,SEEK_SET);
	char *buffer = (char*)malloc(size);
	if(buffer == NULL || fread(buffer, size, 1, f) != 1)
	{
		fclose(f);
		return false;
	}
	fclose(f);
	long c = 0;
	while(c < size)
	{
		if(c+4 >= size)
			break;
		memcpy(&ID, &buffer[c], 4);
		c += 4;
		memcpy(&at, &buffer[c], sizeof(AreaTrigger));
		c+=sizeof(AreaTrigger);
		if(ID) RealmServer.AreaTriggers[ID]=at;
	}
	free(buffer);
	return true;
}

void InitGOLoots()
{
	unsigned long guid;
	unsigned long count;
	LootItem li;
	CGameObjectTemplate *pTemplate;
	FILE *f=fopen("data/gameobjloot.dat", STORAGE_READ);
	if(f==NULL) return;
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f,0,SEEK_SET);
	while(1)
	{
		if(fread(&guid,sizeof(unsigned long),1,f)!=1)
		{
			fclose(f);
			return;
		}
		if(fread(&count,sizeof(unsigned long),1,f)!=1)
		{
			fclose(f);
			return;
		}
		if(!DataManager.RetrieveObject((CWoWObject**)&pTemplate,OBJ_GAMEOBJECTTEMPLATE,guid)) pTemplate=NULL;
		else pTemplate->LootTable.clear();
		for(unsigned long i=0;i<count;i++)
		{
			if(fread(&li,sizeof(LootItem),1,f)!=1)
			{
				fclose(f);
				return;
			}
			if(pTemplate) pTemplate->LootTable.push_back(li);
		}
		if(ftell(f) >= size)
		{
			fclose(f);
			return;
		}
	}
}

struct Point
{
	unsigned long X;
	unsigned long Y;
	float Z;
};

bool LoadMapFile(FILE *f)
{
	unsigned long Header[3]; // Continent, AreaID, Count
	if(fread(Header,4,3,f)!=3)// || Header[0] > 1)
	{
		fclose(f);
		return false;
	}

	Point Pt;
	CContinent *pContinent=RegionManager.Continents[Header[0]];
	if(!pContinent)
	{
		Debug.Logf("Continent %i not found.",Header[0]);
		return false;
	}
	for(unsigned long i=0;i<Header[2];i++)
	{
		if(!fread(&Pt,sizeof(Point),1,f))
		{
			fclose(f);
			Debug.Logf("Map File (continent %04X, area %04X) invalid: expected %i points, got %i",Header[0],Header[1],Header[2],i);
			return false;
		}
		pContinent->HeightMap[((Pt.X & HEIGHTMAP_MASK) << 16) + (Pt.Y & HEIGHTMAP_MASK)]=Pt.Z;
	}
	fclose(f);
	return true;
}

bool DoItemTemplates(unsigned long ID)
{
	CItemTemplate *pTemplate;
	if (!DataManager.RetrieveObject((CWoWObject**)&pTemplate, OBJ_ITEMTEMPLATE, ID))
		return true;

	//DataManager.ItemTemplates[pTemplate->Data.ItemID] = ID;
	return true;
}

void LoadTrainTemplates(void)
{
	/*	if(!FileExists("data/selltemplates.bin"))
	{
	Debug.Log("Sell Template data file not found!!!!!");
	return;
	}*/
	FILE *f = fopen("data/trainertemplates.bin","rb");
	if (!f)
	{
		Debug.Log("Can't open trainertemplates.bin");
		return;
	}

	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	//long approxcount = size/sizeof(_TrainerTempBinItem);
	fseek(f,0,SEEK_SET);
	char *buffer = (char*)malloc(size);
	if(buffer == NULL || fread(buffer, size, 1, f) != 1)
	{
		fclose(f);
		return;
	}
	fclose(f);
	long c = 0;
	unsigned long creatureid;
	unsigned long creatureid2;
	unsigned long oldvendorid = 0;
	int vendorcount = 0;
	int itemcount = 0;

	_TrainerTempBinItem si;
	_TrainerItem trainitem;
	while(c < size)
	{
		if(c+4 >= size)
			break;
		memcpy(&creatureid, &buffer[c], 4);
		memcpy(&si, &buffer[c], sizeof(_TrainerTempBinItem));
		c+=sizeof(_TrainerTempBinItem);
		creatureid2 = DataManager.CreatureTemplates(creatureid);
		if (oldvendorid != creatureid2)
		{
			oldvendorid = creatureid2;
			vendorcount++;
		}

		// itemid = DataManager.ItemTemplates[si.SellID];
		trainitem.SkillLine = (short)RealmServer.SkillLines[si.SpellID];
		trainitem.SpellID = si.SpellID;
		trainitem.ReqSpell = si.ReqSpell;
		trainitem.SpellCost = (short)si.SpellCost;

		itemcount++;
		DataManager.TrainerTemplates[creatureid2].push_back(trainitem);
		///if (!(count % 689)) RealmServer.SetProgressBar(ftell(f)/size, approxcount, "Loading Trainers...");
		//if(ID) RealmServer.AreaTriggers[ID]=at;
	}
	free(buffer);
	Debug.Logf("%d spells at %d trainers loaded!", itemcount,vendorcount);
}

void LoadSellTemplates(void)
{
	/*	if(!FileExists("data/selltemplates.bin"))
	{
	Debug.Log("Sell Template data file not found!!!!!");
	return;
	}*/
	FILE *f = fopen("data/selltemplates.bin","rb");
	if (!f)
	{
		Debug.Log("Can't open selltemplate");
		return;
	}

	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f,0,SEEK_SET);
	char *buffer = (char*)malloc(size);
	if(buffer == NULL || fread(buffer, size, 1, f) != 1)
	{
		fclose(f);
		return;
	}
	fclose(f);
	long c = 0;
	unsigned long creatureid;
	unsigned long creatureid2;
	unsigned long itemid;
	unsigned long oldvendorid = 0;
	int vendorcount = 0;
	int itemcount = 0;

	_SellTempBinItem si;
	while(c < size)
	{
		if(c+4 >= size)
			break;
		memcpy(&creatureid, &buffer[c], 4);
		memcpy(&si, &buffer[c], sizeof(_SellTempBinItem));
		c+=sizeof(_SellTempBinItem);
		creatureid2 = DataManager.CreatureTemplates(creatureid);
		if (oldvendorid != creatureid2)
		{
			oldvendorid = creatureid2;
			vendorcount++;
		}

		itemid = DataManager.ItemTemplates(si.SellID);
		itemcount++;
		DataManager.SellTemplates[creatureid2].push_back(itemid);


		//if(ID) RealmServer.AreaTriggers[ID]=at;
	}
	free(buffer);
	char printtext[60];
	sprintf(printtext,"%d items at %d vendors loaded!", itemcount,vendorcount);
	Debug.Log(printtext);

}

bool InitQuestRelation(unsigned long ID)
{
	CQuestRelation *pqr;
	if (!DataManager.RetrieveObject((CWoWObject**)&pqr, OBJ_QUESTRELATION, ID))
		return true;

	if (pqr->Data.involver)
		DataManager.CreatureInvolvedRelation[pqr->Data.templateguid].push_back(pqr->Data.questguid);
	else
		DataManager.CreatureQuestRelation[pqr->Data.templateguid].push_back(pqr->Data.questguid);

	return true;
}

bool InitWaypoints()
{
	FILE *f = fopen("data/waypoints.bin","rb");
	if (!f)
	{
		Debug.Log("Can't open waypoints.bin");
		return false;
	}

	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	//long approxcount = size/sizeof(Waypoint);
	fseek(f,0,SEEK_SET);
	char *buffer = (char*)malloc(size);
	if(buffer == NULL || fread(buffer, size, 1, f) != 1)
	{
		fclose(f);
		return false;
	}
	fclose(f);
	long c = 0;
	int itemcount = 0;

	Waypoint point;

	while(c < size)
	{
		if(c+4 >= size)
			break;
		memcpy(&point, &buffer[c], sizeof(Waypoint));
		c+=sizeof(Waypoint);
		itemcount++;
		RealmServer.Waypoints[point.PointID] = point;
	}
	free(buffer);
	char printtext[60];
	sprintf(printtext,"%d waypoints loaded!", itemcount);
	Debug.Log(printtext);

	return true;
}

void CRealmServer::Go()
{
	SetStatusText("Loading Settings...");
	Settings.LoadSettings();

	if (CRealmServer::Initialize())
	{
		SetStatusText("Loading DBC files...");
		DBCManager.Initialize();

		SetStatusText("Loading Stored Data...");
		if (Storage.Initialize())
		{
			SetStatusText("Initializing Storage Manager...");
			// convert if necessary
			Storage.SetObjectSize(OBJ_ACCOUNT,sizeof(AccountData));
			Storage.SetObjectSize(OBJ_PLAYER,sizeof(PlayerData));
			Storage.SetObjectSize(OBJ_ITEM,sizeof(ItemData));
			Storage.SetObjectSize(OBJ_ITEMTEMPLATE,sizeof(ItemTemplateData));
			Storage.SetObjectSize(OBJ_CREATURE,sizeof(CreatureData));
			Storage.SetObjectSize(OBJ_CREATURETEMPLATE,sizeof(CreatureTemplateData));
			Storage.SetObjectSize(OBJ_SPAWNPOINT,sizeof(SpawnPointData));
			Storage.SetObjectSize(OBJ_LOOTTABLE,sizeof(LootTableData));
			Storage.SetObjectSize(OBJ_ZONE,sizeof(ZoneData));
			//			Storage.SetObjectSize(OBJ_CONTAINER,sizeof(ContainerData));
			Storage.SetObjectSize(OBJ_PATHGROUP,sizeof(PathGroupData));
			Storage.SetObjectSize(OBJ_GUILD,sizeof(GuildData));
			Storage.SetObjectSize(OBJ_CORPSE,sizeof(CorpseData));
			Storage.SetObjectSize(OBJ_QUESTINFO,sizeof(QuestData));
			Storage.SetObjectSize(OBJ_TRAINERTEMPLATE,sizeof(TrainerTemplateData));
			Storage.SetObjectSize(OBJ_QUESTRELATION,sizeof(QuestRelationData));

			// ok, set up the name caches
			SetStatusText("Finding Item Template IDs...");
			Storage.EnumObjectIDs(OBJ_ITEMTEMPLATE, DoItemTemplates);

			/*SetStatusText("Setting up default player info...");
			InitPlayerStartItems();*/ // now done in CPlayer::New()

			SetStatusText("Initializing Creature Templates...");
			Storage.EnumObjects(OBJ_CREATURETEMPLATE,DoCreatureTemplateNames);

			SetStatusText("Initializing Quest Relations...");
			Storage.EnumObjectIDs(OBJ_QUESTRELATION, InitQuestRelation);

			SetStatusText("Initializing Sell Templates...");
			// Storage.EnumObjectIDs(OBJ_SELLTEMPLATE, InitSellTemplates);
			LoadSellTemplates();

			SetStatusText("Loading Waypoints...");
			InitWaypoints();

			SetStatusText("Loading Accounts...");

			Storage.EnumObjects(OBJ_ACCOUNT,DoAccountNames);
			Storage.EnumObjects(OBJ_ACCOUNT,DoPlayerNames);

			SetStatusText("Finding Quests...");
			Storage.EnumObjectIDs(OBJ_QUESTINFO,InitQuestInfos);

#ifdef WIN32
			SetStatusText("Initializing Skill Lines...");
#endif
			InitSkillLines();
#ifndef WIN32
			printf("\r%-79s\n","Initializing Skill Lines: Done");
#endif

			SetStatusText("Initializing Trainer Templates...");
			//Storage.EnumObjectIDs(OBJ_TRAINERTEMPLATE, DoTrainerTemplateInit);
			LoadTrainTemplates();

			SetStatusText("Freeing temp memory...");
			SkillLines.clear();

#ifdef WIN32
#define NUMMAPS 859
			CFileFind fileFinder;
			/*
			char acctdir[1024];
			strcpy(acctdir,Settings.accounts_path);
			for(unsigned long i=0;i<strlen(Settings.accounts_path);i++) //windows sux0rs with backslashes!
			{
				if(acctdir[i]=='/') acctdir[i]='\\';
			}
			strcat(acctdir,"\\*.*");
			BOOL working = fileFinder.FindFile(acctdir);
			CClient *tempClient=new CClient;
			while(working)
			{
				working = fileFinder.FindNextFile();
				if(fileFinder.GetFileName()[0] != '.')
				{
					LoadAccount(fileFinder.GetFileName().GetBuffer(),tempClient, true);
				}
			}
			delete tempClient;
			*/

			SetStatusText("Loading Maps...");
			int ct=0;
			char mapsdir[1024];
			strcpy(mapsdir,Settings.maps_path);
			for(unsigned long i=0;i<strlen(Settings.maps_path);i++) //windows sux0rs with backslashes!
			{
				if(mapsdir[i]=='/') mapsdir[i]='\\';
			}
			strcat(mapsdir,"\\map????????.bin");
			BOOL working = fileFinder.FindFile(mapsdir);
			char fn[1024];
			while(working)
			{
				working = fileFinder.FindNextFile();
				ct++;
				if(!(ct&3)) // ct % 4
				{
					dlg->Ctl_Progress.SetPos(100*ct/NUMMAPS);
				}
				strcpy(fn,Settings.maps_path);
				strcat(fn,fileFinder.GetFileName().GetBuffer());
				FILE *f=fopen(fn,"rb");
				if(!f) continue;
				LoadMapFile(f); //will automatically close file
				// true = success, false = failure
			}
			dlg->Ctl_Progress.SetPos(0);
#else
#define NUMMAPS 861
			DIR *pdir;
			struct dirent *pent;
			/*
			char acctdir[1024];
			strcpy(acctdir,"./");
			strcat(acctdir,Settings.accounts_path);
			strcat(acctdir,"/");
			pdir=opendir(acctdir);
			CClient *tempClient=new CClient;
			if(pdir)
			{
				errno=0;
				while ((pent=readdir(pdir)))
				{
					LoadAccount(pent->d_name,tempClient, true);
				}
				closedir(pdir);
			}
			delete tempClient;
			*/

			setbuf(stdout,NULL);
			char mapsdir[1024];
			strcpy(mapsdir,"./");
			strcat(mapsdir,Settings.maps_path);
			strcat(mapsdir,"/");
			pdir=opendir(mapsdir);
			char fn[1024];
			if(pdir)
			{
				printf("Progress: %3i/%3i",0,NUMMAPS);
				errno=0;
				int count=0;
				while ((pent=readdir(pdir)))
				{
					count++;
					SetProgressBar(count,NUMMAPS,"Loading Maps");
					strcpy(fn,Settings.maps_path);
					char *mapfilename=pent->d_name;
					if(strlen(mapfilename)!=15) continue;
					if(strncmp(mapfilename,"map",3)) continue;
					if(strncmp(mapfilename+11,".bin",4)) continue;
					strcat(fn,pent->d_name);
					FILE *f=fopen(fn,"rb");
					if(!f) continue;
					LoadMapFile(f); //will automatically close file
					// true = success, false = failure
				}
				closedir(pdir);
				printf("\r%-79s\n","Loading Maps: Done");
			}
			else printf("Error: maps not found.\n");
#endif // WIN32
#undef NUMMAPS
			SetStatusText("Precaching objects...");
			Storage.EnumObjectIDs(OBJ_PATHGROUP,InitPathGroups); // set up pathing point groups
			Storage.EnumObjectIDs(OBJ_SPAWNPOINT,InitSpawnPoints); // cache spawn points
			Storage.EnumObjectIDs(OBJ_GUILD,InitGuilds); // cache guilds

			// cache Texts and load Mail
			SetStatusText("Loading Texts and Mails...");
			Storage.EnumObjectIDs(OBJ_NPCTEXT,PreCacheNPCTexts);
			Storage.EnumObjectIDs(OBJ_PAGETEXT,PreCachePageTexts);
			Storage.EnumObjectIDs(OBJ_MAIL,LoadMails);

			SetStatusText("Loading Areatriggers...");
			InitAreaTriggerTable();
			SetStatusText("Mapping GameObject Templates...");
			Storage.EnumObjectIDs(OBJ_GAMEOBJECTTEMPLATE,DoGOTemplateInit);
			SetStatusText("Loading GameObject loot...");
			InitGOLoots();
			SetStatusText("Loading GameObjects...");
			Storage.EnumObjectIDs(OBJ_GAMEOBJECT,LoadGO);
			SetStatusText("Loading Creatures...");
			Storage.EnumObjectIDs(OBJ_CREATURE,LoadCreatures);
		}
#ifdef WIN32 // On *nix, progress bar will automatically update the progress
		SetStatusText("Spawning Creatures...");
#endif
		SpawnSavedCreatures();
#ifdef WIN32
		SetStatusText("Spawning GameObjects...");
#endif
		SpawnSavedGameObjects();

		SetStatusText("Loading TaxiHandler Data...");
		LoadTaxiData();

		SetStatusText("Spawning Spirithealers");
		//SpawnSpiritHealers();

		RealmThread.BeginThread(RealmServerThreadFunction,this);
		SetStatusText("Running");
#ifdef WIN32
		if(dlg)
		{
			dlg->Ctl_Progress.SetPos(0);
			dlg->Txt_ServerName.SetWindowText(Name);
			dlg->Btn_SendPacketDlg.EnableWindow();
			dlg->Btn_Save.EnableWindow();
			dlg->Btn_SendMail.EnableWindow();
			dlg->rs_started=TRUE;
			dlg->Btn_StartButton.SetBitmaps(IDB_BITMAP_STOP_NORMAL,IDB_BITMAP_STOP_OVER,IDB_BITMAP_STOP_PRESSED,IDB_BITMAP_STOP_DISABLED);
			dlg->Btn_StartButton.SetWindowText("&Stop");
			dlg->Btn_StartButton.EnableWindow(true);
		}
#endif
	}
#ifdef WIN32
	else if(dlg)
	{
		dlg->Txt_Status.SetWindowText("Failed to start! Ports not available.");
		RealmServer.Listener.Close();
		//RealmServer.RedirectListener.Close();
		//RealmServer.LoginListener.Close();
		RealmServer.MasterLists.Cleanup();
		RealmServer.MasterList.ShutDown();
		dlg->Btn_StartButton.EnableWindow(true);
	}
#else
	else
	{
		printf("Failed to start! Ports not available.");
		exit(1); //error code!
	}
#endif
}

void CRealmServer::SetProgressBar (long progressPos, long progressTotal, char *label)
{
#ifndef WIN32
	printf ("\r%s: [",label);

	long barPos = progressPos * 30 / progressTotal + 1;
	long p;
	for (p = 0; p < barPos; p++) putchar ('#');
	for (; p < 30; p++) putchar (' ');

	printf ("] %d%%, %d/%d \r", progressPos * 100 / progressTotal, progressPos, progressTotal);
	fflush(stdout);
#else
	if (dlg) dlg->Ctl_Progress.SetPos(progressPos * 100 / progressTotal);
#endif
}

bool CRealmServer::Initialize()
{
	if (!Listener.Create(Settings.Port_Realm))
		return false;
	if (!Listener.Listen())
		return false;
	/*if (!RedirectListener.Create(Settings.Port_Redirect))
	return false;
	if (!RedirectListener.Listen())
	return false;*/
	/*if (!LoginListener.Create(8087))
	return false;
	if (!LoginListener.Listen())
	return false;*/
	if (!MasterList.Create(Settings.Port_Masterlist))
		return false;
	return true;
}

void CRealmServer::UpdateMasterLists(int State)
{
	// construct packet
	RealmPacket Packet;
	memset(&Packet,0,sizeof(RealmPacket));
	Packet.Port=(unsigned short)Settings.Port_Realm; //Port_Redirect;
	strcpy(Packet.IPAddr,RealmServer.IPAddr);
	switch(State)
	{
	case -1:
		Packet.Name[0]='*';
		Packet.Icon=(Settings.PvPServer?REALMICON_PVP:REALMICON_NORMAL);
		Packet.Language=REALMLANGUAGE_ENGLISH;
		strncpy(&Packet.Name[1],Name,62);
		Packet.Name[63]=0;
		break;
	case 1:
		Packet.nPlayers=nClients;
		Packet.Name[0]='*';
		Packet.Icon=(Settings.PvPServer?REALMICON_PVP:REALMICON_NORMAL);
		Packet.Language=REALMLANGUAGE_ENGLISH;
		strncpy(&Packet.Name[1],Name,62);
		Packet.Name[63]=0;
		break;
	case 0:
	default:
		Packet.nPlayers=nClients;
		Packet.Icon=(Settings.PvPServer?REALMICON_PVP:REALMICON_NORMAL);
		Packet.Language=REALMLANGUAGE_ENGLISH;
		strcpy(Packet.Name,Name);
		break;
	}
	int nRL=0;
	for (unsigned long i = 0 ; i < MasterLists.Size ; i++)
	{
		if (Addr* pAddr=MasterLists[i])
		{
			MasterList.SendTo(&Packet,sizeof(RealmPacket),*pAddr);
			nRL++;
		}
	}
#ifdef WIN32
	if(dlg && State!=-1)
	{
		char temp[80];
		sprintf(temp,"Connected to %i Realm List Server%c",nRL,(nRL==1)?'\x00':'s');
		dlg->Txt_RLStatus.SetWindowText(temp);
	}
#endif
}

CCreature *CRealmServer::GenerateCreatureNew(CCreatureTemplate *pTemplate, unsigned long Continent,
											 _Location Loc, float Facing)
{
	CCreature *pCreature = new CCreature;

	pCreature->New(*pTemplate);
	pCreature->Data.Continent=Continent;
	pCreature->Data.SpawnLoc=Loc;
	pCreature->Data.Loc=Loc;
	pCreature->Data.SpawnFacing=Facing;
	pCreature->Data.Facing=Facing;
	pCreature->pTemplate=pTemplate;
	pCreature->FirstPoint=0;
	DataManager.NewObject(*pCreature);

	return pCreature;
}

CCreature *CRealmServer::GenerateCreature(unsigned long Model, const char *Name, unsigned long Continent,
										  _Location Loc, float Facing)
{
	return NULL;	// THIS FUNCTION SHOULD NOT BE CALLED ANYMORE!
	/*
	CCreatureTemplate *pCreatureTemplate = NULL;
	CCreature *pCreature = new CCreature;
	string TemplateName=Name;
	MakeLower(TemplateName);
	int TemplateID=DataManager.CreatureTemplateNames[TemplateName];
	if(!TemplateID || !DataManager.RetrieveObject((CWoWObject**)&pCreatureTemplate, OBJ_CREATURETEMPLATE, TemplateID))
	{
	pCreatureTemplate=new CCreatureTemplate;
	pCreatureTemplate->New(Name);
	pCreatureTemplate->Generated=true;
	pCreature->New(pCreatureTemplate->guid);
	//		strcpy(pCreature->Data.Name,Name);
	pCreature->Data.CurrentStats.HitPoints=65;
	pCreature->Data.Level=1;
	pCreature->Data.Model=Model;
	pCreature->Data.NormalStats.HitPoints=65;
	pCreature->Data.DamageMax=6;
	pCreature->Data.DamageMin=4;
	pCreature->Data.Exp = 200;
	pCreature->Data.Continent=Continent;
	pCreature->Data.SpawnLoc=Loc;
	pCreature->Data.Loc=Loc;
	pCreature->Data.SpawnFacing=Facing;
	pCreature->Data.Facing=Facing;
	DataManager.NewObject(*pCreatureTemplate);
	}
	else
	{
	pCreature->New(*pCreatureTemplate);
	pCreature->Data.Continent=Continent;
	pCreature->Data.SpawnLoc=Loc;
	pCreature->Data.Loc=Loc;
	pCreature->Data.SpawnFacing=Facing;
	pCreature->Data.Facing=Facing;
	}
	pCreature->pTemplate=pCreatureTemplate;
	DataManager.NewObject(*pCreature);

	// lets make him despawn.
	// creatures will live for 300 seconds  (5 minutes)
	//EventManager.AddEvent(*Creature,300000,EVENT_CREATURE_DESPAWN,0,0);
	//EventManager.AddEvent(*Creature,10000,EVENT_CREATURE_REGENERATE,0,0);
	//if(!pCreature->Data.NPCType) EventManager.AddEvent(*pCreature,30000,EVENT_CREATURE_WANDER,0,0);

	return pCreature;*/
}

CTaxiMob *CRealmServer::GenerateTaxiMob(unsigned long Model, const char *Name, unsigned long Continent,
										_Location Loc, float Facing)
{
	CTaxiMob *pCreature = new CTaxiMob;
	CCreatureTemplate *pCreatureTemplate=new CCreatureTemplate;
	pCreatureTemplate->New(Name);
	pCreatureTemplate->Data.Level = 1;
	pCreatureTemplate->Data.Model = Model;
	pCreatureTemplate->Data.NormalStats.HitPoints = 65;
	pCreatureTemplate->Data.DamageMax = 6;
	pCreatureTemplate->Data.DamageMin = 4;
	pCreatureTemplate->Generated=true;
	pCreature->New(pCreatureTemplate->guid);
	pCreature->Data.CurrentStats.HitPoints=65;
	pCreature->Data.Continent=Continent;
	pCreature->Data.SpawnLoc=Loc;
	pCreature->Data.Loc=Loc;
	pCreature->Data.SpawnFacing=Facing;
	pCreature->Data.Facing=Facing;
	pCreature->FirstPoint=0;
	DataManager.NewObject(*pCreatureTemplate);
	pCreature->pTemplate=pCreatureTemplate;
	//DataManager.NewObject(*pCreature);
	return pCreature;
}

void CRealmServer::BroadcastOutPacket(unsigned short OpCode, void *buffer, unsigned short Length)
{
	CLock L(&Clients.CS);// exclusive lock on clients for this, not guaranteed to be in the realm server thread
	for (unsigned long i = 0 ; i < Clients.Size ; i++)
	{
		if (CClient *pClient=Clients[i])
		{
			pClient->OutPacket(OpCode,buffer,Length);
		}
	}
}

void CRealmServer::SetStatusText(char newtext[])
{
#ifdef WIN32
	if(dlg)
	{
		dlg->Txt_Status.SetWindowTextA(newtext);
		dlg->LogText(newtext);
	}
#else
	puts(newtext);
#endif
}

void CRealmServer::SpawnSpiritHealers(void)
{
	CCreature *pCreature = NULL;
	CCreatureTemplate *pTemplate = NULL;
	int count = 0;

	if(DataManager.RetrieveObject((CWoWObject**)&pTemplate,OBJ_CREATURETEMPLATE,SPIRITHEALER_GUID))
	{
		for (int i=0; i<NUM_GRAVEYARDS; i++)
		{
			_Location loc;
			unsigned long continent = SHLocations[i].Continent;
			loc.X = SHLocations[i].Loc.X;
			loc.Y = SHLocations[i].Loc.Y;
			loc.Z = SHLocations[i].Loc.Z;
			pCreature = GenerateCreatureNew(pTemplate,continent,loc,0);
			RegionManager.ObjectNew(*pCreature,0,loc.X,loc.Y);
			SetProgressBar(i+1,NUM_GRAVEYARDS, "Spawning Spirithealers");
			count++;
		}
	}
	Debug.Logf("%d spirit healers spawned.",count);

	return;
}

int CRealmServer::SpawnSavedCreatures(void)
{
	CCreature *pCreature = NULL;
	int count = 0;
	long filesize;
	string creaturename;

	FILE *f = fopen("data/spawns.sav", STORAGE_READ);
	if(f == NULL)
		return -1;
	fseek(f,0,SEEK_END);
	filesize=ftell(f);
	fseek(f,0,SEEK_SET);
	long size = sizeof(CreatureSaveData);
	long approxcreatures=filesize/size;
	long spawnedcreatures = 0;
	char *buffer = (char*)malloc(size);
	unsigned long templatenumber;
	unsigned short spawnid = 0;
	CCreatureTemplate *pTemplate = NULL;
	if(buffer == NULL)
	{
		fclose(f);
		return -1;
	}
	while (fread(buffer, size, 1, f) == 1)
	{
		count++;
		if (!(count % 689)) SetProgressBar(ftell(f)/size, approxcreatures, "Spawning Creatures");
		CreatureSaveData *Data = (CreatureSaveData *)buffer;
		templatenumber=DataManager.CreatureTemplates(Data->TemplateID);
		//temp disabled check on SH; they don't show up?
		//if(templatenumber==SPIRITHEALER_GUID) continue; // don't spawn SH, we spawn those independently
		if(DataManager.RetrieveObject((CWoWObject**)&pTemplate, OBJ_CREATURETEMPLATE, templatenumber))
		{
			pCreature = RealmServer.GenerateCreatureNew(pTemplate,Data->Continent, Data->Loc, Data->Facing);
			spawnedcreatures++;
			spawnid++;
			pCreature->Data.Template = templatenumber;
			pCreature->Data.SpawnID = spawnid;
			pCreature->Data.CurrentStats = pTemplate->Data.NormalStats;
			pCreature->FirstPoint = Data->FirstPoint;
			RegionManager.ObjectNew(*pCreature, pCreature->Data.Continent, pCreature->Data.Loc.X, pCreature->Data.Loc.Y);
			Spawns[spawnid] = *Data;
		} else {
			Debug.Logf("Can't spawn %d",Data->TemplateID);
		}
	}

#ifndef WIN32
	printf("%d of %d creatures spawned                                          \r\n", spawnedcreatures, approxcreatures);
#else
	Debug.Logf("%d of %d creatures spawned.", spawnedcreatures, approxcreatures);
#endif
	HighestSpawnID = spawnid;
	free(buffer);
	fclose(f);
	return 0;
}

int CRealmServer::SpawnSavedGameObjects(void)
{
	int count = 0;
	long filesize;

	FILE *f = fopen("data/gospawns.sav", STORAGE_READ);
	if(f == NULL)
		return -1;
	fseek(f,0,SEEK_END);
	filesize=ftell(f);
	fseek(f,0,SEEK_SET);
	long size = sizeof(GameObjectSaveData);
	long approxcreatures=filesize/size;
	long spawnedcreatures = 0;
	char *buffer = (char*)malloc(size);
	unsigned long templatenumber;
	CGameObjectTemplate *pTemplate = NULL;
	CGameObject *pObject;
	if(buffer == NULL)
	{
		fclose(f);
		return -1;
	}
	while (fread(buffer, size, 1, f) == 1)
	{
		count++;
		if (!(count % 289)) SetProgressBar(ftell(f)/size, approxcreatures, "Spawning GameObjects");
		GameObjectSaveData *Data = (GameObjectSaveData *)buffer;
		templatenumber=Data->TemplateID;
		if(DataManager.RetrieveObject((CWoWObject**)&pTemplate, OBJ_GAMEOBJECTTEMPLATE, templatenumber))
		{
			spawnedcreatures++;
			pObject = new CGameObject;
			pObject->New(templatenumber);
			pObject->Data.Continent = Data->Continent;
			pObject->Data.Loc.X = Data->Loc.X;
			pObject->Data.Loc.Y = Data->Loc.Y;
			pObject->Data.Loc.Z = Data->Loc.Z;
			pObject->Data.Facing = Data->Facing;
			pObject->Data.Rotation[0] = Data->Rotation[0];
			pObject->Data.Rotation[1] = Data->Rotation[1];
			pObject->Data.Rotation[2] = Data->Rotation[2];
			pObject->Data.Rotation[3] = Data->Rotation[3];
			// pObject->Data.Model = pTemplate->Data.Model;
			// pObject->Data.Type = pTemplate->Data.Type;
			// pObject->Data.Flags = pTemplate->Data.Flags;
			pObject->Data.Faction = pTemplate->Data.Faction;
			/*if (Data->GType)
			{
			pObject->pTemplate->Data.GType = Data->GType;
			}
			if (Data->Type)
			{
			pObject->pTemplate->Data.Type = Data->Type;
			}*/
			DataManager.NewObject(*pObject);
			RegionManager.ObjectNew(*pObject, pObject->Data.Continent, pObject->Data.Loc.X, pObject->Data.Loc.Y);
		}
	}

#ifndef WIN32
	printf("%d of %d gameobjects spawned                                          \r\n", spawnedcreatures, approxcreatures);
#else
	Debug.Logf("%d of %d gameobjects spawned.", spawnedcreatures, approxcreatures);
#endif
	free(buffer);
	fclose(f);
	return 0;
}
