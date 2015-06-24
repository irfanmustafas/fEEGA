cmake_minimum_required (VERSION 2.8.6 FATAL_ERROR)
project (fEEGA)

if (WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/fEEGA" CACHE PATH "Change default directory in windows" FORCE)
endif (WIN32)

# Project name
project ("libfEEGA")

# Project version number
set (Tutorial_VERSION_MAJOR  0  CACHE)
set (Tutorial_VERSION_MINOR  0  CACHE)
mark_as_advanced(VERSION_MAJOR VERSION_MINOR)


include_directories ( ${PROJECT_BINARY_DIR}/include )

# Compile variable for FFTW library path
set(FFTW_PATH "" CACHE PATH "Path the FFTW folder")

add_subdirectory (src)

# Build a library
add_library (fEEGA SHARED ${fEEGA_SRCS} ${fEEGA_INCS})

# Necessary for windows .dll support
generate_export_header(fEEGA
    EXPORT_MACRO_NAME fEEGA_EXPORT
    EXPORT_FILE_NAME include/fEEGA/fEEGA_export.h)
