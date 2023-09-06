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
MY_TARVERSION=${MY_NAME}_-_${MY_DATE}

echo ${MY_DATE}
echo ${MY_NAME}
echo ${MY_TARVERSION}

mkdir -p ./tar-version-src
mkdir -p ./tar-version-src/${MY_TARVERSION}
mkdir -p ./tar-version-src/${MY_TARVERSION}/src



