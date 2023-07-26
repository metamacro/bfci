macro(set_local_and_parent NAME VALUE)
    set(${ARGV0} ${ARGV1})
    set(${ARGV0} ${ARGV1} PARENT_SCOPE)
endmacro()


macro(git_submodule_update_init)
    find_package(Git QUIET)

    if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        set(GIT_SUBMODULE_UPDATE_INIT_CMD 
            ${GIT_EXECUTABLE} submodule update --init)

        execute_process(COMMAND ${GIT_SUBMODULE_UPDATE_INIT_CMD}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)

        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR 
                    "Failed command: \'${GIT_SUBMODULE_UPDATE_INIT_CMD}\'")
        else()
            message(STATUS 
                    "Git submodule update init done")
        endif()
    endif()
endmacro()
