# Generated files from folly/build/generate_*.py
auto_sources(genfiles "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/gen")

# Main folly library files
auto_sources(files "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/folly")
auto_sources(cfiles "*.c" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/folly")

# Subprocess requires flatmap from boost 1.48
# and some other folly pieces we're not including yet
# For now, that's not actually a requirement, so skip it
list(REMOVE_ITEM files ${CMAKE_CURRENT_SOURCE_DIR}/folly/Subprocess.cpp)
add_library(folly STATIC ${files} ${genfiles} ${cfiles} )

find_package(Boost 1.48.0 COMPONENTS system program_options filesystem regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

target_link_libraries(folly ${Boost_LIBRARIES})
