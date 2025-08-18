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
    uint64_t unk48;                                    // 48
    uint64_t unk50;                                    // 50
    uint32_t characterIndex;                           // 58
    PhotoModeCharacterType characterType;              // 5C
    gamedataItemType itemType;                         // 60
    uint32_t unk64;                                    // 64
    uint8_t unk68;                                     // 68
    uint8_t unk69;                                     // 69
    uint8_t unk6A;                                     // 6A
    uint8_t unk6B;                                     // 6B
    uint32_t unk6C;                                    // 6C
    uint8_t unk70;                                     // 70
    uint8_t unk71;                                     // 71
    uint8_t unk72;                                     // 72
    uint8_t unk73;                                     // 73
    uint64_t unk78;                                    // 78
    uint64_t unk80;                                    // 80
    Vector3 relativePosition;                          // 88
    bool updateTransform;                              // 94
    bool unk95;                                        // 95
    uint8_t unk96;                                     // 96
    uint8_t unk97;                                     // 97
    uint64_t unk98;                                    // 98
    uint64_t unkA0;                                    // A0
    uint32_t unkA8;                                    // A8
    uint32_t categoryIndex;                            // AC
    bool allowLookAtCamera;                            // B0
    uint32_t unkB4;                                    // B4
    uint32_t unkB8;                                    // B8
    uint32_t unkBC;                                    // BC
    uint32_t unkC0;                                    // C0
    uint32_t unkC4;                                    // C4
    uint32_t unkC8;                                    // C8
    bool unkCC;                                        // CC
    CName lookAtCameraPreset;                          // D0
    uint64_t unkD8;                                    // D8
    uint64_t unkE0;                                    // E0
    uint8_t unkE8;                                     // E8
    float spawnedState;                                // EC
    float categoryState;                               // F0
    float poseState;                                   // F4
    uint32_t unkF8;                                    // F8
    float lootAtCameraState;                           // FC
    uint32_t unk100;                                   // 100
    float relativeRotation;                            // 104
    float relativeOffsetRight;                         // 108
    float relativeOffsetForward;                       // 10C
    Quaternion spawnOrientation;                       // 110
    Vector3 spawnPosition;                             // 120
    uint32_t state;                                    // 12C
    uint8_t unk130[0x17C-0x130];                       // 130
    int32_t unk17C;                                    // 17C
    uint8_t unk180[0x190-0x180];                       // 180
};
RED4EXT_ASSERT_SIZE(PhotoModeCharacter, 0x190);
RED4EXT_ASSERT_OFFSET(PhotoModeCharacter, puppet, 0x0);
RED4EXT_ASSERT_OFFSET(PhotoModeCharacter, characterIndex, 0x58);
RED4EXT_ASSERT_OFFSET(PhotoModeCharacter, characterType, 0x5C);
RED4EXT_ASSERT_OFFSET(PhotoModeCharacter, relativePosition, 0x88);
RED4EXT_ASSERT_OFFSET(PhotoModeCharacter, updateTransform, 0x94);
RED4EXT_ASSERT_OFFSET(PhotoModeCharacter, lookAtCameraPreset, 0xD0);
RED4EXT_ASSERT_OFFSET(PhotoModeCharacter, spawnOrientation, 0x110);
RED4EXT_ASSERT_OFFSET(PhotoModeCharacter, spawnPosition, 0x120);
RED4EXT_ASSERT_OFFSET(PhotoModeCharacter, state, 0x12C);
}

namespace Raw::PhotoModeSystem
{
using PlayerList = Core::OffsetPtr<0x130, Red::DynArray<Red::PhotoModeCharacter>>;
using PlayerBgOffset = Core::OffsetPtr<0x170, Red::Vector3>;
using Player = Core::OffsetPtr<0x140, Red::PhotoModeCharacter*>;
using CharacterList = Core::OffsetPtr<0x180, Red::DynArray<Red::PhotoModeCharacter>>;
using CharacterBgOffset = Core::OffsetPtr<0x1C0, Red::Vector3>;
using SpawnList = Core::OffsetPtr<0x1D0, Red::PhotoModeCharacter*[3]>;
using EditSlot = Core::OffsetPtr<0x36C, uint32_t>;
using SpawnSlot = Core::OffsetPtr<0x370, uint32_t>;

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
                          Red::DynArray<Red::gameuiPhotoModeOptionSelectorData>& aOutPoses)>();

constexpr auto ResolveCurrentPose = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_ResolveCurrentPose,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex,
                          uint32_t* aOutCategoryIndex, uint32_t* aOutPoseIndex)>();

constexpr auto GetAvailableCategoriesCount = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_GetAvailableCategoriesCount,
    /* type = */ uint64_t (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex)>();

constexpr auto GetAvailablePosesCount = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_GetAvailablePosesCount,
    /* type = */ uint64_t (*)(Red::gamePhotoModeSystem* aSystem, uint32_t aCharacterIndex, uint32_t aCategoryIndex)>();

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
                          const Red::Transform& aSpawnTransform, uint64_t a5)>();

constexpr auto ApplyPuppetTransforms = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_ApplyPuppetTransforms,
    /* type = */ void (*)(Red::gamePhotoModeSystem* aSystem, Red::DynArray<Red::PhotoModeCharacter>& aCharacterList,
                          uint8_t aCharacterGroup)>();

constexpr auto SetRelativePosition = Core::RawFunc<
    /* addr = */ Red::AddressLib::PhotoModeSystem_SetRelativePosition,
    /* type = */ void (*)(Red::gamePhotoModeSystem *aSystem, void* a2, uint8_t a3, uint8_t aCharacterGroup)>();

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
