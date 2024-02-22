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

# La première partie de la ligne est pour éviter que chmod ne reporte une erreur si tools/src n’existe pas. 
mkdir -p tools/src && chmod +w tools/src/ && rm -Rf tools

mkdir -p tools
mkdir -p tools/src
mkdir -p tools/build
mkdir -p tools/bin

cp -fp ../project-tools/src/*.c  tools/src/
cp -fp ../project-tools/src/*.ci tools/src/

chmod -wx tools/src/*
chmod -w tools/src/

