#include "AI/ScriptDevAI/include/sc_common.h"
#include "Globals/ObjectMgr.h"
#include "World/World.h"
#include "Chat/Chat.h"
#include "Spells/Spell.h"

#define SPELL_POLEARM 200
#define SPELL_OH_SWORD 201
#define SPELL_BOWS 264
#define SPELL_STAVES 227
#define SPELL_2H_AXES 197
#define SPELL_OH_MACES 198
#define SPELL_DAGGERS 1180
#define SPELL_GUNS 266
#define SPELL_OH_AXES 196
#define SPELL_2H_MACES 199
#define SPELL_2H_SWORD 202
#define SPELL_THROWN 2567
#define SPELL_CROSSBOW 5011
#define SPELL_FIST 15590

bool GossipHello_SkillNPC(Player* player, Creature* creature)
{
	uint32 playerClass = player->getClass();
	
	if (playerClass == 1) //Warrior
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to learn all my warrior skills!", GOSSIP_SENDER_MAIN, 101);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to max all my warrior skills!", GOSSIP_SENDER_MAIN, 102);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Close", GOSSIP_SENDER_MAIN, 1001);
	}
	else if (playerClass == 2)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to learn all my paladin skills!", GOSSIP_SENDER_MAIN, 201);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to max all my paladin skills!", GOSSIP_SENDER_MAIN, 202);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Close", GOSSIP_SENDER_MAIN, 1001);
	}
	else if (playerClass == 3)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to learn all my hunter skills!", GOSSIP_SENDER_MAIN, 301);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to max all my hunter skills!", GOSSIP_SENDER_MAIN, 302);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Close", GOSSIP_SENDER_MAIN, 1001);
	}
	else if (playerClass == 4)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to learn all my rogue skills!", GOSSIP_SENDER_MAIN, 401);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to max all my rogue skills!", GOSSIP_SENDER_MAIN, 402);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Close", GOSSIP_SENDER_MAIN, 1001);
	}
	else if (playerClass == 5)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to learn all my priest skills!", GOSSIP_SENDER_MAIN, 501);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to max all my priest skills!", GOSSIP_SENDER_MAIN, 502);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Close", GOSSIP_SENDER_MAIN, 1001);
	}
	else if (playerClass == 7)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to learn all my shaman skills!", GOSSIP_SENDER_MAIN, 701);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to max all my shaman skills!", GOSSIP_SENDER_MAIN, 702);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Close", GOSSIP_SENDER_MAIN, 1001);
	}
	else if (playerClass == 8)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to learn all my mage skills!", GOSSIP_SENDER_MAIN, 801);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to max all my mage skills!", GOSSIP_SENDER_MAIN, 802);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Close", GOSSIP_SENDER_MAIN, 1001);
	}
	else if (playerClass == 9)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to learn all my warlock skills!", GOSSIP_SENDER_MAIN, 901);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to max all my warlock skills!", GOSSIP_SENDER_MAIN, 902);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Close", GOSSIP_SENDER_MAIN, 1001);
	}
	else if (playerClass == 11)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to learn all my druid skills!", GOSSIP_SENDER_MAIN, 1101);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I wish to max all my druid skills!", GOSSIP_SENDER_MAIN, 1102);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Close", GOSSIP_SENDER_MAIN, 1001);
	}
	else
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "I don't know what you are", GOSSIP_SENDER_MAIN, 1000);
	}
	player->GetPlayerMenu()->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
	return true;
}

bool GossipSelect_SkillNPC(Player* player, Creature* creature, uint32 sender, uint32 action)
{
	uint16 maxOHSwordsLevel = player->GetSkillMaxPure(SKILL_SWORDS);
	uint16 maxDaggersLevel = player->GetSkillMaxPure(SKILL_DAGGERS);
	uint16 maxDefenseLevel = player->GetSkillMaxPure(SKILL_DEFENSE);
	uint16 maxUnarmedLevel = player->GetSkillMaxPure(SKILL_UNARMED);
	uint16 maxWandsLevel = player->GetSkillMaxPure(SKILL_WANDS);
	uint16 maxStavesLevel = player->GetSkillMaxPure(SKILL_STAVES);
	uint16 maxPolearmsLevel = player->GetSkillMaxPure(SKILL_POLEARMS);
	uint16 maxBowsLevel = player->GetSkillMaxPure(SKILL_BOWS);
	uint16 max2HAxesLevel = player->GetSkillMaxPure(SKILL_2H_AXES);
	uint16 maxOHMacesLevel = player->GetSkillMaxPure(SKILL_MACES);
	uint16 maxGunsLevel = player->GetSkillMaxPure(SKILL_GUNS);
	uint16 maxOHAxesLevel = player->GetSkillMaxPure(SKILL_AXES);
	uint16 max2HMacesLevel = player->GetSkillMaxPure(SKILL_2H_MACES);
	uint16 max2HSwordsLevel = player->GetSkillMaxPure(SKILL_2H_SWORDS);
	uint16 maxThrownLevel = player->GetSkillMaxPure(SKILL_THROWN);
	uint16 maxCrossbowsLevel = player->GetSkillMaxPure(SKILL_CROSSBOWS);
	uint16 maxFistLevel = player->GetSkillMaxPure(SKILL_FIST_WEAPONS);

	uint32 playerRace = player->getRace();

	switch (action)
	{
	case 101:
		player->learnSpell(SPELL_BOWS, false);
		player->learnSpell(SPELL_CROSSBOW, false);
		player->learnSpell(SPELL_FIST, false);
		player->learnSpell(SPELL_STAVES, false);
		player->learnSpell(SPELL_GUNS, false);
		player->learnSpell(SPELL_POLEARM, false);
		player->learnSpell(355, false);
		player->learnSpell(7386, false);
		if (playerRace == 2) //Orc
		{
			player->learnSpell(SPELL_DAGGERS, false);
			player->learnSpell(SPELL_OH_MACES, false);
			player->learnSpell(SPELL_THROWN, false);
			player->learnSpell(SPELL_2H_MACES, false);
			player->learnSpell(SPELL_2H_SWORD, false);
		}
		else if (playerRace == 5) //Undead
		{
			player->learnSpell(SPELL_OH_AXES, false);
			player->learnSpell(SPELL_THROWN, false);
			player->learnSpell(SPELL_2H_AXES, false);
			player->learnSpell(SPELL_2H_MACES, false);
			player->learnSpell(SPELL_OH_MACES, false);
		}
		else if (playerRace == 6) //Tauren
		{
			player->learnSpell(SPELL_DAGGERS, false);
			player->learnSpell(SPELL_OH_SWORD, false);
			player->learnSpell(SPELL_THROWN, false);
			player->learnSpell(SPELL_2H_AXES, false);
			player->learnSpell(SPELL_2H_SWORD, false);
		}
		else if (playerRace == 8) //Troll
		{
			player->learnSpell(SPELL_OH_MACES, false);
			player->learnSpell(SPELL_OH_SWORD, false);
			player->learnSpell(SPELL_2H_AXES, false);
			player->learnSpell(SPELL_2H_MACES, false);
			player->learnSpell(SPELL_2H_SWORD, false);
		}
		player->GetSession()->SendNotification("You learned all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 102:
		player->SetSkill(SKILL_SWORDS, maxOHSwordsLevel, maxOHSwordsLevel);
		player->SetSkill(SKILL_2H_SWORDS, max2HSwordsLevel, max2HSwordsLevel);
		player->SetSkill(SKILL_DAGGERS, maxDaggersLevel, maxDaggersLevel);
		player->SetSkill(SKILL_STAVES, maxStavesLevel, maxStavesLevel);
		player->SetSkill(SKILL_AXES, maxOHAxesLevel, maxOHAxesLevel);
		player->SetSkill(SKILL_BOWS, maxBowsLevel, maxBowsLevel);
		player->SetSkill(SKILL_FIST_WEAPONS, maxFistLevel, maxFistLevel);
		player->SetSkill(SKILL_THROWN, maxThrownLevel, maxThrownLevel);
		player->SetSkill(SKILL_2H_AXES, max2HAxesLevel, max2HAxesLevel);
		player->SetSkill(SKILL_CROSSBOWS, maxCrossbowsLevel, maxCrossbowsLevel);
		player->SetSkill(SKILL_GUNS, maxGunsLevel, maxGunsLevel);
		player->SetSkill(SKILL_2H_MACES, max2HMacesLevel, max2HMacesLevel);
		player->SetSkill(SKILL_MACES, maxOHMacesLevel, maxOHMacesLevel);
		player->SetSkill(SKILL_POLEARMS, maxPolearmsLevel, maxPolearmsLevel);
		player->SetSkill(SKILL_DEFENSE, maxDefenseLevel, maxDefenseLevel);
		player->SetSkill(SKILL_UNARMED, maxUnarmedLevel, maxUnarmedLevel);
		player->GetSession()->SendNotification("You maxed all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 201:
		if (playerRace == 10) //Blood Elf
		{
			player->learnSpell(SPELL_POLEARM, false);
			player->learnSpell(SPELL_OH_AXES, false);
			player->learnSpell(SPELL_2H_AXES, false);
			player->learnSpell(SPELL_OH_MACES, false);
			player->learnSpell(SPELL_2H_MACES, false);
		}
		player->GetSession()->SendNotification("You learned all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 202:
		player->SetSkill(SKILL_SWORDS, maxOHSwordsLevel, maxOHSwordsLevel);
		player->SetSkill(SKILL_2H_SWORDS, max2HSwordsLevel, max2HSwordsLevel);
		player->SetSkill(SKILL_AXES, maxOHAxesLevel, maxOHAxesLevel);
		player->SetSkill(SKILL_2H_AXES, max2HAxesLevel, max2HAxesLevel);
		player->SetSkill(SKILL_2H_MACES, max2HMacesLevel, max2HMacesLevel);
		player->SetSkill(SKILL_MACES, maxOHMacesLevel, maxOHMacesLevel);
		player->SetSkill(SKILL_POLEARMS, maxPolearmsLevel, maxPolearmsLevel);
		player->SetSkill(SKILL_DEFENSE, maxDefenseLevel, maxDefenseLevel);
		player->SetSkill(SKILL_UNARMED, maxUnarmedLevel, maxUnarmedLevel);
		player->GetSession()->SendNotification("You maxed all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 301:
		player->learnSpell(SPELL_CROSSBOW, false);
		player->learnSpell(SPELL_FIST, false);
		player->learnSpell(SPELL_OH_SWORD, false);
		player->learnSpell(SPELL_POLEARM, false);
		player->learnSpell(SPELL_STAVES, false);
		player->learnSpell(SPELL_THROWN, false);
		player->learnSpell(SPELL_2H_AXES, false);
		player->learnSpell(SPELL_2H_SWORD, false);
		if (playerRace == 2 || playerRace == 8)
		{
			player->learnSpell(SPELL_DAGGERS, false);
			player->learnSpell(SPELL_GUNS, false);
		}
		else if (playerRace == 6)
		{
			player->learnSpell(SPELL_BOWS, false);
			player->learnSpell(SPELL_DAGGERS, false);
		}
		else if (playerRace == 10)
		{
			player->learnSpell(SPELL_OH_AXES, false);
			player->learnSpell(SPELL_GUNS, false);
		}
		player->GetSession()->SendNotification("You learned all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 302:
		player->SetSkill(SKILL_SWORDS, maxOHSwordsLevel, maxOHSwordsLevel);
		player->SetSkill(SKILL_2H_SWORDS, max2HSwordsLevel, max2HSwordsLevel);
		player->SetSkill(SKILL_DAGGERS, maxDaggersLevel, maxDaggersLevel);
		player->SetSkill(SKILL_STAVES, maxStavesLevel, maxStavesLevel);
		player->SetSkill(SKILL_AXES, maxOHAxesLevel, maxOHAxesLevel);
		player->SetSkill(SKILL_BOWS, maxBowsLevel, maxBowsLevel);
		player->SetSkill(SKILL_FIST_WEAPONS, maxFistLevel, maxFistLevel);
		player->SetSkill(SKILL_THROWN, maxThrownLevel, maxThrownLevel);
		player->SetSkill(SKILL_2H_AXES, max2HAxesLevel, max2HAxesLevel);
		player->SetSkill(SKILL_CROSSBOWS, maxCrossbowsLevel, maxCrossbowsLevel);
		player->SetSkill(SKILL_GUNS, maxGunsLevel, maxGunsLevel);
		player->SetSkill(SKILL_POLEARMS, maxPolearmsLevel, maxPolearmsLevel);
		player->SetSkill(SKILL_DEFENSE, maxDefenseLevel, maxDefenseLevel);
		player->SetSkill(SKILL_UNARMED, maxUnarmedLevel, maxUnarmedLevel);
		player->GetSession()->SendNotification("You maxed all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 401:
		player->learnSpell(SPELL_BOWS, false);
		player->learnSpell(SPELL_FIST, false);
		player->learnSpell(SPELL_OH_SWORD, false);
		player->learnSpell(SPELL_CROSSBOW, false);
		player->learnSpell(SPELL_GUNS, false);
		player->learnSpell(SPELL_OH_MACES, false);
		player->GetSession()->SendNotification("You learned all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 402:
		player->SetSkill(SKILL_SWORDS, maxOHSwordsLevel, maxOHSwordsLevel);
		player->SetSkill(SKILL_DAGGERS, maxDaggersLevel, maxDaggersLevel);
		player->SetSkill(SKILL_MACES, maxOHMacesLevel, maxOHMacesLevel);
		player->SetSkill(SKILL_BOWS, maxBowsLevel, maxBowsLevel);
		player->SetSkill(SKILL_FIST_WEAPONS, maxFistLevel, maxFistLevel);
		player->SetSkill(SKILL_THROWN, maxThrownLevel, maxThrownLevel);
		player->SetSkill(SKILL_CROSSBOWS, maxCrossbowsLevel, maxCrossbowsLevel);
		player->SetSkill(SKILL_GUNS, maxGunsLevel, maxGunsLevel);
		player->SetSkill(SKILL_DEFENSE, maxDefenseLevel, maxDefenseLevel);
		player->SetSkill(SKILL_UNARMED, maxUnarmedLevel, maxUnarmedLevel);
		player->GetSession()->SendNotification("You maxed all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 501:
		player->learnSpell(SPELL_STAVES, false);
		player->learnSpell(SPELL_DAGGERS, false);
		player->GetSession()->SendNotification("You learned all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 502:
		player->SetSkill(SKILL_MACES, maxOHMacesLevel, maxOHMacesLevel);
		player->SetSkill(SKILL_DAGGERS, maxDaggersLevel, maxDaggersLevel);
		player->SetSkill(SKILL_DEFENSE, maxDefenseLevel, maxDefenseLevel);
		player->SetSkill(SKILL_UNARMED, maxUnarmedLevel, maxUnarmedLevel);
		player->SetSkill(SKILL_WANDS, maxWandsLevel, maxWandsLevel);
		player->SetSkill(SKILL_STAVES, maxStavesLevel, maxStavesLevel);
		player->GetSession()->SendNotification("You maxed all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 701: //Shaman
		player->learnSpell(SPELL_OH_AXES, false);
		player->learnSpell(SPELL_DAGGERS, false);
		player->learnSpell(SPELL_FIST, false);
		player->StoreNewItemInInventorySlot(5175, 1);
		player->StoreNewItemInInventorySlot(5176, 1);
		player->StoreNewItemInInventorySlot(5177, 1);
		player->StoreNewItemInInventorySlot(5178, 1);
		player->GetSession()->SendNotification("You learned all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 702:
		player->SetSkill(SKILL_MACES, maxOHMacesLevel, maxOHMacesLevel);
		player->SetSkill(SKILL_DAGGERS, maxDaggersLevel, maxDaggersLevel);
		player->SetSkill(SKILL_DEFENSE, maxDefenseLevel, maxDefenseLevel);
		player->SetSkill(SKILL_UNARMED, maxUnarmedLevel, maxUnarmedLevel);
		player->SetSkill(SKILL_AXES, maxOHAxesLevel, maxOHAxesLevel);
		player->SetSkill(SKILL_FIST_WEAPONS, maxFistLevel, maxFistLevel);
		player->SetSkill(SKILL_STAVES, maxStavesLevel, maxStavesLevel);
		player->GetSession()->SendNotification("You maxed all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 801:
		player->learnSpell(SPELL_OH_SWORD,false);
		player->learnSpell(SPELL_DAGGERS, false);
		player->GetSession()->SendNotification("You learned all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 802:
		player->SetSkill(SKILL_SWORDS, maxOHSwordsLevel, maxOHSwordsLevel);
		player->SetSkill(SKILL_DAGGERS, maxDaggersLevel, maxDaggersLevel);
		player->SetSkill(SKILL_DEFENSE, maxDefenseLevel, maxDefenseLevel);
		player->SetSkill(SKILL_UNARMED, maxUnarmedLevel, maxUnarmedLevel);
		player->SetSkill(SKILL_WANDS, maxWandsLevel, maxWandsLevel);
		player->SetSkill(SKILL_STAVES, maxStavesLevel, maxStavesLevel);
		player->GetSession()->SendNotification("You maxed all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 901:
		player->learnSpell(SPELL_OH_SWORD, false);
		player->learnSpell(SPELL_STAVES, false);
		player->GetSession()->SendNotification("You learned all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 902:
		player->SetSkill(SKILL_SWORDS, maxOHSwordsLevel, maxOHSwordsLevel);
		player->SetSkill(SKILL_DAGGERS, maxDaggersLevel, maxDaggersLevel);
		player->SetSkill(SKILL_DEFENSE, maxDefenseLevel, maxDefenseLevel);
		player->SetSkill(SKILL_UNARMED, maxUnarmedLevel, maxUnarmedLevel);
		player->SetSkill(SKILL_WANDS, maxWandsLevel, maxWandsLevel);
		player->SetSkill(SKILL_STAVES, maxStavesLevel, maxStavesLevel);
		player->GetSession()->SendNotification("You maxed all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 1101:
		player->learnSpell(SPELL_FIST, false);
		player->learnSpell(SPELL_2H_MACES, false);
		if (playerRace == 4) //Night Elf
		{
			player->learnSpell(SPELL_OH_MACES, false);
		}
		if (playerRace == 6) //Tauren
		{
			player->learnSpell(SPELL_DAGGERS, false);
		}
		player->GetSession()->SendNotification("You learned all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 1102:
		player->SetSkill(SKILL_FIST_WEAPONS, maxFistLevel, maxFistLevel);
		player->SetSkill(SKILL_2H_MACES, max2HMacesLevel, max2HMacesLevel);
		player->SetSkill(SKILL_DAGGERS, maxDaggersLevel, maxDaggersLevel);
		player->SetSkill(SKILL_STAVES, maxStavesLevel, maxStavesLevel);
		player->SetSkill(SKILL_MACES, maxOHMacesLevel, maxOHMacesLevel);
		player->SetSkill(SKILL_DEFENSE, maxDefenseLevel, maxDefenseLevel);
		player->SetSkill(SKILL_UNARMED, maxUnarmedLevel, maxUnarmedLevel);		
		player->GetSession()->SendNotification("You maxed all skills.");
		player->CLOSE_GOSSIP_MENU();
		break;

	case 1000:
		player->GetSession()->SendNotification("I can't teach you!");
		player->GetPlayerMenu()->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
		break;

	case 1001:
		player->CLOSE_GOSSIP_MENU();
		break;
	}
	return true;
}

void AddSC_skill_npc()
{
	Script* pNewScript = new Script;
	pNewScript->Name = "custom_skill_npc";
	pNewScript->pGossipHello = &GossipHello_SkillNPC;
	pNewScript->pGossipSelect = &GossipSelect_SkillNPC;
	pNewScript->RegisterSelf();
}