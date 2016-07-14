*The Big Book of Bots.....*  
*The Mega Manual of Minions....*   
*blah..*   
# [ THE BOTS GUIDE ]
>Compiled by: Thesawolf (@ Gmail dot Com)  
>Version 0.1 - 13 July 2016
---------------------------------------
#### Sections
1. [Introduction](#introduction)
2. [NPCBots](#npcbots)
    - [NPCBot Commands](#npcbot-commands)
    - [NPCBot Control and Usage](#npcbot-control-and-usage)
        - [NPCBot Getting Started](#npcbot-getting-started)
        - [NPCBot Getting Around](#npcbot-getting-around)
        - [NPCBot Equipment](#npcbot-equipment)
        - [NPCBot Roles](#npcbot-roles)
        - [NPCBot Formation](#npcbot-formation)
        - [NPCBot Abilities](#npcbot-abilities)
        - [NPCBot Grouping](#npcbot-grouping)
        - [NPCBot Extras](#npcbot-extras)
    - [NPCBot Database Information](#npcbot-database-information)
    - [NPCBot System Usage Information](#npcbot-system-usage-information)
3. [PlayerBots](#playerbots)
    - [PlayerBot Commands](#playerbot-commands)
    - [PlayerBot Control and Usage](#playerbot-control-and-usage)
        - [PlayerBot Getting Started](#playerbot-getting-started)
        - [PlayerBot Getting Around](#playerbot-getting-around)
        - [PlayerBot Equipment](#playerbot-equipment)
        - [PlayerBot Roles](#playerbot-roles)
        - [PlayerBot Formation](#playerbot-formation)
        - [PlayerBot Abilities](#playerbot-abilities)
        - [PlayerBot Grouping](#playerbot-grouping)
        - [PlayerBot Extras](#playerbot-extras)
    - [PlayerBot Database Information](#playerbot-database-information)
    - [PlayerBot System Usage Information](#playerbot-system-usage-information)
4. [Guide Changelog](#guide-changelog)
---------------------------------------    
#### Introduction
First and foremost, please be aware that I do NOT take credit for the the coding, development and
documentation for all the marvels of engineering found in the "NPCBots" nor the "PlayerBots", that distinction
goes toward the known authors of those respective bot systems listed below:

- PlayerBots (aka MaNGOS-Bots) by ike3 (https://github.com/ike3/mangosbot)  
	Originally developed by Blueboy (https://github.com/playerbot/mangos)  
	with various enhancements by Thesawolf [hey, that's me] (https://github.com/thesawolf/TrinityCore)
	
- NPCBots (aka NewNPCBots, LordPsyanBots, MinionBots) by LordPsyan (https://bitbucket.org/lordpsyan/lordpsyan-patches)  
	with numerous enhancements by Graff/Trickerer (https://bitbucket.org/trickerer/trinity-bots/src)  
	and various enhancements by Thesawolf [hey, that's me again.. repo the same as previous] 

This guide is an ATTEMPT to better, and fully, document the commands and usage examples for the respective
bot systems.   
Please note that while every attempt is made to do so, this guide may not (nor ever) be
100% complete or thorough (but I'll try).
---------------------------------------
## NPCBOTS
NPCBots are minion-like bots that have limited functionality and control. They follow you around, buff you, attack things and occassionally they can do class-specific things like summon drink/water, open portals, summon healthstones, etc. They are most handy at lower levels or outside dungeons/raids although they CAN do dungeons and raids, but expect some frustrations due to the lack of controls for them.

#### NPCBot Commands
Command references are current up to the date of this documentation (and includes the various enhancements) by myself and may not be applicable to all installations out there. If a command doesn't show up in the listing or gives an error message that it's invalid.. there's a good chance that install/repack doesn't have a "current" codebase.

Also, please note that command access is dependent upon the installation you are using and some commands may not be
available to all accounts (depending on their access level and permissions set in the RBAC tables). Optionally, you can make RBAC adjustments by yourself with tools such as phpmyadmin, HeidiSQL to the rbac tables in the 'auth' database, but that is beyond the scope of this document.

>< > _(less/greater than)_ indicates information or action you need for the command, can be left out to list information  
>|  _(pipe character)_ indicates parameter options (i.e. this|that  = this OR that)  
>-- _(two dashes)_ indicates information follows about the command

**COMMAND**: **`.npcbot`** (by itself will list all syntax available)  
- **`lookup <CLASS>`** -- lookup the available npcbot Name/ID by class#  
    - _CLASS_ = Class# of npcbots (i.e. 1 for WARRIORs)  
    **Example Usage**:  
        - `.npcbot lookup` (to list all classes)  
        - `.npcbot lookup 1` (to list all Warriors)  
- **`add <ENTRY>`** -- adds npcbot bypassing the price conditions
	- _ENTRY_ = ID# of npcbot (obtained from lookup list)  
	**Example Usage**:
	    - `.npcbot add 70001` (to add npcbot with ID 70001 from lookup list)
- **`spawn <ENTRY>`** -- adds npcbot
    - _ENTRY_ = ID# of npcbot (obtained from lookup list)  
	**Example Usage**:
        - `.npcbot spawn 70001` (to spawn npcbot with ID 70001 from lookup list)
- **`set <faction|owner> TARGET`**
    - `faction <a|h|m|f> TARGET` -- sets the selected npcbot faction manually 
        - _a_ = alliance  
		- _h_ = horde  
		- _m_ = monster  
		- _f_ = friendly to all  
		- _TARGET_ = selected NPCBot  
	- `owner <GUID|NAME> TARGET` -- sets ownership of a selected npcbot to a specific player   
		- _GUID_ = guID of a player (in database)
		- _NAME_ = name of a player
		- _TARGET_ = selected npcbot  
        **Example Usage:**
            - `.npcbot set` (displays list of subcommands)
			- `.npcbot set faction` (displays list of subcommands for faction)
			- `.npcbot set faction a TARGET` (sets the selected NPCBot to Alliance)
			- `.npcbot set owner` (displays subcommand list)
			- `.npcbot set owner MyPlayer TARGET` (sets the selected NPCbot owner to MyPlayer)
- **`remove TARGET`** -- frees npcbot from control.  
    (_NOTE_: If an npcbot is selected, this will remove that specific npcbot or if a PLAYER is selected, this will remove ALL npcbots they own.  
The npcbot will then return to their spawned location.)
	- _TARGET_ = selected npcbot OR npcbots OF selected player, _see note above_   
	    **Example Usage:**
        - `.npcbot remove TARGET` (removes the selected npcbot or npcbots of selected player)
- **`delete TARGET`** -- deletes npcbot from control and active npcbot listing in database 
	- _TARGET_ = selected npcbot OR npcbots OF selected player
	    **Example Usage:**
        - `.npcbot delete TARGET` (deletes the selected npcbot or npcbots of selected player)
- **`revive TARGET`** -- revives selected npcbot. If player is selected, revives all npcbots of selected player)
	- _TARGET_ = selected npcbot OR npcbots OF selected player  
		**Example Usage:**
        - `.npcbot revive TARGET` (revives dead, selected npcbot or npcbots of selected player)
- **`cast`** -- dev only command and mostly deactivated code-wise
- **`info TARGET`** -- list npcbots' information for selected player or self
- **`reset TARGET`** -- resets selected npcbot. (_NOTE_: Cannot be used in combat)
- **`command <COMMAND>`** -- forces ALL npcbot followers to either FOLLOW or STAY
	- `command <s|st|stay|stand|f|fo|fol|follow>` -- sets the npcbot stances manually
		- _s, st, stay, stand_ = STAY mode
		- _f, fo, fol, follow_ = FOLLOW mode  
            **Example Usage:**
            - `.npcbot command stay` (selected npcbot will stay at location)
	        - `.npcbot command follow` (selected npcbot will follow owner)
- **`distance <#>`**  -- sets ALL npcbots follow distance from owner  
    (*NOTE*: If set to **0**, npcbots will follow passively
					(not attacking anything) until owner attacks something)
	- _#_ = value between 0 and 75 (75 being furthest distance away)  
		**Example Usage:**  
        - `.npcbot distance 0` (selected npcbot will follow and not attack anything)  
        - `.npcbot distance 75` (selected npcbot will follow you from furthest distance)

#### NPCBot Control and Usage
##### NPCBot Getting started
If this is your first time using an NPCBot, you'll need to do the following to get started:   
- `.npcbot lookup`  
    This will give you a listing of the available classes with an ID to indicate each class. For example, 1 could be the Class ID for Warriors.
    _Example Output_:
```
.npcbot lookup #class  
Looks up npcbots by #class, and retusn all matches with their creature ID's.
BOT_CLASS_WARRIOR = 1   
BOT_CLASS_PALADIN = 2   
BOT_CLASS_HUNTER = 3   
BOT_CLASS_ROGUE = 4   
BOT_CLASS_PRIEST = 5   
BOT_CLASS_DEATH_KNIGHT = 6   
BOT_CLASS_SHAMAN = 7   
BOT_CLASS_MAGE = 8   
BOT_CLASS_WARLOCK = 9   
BOT_CLASS_DRUID = 11   
BOT_CLASS_BM = 12   
```

After you have figured out which class you want to lookup NPCBots in:
- `.npcbot lookup 1`   
    For this example, we'll look for Warrior NPCBots.   
    _Example Output_:
```
Looking for bots of class 1...
70146 - [Wu]
70147 - [Ilsa]
70173 - [Darnath]
70175 - [Evencane]
70201 - [Kore]   
70217 - [Ahonan]
70220 - [Behomat]
70224 - [Ruada]
```
Next, you'll select an NPCBot from the list:
- `.npcbot spawn 70224`  
    For this example, we'll select _Ruada_ with an ID of 70224

Ruada will spawn at your location as a level 80 Warrior (by default, NPCBots spawn as Level 80)
In previous versions of the NPCBots, they would spawn as Level 80 Monsters and would require you to manually set their faction. Now, NPCBot '_Thesawolf_' enhancements have NPCBots automatically spawning as the faction of the individual spawning them. In the event of some SetFaction failure, the NPCBot will spawn with the "Friendly to All" faction so that they are not KoS (killed on sight) by city guards, etc. (another '_Thesawolf_' enhancement).   

Right-clicking on the NPCBot will open what's called a _Gossip Menu_ (which gives you some command choices)   
_Example Output_:
```
You need something?
- Will you follow me? (hire)
- Pick a side! (set faction)
- You can go now... (delete)
- Nevermind
```
Next, you'll most likely just select '_Will you follow me? (hire)_' which will popup a Hire box asking:   
"Do you wish to hire Ruada?", with a cost amount that you can _Accept_ or _Cancel_.

**Reference**: The other options in the pre-hire Gossip include:
- _Will You follow me? (hire)_ - already discussed
- _Pick a side! (set faction)_ - this selection will open a submenu displaying:
```
- Alliance
- Horde
- Monster
- Friend to all
- (BACK)
```
This option will let you set an NPCBot's faction that will allow you to attack them as a Monster or as an opposing faction member for PvP, etc.
- _You can go now... (delete)_ - this selection will delete the NPCBot (in case you change your mind or need to cleanup NPCBots left in various areas)
- _Nevermind_ - this selection closes the pre-hire Gossip Menu

After hiring the NPCBot, they will automatically level themselves to your level (shouting "DING!" in the process).
Right-clicking on the NPCBot will open a new _Gossip Menu_ with an assortment of options (discussed in following subsections). Your NPCBot will follow you around in or out of group, but it's probably a good idea to get them into your group so you can monitor their location on mini-map, or health/mana, etc. Your new hired Gossip Menu will show:
```
- Manage equipment...
- Manage roles...
- Manage formation...
- Use ability...
- <Create Group>
- [OPTIONAL options may be displayed here]
- You are dismissed
- You are free to go (reset owner)
- You are fired! (remove)
- Nevermind
```

NOTE: npcbots retain their spawn LOCATION and will return there when owner is logged out or npcbots is removed from control

##### NPCBot Getting Around   

##### NPCBot Equipment

##### NPCBot Roles

##### NPCBot Formation

##### NPCBot Abilities

##### NPCBot Grouping

##### NPCBot Extras


#### NPCBot Database information 
NPCBot data is stored in the following locations:   
- '`characters`' Database   
    - `characters_npcbot` (this contains currently loaded npcbots)   
	also uses:
	    - `character_inventory`
	    - `item_instance` (both for holding information about currently equipped gear for active npcbots)  
- '`world`' Database (stores information in the following tables)
    - `creature_template` (ids 70001-71000) 
    - `creature_template_outfits` (ids 70001-71000)
    - `creature_equip_template` (ids 70001-71000)
    - `creature_template_outfits` (ids 70001-71000)
    - `creature` (ids 70001-71000)
    - `npc_text` (ids 70001-71000)

If you wanted to make changes to the static template data used for NPCBots, you make adjustments
in the `world` Database to those specific ids in the above tables (i.e. npcbot model, outfits, etc.)

Live NPCBots (currently spawned into the world) are found in the `characters` Database

#### NPCBot System Usage information 
Bots are counted as active objects (keep grids loaded like players).  
Bots are being added to world at server loading (along with grids).  
If 2 or more bots are located in same grid, only one grid is loaded.  
If bot leaves grid where he was spawned (following player), that grid can be unloaded.  
Grid size is 533.333 (yd).  
Each grid loaded uses 30-50 Mb of memory.  
Each bot loaded (without grid) uses less than 0.2 Mb of memory.  
Current maximum bots to spawn: 245 (creature_template bot entries amount).  
--------------------------------------- 
## PLAYERBOTS

#### PlayerBot Commands
##### PlayerBot Getting Started

##### PlayerBot Getting Around

##### PlayerBot Equipment

##### PlayerBot Roles

##### PlayerBot Formation

##### PlayerBot Abilities

##### PlayerBot Grouping

##### PlayerBot Extras

#### PlayerBot Control and Usage

#### PlayerBot Database Information

#### PlayerBot System Usage Information

--------------------------------------- 
## Guide Changelog
Development tends to change alot (and hopefully this guide will reflect that). This Changelog should help to see what might've hapened to a feature you THOUGHT was available or if a feature gets deprecated, you can get a timeline when it happened.
- **Version 0.2** (_14 July 2016_)
    - PlayerBot Information
- **Version 0.1** (_13 July 2016_)  
    - NPCBot Information initial submit
        - added new info, reset, command, distance commands too
--------------------------------------- 
