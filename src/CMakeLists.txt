cmake_minimum_required ( VERSION 2.8 )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# add the binary tree to the search path for include files
# so that we will find config.h
include_directories("${PROJECT_BINARY_DIR}")


add_library(legodimensions STATIC legodimensions.c legodimensions_ntag.c legodimensions_characters.c legodimensions_vehicles.c utils.c tea.c)
#target_include_directories(legodimensions PUBLIC ${GLIB2_INCLUDE_DIRS})

#add_library(glib-legodimensions SHARED legodimensions-nfctag.c)

add_library(ultralight STATIC common.c ultralight.c)

add_executable(ulread ulread.c)
target_link_libraries(ulread ultralight nfc)

add_executable(ulwrite ulwrite.c)
target_link_libraries(ulwrite ultralight nfc)

add_executable(ldpwgen ldpwgen.c)
target_link_libraries(ldpwgen ${GLIB2_LIBRARIES} legodimensions)

add_executable(ldcli ldcli.c ldnfc.c)
target_link_libraries(ldcli ${GLIB2_LIBRARIES} legodimensions ultralight nfc)


# convert gui description file (.glade) into .c
add_custom_command (
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gresource.c
	COMMAND glib-compile-resources --generate-source --sourcedir=${PROJECT_SOURCE_DIR} --target=${CMAKE_CURRENT_BINARY_DIR}/gresource.c ${CMAKE_CURRENT_SOURCE_DIR}/ldnfcgui.gresource.xml
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ldnfcgui.gresource.xml
	${PROJECT_SOURCE_DIR}/gui/ldnfcgui.glade
)

add_executable(ldmachine
	ldmachine.c gui.c guicallbacks.c gresource.c )
target_link_libraries(ldmachine ${GLIB2_LIBRARIES} ${GTK3_LIBRARIES} legodimensions ultralight nfc)

add_executable( lddb 
	lddb-main.cpp 
	lddb-window.cpp lddb-window.h 
	lddb-model.cpp lddb-model.h
	legodimensions_characters.c )
target_link_libraries( lddb ${GLIB2_LIBRARIES} ${GTKMM_LIBRARIES})

#add_executable(ldgui ldgui-main.cpp ldgui-application.h ldgui-application.cpp)
#target_compile_features(ldgui PRIVATE cxx_noexcept cxx_auto_type cxx_nullptr cxx_decltype)
#target_link_libraries(ldgui ${GTKMM_LIBRARIES} legodimensions ultralight nfc)

include(CTest)
# does the application run
add_test(ldpwgen-runs ldpwgen -u 049249D2AC4A80)
add_test(ldpwgen-usage ldpwgen)
set_tests_properties (ldpwgen-usage
  PROPERTIES
  PASS_REGULAR_EXPRESSION "Usage:.*-u <7 byte uid in HEX>"
)
add_test(ldpwgen-pwd ldpwgen -u 040b4922a34881)
set_tests_properties (ldpwgen-pwd
  PROPERTIES PASS_REGULAR_EXPRESSION "72c7bf53"
)

add_test(ldpwgen-pwd-character ldpwgen -u 040b4922a34881 -c 13)
set_tests_properties (ldpwgen-pwd-character
  PROPERTIES PASS_REGULAR_EXPRESSION "35b9af33.+e290d5e7.+72c7bf53"
)



