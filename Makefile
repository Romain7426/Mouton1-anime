
default: Makefile build build/anime.a 




SHELL:= /bin/sh
.SHELLFLAGS: -u -e  
#MAKEFLAGS:= s --warn-undefined-variables 
#MAKEFLAGS:= s 
.SUFFIXES: 
#.SILENT:
.NOTPARALLEL:
.EXPORT_ALL_VARIABLES:
.SECONDARY:
.PRECIOUS:
.ONESHELL:




clean:
	rm -Rf build 2>&1

clean-all: clean
	rm -Rf destroot rundir *~ .*~ src/*~ src/*.output COPYING_at_start_of_c_files src/anime.parser.tab.c src/anime.parser.code.c src/anime.lexer.c 2>&1


Makefile: Makefile-gen.mkf
	@echo "--- \"Makefile-gen.mkf\" changed. Please type './configure' (or 'romake -f Makefile-gen.mkf') to update this Makefile ---"
	@false

build:
	mkdir -p build 2>&1 


install: destroot_do

destroot_do:
	rm -Rf destroot
	mkdir -p destroot
	mkdir -p destroot/lib
	cp -fp build/*.a destroot/lib/
	mkdir -p destroot/include
	cp -fp src/anime.h destroot/include/








run: build/anime.exe
	rm -f run
	ln -s build/anime.exe run


build/anime.exe: build/anime.a
	cc -o build/anime.exe build/anime.a -lm  2>&1


build/anime.a: build/anime.o build/anime.global.o build/anime.lexer.o build/anime.parser.tab.o build/anime.parser.code.o build/anime.lexer.o
	ar -r -c build/anime.a build/anime.o build/anime.global.o build/anime.lexer.o build/anime.parser.tab.o build/anime.parser.code.o build/anime.lexer.o 2>&1
	ranlib build/anime.a 2>&1









#src/anime.parser.c: src/anime.parser.y 
src/anime.parser.tab.h src/anime.parser.tab.c src/anime.parser.code.c: src/anime.parser.y 
#	bison --report=all,state,look-ahead,itemset --token-table --debug -d  src/anime.parser.y -o src/anime.parser.c 2>&1
#	yacc -d -t -p yyanime -r -v  -o src/anime.parser.c src/anime.parser.y 2>&1
	yacc -d -t -p yyanime -r -v  -b src/anime.parser src/anime.parser.y 2>&1
#	mv -f parser.c src/anime.parser.c 2>&1 || true 
#	mv -f anime.parser.c src/anime.parser.c 2>&1 || true
#	test -e src/anime.parser.c 2>&1






src/anime.lexer.c: src/anime.lexer.l 
	flex -Pyyanime -Cfa -p  -o src/anime.lexer.c src/anime.lexer.l 2>&1
	test -e src/anime.lexer.c 2>&1






build/anime.o: src/anime.c src/anime.global.h src/anime.h src/anime.lexer.h src/anime.parser.tab.h
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wcast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime.c -o build/anime.o  2>&1

build/anime.global.o: src/anime.global.c src/anime.global.h src/anime.h src/anime.lexer.h src/anime.parser.tab.h
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wcast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime.global.c -o build/anime.global.o  2>&1

build/anime.lexer.o: src/anime.lexer.c src/anime.global.h src/anime.h src/anime.lexer.h src/anime.parser.tab.h
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wcast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime.lexer.c -o build/anime.lexer.o  2>&1

build/anime.parser.code.o: src/anime.parser.code.c src/anime.global.h src/anime.h src/anime.lexer.h src/anime.parser.tab.h
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wcast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime.parser.code.c -o build/anime.parser.code.o  2>&1

build/anime.parser.tab.o: src/anime.parser.tab.c src/anime.global.h src/anime.h src/anime.lexer.h src/anime.parser.tab.h
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wcast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime.parser.tab.c -o build/anime.parser.tab.o  2>&1















