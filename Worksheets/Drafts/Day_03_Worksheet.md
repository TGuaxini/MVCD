# Worksheet - Day 03: First Destruction Actor Prototype

## Objective
Create the first usable destruction prototype in Unreal Engine and begin connecting Chaos destruction behaviour to the MVCD framework architecture.

## Time Budget
Total: 4 hours

---

# Block 1 - Review Current Framework
Estimated time: 30 minutes

- [x] Open the UE5 project
- [x] Confirm project compiles successfully
- [x] Confirm existing framework classes exist:
  - [x] MVCDGameState
  - [x] MVCDDestructionManager
  - [x] MVCDDestructionComponent
  - [x] MVCDDestructionReplicationComp
- [x] Open the test/sandbox level or create a temporary one

## Evidence
- [x] Screenshot: Framework_Classes_Visible.png

---

# Block 2 - Create First Destructible Actor Prototype
Estimated time: 1 hour

Create a first test actor or Blueprint using the destruction architecture.

Recommended approach:
- [x] Create a simple test actor for destruction experiments
- [x] Add a Static Mesh or Geometry Collection component
- [ ] Add/attach MVCDDestructionComponent if appropriate
- [x] Keep logic minimal
- [x] Focus on creating a testable object, not a final system

Suggested class/asset names:
- [x] BP_TestDestructibleBuilding
- [ ] GC_TestWall or GC_TestBuildingBlock
- [x] L_TestDestructionSandbox

## Evidence
- [x] Screenshot: Test_Destructible_Actor.png

---

# Block 3 - Geometry Collection Preparation
Estimated time: 1 hour

Prepare a simple destructible asset.

- [x] Choose or create a simple mesh/block
- [x] Convert or prepare it as a Geometry Collection
- [x] Apply basic fracture settings
- [x] Confirm collision/physics settings
- [x] Place it in the sandbox level
- [x] Test if Chaos can fracture or simulate it

## Evidence
- [x] Screenshot: Geometry_Collection_Setup.png

---

# Block 4 - Basic Destruction Test
Estimated time: 45 minutes

Run a simple destruction test.

Options:
- [x] Use physics impulse
- [ ] Use field/force
- [ ] Use manual editor simulation
- [ ] Use a temporary Blueprint trigger

Goals:
- [x] Confirm destruction can happen
- [x] Observe physics behavior
- [x] Record what works and what does not

## Evidence
- [x] Screenshot: First_Destruction_Test.png

---

# Block 5 - Framework Notes
Estimated time: 30 minutes

Document:
- [x] how destruction should be triggered in the future
- [x] what data a destruction event should contain
- [x] what should be handled by the manager
- [x] what should be handled by the actor/component
- [x] what should eventually replicate over the network

## Evidence
- [x] Screenshot: Destruction_Framework_Notes.png

---

# Block 6 - Commit and Documentation
Estimated time: 15 minutes

- [x] Update daily log
- [ ] Store screenshots in docs/assets/screenshots/Day_03/
- [ ] Run evidence generation script if Python is available
- [ ] Update progress.json after completion
- [ ] Commit changes
- [ ] Push origin

---

# Done Criteria

- [ ] First destruction prototype asset exists
- [ ] Basic Geometry Collection test exists
- [ ] Basic destruction behavior was tested
- [ ] Framework direction was documented
- [ ] Evidence screenshots captured
- [ ] Daily log updated
- [ ] Repository pushed
