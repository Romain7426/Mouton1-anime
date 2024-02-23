
default: Makefile build build_ci build_i build_o build/anime.a build/anime.exe run 




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
	rm -Rf destroot run rundir *~ .*~ src/*~ src/*.output COPYING_at_start_of_c_files   2>&1


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
	cp -fp build/*.exe destroot/bin/anime
	mkdir -p destroot/lib
	cp -fp build/anime.a destroot/lib/anime.a
	mkdir -p destroot/include
	cp -fp src/anime.h destroot/include/








run: build/anime.exe
	rm -f run
	ln -s build/anime.exe run


build/anime.exe: build/anime.a build/main.o 
	/usr/bin/cc -o build/anime.exe build/main.o build/anime.a     2>&1


build/anime.a: build/anime.o build/anime_data_generation_001_from_tokens.o build/anime_data_generation_002_from_trees.o build/anime_data_generation_003_from_syntax_filtering.o build/anime_global.o build/anime_syntax_filtering_engine.o build/anime_token.o build/anime_token_automata.o build/anime_token_input_buffering.o build/anime_token_parser.o build/anime_token_type.o build/anime_tree.o build/anime_tree_parser.o
	ar -r -c build/anime.a build/anime.o build/anime_data_generation_001_from_tokens.o build/anime_data_generation_002_from_trees.o build/anime_data_generation_003_from_syntax_filtering.o build/anime_global.o build/anime_syntax_filtering_engine.o build/anime_token.o build/anime_token_automata.o build/anime_token_input_buffering.o build/anime_token_parser.o build/anime_token_type.o build/anime_tree.o build/anime_tree_parser.o 2>&1
	ranlib build/anime.a 2>&1















build/anime.h: src/anime.h 
	ln src/anime.h build/anime.h 

build/anime_data_generation_001_from_tokens.h: src/anime_data_generation_001_from_tokens.h 
	ln src/anime_data_generation_001_from_tokens.h build/anime_data_generation_001_from_tokens.h 

build/anime_data_generation_002_from_trees.h: src/anime_data_generation_002_from_trees.h 
	ln src/anime_data_generation_002_from_trees.h build/anime_data_generation_002_from_trees.h 

build/anime_data_generation_003_from_syntax_filtering.h: src/anime_data_generation_003_from_syntax_filtering.h 
	ln src/anime_data_generation_003_from_syntax_filtering.h build/anime_data_generation_003_from_syntax_filtering.h 

build/anime_global.h: src/anime_global.h 
	ln src/anime_global.h build/anime_global.h 

build/anime_syntax_filtering_engine.h: src/anime_syntax_filtering_engine.h 
	ln src/anime_syntax_filtering_engine.h build/anime_syntax_filtering_engine.h 

build/anime_token.h: src/anime_token.h 
	ln src/anime_token.h build/anime_token.h 

build/anime_token_automata.h: src/anime_token_automata.h 
	ln src/anime_token_automata.h build/anime_token_automata.h 

build/anime_token_input_buffering.h: src/anime_token_input_buffering.h 
	ln src/anime_token_input_buffering.h build/anime_token_input_buffering.h 

build/anime_token_parser.h: src/anime_token_parser.h 
	ln src/anime_token_parser.h build/anime_token_parser.h 

build/anime_token_type.h: src/anime_token_type.h 
	ln src/anime_token_type.h build/anime_token_type.h 

build/anime_tree.h: src/anime_tree.h 
	ln src/anime_tree.h build/anime_tree.h 

build/anime_tree_parser.h: src/anime_tree_parser.h 
	ln src/anime_tree_parser.h build/anime_tree_parser.h 

build/anime_type.h: src/anime_type.h 
	ln src/anime_type.h build/anime_type.h 

build/main.h: src/main.h 
	ln src/main.h build/main.h 




build_ci: build build/anime_consistency.ci build/anime_error.ci build/anime_print.ci build/anime_print_field.ci build/anime_string.ci build/anime_subr.ci build/anime_token_env.ci build/chaman.anime.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/main_old.ci build/main_options.ci build/main_stdlog_buffering.ci build/main_subr.ci 

build/anime_consistency.ci: src/anime_consistency.ci 
	ln src/anime_consistency.ci build/anime_consistency.ci 

build/anime_error.ci: src/anime_error.ci 
	ln src/anime_error.ci build/anime_error.ci 

build/anime_print.ci: src/anime_print.ci 
	ln src/anime_print.ci build/anime_print.ci 

build/anime_print_field.ci: src/anime_print_field.ci 
	ln src/anime_print_field.ci build/anime_print_field.ci 

build/anime_string.ci: src/anime_string.ci 
	ln src/anime_string.ci build/anime_string.ci 

build/anime_subr.ci: src/anime_subr.ci 
	ln src/anime_subr.ci build/anime_subr.ci 

build/anime_token_env.ci: src/anime_token_env.ci 
	ln src/anime_token_env.ci build/anime_token_env.ci 

build/chaman.anime.ci: src/chaman.anime.ci 
	ln src/chaman.anime.ci build/chaman.anime.ci 

build/lib__01__pre_header.ci: src/lib__01__pre_header.ci 
	ln src/lib__01__pre_header.ci build/lib__01__pre_header.ci 

build/lib__02__header.ci: src/lib__02__header.ci 
	ln src/lib__02__header.ci build/lib__02__header.ci 

build/lib__03.ci: src/lib__03.ci 
	ln src/lib__03.ci build/lib__03.ci 

build/lib__04__string_stack.ci: src/lib__04__string_stack.ci 
	ln src/lib__04__string_stack.ci build/lib__04__string_stack.ci 

build/lib__05__error_state.ci: src/lib__05__error_state.ci 
	ln src/lib__05__error_state.ci build/lib__05__error_state.ci 

build/lib__06__exception.ci: src/lib__06__exception.ci 
	ln src/lib__06__exception.ci build/lib__06__exception.ci 

build/lib__07__buffered_outstream.ci: src/lib__07__buffered_outstream.ci 
	ln src/lib__07__buffered_outstream.ci build/lib__07__buffered_outstream.ci 

build/main_old.ci: src/main_old.ci 
	ln src/main_old.ci build/main_old.ci 

build/main_options.ci: src/main_options.ci 
	ln src/main_options.ci build/main_options.ci 

build/main_stdlog_buffering.ci: src/main_stdlog_buffering.ci 
	ln src/main_stdlog_buffering.ci build/main_stdlog_buffering.ci 

build/main_subr.ci: src/main_subr.ci 
	ln src/main_subr.ci build/main_subr.ci 




build/anime.c: src/anime.c 
	ln src/anime.c build/anime.c 

build/anime_data_generation_001_from_tokens.c: src/anime_data_generation_001_from_tokens.c 
	ln src/anime_data_generation_001_from_tokens.c build/anime_data_generation_001_from_tokens.c 

build/anime_data_generation_002_from_trees.c: src/anime_data_generation_002_from_trees.c 
	ln src/anime_data_generation_002_from_trees.c build/anime_data_generation_002_from_trees.c 

build/anime_data_generation_003_from_syntax_filtering.c: src/anime_data_generation_003_from_syntax_filtering.c 
	ln src/anime_data_generation_003_from_syntax_filtering.c build/anime_data_generation_003_from_syntax_filtering.c 

build/anime_global.c: src/anime_global.c 
	ln src/anime_global.c build/anime_global.c 

build/anime_syntax_filtering_engine.c: src/anime_syntax_filtering_engine.c 
	ln src/anime_syntax_filtering_engine.c build/anime_syntax_filtering_engine.c 

build/anime_token.c: src/anime_token.c 
	ln src/anime_token.c build/anime_token.c 

build/anime_token_automata.c: src/anime_token_automata.c 
	ln src/anime_token_automata.c build/anime_token_automata.c 

build/anime_token_input_buffering.c: src/anime_token_input_buffering.c 
	ln src/anime_token_input_buffering.c build/anime_token_input_buffering.c 

build/anime_token_parser.c: src/anime_token_parser.c 
	ln src/anime_token_parser.c build/anime_token_parser.c 

build/anime_token_type.c: src/anime_token_type.c 
	ln src/anime_token_type.c build/anime_token_type.c 

build/anime_tree.c: src/anime_tree.c 
	ln src/anime_tree.c build/anime_tree.c 

build/anime_tree_parser.c: src/anime_tree_parser.c 
	ln src/anime_tree_parser.c build/anime_tree_parser.c 

build/main.c: src/main.c 
	ln src/main.c build/main.c 









build_i: build build/anime.i build/anime_data_generation_001_from_tokens.i build/anime_data_generation_002_from_trees.i build/anime_data_generation_003_from_syntax_filtering.i build/anime_global.i build/anime_syntax_filtering_engine.i build/anime_token.i build/anime_token_automata.i build/anime_token_input_buffering.i build/anime_token_parser.i build/anime_token_type.i build/anime_tree.i build/anime_tree_parser.i build/main.i 

build/anime.i: build/anime.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_token.h build/anime_token_input_buffering.h build/anime_token_parser.h build/anime_data_generation_003_from_syntax_filtering.h build/anime_string.ci build/anime_subr.ci build/anime_error.ci build/anime_print.ci build/anime_print_field.ci build/anime_consistency.ci build/chaman.anime.ci 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime.c -o build/anime.i  2>&1

build/anime_data_generation_001_from_tokens.i: build/anime_data_generation_001_from_tokens.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_token.h build/anime_token_type.h build/anime_token_input_buffering.h build/anime_token_parser.h build/anime_data_generation_001_from_tokens.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_data_generation_001_from_tokens.c -o build/anime_data_generation_001_from_tokens.i  2>&1

build/anime_data_generation_002_from_trees.i: build/anime_data_generation_002_from_trees.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_token.h build/anime_token_type.h build/anime_token_input_buffering.h build/anime_token_parser.h build/anime_tree.h build/anime_data_generation_002_from_trees.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_data_generation_002_from_trees.c -o build/anime_data_generation_002_from_trees.i  2>&1

build/anime_data_generation_003_from_syntax_filtering.i: build/anime_data_generation_003_from_syntax_filtering.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_token.h build/anime_token_type.h build/anime_syntax_filtering_engine.h build/anime_data_generation_003_from_syntax_filtering.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_data_generation_003_from_syntax_filtering.c -o build/anime_data_generation_003_from_syntax_filtering.i  2>&1

build/anime_global.i: build/anime_global.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/lib__07__buffered_outstream.ci 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_global.c -o build/anime_global.i  2>&1

build/anime_syntax_filtering_engine.i: build/anime_syntax_filtering_engine.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_token_type.h build/anime_token.h build/anime_syntax_filtering_engine.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_syntax_filtering_engine.c -o build/anime_syntax_filtering_engine.i  2>&1

build/anime_token.i: build/anime_token.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime_token.h build/anime_token_type.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_token.c -o build/anime_token.i  2>&1

build/anime_token_automata.i: build/anime_token_automata.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime_token_type.h build/anime_token.h build/anime_token_automata.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_token_automata.c -o build/anime_token_automata.i  2>&1

build/anime_token_input_buffering.i: build/anime_token_input_buffering.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime_token_input_buffering.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_token_input_buffering.c -o build/anime_token_input_buffering.i  2>&1

build/anime_token_parser.i: build/anime_token_parser.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_token_type.h build/anime_token.h build/anime_token_automata.h build/anime_token_input_buffering.h build/anime_token_parser.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_token_parser.c -o build/anime_token_parser.i  2>&1

build/anime_token_type.i: build/anime_token_type.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime_token_type.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_token_type.c -o build/anime_token_type.i  2>&1

build/anime_tree.i: build/anime_tree.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_tree.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_tree.c -o build/anime_tree.i  2>&1

build/anime_tree_parser.i: build/anime_tree_parser.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_token_type.h build/anime_token.h build/anime_tree.h build/anime_tree_parser.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/anime_tree_parser.c -o build/anime_tree_parser.i  2>&1

build/main.i: build/main.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/main.h build/main_stdlog_buffering.ci build/main_subr.ci build/main_options.ci 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/main.c -o build/main.i  2>&1






build_o: build build/anime.o build/anime_data_generation_001_from_tokens.o build/anime_data_generation_002_from_trees.o build/anime_data_generation_003_from_syntax_filtering.o build/anime_global.o build/anime_syntax_filtering_engine.o build/anime_token.o build/anime_token_automata.o build/anime_token_input_buffering.o build/anime_token_parser.o build/anime_token_type.o build/anime_tree.o build/anime_tree_parser.o build/main.o 

build/anime.o: build/anime.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_token.h build/anime_token_input_buffering.h build/anime_token_parser.h build/anime_data_generation_003_from_syntax_filtering.h build/anime_string.ci build/anime_subr.ci build/anime_error.ci build/anime_print.ci build/anime_print_field.ci build/anime_consistency.ci build/chaman.anime.ci 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime.c -o build/anime.o  2>&1

build/anime_data_generation_001_from_tokens.o: build/anime_data_generation_001_from_tokens.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_token.h build/anime_token_type.h build/anime_token_input_buffering.h build/anime_token_parser.h build/anime_data_generation_001_from_tokens.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_data_generation_001_from_tokens.c -o build/anime_data_generation_001_from_tokens.o  2>&1

build/anime_data_generation_002_from_trees.o: build/anime_data_generation_002_from_trees.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_token.h build/anime_token_type.h build/anime_token_input_buffering.h build/anime_token_parser.h build/anime_tree.h build/anime_data_generation_002_from_trees.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_data_generation_002_from_trees.c -o build/anime_data_generation_002_from_trees.o  2>&1

build/anime_data_generation_003_from_syntax_filtering.o: build/anime_data_generation_003_from_syntax_filtering.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_token.h build/anime_token_type.h build/anime_syntax_filtering_engine.h build/anime_data_generation_003_from_syntax_filtering.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_data_generation_003_from_syntax_filtering.c -o build/anime_data_generation_003_from_syntax_filtering.o  2>&1

build/anime_global.o: build/anime_global.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/lib__07__buffered_outstream.ci 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_global.c -o build/anime_global.o  2>&1

build/anime_syntax_filtering_engine.o: build/anime_syntax_filtering_engine.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_token_type.h build/anime_token.h build/anime_syntax_filtering_engine.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_syntax_filtering_engine.c -o build/anime_syntax_filtering_engine.o  2>&1

build/anime_token.o: build/anime_token.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime_token.h build/anime_token_type.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_token.c -o build/anime_token.o  2>&1

build/anime_token_automata.o: build/anime_token_automata.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime_token_type.h build/anime_token.h build/anime_token_automata.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_token_automata.c -o build/anime_token_automata.o  2>&1

build/anime_token_input_buffering.o: build/anime_token_input_buffering.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime_token_input_buffering.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_token_input_buffering.c -o build/anime_token_input_buffering.o  2>&1

build/anime_token_parser.o: build/anime_token_parser.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_token_type.h build/anime_token.h build/anime_token_automata.h build/anime_token_input_buffering.h build/anime_token_parser.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_token_parser.c -o build/anime_token_parser.o  2>&1

build/anime_token_type.o: build/anime_token_type.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime_token_type.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_token_type.c -o build/anime_token_type.o  2>&1

build/anime_tree.o: build/anime_tree.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_tree.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_tree.c -o build/anime_tree.o  2>&1

build/anime_tree_parser.o: build/anime_tree_parser.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/anime_token_type.h build/anime_token.h build/anime_tree.h build/anime_tree_parser.h 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/anime_tree_parser.c -o build/anime_tree_parser.o  2>&1

build/main.o: build/main.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/anime_global.h build/anime.h build/main.h build/main_stdlog_buffering.ci build/main_subr.ci build/main_options.ci 
	/usr/bin/cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -D ENDIANNESS=little -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/main.c -o build/main.o  2>&1















