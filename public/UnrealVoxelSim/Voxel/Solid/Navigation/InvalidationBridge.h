#pragma once
#include "UnrealVoxelSim/Events/Api/Subscription.h"
#include "UnrealVoxelSim/Navigation/Voxel/Api/IInvalidationSink.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/IChangeSource.h"

// TODO This bridge encodes the dependency in the wrong direction.
//
// Voxel::Solid should expose the domain fact that voxel regions changed, but it should not know
// that Navigation exists or translate that change into a navigation-specific invalidation command.
//
// Navigation::Voxel is the component that understands how voxel changes affect its topology/cache
// state. Prefer moving this integration to the Navigation side, where it can subscribe to
// Voxel::Solid::Api::IChangeSource and perform the corresponding invalidation internally.
//
// This may also eliminate the need for Navigation::Voxel::Api::IInvalidationSink, which currently
// exposes an implementation maintenance operation as public API.
namespace UnrealVoxelSim::Voxel::Solid::Navigation
{
	class InvalidationBridge final
	{
	public:
		InvalidationBridge(Api::IChangeSource& changes,
		                   UnrealVoxelSim::Navigation::Voxel::Api::IInvalidationSink& sink);
		~InvalidationBridge();
		InvalidationBridge(const InvalidationBridge&) = delete;
		InvalidationBridge& operator=(const InvalidationBridge&) = delete;

	private:
		Events::Api::Subscription m_Subscription;
	};
}
