# Day 03 - First Destruction Actor Prototype

## Status
- State: Completed
- Date: 21/05/2026
- Hours Worked: 4h
- Main Focus: Create the first destruction actor prototype and prepare the framework for damage-event based destruction.

## Planned Tasks
- [x] Create first destructible test actor class
- [x] Create or prepare a basic Geometry Collection test asset
- [x] Add initial destruction event concept
- [x] Connect destruction actor to existing destruction framework classes
- [x] Test basic destruction behaviour in a sandbox level
- [x] Capture evidence screenshots
- [x] Compile project successfully

## Work Completed
- [x] Created the first destruction testing sandbox level.
- [x] Created BP_TestDestructibleBuilding as the initial destruction prototype actor.
- [x] Generated the GC_TestWall Geometry Collection asset from a static mesh.
- [x] Applied Uniform Voronoi fracture with 25 fracture sites.
- [x] Verified fracture generation through Explode View visualization.
- [x] Confirmed Chaos physics simulation on the Geometry Collection asset.
- [x] Established the first destruction testing workflow inside Unreal Engine.
- [x] Documented the destruction event architecture and framework responsibilities.
- [x] Captured implementation evidence for repository publication.

## Technical Notes
The first destruction prototype was implemented using a Geometry Collection workflow. A simple static mesh was converted into a Geometry Collection and fractured using Uniform Voronoi fracture generation with 25 fracture sites.

The fracture hierarchy was verified through the Explode View tool, confirming that Chaos successfully generated independent destruction chunks. Physics simulation and gravity settings were tested to validate interaction with the Chaos system.

A sandbox level was created specifically for destruction experiments. The level provides an isolated environment for testing Geometry Collections, future damage events and destruction framework behaviour.

The destruction framework classes created during Day 02 remain intentionally lightweight. The current prototype focuses on validating the Chaos workflow before introducing complex destruction logic. The planned architecture separates destruction management, local destruction behaviour and future replication responsibilities into dedicated framework classes.

## Problems Encountered
- MVCDDestructionComponent was not available for Blueprint attachment because Blueprint exposure has not yet been implemented.
- Initial expectations assumed Geometry Collections would fracture automatically when falling, however fracture generation and destruction triggering are separate systems within Chaos.
- Additional investigation was required to understand fracture visualization using Explode View and the relationship between chunk generation and runtime destruction.

## Solutions / Decisions
- The destruction component will remain a framework-level C++ component until Blueprint exposure becomes necessary.
- The first prototype intentionally prioritizes Chaos workflow validation rather than gameplay functionality.
- Geometry Collection verification is performed through fracture visualization before introducing runtime destruction triggers.
- Future destruction behaviour will be driven by destruction events routed through the Destruction Manager rather than actor-specific logic.
- Replication responsibilities will remain isolated inside dedicated framework components to support future multiplayer implementation.

## Evidence Captured
- Screenshot: Framework_Classes_Visible.png
- Screenshot: Test_Destructible_Actor.png
- Screenshot: Geometry_Collection_Setup.png
- Screenshot: First_Destruction_Test.png
- Screenshot: Destruction_Framework_Notes.png
- Commit: First destruction prototype and Geometry Collection workflow

## Dissertation Notes
This day begins the practical destruction prototype stage. The goal is to move from project architecture into a testable destruction workflow while keeping the system modular and suitable for later multiplayer synchronization.

## Tomorrow
- [ ] Refine destruction event data structure
- [ ] Add basic damage values/material resistance idea
- [ ] Improve destruction manager communication
- [ ] Prepare first benchmark-style destruction test
