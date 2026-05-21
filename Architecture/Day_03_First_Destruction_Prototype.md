# Day 03 Architecture Note - First Destruction Prototype

## Purpose
Day 03 introduces the first practical destruction prototype and begins connecting Unreal Chaos behaviour to the MVCD framework architecture.

## Prototype Goal
The first prototype should prove that:
- a destructible object can exist in the sandbox,
- Chaos/Geometry Collection setup works,
- destruction behaviour can be triggered,
- the framework can later route destruction through events instead of direct ad-hoc logic.

## Early Destruction Event Concept

A future destruction event may contain:

```text
DestructionEvent
├── Source Actor
├── Target Actor
├── Impact Location
├── Impact Direction
├── Damage Amount
├── Damage Type
├── Material/Resistance Data
├── Replication ID
└── Timestamp
```

## Responsibility Split

### Destructible Actor / Component
- Owns local destructible state
- Receives damage/destruction requests
- Applies local destruction response

### Destruction Manager
- Coordinates destruction events
- Tracks active destruction objects
- Prepares future benchmark/stat tracking

### Replication Component
- Future responsibility for sending destruction events/states across the network
- Should avoid full physics chunk replication

## Day 03 Rule
Do not overbuild. The goal is to create the first testable destruction loop, not the final system.
