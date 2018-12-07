cmake_minimum_required( VERSION 3.0 )
project( ECS )

set( CMAKE_CXX_STANDARD 17 )

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7.0)")
		message(FATAL_ERROR "Insufficient gcc version : ${CMAKE_CXX_COMPILER_VERSION}")
	endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "your.required.msvc.version")
		message(FATAL_ERROR "Insufficient msvc version : ${CMMAKE_CXX_COMPILER_VERSION}")
	endif()
elseif(...)
	# etc.
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -pedantic -Wfloat-equal -Wshadow \
	-Weffc++ -Wstrict-overflow=5 -Wcast-align -Wconversion -ftrapv \
	-Wuninitialized -Wuseless-cast -Wold-style-cast -Wnon-virtual-dtor -Wfloat-equal")
endif()


add_executable( ECS
				main.cpp
				src/EcsComponent.hpp src/EcsComponent.cpp
				src/EcsCore.hpp src/EcsCore.cpp
				src/EcsInteraction.cpp
				src/EcsSystem.hpp src/EcsSystem.cpp
				src/utils.hpp
				src/Position.hpp
				src/CollisionEngine.cpp src/CollisionEngine.hpp src/Math/Vector3.cpp src/Math/Vector3.hpp src/Math/common.hpp )