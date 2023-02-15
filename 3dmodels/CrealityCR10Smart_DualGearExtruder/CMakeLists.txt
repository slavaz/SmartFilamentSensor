set (FREECAD_OBJECT_NAMES "BearingSupport" "EngineMainBody" "EngineShaftWheel" "FilamentWheel" "MainBody")

foreach(FreeCadObject ${FREECAD_OBJECT_NAMES})

    configure_file(${PROJECT_SOURCE_DIR}/3dmodels/export-to-stl.freecad.script.in
        ${CMAKE_CURRENT_BINARY_DIR}/${FreeCadObject}.freecad.script)

    add_custom_target(generate_${FreeCadObject}.stl
        ALL
        DEPENDS
            ${FreeCadObject}.stl
            ${PROJECT_SOURCE_DIR}/3dmodels/export-to-stl.freecad.script.in
            ${CMAKE_CURRENT_BINARY_DIR}/${FreeCadObject}.freecad.script
            ${CMAKE_CURRENT_LIST_DIR}/${FreeCadObject}.FCStd
        COMMENT "Generating '${FreeCadObject}' STL file"
      )

      add_custom_command(
        COMMAND ${FREECAD_EXECUTABLE} < ${CMAKE_CURRENT_BINARY_DIR}/${FreeCadObject}.freecad.script
        DEPENDS 
            ${CMAKE_CURRENT_BINARY_DIR}/${FreeCadObject}.freecad.script
            ${CMAKE_CURRENT_LIST_DIR}/${FreeCadObject}.FCStd
        OUTPUT  ${FreeCadObject}.stl
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running FreeCAD for generate ${FreeCadObject}.stl"
    )

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${FreeCadObject}.stl DESTINATION 3d-models)

endforeach(FreeCadObject)
