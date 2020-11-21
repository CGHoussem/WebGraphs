cmake_minimum_required(VERSION "3.10.2")


project("GraphesOCA")

add_executable("${PROJECT_NAME}" "src/main.cpp")

install(TARGETS "${PROJECT_NAME}" DESTINATION bin) #${CMAKE_INSTALL_PREFIX}/bin
install(FILES "src/main.cpp" DESTINATION src) #${CMAKE_INSTALL_PREFIX}/src
