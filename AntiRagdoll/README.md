# AntiRagdoll

# DEPRECATED - no support/updates see PBMovement

This is a simple mod that prevents you from *ever* ragdolling. 

Thanks to Questwalker for discovering the crash fix - the mod now essentially forces "Player Physics Damage" setting enabled. Otherwise it causes an infinite loop then crashes on ragdoll.


Hook code:

```cpp
ragdoll_mode_hook_ = UObjectGlobals::RegisterHook(
			STR("/Game/main/mainPlayer.mainPlayer_C:ragdollMode"),
			[](Unreal::UnrealScriptFunctionCallableContext& Context, void* CustomData) -> void {

					// Define func parameter structure
					struct RagdollParams {
						bool ragdoll;
						bool passOut;
						bool death;
					};
                
					// Try to read and modify parameters
					auto& params = Context.GetParams<RagdollParams>();
                
					if (params.ragdoll) {
						Output::send<LogLevel::Normal>(STR("AntiRagdoll: Preventing ragdoll\n"));
						params.ragdoll = false;  // Try to prevent ragdoll
					}

			},
			[](Unreal::UnrealScriptFunctionCallableContext& Context, void* CustomData) -> void {
				// Post-hook logic 
			},
			nullptr 
		);
```