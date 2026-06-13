# PB Movement for Voices of the Void

Gives your character **Half-Life 2 / Source-engine movement** - air-strafing, bunnyhopping, and **surfing** - in place of VotV's default movement.

## What you get

**Air-strafing**, **bunnyhop** (manual or auto), **surfing** on steep ramps Source-style, classic HL2/Source style character movment straight from Project Borealis. 

> Built for **VotV a09 / a09n**. 

## Configuring it - `PBMovement.ini`

| Setting | What it does |
|---|---|
| `EnableGraft` | `true`/`false` master switch. Set to `false` to temporarily get vanilla VotV movement back without uninstalling. |
| `RunSpeed` | Your normal move speed. PB defaults are HL2-scale. |
| `SprintSpeed` | Speed while holding your run key. |
| `WalkSpeed` | Slow-walk speed. |
| `JumpZVelocity` | How high you jump. |
| `AutoBunnyhop` | `true` = hold jump to auto-bhop. `false` = you must tap jump each time. |
| `AirControl` | How much you can steer mid-air. `1.0` is full HL2-style control. |

### Surf feel (if ramps don't behave)

| Setting | What it does |
|---|---|
| `SurfEntrySpeed` | How fast you must be falling/moving to "stick" to a ramp instead of just landing on it. Lower it if you slide off ramps you wanted to surf; raise it if you stick to little bumps you'd rather walk over. |
| `SurfEntryMaxNormalZ` | How steep a ramp has to be to surf. Raise toward `1.0` to surf gentler ramps; lower it to require steeper ones. |

The remaining sections (`[Acceleration]`, `[Braking]`, `[EdgeFriction]`,
`[Slope]`, `[Misc]`) are for fine-tuning.


## How it works

PB's `UPBPlayerMovement`/`APBPlayerCharacter` are native engine classes that
*can't* be registered into the shipped game, so instead of instantiating them we
**port PB's logic into the mod** and graft it onto VotV's existing
`UCharacterMovementComponent`. Two techniques:

1. **Per-instance vtable swap**:
   on player spawn we copy the component's vtable, point the movement virtuals
   (`CalcVelocity`, `DoJump`, `HandleSlopeBoosting`, `GetMaxSpeed`,
   `NewFallVelocity`, `ShouldLimitAirControl`) at our ported C++, and swap the
   instance's vtable pointer. Only the player's component is affected.
2. **Blueprint bytecode patch**: VotV's settings
   graph overwrote `AirControl`/`JumpZVelocity` every load, so we `NopRange`
   those two `EX_Let` writes in `ExecuteUbergraph_mainPlayer` (size-preserving)
   so PB's values stick.

## Credits & license

Movement design and reference implementation by **Project Borealis**
([PBCharacterMovement](https://github.com/ProjectBorealis/PBCharacterMovement)),
which is released under the [**MIT License**](https://github.com/ProjectBorealis/PBCharacterMovement?tab=MIT-1-ov-file#readme). This mod ports that movement logic and grafts it onto VotV's player at runtime.

Physics reference from Jiangwei Chong's [Half-Life Physics Reference](https://www.jwchong.com/hl/movement.html)