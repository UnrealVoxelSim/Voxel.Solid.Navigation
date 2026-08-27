#include "UnrealVoxelSim/Voxel/Solid/Navigation/InvalidationBridge.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/Changed.h"

namespace UnrealVoxelSim::Voxel::Solid::Navigation
{
	InvalidationBridge::InvalidationBridge(Api::IChangeSource& changes,
	                                       UnrealVoxelSim::Navigation::Voxel::Api::IInvalidationSink& sink)
	{
		m_Subscription = changes.Subscribe([&sink](const Api::Changed& changed) noexcept
		{
			sink.Invalidate(changed.Regions);
		});
	}

	InvalidationBridge::~InvalidationBridge() { m_Subscription.Reset(); }
}
