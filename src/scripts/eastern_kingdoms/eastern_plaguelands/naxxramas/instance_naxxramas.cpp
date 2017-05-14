/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Instance_Naxxramas
SD%Complete: 90%
SDComment:
SDCategory: Naxxramas
EndScriptData */

#include "scriptPCH.h"
#include "naxxramas.h"

instance_naxxramas::instance_naxxramas(Map* pMap) : ScriptedInstance(pMap),
    m_faerlinaHaveGreeted(false),


    m_uiAracEyeRampGUID(0),
    m_uiPlagEyeRampGUID(0),
    m_uiMiliEyeRampGUID(0),
    m_uiConsEyeRampGUID(0),

    m_uiAracPortalGUID(0),
    m_uiPlagPortalGUID(0),
    m_uiMiliPortalGUID(0),
    m_uiConsPortalGUID(0),

    m_uiAnubRekhanGUID(0),
    m_uiFaerlinanGUID(0),

    m_uiZeliekGUID(0),
    m_uiThaneGUID(0),
    m_uiBlaumeuxGUID(0),
    m_uiRivendareGUID(0),

    m_uiThaddiusGUID(0),
    m_uiStalaggGUID(0),
    m_uiFeugenGUID(0),

    m_uiPathExitDoorGUID(0),
    m_uiGlutExitDoorGUID(0),
    m_uiThadDoorGUID(0),

    m_uiAnubDoorGUID(0),
    m_uiAnubGateGUID(0),
    m_uiFaerDoorGUID(0),
    m_uiFaerWebGUID(0),
    m_uiMaexOuterGUID(0),
    m_uiMaexInnerGUID(0),

    m_uiGothikGUID(0),
    m_uiGothCombatGateGUID(0),
    m_uiGothikEntryDoorGUID(0),
    m_uiGothikExitDoorGUID(0),
    m_uiHorsemenDoorGUID(0),
    m_uiHorsemenChestGUID(0),

    m_uiNothEntryDoorGUID(0),
    m_uiNothExitDoorGUID(0),
    m_uiHeigEntryDoorGUID(0),
    m_uiHeigExitDoorGUID(0),
    m_uiLoathebDoorGUID(0),

    m_uiKelthuzadDoorGUID(0),
    m_fChamberCenterX(0.0f),
    m_fChamberCenterY(0.0f),
    m_fChamberCenterZ(0.0f)
{
    Initialize();
}

void instance_naxxramas::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
}

void instance_naxxramas::OnCreatureCreate(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_ANUB_REKHAN:
            m_uiAnubRekhanGUID = pCreature->GetGUID();
            break;
        case NPC_FAERLINA:
            m_uiFaerlinanGUID = pCreature->GetGUID();
            break;
        case NPC_THADDIUS:
            m_uiThaddiusGUID = pCreature->GetGUID();
            break;
        case NPC_STALAGG:
            m_uiStalaggGUID = pCreature->GetGUID();
            break;
        case NPC_FEUGEN:
            m_uiFeugenGUID = pCreature->GetGUID();
            break;
        case NPC_ZELIEK:
            m_uiZeliekGUID = pCreature->GetGUID();
            break;
        case NPC_THANE:
            m_uiThaneGUID = pCreature->GetGUID();
            break;
        case NPC_BLAUMEUX:
            m_uiBlaumeuxGUID = pCreature->GetGUID();
            break;
        case NPC_RIVENDARE:
            m_uiRivendareGUID = pCreature->GetGUID();
            break;
        case NPC_GOTHIK:
            m_uiGothikGUID = pCreature->GetGUID();
            break;
        case NPC_SUB_BOSS_TRIGGER:
            m_lGothTriggerList.push_back(pCreature->GetGUID());
            break;
    }
}

void instance_naxxramas::OnObjectCreate(GameObject* pGo)
{
    switch (pGo->GetEntry())
    {
        case GO_ARAC_ANUB_DOOR:
            m_uiAnubDoorGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_ANUB_REKHAN] == DONE)
            {
                pGo->SetGoState(GO_STATE_ACTIVE);
                pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
            }
            else
            {
                pGo->SetGoState(GO_STATE_READY);
                pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
            }
            break;
        case GO_ARAC_ANUB_GATE:
            m_uiAnubGateGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_ANUB_REKHAN] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            else
                pGo->SetGoState(GO_STATE_READY);
            break;
        case GO_ARAC_FAER_WEB:
            m_uiFaerWebGUID = pGo->GetGUID();
            pGo->SetGoState(GO_STATE_ACTIVE);
            //PreMapAddOpenDoor(pGo);
            break;
        case GO_ARAC_FAER_DOOR:
            m_uiFaerDoorGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_FAERLINA] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            else
                pGo->SetGoState(GO_STATE_READY);
            break;
        case GO_ARAC_MAEX_INNER_DOOR:
            m_uiMaexInnerGUID = pGo->GetGUID();
            break;
        case GO_ARAC_MAEX_OUTER_DOOR:
            m_uiMaexOuterGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_FAERLINA] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_PLAG_NOTH_ENTRY_DOOR:
            m_uiNothEntryDoorGUID = pGo->GetGUID();
            break;
        case GO_PLAG_NOTH_EXIT_DOOR:
            m_uiNothExitDoorGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_NOTH] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_PLAG_HEIG_ENTRY_DOOR:
            m_uiHeigEntryDoorGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_NOTH] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_PLAG_HEIG_EXIT_DOOR:
            m_uiHeigExitDoorGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_HEIGAN] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_PLAG_LOAT_DOOR:
            m_uiLoathebDoorGUID = pGo->GetGUID();
            break;

        case GO_MILI_GOTH_ENTRY_GATE:
            m_uiGothikEntryDoorGUID = pGo->GetGUID();
            break;
        case GO_MILI_GOTH_EXIT_GATE:
            m_uiGothikExitDoorGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_GOTHIK] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_MILI_GOTH_COMBAT_GATE:
            m_uiGothCombatGateGUID = pGo->GetGUID();
            break;
        case GO_MILI_HORSEMEN_DOOR:
            m_uiHorsemenDoorGUID  = pGo->GetGUID();
            if (m_auiEncounter[TYPE_GOTHIK] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        case GO_CHEST_HORSEMEN_NORM:
            m_uiHorsemenChestGUID = pGo->GetGUID();
            break;

        case GO_CONS_PATH_EXIT_DOOR:
            m_uiPathExitDoorGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_PATCHWERK] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_CONS_GLUT_EXIT_DOOR:
            m_uiGlutExitDoorGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_GLUTH] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_CONS_THAD_DOOR:
            m_uiThadDoorGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_GLUTH] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        case GO_KELTHUZAD_WATERFALL_DOOR:
            m_uiKelthuzadDoorGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_SAPPHIRON] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        case GO_ARAC_EYE_RAMP:
            m_uiAracEyeRampGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_MAEXXNA] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_PLAG_EYE_RAMP:
            m_uiPlagEyeRampGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_LOATHEB] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_MILI_EYE_RAMP:
            m_uiMiliEyeRampGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_FOUR_HORSEMEN] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_CONS_EYE_RAMP:
            m_uiConsEyeRampGUID = pGo->GetGUID();
            if (m_auiEncounter[TYPE_THADDIUS] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        case GO_ARAC_PORTAL:
            m_uiAracPortalGUID = pGo->GetGUID();
            break;
        case GO_PLAG_PORTAL:
            m_uiPlagPortalGUID = pGo->GetGUID();
            break;
        case GO_MILI_PORTAL:
            m_uiMiliPortalGUID = pGo->GetGUID();
            break;
        case GO_CONS_PORTAL:
            m_uiConsPortalGUID = pGo->GetGUID();
            break;
    }
}

bool instance_naxxramas::IsEncounterInProgress()
{
    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
        if (m_auiEncounter[i] == IN_PROGRESS)
            return true;

    return false;
}

void instance_naxxramas::SetData(uint32 uiType, uint32 uiData)
{
    ASSERT(this)

    switch (uiType)
    {
        case TYPE_ANUB_REKHAN:
            m_auiEncounter[uiType] = uiData;
            if (GameObject* pGo = GetGameObject(m_uiAnubDoorGUID))
            {
                switch (uiData)
                {
                case NOT_STARTED:
                    pGo->SetGoState(GO_STATE_READY);
                    pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
                    break;
                case IN_PROGRESS:
                    pGo->SetGoState(GO_STATE_READY);
                    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
                    break;
                case FAIL:
                case DONE:
                case SPECIAL:
                    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
                    pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                }
            }
            if (GameObject* pGo = GetGameObject(m_uiAnubGateGUID))
            {
                if(uiData == DONE)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                else
                    pGo->SetGoState(GO_STATE_READY);
            }
            break;
        case TYPE_FAERLINA:
            m_auiEncounter[uiType] = uiData;
            if (GameObject* pGo = GetGameObject(m_uiFaerWebGUID))
            {
                switch (uiData)
                {
                case NOT_STARTED:
                case FAIL:
                case DONE:
                case SPECIAL:
                    pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case IN_PROGRESS:
                    pGo->SetGoState(GO_STATE_READY);
                    break;
                }
            }
            if (uiData == DONE)
            {
                if (GameObject* pGo = GetGameObject(m_uiFaerDoorGUID))
                    pGo->SetGoState(GO_STATE_ACTIVE);
                if (GameObject* pGo = GetGameObject(m_uiMaexOuterGUID))
                    pGo->SetGoState(GO_STATE_ACTIVE);
            }
            else
            {
                if (GameObject* pGo = GetGameObject(m_uiFaerDoorGUID))
                    pGo->SetGoState(GO_STATE_READY);
                if (GameObject* pGo = GetGameObject(m_uiMaexOuterGUID))
                    pGo->SetGoState(GO_STATE_READY);
            }
            break;
        case TYPE_MAEXXNA:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiMaexInnerGUID, uiData);
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiAracEyeRampGUID);
                DoRespawnGameObject(m_uiAracPortalGUID, 30 * MINUTE);
            }
            break;
        case TYPE_NOTH:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiNothEntryDoorGUID);
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiNothExitDoorGUID);
                DoUseDoorOrButton(m_uiHeigEntryDoorGUID);
            }
            break;
        case TYPE_HEIGAN:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiHeigEntryDoorGUID);
            if (uiData == DONE)
                DoUseDoorOrButton(m_uiHeigExitDoorGUID);
            break;
        case TYPE_LOATHEB:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiLoathebDoorGUID);
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiPlagEyeRampGUID);
                DoRespawnGameObject(m_uiPlagPortalGUID, 30 * MINUTE);
            }
            break;
        case TYPE_RAZUVIOUS:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
                DoUseDoorOrButton(m_uiGothikEntryDoorGUID);
            break;
        case TYPE_GOTHIK:
            switch (uiData)
            {
                case IN_PROGRESS:
                    DoUseDoorOrButton(m_uiGothikEntryDoorGUID);
                    DoUseDoorOrButton(m_uiGothCombatGateGUID);
                    break;
                case SPECIAL:
                    DoUseDoorOrButton(m_uiGothCombatGateGUID);
                    break;
                case FAIL:
                    if (m_auiEncounter[TYPE_RAZUVIOUS] == IN_PROGRESS) // double check TYPE_RAZUVIOUS is correct. Was hard-coded to 7, which referred to TYPE_RAZUVIOUS
                        DoUseDoorOrButton(m_uiGothCombatGateGUID);

                    DoUseDoorOrButton(m_uiGothikEntryDoorGUID);
                    break;
                case DONE:
                    DoUseDoorOrButton(m_uiGothikEntryDoorGUID);
                    DoUseDoorOrButton(m_uiGothikExitDoorGUID);
                    DoUseDoorOrButton(m_uiHorsemenDoorGUID);
                    break;
            }
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_FOUR_HORSEMEN:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiHorsemenDoorGUID);
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiMiliEyeRampGUID);
                DoRespawnGameObject(m_uiMiliPortalGUID, 30 * MINUTE);
                DoRespawnGameObject(m_uiHorsemenChestGUID, 30 * MINUTE);
            }
            break;
        case TYPE_PATCHWERK:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
                DoUseDoorOrButton(m_uiPathExitDoorGUID);
            break;
        case TYPE_GROBBULUS:
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_GLUTH:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiGlutExitDoorGUID);
                DoUseDoorOrButton(m_uiThadDoorGUID);
            }
            break;
        case TYPE_THADDIUS:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiThadDoorGUID, uiData);
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiConsEyeRampGUID);
                DoRespawnGameObject(m_uiConsPortalGUID, 30 * MINUTE);
            }
            break;
        case TYPE_SAPPHIRON:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
                DoUseDoorOrButton(m_uiKelthuzadDoorGUID);
            break;
        case TYPE_KELTHUZAD:
            switch (uiData)
            {
                case SPECIAL:
                {
                    Map::PlayerList const& lPlayers = instance->GetPlayers();

                    if (lPlayers.isEmpty())
                        return;

                    bool bCanBegin = true;

                    for (Map::PlayerList::const_iterator itr = lPlayers.begin(); itr != lPlayers.end(); ++itr)
                    {
                        if (Player* pPlayer = itr->getSource())
                        {
                            if (!pPlayer->IsWithinDist2d(m_fChamberCenterX, m_fChamberCenterY, 15.0f))
                                bCanBegin = false;
                        }
                    }

                    if (bCanBegin)
                        m_auiEncounter[uiType] = IN_PROGRESS;

                    break;
                }
                case FAIL:
                    m_auiEncounter[uiType] = NOT_STARTED;
                    break;
                default:
                    m_auiEncounter[uiType] = uiData;
                    break;
            }
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        for (int i = 0; i < MAX_ENCOUNTER; ++i)
            saveStream << m_auiEncounter[i] << " ";

        strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_naxxramas::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    for (int i = 0; i < MAX_ENCOUNTER; ++i)
    {
        loadStream >> m_auiEncounter[i];
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

uint32 instance_naxxramas::GetData(uint32 uiType)
{
    if (uiType < MAX_ENCOUNTER)
        return m_auiEncounter[uiType];

    sLog.outError("instance_naxxramas::GetData() called with %d as param. %d is MAX_ENCOUNTERS", uiType, MAX_ENCOUNTER);
    return 0;
}

uint64 instance_naxxramas::GetData64(uint32 uiData)
{
    switch (uiData)
    {
        case GO_ARAC_ANUB_DOOR:
            return m_uiAnubDoorGUID;
        case NPC_ANUB_REKHAN:
            return m_uiAnubRekhanGUID;
        case NPC_FAERLINA:
            return m_uiFaerlinanGUID;
        case GO_MILI_GOTH_COMBAT_GATE:
            return m_uiGothCombatGateGUID;
        case NPC_ZELIEK:
            return m_uiZeliekGUID;
        case NPC_THANE:
            return m_uiThaneGUID;
        case NPC_BLAUMEUX:
            return m_uiBlaumeuxGUID;
        case NPC_RIVENDARE:
            return m_uiRivendareGUID;
        case NPC_THADDIUS:
            return m_uiThaddiusGUID;
        case NPC_STALAGG:
            return m_uiStalaggGUID;
        case NPC_FEUGEN:
            return m_uiFeugenGUID;
        case NPC_GOTHIK:
            return m_uiGothikGUID;
    }
    return 0;
}

void instance_naxxramas::SetGothTriggers()
{
    Creature* pGoth = instance->GetCreature(m_uiGothikGUID);

    if (!pGoth)
        return;

    for (std::list<uint64>::iterator itr = m_lGothTriggerList.begin(); itr != m_lGothTriggerList.end(); ++itr)
    {
        if (Creature* pTrigger = instance->GetCreature(*itr))
        {
            GothTrigger pGt;
            pGt.bIsAnchorHigh = (pTrigger->GetPositionZ() >= (pGoth->GetPositionZ() - 5.0f));
            pGt.bIsRightSide = IsInRightSideGothArea(pTrigger);

            m_mGothTriggerMap[pTrigger->GetGUID()] = pGt;
        }
    }
}

Creature* instance_naxxramas::GetClosestAnchorForGoth(Creature* pSource, bool bRightSide)
{
    std::list<Creature* > lList;

    for (UNORDERED_MAP<uint64, GothTrigger>::iterator itr = m_mGothTriggerMap.begin(); itr != m_mGothTriggerMap.end(); ++itr)
    {
        if (!itr->second.bIsAnchorHigh)
            continue;

        if (itr->second.bIsRightSide != bRightSide)
            continue;

        if (Creature* pCreature = instance->GetCreature(itr->first))
            lList.push_back(pCreature);
    }

    if (!lList.empty())
    {
        lList.sort(ObjectDistanceOrder(pSource));
        return lList.front();
    }

    return NULL;
}

void instance_naxxramas::GetGothSummonPointCreatures(std::list<Creature*> &lList, bool bRightSide)
{
    for (UNORDERED_MAP<uint64, GothTrigger>::iterator itr = m_mGothTriggerMap.begin(); itr != m_mGothTriggerMap.end(); ++itr)
    {
        if (itr->second.bIsAnchorHigh)
            continue;

        if (itr->second.bIsRightSide != bRightSide)
            continue;

        if (Creature* pCreature = instance->GetCreature(itr->first))
            lList.push_back(pCreature);
    }
}

bool instance_naxxramas::IsInRightSideGothArea(Unit* pUnit)
{
    if (GameObject* pCombatGate = instance->GetGameObject(m_uiGothCombatGateGUID))
        return (pCombatGate->GetPositionY() >= pUnit->GetPositionY());

    sLog.outError("left/right side check, Gothik combat area failed.");
    return true;
}

void instance_naxxramas::SetChamberCenterCoords(float fX, float fY, float fZ)
{
    m_fChamberCenterX = fX;
    m_fChamberCenterY = fY;
    m_fChamberCenterZ = fZ;
}

void instance_naxxramas::OnPlayerDeath(Player* p)
{
    if (m_auiEncounter[TYPE_ANUB_REKHAN] == IN_PROGRESS)
    {
        // On player death we spawn 5 scarabs under the player. Since the player
        // can die from falldmg or other sources, anubs script impl of KilledUnit may not
        // be called, thus we need to do it here.
        if (Creature* pAnub = instance->GetCreature(m_uiAnubRekhanGUID))
        {
            pAnub->AI()->DoCast(p, 29105, true);
            for (int i = 0; i < 5; i++)
            {
                if (Creature* cs = pAnub->SummonCreature(16698, p->GetPositionX(), p->GetPositionY(), p->GetPositionZ(), 0,
                    TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 60000))
                {
                    cs->SetInCombatWithZone();
                    if (Unit* csTarget = pAnub->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    {
                        cs->AI()->AttackStart(csTarget);
                        cs->AddThreat(csTarget, 5000);
                    }
                }
            }
        }
    }
}

InstanceData* GetInstanceData_instance_naxxramas(Map* pMap)
{
    return new instance_naxxramas(pMap);
}

void instance_naxxramas::onNaxxramasAreaTrigger(Player* pPlayer, const AreaTriggerEntry* pAt)
{
    switch (pAt->id)
    {
    case AREATRIGGER_KELTHUZAD:
        if (instance_naxxramas* pInstance = (instance_naxxramas*)pPlayer->GetInstanceData())
        {
            if (pInstance->GetData(TYPE_KELTHUZAD) == NOT_STARTED)
            {
                pInstance->SetData(TYPE_KELTHUZAD, SPECIAL);
                pInstance->SetChamberCenterCoords(pAt->x, pAt->y, pAt->z);
            }
        }
        break;
    case AREATRIGGER_FAERLINA:
        if (!m_faerlinaHaveGreeted)
        {
            m_faerlinaHaveGreeted = true;
            if (Creature* pFaerlina = GetCreature(m_uiFaerlinanGUID))
            {
                DoScriptText(-1533009, pFaerlina);
            }
        }
        break;
    }
}

bool AreaTrigger_at_naxxramas(Player* pPlayer, const AreaTriggerEntry* pAt)
{
    if (pPlayer->isGameMaster() || !pPlayer->isAlive())
        return false;

    if (instance_naxxramas* pInstance = (instance_naxxramas*)pPlayer->GetInstanceData())
    {
        pInstance->onNaxxramasAreaTrigger(pPlayer, pAt);
    }
    return false;
}

void AddSC_instance_naxxramas()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_naxxramas";
    pNewScript->GetInstanceData = &GetInstanceData_instance_naxxramas;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_naxxramas";
    pNewScript->pAreaTrigger = &AreaTrigger_at_naxxramas;
    pNewScript->RegisterSelf();
}
