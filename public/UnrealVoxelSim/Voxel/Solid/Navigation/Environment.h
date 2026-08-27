#pragma once
#include "UnrealVoxelSim/Navigation/Voxel/Api/IEnvironment.h"
#include "UnrealVoxelSim/Voxel/Api/IBounds.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/IRegionReader.h"
#include <memory>

// TODO This adapter appears to belong to the Navigation domain rather than Voxel.
//
// Its responsibility is to adapt Voxel::Solid world data to the representation required by the
// voxel-navigation implementation. Voxel::Solid should not need to know that Navigation exists;
// Navigation::Voxel may legitimately depend on Voxel::Solid as one particular world backend.
//
// Consider moving this to UnrealVoxelSim::Navigation::Voxel::Solid (or another Navigation-owned
// integration namespace).
//
// Also reconsider this class together with Navigation::Voxel::Api::IEnvironment. If IEnvironment
// is only an internal port of the voxel-navigation implementation, both the interface and this
// adapter should probably remain internal to Navigation rather than forming a public cross-domain API.
namespace UnrealVoxelSim::Voxel::Solid::Navigation
{
	// TODO See todo in UnrealVoxelSim::Navigation::Voxel::Api::IEnvironment
	class Environment final : public UnrealVoxelSim::Navigation::Voxel::Api::IEnvironment
	{
	public:
		Environment(const UnrealVoxelSim::Voxel::Api::IBounds& bounds, const Api::IRegionReader& reader);
		~Environment() override;


		[[nodiscard]] UnrealVoxelSim::Voxel::Api::Region Bounds() const noexcept override;
		[[nodiscard]] std::expected<void, UnrealVoxelSim::Voxel::Api::ReadError> ReadRegion(
			UnrealVoxelSim::Voxel::Api::Region region,
			std::span<UnrealVoxelSim::Navigation::Voxel::Api::Cell> output) const override;

	private:
		class Impl;
		std::unique_ptr<Impl> m_Impl;
	};
}
