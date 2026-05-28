
## Purpose

The MVCD destruction framework should support different material responses instead of treating every destructible object the same way.

The goal is not to simulate real engineering material behavior exactly, but to create a simplified gameplay-oriented resistance model that can scale to large destruction environments.

## Material Categories

| Material | Resistance | Intended Behaviour |
|---|---:|---|
| Glass | 10 | Breaks easily with low damage |
| Wood | 35 | Breaks with moderate force |
| Concrete | 70 | Requires stronger impact or repeated damage |
| Steel | 100 | High resistance, should deform/break only under extreme force |

## Future Damage Logic

A future destruction event could compare:

```text
DamageAmount >= MaterialResistance