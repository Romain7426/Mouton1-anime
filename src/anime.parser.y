%{ /* Header */
#include <stdlib.h>
#include <stdio.h>
#include "anime.h"
#include "anime.global.h"
#include "anime.parser.tab.h"
//#include "action.hpp"

/*
extern const int get_nb_lignes(void);
extern const int get_nb_chars(void);
extern const int get_nb_chars_tot(void);
extern const int get_yyleng(void);
extern const char * get_yytext(void);
extern int yylex(void);
*/
static void yyerror(const char * s);
static inline void yyerror3(const char * str1, const char * str2, const char * str3);


#define VERIF_NOT_NULL(a,b) if (a == NULL) {yyerror("Manque de mémoire."); return b;}

#define this yyanime_global_objet_being_filled_up_while_parsing


#if 1
void anime_parser_reset(void) {
}
#else
 CBonhomme * bongars;


#define MAXMEMBRE 32
static anime_memdesc memtab[MAXMEMBRE];
static int memnbelts = 0;
static const int memlookup(char * nom) {
  for (int i = 0; i < memnbelts; i++) {
    if (strcmp(nom, memtab[i].nom) == 0) {
      return i;
    }
  }
  return -1;
}


static const void memempiler(CPantin * pere, liste * fils) {
  anime_filsdesc * temp;

  while (fils != NULL) {
    int j;
    temp = (anime_filsdesc *) fils -> contenu;

    if ((j = memlookup(temp -> qui)) < 0) {
      yyerror3("Le membre \"", temp -> qui, " n'a pas ete defini. On continue néanmoins.\n");
    }
    
    else {
      CPantin * p = new CPantin;
      p -> AjouterMembre(memtab[j].image, temp -> x, temp -> y, temp -> z, memtab[j].largeur, memtab[j].hauteur, memtab[j].angle_max_y);
      pere -> SetPantinFilsAuDernierMembre(p);
      memempiler(p, memtab[j].fils);
    }
    fils = fils -> suivant;
  }
}


void anime_parser_reset(void) {
  memnbelts = 0;
}
#endif 



%}

/* Le type de yylval. */
/* Attention !!!!!!!!
   Si problème de définition de type, bien regardé le makefile,
   mais surtout avant chaque #include "parser.h"
   avoir mis un #include "le fichier de description des types.h"
*/
%union {
booleen yybooleen;
int yyentier;
float yyreel;
char * yychaine;
char * yyident;
char * yynom;
#if 0
anime_action yylaction;

anime_tcode * yycode;
anime_sgenere * yygenere;
anime_filsdesc * yyfils;
anime_tmembre * yymembre;
anime_tevent * yyevent;
anime_taction * yyaction;
liste * yyliste;
#endif 
}

%token <yybooleen> Token_Booleen
%token <yyentier>  Token_Entier
%token <yyreel>    Token_Reel
%token <yychaine>  Token_Chaine
%token <yyident>   Token_Ident
%token <yyaction>  Token_LAction

/*
  %token Token_Assign
  %token Token_Plus Token_Moins
  %token Token_Mult Token_Div
*/

%token Token_OpenPar Token_OpenBrace Token_OpenBracket
%token Token_ClosePar Token_CloseBrace Token_CloseBracket

%token Token_Ptvirg Token_Virgule
%token Token_EOF

%token Token_Zone Token_Choc Token_Masse Token_Invincible
%token Token_Membres Token_Racines
%token Token_Action
%token Token_Menu Token_Affichage Token_Gestionnaire
%token Token_Evenement Token_Genere Token_Par Token_Traitement
%token Token_Membre Token_Fils Token_Angle Token_Max
%token Token_Qui Token_X Token_Y Token_Z
%token Token_Tous Token_Aucun
%token Token_Image

%token Token_Points Token_De Token_Vie Token_Hostile

%token Token_Largeur Token_Longueur Token_Hauteur

%token Token_Physique Token_Gameplay Token_Graphique

%token Token_Fichier Token_Procedure Token_Icone



%token Token_Assign

/*
%token Token_Begin Token_End
%token Token_If Token_Then Token_Else
%token Token_While Token_Do
%token Token_Repeat Token_Until
%token Token_For Token_To
%token Token_Write Token_Writeln
%token Token_Read Token_Readln
%token Token_DeuxPoints
%token Token_Plus Token_Moins Token_Mult Token_Div Token_Mod
%token Token_Ou Token_Et
%token Token_Equal Token_Diff Token_Inf Token_Sup Token_InfEq Token_SupEq Token_Not
%token Token_Pascal
%token Token_Function Token_Procedure
%token Token_Var
%token Token_Integer Token_Real Token_Boolean
*/




%type <yyentier> expr_entier expr_entier1 expr_entier2 
%token Token_PlusEntier Token_MoinsEntier Token_MultEntier Token_DivEntier Token_ModEntier

%type <yyreel> expr_reel expr_reel1 expr_reel2
//%token Token_ZSol
%token Token_PlusReel Token_MoinsReel Token_MultReel Token_DivReel





%type <yynom> nom

%type <yycode> code
%type <yygenere> genere
%type <yyfils> fils
%type <yymembre> membre
%type <yyevent> evenement 
//%type <yyaction> action

%type <yyliste> liste_membre
%type <yyliste> liste_membres_racines
%type <yyliste> liste_fils
%type <yyliste> liste_evenement
//%type <yyliste> liste_action

//%type <physique> physique 
//%type <gameplay> gameplay 
//%type <graphique> graphique
//%type <anime> main

%start main

%%

main: physique gameplay graphique {
  return 0;
};

physique: 
Token_Physique Token_OpenBrace
  Token_Zone Token_De Token_Choc Token_Assign Token_OpenBrace
    Token_Longueur Token_Assign expr_reel Token_Ptvirg
    Token_Largeur  Token_Assign expr_reel Token_Ptvirg
    Token_Hauteur  Token_Assign expr_reel Token_Ptvirg
  Token_CloseBrace Token_Ptvirg
Token_Masse Token_Assign expr_reel Token_Ptvirg
Token_CloseBrace
{
#if 1
  this -> choc_longueur = $10; 
  this -> choc_largeur = $14; 
  this -> choc_hauteur = $18; 
  this -> masse = $24; 
#else 
  bongars -> SetDimension($10, $14, $18);
#endif 
};

gameplay:
Token_Gameplay Token_OpenBrace 
 Token_Points Token_De Token_Vie Token_Assign  expr_entier  Token_Ptvirg
 Token_Invincible                Token_Assign Token_Booleen Token_Ptvirg
 Token_Hostile                   Token_Assign Token_Booleen Token_Ptvirg
 liste_action
 liste_evenement
Token_CloseBrace
{
#if 1
  this -> vie        =  $7; 
  this -> invincible = $11; 
  this -> hostile    = $15; 
#else 
  bongars->Hostile = $15;
#endif 
};

graphique:
Token_Graphique Token_OpenBrace 
 liste_membre
 Token_Membres Token_Racines Token_Assign liste_membres_racines Token_Ptvirg
Token_CloseBrace
{
#if 1 
  // Do nothing 
#else
  anime_filsdesc * temp;
  while ($7 != NULL) {
    int j;
    temp = (anime_filsdesc *) $7->contenu;

    if ((j = memlookup(temp -> qui)) < 0) {
      yyerror3("Le membre \"", temp -> qui, "\" n'a pas ete defini. On continue néanmoins.\n");
    }
    
    else {
      bongars -> AjouterMembre(memtab[j].image, temp -> x, temp -> y, temp -> z, memtab[j].largeur, memtab[j].hauteur, memtab[j].angle_max_y);
      memempiler(bongars, memtab[j].fils);
    }
    $7 = $7 -> suivant;
  }
#endif 
};


liste_action:
action liste_action  
| 
;

action:
Token_Action nom Token_OpenBrace
  Token_Affichage    Token_Assign Token_Chaine Token_Ptvirg 
  Token_Icone        Token_Assign Token_Chaine Token_Ptvirg 
  Token_Gestionnaire Token_Assign code         Token_Ptvirg 
Token_CloseBrace
{
#if 1 
  anime__actions_push(this, $2, /*affichage*/$6, /*icone*/$10, /*gestionnaire_fichier*/this -> temp_code_fichier, /*gestionnaire_proc*/this -> temp_code_proc);  
#else 
  bongars->AjouterAction($6, $10, $14->fichier, $14->proc);
  anime_del_code(&($14));
#endif 
};

liste_evenement:
  evenement liste_evenement {
#if 0 
$$ = mp($2, $1); VERIF_NOT_NULL($$,-8); 
#endif 
}
| {
#if 0 
$$ = liste_vide();
#endif 
}
;

evenement:
Token_Evenement nom Token_OpenBrace
  Token_Genere Token_Par Token_Assign genere Token_Ptvirg 
  Token_Traitement       Token_Assign code   Token_Ptvirg 
Token_CloseBrace
{
#if 1
  anime__events_push(this, /*events_nom*/$2, 
    /*events_genere_type*/this -> temp_events_genere_type, /*events_genere_code_fichier*/this -> temp_events_genere_code_fichier, /*events_genere_code_proc*/this -> temp_events_genere_code_proc, 
    /*events_traitement_fichier*/this -> temp_events_traitement_code_fichier, /*events_traitement_proc*/this -> temp_events_traitement_code_proc);  

#else 
  $$ = anime_new_event();
  VERIF_NOT_NULL($$,-9)

  $$->genere = $7->type;
  if ($7->type == CODE) {
    $$->par = (anime_tcode *)NULL;
  }

  else {
    $$->par = $7->code;
  }

  anime_del_sgenere($7);
  $$->traitement = $11;
#endif 
};



liste_membre:
  membre liste_membre { 
#if 0 
$$ = mp($2, $1); VERIF_NOT_NULL($$,-10); 
#endif 
}
| {
#if 0 
$$ = liste_vide();
#endif 
}
;

membre:
Token_Membre nom Token_OpenBrace 
  Token_Fils                    Token_Assign liste_fils   Token_Ptvirg 
  Token_Image                   Token_Assign Token_Chaine Token_Ptvirg 
  Token_Largeur                 Token_Assign expr_reel    Token_Ptvirg 
  Token_Hauteur                 Token_Assign expr_reel    Token_Ptvirg 
  Token_Angle Token_Max Token_Y Token_Assign expr_reel    Token_Ptvirg 
Token_CloseBrace
{
#if 1
  anime__membres_push(this, $2, $10, /*largeur*/$14, /*hauteur*/$18, /*angle_max_y*/$24); 
#else
  if (memnbelts < MAXMEMBRE) {
    memtab[memnbelts].nom = $2;
    memtab[memnbelts].image = $10;
    memtab[memnbelts].fils = $6;
    memtab[memnbelts].largeur = $14;
    memtab[memnbelts].hauteur = $18;
    memtab[memnbelts].angle_max_y = $24;
    memnbelts++;
  }
#endif 
};

liste_membres_racines: 
  une_racine liste_virg liste_membres_racines {
}
| liste_virg {
};

une_racine:
Token_OpenBrace
  Token_Qui           Token_Assign nom       Token_Ptvirg 
  Token_X             Token_Assign expr_reel Token_Ptvirg 
  Token_Y             Token_Assign expr_reel Token_Ptvirg 
  Token_Z             Token_Assign expr_reel Token_Ptvirg 
  Token_Angle Token_Y Token_Assign expr_reel Token_Ptvirg 
Token_CloseBrace
{
#if 1
  anime__racines_push(this, /*qui*/$4, /*x*/$8, /*y*/$12, /*z*/$16, /*angle_y*/$21); 
#else
/*
  $$ = new anime_filsdesc;
  $$->qui = $4;
  $$->x = $8;
  $$->y = $12;
  $$->z = $16;
  $$->angle_y = $21;
*/
#endif 
};





liste_fils:
  liste_fils fils liste_virg {
#if 0 
$$ = mp($2, $1); VERIF_NOT_NULL($$,-12);
#endif 
}
| liste_virg {
#if 0 
$$ = liste_vide();
#endif 
}
;

fils:
Token_OpenBrace
 Token_Qui Token_Assign Token_Ident Token_Ptvirg
 Token_X Token_Assign expr_reel Token_Ptvirg
 Token_Y Token_Assign expr_reel Token_Ptvirg
 Token_Z Token_Assign expr_reel Token_Ptvirg
 Token_Angle Token_Y Token_Assign expr_reel Token_Ptvirg
Token_CloseBrace
{
#if 1
#else 
  $$ = new anime_filsdesc;
  $$->qui = $4;
  $$->x = $8;
  $$->y = $12;
  $$->z = $16;
  $$->angle_y = $21;
#endif 
};


liste_virg:
  liste_virg Token_Virgule
| 
  ;


genere:
  Token_Aucun {
#if 1 
    this -> temp_events_genere_type         = ANIME_EVENTS_AUCUN; 
    this -> temp_events_genere_code_fichier = NULL; 
    this -> temp_events_genere_code_proc    = NULL; 
#else 
    $$ = anime_new_sgenere(); VERIF_NOT_NULL($$,-14); $$->type = AUCUN; $$->code = NULL;
#endif 
}
| Token_Tous {
#if 1
  this -> temp_events_genere_type         = ANIME_EVENTS_TOUS; 
  this -> temp_events_genere_code_fichier = NULL; 
  this -> temp_events_genere_code_proc    = NULL; 
#else 
  $$ = anime_new_sgenere(); VERIF_NOT_NULL($$,-15); $$->type = TOUS; $$->code = NULL;
#endif 
}
| code {
#if 1
  this -> temp_events_genere_type         = ANIME_EVENTS_CODE; 
  this -> temp_events_genere_code_fichier = this -> temp_code_fichier; 
  this -> temp_events_genere_code_proc    = this -> temp_code_fichier; 
#else 
  $$ = anime_new_sgenere(); VERIF_NOT_NULL($$,-16); $$->type = CODE; $$->code = $1;
#endif 
}
;

code:  
Token_OpenBrace 
Token_Fichier   Token_Assign Token_Chaine Token_Ptvirg 
Token_Procedure Token_Assign Token_Chaine Token_Ptvirg
Token_CloseBrace
{ 
#if 1 
  this -> temp_code_fichier = $4;
  this -> temp_code_proc = $8; 
#else 
  $$ = anime_new_code(); $$->fichier = $4; $$->proc = $8; 
#endif 
};




expr_entier:
  expr_entier Token_PlusEntier  expr_entier1 { $$ = $1 + $3; }
| expr_entier Token_MoinsEntier expr_entier1 { $$ = $1 - $3; }
| expr_entier1 { $$= $1; }
;

expr_entier1:
  expr_entier1 Token_MultEntier expr_entier2 { $$ = $1 * $3; }
| expr_entier1 Token_DivEntier  expr_entier2 { $$ = $1 / $3; }
| expr_entier1 Token_ModEntier  expr_entier2 { $$ = $1 % $3; }
| expr_entier2 { $$ = $1; }
;

expr_entier2:
  Token_Entier { $$ = $1; }
| Token_PlusEntier  expr_entier2 { $$ = $2; }
| Token_MoinsEntier expr_entier2 { $$ = - $2; }
| Token_OpenPar expr_entier Token_ClosePar { $$ = $2; }
;




expr_reel:
  expr_reel Token_PlusReel    expr_reel1 { $$ = $1 + $3; }
| expr_reel Token_PlusEntier  expr_reel1 { $$ = $1 + $3; }
| expr_reel Token_MoinsReel   expr_reel1 { $$ = $1 - $3; }
| expr_reel Token_MoinsEntier expr_reel1 { $$ = $1 - $3; }
| expr_reel1 { $$= $1; }
;

expr_reel1:
  expr_reel1 Token_MultReel   expr_reel2 { $$ = $1 * $3; }
| expr_reel1 Token_MultEntier expr_reel2 { $$ = $1 * $3; }
| expr_reel1 Token_DivReel    expr_reel2 { $$ = $1 / $3; }
| expr_reel1 Token_DivEntier  expr_reel2 { $$ = $1 / $3; }
| expr_reel2 { $$ = $1; }
;

expr_reel2:
  Token_Reel   { $$ = $1; }
| Token_Entier { $$ = $1; }
| Token_PlusReel    expr_reel2 { $$ = $2; }
| Token_PlusEntier  expr_reel2 { $$ = $2; }
| Token_MoinsReel   expr_reel2 { $$ = - $2; }
| Token_MoinsEntier expr_reel2 { $$ = - $2; }
| Token_OpenPar     expr_reel  Token_ClosePar { $$ = $2; } 
;



nom:
  Token_Chaine { $$ = $1; }
| Token_Ident  { $$ = $1; }




%%

void yyerror(const char * s) {
  int a, b, c;
  a = anime_get_nb_chars();
  b = anime_get_nb_chars_tot();
  c = anime_get_yyleng();
  //(void) fprintf(stderr, "%s: Erreur d'analyse syntaxique sur le lexème \"%s\" à la ligne %d (caractères %d (%d) à %d (%d)) [%s]\n", this -> filename, anime_get_yytext(), anime_get_nb_lignes() + 1, a - c, b - c, a - 1, b - 1, s);
  //(void) fprintf(stderr, "%s:%d:%d-%d: Erreur d'analyse syntaxique sur le lexème \"%s\" [%s]\n", this -> filename, anime_get_nb_lignes() + 1, a - c, a - 1, anime_get_yytext(), s);
  anime_err("%s:%d:%d-%d: Erreur d'analyse syntaxique sur le lexème \"%s\" [%s]\n", this -> filename, anime_get_nb_lignes() + 1, a - c, a - 1, anime_get_yytext(), s);
}


void yyerror3(const char * str1, const char * str2, const char * str3) {
  size_t len, len1, len2, len3;
  char * str;
  
  len1 = strlen(str1);
  len2 = strlen(str2);
  len3 = strlen(str3);
  
  len = len1 + len2 + len3;
  
  str = (char *) malloc(len + 1);
  
  yyerror(strcat(strcat(strcpy(str, str1), str2), str3));
  
  free(str);
}

