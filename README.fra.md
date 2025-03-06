
FRANCAIS: [README.fra.md](README.fra.md)
GLOBISH: [README.eng.md](README.eng.md)

---------------------------------------------------------------------------

COMMENTAIRE de mars 2025

Ici, il s'agit d'un commentaire en complément de la description ci-dessous (datant de mars 2024).
 - Tout d'abord, j'en ai marre du globish. Je suis français et vous me saoulez. 
 - Ensuite, j'en ai marre du langage [*C*](https://en.wikipedia.org/wiki/C_(programming_language)). 
   À mon avis, le principe du langage C est bon: faire abstraction du processeur sous-jacent, 
   et opérer sur la mémoire. Opérant sur la mémoire, le langage C est appelé le langage de pointeurs.
   De ce fait, le langage C serait un bon intermédiaire entre un langage processeur et un 
   langage utilisateur. D'ailleurs, d'aucuns le considère comme un méta-assembleur.
 - Cependant, l'implémentation actuelle est infâme. (Moins pire que le C++ cependant.) 
 - À propos du C++, rappelons ces propos de son créateur, Bjarne Stroustrup: ["I did it for you all"]([*C*](http://harmful.cat-v.org/software/c++/I_did_it_for_you_all)
 - Un programme ne compile jamais de la même facon. Ca dépend du systeme et de l'année.
   Quelque chose qui compile sur un systeme ne compilera pas sur le voisin.
   Quelque chose qui compilait l'année dernière ne compilera plus cette année.
 - Quand on écrit une erreur, le compilateur essaye de trouver une semantique puis continue. 
   Pour corriger un tel comportement, il faut activer moult options du compilateur. 
   (Par exemple, dans Mouton2, il y avait une faute de frappe dans un nom d'une fonction, 
   et ça n'a pas empêché le compilateur de compiler. Magie noire.) 
 - On a beau lui dire de désactiver les optimisations, le compilateur optimise quand même.
   Et quand on se retrouve dans le débuggueur, celui-ci ne sait pas où on est.
   Et quand on lui demande d'afficher une variable, il répond que il ne la trouve pas. 
 - Et ceci, quand gdb fonctionne. La plupart du temps, gdb plante.
   Et quand il ne plante pas, il n'affiche que des points d'interrogation dans la backtrace. 
   Donc on se retrouve à débugguer en mettant des printf partout. 
 - De fait, les compilateurs C sont des programmes bloated, qui doivent savoir faire le café.
 - Les préprocesseur bizarre. 
 - L'absence de modules!!!!! (collision des noms) (et portée des nom)
 - La gestion des dépendances (entre modules) est infecte. 
 - une libc bizarre
 - libkernelcall (unistd.h) et la libc devrait être séparées. On voudrait pouvoir ne pas utiliser la libc. 
   En revanche, on ne veut pas savoir comment techniquement réalisé un kernel call (int 80? syscall? On s'en fout.) 
   On devrait pouvoir utiliser la libC qui nous plait. 
 - De fait, il existe un concours du code le plus obscur en C. 
 - Les bibliothèques tierces qui ne compilent jamais ("Tient! Cette bibliothèque a l'air de résoudre notre problème." Puis make échoue.). 
 - GitHub est pénible. (Le côté réseau social pour geek est néanmoins sympa.)
 - Dans les faits, je suis improductif en C. Je perds la quasi-totalité de mon temps 
   en futilités et en points techniques qui n'ont aucun intérêt. Vraiment en putain de conneries. 
   Alors que je devrais programmer le jeu sur un plan projectif! 
   J'en ai putain de marre. Ca me saoule. 
   Tout ça est une perte de temps. 
   Donc j'arrête. Terminé. Je ne veux plus en entendre parler. 
   J'ai le jeu. Il possède une beauté. Mais je ne retouche plus au C.
   Pour ma part, par le passé, le langage où je fus productif fut le Pascal (Turbo/Delphi). 
   J'arrête. 
   Il n'y aura aucune amélioration à l'avenir. Ni aucun correctif.
   J'arrête. 


À toute cette instabilité et ce chaos, je préfère les consoles de jeux:
 - le matériel ne change jamais 
 - le compilateur ne change jamais

Sept ans plus tard, le même programme compile et fonctionne de la même facon!


Ceci étant dit, je suis admiratif de [Fabrice Bellard](http://fr.wikipedia.org/Fabrice_Bellard) qui, lui, arrive à coder C et produire de puissants logiciels: [FFmpag](http://fr.wikipedia.org/FFmpeg), [QEmu](http://fr.wikipedia.org/QEmu), et [TinyCC](http://fr.wikipedia.org/TinyCC). 
 
Nous sommes tous différents.

J'arrete.   


---------------------------------------------------------------------------

VERSION de mars 2024

---------------------------------------------------------------------------

# Mouton1-anime
 
*Mouton1-anime* est un sous-projet du jeu [*Mouton1*](https://github.com/Romain7426/Mouton1). 

## De quoi s'agit-il?  

*Mouton1-anime* est un DSL ([«data specific language»](https://www.youtube.com/watch?v=Z8Xamkb-J2k) ou [là](https://www.youtube.com/watch?v=oSmqbnhHp1c)), une bibliothèque, et un programme: 
 - Il spécifie un langage pour décrire un objet *anime*. 
 - Il fournit fournit une bibliothèque qui lit une description *anime* et qui remplit une structure [*C*](https://en.wikipedia.org/wiki/C_(programming_language)). 
 - Il fournit un programme qui vérifie la syntaxe d'une description d'un objet *anime*, et qui affiche une description des erreurs. 


## Compilation et installation 

<pre>
$ echo "tcc" > ./CC          # Ou votre compilateur [*C*](https://en.wikipedia.org/wiki/C_(programming_language)) favori. (Nous utilisons [tcc](https://en.wikipedia.org/wiki/Tiny_C_Compiler) pour le développement.) 
$ echo "gmake" > ./GMAKE     # GNU-Make est un pré-requis. 
$ sh ./configure.sh          # Génération des outils, puis génération du Makefile. 
$ make 
$ make install 
</pre>
 
Personnalisations
 - [Compilateur](https://fr.wikipedia.org/wiki/Compilateur) — Le compilateur utilisé par défaut est 'cc'. Vous pouvez utiliser votre compilateur préféré à travers le fichier ['./CC'](CC). 
    - $ echo "cc" > ./CC 
    - $ echo "clang" > ./CC 
    - $ echo "/usr/local/bin/x86_64-unknown-openbsd7.0-gcc-11.2.0" > ./CC 
    - $ echo "pcc -L /usr/lib " > ./CC 
    - $ echo "tcc" > ./CC 
 - Le répertoire d'installation — Par défaut, l'installation se fait dans le sous-répertoire './destroot'. Ensuite, il suffit de copier ce répertoire où vous voulez. 
 - Aucune autre personnalisation. 
 
Configuration
 - La système de onfiguration n'est pas basé sur [GNU Autohell](https://en.wikipedia.org/wiki/Autohell). 
 - À la place, nous avons conçu notre propre système. Celui-ci est basé sur [GNU Make](https://en.wikipedia.org/wiki/GNU_make). 
 - Le [Makefile](https://en.wikipedia.org/wiki/Make_(software)#Makefile) est générer par GMake à partir du fichier ['./Makefile-gen.mkf'](Makefile-gen.mkf). 
 - Le script ['./Makefile-gen.mkf'](Makefile-gen.mkf) nécessite des outils qui doivent être compilés en amont. Ceux-ci sont localisés dans le sous-répertoire ['./tools'](tools). Pour les compiler, il faut lancer le script sell ['./tools-compile.sh'](tools-compile.sh): «sh ./tools-compile.sh» 
 - Et c'est fini. 
 - En une seule étape, il est possible d'utiliser le script [shell](https://en.wikipedia.org/wiki/Bourne_shell) ['./configure.sh'](configure.sh): «sh ./congigure.sh» 
 - Le script shell ['./configure.sh'](configure.sh) aura besoin de savoir comment invoquer GMake: 
    - $ echo "gmake" > GMAKE
 
Testé avec les [compilateurs](https://fr.wikipedia.org/wiki/Compilateur): 
 - [clang](https://fr.wikipedia.org/wiki/Clang)
 - [gcc11](https://fr.wikipedia.org/wiki/GNU_Compiler_Collection)
 - [tcc](https://fr.wikipedia.org/wiki/Tiny_C_Compiler)
 - [pcc](https://fr.wikipedia.org/wiki/Portable_C_Compiler) - Echoue. Son préprocesseur meurt. 

Testé sur les systèmes suivants: 
 - [OpenBSD](https://en.wikipedia.org/wiki/OpenBSD) 
 - Les autres [BSD](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution) - Pas testé mais ne devrait pas poser de problèmes. 
 - [MacOSX](https://en.wikipedia.org/wiki/MacOS) - Pas testé mais ne devrait pas poser de problèmes. 
 - [Unix](https://en.wikipedia.org/wiki/Unix)-compatible - Pas testé mais ne devrait pas poser de problèmes. 
 - [Windows](https://en.wikipedia.org/wiki/Microsoft_Windows) - Il y a vingt ans, il y fonctionnait. Hui, je ne sais pas. ([Cygwin](https://en.wikipedia.org/wiki/Cygwin)? [MinGW](https://en.wikipedia.org/wiki/MinGW)? Autre?)
 
Dépendances: 
 - Le code source est écrit en [C99](https://en.wikipedia.org/wiki/C99). 
 - [GNU Make](https://fr.wikipedia.org/wiki/GNU_make). 
 

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

 action "parler" {
  affichage := "parler";
  icone := "";
  gestionnaire := { fichier := "script.pml"; procedure := "chaman_parler"; } ; 
 } 
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


## Lib exemple

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


## Executable example 

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



## Notes techniques

[*Lex*](https://fr.wikipedia.org/wiki/Lex_programming_tool) et [*Yacc*](https://fr.wikipedia.org/wiki/Yacc) donnant des messages d'erreurs abscons, voire étant inintuitifs, nous avons écrit notre propre analyseur. Quand nous avions des erreurs de syntaxe ou d'analyse lexicale, personne ne comprenait quelle était l'erreur. 

Notre analyseur regroupe les caractères en lexèmes (unités lexicales, tokens). Et, stricto sensu, l'analyseur syntaxique n'en ai pas un. Il vérifie la syntaxe. Car, si la syntaxe est correcte, alors on peut directement interprétées et générées les données. De ce fait, notre analyseur ne produit pas d'arbre de syntaxe. L'analyseur se contente donc de vérifier la correction de la syntaxe. Toutefois, pour vérifier la syntaxe d'une expression infixe, un analyseur LALR(0) possèdant deux états a été implémenté pour les sous-expressions (pour analyser les sous-expressions, on est obligé de se souvenir du chemin, et du point où on en était dans l'analyse quand on remonte). 

Nota bene: 
 - Les commentaires multi-lignes du [*C*](https://en.wikipedia.org/wiki/C_(programming_language)) ne sont pas reconnus. 
   Mais les commentaires intra-lignes sont reconnus: /* .... */ <br> 

À propos des DSL («data specific language»), vous pouvez visionner ces vidéos de [*Naughty Dog*](https://en.wikipedia.org/wiki/Naughty_Dog): 
 - https://www.youtube.com/watch?v=Z8Xamkb-J2k
 - https://www.youtube.com/watch?v=oSmqbnhHp1c 
 
À propos de l'analyse lexicale et syntaxique, il y a ce site: 
 - http://compilation.irisa.fr 
 
 
## Auteurs 
 
Auteurs: 
 - [Romain: https://github.com/Romain7426](https://github.com/Romain7426)


## [Propriété intellectuelle](https://fr.wikipedia.org/wiki/Propriete_intellectuelle) 

On s'en fout. Faites-en ce que vous en voulez. 
 
Ce travail aurait pu être publié dans le [domaine publique](https://en.wikipedia.org/wiki/Public_domain). Cependant, il semblerait que il existe des moyens s'approprier respectivement des droits. Et donc nous désapproprier ce travail. Pour empêcher ce cas, ce travail est publiée sous une version allégée de la [licence ISC](https://en.wikipedia.org/wiki/ISC_license). Vous pouvez consulter [COPYING](COPYING)
 
 
##  AGENDA 
 
 - Un [GUI](https://en.wikipedia.org/wiki/GUI) en [FLTK](https://en.wikipedia.org/wiki/FLTK) 
 - Un [GUI](https://en.wikipedia.org/wiki/GUI) en [curses](https://en.wikipedia.org/wiki/Curses)/[PDcurses](https://en.wikipedia.org/wiki/PDcurses) 
 - Un [GUI](https://en.wikipedia.org/wiki/GUI) en [Lazarus](https://en.wikipedia.org/wiki/Lazarus_(software))
 - Nettoyer le code


## Merci 

Merci!! :smile: 

Nous vous aimons. :kissing_heart: 
