set(SOURCE_FILE
  ${PROJ_SRC_DIR}/mymath.cpp
  ${PROJ_SRC_DIR}/crystal.cpp
  ${PROJ_SRC_DIR}/optics.cpp
  ${PROJ_SRC_DIR}/context.cpp
  ${PROJ_SRC_DIR}/render.cpp
  ${PROJ_SRC_DIR}/files.cpp
  ${PROJ_SRC_DIR}/simulation.cpp
  ${PROJ_SRC_DIR}/threadingpool.cpp)

add_executable(test
  ${SOURCE_FILE}
  test_crystal.cpp
  test_context.cpp
  test_optics.cpp
  test_main.cpp)
target_include_directories(test
  PUBLIC ${PROJ_SRC_DIR} ${Boost_INCLUDE_DIRS} "${MODULE_ROOT}/rapidjson/include")
target_link_libraries(test
  PUBLIC ${Boost_LIBRARIES} gtest)

add_test(NAME "IceHaloTest" COMMAND test "${PROJ_ROOT}/test/config_01.json")
