#include "Application.hpp"
#include "App/Environment.hpp"
#include "App/Migration.hpp"
#include "App/PhotoMode/PhotoModeExService.hpp"
#include "App/PhotoMode/PhotoModeNpcPatch.hpp"
#include "App/Project.hpp"
#include "Core/Foundation/LocaleProvider.hpp"
#include "Core/Foundation/RuntimeProvider.hpp"
#include "Support/MinHook/MinHookProvider.hpp"
#include "Support/RED4ext/RED4extProvider.hpp"
#include "Support/RedLib/RedLibProvider.hpp"
#include "Support/Spdlog/SpdlogProvider.hpp"

App::Application::Application(HMODULE aHandle, const RED4ext::Sdk* aSdk)
{
    Register<Core::LocaleProvider>();
    Register<Core::RuntimeProvider>(aHandle)
        ->SetBaseImagePathDepth(2);

    Register<Support::MinHookProvider>();
    Register<Support::SpdlogProvider>()
        ->AppendTimestampToLogName()
        ->CreateRecentLogSymlink();
    Register<Support::RED4extProvider>(aHandle, aSdk)
        ->EnableAddressLibrary()
        ->RegisterScripts(Env::ScriptsDir());
    Register<Support::RedLibProvider>();

    Register<App::PhotoModeExService>();
    Register<App::PhotoModeNpcPatch>();
}

void App::Application::OnStarting()
{
    LogInfo("{} {} is initializing...", Project::Name, Project::Version.to_string());

    Migration::CleanUp(Env::LegacyScriptsDir());
    Migration::CleanUp(Env::PreReleaseScriptFile());
}

void App::Application::OnStarted()
{
    LogInfo("{} is initialized.", Project::Name);
}
