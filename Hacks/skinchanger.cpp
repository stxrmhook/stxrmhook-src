#include "skinchanger.h"
#include "../Configs/skins.h"
#include "../Configs/Config.h"

int Knife = skin.KnifeCT; // Change knife models skins.h
int KnifeT = skin.KnifeT; // Change knife models skins.h
bool skinsLoaded = false;

unordered_map<int, cSkin> cSkinchanger::SkinList = unordered_map<int, cSkin>( {
	/* https://github.com/sonicrules11/CSGO-skin-ID-dumper/blob/master/item_index.txt */
	// make_pair(WEAPON, cSkin(SKIN, Seed, -1, Stattrak, Entity Quality, (char*)("Name") or nullptr for no name, Wear)),
    make_pair(WEAPON_KNIFE, cSkin(skin.CTKnifeID, -1, Knife, -1, 3, nullptr, 0.0001f)),
    make_pair(WEAPON_KNIFE_T, cSkin(skin.TKnifeID, -1, KnifeT, -1, 3, nullptr, 0.0001f)),
	// Pistols
	make_pair(WEAPON_CZ75A, cSkin(skin.cz, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_DEAGLE, cSkin(skin.deagle, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_ELITE, cSkin(skin.dual, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_FIVESEVEN, cSkin(skin.five7, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_GLOCK, cSkin(skin.glock, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_HKP2000, cSkin(skin.p2000, -1, -1, -1, 0, nullptr, 0.0001f)), // P2000
	make_pair(WEAPON_P250, cSkin(skin.p250, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_REVOLVER, cSkin(skin.revolver, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_TEC9, cSkin(skin.tec9, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_USP_SILENCER, cSkin(skin.usp, -1, -1, -1, 0, nullptr, 0.0001f)),
	// Rifles
	make_pair(WEAPON_AK47, cSkin(skin.ak47, -1, -1, -1, 0, (char*)("My Love"), 0.0001f)),
	make_pair(WEAPON_AUG, cSkin(skin.aug, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_AWP, cSkin(skin.awp, -1, -1, -1, 12, (char*)("I sucked cock for this"), 0.4202f)),
	make_pair(WEAPON_FAMAS, cSkin(skin.famas, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_G3SG1, cSkin(skin.g3, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_M4A1_SILENCER, cSkin(skin.m4a1, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_M4A1, cSkin(skin.m4a4, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_SCAR20, cSkin(skin.scar, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_SG556, cSkin(skin.sg, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_SSG08, cSkin(skin.scout, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_GALILAR, cSkin(skin.galil, -1, -1, -1, 0, nullptr, 0.0001f)),
	// SMGs
	make_pair(WEAPON_MAC10, cSkin(skin.mac10, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_MP7, cSkin(skin.mp7, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_MP9, cSkin(skin.mp9, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_P90, cSkin(skin.p90, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_UMP45, cSkin(skin.ump, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_BIZON, cSkin(skin.bizon, -1, -1, -1, 0, nullptr, 0.0001f)),
	// Heavy
	make_pair(WEAPON_MAG7, cSkin(skin.mag7, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_NOVA, cSkin(skin.nova, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_SAWEDOFF, cSkin(skin.sawed, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_XM1014, cSkin(skin.xm, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_M249, cSkin(skin.m249, -1, -1, -1, 0, nullptr, 0.0001f)),
	make_pair(WEAPON_NEGEV, cSkin(skin.negev, -1, -1, -1, 0, nullptr, 0.0001f)),	
});

unordered_map<int, const char*> cSkinchanger::ModelList;

cSkinchanger* skinchanger = new cSkinchanger;

void cSkinchanger::FrameStageNotify(ClientFrameStage_t stage) {
    if(stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START){
        pLocalPlayer = (C_BaseEntity*)(pEntList->GetClientEntity(pEngine->GetLocalPlayer()));

        if(pLocalPlayer && pLocalPlayer->GetHealth() > 0){
            if(!bInit){
                Init();
                bInit = true;
            }
            ForceSkins();
        }
    }
}

void cSkinchanger::FindModels() {
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl")] = KnifeToModelMatrix[Knife].c_str();
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl")] = KnifeToModelMatrix[KnifeT].c_str();
}

void cSkinchanger::LoadSkinsConfig() {
}

void cSkinchanger::ForceSkins() {
    IEngineClient::player_info_t player_info;

    if(pEngine->GetPlayerInfo(pLocalPlayer->GetId(), &player_info)){

        int* pWeapons = pLocalPlayer->GetWeapons();

        C_BaseViewModel* LocalPlayerViewModel = (C_BaseViewModel*)pEntList->GetClientEntityFromHandle(pLocalPlayer->GetViewModel());

        C_BaseAttributableItem* WeaponViewModel = nullptr;

        if(LocalPlayerViewModel)
            WeaponViewModel = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(LocalPlayerViewModel->GetWeapon());

        C_BaseCombatWeapon* localWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(pLocalPlayer->GetActiveWeapon());

        if(pWeapons){
            for(int i = 0; pWeapons[i]; i++){
                C_BaseAttributableItem* attributableItem = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(pWeapons[i]);

                if(attributableItem){
                    int* Definition = attributableItem->GetItemDefinitionIndex();

                    unordered_map<int, cSkin>::iterator SkinIter = (*Definition == WEAPON_KNIFE_T ? SkinList.find(WEAPON_KNIFE) : SkinList.find(*Definition));

                    if(SkinIter != SkinList.end()) {
                        if(*attributableItem->GetOriginalOwnerXuidLow() == player_info.xuidlow && *attributableItem->GetOriginalOwnerXuidHigh() == player_info.xuidhigh){

                            int* model_index = attributableItem->GetModelIndex();

                            unordered_map<int, const char*>::iterator model_iter = ModelList.find(*model_index);

                            if(model_iter != ModelList.end()){
                                *model_index = pModelInfo->GetModelIndex(model_iter->second);
                            }

                            cSkin skin = move(SkinIter->second);

                            if(Knife && (*Definition == WEAPON_KNIFE))
                                *attributableItem->GetItemDefinitionIndex() = Knife;
                            else if(KnifeT && (*Definition == WEAPON_KNIFE_T))
                                *attributableItem->GetItemDefinitionIndex() = KnifeT;

                            if(skin.name) {
                                sprintf(attributableItem->GetCustomName(), "%s", skin.name);
                            }

                            *attributableItem->GetItemIDHigh() = -1;
                            *attributableItem->GetFallbackPaintKit() = skin.Paintkit;
                            *attributableItem->GetFallbackStatTrak() = skin.StatTrack;
                            *attributableItem->GetEntityQuality() = skin.EntityQuality;
                            *attributableItem->GetFallbackSeed() = skin.Seed;
                            *attributableItem->GetFallbackWear() = skin.Wear;
                            *attributableItem->GetAccountID() = player_info.xuidlow;
                        }
                    }

                    if (WeaponViewModel && WeaponViewModel == attributableItem) {
                        int* model_index = ((C_BaseEntity*)LocalPlayerViewModel)->GetModelIndex();

                        unordered_map<int, const char*>::iterator model_iter = ModelList.find(*model_index);

                        if (model_iter != ModelList.end()) {
                            *model_index = pModelInfo->GetModelIndex(model_iter->second);
                        }
                    }
                }
            }

            if(LocalPlayerViewModel && localWeapon) {

                int* model_index = ((C_BaseEntity*)LocalPlayerViewModel)->GetModelIndex();

                unordered_map<int, const char*>::iterator model_iter = ModelList.find(*((C_BaseEntity*)localWeapon)->GetModelIndex());

                if(model_iter != ModelList.end()){
                    *model_index = pModelInfo->GetModelIndex(model_iter->second);
                }
            }
        }
    }
}

void cSkinchanger::Init() {
    ModelList.clear();
    FindModels();
}

void cSkinchanger::FireEventClientSide(IGameEvent *event) {
    if(!strcmp(event->GetName(), "game_newmap")) {
        Init();
    }
}

// Fix Animations (I don't know if any of the new knives have a new animation so I can't update them)
inline const int RandomSequence(int low, int high) {
    return (rand() % (high - low + 1) + low);
}

void HSequenceProxyFn(const CRecvProxyData *pDataConst, void *pStruct, void *pOut) {
    CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);
    C_BaseViewModel* pViewModel = (C_BaseViewModel*)pStruct;
    
    if(!pViewModel)
        return g_pSequence(pDataConst, pStruct, pOut);
    
    C_BaseEntity* pOwner = (C_BaseEntity*)pEntList->GetClientEntityFromHandle(pViewModel->GetOwner());
    
    if (pViewModel && pOwner) {
        if (pOwner->GetIndex() == pEngine->GetLocalPlayer()) {
            
            const model_t* knife_model = pModelInfo->GetModel(*pViewModel->GetModelIndex());
            const char* model_filename = pModelInfo->GetModelName(knife_model);
            
            int m_nSequence = (int)pData->m_Value.m_Int;
            
            if (!strcmp(model_filename, "models/weapons/v_knife_butterfly.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                        m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
                        break;
                    default:
                        m_nSequence++;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_falchion_advanced.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_FALCHION_IDLE1;
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_MISS1:
                        m_nSequence = RandomSequence(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
                        break;
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    default:
                        m_nSequence--;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_push.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_DAGGERS_IDLE1;
                        break;
                    case SEQUENCE_DEFAULT_LIGHT_MISS1:
                    case SEQUENCE_DEFAULT_LIGHT_MISS2:
                        m_nSequence = RandomSequence(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_MISS1:
                        m_nSequence = RandomSequence(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_HIT1:
                    case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence += 3;
                        break;
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    default:
                        m_nSequence += 2;
                }   
            } else if (!strcmp(model_filename, "models/weapons/v_knife_survival_bowie.mdl")) {
                
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_BOWIE_IDLE1;
                        break;
                    default:
                        m_nSequence--;
                }   
            }
            pData->m_Value.m_Int = m_nSequence;
        }
    }
    return g_pSequence(pData, pStruct, pOut);
}
