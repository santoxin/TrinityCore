#include <time.h>
#include "ScriptPCH.h"
#include "Language.h"
#include "ScriptedGossip.h"

#define GOSSIP_SENDER_WOWBOOK_TRAINER 2
#define GOSSIP_SENDER_WOWBOOK_SHOP 3
#define GOSSIP_SENDER_WOWBOOK_RIDER 4
#define GOSSIP_SENDER_WOWBOOK_MEMBERSHIP 5

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
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, player->GetSession()->GetTrinityString(LANG_CITY_DALARAN), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				AddGossipItemFor(player, GOSSIP_ICON_CHAT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_SHOP), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
				AddGossipItemFor(player, GOSSIP_ICON_CHAT, player->GetSession()->GetTrinityString(LANG_WOWBOOK_RIDER), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, player->GetSession()->GetTrinityString(LANG_WOWBOOK_QUERY_MEMBERSHIP), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
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
				case GOSSIP_ACTION_INFO_DEF + 1: //LANG_CITY_DALARAN
					CloseGossipMenuFor(player);
					player->TeleportTo(571, 5804.149902f, 624.770996f, 647.767029f, 1.640000f);
					break;
				case GOSSIP_ACTION_INFO_DEF + 2: //LANG_WOWBOOK_SHOP
					OnHandleMembershipShop(player);
					break;
				case GOSSIP_ACTION_INFO_DEF + 3: //LANG_WOWBOOK_RIDER
					OnHandleRiderShop(player);
					break;
				case GOSSIP_ACTION_INFO_DEF + 4: //LANG_WOWBOOK_QUERY_MEMBERSHIP
					OnHandleMembership(player);
					break;
				default:
					break;
				}
			}
			return true;
		}

		const uint32 GetTrainerId(Player* player)
		{
			switch (player->getClass())
			{
			case CLASS_WARRIOR:
				return (player->GetTeam() == ALLIANCE)? 913: 3169;
			case CLASS_HUNTER:
				return (player->GetTeam() == ALLIANCE) ? 5516 : 3171;
			case CLASS_ROGUE:
				return (player->GetTeam() == ALLIANCE) ? 917 : 3170;
			case CLASS_DEATH_KNIGHT:
				return (player->GetTeam() == ALLIANCE) ? 28471 : 28471;
			case CLASS_MAGE:
				return (player->GetTeam() == ALLIANCE) ? 328 : 5880;
			case CLASS_WARLOCK:
				return (player->GetTeam() == ALLIANCE) ? 906 : 3172;
			case CLASS_PALADIN:
				return (player->GetTeam() == ALLIANCE) ? 927 : 16275;
			case CLASS_PRIEST:
				return (player->GetTeam() == ALLIANCE) ? 377 : 3706;
			case CLASS_SHAMAN:
				return (player->GetTeam() == ALLIANCE) ? 20407 : 3173;
			case CLASS_DRUID:
				return (player->GetTeam() == ALLIANCE) ? 5504 : 3064;
			default:
				break;
			}

			return 0;
		}
		void OnSummonTrainer(Player* player)
		{
			/*time_t now = time(0);
			if (now - player->m_lastSummonTrainerTime < 5 * 60)
			{
				ChatHandler(player->GetSession()).PSendSysMessage(player->GetSession()->GetTrinityString(LANG_SUMMON_TRAINER_CD));
				return;
			}*/
			ObjectGuid guid(HighGuid::Unit, GetTrainerId(player));
			Creature* tmp= player->GetMap()->GetCreature(guid);
			if(tmp==NULL)
				tmp = player->SummonCreature(GetTrainerId(player), player->GetPositionX() + 4, player->GetPositionY(), player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 5*60*1000);
			if (tmp)
			{
				//player->m_lastSummonTrainerTime = now;
				ChatHandler(player->GetSession()).PSendSysMessage(player->GetSession()->GetTrinityString(LANG_SUMMON_TRAINER_SUCCESS));
				player->PrepareGossipMenu(tmp, tmp->GetCreatureTemplate()->GossipMenuId);
				player->SendPreparedGossip(tmp);
			}
			else
			{
				ChatHandler(player->GetSession()).PSendSysMessage(player->GetSession()->GetTrinityString(LANG_SUMMON_TRAINER_FAIL));
			}
			//CloseGossipMenuFor(player);
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