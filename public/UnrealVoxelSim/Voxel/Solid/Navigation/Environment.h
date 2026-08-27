#pragma once
#include "UnrealVoxelSim/Navigation/Voxel/Api/IEnvironment.h"
#include "UnrealVoxelSim/Voxel/Api/IBounds.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/IRegionReader.h"
#include <memory>

namespace UnrealVoxelSim::Voxel::Solid::Navigation
{
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
} // namespace UnrealVoxelSim::Voxel::Solid::Navigation
