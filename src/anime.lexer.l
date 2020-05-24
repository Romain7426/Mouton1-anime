%{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "anime.h"
#include "anime.global.h"
#include "anime.parser.tab.h"

/* yytext yyleng ECHO */
/* Pour faire le pipe, on fait option + maj + l
   Maintenant, on cherche le tilde. */
/* Le tilde, il faut faire option + n + la touche appropriee. */
/* yytext, yyleng, yymore(), yyless, unput(), %array, input(), yyinput(), yyterminate(), yyin, yyout, yyrestart(), yywrap(), yy_scan_string(), yy_scan_buffer(), yy_scan_bytes(), 
*/
/* #define YY_DECL float lexscan( a, b ) float a, b; */
/* int yylex(void) */

#define yyinput input


#define PRINT_OUT(a)  nb_chars += yyleng; nb_chars_tot += yyleng; (void) fprintf(yyout, "%s[%s] ", a, yytext);

static int nb_lignes = 0, nb_chars = 0, nb_chars_tot = 0;

extern void anime_restart_lexer(void) {
 nb_lignes = nb_chars =  nb_chars_tot = 0;
}   

extern int anime_get_nb_lignes(void) {
 return nb_lignes;
}   

extern int anime_get_nb_chars(void) {
 return nb_chars;
}   

extern int anime_get_nb_chars_tot(void) {
 return nb_chars_tot;
}   

extern int anime_get_yyleng(void) {
 return yyleng;
}   

extern char * anime_get_yytext(void) {
 return yytext;
}   


static int match_symbole(char symbole[]) {
  char *temp;
  size_t taille;
  size_t i;

  taille = strlen(symbole);
  temp = (char *) malloc((taille + 1) * sizeof(char));

  if (temp == NULL) {
    PRINT_OUT("Manque de mémoire. On s'arrête.");
    return Token_EOF;
  }

  for (i = 0; i < taille; i++) {
    temp[i] = (char) tolower((int) symbole[i]);
  }
  temp[i] = '\0';
  /* fprintf(yyout, "%s%d%s", symbole, taille, temp); */

  
  /* Maintenant on compare le contenu du symbole aux mots-clefs
     en minuscule. C'est très moche comparé à l'OCaml. */
  /* if (strcmp(temp, "") == 0) {free(temp); return Token_;} */
  if (strcmp(temp, "physique") == 0) {free(temp); return Token_Physique;}
  if (strcmp(temp, "gameplay") == 0) {free(temp); return Token_Gameplay;}
  if (strcmp(temp, "graphique") == 0) {free(temp); return Token_Graphique;}
  if (strcmp(temp, "zone") == 0) {free(temp); return Token_Zone;}
  if (strcmp(temp, "choc") == 0) {free(temp); return Token_Choc;}
  if (strcmp(temp, "largeur") == 0) {free(temp); return Token_Largeur;}
  if (strcmp(temp, "longueur") == 0) {free(temp); return Token_Longueur;}
  if (strcmp(temp, "hauteur") == 0) {free(temp); return Token_Hauteur;}
  if (strcmp(temp, "masse") == 0) {free(temp); return Token_Masse;}
  if (strcmp(temp, "invincible") == 0) {free(temp); return Token_Invincible;}
  if (strcmp(temp, "membres") == 0) {free(temp); return Token_Membres;}
  if (strcmp(temp, "racines") == 0) {free(temp); return Token_Racines;}
  if (strcmp(temp, "action") == 0) {free(temp); return Token_Action;}
  if (strcmp(temp, "laction") == 0) {free(temp); return Token_LAction;}
  if (strcmp(temp, "menu") == 0) {free(temp); return Token_Menu;}
  if (strcmp(temp, "affichage") == 0) {free(temp); return Token_Affichage;}
  if (strcmp(temp, "gestionnaire") == 0) {free(temp); return Token_Gestionnaire;}
  if (strcmp(temp, "evenement") == 0) {free(temp); return Token_Evenement;}
  if (strcmp(temp, "genere") == 0) {free(temp); return Token_Genere;}
  if (strcmp(temp, "par") == 0) {free(temp); return Token_Par;}
  if (strcmp(temp, "traitement") == 0) {free(temp); return Token_Traitement;}
  if (strcmp(temp, "membre") == 0) {free(temp); return Token_Membre;}
  if (strcmp(temp, "fils") == 0) {free(temp); return Token_Fils;}
  if (strcmp(temp, "angle") == 0) {free(temp); return Token_Angle;}
  if (strcmp(temp, "max") == 0) {free(temp); return Token_Max;}
  if (strcmp(temp, "qui") == 0) {free(temp); return Token_Qui;}
  if (strcmp(temp, "x") == 0) {free(temp); return Token_X;}
  if (strcmp(temp, "y") == 0) {free(temp); return Token_Y;}
  if (strcmp(temp, "z") == 0) {free(temp); return Token_Z;}
  if (strcmp(temp, "tous") == 0) {free(temp); return Token_Tous;}
  if (strcmp(temp, "aucun") == 0) {free(temp); return Token_Aucun;}
  if (strcmp(temp, "points") == 0) {free(temp); return Token_Points;}
  if (strcmp(temp, "de") == 0) {free(temp); return Token_De;}
  if (strcmp(temp, "vie") == 0) {free(temp); return Token_Vie;}
  if (strcmp(temp, "hostile") == 0) {free(temp); return Token_Hostile;}
  if (strcmp(temp, "image") == 0) {free(temp); return Token_Image;}

  if (strcmp(temp, "vrai") == 0) {free(temp); yyanimelval.yybooleen = vrai; return Token_Booleen;}
  if (strcmp(temp, "faux") == 0) {free(temp); yyanimelval.yybooleen = faux; return Token_Booleen;}

  if (strcmp(temp, "div") == 0) {free(temp); return Token_DivEntier;}
  if (strcmp(temp, "mod") == 0) {free(temp); return Token_ModEntier;}

  if (strcmp(temp, "pi") == 0) {free(temp); yyanimelval.yyreel = (double) pi; return Token_Reel;}
  if (strcmp(temp, "e") == 0) {free(temp); yyanimelval.yyreel = (double) e; return Token_Reel;}

  //if (strcmp(temp, "parler") == 0) {free(temp); yyanimelval.yylaction = parler; return Token_LAction;}
  //if (strcmp(temp, "voler") == 0) {free(temp); yyanimelval.yylaction = voler; return Token_LAction;}

  if (strcmp(temp, "fichier") == 0) {free(temp); return Token_Fichier;}
  if (strcmp(temp, "procedure") == 0) {free(temp); return Token_Procedure;}
  if (strcmp(temp, "procédure") == 0) {free(temp); return Token_Procedure;}
  if (strcmp(temp, "icone") == 0) {free(temp); return Token_Icone;}
  if (strcmp(temp, "icône") == 0) {free(temp); return Token_Icone;}

  free(temp);
  return Token_Ident;
}
  

%}


eol \n
blancs [\t\r\ ]+
comment (\/\/[^\n]*)|(#[^\n]*)

chiffre  [0-9]
entier  {chiffre}+
reel    (\.{chiffre}+)|({chiffre}+\.{chiffre}*)

lettre [a-zA-Z]
symbole {lettre}({lettre}|[\-\_\.]|{chiffre})*

chaine \"[^\"]*\"

open_par \(
open_brace \{
open_bracket \[
close_par \)
close_brace \}
close_bracket \]

plusentier \+
moinsentier \-
multentier \*

plusreel \+\.
moinsreel \-\.
multreel \*\.
divreel \/\.


assign \:\=
virgule \,
ptvirg \;



%option noyywrap
%option nounput
%%

<<EOF>>        (void) fprintf(yyout, "Fin.\nNombre de lignes : %d\nNombre de caractères dans la ligne courante : %d\nNombre total de caractères : %d\n", nb_lignes, nb_chars, nb_chars_tot); BEGIN(INITIAL); return Token_EOF;

{eol}          PRINT_OUT("EOL "); nb_lignes++; nb_chars = 0; 

{blancs}       PRINT_OUT("Blancs ");

{comment}      PRINT_OUT("Commentaire one-line");

"/*"        {
              PRINT_OUT("Commentaire multi-lines");
              int c;

              for (;;) {
                do { c = yyinput(); } while (c != '*' && c != EOF);

                if (c == EOF) {
                  fprintf(yyout, "EOF in comment" );
                  break;
                }

                do { c = yyinput(); } while (c == '*');

                if (c == '/') break;
              }
            }


{entier} {
  PRINT_OUT("Entier "); 
  yyanimelval.yyentier = atoi(yytext); 
  return Token_Entier;
}

{reel} {
  PRINT_OUT("Reel ");
  yyanimelval.yyreel = atof(yytext);
  return Token_Reel;
}

{symbole} {
  int token;
  PRINT_OUT("Symbole ");
  token = match_symbole(yytext);

  if (token != Token_Ident) {
    return token;
  }

  yyanimelval.yyident = (char *) malloc((yyleng + 1) * sizeof(char));
  //yyanimelval.yyident = new char[yyleng + 1];

  if (yyanimelval.yyident == NULL) {
    PRINT_OUT("Pas assez de mémoire pour continuer.");
    return Token_EOF;
  }

  strcpy(yyanimelval.yyident, yytext);
  return token;
}

{chaine} {
  PRINT_OUT("Chaine ");
  yyanimelval.yychaine = (char *) malloc((yyleng - 1) * sizeof(char));
  //yyanimelval.yychaine = new char[yyleng -2 + 1];

  if (yyanimelval.yychaine == NULL) {
    PRINT_OUT("Pas assez de mémoire pour continuer.");
    return Token_EOF;
  }
  
  strncpy(yyanimelval.yychaine, &(yytext[1]), yyleng - 2);
  yyanimelval.yychaine[yyleng - 2] = '\0';
  return Token_Chaine;
}
  

{open_par}     PRINT_OUT("Open_Par "); return Token_OpenPar;
{open_brace}   PRINT_OUT("Open_Brace "); return Token_OpenBrace;
{open_bracket} PRINT_OUT("Open_Bracket "); return Token_OpenBracket;
 
{close_par}     PRINT_OUT("Close_Par "); return Token_ClosePar;
{close_brace}   PRINT_OUT("Close_Brace "); return Token_CloseBrace;
{close_bracket} PRINT_OUT("Close_Bracket "); return Token_CloseBracket;

{plusreel}         PRINT_OUT("PlusReel ");  return Token_PlusReel;
{moinsreel}        PRINT_OUT("MoinsReel "); return Token_MoinsReel;
{multreel}         PRINT_OUT("MultReel ");  return Token_MultReel;
{divreel}          PRINT_OUT("Div ");   return Token_DivReel;

{plusentier}         PRINT_OUT("PlusEntier ");  return Token_PlusEntier;
{moinsentier}        PRINT_OUT("MoinsEntier "); return Token_MoinsEntier;
{multentier}         PRINT_OUT("MultEntier ");  return Token_MultEntier;

{assign}       PRINT_OUT("Assign ");  return Token_Assign;
{virgule}      PRINT_OUT("Virgule ");  return Token_Virgule;
{ptvirg}       PRINT_OUT("Ptvirg ");  return Token_Ptvirg;

.              PRINT_OUT("Autre ");

%%
/*
// Fonction qui est appelée lorsque EOF est atteint.
// Retourne 0 (false) si on continue.
// Sinon, ça termine et renvoie 0 à l'appelant.
// %option noyywrap
//yywrap(){}
*/
