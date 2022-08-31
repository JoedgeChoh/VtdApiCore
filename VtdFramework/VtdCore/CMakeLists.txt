cmake_minimum_required(VERSION 3.5)

project(VtdCore VERSION ${VtdFramework_VERSION} LANGUAGES CXX)

set(TARGET VtdCore)

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
message("CMAKE_BINARY_DIR in VtdCore is ${CMAKE_BINARY_DIR}")
message("CMAKE_CURRENT_BINARY_DIR in VtdCore is ${CMAKE_CURRENT_BINARY_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR in VtdCore is ${CMAKE_CURRENT_SOURCE_DIR}")
message("PROJECT_VERSION in VtdCore is ${PROJECT_VERSION}")

create_version_header("${CMAKE_CURRENT_LIST_DIR}/../cmake/Version.h.in" "${GENERATED_DIR}/inc/${TARGET}/Version.h")

# Dependencies
find_package(Boost 1.63 REQUIRED COMPONENTS thread chrono filesystem)
find_package(TinyXML REQUIRED)

collect_source_files(${TARGET} include)
collect_source_files(${TARGET} src/Common)
collect_source_files(${TARGET} src/${CMAKE_SYSTEM_NAME}) # specific current OS
message("VtdCore_SOURCE_LIST is ${${TARGET}_SOURCE_LIST}")

if(VtdFramework_BUILD_SHARED)
    add_library(${TARGET} SHARED ${${TARGET}_SOURCE_LIST})
else()
    add_library(${TARGET} STATIC ${${TARGET}_SOURCE_LIST})
    set_property(TARGET ${TARGET} PROPERTY POSITION_INDEPENDENT_CODE True)
endif()
set_target_properties(${TARGET} PROPERTIES
    VERSION ${PROJECT_VERSION}
    DEBUG_POSTFIX "-d"   # 在生成的库文件后缀-d,表示debug编译模式
)

## 功能等同于include_directories()
##作为第三方库被搜索时，设置从build被引用和从package安装位置被引用需要不同的借口路径
target_include_directories(${TARGET} PUBLIC  
    $<BUILD_INTERFACE:${GENERATED_DIR}/inc>  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

message("CMAKE_CXX_COMPILER_ID is ${CMAKE_CXX_COMPILER_ID}")
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")  ## 编译器为GCC
    option(USE_CXX11_ABI OFF "See GCC's libstdc++ Dual-ABI")
    ## 为目标添加预设宏声明以及定义
    ## PUBLIC表明相关设置不仅作用与当前指定的target，而且会随依赖关系进行传递
    target_compile_definitions(${TARGET} PUBLIC _GLIBCXX_USE_CXX11_ABI=$<BOOL:${USE_CXX11_ABI}>)
endif()
## 向target添加编译选项
target_compile_options(${TARGET} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wconversion>)

target_compile_definitions(${TARGET} PUBLIC
    $<$<CONFIG:Debug>:VTD_DEBUG>
    $<$<PLATFORM_ID:Linux>:VTD_OS_LINUX>
    $<$<PLATFORM_ID:Windows>:VTD_OS_WINDOWS>
)

target_link_libraries( ${TARGET} PRIVATE
    $<$<PLATFORM_ID:Linux>:rt>
)

target_link_libraries(${TARGET} PUBLIC TinyXML::Static Boost::chrono Boost::filesystem Boost::thread)

## Documentation
set(VtdFramework_FILES "${VtdFramework_FILES} ${${TARGET}_SOURCE_LIST}" PARENT_SCOPE)

## Testing:
if(BUILD_TESTING AND VtdFramework_TEST)
    setup_coverage_for_target(
        TARGET ${TARGET}
        COVERAGE_EXECUTABLES ${TARGET}_TEST
    )

    add_subdirectory(test)
endif()

## package creation:
if(VtdFramework_INSTALL)
    install(TARGETS ${TARGET}
        EXPORT VtdFramework
        DESTINATION lib
    )
    install(DIRECTORY include/ DESTINATION include 
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE
    )
endif()
