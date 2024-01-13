# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(rapidcsv_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(rapidcsv_FRAMEWORKS_FOUND_DEBUG "${rapidcsv_FRAMEWORKS_DEBUG}" "${rapidcsv_FRAMEWORK_DIRS_DEBUG}")

set(rapidcsv_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET rapidcsv_DEPS_TARGET)
    add_library(rapidcsv_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET rapidcsv_DEPS_TARGET
             PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${rapidcsv_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${rapidcsv_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:>
             APPEND)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### rapidcsv_DEPS_TARGET to all of them
conan_package_library_targets("${rapidcsv_LIBS_DEBUG}"    # libraries
                              "${rapidcsv_LIB_DIRS_DEBUG}" # package_libdir
                              "${rapidcsv_BIN_DIRS_DEBUG}" # package_bindir
                              "${rapidcsv_LIBRARY_TYPE_DEBUG}"
                              "${rapidcsv_IS_HOST_WINDOWS_DEBUG}"
                              rapidcsv_DEPS_TARGET
                              rapidcsv_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "rapidcsv"    # package_name
                              "${rapidcsv_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${rapidcsv_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET rapidcsv::rapidcsv
                 PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${rapidcsv_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${rapidcsv_LIBRARIES_TARGETS}>
                 APPEND)

    if("${rapidcsv_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET rapidcsv::rapidcsv
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     rapidcsv_DEPS_TARGET
                     APPEND)
    endif()

    set_property(TARGET rapidcsv::rapidcsv
                 PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${rapidcsv_LINKER_FLAGS_DEBUG}> APPEND)
    set_property(TARGET rapidcsv::rapidcsv
                 PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${rapidcsv_INCLUDE_DIRS_DEBUG}> APPEND)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET rapidcsv::rapidcsv
                 PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${rapidcsv_LIB_DIRS_DEBUG}> APPEND)
    set_property(TARGET rapidcsv::rapidcsv
                 PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${rapidcsv_COMPILE_DEFINITIONS_DEBUG}> APPEND)
    set_property(TARGET rapidcsv::rapidcsv
                 PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${rapidcsv_COMPILE_OPTIONS_DEBUG}> APPEND)

########## For the modules (FindXXX)
set(rapidcsv_LIBRARIES_DEBUG rapidcsv::rapidcsv)
