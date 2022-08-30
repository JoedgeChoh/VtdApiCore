cmake_minimum_required(VERSION 3.5)

set(TARGET ExampleSharedMemoryVideoStreamer)

project(${TARGET} VERSION 0.0.2)

find_package(FFMPEG COMPONENTS avutil swresample swscale avcodec avformat avfilter avdevice)
if(NOT FFMPEG_VERSION)
    message("FFMPEG could not be found ${TARGET} will not be built.")
    return()
endif()

find_package(VtdFramework REQUIRED CONFIG PATHS "${VtdFramework_ROOT}" "${CMAKE_CURRENT_SOURCE_DIR}/../../../VtdFramework/cmake")
find_package(Boost REQUIRED COMPONENTS timer system thread chrono program_options)
collect_source_files(${TARGET} src)
collect_source_files(${TARGET} inc)

add_executable(${TARGET} ${${TARGET}_SOURCE_LIST})

target_include_directories(${TARGET} PRIVATE src inc)


set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
create_version_header(
    "${CMAKE_CURRENT_SOURCE_DIR}/Version.h.in"
    "${GENERATED_DIR}/inc/${PROJECT_NAME}/Version.h")
target_include_directories(${TARGET} PUBLIC
    $<BUILD_INTERFACE:${GENERATED_DIR}/inc>)

target_link_libraries(${TARGET} PUBLIC
    FFmpeg::avcodec
    FFmpeg::avutil
    FFmpeg::avformat
    FFmpeg::swscale
    FFmpeg::swresample
    Boost::timer
    Boost::chrono
    Boost::system
    Boost::thread
    Boost::program_options
    VtdToolkit)

target_compile_definitions(${TARGET} PRIVATE
    __STDC_CONSTANT_MACROS)

file(GLOB DATA_FILES
  "data/*"
)
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

