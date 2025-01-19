#pragma once

namespace Red
{
enum class PhotoModeCharacterType : uint32_t
{
    Invalid = 0,
    PlayerFemale = 1,
    PlayerMale = 2,
    NPC = 4,
};

struct PhotoModeCharacter
{
    Handle<gamePuppet> puppet;                         // 00
    Handle<entSimpleColliderComponent> collider;       // 10
    Handle<gameIAttachmentSlotsListener> slotListener; // 20
    uint32_t unk30;                                    // 30
    uint32_t unk34;                                    // 38
    uint32_t unk38;                                    // 38
    uint32_t unk3C;                                    // 40
    uint64_t unk40;                                    // 40
    uint32_t characterIndex;                           // 48
    PhotoModeCharacterType characterType;              // 4C
    uint64_t unk50;                                    // 50
    uint8_t unk58;                                     // 58
    uint8_t unk59;                                     // 59
    uint8_t unk5A;                                     // 5A
    uint8_t unk5B;                                     // 5B
    uint32_t unk5C;                                    // 5C
    uint8_t unk60;                                     // 60
    uint8_t unk61;                                     // 61
    uint8_t unk62;                                     // 62
    uint8_t unk63;                                     // 63
    uint64_t unk68;                                    // 68
    uint64_t unk70;                                    // 70
    Vector3 relativePosition;                          // 78
    bool updateTransform;                              // 84
    bool unk85;                                        // 85
    uint8_t unk86;                                     // 86
    uint8_t unk87;                                     // 87
    uint64_t unk88;                                    // 88
    uint64_t unk90;                                    // 90
    uint32_t unk98;                                    // 98
    uint32_t unk9C;                                    // 9C
    bool allowLookAtCamera;                            // A0
    uint32_t unkA4;                                    // A4
    uint32_t unkA8;                                    // A8
    uint32_t unkAC;                                    // AC
    uint32_t unkB0;                                    // B0
    uint32_t unkB4;                                    // B4
    uint32_t unkB8;                                    // B8
    bool unkBC;                                        // BC
    CName lookAtCameraPreset;                          // C0
    uint64_t unkC8;                                    // C8
    uint64_t unkD0;                                    // D0
    uint8_t unkD8;                                     // D8
    float spawnedState;                                // DC
    uint32_t unkE0;                                    // E0
    uint32_t unkE4;                                    // E4
    uint32_t unkE8;                                    // E8
    float lootAtCameraState;                           // EC
    uint32_t unkF0;                                    // F0
    float relativeRotation;                            // F4
    float relativeOffsetRight;                         // F8
    float relativeOffsetForward;                       // FC
    Quaternion spawnOrientation;                       // 100
    Vector3 spawnPosition;                             // 110
    uint32_t state;                                    // 11C
};
RED4EXT_ASSERT_SIZE(PhotoModeCharacter, 0x120);
RED4EXT_ASSERT_OFFSET(PhotoModeCharacter, characterIndex, 0x48);
RED4EXT_ASSERT_OFFSET(PhotoModeCharacter, lookAtCameraPreset, 0xC0);
}

namespace Raw::PhotoModeSystem
{
using PlayerList = Core::OffsetPtr<0x130, Red::DynArray<Red::PhotoModeCharacter>>;
using PlayerBgOffset = Core::OffsetPtr<0x170, Red::Vector3>;
using Player = Core::OffsetPtr<0x140, Red::PhotoModeCharacter*>;
using CharacterList = Core::OffsetPtr<0x180, Red::DynArray<Red::PhotoModeCharacter>>;
using CharacterBgOffset = Core::OffsetPtr<0x1C0, Red::Vector3>;
using SpawnList = Core::OffsetPtr<0x1D0, Red::PhotoModeCharacter*[3]>;
using SpawnSlot = Core::OffsetPtr<0x3A0, uint32_t>;
using EditSlot = Core::OffsetPtr<0x39C, uint32_t>;

constexpr auto Activate = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_Activate,
    /* type = */ bool (*)(Red::gamePhotoModeSystem* aSystem)>();

constexpr auto Finalize = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_Finalize,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem)>();

constexpr auto Deactivate = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_Deactivate,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem)>();

constexpr auto GetAttributeValue = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_GetAttributeValue,
    /* type = */ void (*)(Red::gamePhotoModeSystem *aSystem, uint32_t aAttribute, float& aValue)>();

constexpr auto SetAttributeValue = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_SetAttributeValue,
    /* type = */ void (*)(Red::gamePhotoModeSystem *aSystem, uint32_t aAttribute, float aValue, bool aApply)>();

constexpr auto ProcessAttribute = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_ProcessAttribute,
    /* type = */ void (*)(Red::gamePhotoModeSystem *aSystem, uint32_t aAttribute)>();

constexpr auto RegisterCharacter = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_RegisterCharacter,
    /* type = */ bool (*)(Red::gamePhotoModeSystem* aSystem,
                          uint32_t aCharacterIndex,
                          Red::DynArray<Red::PhotoModeCharacter>& aCharacterList,
                          Red::PhotoModeCharacterType aCharacterType,
                          Red::DynArray<Red::gamedataItemType>& aItemTypes,
                          Red::DynArray<Red::Handle<Red::gameItemObject>>& aClothingItems)>();

constexpr auto ValidateCharacter = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_ValidateCharacter,
    /* type = */ bool (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex)>();

constexpr auto RegisterPoses = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_RegisterPoses,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                          Red::PhotoModeCharacterType aCharacterType)>();

constexpr auto RegisterWeaponPoses = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_RegisterWeaponPoses,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                          Red::DynArray<Red::gamedataItemType>& aItemTypes)>();

constexpr auto RegisterClothingItems = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_RegisterClothingItems,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                          Red::DynArray<Red::Handle<Red::gameItemObject>>& aClothingItems)>();

constexpr auto PrepareCategories = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_PrepareCategories,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex, uint64_t a3)>();

constexpr auto PreparePoses = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_PreparePoses,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex, uint32_t aCategoryIndex,
                          uint64_t a4)>();

constexpr auto PrepareCameras = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_PrepareCameras,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex, uint32_t* a3, uint32_t* a4)>();

constexpr auto UpdateCategoryDependents = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_UpdateCategoryDependents,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCategoryIndex,
                          Red::PhotoModeCharacter* aCharacter, uint64_t a4)>();

constexpr auto UpdatePoseDependents = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_UpdatePoseDependents,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCategoryIndex, uint32_t aPoseIndex,
                          Red::PhotoModeCharacter* aCharacter)>();

constexpr auto CalculateSpawnTransform = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_CalculateSpawnTransform,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, Red::Transform& aSpawnTransform,
                          const Red::Transform& aInitialTransform, uint64_t* a4, bool a5)>();

constexpr auto CalculateGroundOffset = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_CalculateGroundOffset,
    /* type = */ float (*)(Red::gamePhotoModeSystem* aSystem, Red::Vector3* aPosition, uint64_t a4, uint64_t a5)>();

constexpr auto AdjustPuppetPosition = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_AdjustPuppetPosition,
    /* type = */ void (*)(Red::Vector3* aResult, uint64_t* a2, uint64_t* a3, uint64_t* a4, Red::Vector3* aPosition,
                          Red::Vector3* aOffset, uint64_t* a7)>();

constexpr auto SpawnCharacter = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_SpawnCharacter,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, Red::PhotoModeCharacter* aCharacter,
                          uint32_t a3, const Red::Transform& aSpawnTransform, uint64_t a5)>();

constexpr auto ApplyPuppetTransforms = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_ApplyPuppetTransforms,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, Red::DynArray<Red::PhotoModeCharacter>& aCharacterList,
                          uint8_t aCharacterGroup)>();

constexpr auto SetRelativePosition = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_SetRelativePosition,
    /* type = */ void (*)(Red::gamePhotoModeSystem *aSystem, uint8_t a2, uint8_t aCharacterGroup)>();

constexpr auto SyncRelativePosition = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_SyncRelativePosition,
    /* type = */ void (*)(Red::gamePhotoModeSystem *aSystem)>();
}

namespace Raw::PhotoModeMenuController
{
constexpr auto AddMenuItem = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeMenuController_AddMenuItem,
    /* type = */ void (*)(Red::gameuiPhotoModeMenuController* aController, Red::CName aEventName,
                          const Red::CString& aLabel, uint32_t aAttribute, uint32_t aPage)>();

constexpr auto SetAttributeEnabled = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeMenuController_SetAttributeEnabled,
    /* type = */ void (*)(Red::gameuiPhotoModeMenuController* aController, uint32_t aAttribute, bool aEnabled)>();

constexpr auto SetupScrollBar = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeMenuController_SetupScrollBar,
    /* type = */ bool (*)(void* aCallback, uint64_t aEvent, uint8_t& a3, uint32_t& aAttribute, float& aStartValue,
                          float& aMinValue, float& aMaxValue, float& aStep, bool& aShowPercents)>();

constexpr auto SetupOptionSelector = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeMenuController_SetupOptionSelector,
    /* type = */ bool (*)(void* aCallback, uint64_t aEvent, uint8_t& a3, uint32_t& aAttribute,
                          Red::DynArray<Red::gameuiPhotoModeOptionSelectorData>& aElements,
                          int32_t& aDefaultIndex, bool& aApply)>();

constexpr auto SetupGridSelector = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeMenuController_SetupGridSelector,
    /* type = */ bool (*)(void* aCallback, uint64_t aEvent, uint8_t& a3, uint32_t& aAttribute,
                          Red::DynArray<Red::gameuiPhotoModeOptionGridButtonData>& aElements,
                          uint32_t& aElementsCount, uint32_t& aElementsInRow)>();

constexpr auto ForceAttributeVaulue = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeMenuController_ForceAttributeVaulue,
    /* type = */ bool (*)(void* aCallback, uint64_t aEvent, uint8_t& a3, uint32_t& aAttribute,
                          float& aValue, bool& aApply)>();

constexpr auto SetNpcImageCallback = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeMenuController_SetNpcImageCallback,
    /* type = */ void (*)(void* aCallback, uint32_t aCharacterIndex, Red::ResourcePath aAtlasPath,
                          Red::CName aImagePart, int32_t aImageIndex)>();

constexpr auto FireSetupOptionSelectorEvent = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeMenuController_FireSetupOptionSelectorEvent,
    /* type = */ void (*)(Red::gameuiPhotoModeMenuController* aController,
                          const Red::gameuiSetupOptionSelectorForAttributeEvent& aEvent)>();
}
