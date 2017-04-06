#include <time.h>
#include "ScriptPCH.h"
#include "Language.h"
#include "ScriptedGossip.h"

#define GOSSIP_SENDER_WOWBOOK_DALARAN GOSSIP_ACTION_INFO_DEF + 1
#define GOSSIP_SENDER_WOWBOOK_HEROS GOSSIP_ACTION_INFO_DEF + 2
#define GOSSIP_SENDER_WOWBOOK_SHOP GOSSIP_ACTION_INFO_DEF + 3
#define GOSSIP_SENDER_WOWBOOK_RIDER GOSSIP_ACTION_INFO_DEF + 4
#define GOSSIP_SENDER_WOWBOOK_MEMBERSHIP GOSSIP_ACTION_INFO_DEF + 5

class wowbook : public ItemScript
{
    public:
        wowbook() : ItemScript("wowbook") { }
 		bool OnUse(Player *player, Item *_item, SpellCastTargets const& /*targets*/)
		{
			if (player->IsInCombat())
			{
				CloseGossipMenuFor(player);
				ChatHandler(player->GetSession()).PSendSysMessage(player->GetSession()->GetTrinityString(LANG_YOU_IN_COMBAT));
				return true;
			}
			else
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, player->GetSession()->GetTrinityString(LANG_CITY_DALARAN), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_DALARAN);
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, player->GetSession()->GetTrinityString(LANG_WOWBOOK_HEROS), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_HEROS);
				AddGossipItemFor(player, GOSSIP_ICON_CHAT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_SHOP), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_SHOP);
				AddGossipItemFor(player, GOSSIP_ICON_CHAT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_RIDER), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_RIDER);
				AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, player->GetSession()->GetTrinityString(LANG_WOWBOOK_QUERY_MEMBERSHIP), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_MEMBERSHIP);
			}
			SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, _item->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player *player, Item *_item, uint32 sender, uint32 uiAction)
		{
			if (player->IsInCombat())
			{
				CloseGossipMenuFor(player);
				ChatHandler(player->GetSession()).PSendSysMessage(player->GetSession()->GetTrinityString(LANG_YOU_IN_COMBAT));
				return true;
			}

			if (sender == GOSSIP_SENDER_MAIN)
			{
				ClearGossipMenuFor(player);
				switch(uiAction)
				{
				case GOSSIP_SENDER_WOWBOOK_DALARAN: //LANG_CITY_DALARAN
					CloseGossipMenuFor(player);
					player->TeleportTo(571, 5804.149902f, 624.770996f, 647.767029f, 1.640000f);
					break;
				case GOSSIP_SENDER_WOWBOOK_HEROS: //LANG_WOWBOOK_HEROS
					OnHandleHeros(player);
					break;
				case GOSSIP_SENDER_WOWBOOK_SHOP: //LANG_WOWBOOK_SHOP
					OnHandleMembershipShop(player);
					break;
				case GOSSIP_SENDER_WOWBOOK_RIDER: //LANG_WOWBOOK_RIDER
					OnHandleRiderShop(player);
					break;
				case GOSSIP_SENDER_WOWBOOK_MEMBERSHIP: //LANG_WOWBOOK_QUERY_MEMBERSHIP
					OnHandleMembership(player);
					break;
				default:
					break;
				}
			}
			return true;
		}

		void OnHandleHeros(Player* player)
		{
			AddGossipItemFor(player, GOSSIP_ICON_DOT, player->GetSession()->GetTrinityString(LANG_CITY_DALARAN), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_DALARAN);
			AddGossipItemFor(player, GOSSIP_ICON_DOT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_HEROS), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_HEROS);
			AddGossipItemFor(player, GOSSIP_ICON_DOT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_SHOP), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_SHOP);
			AddGossipItemFor(player, GOSSIP_ICON_DOT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_RIDER), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_RIDER);
			AddGossipItemFor(player, GOSSIP_ICON_DOT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_QUERY_MEMBERSHIP), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_MEMBERSHIP);
			SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, _item->GetGUID());
		}
		
		void OnHandleMembership(Player* player)
		{

		}

		void OnHandleMembershipShop(Player* player)
		{

		}

		void OnHandleRiderShop(Player* player)
		{

		}
};



void AddSC_wowbook()
{
    new wowbook();
}