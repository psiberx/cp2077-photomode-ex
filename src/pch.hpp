#pragma once

#include <algorithm>
#include <codecvt>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <future>
#include <map>
#include <memory>
#include <ranges>
#include <regex>
#include <set>
#include <source_location>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <RED4ext/RED4ext.hpp>

#include <RED4ext/JobQueue.hpp>
#include <RED4ext/ResourceDepot.hpp>
#include <RED4ext/ResourceLoader.hpp>
#include <RED4ext/Scripting/Natives/Generated/appearance/AppearanceDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/appearance/AppearancePartOverrides.hpp>
#include <RED4ext/Scripting/Natives/Generated/appearance/AppearanceResource.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/Entity.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/EntityID.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/EntityTemplate.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/IComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/ITransformBinding.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/SimpleColliderComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/SlotComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/VisualTagsSchema.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/IPersistencySystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ITransactionSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/PersistentState.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/PhotoModeAttachmentSlotsListener.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/PhotoModeSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/Puppet.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ScriptableSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/data/Character_Record.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/data/ItemType.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ui/PhotoModeMenuController.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ui/PhotoModeOptionGridButtonData.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ui/PhotoModeOptionSelectorData.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ui/SetupOptionSelectorForAttributeEvent.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/IRuntimeSystem.hpp>
#include <RED4ext/Scripting/Natives/ScriptGameInstance.hpp>
#include <RED4ext/StringView.hpp>

#include <nameof.hpp>
#include <semver.hpp>

#include "Core/Raw.hpp"
#include "Core/Stl.hpp"

#include "Red/Alias.hpp"
#include "Red/Engine.hpp"
#include "Red/Specializations.hpp"
#include "Red/TypeInfo.hpp"
#include "Red/Utils.hpp"

#include "Red/Addresses/Library.hpp"
