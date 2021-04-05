
default: Makefile build build/anime.a build/anime.exe run 




SHELL:= /bin/sh
.SHELLFLAGS: -u -e  
#MAKEFLAGS:=  --warn-undefined-variables 
#MAKEFLAGS:=  
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
	rm -Rf destroot run rundir *~ .*~ src/*~ src/*.output src/chaman.anime.ci COPYING_at_start_of_c_files   2>&1


Makefile: Makefile-gen.mkf
	@echo "--- \"Makefile-gen.mkf\" changed. Please type './configure' (or 'romake -f Makefile-gen.mkf') to update this Makefile ---"
	@false

build:
	mkdir -p build 2>&1 


install: destroot_do

destroot_do:
	rm -Rf destroot
	mkdir -p destroot
	mkdir -p destroot/bin
	cp -fp build/*.exe destroot/bin/
	mkdir -p destroot/lib
	cp -fp build/*.a destroot/lib/
	mkdir -p destroot/include
	cp -fp src/anime.h destroot/include/








run: build/anime.exe
	rm -f run
	ln -s build/anime.exe run


build/anime.exe: build/anime.a build/main.o 
	cc -o build/anime.exe build/main.o build/anime.a  2>&1


build/anime.a: build/anime.o build/anime_data_generation_001_from_tokens.o build/anime_data_generation_002_from_trees.o build/anime_data_generation_003_from_syntax_filtering.o build/anime_global.o build/anime_syntax_filtering_engine.o build/anime_token.o build/anime_token_automata.o build/anime_token_input_buffering.o build/anime_token_parser.o build/anime_token_type.o build/anime_tree.o build/anime_tree_parser.o
	ar -r -c build/anime.a build/anime.o build/anime_data_generation_001_from_tokens.o build/anime_data_generation_002_from_trees.o build/anime_data_generation_003_from_syntax_filtering.o build/anime_global.o build/anime_syntax_filtering_engine.o build/anime_token.o build/anime_token_automata.o build/anime_token_input_buffering.o build/anime_token_parser.o build/anime_token_type.o build/anime_tree.o build/anime_tree_parser.o 2>&1
	ranlib build/anime.a 2>&1






src/chaman.anime.ci: src/chaman.anime
	cat src/chaman.anime | ./tools/bin/text2cstring > src/chaman.anime.ci 





















build/anime.o: src/anime.c src/anime_global.h src/anime.h src/anime_token.h src/anime_token_input_buffering.h src/anime_token_parser.h src/anime_data_generation_003_from_syntax_filtering.h src/chaman.anime.ci 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime.c -o build/anime.o  2>&1

build/anime_data_generation_001_from_tokens.o: src/anime_data_generation_001_from_tokens.c src/anime_global.h src/anime.h src/anime_token.h src/anime_token_type.h src/anime_token_input_buffering.h src/anime_token_parser.h src/anime_data_generation_001_from_tokens.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_data_generation_001_from_tokens.c -o build/anime_data_generation_001_from_tokens.o  2>&1

build/anime_data_generation_002_from_trees.o: src/anime_data_generation_002_from_trees.c src/anime_global.h src/anime.h src/anime_token.h src/anime_token_type.h src/anime_token_input_buffering.h src/anime_token_parser.h src/anime_tree.h src/anime_data_generation_002_from_trees.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_data_generation_002_from_trees.c -o build/anime_data_generation_002_from_trees.o  2>&1

build/anime_data_generation_003_from_syntax_filtering.o: src/anime_data_generation_003_from_syntax_filtering.c src/anime_global.h src/anime.h src/anime_token.h src/anime_token_type.h src/anime_syntax_filtering_engine.h src/anime_data_generation_003_from_syntax_filtering.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_data_generation_003_from_syntax_filtering.c -o build/anime_data_generation_003_from_syntax_filtering.o  2>&1

build/anime_global.o: src/anime_global.c src/anime_global.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_global.c -o build/anime_global.o  2>&1

build/anime_syntax_filtering_engine.o: src/anime_syntax_filtering_engine.c src/anime_global.h src/anime.h src/anime_token_type.h src/anime_token.h src/anime_syntax_filtering_engine.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_syntax_filtering_engine.c -o build/anime_syntax_filtering_engine.o  2>&1

build/anime_token.o: src/anime_token.c src/anime_global.h src/anime_token.h src/anime_token_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_token.c -o build/anime_token.o  2>&1

build/anime_token_automata.o: src/anime_token_automata.c src/anime_global.h src/anime_token_type.h src/anime_token.h src/anime_token_automata.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_token_automata.c -o build/anime_token_automata.o  2>&1

build/anime_token_input_buffering.o: src/anime_token_input_buffering.c src/anime_global.h src/anime_token_input_buffering.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_token_input_buffering.c -o build/anime_token_input_buffering.o  2>&1

build/anime_token_parser.o: src/anime_token_parser.c src/anime_global.h src/anime.h src/anime_token_type.h src/anime_token.h src/anime_token_automata.h src/anime_token_input_buffering.h src/anime_token_parser.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_token_parser.c -o build/anime_token_parser.o  2>&1

build/anime_token_type.o: src/anime_token_type.c src/anime_global.h src/anime_token_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_token_type.c -o build/anime_token_type.o  2>&1

build/anime_tree.o: src/anime_tree.c src/anime_global.h src/anime.h src/anime_tree.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_tree.c -o build/anime_tree.o  2>&1

build/anime_tree_parser.o: src/anime_tree_parser.c src/anime_global.h src/anime.h src/anime_token_type.h src/anime_token.h src/anime_tree.h src/anime_tree_parser.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/anime_tree_parser.c -o build/anime_tree_parser.o  2>&1

build/main.o: src/main.c src/anime_global.h src/anime.h src/main.h src/main_options.ci 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG  -O0 -Wall -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -Wnewline-eof -Wfatal-errors -Werror-implicit-function-declaration -fno-exceptions -fstack-check -Werror -W  -Wparentheses -fverbose-asm -fno-omit-frame-pointer -ffreestanding -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -gfull  -feliminate-unused-debug-types  -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type  -Wstrict-prototypes -Wpacked -Wcast-qual -Wno-cast-align -Wno-system-headers -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unsequenced -I /usr/X11R6/include  -I ./libs/SDL-1.2.15/destroot/include -I ./src/SDL_image -I ./src/SDL_mixer   -c src/main.c -o build/main.o  2>&1















