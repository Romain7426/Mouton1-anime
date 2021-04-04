#!/bin/sh
#!/bin/sh -u -e 
# http://www.davidpashley.com/articles/writing-robust-shell-scripts/#id2382181
# mkstructures #pour générer le fichier des structures

set -u 
set -e
#set -x




echo "Generating tools"

rm -Rf tools/build
mkdir -p tools/build
mkdir -p tools/bin

CC_OPTS=" -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0 -Wall -fmessage-length=0 -fno-exceptions -Werror -W  -Wparentheses -fverbose-asm -gstabs+3 -fno-omit-frame-pointer -Wmissing-prototypes -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wmissing-prototypes -Wpacked -Wcast-qual -Wcast-align -Wsystem-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wmissing-declarations -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function "

CC_OPTS=" -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG "

#echo $CC_OPTS

#exit


test -e tools/src/filename_without_path.c
cc $CC_OPTS tools/src/filename_without_path.c -o tools/build/filename_without_path.exe
rm -f tools/bin/filename_without_path 
ln -s ../build/filename_without_path.exe tools/bin/filename_without_path 

test -e tools/src/filename_remove_extension.c
cc $CC_OPTS tools/src/filename_remove_extension.c -o tools/build/filename_remove_extension.exe
rm -f tools/bin/filename_remove_extension 
ln -s ../build/filename_remove_extension.exe tools/bin/filename_remove_extension


for file_path_i in `ls tools/src/*.c`; do
  file_i=`./tools/bin/filename_without_path $file_path_i`
  file_i_wo_ext=`./tools/bin/filename_remove_extension $file_i`
#  echo $file_path_i
#  echo $file_i
#  echo $file_i_wo_ext
  cc $CC_OPTS tools/src/$file_i_wo_ext.c -o tools/build/$file_i_wo_ext.exe
  rm -f tools/bin/$file_i_wo_ext 
  ln -s ../build/$file_i_wo_ext.exe tools/bin/$file_i_wo_ext 
done;

#exit

