setupSources(SOURCES
        Command.cpp
        Command2010Exporter2010.cpp
        Command2010Importer2010.cpp

GROUP datablocks\\commands)

include(${CMAKE_CURRENT_LIST_DIR}/ecucommands/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/luxcommands/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/miniluxcommands/CMakeLists.txt)
