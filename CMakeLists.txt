cmake_minimum_required(VERSION 3.22) # Require Ubuntu 22.04's apt-provided CMake version or newer.
project(biggish VERSION 0.1.0 LANGUAGES C) # Name this project, give it a small version, and say it only uses C.

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR) # Check whether the build directory is the same as the source directory.
    message(FATAL_ERROR "Please use an out-of-source build, for example: cmake -S . -B build") # Stop before CMake writes generated files into the source tree.
endif() # End the out-of-source build check.

set(CMAKE_C_STANDARD 11) # Ask CMake to compile C files as C11.
set(CMAKE_C_STANDARD_REQUIRED ON) # Tell CMake that C11 is required, not just preferred.
set(CMAKE_C_EXTENSIONS OFF) # Prefer portable C11 flags instead of compiler-specific GNU extensions.

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE) # Check whether a single-config generator has no build type yet.
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type: Debug, Release, RelWithDebInfo, or MinSizeRel" FORCE) # Default single-config builds to Debug.
endif() # End the default build type setup.

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel) # Show common build-type choices in CMake GUIs.

set(LIMB_SIZE 32 CACHE STRING "Limb size in bits; supported values are 32 and 64") # Create a user-settable CMake cache variable for the limb width.
set_property(CACHE LIMB_SIZE PROPERTY STRINGS 32 64) # Show the supported limb-size choices in CMake GUIs.

if(NOT LIMB_SIZE STREQUAL "32" AND NOT LIMB_SIZE STREQUAL "64") # Validate that the user chose one of the supported limb sizes.
    message(FATAL_ERROR "LIMB_SIZE must be 32 or 64; configure with -DLIMB_SIZE=32 or -DLIMB_SIZE=64") # Stop with a helpful error for unsupported values.
endif() # End the limb-size validation.

add_library(biggish_lib STATIC src/biggish.c) # Build the reusable biggish code as a static library.
add_library(biggish::lib ALIAS biggish_lib) # Provide a namespaced alias that other CMake targets can link to.

target_include_directories(biggish_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # Make the public header directory available to this library and anything that links to it.

# The current header uses 32-bit limbs when LIMB_SIZE is not defined, so only 64-bit builds need an added definition.
if(LIMB_SIZE STREQUAL "64") # Check whether the requested limb size is 64 bits.
    target_compile_definitions(biggish_lib PUBLIC LIMB_SIZE=64) # Define LIMB_SIZE for the library and for targets that consume its header.
endif() # End the 64-bit limb configuration.

add_executable(biggish src/main.c) # Build the command-line/demo program from main.c.
target_link_libraries(biggish PRIVATE biggish::lib) # Link the executable against the biggish library target.
