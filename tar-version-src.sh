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
PROJECT_TOP_DIR=${PWD}

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

for i in COPYING Makefile-gen.mkf README.eng.md README.fra.md README.md configure.sh list_of_dynamic_functions_for_the_linker.txt ./tools-compile.sh ; do 
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


if ! ls ./tar-version-src/*.tgz > /dev/null 2>&1  ; then 
#if ! ls *.tgz 2>/dev/null ; then 
    #bsdtar czf ./tar-version-src/${MY_TARVERSION}.tgz --uname "" --gname "" -C ./tar-version-src/ ./${MY_TARVERSION}
    #cd ./tar-version-src/ &&  pax -w -z -x pax ./${MY_TARVERSION} > ./${MY_TARVERSION}.tgz ; cd ${PROJECT_TOP_DIR}
    bsdtar czf ./tar-version-src/${MY_TARVERSION}.tgz  --format pax --uname "" --gname "" -C ./tar-version-src/ ./${MY_TARVERSION}
    rm -Rf ./tar-version-src/${MY_TARVERSION}
    exit 0; 
fi; 


if false; then 
echo $*
echo $#
echo $0 
echo $1 
exit 0; 
fi; 

#set -x 
if test $# -ge 1 ; then 
    if test "$1" = "nodiff" ; then 
	#bsdtar czf ./tar-version-src/${MY_TARVERSION}.tgz --uname "" --gname "" -C ./tar-version-src/ ./${MY_TARVERSION}
	#cd ./tar-version-src/ &&  pax -w -z -x pax ./${MY_TARVERSION} > ./${MY_TARVERSION}.tgz ; cd ${PROJECT_TOP_DIR}
	bsdtar czf ./tar-version-src/${MY_TARVERSION}.tgz --format pax --uname "" --gname "" -C ./tar-version-src/ ./${MY_TARVERSION}
	rm -Rf ./tar-version-src/${MY_TARVERSION}
    exit 0; 
    fi; 
fi; 



LAST_TARVERSION=$(ls ./tar-version-src/*.tgz | sort | tail -1) 
LAST_TARVERSION=$(basename ${LAST_TARVERSION} .tgz)

#echo ${LAST_TARVERSION}

rm -Rf ./tar-version-src/${LAST_TARVERSION} 

bsdtar xzf ./tar-version-src/${LAST_TARVERSION}.tgz -C ./tar-version-src/ 
#cd ./tar-version-src/ &&  pax -r -z ./${MY_TARVERSION}  ; cd ${PROJECT_TOP_DIR}


# diff(1) returns non-zero status on success. 
#PROJECT_TOP_DIR=${PWD}
set +e 
#diff -u -r ./tar-version-src/${LAST_TARVERSION} ./tar-version-src/${MY_TARVERSION} > ./tar-version-src/${MY_TARVERSION}.diff
#diff -u -r ./tar-version-src/${LAST_TARVERSION} ./tar-version-src/${MY_TARVERSION} | gzip -f > ./tar-version-src/${MY_TARVERSION}.zdiff
#cd ./tar-version-src && diff -u -r ./${LAST_TARVERSION} ./${MY_TARVERSION} | gzip -f > ./${MY_TARVERSION}.zdiff
cd ./tar-version-src && diff -u -r -N -P ./${LAST_TARVERSION} ./${MY_TARVERSION} | gzip -f > ./${MY_TARVERSION}.zdiff
set -e 
cd ${PROJECT_TOP_DIR}

echo "${LAST_TARVERSION}" > ./tar-version-src/${MY_TARVERSION}.orig

rm -Rf ./tar-version-src/${LAST_TARVERSION} 
rm -Rf ./tar-version-src/${MY_TARVERSION} 

