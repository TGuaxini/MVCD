
Destruction should eventually be triggered through an event-based system rather than direct actor-specific logic. A player, projectile, physics impact, or scripted force should create a destruction event that is passed into the MVCD destruction framework.

A destruction event should contain:
- source actor
- target actor
- impact location
- impact direction
- damage amount
- damage type
- material or resistance information
- replication identifier
- timestamp

The Destruction Manager should handle:
- registering destructible actors
- receiving destruction requests
- validating destruction events
- coordinating destruction tests
- tracking destruction statistics
- preparing benchmark data

The actor or destruction component should handle:
- local destructible state
- receiving damage requests
- applying damage to the Geometry Collection
- deciding if the object should fracture
- exposing debug information

For multiplayer, the framework should eventually replicate:
- destruction events
- damage states
- destroyed/not destroyed state
- important fracture triggers

It should avoid replicating every physics chunk directly because full physics replication would be too expensive for large-scale destruction.