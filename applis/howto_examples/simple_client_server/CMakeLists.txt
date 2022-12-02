file (GLOB simple_server_sources ./simple_server.c)

set(SIMPLE_SERVER_BIN ${EXECUTABLE_OUTPUT_PATH}/simple_server CACHE STRING "simple_server exe")
add_executable(simple_server ${simple_server_sources})

target_link_libraries(simple_server openfec m)


file (GLOB simple_client_sources ./simple_client.c)

set(SIMPLE_SERVER_BIN ${EXECUTABLE_OUTPUT_PATH}/simple_client CACHE STRING "simple_client exe")
add_executable(simple_client ${simple_client_sources})

target_link_libraries(simple_client openfec m)

if(INSTALL_DEVTOOLS)
  install(TARGETS simple_server simple_client
    RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
    COMPONENT applis)
endif()
