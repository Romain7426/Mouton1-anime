#!/bin/sh

# Stop on first error 
set -e 

# Stop if any used variable is unset 
set -u

# Print every command 
#set -x 
# Do not print commands 
set +x

# The return value of a pipe is the first one that fails. 
set -o pipefail

MY_DATE=$(TZ="UTC"  date  "+%Y_%m_%d-%Hh%Mm%Ss") 
MY_NAME=$(basename ${PWD})
MY_TARVERSION=${MY_NAME}.${MY_DATE}

if false ; then 
echo ${MY_DATE}
echo ${MY_NAME}
echo ${MY_TARVERSION}
fi

mkdir -p ./tar-version-src
mkdir -p ./tar-version-src/${MY_TARVERSION}
mkdir -p ./tar-version-src/${MY_TARVERSION}/src
mkdir -p ./tar-version-src/${MY_TARVERSION}/tools
mkdir -p ./tar-version-src/${MY_TARVERSION}/tools/src

for i in COPYING Makefile-gen.mkf README.eng.md README.fra.md README.md configure.sh dynamic_list_of_functions_for_the_linker.txt ./tools-compile.sh ; do 
    FILE=$(basename ${i})
    ln ./${FILE} ./tar-version-src/${MY_TARVERSION}/${FILE}
done;

for i in src/*.c src/*.h src/*.ci src/*.anime ; do 
    FILE=$(basename ${i})
    ln src/${FILE} ./tar-version-src/${MY_TARVERSION}/src/${FILE}
done;

for i in tools/src/* ; do 
    FILE=$(basename ${i})
    ln tools/src/${FILE} ./tar-version-src/${MY_TARVERSION}/tools/src/${FILE}
done;

bsdtar czf ./tar-version-src/${MY_TARVERSION}.tgz --uname "" --gname "" -C ./tar-version-src/ ./${MY_TARVERSION}

rm -Rf ./tar-version-src/${MY_TARVERSION}

