cmake_minimum_required(VERSION 3.5)
project(pcl_conversions)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(message_filters REQUIRED)
find_package(PCL REQUIRED QUIET COMPONENTS common io)
find_package(pcl_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

set(dependencies
  message_filters
  pcl_msgs
  rclcpp
  sensor_msgs
  std_msgs
)

add_library(pcl_conversions INTERFACE)
target_include_directories(pcl_conversions
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${PCL_COMMON_INCLUDE_DIRS}
)
#ament_target_dependencies(pcl_conversions ${dependencies})
target_link_libraries(pcl_conversions
  INTERFACE
    ${PCL_LIBRARIES})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}/
)

install(
  TARGETS
    pcl_conversions
  EXPORT export_pcl_conversions
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

# Add gtest based cpp test target
if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  ament_add_gtest(${PROJECT_NAME}-test test/test_pcl_conversions.cpp)
  ament_target_dependencies(${PROJECT_NAME}-test
    ${dependencies}
  )
  target_link_libraries(${PROJECT_NAME}-test ${Boost_LIBRARIES} ${PCL_LIBRARIES})
endif()

ament_export_include_directories(include ${PCL_COMMON_INCLUDE_DIRS})
ament_export_dependencies(${dependencies})
ament_export_targets(export_pcl_conversions HAS_LIBRARY_TARGET)
ament_package()
