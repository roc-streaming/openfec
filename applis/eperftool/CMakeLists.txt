file (GLOB eperftool_sources ./*)

set(EPERFTOOL_BIN ${EXECUTABLE_OUTPUT_PATH}/eperftool CACHE STRING "eperftool exe")
add_executable( eperftool ${eperftool_sources})


target_link_libraries( eperftool openfec m)

if(INSTALL_DEVTOOLS)
  install(TARGETS eperftool
    RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
    COMPONENT devtools)
endif()
