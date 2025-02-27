#! /bin/sh
 
# HINT: If, for some reasons, './configure.sh' is refused to be run, just type 'sh ./configure.sh'. 

# Y a-t-il un fichier CC? 
#(cat CC > /dev/null 2>&1 ) || (echo "No './CC' file (it holds path to C compiler)" ; exit 1 ; ) || exit 1;
(cat CC > /dev/null 2>&1 ) || (echo "cc" >> ./CC ) ; 

CC="$(cat CC | head -1)"
echo "CC="\"${CC}\" 


# Y a-t-il un fichier GMAKE?
(cat GMAKE > /dev/null 2>&1 ) || (echo "gmake" >> ./GMAKE ) ; 

GMAKE="$(cat GMAKE | head -1)"
echo "GMAKE="\"${GMAKE}\" 


(${SHELL} ./tools-compile.sh ) || exit 1; 

echo "Generating Makefile"
CC="${CC}" ${GMAKE} -r -R -S -j 1 --warn-undefined-variables -f ./Makefile-gen.mkf 


exit $?;



 
if which gmake > /dev/null 2>&1 ; then 
 CC="${CC}" gmake -r -R -S -j 1 --warn-undefined-variables -f ./Makefile-gen.mkf 
 exit $? 
fi; 

if which make > /dev/null 2>&1 ; then 
  CC="${CC}" make -r -R -S -j 1 --warn-undefined-variables -f ./Makefile-gen.mkf 
  exit $? 
fi; 


echo "I could not find GNU Make" 






exit 1; 


which gmake && (gmake -r -R -S -j 1 --warn-undefined-variables -f ./Makefile-gen.mkf ;  exit $? ) 

which make && (make -r -R -S -j 1 --warn-undefined-variables -f ./Makefile-gen.mkf ;  exit $? ) 

echo "I cannot find GNU Make" 



