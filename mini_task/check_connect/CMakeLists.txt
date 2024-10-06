cmake_minimum_required(VERSION 3.0)
#set minimum version CMake
project(check_connect)
#set name of project


set(LIBUSB_INCLUDE_DIR "/usr/include/libusb-1.0")
#LIBUSB_INCLUDE_DIR = (addres to directories)"/usr/include/libusb-1.0"

set(LIBUSB_LIBRARY "/usr/lib/x86_64-linux-gnu/libusb-1.0.so")
#LIBUSB_INCLUDE_DIR = (addres to file .so)"/usr/include/libusb-1.0"
add_executable(check_connect main.cpp Rtl_connect_process.cpp)
#add executable file


target_include_directories(check_connect PRIVATE ${LIBUSB_INCLUDE_DIR})
#add file in LIBUSB_INCLUDE_DIR

target_link_libraries(check_connect PRIVATE ${LIBUSB_LIBRARY})
#connect with libusb-1.0

install(TARGETS check_connect RUNTIME DESTINATION bin)
