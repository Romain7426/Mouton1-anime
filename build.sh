#!/bin/sh

rm -Rf build 2>&1

mkdir -p build 2>&1











pcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D SRCFILE_UTF8    -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D DEFAULTSTACKSIZE=130193347833888 -D COMPILER_PCC -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden        -fpic -Wno-unreachable-code -Wno-shadow     -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions     -c src/anime_generation_module.c -o build/anime_generation_module.o  2>&1
pcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D SRCFILE_UTF8    -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D DEFAULTSTACKSIZE=130193347833888 -D COMPILER_PCC -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden        -fpic -Wno-unreachable-code -Wno-shadow     -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions     -c src/anime_lexer_module.c -o build/anime_lexer_module.o  2>&1
pcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D SRCFILE_UTF8    -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D DEFAULTSTACKSIZE=130193347833888 -D COMPILER_PCC -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden        -fpic -Wno-unreachable-code -Wno-shadow     -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions     -c src/anime_module.c -o build/anime_module.o  2>&1
pcc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -D SRCFILE_UTF8    -D ENDIANNESS=little -D PIPEBUFFERSIZE=65534 -D FLOATBYTESIZE=4 -D DEFAULTSTACKSIZE=130193347833888 -D COMPILER_PCC -D STDLIB_PROVIDES_ARC4RANDOM  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types -fjump-tables -fmerge-all-constants -fshort-enums -ftrapv -fvisibility=hidden        -fpic -Wno-unreachable-code -Wno-shadow     -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions     -c src/anime_syntax_module.c -o build/anime_syntax_module.o  2>&1
ar -r -c build/anime.a build/anime_generation_module.o build/anime_lexer_module.o build/anime_module.o build/anime_syntax_module.o 2>&1
ranlib build/anime.a 2>&1
pcc -o build/anime.exe build/anime.a     2>&1

rm -f run
ln -s build/anime.exe run
chmod +x run

