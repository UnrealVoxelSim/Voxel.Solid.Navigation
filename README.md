# UnrealVoxelSim.Voxel.Solid.Navigation

Adapter from solid voxel payload to grounded navigation environment samples. It performs coarse region reads, maps
non-empty solid materials to occupancy and support, and bridges solid change regions into navigation invalidation. The
solid domain remains unaware of navigation.
