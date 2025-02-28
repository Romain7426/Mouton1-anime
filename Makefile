
default: Makefile build build_ci build_hi build_i build_o build/anime.a build/anime.exe run 




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
	tcc -o build/anime.exe build/main.o build/anime.a     2>&1


build/anime.a: build/anime_generation_module.o build/anime_global.o build/anime_lexer_module.o build/anime_module.o build/anime_syntax_module.o
	ar -r -c build/anime.a build/anime_generation_module.o build/anime_global.o build/anime_lexer_module.o build/anime_module.o build/anime_syntax_module.o 2>&1
	ranlib build/anime.a 2>&1















build/anime.h: src/anime.h 
	ln src/anime.h build/anime.h 

build/anime_generation_module.h: src/anime_generation_module.h 
	ln src/anime_generation_module.h build/anime_generation_module.h 

build/anime_global.h: src/anime_global.h 
	ln src/anime_global.h build/anime_global.h 

build/anime_lexer_module.h: src/anime_lexer_module.h 
	ln src/anime_lexer_module.h build/anime_lexer_module.h 

build/anime_module.h: src/anime_module.h 
	ln src/anime_module.h build/anime_module.h 

build/anime_syntax_module.h: src/anime_syntax_module.h 
	ln src/anime_syntax_module.h build/anime_syntax_module.h 

build/anime_type.h: src/anime_type.h 
	ln src/anime_type.h build/anime_type.h 

build/main.h: src/main.h 
	ln src/main.h build/main.h 




build_ci: build build/000_oldies.ci build/anime_generation_module_infix_to_postfix.ci build/anime_generation_module_syntax_type.ci build/anime_lexer_module_automata.ci build/anime_lexer_module_automata_type.ci build/anime_lexer_module_print.ci build/anime_lexer_module_token_type.ci build/anime_module_consistency.ci build/anime_module_dump_and_restore.ci build/anime_module_error.ci build/anime_module_lexeme.ci build/anime_module_print.ci build/anime_module_print_field.ci build/anime_module_string.ci build/anime_module_subr.ci build/anime_module_type.ci build/chaman.anime.ci build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/main_old.ci build/main_options.ci build/main_stdlog_buffering.ci build/main_subr.ci 

build/000_oldies.ci: src/000_oldies.ci 
	ln src/000_oldies.ci build/000_oldies.ci 

build/anime_generation_module_infix_to_postfix.ci: src/anime_generation_module_infix_to_postfix.ci 
	ln src/anime_generation_module_infix_to_postfix.ci build/anime_generation_module_infix_to_postfix.ci 

build/anime_generation_module_syntax_type.ci: src/anime_generation_module_syntax_type.ci 
	ln src/anime_generation_module_syntax_type.ci build/anime_generation_module_syntax_type.ci 

build/anime_lexer_module_automata.ci: src/anime_lexer_module_automata.ci 
	ln src/anime_lexer_module_automata.ci build/anime_lexer_module_automata.ci 

build/anime_lexer_module_automata_type.ci: src/anime_lexer_module_automata_type.ci 
	ln src/anime_lexer_module_automata_type.ci build/anime_lexer_module_automata_type.ci 

build/anime_lexer_module_print.ci: src/anime_lexer_module_print.ci 
	ln src/anime_lexer_module_print.ci build/anime_lexer_module_print.ci 

build/anime_lexer_module_token_type.ci: src/anime_lexer_module_token_type.ci 
	ln src/anime_lexer_module_token_type.ci build/anime_lexer_module_token_type.ci 

build/anime_module_consistency.ci: src/anime_module_consistency.ci 
	ln src/anime_module_consistency.ci build/anime_module_consistency.ci 

build/anime_module_dump_and_restore.ci: src/anime_module_dump_and_restore.ci 
	ln src/anime_module_dump_and_restore.ci build/anime_module_dump_and_restore.ci 

build/anime_module_error.ci: src/anime_module_error.ci 
	ln src/anime_module_error.ci build/anime_module_error.ci 

build/anime_module_lexeme.ci: src/anime_module_lexeme.ci 
	ln src/anime_module_lexeme.ci build/anime_module_lexeme.ci 

build/anime_module_print.ci: src/anime_module_print.ci 
	ln src/anime_module_print.ci build/anime_module_print.ci 

build/anime_module_print_field.ci: src/anime_module_print_field.ci 
	ln src/anime_module_print_field.ci build/anime_module_print_field.ci 

build/anime_module_string.ci: src/anime_module_string.ci 
	ln src/anime_module_string.ci build/anime_module_string.ci 

build/anime_module_subr.ci: src/anime_module_subr.ci 
	ln src/anime_module_subr.ci build/anime_module_subr.ci 

build/anime_module_type.ci: src/anime_module_type.ci 
	ln src/anime_module_type.ci build/anime_module_type.ci 

build/chaman.anime.ci: src/chaman.anime.ci 
	ln src/chaman.anime.ci build/chaman.anime.ci 

build/lib__00__oldies.ci: src/lib__00__oldies.ci 
	ln src/lib__00__oldies.ci build/lib__00__oldies.ci 

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

build/lib__08__cstring.ci: src/lib__08__cstring.ci 
	ln src/lib__08__cstring.ci build/lib__08__cstring.ci 

build/lib__09__write_string.ci: src/lib__09__write_string.ci 
	ln src/lib__09__write_string.ci build/lib__09__write_string.ci 

build/lib__10__local_alloca.ci: src/lib__10__local_alloca.ci 
	ln src/lib__10__local_alloca.ci build/lib__10__local_alloca.ci 

build/lib__11__buffer_to_fd.ci: src/lib__11__buffer_to_fd.ci 
	ln src/lib__11__buffer_to_fd.ci build/lib__11__buffer_to_fd.ci 

build/main_old.ci: src/main_old.ci 
	ln src/main_old.ci build/main_old.ci 

build/main_options.ci: src/main_options.ci 
	ln src/main_options.ci build/main_options.ci 

build/main_stdlog_buffering.ci: src/main_stdlog_buffering.ci 
	ln src/main_stdlog_buffering.ci build/main_stdlog_buffering.ci 

build/main_subr.ci: src/main_subr.ci 
	ln src/main_subr.ci build/main_subr.ci 




build_hi: build build/anime_lexer_module_automata.hi build/anime_lexer_module_token_type.hi build/anime_module_type.hi 

build/anime_lexer_module_automata.hi: src/anime_lexer_module_automata.hi 
	ln src/anime_lexer_module_automata.hi build/anime_lexer_module_automata.hi 

build/anime_lexer_module_token_type.hi: src/anime_lexer_module_token_type.hi 
	ln src/anime_lexer_module_token_type.hi build/anime_lexer_module_token_type.hi 

build/anime_module_type.hi: src/anime_module_type.hi 
	ln src/anime_module_type.hi build/anime_module_type.hi 




build/anime_generation_module.c: src/anime_generation_module.c 
	ln src/anime_generation_module.c build/anime_generation_module.c 

build/anime_global.c: src/anime_global.c 
	ln src/anime_global.c build/anime_global.c 

build/anime_lexer_module.c: src/anime_lexer_module.c 
	ln src/anime_lexer_module.c build/anime_lexer_module.c 

build/anime_module.c: src/anime_module.c 
	ln src/anime_module.c build/anime_module.c 

build/anime_syntax_module.c: src/anime_syntax_module.c 
	ln src/anime_syntax_module.c build/anime_syntax_module.c 

build/main.c: src/main.c 
	ln src/main.c build/main.c 









build_i: build build/anime_generation_module.i build/anime_global.i build/anime_lexer_module.i build/anime_module.i build/anime_syntax_module.i build/main.i 

build/anime_generation_module.i: build/anime_generation_module.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_generation_module.h build/anime_lexer_module.h build/anime_generation_module_infix_to_postfix.ci 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -E build/anime_generation_module.c -o build/anime_generation_module.i  2>&1

build/anime_global.i: build/anime_global.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/lib__07__buffered_outstream.ci build/lib__11__buffer_to_fd.ci 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -E build/anime_global.c -o build/anime_global.i  2>&1

build/anime_lexer_module.i: build/anime_lexer_module.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_lexer_module.h build/anime_lexer_module_automata.ci build/anime_lexer_module_print.ci build/anime_lexer_module_token_type.ci build/anime_lexer_module_automata_type.ci 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -E build/anime_lexer_module.c -o build/anime_lexer_module.i  2>&1

build/anime_module.i: build/anime_module.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/anime.h build/anime_module.h build/anime_type.h build/anime_lexer_module.h build/anime_syntax_module.h build/anime_module_type.hi build/anime_module_type.ci build/anime_module_string.ci build/anime_module_subr.ci build/anime_module_print.ci build/anime_module_print_field.ci build/anime_module_consistency.ci build/anime_module_dump_and_restore.ci build/anime_module_lexeme.ci build/anime_generation_module.h build/chaman.anime.ci build/anime_module_error.ci 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -E build/anime_module.c -o build/anime_module.i  2>&1

build/anime_syntax_module.i: build/anime_syntax_module.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_syntax_module.h build/anime_lexer_module_token_type.hi 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -E build/anime_syntax_module.c -o build/anime_syntax_module.i  2>&1

build/main.i: build/main.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/anime.h build/main.h build/main_stdlog_buffering.ci build/main_subr.ci build/main_options.ci 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -E build/main.c -o build/main.i  2>&1






build_o: build build/anime_generation_module.o build/anime_global.o build/anime_lexer_module.o build/anime_module.o build/anime_syntax_module.o build/main.o 

build/anime_generation_module.o: build/anime_generation_module.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_generation_module.h build/anime_lexer_module.h build/anime_generation_module_infix_to_postfix.ci 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -c build/anime_generation_module.c -o build/anime_generation_module.o  2>&1

build/anime_global.o: build/anime_global.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/lib__07__buffered_outstream.ci build/lib__11__buffer_to_fd.ci 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -c build/anime_global.c -o build/anime_global.o  2>&1

build/anime_lexer_module.o: build/anime_lexer_module.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_lexer_module.h build/anime_lexer_module_automata.ci build/anime_lexer_module_print.ci build/anime_lexer_module_token_type.ci build/anime_lexer_module_automata_type.ci 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -c build/anime_lexer_module.c -o build/anime_lexer_module.o  2>&1

build/anime_module.o: build/anime_module.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/anime.h build/anime_module.h build/anime_type.h build/anime_lexer_module.h build/anime_syntax_module.h build/anime_module_type.hi build/anime_module_type.ci build/anime_module_string.ci build/anime_module_subr.ci build/anime_module_print.ci build/anime_module_print_field.ci build/anime_module_consistency.ci build/anime_module_dump_and_restore.ci build/anime_module_lexeme.ci build/anime_generation_module.h build/chaman.anime.ci build/anime_module_error.ci 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -c build/anime_module.c -o build/anime_module.o  2>&1

build/anime_syntax_module.o: build/anime_syntax_module.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/anime.h build/anime_type.h build/anime_syntax_module.h build/anime_lexer_module_token_type.hi 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -c build/anime_syntax_module.c -o build/anime_syntax_module.o  2>&1

build/main.o: build/main.c build/lib__00__oldies.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/lib__07__buffered_outstream.ci build/lib__08__cstring.ci build/lib__09__write_string.ci build/lib__10__local_alloca.ci build/lib__11__buffer_to_fd.ci build/anime_global.h build/anime.h build/main.h build/main_stdlog_buffering.ci build/main_subr.ci build/main_options.ci 
	tcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas        -g -bt100   -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral -Wno-unused-command-line-argument    -c build/main.c -o build/main.o  2>&1















