# PBMovement

A UE4SS C++ mod that grafts **Project Borealis** (Half-Life 2 style) character
movement onto **Voices of the Void**'s player at runtime - without recompiling
the game or replacing its Blueprint.

## What it does

**HL2 ground acceleration, Air-strafing, Jump, Surfing, Per-surface friction, Terminal-velocity** 

## How it works

PB's `UPBPlayerMovement`/`APBPlayerCharacter` are native engine classes that
*can't* be registered into the shipped game, so instead of instantiating them we
**port PB's logic into the mod** and graft it onto VotV's existing
`UCharacterMovementComponent`. Two techniques:

1. **Per-instance vtable swap**:
   on player spawn we copy the component's vtable, point the movement virtuals
   (`CalcVelocity`, `DoJump`, `HandleSlopeBoosting`, `GetMaxSpeed`,
   `NewFallVelocity`, `ShouldLimitAirControl`) at our ported C++, and swap the
   instance's vtable pointer. Only the player's component is affected - NPCs are
   untouched (we never patch the shared class vtable).
2. **Blueprint bytecode patch**: VotV's settings
   graph overwrote `AirControl`/`JumpZVelocity` every load, so we `NopRange`
   those two `EX_Let` writes in `ExecuteUbergraph_mainPlayer` (size-preserving)
   so PB's values stick.

## Status

Movement feature-complete. Remaining is cosmetic: camera roll, smooth crouch
resize, and the dynamic-step-height slope-slide. Ladder/noclip are out of scope.

## Credits

Movement design & reference implementation: **Project Borealis**
([PBCharacterMovement](https://github.com/ProjectBorealis/PBCharacterMovement)).
Graft/port for VotV via UE4SS.
