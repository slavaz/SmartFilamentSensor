#!/bin/bash

source $1

RELEASE_TYPE=$2
RELEASE_BUILD_DIR=${CMAKE_CURRENT_BINARY_DIR}/release_build

check_uncommitted_files(){
    test -n "$(git status --short --untracked-files=no)" && {
        echo 'You have uncommitted changes!'
        exit 1
    }
}

check_that_current_branch_is_main(){
    BRANCH_NAME="$(git rev-parse --abbrev-ref HEAD)"
    test "main" != "${BRANCH_NAME}" && {
        echo "Current git branch shound be 'main'"
        exit 1
    }
}

get_next_version(){
    RELEASE_TYPE=$1

    case "${RELEASE_TYPE}" in
        MAJOR)
            SCRIPT_FLAG="-M"
        ;;
        MINOR)
            SCRIPT_FLAG="-m"
        ;;
        PATCH)
            SCRIPT_FLAG="-p"
        ;;
    esac
    test -z "${SCRIPT_FLAG}" && {
        return
    }
    "${CMAKE_SOURCE_DIR}/scripts/increment_version.sh" "${SCRIPT_FLAG}" "${GIT_TAG}"
}

create_new_git_tag(){
    NEXT_VERSION=$1
    git tag "${NEXT_VERSION}"
}

make_package() {
    rm -fr "${RELEASE_BUILD_DIR}" 
    mkdir -p "${RELEASE_BUILD_DIR}"
    pushd "${RELEASE_BUILD_DIR}"
     cmake "${CMAKE_SOURCE_DIR}" && make package
     RETURN_CODE=$?
    popd
    test ${RETURN_CODE} -ne 0 && exit 1
}

copy_package_to_release_dir(){
    NEXT_VERSION=$1
    RELEASE_DIR="${CMAKE_SOURCE_DIR}/releases/${NEXT_VERSION}"
    mkdir -p "${RELEASE_DIR}"
    cp "${RELEASE_BUILD_DIR}/package/"*.tar.bz2 "${RELEASE_DIR}"
}

commit_changes(){
    NEXT_VERSION=$1
    RELEASE_DIR="${CMAKE_SOURCE_DIR}/releases/${NEXT_VERSION}"

    git add "${RELEASE_DIR}"
    git commit -m "New ${RELEASE_TYPE} version release: ${NEXT_VERSION}"
}

recreate_git_tag(){
    NEXT_VERSION=$1

    git tag -d "${NEXT_VERSION}"
    git tag "${NEXT_VERSION}"
}

push_changes(){
    NEXT_VERSION=$1

    git push origin main
    git push origin "${NEXT_VERSION}"
}

# ---------------------------------------------------------------------------------------------

#check_uncommitted_files

check_that_current_branch_is_main

NEXT_VERSION=$(get_next_version "${RELEASE_TYPE}")

[ -z "${NEXT_VERSION}" ] && {
        echo "2'n argument (RELEASE_TYPE) should be one of: MAJPR, MINOR, PATCH" 
        exit 1
}

create_new_git_tag "${NEXT_VERSION}"

make_package

copy_package_to_release_dir "${NEXT_VERSION}"

commit_changes "${NEXT_VERSION}"

recreate_git_tag "${NEXT_VERSION}"

push_changes "${NEXT_VERSION}"
