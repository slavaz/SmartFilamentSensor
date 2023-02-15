
find_file (FREECAD_EXECUTABLE NAMES FreeCADCmd freecad.cmd)

if (EXISTS ${FREECAD_EXECUTABLE})
    add_subdirectory(CrealityCR10Smart_DualGearExtruder)
else()
    message( WARNING "FreeCAD not found! STL files will not be generated. Please install FreeCAD")
endif()

