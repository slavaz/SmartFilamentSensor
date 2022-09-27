
execute_process(COMMAND git describe  --abbrev=0 --tags
                OUTPUT_VARIABLE GIT_TAG
                ERROR_QUIET)

if(NOT GIT_TAG)
    set(GIT_TAG "0.0")
endif()

execute_process(COMMAND git log --pretty=format:'%h' -n 1
    OUTPUT_VARIABLE GIT_REV ERROR_QUIET)

execute_process(COMMAND git rev-parse --abbrev-ref HEAD
    OUTPUT_VARIABLE GIT_BRANCH ERROR_QUIET)

string(STRIP "${GIT_TAG}" GIT_TAG)
string(STRIP "${GIT_REV}" GIT_REV)
string(SUBSTRING "${GIT_REV}" 1 7 GIT_REV)
string(STRIP "${GIT_BRANCH}" GIT_BRANCH)

set(VERSION "${GIT_TAG}-${GIT_REV}-${GIT_BRANCH}")
