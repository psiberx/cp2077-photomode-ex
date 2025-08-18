#pragma once

namespace Red::AddressLib
{
constexpr uint32_t Main = 240386859;

constexpr uint32_t EngineConfig_GetInstance = 3182170505;
constexpr uint32_t EngineConfigStore_GetVar = 3758823966;

constexpr uint32_t PhotoModeMenuController_AddMenuItem = 3959824448;
constexpr uint32_t PhotoModeMenuController_SetAttributeEnabled = 1413222104;
constexpr uint32_t PhotoModeMenuController_SetupScrollBar = 1717706078;
constexpr uint32_t PhotoModeMenuController_SetupOptionSelector = 4152117147;
constexpr uint32_t PhotoModeMenuController_SetupGridSelector = 3755427483;
constexpr uint32_t PhotoModeMenuController_ForceAttributeVaulue = 1408114049;
constexpr uint32_t PhotoModeMenuController_SetNpcImageCallback = 3051761678;
constexpr uint32_t PhotoModeMenuController_FireSetupOptionSelectorEvent = 3264229194;

constexpr uint32_t PhotoModeSystem_Activate = 2593396187;
constexpr uint32_t PhotoModeSystem_Finalize = 2623149552;
constexpr uint32_t PhotoModeSystem_Deactivate = 3043759683;
constexpr uint32_t PhotoModeSystem_GetAttributeValue = 818420519;
constexpr uint32_t PhotoModeSystem_SetAttributeValue = 815536999;
constexpr uint32_t PhotoModeSystem_ProcessAttribute = 2433030483;
constexpr uint32_t PhotoModeSystem_RegisterCharacter = 3267708234;
constexpr uint32_t PhotoModeSystem_RegisterPoses = 3714525185;
constexpr uint32_t PhotoModeSystem_RegisterWeaponPoses = 788083328;
constexpr uint32_t PhotoModeSystem_RegisterClothingItems = 1375351833;
constexpr uint32_t PhotoModeSystem_UpdateCategoryDependents = 3893174133;
constexpr uint32_t PhotoModeSystem_UpdatePoseDependents = 231086722;
constexpr uint32_t PhotoModeSystem_GetAvailableCategoriesCount = 3842776524;
constexpr uint32_t PhotoModeSystem_GetAvailablePosesCount = 1623268358;
constexpr uint32_t PhotoModeSystem_PrepareCategories = 1220162374;
constexpr uint32_t PhotoModeSystem_PreparePoses = 1533423999;
constexpr uint32_t PhotoModeSystem_ResolveCurrentPose = 1972968407;
constexpr uint32_t PhotoModeSystem_CalculateSpawnTransform = 4059437596;
constexpr uint32_t PhotoModeSystem_CalculateGroundOffset = 3498779312;
constexpr uint32_t PhotoModeSystem_AdjustPuppetPosition = 2808687650;
constexpr uint32_t PhotoModeSystem_SpawnCharacter = 978529375;
constexpr uint32_t PhotoModeSystem_ApplyPuppetTransforms = 2694650124;
constexpr uint32_t PhotoModeSystem_SetRelativePosition = 1847598004;
constexpr uint32_t PhotoModeSystem_SyncRelativePosition = 4175827669;
constexpr uint32_t PhotoModeSystem_HandleCategoryChange = 4088864130;

constexpr uint32_t TweakDB_Load = 3602585178; // game::data::TweakDB::LoadOptimized
}
