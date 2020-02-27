cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )
set (DEBUG TRUE)


# GDB debugging object
project (Playing)
enable_language(CXX)
set (CMAKE_CXX_STANDARD 17)
if(DEBUG)
    set(CMAKE_CXX_FLAGS "-ggdb")
endif()


# Set the source files
get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
include_directories("${APP_PATH}/include")



# include the important fles
set(SRC_FILES
    "${APP_PATH}/include/Particles/ParticleController.h"
    "${APP_PATH}/include/Particles/Particle.h"

    "${APP_PATH}/src/Particles/Particle.cpp"
    "${APP_PATH}/src/Particles/ParticleController.cpp"    

    "${APP_PATH}/include/Util/Util.h"
    "${APP_PATH}/include/Util/QuadTree.h"
    "${APP_PATH}/src/Util/Util.cpp"
    "${APP_PATH}/include/Util/CollisionEngine.h"
)
include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")
set(MAIN_SRC_FILES "${SRC_FILES}"
    "${APP_PATH}/src/PlayingApp.cpp"  # Any additional files that are specific to only the actual executable build
)

ci_make_app(
    APP_NAME "Playing"
    SOURCES ${MAIN_SRC_FILES} 
    CINDER_PATH ${CINDER_PATH}
    INCLUDES ${APP_PATH}/include
)



# IF the debug flag is on then compile the tests
if(DEBUG)
    enable_testing()
    add_subdirectory("${APP_PATH}/tests")
    # Manually add the tests here
    add_test(quadTreeTest Playing)
endif()