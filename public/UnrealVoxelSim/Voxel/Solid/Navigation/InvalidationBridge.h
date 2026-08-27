#pragma once
#include "UnrealVoxelSim/Events/Api/Subscription.h"
#include "UnrealVoxelSim/Navigation/Voxel/Api/IInvalidationSink.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/IChangeSource.h"
namespace UnrealVoxelSim::Voxel::Solid::Navigation
{
class InvalidationBridge final
{
  public:
    InvalidationBridge(Api::IChangeSource &changes, UnrealVoxelSim::Navigation::Voxel::Api::IInvalidationSink &sink);
    ~InvalidationBridge();
    InvalidationBridge(const InvalidationBridge &) = delete;
    InvalidationBridge &operator=(const InvalidationBridge &) = delete;
  private:
    Events::Api::Subscription m_Subscription;
};
} // namespace UnrealVoxelSim::Voxel::Solid::Navigation
