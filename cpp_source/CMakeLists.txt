cmake_minimum_required( VERSION 2.8 )
project( engineapp C CXX )


# set default build type
if(NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
	set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")
endif()

include( CheckCXXCompilerFlag )
check_cxx_compiler_flag( "-std=c++11"   COMPILER_SUPPORTS_CXX11 )
if( COMPILER_SUPPORTS_CXX11 )
    if( CMAKE_COMPILER_IS_GNUCXX )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11" )
    else()
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
    endif()
endif()

if(ENGINE_DEBUGON)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENGINE_DEBUGON")
endif()
if(LICENSE_ON)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLICENSE_ON")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,./")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH} ./")
endif() 

#########################

file(GLOB_RECURSE HEADER_FILES 
	${PROJECT_SOURCE_DIR}/include/*.h 
	${PROJECT_SOURCE_DIR}/include/*.hpp
	${PROJECT_SOURCE_DIR}/*.h 
	${PROJECT_SOURCE_DIR}/*.hpp
)
source_group("Include" FILES ${HEADER_FILES})
aux_source_directory(. DIR_SRCS)

#include_directories(${PROJECT_SOURCE_DIR}/../include)
#include_directories(${PROJECT_SOURCE_DIR}/../../include)
#include_directories(${PROJECT_SOURCE_DIR}/../../common/loghelper/include)
#include_directories(${PROJECT_SOURCE_DIR}/../../common/netmodule/include)
#include_directories(${PROJECT_SOURCE_DIR}/../appconfig_reader)
#include_directories(${PROJECT_SOURCE_DIR}/../../common/message_type_reader)
#include_directories(${PROJECT_SOURCE_DIR}/../../common/curlftp)
#include_directories(${PROJECT_SOURCE_DIR}/../../common/license)
#include_directories(${PROJECT_SOURCE_DIR}/../../include/curl)


#link_directories(${PROJECT_SOURCE_DIR}/../lib)
#if(CMAKE_CL_64)
#link_directories(${PROJECT_SOURCE_DIR}/../lib/ubuntu16.04)
#else()
#    if(CENTOS32)
#    link_directories(${PROJECT_SOURCE_DIR}/../lib/centos7_32)
#    else()
#    link_directories(${PROJECT_SOURCE_DIR}/../lib/ubuntu16.04_32)
#    endif()
#endif()
#link_directories(${PROJECT_SOURCE_DIR}/../../lib)

add_executable(${PROJECT_NAME} ${DIR_SRCS} ${HEADER_FILES})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DROCK_LINUX_PLATFORM -DBOOST_LOG_DYN_LINK)
	# TODO
    MESSAGE(STATUS "current platform: Linux")
    target_link_libraries(${PROJECT_NAME}
        opencv_core
        opencv_highgui
        opencv_imgproc
        boost_system
        boost_filesystem
        boost_program_options
	pthread)
    if( CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_libraries(${PROJECT_NAME}
#			licenseclient-d
#            		tcpclient-d
    )
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_link_libraries(${PROJECT_NAME}
#			licenseclient
#            		tcpclient
    )
    endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")

	target_link_libraries(${PROJECT_NAME}
    )
    
    if( CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_libraries(${PROJECT_NAME}
			opencv_core2411d
			opencv_highgui2411d
			opencv_imgproc2411d
        )
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_link_libraries(${PROJECT_NAME}
			opencv_core2411
			opencv_highgui2411
			opencv_imgproc2411
        )
    endif()

endif()

########################

INSTALL(TARGETS ${PROJECT_NAME} 
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)
