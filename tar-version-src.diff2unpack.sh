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



if test $# -ne 1 ; then 
    printf "diff version required\n" 
    exit 1;
fi; 

MY_TARVERSION=$1

if test ! -e ./tar-version-src/${MY_TARVERSION}.zdiff ; then
    printf "File '%s' missing\n" ./tar-version-src/${MY_TARVERSION}.zdiff
    exit 2;
fi; 

if test ! -e ./tar-version-src/${MY_TARVERSION}.orig ; then
    printf "File '%s' missing\n" ./tar-version-src/${MY_TARVERSION}.orig
    exit 2;
fi; 

LAST_TARVERSION=$(cat ./tar-version-src/${MY_TARVERSION}.orig) 

rm -Rf ./tar-version-src/${LAST_TARVERSION} 
rm -Rf ./tar-version-src/${MY_TARVERSION}
rm -Rf ./tar-version-src/${MY_TARVERSION}.tgz

bsdtar xzf ./tar-version-src/${LAST_TARVERSION}.tgz -C ./tar-version-src/ 

#gzcat ./tar-version-src/${MY_TARVERSION}.zdiff | patch  -u 
gzcat ./tar-version-src/${MY_TARVERSION}.zdiff | patch -d ./tar-version-src/ -u 1>/dev/null

mv ./tar-version-src/${LAST_TARVERSION} ./tar-version-src/${MY_TARVERSION} 

#bsdtar czf ./tar-version-src/${MY_TARVERSION}.tgz --uname "" --gname "" -C ./tar-version-src/ ./${MY_TARVERSION}

#rm -Rf ./tar-version-src/${MY_TARVERSION}

exit 0; 

