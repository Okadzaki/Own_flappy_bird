
cmake_policy(SET CMP0017 NEW)

cmake_minimum_required(VERSION 2.8)

set(APP_NAME MyGame)
project (${APP_NAME})

set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/cocos2d)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COCOS2D_ROOT}/cmake/Modules/")
include(CocosBuildHelpers)

# libcocos2d
set(BUILD_CPP_TESTS OFF CACHE BOOL "turn off build cpp-tests")
set(BUILD_LUA_LIBS OFF CACHE BOOL "turn off build lua-tests")
add_subdirectory(${COCOS2D_ROOT})

# Some macro definitions
if(WINDOWS)
  if(BUILD_SHARED_LIBS)
    ADD_DEFINITIONS (-D_USRDLL -D_EXPORT_DLL_ -D_USEGUIDLL -D_USREXDLL -D_USRSTUDIODLL)
  else()
    ADD_DEFINITIONS (-DCC_STATIC)
  endif()

  ADD_DEFINITIONS (-DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32 -D_WIN32)
  set(PLATFORM_FOLDER win32)
elseif(MACOSX OR APPLE)
  ADD_DEFINITIONS (-DCC_TARGET_OS_MAC)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER mac)
elseif(LINUX)
  ADD_DEFINITIONS(-DLINUX)
  set(PLATFORM_FOLDER linux)
elseif(ANDROID)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER android)
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()


# Compiler options
if(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
                  -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
                  -wd4514 -wd4056 -wd4996 -wd4099)
else()
  set(CMAKE_C_FLAGS_DEBUG "-g -Wall -DCOCOS2D_DEBUG=1")
  set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -std=c99")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -std=c++11 -Wno-deprecated-declarations -Wno-reorder")
  if(CLANG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  endif()
endif(MSVC)



set(PLATFORM_SPECIFIC_SRC)
set(PLATFORM_SPECIFIC_HEADERS)
if(MACOSX OR APPLE)
set(PLATFORM_SPECIFIC_SRC
  proj.ios_mac/ios/main.m
  proj.ios_mac/ios/RootViewController.mm
  proj.ios_mac/ios/AppController.mm
)
set(PLATFORM_SPECIFIC_HEADERS
  proj.ios_mac/ios/RootViewController.h
  proj.ios_mac/ios/AppController.h
)
elseif(LINUX) #assume linux
set(PLATFORM_SPECIFIC_SRC
  proj.linux/main.cpp
)
elseif ( WIN32 )
set(PLATFORM_SPECIFIC_SRC
  proj.win32/main.cpp
)
set(PLATFORM_SPECIFIC_HEADERS
  proj.win32/main.h
  proj.win32/resource.h
)
endif()

include_directories(
  /usr/local/include/GLFW
  /usr/include/GLFW
  ${COCOS2D_ROOT}/cocos
  Classes
)

set(GAME_SRC
  Classes/AppDelegate.cpp
  Classes/HelloWorldScene.cpp
  Classes/Bird.cpp
    Classes/AddPipe.cpp
Classes/Collision.cpp
Classes/Flying.cpp
Classes/MoveLeft.cpp
Classes/MoveLoop.cpp

  ${PLATFORM_SPECIFIC_SRC}
)

set(GAME_HEADERS
  Classes/AppDelegate.h
  Classes/HelloWorldScene.h
   Classes/config.h
  Classes/Bird.h
Classes/AddPipe.h
Classes/Collision.h
Classes/Flying.h
Classes/MoveLeft.h
Classes/MoveLoop.h



  ${PLATFORM_SPECIFIC_HEADERS}
)

if(GAME_HEADERS)
add_executable(${APP_NAME} ${GAME_SRC} ${GAME_HEADERS})
else()
add_executable(${APP_NAME} ${GAME_SRC})
endif()

target_link_libraries(${APP_NAME} cocos2d)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

if ( WIN32 )
  #also copying dlls to binary directory for the executable to run
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/gles/prebuilt/glew32.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
	COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/zlib/prebuilt/zlib1.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
	)
else()
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
    )

endif()
