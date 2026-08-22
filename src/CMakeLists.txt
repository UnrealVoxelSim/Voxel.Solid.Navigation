add_library(${PROJECT_NAME} UnrealVoxelSim/Voxel/Solid/Navigation/Environment.cpp UnrealVoxelSim/Voxel/Solid/Navigation/InvalidationBridge.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/public>" "$<INSTALL_INTERFACE:include>")
target_link_libraries(${PROJECT_NAME} PUBLIC UnrealVoxelSim.Navigation.Voxel.Api UnrealVoxelSim.Voxel.Solid.Api)
UnrealVoxelSimConfigureTarget(${PROJECT_NAME})
