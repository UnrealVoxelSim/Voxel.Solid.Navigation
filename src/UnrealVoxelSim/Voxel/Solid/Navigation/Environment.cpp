#include "UnrealVoxelSim/Voxel/Solid/Navigation/Environment.h"
#include <algorithm>
#include <cassert>
#include <thread>
#include <vector>
namespace UnrealVoxelSim::Voxel::Solid::Navigation
{
class Environment::Impl final
{
  public:
    Impl(const UnrealVoxelSim::Voxel::Api::IBounds &bounds, const Api::IRegionReader &reader) : BoundsReader(bounds), Reader(reader) {}
    void AssertOwnerThread() const noexcept { assert(std::this_thread::get_id() == OwnerThread); }
    const UnrealVoxelSim::Voxel::Api::IBounds &BoundsReader;
    const Api::IRegionReader &Reader;
    mutable std::vector<Api::Cell> Scratch;
    std::thread::id OwnerThread{std::this_thread::get_id()};
};
Environment::Environment(const UnrealVoxelSim::Voxel::Api::IBounds &bounds, const Api::IRegionReader &reader)
    : Impl_(std::make_unique<Impl>(bounds, reader)) {}
Environment::~Environment() = default;
UnrealVoxelSim::Voxel::Api::Region Environment::Bounds() const noexcept
{
    Impl_->AssertOwnerThread();
    return Impl_->BoundsReader.Bounds();
}
std::expected<void, UnrealVoxelSim::Voxel::Api::ReadError> Environment::ReadRegion(
    const UnrealVoxelSim::Voxel::Api::Region region,
    const std::span<UnrealVoxelSim::Navigation::Voxel::Api::Cell> output) const
{
    Impl_->AssertOwnerThread();
    Impl_->Scratch.resize(output.size());
    const auto result = Impl_->Reader.ReadRegion(region, Impl_->Scratch);
    if (!result) return std::unexpected{result.error()};
    std::ranges::transform(Impl_->Scratch, output.begin(), [](const Api::Cell cell) {
        const auto occupied = !cell.IsEmpty();
        return UnrealVoxelSim::Navigation::Voxel::Api::Cell{occupied, occupied, 1000};
    });
    return {};
}
} // namespace UnrealVoxelSim::Voxel::Solid::Navigation
