set(BOOST_PATHS $ENV{HOME}/Apps/boost)

message("Boost configure")

find_path(Boost_INCLUDE_DIR boost/version.hpp PATH_SUFFIXES include PATHS ${BOOST_PATHS})
# find_library(Boost_LIBRARIES noboost PATH_SUFFIXES lib64 lib PATHS ${BOOST_PATHS})
