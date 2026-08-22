# UnrealVoxelSim.Voxel.Solid.Navigation

Adapter from the authoritative solid-material voxel domain to the navigation-oriented environment projection. The solid
domain remains unaware of navigation: this module depends on both APIs and owns the translation and event bridge.

## Environment projection

`Environment` implements `Navigation::Voxel::Api::IEnvironment` using a voxel bounds provider and
`Voxel::Solid::Api::IRegionReader`. Reads are batched by region and reuse private scratch storage. Each solid cell is
currently mapped as follows:

| Solid payload | Blocks occupancy | Supports grounded body | Traversal cost |
| --- | --- | --- | --- |
| Empty | No | No | `1000` |
| Any non-empty material | Yes | Yes | `1000` |

This is V1 human-grounded policy: dirt, grass, stone, and every other non-empty solid material are equivalent to the
planner. The adapter does not mutate or cache authoritative solids. It is thread-affine because its source readers and
reused scratch buffer are owned by the simulation thread.

Material-specific costs or walkability belong in an adapter policy, not in `Voxel.Solid.Api`. A future composite
environment may read solid, liquid, and other layer APIs and combine them into navigation cells. Agents with incompatible
medium semantics, such as a human and a ship, can be composed with different environment-policy/planner instances while
the layer modules remain unchanged.

## Invalidation bridge

`InvalidationBridge` subscribes to `Voxel::Solid::Api::IChangeSource` and forwards each committed changed region to a
`Navigation::Voxel::Api::IInvalidationSink`. The sink discards derived topology whose dependency regions intersect the
change and increments its environment revision; the bridge never requests a synchronous rebuild.

The change source and invalidation sink must outlive the bridge. The bridge owns its RAII subscription and disconnects
on destruction. The composition root controls queued event dispatch, so solid changes should be committed and dispatched
before topology maintenance and planner advancement in the same simulation tick.

Initial or newly streamed regions are not changes and should be announced separately through
`Navigation::Voxel::Api::IPreparationSink::Prepare`. This keeps proactive topology construction distinct from
authoritative mutation invalidation.
