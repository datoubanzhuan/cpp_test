
project(test01)
cmake_minimum_required(VERSION 3.4.1)
add_definitions(-std=c++11 -O2 -Wall)

# find all fires in a directory (<dir> <variable>)
aux_source_directory(. DIR_SRCS)

# (GLOB_RECUSE <variable> <globbing-expressions>...) 产生一个匹配<globbing-expressions>的文件列表并将它存储到变量<variable>中
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/*.h)

# add a executable using specified files (<name> [source1] [source2])
add_executable(${PROJECT_NAME} ${DIR_SRCS} ${HEADER_FILES})
MESSAGE(STATUS "compile")

# add specific library
    ## (<VAR> name... [path]...) find a library, set path to VAR 
    #find_library(RUNTIME_LIB rt /usr/lib /usr/local/lib NO_DEFAULT_PATH)
    ## (library <debug|optimized> library2...) link library added later
    #link_libraries(" /usr/local/lib64/libgtest.a")
    #link_libraries(gtest)

# add specific library
    ## add a library using specified source files (<name> [STATIC|SHARED|MODULE] [IMPORTED])
    #add_library(libgtest STATIC IMPORTED)
    ## set properties on targets (target1 target2 ... PROPERTIES prop1 value1 prop2 value2)
    #set_target_properties(libgtest PROPERTIES IMPORTED_LOCATION /usr/local/lib64/libgtest.a)

# generate a library and used in executable
    ## generate; like add_executable
    #add_library(lib_demo cmd.cpp md5.cpp)
    ## link to executable
    #link_libraries(lib_demo)
    ## generate executable
    #add_executable(demo main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# specify library (<target> ... <Item> ... )
target_link_libraries(${PROJECT_NAME} gtest pthread)

# install targets from a project (TARGETS <target>... [[ARCHIVE|LIBRARY|RUNTIME] [DESTINATION <dir>] ....)
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
