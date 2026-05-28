# Day 04 - Destruction Event System Foundation

## Status
- State: Completed
- Date: 28/05/2026
- Hours Worked: 4h
- Main Focus: Establish the first destruction-event architecture and connect the destruction framework components through a centralized workflow.

## Planned Tasks
- [x] Create FMVCDDestructionEvent structure
- [x] Expand MVCDDestructionComponent architecture
- [x] Expand MVCDDestructionManager architecture
- [x] Implement first event processing flow
- [x] Define material resistance design concept
- [x] Capture implementation evidence
- [x] Compile project successfully

## Work Completed
- [x]  Created the FMVCDDestructionEvent structure.
- [x]  Defined the first standardized destruction-event data model.
- [x]  Expanded MVCDDestructionComponent with initial damage-processing architecture.
- [x]  Expanded MVCDDestructionManager with actor registration and event-processing functionality.
- [x]  Established the first framework communication workflow between manager and component.
- [x]  Implemented temporary destruction-event processing tests through BeginPlay.
- [x] Registered destructible actors through tag-based discovery.
- [x]  Verified destruction-event routing through Unreal Output Log.
- [x]  Documented the material resistance architecture concept.
- [x]  Captured framework implementation evidence screenshots.

## Technical Notes
The first formal destruction-event structure was implemented using FMVCDDestructionEvent. The structure standardizes how destruction requests are represented inside the framework and provides a scalable foundation for future gameplay, networking and benchmark systems.

The destruction workflow was expanded from isolated Chaos testing into an event-driven framework model. Destruction events are now routed through MVCDDestructionManager before reaching local destruction components.

MVCDDestructionComponent was expanded with ApplyDamage(), CanBeDestroyed() and HandleDestruction() functions to establish separation between destruction management and local actor behaviour.

MVCDDestructionManager was expanded with actor registration and destruction-event processing functionality. A temporary BeginPlay test workflow was implemented to validate communication between the manager and destruction components.

Destructible actors were registered dynamically through Actor Tags and processed through the manager. Successful event routing and damage application were verified through the Unreal Output Log.

The framework architecture now supports scalable event-based destruction processing instead of direct actor-specific destruction logic.
## Problems Encountered

- MVCDDestructionComponent initially did not appear inside Blueprint component selection.
- Unreal required BlueprintSpawnableComponent metadata for Blueprint component visibility.
- Additional project recompilation and editor restart steps were required after modifying component metadata.
- Initial confusion existed regarding actor registration flow before destruction-event processing.
- Event processing required additional includes for TActorIterator support.

## Solutions / Decisions

- MVCDDestructionComponent was configured as a BlueprintSpawnableComponent to support Blueprint integration.
- Temporary BeginPlay event processing was used to validate framework communication before gameplay integration.
- Destructible actors are currently discovered through Actor Tags as a lightweight prototype solution.
- The framework architecture prioritizes event-driven communication instead of direct actor destruction calls.
- Damage processing responsibilities remain isolated inside the destruction component while coordination remains centralized inside the destruction manager.
- Material resistance remains conceptual until the destruction-event workflow becomes stable.
- Future multiplayer support will replicate validated destruction events instead of raw physics chunk simulation.
## Evidence Captured

- Screenshot: Destruction_Event_Struct.png
- Screenshot: Destruction_Component_Expanded.png
- Screenshot: Destruction_Manager_Expanded.png
- Screenshot: Event_Processing_Test.png
- Screenshot: Material_Resistance_Notes.png
- Commit: Event-driven destruction framework foundation

## Dissertation Notes
This day introduces the first event-driven destruction architecture. Instead of destruction being triggered directly by gameplay objects, destruction requests are represented as formal framework events processed through a centralized destruction manager. This design supports future multiplayer synchronization and scalable destruction management.

## Tomorrow
- [ ] Connect destruction events to Geometry Collections
- [ ] Begin damage-response workflow
- [ ] Implement basic destruction triggering
- [ ] Expand framework testing environment