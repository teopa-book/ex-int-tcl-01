cmake_minimum_required(VERSION 3.18)
project(tclmin)

set(TARGET_BASE_NAME "${PROJECT_NAME}")
set(APP_NAME "${TARGET_BASE_NAME}")
set(TCL_ROOT "${PROJECT_SOURCE_DIR}/lib/tcl9.0b1")
set(TCL_INCLUDE_DIR "${TCL_ROOT}/win/release/include")

add_executable(${APP_NAME}
  src/embedtcl.c
)

target_include_directories(${APP_NAME} PRIVATE
  "${TCL_INCLUDE_DIR}"
)

target_link_libraries(${APP_NAME}
  optimized "${TCL_LIB_DIR}/release/lib/tcl90s.lib"
  debug "${TCL_LIB_DIR}/debug/lib/tcl90s.lib"
  general netapi32.lib
)

target_compile_definitions(${APP_NAME} PUBLIC
  STATIC_BUILD
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${APP_NAME} PRIVATE -Wall)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_link_options(${APP_NAME} PRIVATE /LTCG)
  set_property(TARGET ${APP_NAME} PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
  )
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  execute_process(
    COMMAND nmake -f makefile.vc all OPTS=static,pdbs,nomsvcrt
    COMMAND nmake -f makefile.vc install INSTALLDIR=release OPTS=static,pdbs,nomsvcrt
    COMMAND nmake -f makefile.vc all OPTS=static,symbols,nomsvcrt
    COMMAND nmake -f makefile.vc install INSTALLDIR=debug OPTS=static,symbols,nomsvcrt
    WORKING_DIRECTORY "${TCL_ROOT}/win"
  )
endif()
