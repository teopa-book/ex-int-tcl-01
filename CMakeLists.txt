cmake_minimum_required(VERSION 3.18)
project(tclmin)

set(TARGET_BASE_NAME "${PROJECT_NAME}")
set(APP_NAME "${TARGET_BASE_NAME}")
set(TCL_ROOT "${PROJECT_SOURCE_DIR}/lib/tcl9.0b1")

add_executable(${APP_NAME}
  src/app.c
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_include_directories(${APP_NAME} PRIVATE
    "${TCL_ROOT}/unix/release/include"
  )

  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(${APP_NAME}
      general "${TCL_ROOT}/unix/release/lib/libtcl9.0.a"
      general m
      general z
    )
  else()
    target_link_libraries(${APP_NAME}
      general "${TCL_ROOT}/unix/debug/lib/libtcl9.0.a"
      general m
      general z
    )
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_include_directories(${APP_NAME} PRIVATE
    "${TCL_ROOT}/win/release/include"
  )

  target_link_libraries(${APP_NAME}
    optimized "${TCL_ROOT}/win/release/lib/tcl90s.lib"
    debug "${TCL_ROOT}/win/debug/lib/tcl90s.lib"
    general netapi32.lib
  )
endif()

target_compile_definitions(${APP_NAME} PUBLIC
  STATIC_BUILD
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${APP_NAME} PRIVATE -Wall)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_link_options(${APP_NAME} PRIVATE "$<$<CONFIG:Release>:/LTCG>")
  set_property(TARGET ${APP_NAME} PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
  )
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(NOT EXISTS "${TCL_ROOT}/unix/release/lib/libtcl9.0.a")
    execute_process(
      COMMAND configure --prefix=$PWD/release --enable-shared=no
      WORKING_DIRECTORY "${TCL_ROOT}/unix"
    )
    execute_process(
      COMMAND make
      WORKING_DIRECTORY "${TCL_ROOT}/unix"
    )
    execute_process(
      COMMAND make install
      WORKING_DIRECTORY "${TCL_ROOT}/unix"
    )
    endif()
  if(NOT EXISTS "${TCL_ROOT}/unix/debug/lib/libtcl9.0.a")
    execute_process(
      COMMAND configure --prefix=$PWD/debug --enable-shared=no --enable-symbols
      WORKING_DIRECTORY "${TCL_ROOT}/unix"
    )
    execute_process(
      COMMAND make
      WORKING_DIRECTORY "${TCL_ROOT}/unix"
    )
    execute_process(
      COMMAND make install
      WORKING_DIRECTORY "${TCL_ROOT}/unix"
    )
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if(NOT EXISTS "${TCL_ROOT}/win/release/lib/tcl90s.lib")
    execute_process(
      COMMAND nmake -f makefile.vc all OPTS=static,pdbs,nomsvcrt
      WORKING_DIRECTORY "${TCL_ROOT}/win"
    )
    execute_process(
      COMMAND nmake -f makefile.vc install INSTALLDIR=release OPTS=static,pdbs,nomsvcrt
      WORKING_DIRECTORY "${TCL_ROOT}/win"
    )
  endif()
  if(NOT EXISTS "${TCL_ROOT}/win/debug/lib/tcl90s.lib")
    execute_process(
      COMMAND nmake -f makefile.vc all OPTS=static,symbols,nomsvcrt
      WORKING_DIRECTORY "${TCL_ROOT}/win"
    )
    execute_process(
      COMMAND nmake -f makefile.vc install INSTALLDIR=debug OPTS=static,symbols,nomsvcrt
      WORKING_DIRECTORY "${TCL_ROOT}/win"
    )
  endif()
endif()
