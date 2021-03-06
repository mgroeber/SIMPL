#///////////////////////////////////////////////////////////////////////////////
#//
#//  Copyright (c) 2009, Michael A. Jackson. BlueQuartz Software
#//  All rights reserved.
#//  BSD License: http://www.opensource.org/licenses/bsd-license.html
#//
#///////////////////////////////////////////////////////////////////////////////


# ------------------------------------------------------------------------------
# This CMake code sets up for CPack to be used to generate native installers
# ------------------------------------------------------------------------------
if(MSVC)
    # Skip the install rules, we only want to gather a list of the system libraries
    SET(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP 1)
    #SET(CMAKE_INSTALL_DEBUG_LIBRARIES OFF)

    if(NOT DREAM3D_DISABLE_DEPENDENCY_COPY_INSTALL_RULES)
      # Gather the list of system level runtime libraries
      include(InstallRequiredSystemLibraries)
    endif()

    # Our own Install rule for Release builds of the MSVC runtime libs
    if(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
      INSTALL(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
        DESTINATION ./
        PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ
        COMPONENT Applications
        CONFIGURATIONS Release)
    endif(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
endif()

if(UNIX AND NOT APPLE)
    SET(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP 0)
    if(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
      INSTALL(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
        DESTINATION ./lib
        PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ
        COMPONENT Applications
        CONFIGURATIONS Release)
    endif(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
endif()

message(STATUS "SIMPLProj_RELEASE_TYPE: ${SIMPLProj_RELEASE_TYPE}")
if("${SIMPLProj_RELEASE_TYPE}" STREQUAL "Official")
  set(SIMPL_VERSION_SHORT "${SIMPLProj_VERSION_MAJOR}.${SIMPLProj_VERSION_MINOR}.${SIMPLProj_VERSION_PATCH}")
elseif("${SIMPLProj_RELEASE_TYPE}" STREQUAL "Beta")
  set(SIMPL_VERSION_SHORT "${SIMPLProj_VERSION_MAJOR}.${SIMPLProj_VERSION_MINOR}-${SIMPLProj_RELEASE_TYPE}-${SIMPLProj_VERSION_TWEAK}")
elseif("${SIMPLProj_RELEASE_TYPE}" STREQUAL "Development")
  set(SIMPL_VERSION_SHORT "${SIMPLProj_VERSION_MAJOR}.${SIMPLProj_VERSION_MINOR}.${SIMPLProj_VERSION_PATCH}.${SIMPLProj_VERSION_TWEAK}")
else()
  set(SIMPL_VERSION_SHORT "0.0.0")
endif()


message(STATUS "SIMPL_VERSION_SHORT: ${SIMPL_VERSION_SHORT}")


SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SIMPLView Tools")
SET(CPACK_PACKAGE_VENDOR "BlueQuartz Software, LLC")
#SET(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_BINARY_DIR}/ReadMe.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_RESOURCES_DIR}/SIMPL/SIMPLLicense.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR ${SIMPL_VER_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${SIMPL_VER_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${SIMPL_VER_PATCH})
SET(CPACK_PACKAGE_VERSION ${SIMPL_VERSION})
#SET(CPACK_COMPONENTS_ALL Applications Headers)
#set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Applications")
#set(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION  "The SIMPL Software Tools Suite")
#set(CPACK_COMPONENT_APPLICATIONS_REQUIRED 1)
#set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Headers")
#set(CPACK_COMPONENT_HEADERS_DESCRIPTION  "Development Header Files")
#set(CPACK_COMPONENT_HEADERS_REQUIRED 0)
#set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime")
#set(CPACK_COMPONENT_RUNTIME_DESCRIPTION  "Runtime Libraries")
#set(CPACK_COMPONENT_RUNTIME_REQUIRED 1)

set(CPACK_PACKAGE_EXECUTABLES
    SIMPL SIMPL StatsGenerator StatsGenerator DevHelper DevHelper)
set(UPLOAD_FILE_NAME "")

if(APPLE)
    set(CPACK_PACKAGE_FILE_NAME "SIMPL-${SIMPL_VERSION_SHORT}-OSX")
    # This ASSUMES we are creating a tar.gz package. If you change that below to
    # anything else then you need to update this.
    set(UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.tar.gz)
elseif(WIN32)
    if( "${CMAKE_SIZEOF_VOID_P}" EQUAL "8" )
            set(CPACK_PACKAGE_FILE_NAME "SIMPL-${SIMPL_VERSION_SHORT}-Win64")
            set(UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.zip)
    elseif( "${CMAKE_SIZEOF_VOID_P}" EQUAL "4" )
            set(CPACK_PACKAGE_FILE_NAME "SIMPL-${SIMPL_VERSION_SHORT}-Win32")
            set(UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.zip)
    else()
        set(CPACK_PACKAGE_FILE_NAME "SIMPL-${SIMPL_VERSION_SHORT}-Unknown")
        set(UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.zip)
    endif()
else()
    if( "${CMAKE_SIZEOF_VOID_P}" EQUAL "8" )
            set(CPACK_PACKAGE_FILE_NAME "SIMPL-${SIMPL_VERSION_SHORT}-${SIMPL_LINUX_SYSTEM}-x86_64")
            set(UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.tar.gz)
    elseif( "${CMAKE_SIZEOF_VOID_P}" EQUAL "4" )
            set(CPACK_PACKAGE_FILE_NAME "SIMPL-${SIMPL_VERSION_SHORT}-${SIMPL_LINUX_SYSTEM}-i386")
            set(UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.tar.gz)
    else()
        set(CPACK_PACKAGE_FILE_NAME "SIMPL-${SIMPL_VERSION_SHORT}-${CMAKE_SYSTEM_NAME}")
        set(UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.tar.gz)
    endif()
endif()


set(SIMPL_WEBSITE_SERVER "thor.bluequartz.net")
set(SIMPL_WEBSITE_SERVER_PATH "/var/www/dream3d-wp.bluequartz.net")
set(SIMPL_WEBSITE_SCP_USERNAME "mjackson")
#-- Create a bash script file that will upload the latest version to the web server
configure_file(${PROJECT_RESOURCES_DIR}/upload.sh.in
            ${PROJECT_BINARY_DIR}/upload.sh)
if(WIN32)
    configure_file(${PROJECT_RESOURCES_DIR}/copy_nightly.bat.in
            ${PROJECT_BINARY_DIR}/copy_nightly.bat)
endif()

# Create an ZIP based installer for Windows Systems
if(WIN32 AND NOT UNIX)
  # There is a bug in NSIS that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  SET(CPACK_NSIS_DISPLAY_NAME "SIMPLView Software Tools")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\dream3d.bluequartz.net")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\dream3d.bluequartz.net")
  SET(CPACK_NSIS_CONTACT "dream3d@bluequartz.net")
  SET(CPACK_NSIS_MODIFY_PATH ON)
  SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "SIMPL Software Tools")
ENDif(WIN32 AND NOT UNIX)

if(NOT CPACK_GENERATOR)
  if(UNIX)
    if(CYGWIN)
      option(CPACK_BINARY_CYGWIN "Enable to build Cygwin binary packages" ON)
    else(CYGWIN)
      if(APPLE)
        option(CPACK_BINARY_PACKAGEMAKER "Enable to build PackageMaker packages" OFF)
        option(CPACK_BINARY_OSXX11       "Enable to build OSX X11 packages"      OFF)
      else(APPLE)
        option(CPACK_BINARY_TZ  "Enable to build TZ packages"     OFF)
      endif(APPLE)
      option(CPACK_BINARY_STGZ "Enable to build STGZ packages"    OFF)
      option(CPACK_BINARY_TGZ  "Enable to build TGZ packages"     ON)
      option(CPACK_BINARY_TBZ2 "Enable to build TBZ2 packages"    OFF)
      option(CPACK_BINARY_DEB  "Enable to build Debian packages"  OFF)
      option(CPACK_BINARY_RPM  "Enable to build RPM packages"     OFF)
      option(CPACK_BINARY_NSIS "Enable to build NSIS packages"    OFF)
    endif(CYGWIN)
  else(UNIX)
    option(CPACK_BINARY_NSIS "Enable to build NSIS packages" OFF)
    option(CPACK_BINARY_ZIP  "Enable to build ZIP packages" ON)
  endif(UNIX)

endif(NOT CPACK_GENERATOR)


SET(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "SIMPL-${SIMPL_VERSION_SHORT}-Source")

#-- Create a bash script file that will upload the latest version to the web server
set(UPLOAD_FILE_NAME ${CPACK_SOURCE_PACKAGE_FILE_NAME}.tar.gz)
configure_file(${PROJECT_RESOURCES_DIR}/upload.sh.in
               ${PROJECT_BINARY_DIR}/src_upload.sh)

#-- Create a bash script file that will upload a version file to the server
configure_file(${PROJECT_RESOURCES_DIR}/version_upload.sh.in
               ${PROJECT_BINARY_DIR}/version_upload.sh)

SET(CPACK_SOURCE_TOPLEVEL_TAG "Source")
SET(CPACK_IGNORE_FILES "/i386/;/x64/;/VS2008/;/zRel/;/Build/;/\\\\.git/;\\\\.*project")
SET(CPACK_SOURCE_IGNORE_FILES "/i386/;/x64/;/VS2008/;/zRel/;/Build/;/\\\\.git/;\\\\.*project")



# THIS MUST BE THE LAST LINE OF THIS FILE BECAUSE ALL THE CPACK VARIABLES MUST BE
# DEFINED BEFORE CPack IS INCLUDED
INCLUDE(CPack)

