# MVCD Framework Architecture - Initial Plan

## Project Definition
Monster Versus City Destruction is a modular Unreal Engine 5 C++ framework for demonstrating scalable destruction in a city sandbox using event-driven damage, simplified structural logic, Chaos physics, and partial multiplayer synchronization.

## Core Modules

```text
MVCD Framework
├── Damage System
├── Structural Integrity System
├── Destruction Execution System
├── Physics Interaction Layer
├── Multiplayer Synchronization Layer
├── Optimization / Cleanup Layer
└── Debug and Telemetry Layer
```

## Initial Unreal Class Ideas

```text
AMVCD_DestructibleActor
UMVCD_DamageComponent
UMVCD_StructuralIntegrityComponent
UMVCD_DestructionSyncComponent
UMVCD_DestructionDataAsset
AMVCD_DestructionManager
```

## Multiplayer Rule
Do not fully replicate physics chunks. Replicate destruction events, damage states, and deterministic destruction triggers where possible.

## Documentation Rule
Every system should have:
- purpose
- responsibility
- class list
- data flow
- multiplayer notes
- performance notes
- dissertation notes
