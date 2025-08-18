#pragma once

#include "App/PhotoMode/PhotoModeExPS.hpp"
#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/PhotoMode.hpp"

namespace App
{
class PhotoModeExService
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
protected:
    void OnBootstrap() override;

    struct CharacterSource
    {
        uint32_t index;
        Red::PhotoModeCharacterType type;
    };

    struct CharacterAddon
    {
        float relativePitch{0.0};
        float relativeRoll{0.0};
        int32_t appeanceIndex{0};
        int32_t appeanceDefaultIndex{0};
        Core::Vector<Red::CName> appearanceNames{};
        Red::DynArray<Red::gameuiPhotoModeOptionSelectorData> appearanceOptions{};
    };

    static void OnLoadTweakDB();
    static void OnActivate(Red::gamePhotoModeSystem* aSystem);
    static void OnFinalize(Red::gamePhotoModeSystem* aSystem);
    static void OnDeactivate(Red::gamePhotoModeSystem* aSystem);
    static void OnRegisterPoses(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                                Red::PhotoModeCharacterType aCharacterType);
    static void OnRegisterWeaponPoses(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                                      Red::DynArray<Red::gamedataItemType>& aItemTypes);
    static void OnPrepareCategories(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex, uint64_t a3);
    static void OnPreparePoses(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex, uint32_t aCategoryIndex,
                               Red::DynArray<Red::gameuiPhotoModeOptionSelectorData>& aOutPoses);
    static void OnResolveCurrentPose(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                                     uint32_t* aOutCategoryIndex, uint32_t* aOutPoseIndex);
    static uint64_t OnGetAvailableCategoriesCount(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex);
    static uint64_t OnGetAvailablePosesCount(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                                            uint32_t aCategoryIndex);
    static void OnUpdatePoseDependents(Red::gamePhotoModeSystem* aSystem, uint32_t aCategoryIndex, uint32_t aPoseIndex,
                                       Red::PhotoModeCharacter* aCharacter);
    static void OnCalculateSpawnTransform(Red::gamePhotoModeSystem* aSystem, Red::Transform& aSpawnTransform,
                                          const Red::Transform& aInitialTransform, uint64_t* a4, bool a5);
    static void OnSpawnCharacter(Red::gamePhotoModeSystem* aSystem, Red::PhotoModeCharacter* aCharacter,
                                 const Red::Transform& aSpawnTransform, uint64_t a5);
    static void OnApplyPuppetTransforms(Red::gamePhotoModeSystem* aSystem,
                                        Red::DynArray<Red::PhotoModeCharacter>& aCharacterList,
                                        uint8_t aCharacterGroup);
    static void OnSetRelativePosition(Red::gamePhotoModeSystem* aSystem, void* a2, uint8_t a3, uint8_t aCharacterGroup);
    static void FixRelativePosition(Red::PhotoModeCharacter* aCharacter);
    static void OnSyncRelativePosition(Red::gamePhotoModeSystem* aSystem);
    static void OnProcessAttribute(Red::gamePhotoModeSystem* aSystem, uint32_t aAttribute);
    static void OnAddMenuItem(Red::gameuiPhotoModeMenuController* aController, Red::CName aEventName,
                              const Red::CString& aLabel, uint32_t aAttribute, uint32_t aPage);
    static void OnSetAttributeEnabled(Red::gameuiPhotoModeMenuController* aController, uint32_t aAttribute,
                                      bool aEnabled);
    static void OnSetupOptionSelector(void* aCallback, uint64_t aEvent,
                                      uint8_t& a3, uint32_t& aAttribute,
                                      Red::DynArray<Red::gameuiPhotoModeOptionSelectorData>& aElements,
                                      int32_t& aDefaultIndex, bool& aApply);
    static void OnSetupGridSelector(void* aCallback, uint64_t aEvent,
                                    uint8_t& a3, uint32_t& aAttribute,
                                    Red::DynArray<Red::gameuiPhotoModeOptionGridButtonData>& aGridData,
                                    uint32_t& aElementsCount, uint32_t& aElementsInRow);
    static void OnSetupScrollBar(void* aCallback, uint64_t aEvent, uint8_t& a3,
                                 uint32_t& aAttribute, float& aStartValue, float& aMinValue, float& aMaxValue,
                                 float& aStep, bool& aShowPercents);
    static void OnForceAttributeVaulue(void* aCallback, uint64_t aEvent,
                                       uint8_t& a3, uint32_t& aAttribute, float& aValue, bool& aApply);
    static void OnSetNpcImage(void* aCallback, uint32_t aCharacterIndex, Red::ResourcePath aAtlasPath,
                              Red::CName aImagePart, int32_t aImageIndex);

    static void UpdateAppearanceList(uint32_t aCharacterIndex);
    static void FillWeaponTypes(Red::DynArray<Red::gamedataItemType>& aItemTypes);
    static Red::CString GetLocalizedText(Red::CName aKey);

    static inline Red::Handle<PhotoModeExPS> s_persistentState;
    static inline Red::gamePhotoModeSystem* s_photoModeSystem;
    static inline Red::gameuiPhotoModeMenuController* s_photoModeController;
    static inline Core::Map<uint32_t, CharacterAddon> s_characterAddons;
    static inline Red::Transform s_playerSpawnTransform;
    static inline bool s_initialized;

    static inline Core::SortedMap<uint32_t, CharacterSource> s_extraCharacters;
    static inline Core::SortedMap<Red::TweakDBID, uint32_t> s_characterIndexMap;
    static inline Core::SortedMap<uint32_t, Red::TweakDBID> s_characterRecordMap;
    static inline int32_t s_dummyCharacterIndex{0};
    static inline int32_t s_maxCharacterIndex{0};
};
}
