
find_file (FREECAD_EXECUTABLE NAMES FreeCADCmd)

if (NOT EXISTS ${FREECAD_EXECUTABLE})
    find_file (FREECAD_EXECUTABLE NAMES freecad.cmd)
endif()

if (NOT EXISTS ${FREECAD_EXECUTABLE})
    message( FATAL_ERROR "FreeCAD not found!" )
endif()

add_subdirectory(CrealityCR10Smart_DualGearExtruder)
