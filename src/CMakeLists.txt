set(gen_mesh_class_dir
  ${CMAKE_CURRENT_SOURCE_DIR}/gen_mesh_classes)

include_directories(${gen_mesh_class_dir})
add_subdirectory(gen_mesh_classes)


find_package(Boost REQUIRED COMPONENTS program_options)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(Mesh_Generator MeshGen_main.cpp)
  target_link_libraries(Mesh_Generator ${Boost_PROGRAM_OPTIONS_LIBRARIES} gen_mesh_classes)
endif()
