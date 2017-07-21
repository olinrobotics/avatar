INCLUDE(FindPackageHandleStandardArgs)

set(CATKIN_INCLUDE_DIR /usr/local/include)

SET(CATKIN_LibrarySearchPaths
        /usr/local/lib
        /usr/lib)

FIND_LIBRARY(CATKIN_LIBRARY
        NAMES catkin
        PATHS ${DLIB_LibrarySearchPaths}
        CMAKE_PREFIX_PATH std_msgs)

FIND_PACKAGE_AHNDLE_STANDARD_ARGS(CATKIN "Could NOT find CATKIN library"
        CATKIN_LIBRARY
        CATKIN_INCLUDE_DIR)

SET(CATKIN_LIBRARIES)
LIST(APPEND CATKIN_LIBRARIES ${CATKIN_LIBRARY})

MARK_AS_ADVANCED(
        CATKIN_INCLUDE_DIR
        DLIB_LIBRARIES
        DLIB_FOUND
)
