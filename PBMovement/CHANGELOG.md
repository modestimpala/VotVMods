# 1.0.1

- New: **GroundTurnFriction** ([Braking], default 8.0) - turning now grips like vanilla VotV instead of drifting. Set to 0 for the old drift. Does not affect bunnyhop landings, carried speed, or air-strafing.
- Fixed: **BrakingFriction** did nothing - the value was hardcoded internally; the INI value now actually works. 
- Changed: **BrakingDecelerationWalking** default 190.5 -> 381 
- Fixed: Ground traction is now pinned at full, and surf/air traction logic is unchanged.

New settings ([Misc])

  - **DisableRagdoll** (default false) - completely disables player ragdolling (falls, pass-outs, deaths, ragdoll key). Patches the game's ragdollMode function to a no-op; sleep/death sequences still work, only the flop is skipped.
  - **DisableFallDamageCrouch** (default true) - the game force-crouches you on non-lethal fall damage, killing all momentum. This option disables that entirely. 