# Mouton1-anime
 
*Mouton1-anime* is a sub-project of [*Mouton1*](https://github.com/Romain7426/Mouton1). 

*Mouton1-anime* is a DSL («data specific language»), a library, and an executable: 
 - It specifies a language to describe *anime* data. 
 - It provides a library that reads an *anime* data file, and fills a [*C*](https://en.wikipedia.org/wiki/C_(programming_language)) struct. 
 - It supplies an executable which checks the syntax of an *anime* data file, and prints descriptions of errors. 


## Installation et compilation

La procédure: 

<pre>
$ echo "clang" > ./CC        # Ou votre compilateur préféré. 
$ sh ./configure.sh          # Génère d'abord les outils puis le Makefile. 
$ make 
$ make install 
</pre>
 
Personnalisation 
 - Choix du [compilateur](https://fr.wikipedia.org/wiki/Compilateur) — par défaut, le [compilateur](https://fr.wikipedia.org/wiki/Compilateur) utilisé est 'cc'; pour utiliser votre [compilateur](https://fr.wikipedia.org/wiki/Compilateur) préféré, il faut en indiquer le chemin dans le fichier ['./CC'](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/CC) (par exemple, «$ echo "/usr/local/bin/x86_64-unknown-openbsd7.0-gcc-11.2.0" > ./CC»). 
 - Choix du répertoire d'installation — par défaut, le répertoire d'installation est './destroot'; pour indiquer votre lieu préféré, il faut éditer le [Makefile](https://fr.wikipedia.org/wiki/Make#Makefile) généré, voire éditer le fichier ['./Makefile-gen.mkf'](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/Makefile-gen.mkf) (il est aussi possible de simplement créer un lien symbolique vers './destroot', ou de copier les fichiers depuis './destroot' vers le lieu d'installation voulu). 
 - Aucune autre configuration possible. (Toutefois, vous pouvez toujours modifier le fichier ['./Makefile-gen.mkf'](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/Makefile-gen.mkf) à votre convenance.) 
 
Architecture de la configuration 
 - La configuration n'est pas basée sur [GNU Autohell](https://en.wikipedia.org/wiki/Autohell). 
 - L'idée est de générer un [Makefile](https://fr.wikipedia.org/wiki/Make#Makefile) qui soit le plus standard possible, parfaitement prévisible et ennuyeux (exemple: [https://github.com/Romain7426/X_Macros_-_Enum/blob/main/Makefile](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/Makefile)), afin de pouvoir être lu par n'importe quelle version exotique de [Make](https://fr.wikipedia.org/wiki/Make). Un tel [Makefile](https://fr.wikipedia.org/wiki/Make#Makefile) est beaucoup plus lisible, plus simple à déboguer, plus compréhensible, et évite au programme [Make](https://fr.wikipedia.org/wiki/Make) de prendre des initiatives (en inférant on ne sait pas quelle règle ésotérique). (En sus, en théorie, un tel [Makefile](https://fr.wikipedia.org/wiki/Make#Makefile) serait distribuable — dans les faits, ceci est improbable dû aux spécificités de chaque [compilateur](https://fr.wikipedia.org/wiki/Compilateur), de chaque [système](https://fr.wikipedia.org/wiki/Syst%C3%A8me_d%27exploitation), etc., spécificités que il faut donc détecter en amont.) 
 - Pour générer un tel [Makefile](https://fr.wikipedia.org/wiki/Make#Makefile) ennuyeux, nous utilisons le fichier ['./Makefile-gen.mkf'](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/Makefile-gen.mkf) qui est un script écrit dans le langage [GNU Make](https://en.wikipedia.org/wiki/GNU_make) (le langage de [GNU Make](https://en.wikipedia.org/wiki/GNU_make) étant beaucoup plus sympathique que le [shell standard](https://fr.wikipedia.org/wiki/Bourne_shell)). 
 - Ce script ['./Makefile-gen.mkf'](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/Makefile-gen.mkf) nécessite des outils extérieurs qui se trouvent dans le sous-répertoire ['./tools'](https://github.com/Romain7426/X_Macros_-_Enum/tree/main/tools). Avant d'exécuter le script ['./Makefile-gen.mkf'](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/Makefile-gen.mkf), il faut générer ces outils. Cela est fait par le script [shell](https://fr.wikipedia.org/wiki/Bourne_shell) ['./tools-compile.sh'](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/tools-compile.sh). (Notons que ces outils devraient compiler sans problème.) 
 - Et c'est tout. Tout cela est automatiquement réalisé par le script [shell](https://fr.wikipedia.org/wiki/Bourne_shell) ['./configure.sh'](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/configure.sh). 
 
Plaintes 
 - Si le script ['./configure.sh'](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/configure.sh) se plaint que il ne trouve pas [GNU Make](https://en.wikipedia.org/wiki/GNU_make), éditez le fichier ['./configure.sh'](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/configure.sh) pour lui indiquer où trouver [GNU Make](https://en.wikipedia.org/wiki/GNU_make). 
 - Tout le code source suppose que le [compilateur](https://fr.wikipedia.org/wiki/Compilateur) est compatible avec la norme [C99](https://fr.wikipedia.org/wiki/C_(langage)#Normalisation). 
 - Pour les autres plaintes, a priori, je ne sais pas. 
 
[Compilateurs](https://fr.wikipedia.org/wiki/Compilateur) testés: 
 - [clang](https://fr.wikipedia.org/wiki/Clang): 86k 
 - [gcc11](https://fr.wikipedia.org/wiki/GNU_Compiler_Collection): 170k 
 - [tcc](https://en.wikipedia.org/wiki/Tiny_C_Compiler): 134k 
 - [pcc](https://en.wikipedia.org/wiki/Portable_C_Compiler): 82k 
 - D'autres? 

[Systèmes](https://fr.wikipedia.org/wiki/Syst%C3%A8me_d%27exploitation) testés: 
 - [OpenBSD](https://fr.wikipedia.org/wiki/OpenBSD) 
 - Les autres systèmes [BSD](https://fr.wikipedia.org/wiki/Berkeley_Software_Distribution) devraient fonctionner sans problème. 
 - Il devrait fonctionner sous [MacOSX](https://fr.wikipedia.org/wiki/MacOS). 
 - Les systèmes compatibles avec [Unix](https://fr.wikipedia.org/wiki/Unix) devraient fonctionner. 
 - Sur [Windows](https://fr.wikipedia.org/wiki/Microsoft_Windows), nous ne savons pas, nous n'avons pas essayé, mais le programme devrait pouvoir fonctionner à travers [Cygwin](https://fr.wikipedia.org/wiki/Cygwin), [MinGW](https://fr.wikipedia.org/wiki/MinGW), etc. 
 
Dépendances: 
 - Un [compilateur](https://fr.wikipedia.org/wiki/Compilateur) compatible avec la norme [C99](https://fr.wikipedia.org/wiki/C_(langage)#Normalisation). 
 - [GNU Make](https://en.wikipedia.org/wiki/GNU_make). 
 
Nota bene: 
 - Si la compilation des outils prend trop de temps, on peut l'éviter et passer directement à la génération du [Makefile](https://fr.wikipedia.org/wiki/Make#Makefile): 
    $ gmake -r -R -S -j 1 --warn-undefined-variables -f ./Makefile-gen.mkf  

## DSL Example

<pre>
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
</pre>

## Lib Example

<pre>
#include "anime.h"

const int stdlog_d  = open("./stdlog.log", O_WRONLY); 
const int stduser_d = 2; //stderr 
int_anime_error_t error_id; 
anime_t a_anime[1]; 
anime__make_r(a_anime, stdlog_d); 
error_id = anime__fill_from_file(a_anime, input_file_name, input_file_fd, stduser_d); 
if (error_id != ANIME__OK) { 
  if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_anime -> error_str); 
  break; 
}; 
</pre>


## Executable Example 

<pre>
$ ./destroot/bin/anime.exe
./destroot/bin/anime.exe: Check if an anime description file is properly written.
Usage: ./destroot/bin/anime.exe [&lt;options&gt;] &lt;infile&gt; [&lt;field name&gt;] 
  &lt;infile&gt; can be a filename or '-' for stdin (use './-' for a file named '-')
  If one &lt;field name&gt; or more are provided, print the value of the matching fields.
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
  --stduser &lt;file&gt;                     	  Redirect all the talk to the user to &lt;file&gt;. (Default is stderr.) (Use 'stdout', 'stderr', and 'stdnull' to redirect to stdout, stderr, and /dev/null.)
  --stdlog &lt;file&gt;                      	  Write stdlog to &lt;file&gt;. (By default, stdlog fd is 3; therefore the output of stdlog can be gotten using '3>&2' or '3>./stdlog.txt'.) (stdlog is intended for dev. But can be used by users.) (Use 'stdout', 'stderr', and 'stdnull' to redirect to stdout, stderr, and /dev/null.)
</pre>
 
<pre>
$ ./destroot/bin/anime.exe chaman.anime 3>./chaman.log
&lt;chaman.anime&gt;: OK
</pre>

<pre>
$ ./destroot/bin/anime.exe chaman.anime physique
physique.zone_de_choc.longueur =   0.500000 
physique.zone_de_choc.largeur  =   0.500000 
physique.zone_de_choc.hauteur  =  50.000000 
physique.masse = 240.000000 
&lt;chaman.anime&gt;: OK
</pre>



## Technical insights 

In order to parse an *anime* data file, *Mouton1-anime* does not use [*Lex*](https://en.wikipedia.org/wiki/Lex_programming_tool) nor [*Yacc*](https://en.wikipedia.org/wiki/Yacc). Instead, it implements its own lexer and parser. Admittedly, this latter approach takes a little longer to be implemented, but, unlike the former one, it is accurate, makes sense, easier to maintain, and prints understandable errors. 

Also, it does not build any tree. Building and maintaining a tree structure in [*C*](https://en.wikipedia.org/wiki/C_(programming_language)) is a pain. As the language is [*LL(1)*](http://compilation.irisa.fr), it reads directly the tokens, and fills the [*C*](https://en.wikipedia.org/wiki/C_(programming_language)) struct accordingly. However, as an extension, it can read expressions. Thus, there's an engine between the tokens and the data generation, which reorders expressions as postfix expressions, which ones can be directly computed on a stack. 

Architecture: 
 - tokenization (input buffer to provide back-tracking, automata, parser)
 - syntax filtering engine (reorders expressions to postfix expressions; check parenthesis; provides a «move to ending parenthesis» procedure) 
 - data generation 
 - consistency check 


## Auteurs  
 
Auteurs: 
 - [Romain: https://github.com/Romain7426](https://github.com/Romain7426)


## [Propriété intellectuelle](https://fr.wikipedia.org/wiki/Propri%C3%A9t%C3%A9_intellectuelle) 
 
Nous ne portons aucun intérêt à la [propriété intellectuelle](https://fr.wikipedia.org/wiki/Propri%C3%A9t%C3%A9_intellectuelle) du présent programme (ni en général, sauf pour en étudier les principes et exprimer que nous désapprouvons ces principes et la [propriété intellectuelle](https://fr.wikipedia.org/wiki/Propri%C3%A9t%C3%A9_intellectuelle) en général). Vous pouvez faire ce que il vous plaît avec ce programe. 

Nous aurions bien laissé ce programme dans le [domaine public](https://fr.wikipedia.org/wiki/Domaine_public_(propri%C3%A9t%C3%A9_intellectuelle)), mais il semblerait que il existerait une possibilité pour s'approprier du matériel qui serait dans le domaine public, et d'en restreindre l'accès. Afin de prévenir ce cas dégénéré, ce programme a été publié sous une licence équivalente à la [licence ISC](https://fr.wikipedia.org/wiki/Licence_ISC), mais en plus relâchée (cf. le fichier [COPYING](https://github.com/Romain7426/X_Macros_-_Enum/blob/main/COPYING) pour la consulter in extenso). En ce qui nous concerne, vous pouvez faire ce que vous voulez avec ce programme et son code, dans la mesure vous n'empêchez personne de l'utiliser, y compris nous-mêmes. 





Merci!! :smile: 

Et nous vous aimons tous. :kissing_heart: 




##  TODO 
 
 - A [FLTK](https://en.wikipedia.org/wiki/FLTK) [GUI](https://en.wikipedia.org/wiki/FLTK). 
 - A [curses](https://fr.wikipedia.org/wiki/Curses)/[PDcurses](https://fr.wikipedia.org/wiki/PDcurses) [GUI](https://en.wikipedia.org/wiki/GUI). 
 


