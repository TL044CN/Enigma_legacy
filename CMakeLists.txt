cmake_minimum_required(VERSION 3.16)
set(SODIR "so")
set(LIBDIR "lib")
set(INCLUDEDIR "include")
set(BINDIR "bin")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/out)

project(enigma
    VERSION 1.0.1
    DESCRIPTION "Enigma Engine"
)

add_library(ttenigma SHARED
    src/Core/EntryPoint.h
    src/Core/Application.cpp
    src/debug/Logger.cpp
    src/debug/Profiler.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(ttenigma PUBLIC
        ENIGMA_LOGGER=1
        ENIGMA_ASSERT=1
    )
endif()

find_package(Threads REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

target_link_libraries(ttenigma
    Threads::Threads
    glm::glm
    glfw
    Vulkan::Vulkan
)

set_property(TARGET ttenigma PROPERTY CXX_STANDARD_REQUIRED 20)
set_property(TARGET ttenigma PROPERTY CXX_STANDARD 20)

set_target_properties(ttenigma PROPERTIES 
    OUTPUT_NAME ttenigma
	VERSION ${PROJECT_VERSION}
	PUBLIC_HEADER "src/Enigma.h"
)

target_compile_definitions(ttenigma PUBLIC TTDEBUG=0)

project(Http
    VERSION 1.0.5
    DESCRIPTION "HTTP Message Extension for Network"
)


install(
TARGETS ttenigma
RUNTIME DESTINATION ${BINDIR}
LIBRARY DESTINATION ${SODIR}
ARCHIVE DESTINATION ${LIBDIR}
PUBLIC_HEADER DESTINATION ${INCLUDEDIR}
)
