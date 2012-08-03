# - Try to find CppFontconfig
# Once done, this will define
#
#  CppFontconfig_FOUND - system has CppFontconfig
#  CppFontconfig_INCLUDE_DIRS - the CppFontconfig include directories
#  CppFontconfig_LIBRARIES - link these to use CppFontconfig

include(LibFindMacros)

# Include dir
find_path(CppFontconfig_INCLUDE_DIR
  NAMES cppfontconfig/cppfontconfig.h
)

# Finally the library itself
find_library(CppFontconfig_LIBRARY
  NAMES cppfontconfig
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(CppFontconfig_PROCESS_INCLUDES CppFontconfig_INCLUDE_DIR)
set(CppFontconfig_PROCESS_LIBS CppFontconfig_LIBRARY)
libfind_process(CppFontconfig)

