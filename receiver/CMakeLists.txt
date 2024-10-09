cmake_minimum_required(VERSION 3.10)
project(receiverRtl)
find_package(PkgConfig REQUIRED)
# Добавляем исходные файлы
add_executable(my_program main.cpp ReceiverRtl.cpp)

# Подключаем библиотеку librtlsdr
if(NOT LIBRTLSDR_FOUND)
  pkg_check_modules (LIBRTLSDR_PKG librtlsdr)
  find_path(LIBRTLSDR_INCLUDE_DIRS NAMES rtl-sdr.h
    PATHS
    ${LIBRTLSDR_PKG_INCLUDE_DIRS}
    /usr/include
    /usr/local/include
  )

  find_library(LIBRTLSDR_LIBRARIES NAMES rtlsdr
    PATHS
    ${LIBRTLSDR_PKG_LIBRARY_DIRS}
    /usr/lib
    /usr/local/lib
  )

  if(LIBRTLSDR_INCLUDE_DIRS AND LIBRTLSDR_LIBRARIES)
    set(LIBRTLSDR_FOUND TRUE CACHE INTERNAL "librtlsdr found")
    message(STATUS "Found librtlsdr: ${LIBRTLSDR_INCLUDE_DIRS}, ${LIBRTLSDR_LIBRARIES}")
  else()
    set(LIBRTLSDR_FOUND FALSE CACHE INTERNAL "librtlsdr not found")
    message(STATUS "librtlsdr not found.")
  endif()

  mark_as_advanced(LIBRTLSDR_LIBRARIES LIBRTLSDR_INCLUDE_DIRS)
endif()

if(LIBRTLSDR_FOUND)
  include_directories(${LIBRTLSDR_INCLUDE_DIRS})
  target_link_libraries(my_program ${LIBRTLSDR_LIBRARIES})
else()
  message(FATAL_ERROR "librtlsdr library not found!")
endif()
