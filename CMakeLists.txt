cmake_minimum_required(VERSION 3.16)

# set the project name
project(dcptest)

set (TEST_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_custom_target(test-output-directory ALL
                  COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_OUTPUT_DIRECTORY})

# add the executable
add_executable(dcptest 
               src/dcpd.cpp
               src/dcpServer.cpp
               src/common/pf_dcp.c
               src/common/pf_scheduler.c
               src/common/pf_eth.c
               src/common/pf_bg_worker.c
               src/common/pf_file.c
               src/common/pf_lldp.c
               src/common/pf_udp.c
               src/device/pf_block_reader.c
               src/device/pf_block_writer.c
               src/device/pf_cmina.c
               src/device/pf_port.c
               src/device/pf_pdport.c
               src/ports/linux/osal.c
               src/ports/linux/pnal.c
               src/ports/linux/pnal_filetools.c
               src/ports/linux/pnal_udp.c
               src/ports/linux/pnal_eth.c)

target_include_directories(dcptest
  PUBLIC .
  PRIVATE include
  PRIVATE src
  PRIVATE src/common
  PRIVATE src/device
  PRIVATE src/ports/linux
)

target_link_libraries(dcptest rt pthread)


set_target_properties(dcptest
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
