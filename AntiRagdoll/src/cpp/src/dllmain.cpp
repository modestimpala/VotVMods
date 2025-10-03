#include <Mod/CppUserModBase.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>
#include <game.hpp>

#include "Hooks.hpp"
#include "UClass.hpp"
#include "UFunction.hpp"

using namespace RC;
using namespace RC::Unreal;

class AntiRagdollCppCpp : public RC::CppUserModBase
{
public:
    AntiRagdollCppCpp() : CppUserModBase()
    {
        ModName = STR("AntiRagdoll");
        ModVersion = STR("1.0");
        ModDescription = STR("Never ragdoll again!");
        ModAuthors = STR("ModestImpala");

        Output::send<LogLevel::Normal>(STR("AntiRagdoll: Initialized\n"));
    }

    ~AntiRagdollCppCpp() override = default;

    auto on_unreal_init() -> void override
    {
        // Wait for mainPlayer to spawn, then set up the ragdoll hook (just to make sure the class is loaded)
        Hook::RegisterStaticConstructObjectPostCallback(
            [this](const FStaticConstructObjectParameters& Params, UObject* ConstructedObject) -> UObject*
            {
                if (!ConstructedObject || ragdoll_hook_registered_)
                {
                    return nullptr;
                }


                auto* actor = Cast<AActor>(ConstructedObject);
                if (!actor) return nullptr;

                auto actor_name = actor->GetClassPrivate()->GetNamePrivate();
                if (actor_name == Unreal::FName(STR("mainPlayer_C"), FNAME_Add))
                {
                    setup_ragdoll_hook(actor);
                    ragdoll_hook_registered_ = true;

                    Output::send<LogLevel::Normal>(
                        STR("AntiRagdoll: Main player found, ragdoll hook registered\n")
                    );
                }


                return nullptr;
            });

        Output::send<LogLevel::Normal>(STR("AntiRagdoll: Waiting for main player spawn\n"));
    }

private:
    std::pair<int, int> ragdoll_mode_hook_;
    bool ragdoll_hook_registered_ = false;

    void setup_ragdoll_hook(AActor* main_player)
    {
        if (!main_player) return;

        ragdoll_mode_hook_ = UObjectGlobals::RegisterHook(
            STR("/Game/main/mainPlayer.mainPlayer_C:ragdollMode"),
            [](Unreal::UnrealScriptFunctionCallableContext& Context, void* CustomData) -> void
            {
                // Pre-hook logic
                Output::send<LogLevel::Normal>(STR("AntiRagdoll: ragdollMode called (pre-hook)\n"));

                // Define func parameter structure
                struct RagdollParams
                {
                    bool ragdoll;
                    bool passOut;
                    bool death;
                };

                // Try to read and modify parameters
                auto& params = Context.GetParams<RagdollParams>();

                if (params.ragdoll)
                {
                    Output::send<LogLevel::Normal>(STR("AntiRagdoll: Preventing ragdoll\n"));
                    params.ragdoll = false; // Try to prevent ragdoll
                }
            },
            [](Unreal::UnrealScriptFunctionCallableContext& Context, void* CustomData) -> void
            {
                // Post-hook logic 
                Output::send<LogLevel::Normal>(STR("AntiRagdoll: ragdollMode completed (post-hook)\n"));
            },
            nullptr
        );

        Output::send<LogLevel::Normal>(STR("AntiRagdoll: ragdollMode hook registered\n"));
    }
};

#define ANTIRAGDOLLCPP_MOD_API __declspec(dllexport)

extern "C" {
ANTIRAGDOLLCPP_MOD_API RC::CppUserModBase* start_mod()
{
    return new AntiRagdollCppCpp();
}

ANTIRAGDOLLCPP_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
{
    delete mod;
}
}
