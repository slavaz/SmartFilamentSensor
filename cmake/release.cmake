
configure_file(${CMAKE_SOURCE_DIR}/scripts/release-variables.sh.in
    ${CMAKE_CURRENT_BINARY_DIR}/scripts/release-variables.sh
)

add_custom_target(release_major
    COMMAND "${CMAKE_SOURCE_DIR}/scripts/release-new-version.sh" ${CMAKE_CURRENT_BINARY_DIR}/scripts/release-variables.sh MAJOR
    COMMENT "Release"
  )

add_custom_target(release_minor
    COMMAND "${CMAKE_SOURCE_DIR}/scripts/release-new-version.sh" ${CMAKE_CURRENT_BINARY_DIR}/scripts/release-variables.sh MINOR
    COMMENT "Release"
  )

add_custom_target(release_patch
    COMMAND "${CMAKE_SOURCE_DIR}/scripts/release-new-version.sh" ${CMAKE_CURRENT_BINARY_DIR}/scripts/release-variables.sh PATCH
    COMMENT "Release"
  )

add_custom_target(release
    DEPENDS  release_minor
    COMMENT "Release"
  )
