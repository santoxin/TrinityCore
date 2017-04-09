#include <time.h>
#include "ScriptPCH.h"
#include "Language.h"
#include "ScriptedGossip.h"
#include "bot_ai.h"

#define HERO_GOSSIP_MESSAGE DEFAULT_GOSSIP_MESSAGE

#define GOSSIP_SENDER_WOWBOOK_DALARAN GOSSIP_ACTION_INFO_DEF + 1
#define GOSSIP_SENDER_WOWBOOK_HEROS GOSSIP_ACTION_INFO_DEF + 2
#define GOSSIP_SENDER_WOWBOOK_SHOP GOSSIP_ACTION_INFO_DEF + 3
#define GOSSIP_SENDER_WOWBOOK_RIDER GOSSIP_ACTION_INFO_DEF + 4
#define GOSSIP_SENDER_WOWBOOK_MEMBERSHIP GOSSIP_ACTION_INFO_DEF + 5
#define GOSSIP_SENDER_WOWBOOK_HERO_DETAILS GOSSIP_ACTION_INFO_DEF + 6

class wowbook : public ItemScript
{
	private:
		uint32 currentBotClass;
		uint32 currentBot;
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
				AddGossipItemFor(player, GOSSIP_ICON_CHAT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_HEROS), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_HEROS);
				//AddGossipItemFor(player, GOSSIP_ICON_CHAT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_SHOP), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_SHOP);
				//AddGossipItemFor(player, GOSSIP_ICON_CHAT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_RIDER), GOSSIP_SENDER_MAIN, GOSSIP_SENDER_WOWBOOK_RIDER);
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
					OnListHeroClasses(player, _item);
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
			else if (sender == GOSSIP_SENDER_WOWBOOK_HEROS) 
			{
				ClearGossipMenuFor(player);
				OnListHerosForClass(player, _item, uiAction);
			}
			else if (sender == GOSSIP_SENDER_WOWBOOK_HERO_DETAILS)
			{
				if (uiAction == 0)//back
				{
					OnListHerosForClass(player, _item, currentBotClass);
				}
				else
				{
					CloseGossipMenuFor(player);
					player->SummonBot(currentBot);
				}
			}
			return true;
		}
		void OnShowHeroDetails(Player* player, Item *_item, uint32 heroId)
		{
			ObjectGuid guildHero = ObjectGuid(HighGuid::Unit, heroId);
			if (player->HaveBot(guildHero))
			{
				AddGossipItemFor(player, GOSSIP_ICON_DOT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_SUMMON), GOSSIP_SENDER_WOWBOOK_HERO_DETAILS, heroId);
			}
			currentBot = heroId;
			AddGossipItemFor(player, GOSSIP_ICON_DOT, player->GetSession()->GetTrinityString(LANG_SLOT_NAME_BACK), GOSSIP_SENDER_WOWBOOK_HERO_DETAILS, 0);
			SendGossipMenuFor(player, HERO_GOSSIP_MESSAGE, _item->GetGUID());
		}
		void OnListHerosForClass(Player* player, Item *_item, uint32 uiAction)
		{
			CloseGossipMenuFor(player);
			ClearGossipMenuFor(player);
			if (uiAction > BOT_CLASS_NORMAL_END)//show hero details, uiAction is hero id
			{
				OnShowHeroDetails(player, _item, uiAction);
			}
			else
			{
				uint8 botclass = uiAction;
				currentBotClass = botclass;
				uint8 localeIndex = ChatHandler(player->GetSession()).GetSessionDbLocaleIndex();
				CreatureTemplateContainer const* ctc = sObjectMgr->GetCreatureTemplates();
				int idx = 0;
				for (CreatureTemplateContainer::const_iterator itr = ctc->begin(); itr != ctc->end()&&idx<10; ++itr)
				{
					uint32 id = itr->second.Entry;
					std::string name;
					
					if (id < BOT_ENTRY_BEGIN || id > BOT_ENTRY_END) continue;
					uint32 trainer_class = itr->second.trainer_class;
					if (trainer_class != botclass) continue;
					
					if (CreatureLocale const* creatureLocale = sObjectMgr->GetCreatureLocale(id))
					{
						if (creatureLocale->Name.size() > localeIndex && !creatureLocale->Name[localeIndex].empty())
						{
							name = creatureLocale->Name[localeIndex];
						}
					}
					else
						name = itr->second.Name;

					if (name.empty())
						continue;
					++idx;
					AddGossipItemFor(player, GOSSIP_ICON_DOT, name, GOSSIP_SENDER_WOWBOOK_HEROS, id);
				}
			}


			SendGossipMenuFor(player, HERO_GOSSIP_MESSAGE, _item->GetGUID());
		}
		void OnListHeroClasses(Player* player, Item *_item)
		{
			CloseGossipMenuFor(player);
			for (int i = BOT_CLASS_NORMAL_START; i <= BOT_CLASS_NORMAL_END; i++)
			{
				if (i == 10)continue;
				AddGossipItemFor(player, GOSSIP_ICON_DOT, player->GetSession()->GetTrinityString(LANG_HEROS_CLASS_BASE+i), GOSSIP_SENDER_WOWBOOK_HEROS, i);
			}
			
			SendGossipMenuFor(player, HERO_GOSSIP_MESSAGE, _item->GetGUID());
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