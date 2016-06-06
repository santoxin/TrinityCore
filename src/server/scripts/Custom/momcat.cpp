#include "Config.h"
#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "bot_ai.h"
#include "Chat.h"

#define MSG_GOSSIP_INTRO_A	"|TInterface\\icons\\INV|Misc|GroupNeedMore:32:32:0:-1|t MINIONS! MINIONS! MINIONS!"
#define MSG_GOSSIP_INTRO_B	"Only the best minions found here!"
#define MSG_GOSSIP_INTRO_C	"|TInterface\\icons\\Spell|Arcane|FocusedPower:32:32:0:-1|t Lonely?"
#define MSG_GOSSIP_INTRO_D	"|TInterface\\icons\\Achievement|Reputation|01:32:32:0:-1|t Need a helping hand?"
#define MSG_GOSSIP_INTRO_E	"|TInterface\\icons\\Achievement|WorldEvent|ChildrensWeek:32:32:0:-1|t Taking over the world?"
#define MSG_GOSSIP_INTRO_F	"Look no further!"
#define MSG_GOSSIP_INTRO_G	"|TInterface\\icons\\Achievement|WorldEvent|BrewMaster:32:32:0:-1|t Order YOUR own Minion NOW!"

#define MSG_GOSSIP_NEXTPAGE	"Next -->"
#define MSG_GOSSIP_BACK		"(Back)"

#define ICON_GOSSIP_BALOON	0
#define ICON_GOSSIP_WING 	2
#define ICON_GOSSIP_BOOK 	3
#define ICON_GOSSIP_WHEEL1 	4
#define ICON_GOSSIP_WHEEL2 	5
#define ICON_GOSSIP_GOLD 	6
#define ICON_GOSSIP_BALOONDOTS 	7
#define ICON_GOSSIP_TABARD 	8
#define ICON_GOSSIP_XSWORDS 	9

#define MSG_CONGRATS		"Congratulations on your Mail Order Minion! They should be there shortly."

#define GOSSIP_SENDER_PICKCLASS

class momcat : public ItemScript
{
public:
    momcat() : ItemScript("momcat") { }
    
    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override
    {
        player->PlayerTalkClass->ClearMenus(); //clears old options
//        player->ADD_GOSSIP_ITEM(0, "|TInterface\\icons\\INV|Misc|GroupNeedMore:32:32:0:-1|t MINIONS! MINIONS! MINIONS!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
//        player->ADD_GOSSIP_ITEM(0, MSG_GOSSIP_INTRO_B, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);    
//        player->ADD_GOSSIP_ITEM(0, MSG_GOSSIP_INTRO_C, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
//        player->ADD_GOSSIP_ITEM(0, MSG_GOSSIP_INTRO_D, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
//        player->ADD_GOSSIP_ITEM(0, MSG_GOSSIP_INTRO_E, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
//        player->ADD_GOSSIP_ITEM(0, MSG_GOSSIP_INTRO_F, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
//        player->ADD_GOSSIP_ITEM(0, MSG_GOSSIP_INTRO_G, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->ADD_GOSSIP_ITEM(0, MSG_GOSSIP_NEXTPAGE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
//        menus = true;
        return false;
    }
    
    void OnGossipSelect(Player* player, Item* /*item*/, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        bool subMenu = false;
        
        switch (action)
        {	
            case GOSSIP_ACTION_INFO_DEF + 1:
            {
                subMenu = true;
                break;
            }
            player->CLOSE_GOSSIP_MENU();
        }
        player->CLOSE_GOSSIP_MENU();
    }
};
    
void AddSC_momcat()
{
    new momcat();
}
          