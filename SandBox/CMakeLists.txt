project(SandBox LANGUAGES C CXX)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${DRAGONFLY_NAME})
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-O0>
  $<$<CONFIG:DEBUG>:-g> $<$<CONFIG:RELEASE>:-O2>)

set_target_properties(${PROJECT_NAME} PROPERTIES
    BUILD_RPATH "$ORIGIN"
    INSTALL_RPATH "$ORIGIN"
)
