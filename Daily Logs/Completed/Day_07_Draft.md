# Day 07 - Configurable Destruction Framework

## Status

- State: Complete
- Date: 17/06
- Hours Worked: 8h
- Main Focus: Replace hardcoded destruction behaviour with configurable destruction settings, object states, and benchmark-ready test actors.

---

## Planned Tasks

- [x] Create FMVCDDestructionSettings structure
- [x] Replace hardcoded component values with settings
- [x] Add destruction state tracking
- [x] Create different destruction test object types
- [x] Add destruction statistics to manager
- [x] Create benchmark-ready test setup
- [x] Validate configurable destruction behaviour
- [x] Capture evidence screenshots
- [x] Compile successfully

---

## Work Completed

- [x] Created FMVCDDestructionSettings structure
- [x] Moved hardcoded destruction values into configurable settings
- [x] Refactored MVCDDestructionComponent to use settings structure
- [x] Added configurable integrity, threshold and impulse values
- [x] Implemented EMVCDDestructionState enumeration
- [x] Added runtime destruction state evaluation
- [x] Added destruction state transition logging
- [x] Created Wood destructible variant
- [x] Created Stone destructible variant
- [x] Created Metal destructible variant
- [x] Extended destruction manager to process multiple actors
- [x] Validated object-specific destruction behaviour
- [x] Tested destruction state transitions
- [x] Captured evidence screenshots
- [x] Successfully compiled and validated framework behaviour

---

## Technical Notes

- Creation of the FMVCDDestructionSettings structure to centralize destruction configuration
- Migration of hardcoded integrity, threshold and impulse values into configurable settings
- Refactoring of MVCDDestructionComponent to initialize from configurable data
- Implementation of the EMVCDDestructionState enumeration
- Runtime destruction state evaluation based on integrity percentage
- Creation of Wood, Stone and Metal destructible variants using shared framework logic
- Extension of the destruction manager to process multiple registered destructible actors
- Validation of different destruction outcomes using identical damage events
- Runtime logging used to verify integrity calculations, state transitions and destruction responses
- Framework preparation for future benchmark and evaluation scenarios

---

## Problems Encountered

Several implementation and validation issues were encountered during development.

The first issue occurred after introducing configurable destruction settings. Although integrity values were correctly exposed in Blueprint, destruction events were being processed before all destructible actors completed initialization. As a result, damage calculations were executed using default integrity values rather than the configured settings. The problem was identified through runtime logging and temporarily resolved by delaying test event execution until actor initialization had completed.

A second issue occurred during multi-object testing. Although Wood, Stone and Metal variants had been created successfully, only a single actor was being processed by the destruction manager. Investigation revealed that only one actor instance had been registered correctly. Additional logging was introduced to inspect registration counts and actor processing order. The issue was ultimately traced to missing actor tags on placed level instances, preventing the manager from discovering all destructible actors.

A third issue appeared during validation of the destruction state system. Runtime logs indicated that state transitions were occurring correctly, but the Blueprint Details panel continued displaying the default state value. Further investigation showed that editor values did not reflect runtime instance changes during Play-In-Editor sessions. Runtime logging was therefore adopted as the primary validation method for destruction state testing.

---

## Solutions / Decisions

Several architectural decisions were made to improve framework flexibility and maintainability.

A dedicated FMVCDDestructionSettings structure was introduced to eliminate hardcoded destruction values and allow object behaviour to be controlled entirely through configuration. This approach reduces code duplication and enables future destructible objects to be created without modifying framework logic.

A destruction state system was implemented to provide a higher-level representation of object condition. Instead of relying solely on integrity values, objects can now be classified as Healthy, Damaged, Critical or Destroyed. This creates a clearer foundation for future gameplay systems such as visual feedback, audio responses, AI reactions and network synchronization.

The destruction manager was extended to process multiple registered destructible actors rather than a single test object. This change improves scalability and establishes the foundation required for benchmark testing and large-scale destruction scenarios.

Object variants were created using shared framework logic and different configuration values. Validation demonstrated that identical damage events could produce different outcomes depending on object settings, confirming that framework behaviour is now configuration-driven rather than object-specific.

The temporary use of a next-frame initialization delay was accepted for prototype validation purposes. However, future iterations should replace this mechanism with a dedicated framework initialization workflow to ensure deterministic startup behaviour.

---

## Evidence Captured

- Screenshot: Configurable_Component_Values.png
- Screenshot: Destruction_State_System.png
- Screenshot: Object_Behaviour_Variants.png
- Screenshot: Day07_Final_Test_Log.png
- Commit: Day 07 - Added configurable destruction settings and state system

---

## Dissertation Notes

This development session transformed the MVCD destruction framework from a fixed destruction prototype into a configurable destruction architecture. By introducing destruction settings, runtime state tracking and multiple object behaviour profiles, the framework now supports different destruction outcomes through configuration rather than object-specific implementations.

The addition of destruction states provides a higher-level abstraction for future gameplay systems, while configurable object variants establish the foundation for benchmark-driven evaluation and experimentation. These improvements increase framework modularity, reusability and scalability, supporting the overall objective of developing a generalized destruction framework for Unreal Engine.

---

## Tomorrow

- [ ] Refine material resistance logic
- [ ] Improve benchmark repeatability
- [ ] Add destruction result reporting
- [ ] Prepare first formal experiment