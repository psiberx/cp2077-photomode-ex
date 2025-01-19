#pragma once

namespace App
{
struct PhotoModeExPS : Red::PersistentState
{
    bool alternativeControls{true};
    bool snapToTerrain{false};
    bool depthOfField{false};

    RTTI_IMPL_TYPEINFO(App::PhotoModeExPS);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::PhotoModeExPS, {
    RTTI_PARENT(Red::PersistentState);
    RTTI_PERSISTENT(alternativeControls);
    RTTI_PERSISTENT(snapToTerrain);
    RTTI_PERSISTENT(depthOfField);
});
