# 1.0.2

* New: **Accelerated Back Hopping** (`[ABH] EnableABH`, default: `true`). Adds the Orange Box jump-speed bonus missing from PB. To ABH, jump forward, turn around in mid-air, release the movement keys, and jump again on landing. Crouching accelerates fastest. At high speed, hold S for AFH or S+A/D for ASH. Forward bunnyhops can now also reach 1.5× run speed. Set this to `false` for pure PB jumping.

* Fixed: **Crouching no longer stops you dead.** The game could reject a crouched move and zero your velocity because crouched players were not allowed to walk off ledges. That behavior is now disabled, which also allows crouched ABH to work correctly.

* Changed: **`BrakingDecelerationWalking` reduced from `381` to `190.5`**, matching PB/HL2. The old value applied more friction than crouched movement could overcome, making crouching and initial acceleration feel sluggish. Unsafe values are now clamped with a warning, and the startup log shows the acceleration and friction budget for each gait.

* Fixed: **Slopes no longer drain speed.** Horizontal ground velocity is now preserved while moving over ramps.

* Fixed: **Ramp landings now use PB’s actual landing rule.** A landing is rejected only when sliding along the surface would launch you upward faster than a normal jump. This prevents ordinary slopes from incorrectly putting you into air movement. `SurfEntrySpeed` and `SurfEntryMaxNormalZ` have been removed.

* Fixed: **`AirSlideSpeedCap` now works.** It correctly limits mid-air strafing while sliding. Air-slide crouch detection, HL2-style substepping, and over-speed checks have also been corrected to match PB.

# 1.0.1

- New: **GroundTurnFriction** ([Braking], default 8.0) - turning now grips like vanilla VotV instead of drifting. Set to 0 for the old drift. Does not affect bunnyhop landings, carried speed, or air-strafing.
- Fixed: **BrakingFriction** did nothing - the value was hardcoded internally; the INI value now actually works. 
- Changed: **BrakingDecelerationWalking** default 190.5 -> 381 
- Fixed: Ground traction is now pinned at full, and surf/air traction logic is unchanged.

New settings ([Misc])

  - **DisableRagdoll** (default false) - completely disables player ragdolling (falls, pass-outs, deaths, ragdoll key). Patches the game's ragdollMode function to a no-op; sleep/death sequences still work, only the flop is skipped.
  - **DisableFallDamageCrouch** (default true) - the game force-crouches you on non-lethal fall damage, killing all momentum. This option disables that entirely. 