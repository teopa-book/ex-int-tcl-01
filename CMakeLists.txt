cmake_minimum_required(VERSION 3.18)
project(tclmin)

set(TARGET_BASE_NAME "${PROJECT_NAME}")
set(APP_NAME "${TARGET_BASE_NAME}")
set(TCL_ROOT "${PROJECT_SOURCE_DIR}/lib/tcl9.0b1")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
include(BuildTclStatic)

add_executable(${APP_NAME}
  src/app.c
)

target_include_directories(${APP_NAME} PRIVATE
  "${TCL_INCLUDE_PATH}"
)

target_link_libraries(${APP_NAME}
  ${TCL_LIBRARY}
)

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
