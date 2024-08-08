include(GNUInstallDirs)

SET(PKG_CONFIG_LIBS
    "-L\${libdir} -l${PROJECT_NAME}"
)
SET(PKG_CONFIG_CFLAGS
    "-I\${includedir}/lib_common -I\${includedir}/lib_stable -I\${includedir}/lib_advanced"
)

message(STATUS "Configuring \"${CMAKE_SOURCE_BINARY_DIR}/${PROJECT_NAME}.pc\"")

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc"
  @ONLY
)

install(
    FILES "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
