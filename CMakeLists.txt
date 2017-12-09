cmake_minimum_required(VERSION 3.5.1)

project(RGLK CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(THIRD_PARTY_LIBRARIES "${CMAKE_SOURCE_DIR}/ThirdPartyLibs")

set(PROJ_NAME "WorknameProject")

set(EXECUTABLE_NAME ${PROJ_NAME}.out)

link_directories(ThirdPartyLibs/)
file(GLOB SOURCE_FILES
	"${THIRD_PARTY_LIBRARIES}/Box2D/Collision/*.h" "${THIRD_PARTY_LIBRARIES}/Box2D/Collision/*.cpp"
	"${THIRD_PARTY_LIBRARIES}/Box2D/Collision/Shapes/*.h" "${THIRD_PARTY_LIBRARIES}/Box2D/Collision/Shapes/*.cpp"
	"${THIRD_PARTY_LIBRARIES}/Box2D/Common/*.h" "${THIRD_PARTY_LIBRARIES}/Box2D/Common/*.cpp"
	"${THIRD_PARTY_LIBRARIES}/Box2D/Dynamics/*.h" "${THIRD_PARTY_LIBRARIES}/Box2D/Dynamics/*.cpp"
	"${THIRD_PARTY_LIBRARIES}/Box2D/Dynamics/Contacts/*.h" "${THIRD_PARTY_LIBRARIES}/Box2D/Dynamics/Contacts/*.cpp"
	"${THIRD_PARTY_LIBRARIES}/Box2D/Dynamics/Joints/*.h" "${THIRD_PARTY_LIBRARIES}/Box2D/Dynamics/Joints/*.cpp"
	"${THIRD_PARTY_LIBRARIES}/Box2D/Dynamics/Rope/*.h" "${THIRD_PARTY_LIBRARIES}/Box2D/Dynamics/Rope/*.cpp"
	"${THIRD_PARTY_LIBRARIES}/Box2D/Box2D.h"
)

file(GLOB SOURCE_FILES
	"${PROJ_NAME}/Controllers/include/*.hpp" "${PROJ_NAME}/Controllers/src/*.cpp"
	"${PROJ_NAME}/Core/include/*.hpp" "${PROJ_NAME}/Core/src/*.cpp"
	"${PROJ_NAME}/Entities/include/*.hpp" "${PROJ_NAME}/Entities/src/*.cpp"
	"${PROJ_NAME}/Scenes/include/*.hpp" "${PROJ_NAME}/Scenes/src/*.cpp"
)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES} ${PROJ_NAME}/main.cpp)

add_library(box2d_static_library STATIC IMPORTED)
set_target_properties(box2d_static_library PROPERTIES IMPORTED_LOCATION ${THIRD_PARTY_LIBRARIES}/libBox2D.a)
target_link_libraries(${EXECUTABLE_NAME} box2d_static_library)

find_package(SFML 2.3.2 REQUIRED graphics window system)
if(NOT SFML_FOUND)
    message(FATAL_ERROR "No SFML lib found in your system!")
endif()
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

find_package(TinyXML)
if (NOT TinyXML_FOUND)
    message(FATAL_ERROR "No TinyXML lib found in your system!")
endif()
include_directories(${TinyXML_INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE_NAME} ${TinyXML_LIBRARIES})
