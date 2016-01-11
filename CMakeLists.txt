cmake_minimum_required(VERSION 2.8.3)
project(imu_test)

add_executable(imu_test src/imu_test.cpp)

target_link_libraries(imu_test 
   RTIMULib
)
