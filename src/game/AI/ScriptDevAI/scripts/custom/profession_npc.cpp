#include "AI/ScriptDevAI/include/sc_common.h"
#include "Globals/ObjectMgr.h"
#include "World/World.h"
#include "Chat/Chat.h"

#define GOSSIP_SENDER_SUB   50

void LearnSkillRecipesHelper(Player* player, uint32 skill_id)
{
    uint32 classmask = player->getClassMask();

    for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
    {
        SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
        if (!skillLine)
            continue;

        // wrong skill
        if (skillLine->skillId != skill_id)
            continue;

        // not high rank
        if (skillLine->forward_spellid)
            continue;

        // skip racial skills
        if (skillLine->racemask != 0)
            continue;

        // skip wrong class skills
        if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
            continue;

        SpellEntry const* spellEntry = sSpellTemplate.LookupEntry<SpellEntry>(skillLine->spellId);
        if (!spellEntry || !SpellMgr::IsSpellValid(spellEntry, player, false))
            continue;

        player->learnSpell(skillLine->spellId, false);
    }
}
bool LearnAllRecipesInProfession(Player* pPlayer, SkillType skill)
{
    ChatHandler handler(pPlayer->GetSession());
    char* skill_name;

    SkillLineEntry const* SkillInfo = sSkillLineStore.LookupEntry(skill);
    skill_name = SkillInfo->name[sWorld.GetDefaultDbcLocale()];

    if (!SkillInfo)
    {
        sLog.outError("Profession NPC: received non-valid skill ID");
        return false;
    }

    pPlayer->SetSkill(SkillInfo->id, 375, 375);
    LearnSkillRecipesHelper(pPlayer, SkillInfo->id);
    pPlayer->GetSession()->SendNotification("All recipes for %s learned", skill_name);
    return true;
}

void CompleteLearnProfession(Player* pPlayer, Creature* pCreature, SkillType skill)
{
    if (pPlayer->GetFreePrimaryProfessionPoints() == 0 && !(skill == SKILL_COOKING || skill == SKILL_FIRST_AID))
    {
        pPlayer->GetSession()->SendNotification("You already know two primary professions.");
    }
    else
    {
        if (!LearnAllRecipesInProfession(pPlayer, skill))
            pPlayer->GetSession()->SendNotification("Internal error.");
    }
}

bool GossipHello_ProfessionNPC(Player* player, Creature* creature)
{
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Alchemy", GOSSIP_SENDER_MAIN, 1);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Blacksmithing", GOSSIP_SENDER_MAIN, 2);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Leatherworking", GOSSIP_SENDER_MAIN, 3);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Tailoring", GOSSIP_SENDER_MAIN, 4);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Engineering", GOSSIP_SENDER_MAIN, 5);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Enchanting", GOSSIP_SENDER_MAIN, 6);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Jewelcrafting", GOSSIP_SENDER_MAIN, 7);
    //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Inscription", GOSSIP_SENDER_MAIN, 8);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Herbalism", GOSSIP_SENDER_MAIN, 9);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Skinning", GOSSIP_SENDER_MAIN, 10);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Mining", GOSSIP_SENDER_MAIN, 11);

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "First Aid", GOSSIP_SENDER_MAIN, 12);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Fishing", GOSSIP_SENDER_MAIN, 13);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Cooking", GOSSIP_SENDER_MAIN, 14);

    player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
    return true;
}

bool GossipSendMainMenu_ProfessionNPC(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    switch (action)
    {
    case 1:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Alchemy", GOSSIP_SENDER_SUB, 101);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Alchemy", GOSSIP_SENDER_SUB, 102);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 2:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Blacksmithing", GOSSIP_SENDER_SUB, 201);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Blacksmithing", GOSSIP_SENDER_SUB, 202);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 3:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Leatherworking", GOSSIP_SENDER_SUB, 301);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Leatherworking", GOSSIP_SENDER_SUB, 302);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 4:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Tailoring", GOSSIP_SENDER_SUB, 401);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Tailoring", GOSSIP_SENDER_SUB, 402);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 5:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Engineering", GOSSIP_SENDER_SUB, 501);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Engineering", GOSSIP_SENDER_SUB, 502);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 6:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Enchanting", GOSSIP_SENDER_SUB, 601);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Enchanting", GOSSIP_SENDER_SUB, 602);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 7:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Jewelcrafting", GOSSIP_SENDER_SUB, 701);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Jewelcrafting", GOSSIP_SENDER_SUB, 702);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 8:
        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Inscription", GOSSIP_SENDER_SUB, 801);
        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Inscription", GOSSIP_SENDER_SUB, 802);
        //player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 9:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Herbalism", GOSSIP_SENDER_SUB, 901);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Herbalism", GOSSIP_SENDER_SUB, 902);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 10:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Skinning", GOSSIP_SENDER_SUB, 1001);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Skinning", GOSSIP_SENDER_SUB, 1002);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 11:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Mining", GOSSIP_SENDER_SUB, 1101);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Mining", GOSSIP_SENDER_SUB, 1102);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 12:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn First Aid", GOSSIP_SENDER_SUB, 1201);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn First Aid", GOSSIP_SENDER_SUB, 1202);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 13:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Fishing", GOSSIP_SENDER_SUB, 1301);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Fishing", GOSSIP_SENDER_SUB, 1302);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    case 14:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Learn Cooking", GOSSIP_SENDER_SUB, 1401);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Unlearn Cooking", GOSSIP_SENDER_SUB, 1402);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetObjectGuid());
        break;
    }
    return true;
}

bool GossipSendSubMenu_ProfessionNPC(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    switch (action)
    {
    case 101:
        if (!player->HasSkill(SKILL_ALCHEMY))
        {
            player->CastSpell(player, 28597, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_ALCHEMY);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 102:
        player->removeSpell(28596);
        player->removeSpell(11611);
        player->removeSpell(3464);
        player->removeSpell(3101);
        player->removeSpell(2259);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 201:
        if (!player->HasSkill(SKILL_BLACKSMITHING))
        {
            player->CastSpell(player, 29845, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_BLACKSMITHING);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 202:
        player->removeSpell(29844);
        player->removeSpell(9785);
        player->removeSpell(3538);
        player->removeSpell(3100);
        player->removeSpell(2018);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 301:
        if (!player->HasSkill(SKILL_LEATHERWORKING))
        {
            player->CastSpell(player, 32550, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_LEATHERWORKING);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 302:
        player->removeSpell(32549);
        player->removeSpell(10662);
        player->removeSpell(3811);
        player->removeSpell(3104);
        player->removeSpell(2108);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 401:
        if (!player->HasSkill(SKILL_TAILORING))
        {
            player->CastSpell(player, 26791, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_TAILORING);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 402:
        player->removeSpell(26790);
        player->removeSpell(12180);
        player->removeSpell(3910);
        player->removeSpell(3909);
        player->removeSpell(3908);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 501:
        if (!player->HasSkill(SKILL_ENGINEERING))
        {
            player->CastSpell(player, 30351, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_ENGINEERING);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 502:
        player->removeSpell(30350);
        player->removeSpell(12656);
        player->removeSpell(4038);
        player->removeSpell(4037);
        player->removeSpell(4036);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 601:
        if (!player->HasSkill(SKILL_ENCHANTING))
        {
            player->CastSpell(player, 28030, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_ENCHANTING);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 602:
        player->removeSpell(28029);
        player->removeSpell(13920);
        player->removeSpell(13262);
        player->removeSpell(7413);
        player->removeSpell(7412);
        player->removeSpell(7411);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 701:
        if (!player->HasSkill(SKILL_JEWELCRAFTING))
        {
            player->CastSpell(player, 28901, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_JEWELCRAFTING);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 702:
        player->removeSpell(31252);
        player->removeSpell(28897);
        player->removeSpell(28895);
        player->removeSpell(28894);
        player->removeSpell(25230);
        player->removeSpell(25229);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 901:
        if (!player->HasSkill(SKILL_HERBALISM))
        {
            player->CastSpell(player, 28696, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_HERBALISM);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 902:
        player->removeSpell(28695);
        player->removeSpell(11993);
        player->removeSpell(3570);
        player->removeSpell(2368);
        player->removeSpell(2366);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 1001:
        if (!player->HasSkill(SKILL_SKINNING))
        {
            player->CastSpell(player, 32679, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_SKINNING);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 1002:
        player->removeSpell(32678);
        player->removeSpell(10768);
        player->removeSpell(8618);
        player->removeSpell(8617);
        player->removeSpell(8613);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 1101:
        if (!player->HasSkill(SKILL_MINING))
        {
            player->CastSpell(player, 23955, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_MINING);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 1102:
        player->removeSpell(29354);
        player->removeSpell(10248);
        player->removeSpell(3564);
        player->removeSpell(2576);
        player->removeSpell(2575);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 1201:
        if (!player->HasSkill(SKILL_FIRST_AID))
        {
            player->CastSpell(player, 33894, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_FIRST_AID);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 1202:
        player->removeSpell(27028);
        player->removeSpell(10846);
        player->removeSpell(7924);
        player->removeSpell(3274);
        player->removeSpell(3273);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 1301:
        if (!player->HasSkill(SKILL_FISHING))
        {
            player->CastSpell(player, 33098, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_FISHING);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 1302:
        player->removeSpell(43308);
        player->removeSpell(33095);
        player->removeSpell(18248);
        player->removeSpell(7732);
        player->removeSpell(7731);
        player->removeSpell(7620);
        player->CLOSE_GOSSIP_MENU();
        break;

    case 1401:
        if (!player->HasSkill(SKILL_COOKING))
        {
            player->CastSpell(player, 33360, TRIGGERED_OLD_TRIGGERED);
            LearnAllRecipesInProfession(player, SKILL_COOKING);
            player->CLOSE_GOSSIP_MENU();
        }
        break;

    case 1402:
        player->removeSpell(51296);
        player->removeSpell(33359);
        player->removeSpell(18260);
        player->removeSpell(3413);
        player->removeSpell(3102);
        player->removeSpell(2550);
        player->CLOSE_GOSSIP_MENU();
        break;
    }
    return true;
}

bool GossipSelect_ProfessionNPC(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    switch (sender)
    {
    case GOSSIP_SENDER_MAIN:
        GossipSendMainMenu_ProfessionNPC(player, creature, sender, action);
        break;
    case GOSSIP_SENDER_SUB:
        GossipSendSubMenu_ProfessionNPC(player, creature, sender, action);
        break;
    }
    return true;
}

void AddSC_profession_npc()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "custom_professions_npc";
    pNewScript->pGossipHello = &GossipHello_ProfessionNPC;
    pNewScript->pGossipSelect = &GossipSelect_ProfessionNPC;
    pNewScript->RegisterSelf();
}