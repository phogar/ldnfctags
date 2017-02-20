cmake_minimum_required ( VERSION 3.5 )

project(LegoDimensionsTagHandler C CXX)

set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 3)

find_package(PkgConfig)

pkg_check_modules(LIBNFC REQUIRED libnfc>=1.7.1)

# look into FindPkgConfig.cmake, it contains documentation.
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0>=3.4)
# Now the variables
# GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES 
# contain what you expect 

pkg_check_modules(GLIB2 REQUIRED glib-2.0>=2.40)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0>=3.10)


include_directories( 
	${LIBNFC_INCLUDE_DIRS}
	${GLIB2_INCLUDE_DIRS}
	${GTK3_INCLUDE_DIRS}
	${GTKMM_INCLUDE_DIRS})

link_directories(
	${LIBNFC_LIBRARY_DIRS}
	${GLIB2_LIBRARY_DIRS}
	${GTK3_LIBRARY_DIRS}
	${GTKMM_LIBRARY_DIRS})

add_subdirectory(src)

