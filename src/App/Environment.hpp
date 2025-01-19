#pragma once

#include "Core/Facades/Runtime.hpp"

namespace App::Env
{
inline std::filesystem::path ScriptsDir()
{
    return Core::Runtime::GetModuleDir() / L"Scripts";
}

inline std::filesystem::path LegacyScriptsDir()
{
    return Core::Runtime::GetRootDir() / L"r6" / L"scripts" / L"PhotoModeEx";
}

inline std::filesystem::path PreReleaseScriptFile()
{
    return Core::Runtime::GetRootDir() / L"r6" / L"scripts" / L"PhotoModeEx.reds";
}

inline std::filesystem::path GameDir()
{
    return Core::Runtime::GetRootDir();
}
}
