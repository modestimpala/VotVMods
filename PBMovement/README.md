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


### Music at speed (`[Music]`)

Play a song of your own once you are actually moving fast. **No music ships with
the mod** - drop a file in the same folder as `main.dll` and name it:

```ini
[Music]
File = The Laser Dance Song.mp3 ; Example
```

WAV, MP3 and FLAC work (OGG does not). It fades in once you pass `SpeedOn`
(`800` uu/s) and fades back out below `SpeedOff` (`650`). Both defaults are
*above* your sprint speed on purpose - sprinting alone won't start it, you have
to have built real speed by bunnyhopping, ABH or surfing.

| Setting | What it does |
|---|---|
| `File` | Your song. Empty (the default) turns the feature off entirely. |
| `SpeedOn` / `SpeedOff` | Fade in at/above the first, out below the second. The gap stops it flickering while you hover at the threshold. |
| `Volume` | `0`-`1`. Your in-game volume sliders still apply on top. |
| `FadeIn` / `FadeOut` | Seconds for each fade. |
| `Loop` | Repeat while you stay fast. |
| `RestartEachTime` | `false` = a brief dip resumes where it left off. `true` = always start from the top. |

Requires `EnableGraft = true` (with the graft off there is no movement tick to
read your speed from).

### Surf feel (if ramps don't behave)

Nothing to tune: whether a ramp catches you is decided the way Project Borealis
decides it; if sliding along the surface would throw you upward faster than a
jump, it isn't treated as a floor and you surf. `BounceMultiplier` in `[Surf]`
is the only knob left (extra bounce off slope clips; `0` = none).

The remaining sections (`[Acceleration]`, `[Braking]`, `[EdgeFriction]`,
`[Slope]`, `[Misc]`) are for fine-tuning the exact feel - the defaults match
Project Borealis, so you can leave them alone unless you're chasing a specific
feel.


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