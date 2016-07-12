#!/bin/bash
# ====================================================================
# please be aware that some of these are specific to my installation
# feel free to disable what you want and change your mysql uname/pword
# ====================================================================
echo "[ARAC]"
cd ./ARAC
echo "Applying initial ARAC (Any Race, Any Class) information..."
mysql -u root -p45c3nt world < world.sql
cd ..
echo "[arena1v1]"
cd ./arena1v1
echo "Applying Arena1v1 character components..."
mysql -u root -p45c3nt characters < character_v2.0.sql
echo "Applying Arena1v1 world creature components.."
mysql -u root -p45c3nt world < world_v1.0.sql
cd ..
echo "[Bots]"
cd ./Bots
echo "Applying MinionBots auth permissions..."
mysql -u root -p45c3nt auth < auth_bots.sql
echo "Applying MinionBots character tables..."
mysql -u root -p45c3nt characters < character_bots.sql
echo "Applying MinionBots world creature templates..."
mysql -u root -p45c3nt world < world_bots.sql
cd ..
echo "[ExtraNPCs]"
cd ./ExtraNPCs
echo "Applying ExtraNPCs world creature templates..."
mysql -u root -p45c3nt world < world-addnpcs.sql
cd ..
echo "[Guildhouses]"
cd ./Guildhouses
echo "Applying Guildhouses world creature and locations..."
mysql -u root -p45c3nt world < world_guildhouses.sql
cd ..
echo "[GuildLevelSystem]"
cd ./GuildLevelSystem
echo "Applying GuildLevelSystem auth permissions..."
mysql -u root -p45c3nt auth < auth_guild_level_system.sql
echo "Applying GuildLevelSystem characters guild levels..."
mysql -u root -p45c3nt characters < characters_guild_level_system.sql
echo "Applying GuildLevelSystem world components..."
mysql -u root -p45c3nt world < world_guild_level_system.sql
cd ..
echo "[objscale]"
cd ./objscale
echo "Applying Rochet objscale sql changes to allow for gob scaling..."
mysql -u root -p45c3nt auth < auth.sql
mysql -u root -p45c3nt world < world.sql
cd ..
echo "[GOMove]"
cd ./GOMove
echo "Applying Rochet GOMove spell targetting circle for GOMove..."
mysql -u root -p45c3nt world < world.sql
cd ..
echo "[ReforgingSQL]"
cd ./ReforgingSQL
echo "Applying Rochet Reforger components..."
mysql -u root -p45c3nt characters < characters.sql
mysql -u root -p45c3nt world < world_npc.sql
cd ..
echo "[Transmogrification]"
cd ./Transmogrification
echo "Applying Rochet Transmogrifier components..."
mysql -u root -p45c3nt characters < characters.sql
mysql -u root -p45c3nt world < world_NPC.sql
mysql -u root -p45c3nt world < world_texts.sql
cd ..
echo "[TransmogVendor]"
cd ./TransmogVendor
echo "Applying Rochet Transmog Vendor components..."
mysql -u root -p45c3nt characters < characters.sql
mysql -u root -p45c3nt world < world_NPC.sql
cd ..
echo "[PlayerBots]"
cd ./PlayerBots
echo "Applying ike3 PlayerBots components..."
mysql -u root -p45c3nt characters < characters_ai_playerbot.sql
mysql -u root -p45c3nt characters < characters_auctionhousebot.sql
mysql -u root -p45c3nt characters < characters_ai_playerbot_names.sql			
mysql -u root -p45c3nt characters < ai_playerbot_guild_names.sql
mysql -u root -p45c3nt characters < characters_ai_playerbot_custom_strategy.sql
mysql -u root -p45c3nt characters < characters_ai_playerbot_speech.sql
mysql -u root -p45c3nt characters < characters_ai_playerbot_locks.sql
cd ..
echo "[LegacyTrinityCore]"
cd ./LegacyTrinityCore
echo "Applying Legacy ARAC world playercreateinfo starting locations changes..."
mysql -u root -p45c3nt world < ARAC-world-playercreateinfo.sql
echo "Applying Legacy MinionBots updates..."
mysql -u root -p45c3nt world < Minions-world-creature_template_outfits.sql
mysql -u root -p45c3nt world < Minions-world-creature_template.sql
echo "Applying Legacy QOL (Quality of Life) achievement updates for every 10 levels..."
mysql -u root -p45c3nt world < QOL-world-achievement_reward.sql
mysql -u root -p45c3nt world < QOL-world-item_loot_template.sql
mysql -u root -p45c3nt world < QOL-world-item_template.sql
mysql -u root -p45c3nt world < QOL-world-creature_template.sql
cd ..
echo "------- ALL DONE! --------"