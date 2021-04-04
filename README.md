# Mouton1-anime
 
*Mouton1-anime* is a sub-project of [*Mouton1*](https://github.com/Romain7426/Mouton1-anime). 

*Mouton1-anime* is a DSL («data specific language»), a library, and an executable: 
 - It specifies a syntax to describe *anime* data. 
 - It provides a library that reads an *anime* data file, and fills a [*C*](https://en.wikipedia.org/wiki/C_(programming_language)) struct. 
 - It supplies an executable which checks the syntax of an *anime* data file, and prints descriptions of errors. 

In order to parser an *anime* data file, *Mouton1-anime* does not use [*Lex*](https://en.wikipedia.org/wiki/Lex_programming_tool) nor [*Yacc*](https://en.wikipedia.org/wiki/Yacc). It implements its own lexer and parser, which takes a little longer to implement, but is accurate, and prints understandable errors. 
 

## Compile 
 
To compile it, tools have to be compiled first: './tools-compile-gcc.sh'

Then: 'gmake -f Makefile-gen.mkf'
 
Then: 'make'
 
Finally: 'make install'
 
That should do. 

 
## DSL Example

physique {
 zone de choc := {
  longueur := 0.5;
  largeur  := 0.5;
  hauteur  := 50.;
 };
 Masse := 240.;
}

gameplay {
 points de vie := 9999;
 invincible    := vrai;
 hostile       := faux;
}

graphique {
 membre corps        { fils := ; image := "./villageois/corps6.png"  ; largeur := 20.; hauteur := 22.; angle max y :=    0.; }
 membre bras_gauche  { fils := ; image := "./villageois/bras12.png"  ; largeur :=  9.; hauteur := 26.; angle max y := -.30.; }
 membre bras_droit   { fils := ; image := "./villageois/bras12.png"  ; largeur :=  9.; hauteur := 26.; angle max y :=   30.; }
 membre tete         { fils := ; image := "./villageois/tetes11.png" ; largeur := 15.; hauteur := 15.; angle max y :=    0.; }
 membre jambe_gauche { fils := ; image := "./villageois/jambes10.png"; largeur :=  9.; hauteur := 20.; angle max y :=   45.; }
 membre jambe_droite { fils := ; image := "./villageois/jambes10.png"; largeur :=  9.; hauteur := 20.; angle max y := -.45.; }

 membres racines := 
	{qui := corps;        x := 0.; y :=    0.; z := 37.; angle y := 0.;},
	{qui := tete;         x := 0.; y :=    0.; z := 49.; angle y := 0.;},
	{qui := jambe_gauche; x := 0.; y :=    5.; z := 19.; angle y := 0.;},
	{qui := jambe_droite; x := 0.; y :=  -.5.; z := 19.; angle y := 0.;},
	{qui := bras_gauche;  x := 0.; y :=   15.; z := 37.; angle y := 0.;},
	{qui := bras_droit;   x := 0.; y := -.15.; z := 37.; angle y := 0.;};

}


## Lib Example

#include "anime.h"

const int stdlog_d = open("./stdlog.log", O_WRONLY); 
int_anime_error_t error_id; 
anime_t a_anime[1]; 
anime__make_r(a_anime, stdlog_d); 
error_id = anime__fill_from_file(a_anime, input_file_name, input_file_fd, stduser_d); 
if (error_id != ANIME__OK) { 
  if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_anime -> error_str); 
  break; 
}; 


## Executable Example 

\$ ./destroot/bin/anime.exe
./destroot/bin/anime.exe: Check if an anime description file is properly written.
Usage: ./destroot/bin/anime.exe [<options>] <infile> [<fields name>] 
  <infile> can be a filename or '-' for stdin (use './-' for a file named '-')
  If <fields name> are provided, print the value of the matching fields.
Options:
  -h,-?,--help,--usage                 	  Display this help
  --copyright,--license,--licence      	  Display the program license
  --copyright-cstr                     	  Display the program license as a C string
  --copyright-ccomment                 	  Display the program license as a C comment
  --copyright-shell_comment            	  Display the program license as a SHELL comment
  --copyright-slash_comment            	  Display the program license as a double-slash comment
  -v,--verbose                         	  Increase verbosity
  -q,--quiet,--mute                    	  Do not tell anything
  -V,--version                         	  Print program version
  --example,--exemple                  	  Print an example
  --url                                	  Print url
  --stduser <file>                     	  Redirect all the talk to the user to <file>. (Default is stderr.) (Use 'stdout', 'stderr', and 'stdnull' to redirect to stdout, stderr, and /dev/null.)
  --stdlog <file>                      	  Write stdlog to <file>. (By default, stdlog fd is 3; therefore the output of stdlog can be gotten using '3>&2' or '3>./stdlog.txt'.) (stdlog is intended for dev. But can be used by users.) (Use 'stdout', 'stderr', and 'stdnull' to redirect to stdout, stderr, and /dev/null.)

 
\$ ./destroot/bin/anime.exe chaman.anime 3>./chaman.log
<chaman.anime>: OK

\$ ./destroot/bin/anime.exe chaman.anime physique
physique.zone_de_choc.longueur =   0.500000 
physique.zone_de_choc.largeur  =   0.500000 
physique.zone_de_choc.hauteur  =  50.000000 
physique.masse = 240.000000 
<chaman.anime>: OK


 

