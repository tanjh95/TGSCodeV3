

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
set(PROJ_NAME TGS)
project(${PROJ_NAME})

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
#option命令对WITH_GEANT$_UIVIS初始化为ON
if(WITH_GEANT4_UIVIS)
find_package(Geant4 REQUIRED ui_all vis_all)
#find_package搜索第三方的库文件
else()
find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/inc
#PROJECT_SOURCE_DIR由project 指令隐式定义就是CMakeList所在的目录
${Geant4_INCLUDE_DIR}
${PROJECT_SOURCE_DIR}/../inc)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.hh)


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(${PROJ_NAME} main.cc ${sources} ${headers})
target_link_libraries(${PROJ_NAME} ${Geant4_LIBRARIES} 
-L${PROJECT_SOURCE_DIR}/../lib sg4)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(det_SCRIPTS
input.txt optical.txt vis.mac Formate.txt StepTree.txt
)

foreach(_script ${det_SCRIPTS})
configure_file(
${PROJECT_SOURCE_DIR}/${_script}
${PROJECT_BINARY_DIR}/../bin/${_script}
COPYONLY
)
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS ${PROJ_NAME} DESTINATION bin)
