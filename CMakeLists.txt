cmake_minimum_required(VERSION 2.9)

set(TARGET_BUILD_PLATFORM x64)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add OpenCV:
set(OpenCV_STATIC OFF)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

project(opencl-project)

include_directories(./libs/OpenCL/)

file(GLOB OPENCL_PROJECT_SRC
	./src/opencl-project/*.h
	./src/opencl-project/*.cpp
)
add_executable(opencl-project ${OPENCL_PROJECT_SRC})

if(MSVC AND OpenCV_STATIC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif()

target_link_libraries(opencl-project  
	${OpenCV_LIBS}
	${CMAKE_CURRENT_SOURCE_DIR}/libs/OpenCL/lib/${TARGET_BUILD_PLATFORM}/OpenCL.lib
)

set(BINARY_DEBUG_DIR ${PROJECT_BINARY_DIR}/Debug/)
set(BINARY_RELEASE_DIR ${PROJECT_BINARY_DIR}/Release/)
file(MAKE_DIRECTORY ${BINARY_DEBUG_DIR})
file(MAKE_DIRECTORY ${BINARY_RELEASE_DIR})

file(GLOB DLL_FILES_DEBUG)
file(GLOB DLL_FILES_RELEASE)
file(COPY ${DLL_FILES_DEBUG} DESTINATION ${BINARY_DEBUG_DIR})
file(COPY ${DLL_FILES_RELEASE} DESTINATION ${BINARY_RELEASE_DIR})

file (GLOB DATA_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/data/*.*
)
file (COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR}/data/)

file (GLOB CL_SRC_FILES
	./src/opencl-project/*.cl
)
file (COPY ${CL_SRC_FILES} DESTINATION ${BINARY_DEBUG_DIR})
file (COPY ${CL_SRC_FILES} DESTINATION ${BINARY_RELEASE_DIR})
file (COPY ${CL_SRC_FILES} DESTINATION ${PROJECT_BINARY_DIR})