find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_LIST_DIR}/Doxyfile)

    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/docs
            DESTINATION ${CMAKE_INSTALL_DOCDIR}
            OPTIONAL
            COMPONENT documentation)
else()
    message("Doxygen need to be installed to generate the doxygen documentation")
endif()
