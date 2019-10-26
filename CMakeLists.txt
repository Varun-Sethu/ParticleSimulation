cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )


project(Playing)
enable_language(CXX)

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

include_directories("${APP_PATH}/include")

set(SRC_FILES
    "${APP_PATH}/src/PlayingApp.cpp"


    "${APP_PATH}/include/Particles/ParticleController.h"
    "${APP_PATH}/include/Particles/Particle.h"
    "${APP_PATH}/src/Particles/Particle.cpp"
    "${APP_PATH}/src/Particles/ParticleController.cpp"    

    "${APP_PATH}/include/Util/Util.h"
    "${APP_PATH}/src/Util/Util.cpp"
)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

ci_make_app(
    APP_NAME "Playing"
    SOURCES ${SRC_FILES}
    CINDER_PATH ${CINDER_PATH}
    INCLUDES ${APP_PATH}/include
)