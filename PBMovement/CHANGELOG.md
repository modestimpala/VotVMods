# 1.0.4

* New: **Speed music** (`[Music]`). Play a local WAV, MP3, or FLAC after exceeding `SpeedOn` (`800` uu/s); it fades out below `SpeedOff` (`650`). An empty `File` disables it. VotV’s music and master volume sliders apply. Requires `EnableGraft = true`.

* Fixed: **Forward bunnyhops no longer lose speed** (`[ABH] JumpBonusNeverSlows`, default: `true`). Jump bonuses that would slow the player are discarded; ABH, AFH, and ASH are unchanged. Set to `false` for Source behavior.

* Fixed: **Air-strafe acceleration is now frame-rate consistent** (`[Misc] SimulationTimeStep`, now `1/33`). This avoids extra movement steps above 33 FPS and matches Half-Life 2 single-player behavior.

* Fixed: **Exhaustion now prevents sprinting** (`[Misc] RespectExhaustion`, default: `true`), including ABH and swimming. Dreams still ignore vitals.

* Fixed: **Sprint now honors agility and heavy carry.** Agility scales sprint up to 1.25×; heavy carry uses a 183.3375 uu/s gait instead of crouch speed.


# 1.0.3

* Fixed: **Swimming is no longer a crawl** (`[Water] EnableWaterMove`, default: `true`). Water now uses HL2-style swimming instead of the air-movement code that capped it at roughly 57 uu/s. Swimming speed is controlled by `WaterSpeedFraction`, while `WaterFriction` controls drag. Scuba still improves your speed: roughly 210 uu/s without air and 280 with it. Sprinting and crouching no longer change your speed while fully submerged. Vertical movement still uses VotV’s existing swim controls.

* Changed: **Waist-deep water now makes you swim even when standing on the bottom** (`SwimWhenWaistDeep`, default: `true`). This matches HL2 and prevents sprinting along the bottom of deep water. Set it to `false` for VotV’s original behavior. Shallow wading is unchanged, and standing on the bottom no longer makes you bob.

* New: **Rivers now carry the player** (`EnableWaterCurrent`, default: `true`). River currents now push you in the same direction as floating objects. On the main map, this produces about 500 uu/s² of acceleration: idling drifts at roughly 85 uu/s, swimming downstream reaches around 300, and swimming upstream remains possible. Adjust `WaterCurrentScale` to change the strength, or set it to `0` to disable currents.

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