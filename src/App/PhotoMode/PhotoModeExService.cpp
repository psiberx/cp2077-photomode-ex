#include "PhotoModeExService.hpp"
#include "Red/EngineConfig.hpp"
#include "Red/TweakDB.hpp"

namespace
{
constexpr uint32_t PlayerYawAttribute = 7u;
constexpr uint32_t PlayerPositionLRAttribute = 8u;
constexpr uint32_t PlayerPositionFBAttribute = 9u;
constexpr uint32_t PlayerLookAtCameraAttribute = 15u;
constexpr uint32_t DepthOfFieldAttribute = 26u;
constexpr uint32_t BackgroundAttribute = 34u;
constexpr uint32_t PlayerPositionUDAttribute = 37u;
constexpr uint32_t CameraSpeedAttribute = 42u;
constexpr uint32_t CharacterSpawnAttribute = 55u;
constexpr uint32_t CharacterLookAtCameraAttribute = 58u;
constexpr uint32_t CharacterYawAttribute = 60u;
constexpr uint32_t CharacterPositionLRAttribute = 61u;
constexpr uint32_t CharacterPositionFBAttribute = 62u;
constexpr uint32_t CharacterPickAttribute = 63u;
constexpr uint32_t CharacterPositionUDAttribute = 66u;
constexpr uint32_t CharacterFirstAttribute = 67u;
constexpr uint32_t CharacterEditAttribute = 68u;

constexpr uint32_t ControlSchemaAttribute = 3401u;
constexpr uint32_t SnapToTerrainAttribute = 3402u;
constexpr uint32_t PlayerPitchAttribute = 3421u;
constexpr uint32_t PlayerRollAttribute = 3422u;
constexpr uint32_t CharacterPitchAttribute = 3431u;
constexpr uint32_t CharacterRollAttribute = 3432u;
constexpr uint32_t CharacterAppearanceAttribute = 3433u;

constexpr Red::CName LookAtCameraTorsoPreset = "LookatPreset.PhotoMode_LookAtCamera";
constexpr Red::CName LookAtCameraHeadPreset = "LookatPreset.PhotoMode_LookAtCamera_Head_Only";
constexpr Red::CName LookAtCameraEyesPreset = "LookatPreset.Eyes";

constexpr Red::TweakDBID WomanAverageID = "Character.Panam_Puppet_Photomode";
constexpr Red::TweakDBID ManAverageID = "Character.Viktor_Puppet_Photomode";
constexpr Red::TweakDBID ManBigID = "Character.Jackie_Puppet_Photomode";
constexpr Red::TweakDBID ManMassiveID = "Character.AdamSmasher_Puppet_Photomode";
constexpr Red::TweakDBID CatID = "Character.Nibbles_Puppet_Photomode";

constexpr Red::CName ManAverageTag = "ManAverage";
constexpr Red::CName ManBigTag = "ManBig";
constexpr Red::CName ManMassiveTag = "ManMassive";
constexpr Red::CName CatTag = "Cat";

constexpr uint32_t DummyCharacterSlots = 2;
}

void OnAdjustPuppetPosition(Red::Vector3* aResult, uint64_t* a2, uint64_t* a3, uint64_t* a4, Red::Vector3* a5,
                            Red::Vector3* aPosition, uint64_t* a7)
{
    *aResult = *a5 + *aPosition;
}

float OnCalculateGroundOffset(Red::gamePhotoModeSystem* aSystem, Red::Vector3* aPosition, uint64_t a4, uint64_t a5)
{
    return 0.0f;
}

void App::PhotoModeExService::OnBootstrap()
{
    HookAfter<Raw::LoadTweakDB>(&OnLoadTweakDB).OrThrow();

    HookAfter<Raw::PhotoModeSystem::Activate>(&OnActivate).OrThrow();
    HookAfter<Raw::PhotoModeSystem::Finalize>(&OnFinalize).OrThrow();
    HookBefore<Raw::PhotoModeSystem::Deactivate>(&OnDeactivate).OrThrow();
    Hook<Raw::PhotoModeSystem::ValidateCharacter>(&OnValidateCharacter).OrThrow();
    Hook<Raw::PhotoModeSystem::RegisterPoses>(&OnRegisterPoses).OrThrow();
    Hook<Raw::PhotoModeSystem::RegisterWeaponPoses>(&OnRegisterWeaponPoses).OrThrow();
    Hook<Raw::PhotoModeSystem::PrepareCategories>(&OnPrepareCategories).OrThrow();
    Hook<Raw::PhotoModeSystem::PreparePoses>(&OnPreparePoses).OrThrow();
    Hook<Raw::PhotoModeSystem::PrepareCameras>(&OnPrepareCameras).OrThrow();
    Hook<Raw::PhotoModeSystem::UpdatePoseDependents>(&OnUpdatePoseDependents).OrThrow();
    HookAfter<Raw::PhotoModeSystem::CalculateSpawnTransform>(&OnCalculateSpawnTransform).OrThrow();
    Hook<Raw::PhotoModeSystem::AdjustPuppetPosition>(&OnAdjustPuppetPosition).OrThrow();
    Hook<Raw::PhotoModeSystem::CalculateGroundOffset>(&OnCalculateGroundOffset).OrThrow();
    HookAfter<Raw::PhotoModeSystem::SpawnCharacter>(&OnSpawnCharacter).OrThrow();
    Hook<Raw::PhotoModeSystem::ApplyPuppetTransforms>(&OnApplyPuppetTransforms).OrThrow();
    HookAfter<Raw::PhotoModeSystem::SetRelativePosition>(&OnSetRelativePosition).OrThrow();
    Hook<Raw::PhotoModeSystem::SyncRelativePosition>(&OnSyncRelativePosition).OrThrow();
    HookAfter<Raw::PhotoModeSystem::ProcessAttribute>(&OnProcessAttribute).OrThrow();

    Hook<Raw::PhotoModeMenuController::AddMenuItem>(&OnAddMenuItem).OrThrow();
    HookAfter<Raw::PhotoModeMenuController::SetAttributeEnabled>(&OnSetAttributeEnabled).OrThrow();
    HookBefore<Raw::PhotoModeMenuController::SetupOptionSelector>(&OnSetupOptionSelector).OrThrow();
    HookBefore<Raw::PhotoModeMenuController::SetupGridSelector>(&OnSetupGridSelector).OrThrow();
    HookBefore<Raw::PhotoModeMenuController::SetupScrollBar>(&OnSetupScrollBar).OrThrow();
    HookBefore<Raw::PhotoModeMenuController::ForceAttributeVaulue>(&OnForceAttributeVaulue).OrThrow();
    Hook<Raw::PhotoModeMenuController::SetNpcImageCallback>(&OnSetNpcImage).OrThrow();

    Red::CNamePool::Add("LookatPreset.Eyes");
}

void App::PhotoModeExService::OnLoadTweakDB()
{
    auto iconList = Red::GetFlat<Red::DynArray<Red::CString>>("photo_mode.npcs.npcRecordID");
    auto puppetList = Red::GetFlat<Red::DynArray<Red::CString>>("photo_mode.general.recordIDForPhotoModePuppet");
    auto nameList = Red::GetFlat<Red::DynArray<Red::CString>>("photo_mode.general.localizedNameForPhotoModePuppet");
    auto factList = Red::GetFlat<Red::DynArray<Red::CString>>("photo_mode.general.questFactIDForPhotoModePuppet");
    auto enabledList = Red::GetFlat<Red::DynArray<bool>>("photo_mode.general.enabledPhotoModePuppet");
    auto customizationList = Red::GetFlat<Red::DynArray<bool>>("photo_mode.general.customizablePhotoModePuppet");
    auto expressionList = Red::GetFlat<Red::DynArray<bool>>("photo_mode.general.expressionChangingPhotoModePuppet");
    auto collisionRadiusList = Red::GetFlat<Red::DynArray<float>>("photo_mode.general.collisionRadiusForPhotoModePuppet");
    auto collisionHeightList = Red::GetFlat<Red::DynArray<float>>("photo_mode.general.collisionHeightForPhotoModePuppet");

    for (uint32_t characterIndex = 0; characterIndex < puppetList.size; ++characterIndex)
    {
        auto characterID = Red::TweakDBID(puppetList[characterIndex].c_str());

        s_characterIndexMap[characterID] = characterIndex;
        s_characterRecordMap[characterIndex] = characterID;
    }

    Core::SortedMap<std::string, Red::Handle<Red::gamedataCharacter_Record>> addedCharacterRecords;

    for (const auto& characterRecord : Red::GetRecords<Red::gamedataCharacter_Record>())
    {
        auto characterID = characterRecord->recordID;
        auto persistentName = Red::GetFlat<Red::CName>({characterID, ".persistentName"});

        if (persistentName != "PhotomodePuppet")
            continue;

        if (s_characterIndexMap.contains(characterID))
            continue;

        auto characterStr = Red::ToStringDebug(characterID);

        addedCharacterRecords[characterStr.c_str()] = characterRecord;
    }

    if (addedCharacterRecords.empty())
        return;

    {
        s_dummyCharacterIndex = puppetList.size;

        auto dummyName = "PhotoModeNpcs.DoNotTouch";
        Red::CreateRecord(dummyName, "PhotoModeSticker");

        for (auto i = DummyCharacterSlots; i > 0; --i)
        {
            iconList.PushBack(dummyName);
            puppetList.PushBack("");
            nameList.PushBack("");
            factList.PushBack("");
            enabledList.PushBack(false);
            customizationList.PushBack(false);
            expressionList.PushBack(false);
            collisionRadiusList.PushBack(0.0);
            collisionHeightList.PushBack(0.0);
        }
    }

    for (const auto& [characterStr, characterRecord] : addedCharacterRecords)
    {
        auto characterID = characterRecord->recordID;
        auto persistentName = Red::GetFlat<Red::CName>({characterID, ".persistentName"});

        auto characterIndex = puppetList.size;
        auto characterSource = s_characterIndexMap[WomanAverageID];
        auto characterType = Red::PhotoModeCharacterType::NPC;

        auto visualTags = Red::GetFlat<Red::DynArray<Red::TweakDBID>>({characterID, ".visualTags"});
        for (const auto& visualTag : visualTags)
        {
            if (visualTag == ManAverageTag)
            {
                characterSource = s_characterIndexMap[ManAverageID];
                break;
            }
            if (visualTag == ManBigTag)
            {
                characterSource = s_characterIndexMap[ManBigID];
                break;
            }
            if (visualTag == ManMassiveTag)
            {
                characterSource = s_characterIndexMap[ManMassiveID];
                break;
            }
            if (visualTag == CatTag)
            {
                characterSource = s_characterIndexMap[CatID];
                break;
            }
        }

        s_extraCharacters[characterIndex] = {characterSource, characterType};
        s_characterIndexMap[characterID] = characterIndex;
        s_characterRecordMap[characterIndex] = characterID;

        auto displayName = Red::GetFlat<Red::gamedataLocKeyWrapper>({characterID, ".displayName"});
        auto nameStr = std::string{"LocKey#"} + std::to_string(displayName.primaryKey);
        auto iconStr = characterStr + ".icon";

        iconList.PushBack(iconStr);
        puppetList.PushBack(characterStr);
        nameList.PushBack(nameStr);
        factList.PushBack("");
        enabledList.PushBack(true);
        customizationList.PushBack(false);
        expressionList.PushBack(true);
        collisionRadiusList.PushBack(0.35);
        collisionHeightList.PushBack(1.2);

        LogInfo("Registered NPC: {}.", characterStr);
    }

    Red::SetFlat("photo_mode.npcs.npcRecordID", iconList);
    Red::SetFlat("photo_mode.general.recordIDForPhotoModePuppet", puppetList);
    Red::SetFlat("photo_mode.general.localizedNameForPhotoModePuppet", nameList);
    Red::SetFlat("photo_mode.general.questFactIDForPhotoModePuppet", factList);
    Red::SetFlat("photo_mode.general.enabledPhotoModePuppet", enabledList);
    Red::SetFlat("photo_mode.general.customizablePhotoModePuppet", customizationList);
    Red::SetFlat("photo_mode.general.expressionChangingPhotoModePuppet", expressionList);
    Red::SetFlat("photo_mode.general.collisionRadiusForPhotoModePuppet", collisionRadiusList);
    Red::SetFlat("photo_mode.general.collisionHeightForPhotoModePuppet", collisionHeightList);

    s_maxCharacterIndex = puppetList.size - 1;
}

void App::PhotoModeExService::OnActivate(Red::gamePhotoModeSystem* aSystem)
{
    s_photoModeSystem = aSystem;
    s_characterAddons.reserve(s_maxCharacterIndex + 1);

    auto& characterList = Raw::PhotoModeSystem::CharacterList::Ref(aSystem);

    if (!characterList.size)
        return;

    for (const auto& [characterIndex, characterSource] : s_extraCharacters)
    {
        Red::DynArray<Red::gamedataItemType> itemTypes;
        Red::DynArray<Red::Handle<Red::gameItemObject>> clothingItems;

        FillWeaponTypes(itemTypes);

        Raw::PhotoModeSystem::RegisterCharacter(aSystem, characterIndex, characterList,
                                                Red::PhotoModeCharacterType::NPC, itemTypes, clothingItems);
    }

    {
        auto persistentStateType = Red::GetClass<PhotoModeExPS>();
        auto persistentStateID = Red::GetTypeHash<PhotoModeExPS>();
        auto persistencySystem = Red::GetGameSystem<Red::IPersistencySystem>();
        persistencySystem->GetPersistentState(s_persistentState, persistentStateID, persistentStateType, true);
    }
}

void App::PhotoModeExService::OnFinalize(Red::gamePhotoModeSystem* aSystem)
{
    s_initialized = true;

    Raw::PhotoModeSystem::SetAttributeValue(aSystem, ControlSchemaAttribute, s_persistentState->alternativeControls ? 1.0 : 0.0, false);
    Raw::PhotoModeSystem::SetAttributeValue(aSystem, SnapToTerrainAttribute, s_persistentState->snapToTerrain ? 1.0 : 0.0, false);
    Raw::PhotoModeSystem::SetAttributeValue(aSystem, DepthOfFieldAttribute, s_persistentState->depthOfField ? 1.0 : 0.0, false);
}

void App::PhotoModeExService::OnDeactivate(Red::gamePhotoModeSystem* aSystem)
{
    Red::EngineConfig::Get()->SetValue("SnapToTerrainIk", "Enabled", true);

    s_characterAddons.clear();
    s_initialized = false;
}

bool App::PhotoModeExService::OnValidateCharacter(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex)
{
    auto extracCharacter = s_extraCharacters.find(aCharacterIndex);
    if (extracCharacter != s_extraCharacters.end())
    {
        aCharacterIndex = extracCharacter->second.index;
    }

    return Raw::PhotoModeSystem::ValidateCharacter(aSystem, aCharacterIndex);
}

void App::PhotoModeExService::OnRegisterPoses(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                                              Red::PhotoModeCharacterType aCharacterType)
{
    if (!s_extraCharacters.contains(aCharacterIndex))
    {
        Raw::PhotoModeSystem::RegisterPoses(aSystem, aCharacterIndex, aCharacterType);
    }
}

void App::PhotoModeExService::OnRegisterWeaponPoses(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                                                    Red::DynArray<Red::gamedataItemType>& aItemTypes)
{
    auto extracCharacter = s_extraCharacters.find(aCharacterIndex);
    if (extracCharacter != s_extraCharacters.end())
    {
        aCharacterIndex = extracCharacter->second.index;
    }

    if (aItemTypes.size == 0)
    {
        FillWeaponTypes(aItemTypes);
    }

    Raw::PhotoModeSystem::RegisterWeaponPoses(aSystem, aCharacterIndex, aItemTypes);
}

void App::PhotoModeExService::OnPrepareCategories(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                                                  uint64_t a3)
{
    auto extracCharacter = s_extraCharacters.find(aCharacterIndex);
    if (extracCharacter != s_extraCharacters.end())
    {
        aCharacterIndex = extracCharacter->second.index;
    }

    Raw::PhotoModeSystem::PrepareCategories(aSystem, aCharacterIndex, a3);
}

void App::PhotoModeExService::OnPreparePoses(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                                             uint32_t aCategoryIndex, uint64_t a4)
{
    auto extracCharacter = s_extraCharacters.find(aCharacterIndex);
    if (extracCharacter != s_extraCharacters.end())
    {
        aCharacterIndex = extracCharacter->second.index;
    }

    Raw::PhotoModeSystem::PreparePoses(aSystem, aCharacterIndex, aCategoryIndex, a4);
}

void App::PhotoModeExService::OnPrepareCameras(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                                               uint32_t* a3, uint32_t* a4)
{
    auto extracCharacter = s_extraCharacters.find(aCharacterIndex);
    if (extracCharacter != s_extraCharacters.end())
    {
        aCharacterIndex = extracCharacter->second.index;
    }

    Raw::PhotoModeSystem::PrepareCameras(aSystem, aCharacterIndex, a3, a4);
}

void App::PhotoModeExService::OnUpdatePoseDependents(Red::gamePhotoModeSystem* aSystem, uint32_t aCategoryIndex,
                                                     uint32_t aPoseIndex, Red::PhotoModeCharacter* aCharacter)
{
    auto extracCharacter = s_extraCharacters.find(aCharacter->characterIndex);
    if (extracCharacter != s_extraCharacters.end())
    {
        aCharacter->characterIndex = extracCharacter->second.index;
    }

    auto lookAtCameraPreset = aCharacter->lookAtCameraPreset;
    if (!lookAtCameraPreset)
    {
        lookAtCameraPreset = LookAtCameraTorsoPreset;
    }

    Raw::PhotoModeSystem::UpdatePoseDependents(aSystem, aCategoryIndex, aPoseIndex, aCharacter);

    if (extracCharacter != s_extraCharacters.end())
    {
        aCharacter->characterIndex = extracCharacter->first;
    }

    aCharacter->allowLookAtCamera = true;
    aCharacter->lookAtCameraPreset = lookAtCameraPreset;
}

void App::PhotoModeExService::OnCalculateSpawnTransform(Red::gamePhotoModeSystem* aSystem,
                                                        Red::Transform& aSpawnTransform,
                                                        const Red::Transform& aInitialTransform, uint64_t* a4, bool a5)
{
    if (s_persistentState->alternativeControls)
    {
        aSpawnTransform = aInitialTransform;
    }
}

void App::PhotoModeExService::OnSpawnCharacter(Red::gamePhotoModeSystem* aSystem, Red::PhotoModeCharacter* aCharacter,
                                               uint32_t a3, const Red::Transform& aSpawnTransform, uint64_t a5)
{
    if (aCharacter->characterType != Red::PhotoModeCharacterType::NPC)
        return;

    if (s_persistentState->alternativeControls)
    {
        auto slot = Raw::PhotoModeSystem::SpawnSlot::Ref(aSystem);
        auto right = 0.0f;
        auto forward = 0.0f;

        switch (slot)
        {
        case 0:
        {
            right = -0.75;
            break;
        }
        case 1:
        {
            right = 0.75;
            break;
        }
        default:
        {
            forward = 0.75;
            break;
        }
        }

        aCharacter->relativeOffsetRight = right;
        aCharacter->relativeOffsetForward = forward;
        aCharacter->updateTransform = true;

        FixRelativePosition(aCharacter);
    }

    auto& addon = s_characterAddons[aCharacter->characterIndex];

    addon.relativePitch = 0;
    addon.relativeRoll = 0;

    if (addon.appearanceOptions.size == 0)
    {
        addon.appearanceOptions.PushBack({"default", 0});

        auto characterIndex = aCharacter->characterIndex;
        auto characterID = s_characterRecordMap[characterIndex];
        auto templatePath = Red::GetFlat<Red::ResourcePath>({characterID, ".entityTemplatePath"});

        auto templateToken = Red::ResourceLoader::Get()->LoadAsync<Red::entEntityTemplate>(templatePath);
        templateToken->OnLoaded([characterIndex](const Red::Handle<Red::entEntityTemplate>& aTemplate) {
            if (aTemplate->appearances.size > 0)
            {
                auto& addon = s_characterAddons[characterIndex];

                addon.appeanceIndex = 0;
                addon.appearanceNames.clear();
                addon.appearanceOptions.Clear();

                for (int32_t optionIndex = 0; optionIndex < aTemplate->appearances.size; ++optionIndex)
                {
                    auto appearanceName = aTemplate->appearances[optionIndex].name;

                    if (appearanceName == aTemplate->defaultAppearance)
                    {
                        addon.appeanceIndex = optionIndex;
                        addon.appeanceDefaultIndex = optionIndex;
                    }

                    std::string appearanceNameStr = appearanceName.ToString();
                    if (appearanceNameStr.length() > 36)
                    {
                        appearanceNameStr.resize(34);
                        appearanceNameStr += "...";
                    }

                    addon.appearanceNames.push_back(appearanceName);
                    addon.appearanceOptions.PushBack({appearanceNameStr, optionIndex});
                }
            }

            UpdateAppearanceList(characterIndex);
        });
    }
    else
    {
        addon.appeanceIndex = addon.appeanceDefaultIndex;
    }
}

void App::PhotoModeExService::OnApplyPuppetTransforms(Red::gamePhotoModeSystem* aSystem,
                                                      Red::DynArray<Red::PhotoModeCharacter>& aCharacterList,
                                                      uint8_t aCharacterGroup)
{
    Core::Vector<Red::PhotoModeCharacter*> updateList;

    for (auto& character : aCharacterList)
    {
        if (character.puppet && character.puppet->transformComponent && character.updateTransform)
        {
            updateList.emplace_back(&character);
        }
    }

    Raw::PhotoModeSystem::ApplyPuppetTransforms(aSystem, aCharacterList, aCharacterGroup);

    for (auto& character : updateList)
    {
        if (character->puppet && character->puppet->transformComponent && !character->updateTransform)
        {
            auto& addon = s_characterAddons[character->characterIndex];

            Red::Quaternion quat{};
            Red::EulerAngles angles{};

            Red::CallStatic("Quaternion", "ToEulerAngles", angles, character->spawnOrientation);

            angles.Yaw += character->relativeRotation;
            angles.Pitch -= addon.relativePitch;
            angles.Roll -= addon.relativeRoll;

            Red::CallStatic("EulerAngles", "ToQuat", quat, angles);

            character->puppet->transformComponent->localTransform.Orientation = quat;
        }
    }
}

void App::PhotoModeExService::OnSetRelativePosition(Red::gamePhotoModeSystem* aSystem, uint8_t a2,
                                                    uint8_t aCharacterGroup)
{
    if (s_persistentState->alternativeControls)
    {
        if (aCharacterGroup == 0)
        {
            auto* player = Raw::PhotoModeSystem::Player::Ptr(aSystem);
            if (player && player->puppet && player->puppet->transformComponent && player->updateTransform)
            {
                FixRelativePosition(player);
            }
        }
        else
        {
            auto& characterList = Raw::PhotoModeSystem::CharacterList::Ref(aSystem);
            for (auto& character : characterList)
            {
                if (character.puppet && character.puppet->transformComponent && character.updateTransform)
                {
                    FixRelativePosition(&character);
                }
            }
        }
    }
}

void App::PhotoModeExService::FixRelativePosition(Red::PhotoModeCharacter* aCharacter)
{
    auto& rot = aCharacter->spawnOrientation;
    auto pos = Red::Vector4{-aCharacter->relativeOffsetRight,
                            aCharacter->relativeOffsetForward,
                            aCharacter->relativePosition.Z,
                            0.0};

    Red::CallStatic("Quaternion", "Transform", pos, rot, pos);

    aCharacter->relativePosition.X = pos.X;
    aCharacter->relativePosition.Y = pos.Y;
    aCharacter->relativePosition.Z = pos.Z;
}

void App::PhotoModeExService::OnSyncRelativePosition(Red::gamePhotoModeSystem* aSystem)
{
    if (!s_persistentState->alternativeControls)
    {
        Raw::PhotoModeSystem::SyncRelativePosition(aSystem);
    }
}

void App::PhotoModeExService::OnProcessAttribute(Red::gamePhotoModeSystem* aSystem, uint32_t aAttribute)
{
    if (!s_initialized)
        return;

    switch (aAttribute)
    {
    case PlayerLookAtCameraAttribute:
    {
        auto* player = Raw::PhotoModeSystem::Player::Ptr(aSystem);
        if (player && player->spawnedState > 0.0)
        {
            float state;
            Raw::PhotoModeSystem::GetAttributeValue(aSystem, aAttribute, state);

            if (state == 1.0)
            {
                player->lookAtCameraPreset = LookAtCameraTorsoPreset;
            }
            else if (state == 2.0)
            {
                player->lookAtCameraPreset = LookAtCameraHeadPreset;
            }
            else if (state == 3.0)
            {
                player->lookAtCameraPreset = LookAtCameraEyesPreset;
            }
            else
            {
                player->lookAtCameraPreset = "";
            }
        }
        break;
    }
    case CharacterLookAtCameraAttribute:
    {
        auto& spawnList = Raw::PhotoModeSystem::SpawnList::Ref(aSystem);
        auto& spawnSlot = Raw::PhotoModeSystem::SpawnSlot::Ref(aSystem);
        if (spawnSlot >= 0 && spawnSlot <= 2)
        {
            auto character = spawnList[spawnSlot];
            if (character && character->spawnedState > 0.0)
            {
                float state;
                Raw::PhotoModeSystem::GetAttributeValue(aSystem, aAttribute, state);

                if (state == 1.0)
                {
                    character->lookAtCameraPreset = LookAtCameraTorsoPreset;
                }
                else if (state == 2.0)
                {
                    character->lookAtCameraPreset = LookAtCameraHeadPreset;
                }
                else if (state == 3.0)
                {
                    character->lookAtCameraPreset = LookAtCameraEyesPreset;
                }
                else
                {
                    character->lookAtCameraPreset = "";
                }
            }
        }
        break;
    }
    case PlayerYawAttribute:
    {
        auto* player = Raw::PhotoModeSystem::Player::Ptr(aSystem);
        if (player)
        {
            Raw::PhotoModeSystem::GetAttributeValue(aSystem, aAttribute, player->relativeRotation);

            player->updateTransform = true;
        }
        break;
    }
    case PlayerPitchAttribute:
    case PlayerRollAttribute:
    {
        auto* player = Raw::PhotoModeSystem::Player::Ptr(aSystem);
        if (player)
        {
            auto& addon = s_characterAddons[player->characterIndex];

            float& value = aAttribute == PlayerPitchAttribute
                               ? addon.relativePitch
                               : addon.relativeRoll;
            Raw::PhotoModeSystem::GetAttributeValue(aSystem, aAttribute, value);

            player->updateTransform = true;
        }
        break;
    }
    case CharacterPitchAttribute:
    case CharacterRollAttribute:
    {
        auto& spawnList = Raw::PhotoModeSystem::SpawnList::Ref(aSystem);
        auto& spawnSlot = Raw::PhotoModeSystem::SpawnSlot::Ref(aSystem);
        if (spawnSlot >= 0 && spawnSlot <= 2)
        {
            auto character = spawnList[spawnSlot];
            if (character)
            {
                auto& addon = s_characterAddons[character->characterIndex];

                float& value = aAttribute == CharacterPitchAttribute
                                   ? addon.relativePitch
                                   : addon.relativeRoll;
                Raw::PhotoModeSystem::GetAttributeValue(aSystem, aAttribute, value);

                character->updateTransform = true;
            }
        }
        break;
    }
    case CharacterAppearanceAttribute:
    {
        auto& spawnList = Raw::PhotoModeSystem::SpawnList::Ref(aSystem);
        auto& spawnSlot = Raw::PhotoModeSystem::SpawnSlot::Ref(aSystem);
        if (spawnSlot >= 0 && spawnSlot <= 2)
        {
            auto character = spawnList[spawnSlot];
            if (character)
            {
                auto& addon = s_characterAddons[character->characterIndex];

                float value;
                Raw::PhotoModeSystem::GetAttributeValue(aSystem, aAttribute, value);

                auto appeanceIndex = static_cast<int32_t>(value);
                if (appeanceIndex >=0 && appeanceIndex < addon.appearanceNames.size())
                {
                    addon.appeanceIndex = appeanceIndex;

                    if (character->puppet && character->spawnedState > 0.0)
                    {
                        Red::CallVirtual(character->puppet, "ScheduleAppearanceChange",
                                         addon.appearanceNames[addon.appeanceIndex]);
                    }
                }
            }
        }
        break;
    }
    case CharacterSpawnAttribute:
    {
        auto& spawnSlot = Raw::PhotoModeSystem::SpawnSlot::Ref(s_photoModeSystem);
        auto& editSlot = Raw::PhotoModeSystem::EditSlot::Ref(s_photoModeSystem);

        editSlot = spawnSlot;

        UpdateAppearanceList(-1);
        break;
    }
    case CharacterEditAttribute:
    {
        auto& spawnSlot = Raw::PhotoModeSystem::SpawnSlot::Ref(s_photoModeSystem);
        auto& editSlot = Raw::PhotoModeSystem::EditSlot::Ref(s_photoModeSystem);

        spawnSlot = editSlot;

        UpdateAppearanceList(-1);
        break;
    }
    case DepthOfFieldAttribute:
    {
        float state;
        Raw::PhotoModeSystem::GetAttributeValue(aSystem, aAttribute, state);

        s_persistentState->depthOfField = (state == 1.0f);
        break;
    }
    case ControlSchemaAttribute:
    {
        float state;
        Raw::PhotoModeSystem::GetAttributeValue(aSystem, aAttribute, state);

        s_persistentState->alternativeControls = (state == 1.0f);
        break;
    }
    case SnapToTerrainAttribute:
    {
        float state;
        Raw::PhotoModeSystem::GetAttributeValue(aSystem, aAttribute, state);

        s_persistentState->snapToTerrain = (state == 1.0f);
        
        Red::EngineConfig::Get()->SetValue("SnapToTerrainIk", "Enabled", s_persistentState->snapToTerrain);
        break;
    }
    case BackgroundAttribute:
    {
        auto& characterList = Raw::PhotoModeSystem::CharacterList::Ref(aSystem);
        auto& characterBgOffset = Raw::PhotoModeSystem::CharacterBgOffset::Ref(aSystem);
        auto& playerBgOffset = Raw::PhotoModeSystem::PlayerBgOffset::Ref(aSystem);

        characterBgOffset = playerBgOffset;

        for (auto& character : characterList)
        {
            if (character.puppet && character.spawnedState > 0.0)
            {
                character.updateTransform = true;
            }
        }
        break;
    }
    }
}

void App::PhotoModeExService::OnAddMenuItem(Red::gameuiPhotoModeMenuController* aController, Red::CName aEventName,
                                            const Red::CString& aLabel, uint32_t aAttribute, uint32_t aPage)
{
    s_photoModeController = aController;

    switch (aAttribute)
    {
    case CameraSpeedAttribute:
    {
        Raw::PhotoModeMenuController::AddMenuItem(aController, aEventName, aLabel, aAttribute, aPage);
        Raw::PhotoModeMenuController::AddMenuItem(aController, aEventName, GetLocalizedText("UI-Settings-Interface-InputSchemesMode"), ControlSchemaAttribute, aPage);
        Raw::PhotoModeMenuController::AddMenuItem(aController, aEventName, "Snap To Terrain", SnapToTerrainAttribute, aPage);
        break;
    }
    case PlayerYawAttribute:
    {
        std::string label = aLabel.c_str(); // GetLocalizedText("UI-PhotoMode-MenuItemPoseAdjustRotation")
        Raw::PhotoModeMenuController::AddMenuItem(aController, aEventName, label + " Y", PlayerYawAttribute, aPage);
        Raw::PhotoModeMenuController::AddMenuItem(aController, aEventName, label + " P", PlayerPitchAttribute, aPage);
        Raw::PhotoModeMenuController::AddMenuItem(aController, aEventName, label + " R", PlayerRollAttribute, aPage);
        break;
    }
    case CharacterYawAttribute:
    {
        std::string label = aLabel.c_str(); // GetLocalizedText("UI-PhotoMode-MenuItemPoseAdjustRotation")
        Raw::PhotoModeMenuController::AddMenuItem(aController, aEventName, label + " Y", CharacterYawAttribute, aPage);
        Raw::PhotoModeMenuController::AddMenuItem(aController, aEventName, label + " P", CharacterPitchAttribute, aPage);
        Raw::PhotoModeMenuController::AddMenuItem(aController, aEventName, label + " R", CharacterRollAttribute, aPage);
        break;
    }
    case CharacterFirstAttribute:
    {
        Raw::PhotoModeMenuController::AddMenuItem(aController, aEventName, GetLocalizedText(28758ull), CharacterAppearanceAttribute, aPage);
    }
    default:
    {
        Raw::PhotoModeMenuController::AddMenuItem(aController, aEventName, aLabel, aAttribute, aPage);
    }
    }
}

void App::PhotoModeExService::OnSetAttributeEnabled(Red::gameuiPhotoModeMenuController* aController,
                                                    uint32_t aAttribute, bool aEnabled)
{
    switch (aAttribute)
    {
    case PlayerYawAttribute:
    {
        Raw::PhotoModeMenuController::SetAttributeEnabled(aController, PlayerPitchAttribute, aEnabled);
        Raw::PhotoModeMenuController::SetAttributeEnabled(aController, PlayerRollAttribute, aEnabled);
        break;
    }
    case CharacterYawAttribute:
    {
        Raw::PhotoModeMenuController::SetAttributeEnabled(aController, CharacterPitchAttribute, aEnabled);
        Raw::PhotoModeMenuController::SetAttributeEnabled(aController, CharacterRollAttribute, aEnabled);
        break;
    }
    case CharacterFirstAttribute:
    {
        Raw::PhotoModeMenuController::SetAttributeEnabled(aController, CharacterAppearanceAttribute, aEnabled);
        break;
    }
    }
}

void App::PhotoModeExService::OnSetupOptionSelector(void* aCallback, uint64_t aEvent, uint8_t& a3, uint32_t& aAttribute,
                                                    Red::DynArray<Red::gameuiPhotoModeOptionSelectorData>& aElements,
                                                    int32_t& aDefaultIndex, bool& aApply)
{
    switch (aAttribute)
    {
    case DepthOfFieldAttribute:
    {
        aAttribute = ControlSchemaAttribute;
        aDefaultIndex = 1;
        Red::DynArray<Red::gameuiPhotoModeOptionSelectorData> controlElements;
        controlElements.PushBack({GetLocalizedText("UI-Settings-Interface-InputSchemeLegacy"), 0});
        controlElements.PushBack({GetLocalizedText("UI-Settings-Interface-InputSchemeAlternative"), 1});
        Raw::PhotoModeMenuController::SetupOptionSelector(aCallback, aEvent, a3, aAttribute, controlElements,
                                                          aDefaultIndex, aApply);

        aAttribute = SnapToTerrainAttribute;
        aDefaultIndex = 0;
        Raw::PhotoModeMenuController::SetupOptionSelector(aCallback, aEvent, a3, aAttribute, aElements,
                                                          aDefaultIndex, aApply);

        aAttribute = DepthOfFieldAttribute;
        break;
    }
    case PlayerLookAtCameraAttribute:
    case CharacterLookAtCameraAttribute:
    {
        std::string eyesPresetLabel = GetLocalizedText("UI-CharacterCreation-eyes").c_str();
        std::string headPresetLabel = GetLocalizedText("UI-ResourceExports-Head").c_str();
        std::string torsoPresetLabel = GetLocalizedText("UI-ResourceExports-Chest").c_str();
        torsoPresetLabel += " + " + headPresetLabel;

        aElements.RemoveAt(1);
        aElements.PushBack({torsoPresetLabel, 1});
        aElements.PushBack({headPresetLabel, 2});
        aElements.PushBack({eyesPresetLabel, 3});
        break;
    }
    }
}

void App::PhotoModeExService::OnSetupGridSelector(void* aCallback, uint64_t aEvent, uint8_t& a3, uint32_t& aAttribute,
                                                  Red::DynArray<Red::gameuiPhotoModeOptionGridButtonData>& aElements,
                                                  uint32_t& aElementsCount, uint32_t& aElementsInRow)
{
    if (aAttribute == CharacterPickAttribute && s_dummyCharacterIndex && aElements.size >= s_dummyCharacterIndex)
    {
        aElementsCount -= DummyCharacterSlots;

        for (auto i = DummyCharacterSlots; i > 0; --i)
        {
            aElements.RemoveAt(s_dummyCharacterIndex - 1);
        }
    }
}

void App::PhotoModeExService::OnSetupScrollBar(void* aCallback, uint64_t aEvent,
                                               uint8_t& a3, uint32_t& aAttribute, float& aStartValue, float& aMinValue,
                                               float& aMaxValue, float& aStep, bool& aShowPercents)
{
    switch (aAttribute)
    {
    case PlayerPositionLRAttribute:
    case PlayerPositionFBAttribute:
    case PlayerPositionUDAttribute:
    case CharacterPositionLRAttribute:
    case CharacterPositionFBAttribute:
    case CharacterPositionUDAttribute:
    {
        aMinValue = std::min(std::max(aMinValue, -1.0f), -5.0f);
        aMaxValue = std::max(std::min(aMaxValue, 1.0f), 5.0f);
        aStep = 0.01;
        break;
    }
    case PlayerYawAttribute:
    {
        aMinValue = -180.0f;
        aMaxValue = 180.0f;

        aAttribute = PlayerPitchAttribute;
        Raw::PhotoModeMenuController::SetupScrollBar(aCallback, aEvent, a3, aAttribute, aStartValue,
                                                     aMinValue, aMaxValue, aStep, aShowPercents);

        aAttribute = PlayerRollAttribute;
        Raw::PhotoModeMenuController::SetupScrollBar(aCallback, aEvent, a3, aAttribute, aStartValue,
                                                     aMinValue, aMaxValue, aStep, aShowPercents);

        aAttribute = PlayerYawAttribute;
        break;
    }
    case CharacterYawAttribute:
    {
        aMinValue = -180.0f;
        aMaxValue = 180.0f;

        aAttribute = CharacterPitchAttribute;
        Raw::PhotoModeMenuController::SetupScrollBar(aCallback, aEvent, a3, aAttribute, aStartValue,
                                                     aMinValue, aMaxValue, aStep, aShowPercents);

        aAttribute = CharacterRollAttribute;
        Raw::PhotoModeMenuController::SetupScrollBar(aCallback, aEvent, a3, aAttribute, aStartValue,
                                                     aMinValue, aMaxValue, aStep, aShowPercents);

        aAttribute = CharacterYawAttribute;
        break;
    }
    }
}

void App::PhotoModeExService::OnForceAttributeVaulue(void* aCallback, uint64_t aEvent, uint8_t& a3,
                                                     uint32_t& aAttribute, float& aValue, bool& aApply)
{
    if (aAttribute == DepthOfFieldAttribute)
    {
        aAttribute = ControlSchemaAttribute;
        aValue = s_persistentState->alternativeControls ? 1.0f : 0.0f;
        Raw::PhotoModeMenuController::ForceAttributeVaulue(aCallback, aEvent, a3, aAttribute, aValue, aApply);

        aAttribute = SnapToTerrainAttribute;
        aValue = s_persistentState->snapToTerrain ? 1.0f : 0.0f;
        Raw::PhotoModeMenuController::ForceAttributeVaulue(aCallback, aEvent, a3, aAttribute, aValue, aApply);

        aAttribute = DepthOfFieldAttribute;
        aValue = s_persistentState->depthOfField ? 1.0f : 0.0f;
    }
}

void App::PhotoModeExService::OnSetNpcImage(void* aCallback, uint32_t aCharacterIndex, Red::ResourcePath aAtlasPath,
                                            Red::CName aImagePart, int32_t aImageIndex)
{
    if (s_dummyCharacterIndex)
    {
        if (aImageIndex >= s_dummyCharacterIndex)
        {
            aImageIndex -= DummyCharacterSlots;
        }
    }

    Raw::PhotoModeMenuController::SetNpcImageCallback(aCallback, aCharacterIndex, aAtlasPath, aImagePart, aImageIndex);
}

void App::PhotoModeExService::UpdateAppearanceList(uint32_t aCharacterIndex)
{
    if (!s_photoModeSystem || !s_photoModeController)
        return;

    auto& spawnList = Raw::PhotoModeSystem::SpawnList::Ref(s_photoModeSystem);
    auto& spawnSlot = Raw::PhotoModeSystem::SpawnSlot::Ref(s_photoModeSystem);
    if (spawnSlot >= 0 && spawnSlot <= 2)
    {
        auto character = spawnList[spawnSlot];
        if (character && (character->characterIndex == aCharacterIndex || aCharacterIndex == -1))
        {
            auto& addon = s_characterAddons[character->characterIndex];

            auto event = Red::MakeHandle<Red::gameuiSetupOptionSelectorForAttributeEvent>();
            event->attribute = CharacterAppearanceAttribute;
            event->values = addon.appearanceOptions;
            event->startDataValue = addon.appeanceIndex;
            event->doApply = true;

            Raw::PhotoModeMenuController::FireSetupOptionSelectorEvent(s_photoModeController, *event);
        }
    }
}

void App::PhotoModeExService::FillWeaponTypes(Red::DynArray<Red::gamedataItemType>& aItemTypes)
{
    auto itemTypeCount = static_cast<uint32_t>(Red::gamedataItemType::Count);
    aItemTypes.Reserve(itemTypeCount);

    for (auto itemType = 0; itemType < itemTypeCount; ++itemType)
    {
        aItemTypes.PushBack(static_cast<Red::gamedataItemType>(itemType));
    }
}

Red::CString App::PhotoModeExService::GetLocalizedText(Red::CName aKey)
{
    Red::CString text;
    Red::CallGlobal("GetLocalizedTextByKey", text, aKey);
    return text;
}
