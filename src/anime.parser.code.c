#include <stdlib.h>
#include <string.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
#define yyparse yyanimeparse
#define yylex yyanimelex
#define yyerror yyanimeerror
#define yychar yyanimechar
#define yyval yyanimeval
#define yylval yyanimelval
#define yydebug yyanimedebug
#define yynerrs yyanimenerrs
#define yyerrflag yyanimeerrflag
#define yyss yyanimess
#define yysslim yyanimesslim
#define yyssp yyanimessp
#define yyvs yyanimevs
#define yyvsp yyanimevsp
#define yystacksize yyanimestacksize
#define yylhs yyanimelhs
#define yylen yyanimelen
#define yydefred yyanimedefred
#define yydgoto yyanimedgoto
#define yysindex yyanimesindex
#define yyrindex yyanimerindex
#define yygindex yyanimegindex
#define yytable yyanimetable
#define yycheck yyanimecheck
#define yyname yyanimename
#define yyrule yyanimerule
#define YYPREFIX "yyanime"
#line 1 "src/anime.parser.y"
 /* Header */
#include <stdlib.h>
#include <stdio.h>
#include "anime.h"
#include "anime.global.h"
#include "anime.parser.tab.h"
/*#include "action.hpp"*/

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



#line 83 "src/anime.parser.y"
#ifndef YYSTYPE_DEFINED
#define YYSTYPE_DEFINED
typedef union {
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
} YYSTYPE;
#endif /* YYSTYPE_DEFINED */
#line 137 "src/anime.parser.code.c"
#define Token_Booleen 257
#define Token_Entier 258
#define Token_Reel 259
#define Token_Chaine 260
#define Token_Ident 261
#define Token_LAction 262
#define Token_OpenPar 263
#define Token_OpenBrace 264
#define Token_OpenBracket 265
#define Token_ClosePar 266
#define Token_CloseBrace 267
#define Token_CloseBracket 268
#define Token_Ptvirg 269
#define Token_Virgule 270
#define Token_EOF 271
#define Token_Zone 272
#define Token_Choc 273
#define Token_Masse 274
#define Token_Invincible 275
#define Token_Membres 276
#define Token_Racines 277
#define Token_Action 278
#define Token_Menu 279
#define Token_Affichage 280
#define Token_Gestionnaire 281
#define Token_Evenement 282
#define Token_Genere 283
#define Token_Par 284
#define Token_Traitement 285
#define Token_Membre 286
#define Token_Fils 287
#define Token_Angle 288
#define Token_Max 289
#define Token_Qui 290
#define Token_X 291
#define Token_Y 292
#define Token_Z 293
#define Token_Tous 294
#define Token_Aucun 295
#define Token_Image 296
#define Token_Points 297
#define Token_De 298
#define Token_Vie 299
#define Token_Hostile 300
#define Token_Largeur 301
#define Token_Longueur 302
#define Token_Hauteur 303
#define Token_Physique 304
#define Token_Gameplay 305
#define Token_Graphique 306
#define Token_Fichier 307
#define Token_Procedure 308
#define Token_Icone 309
#define Token_Assign 310
#define Token_PlusEntier 311
#define Token_MoinsEntier 312
#define Token_MultEntier 313
#define Token_DivEntier 314
#define Token_ModEntier 315
#define Token_PlusReel 316
#define Token_MoinsReel 317
#define Token_MultReel 318
#define Token_DivReel 319
#define YYERRCODE 256
#define YYTABLESIZE 336
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 319
extern const short yylhs[];
extern const short yylen[];
extern const short yydefred[];
extern const short yydgoto[];
extern const short yysindex[];
extern const short yyrindex[];
extern const short yygindex[];
extern const short yytable[];
extern const short yycheck[];
#if YYDEBUG
extern const char *const yyname[];
extern const char *const yyrule[];
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
/* LINTUSED */
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
unsigned int yystacksize;
int yyparse(void);
#line 549 "src/anime.parser.y"


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

#line 278 "src/anime.parser.code.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    unsigned int newsize;
    long sslen;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    sslen = yyssp - yyss;
#ifdef SIZE_MAX
#define YY_SIZE_MAX SIZE_MAX
#else
#define YY_SIZE_MAX 0xffffffffU
#endif
    if (newsize && YY_SIZE_MAX / newsize < sizeof *newss)
        goto bail;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss); /* overflow check above */
    if (newss == NULL)
        goto bail;
    yyss = newss;
    yyssp = newss + sslen;
    if (newsize && YY_SIZE_MAX / newsize < sizeof *newvs)
        goto bail;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs); /* overflow check above */
    if (newvs == NULL)
        goto bail;
    yyvs = newvs;
    yyvsp = newvs + sslen;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
bail:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return -1;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif /* YYDEBUG */

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 200 "src/anime.parser.y"
{
  return 0;
}
break;
case 2:
#line 213 "src/anime.parser.y"
{
#if 1
  this -> choc_longueur = yyvsp[-16].yyreel; 
  this -> choc_largeur = yyvsp[-12].yyreel; 
  this -> choc_hauteur = yyvsp[-8].yyreel; 
  this -> masse = yyvsp[-2].yyreel; 
#else 
  bongars -> SetDimension(yyvsp[-16].yyreel, yyvsp[-12].yyreel, yyvsp[-8].yyreel);
#endif 
}
break;
case 3:
#line 232 "src/anime.parser.y"
{
#if 1
  this -> vie        =  yyvsp[-12].yyentier; 
  this -> invincible = yyvsp[-8].yybooleen; 
  this -> hostile    = yyvsp[-4].yybooleen; 
#else 
  bongars->Hostile = yyvsp[-4].yybooleen;
#endif 
}
break;
case 4:
#line 247 "src/anime.parser.y"
{
#if 1 
  /* Do nothing */
#else
  anime_filsdesc * temp;
  while (yyvsp[-2].yyliste != NULL) {
    int j;
    temp = (anime_filsdesc *) yyvsp[-2].yyliste->contenu;

    if ((j = memlookup(temp -> qui)) < 0) {
      yyerror3("Le membre \"", temp -> qui, "\" n'a pas ete defini. On continue néanmoins.\n");
    }
    
    else {
      bongars -> AjouterMembre(memtab[j].image, temp -> x, temp -> y, temp -> z, memtab[j].largeur, memtab[j].hauteur, memtab[j].angle_max_y);
      memempiler(bongars, memtab[j].fils);
    }
    yyvsp[-2].yyliste = yyvsp[-2].yyliste -> suivant;
  }
#endif 
}
break;
case 7:
#line 281 "src/anime.parser.y"
{
#if 1 
  anime__actions_push(this, yyvsp[-14].yynom, /*affichage*/yyvsp[-10].yychaine, /*icone*/yyvsp[-6].yychaine, /*gestionnaire_fichier*/this -> temp_code_fichier, /*gestionnaire_proc*/this -> temp_code_proc);  
#else 
  bongars->AjouterAction(yyvsp[-10].yychaine, yyvsp[-6].yychaine, yyvsp[-2].yycode->fichier, yyvsp[-2].yycode->proc);
  anime_del_code(&(yyvsp[-2].yycode));
#endif 
}
break;
case 8:
#line 291 "src/anime.parser.y"
{
#if 0 
yyval.yyliste = mp(yyvsp[0].yyliste, yyvsp[-1].yyevent); VERIF_NOT_NULL(yyval.yyliste,-8); 
#endif 
}
break;
case 9:
#line 296 "src/anime.parser.y"
{
#if 0 
yyval.yyliste = liste_vide();
#endif 
}
break;
case 10:
#line 308 "src/anime.parser.y"
{
#if 1
  anime__events_push(this, /*events_nom*/yyvsp[-11].yynom, 
    /*events_genere_type*/this -> temp_events_genere_type, /*events_genere_code_fichier*/this -> temp_events_genere_code_fichier, /*events_genere_code_proc*/this -> temp_events_genere_code_proc, 
    /*events_traitement_fichier*/this -> temp_events_traitement_code_fichier, /*events_traitement_proc*/this -> temp_events_traitement_code_proc);  

#else 
  yyval.yyevent = anime_new_event();
  VERIF_NOT_NULL(yyval.yyevent,-9)

  yyval.yyevent->genere = yyvsp[-6].yygenere->type;
  if (yyvsp[-6].yygenere->type == CODE) {
    yyval.yyevent->par = (anime_tcode *)NULL;
  }

  else {
    yyval.yyevent->par = yyvsp[-6].yygenere->code;
  }

  anime_del_sgenere(yyvsp[-6].yygenere);
  yyval.yyevent->traitement = yyvsp[-2].yycode;
#endif 
}
break;
case 11:
#line 335 "src/anime.parser.y"
{ 
#if 0 
yyval.yyliste = mp(yyvsp[0].yyliste, yyvsp[-1].yymembre); VERIF_NOT_NULL(yyval.yyliste,-10); 
#endif 
}
break;
case 12:
#line 340 "src/anime.parser.y"
{
#if 0 
yyval.yyliste = liste_vide();
#endif 
}
break;
case 13:
#line 355 "src/anime.parser.y"
{
#if 1
  anime__membres_push(this, yyvsp[-24].yynom, yyvsp[-16].yychaine, /*largeur*/yyvsp[-12].yyreel, /*hauteur*/yyvsp[-8].yyreel, /*angle_max_y*/yyvsp[-2].yyreel); 
#else
  if (memnbelts < MAXMEMBRE) {
    memtab[memnbelts].nom = yyvsp[-24].yynom;
    memtab[memnbelts].image = yyvsp[-16].yychaine;
    memtab[memnbelts].fils = yyvsp[-20].yyliste;
    memtab[memnbelts].largeur = yyvsp[-12].yyreel;
    memtab[memnbelts].hauteur = yyvsp[-8].yyreel;
    memtab[memnbelts].angle_max_y = yyvsp[-2].yyreel;
    memnbelts++;
  }
#endif 
}
break;
case 14:
#line 372 "src/anime.parser.y"
{
}
break;
case 15:
#line 374 "src/anime.parser.y"
{
}
break;
case 16:
#line 385 "src/anime.parser.y"
{
#if 1
  anime__racines_push(this, /*qui*/yyvsp[-19].yynom, /*x*/yyvsp[-15].yyreel, /*y*/yyvsp[-11].yyreel, /*z*/yyvsp[-7].yyreel, /*angle_y*/yyvsp[-2].yyreel); 
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
}
break;
case 17:
#line 405 "src/anime.parser.y"
{
#if 0 
yyval.yyliste = mp(yyvsp[-1].yyfils, yyvsp[-2].yyliste); VERIF_NOT_NULL(yyval.yyliste,-12);
#endif 
}
break;
case 18:
#line 410 "src/anime.parser.y"
{
#if 0 
yyval.yyliste = liste_vide();
#endif 
}
break;
case 19:
#line 425 "src/anime.parser.y"
{
#if 1
#else 
  yyval.yyfils = new anime_filsdesc;
  yyval.yyfils->qui = yyvsp[-19].yyident;
  yyval.yyfils->x = yyvsp[-15].yyreel;
  yyval.yyfils->y = yyvsp[-11].yyreel;
  yyval.yyfils->z = yyvsp[-7].yyreel;
  yyval.yyfils->angle_y = yyvsp[-2].yyreel;
#endif 
}
break;
case 22:
#line 445 "src/anime.parser.y"
{
#if 1 
    this -> temp_events_genere_type         = ANIME_EVENTS_AUCUN; 
    this -> temp_events_genere_code_fichier = NULL; 
    this -> temp_events_genere_code_proc    = NULL; 
#else 
    yyval.yygenere = anime_new_sgenere(); VERIF_NOT_NULL(yyval.yygenere,-14); yyval.yygenere->type = AUCUN; yyval.yygenere->code = NULL;
#endif 
}
break;
case 23:
#line 454 "src/anime.parser.y"
{
#if 1
  this -> temp_events_genere_type         = ANIME_EVENTS_TOUS; 
  this -> temp_events_genere_code_fichier = NULL; 
  this -> temp_events_genere_code_proc    = NULL; 
#else 
  yyval.yygenere = anime_new_sgenere(); VERIF_NOT_NULL(yyval.yygenere,-15); yyval.yygenere->type = TOUS; yyval.yygenere->code = NULL;
#endif 
}
break;
case 24:
#line 463 "src/anime.parser.y"
{
#if 1
  this -> temp_events_genere_type         = ANIME_EVENTS_CODE; 
  this -> temp_events_genere_code_fichier = this -> temp_code_fichier; 
  this -> temp_events_genere_code_proc    = this -> temp_code_fichier; 
#else 
  yyval.yygenere = anime_new_sgenere(); VERIF_NOT_NULL(yyval.yygenere,-16); yyval.yygenere->type = CODE; yyval.yygenere->code = yyvsp[0].yycode;
#endif 
}
break;
case 25:
#line 479 "src/anime.parser.y"
{ 
#if 1 
  this -> temp_code_fichier = yyvsp[-6].yychaine;
  this -> temp_code_proc = yyvsp[-2].yychaine; 
#else 
  yyval.yycode = anime_new_code(); yyval.yycode->fichier = yyvsp[-6].yychaine; yyval.yycode->proc = yyvsp[-2].yychaine; 
#endif 
}
break;
case 26:
#line 492 "src/anime.parser.y"
{ yyval.yyentier = yyvsp[-2].yyentier + yyvsp[0].yyentier; }
break;
case 27:
#line 493 "src/anime.parser.y"
{ yyval.yyentier = yyvsp[-2].yyentier - yyvsp[0].yyentier; }
break;
case 28:
#line 494 "src/anime.parser.y"
{ yyval.yyentier= yyvsp[0].yyentier; }
break;
case 29:
#line 498 "src/anime.parser.y"
{ yyval.yyentier = yyvsp[-2].yyentier * yyvsp[0].yyentier; }
break;
case 30:
#line 499 "src/anime.parser.y"
{ yyval.yyentier = yyvsp[-2].yyentier / yyvsp[0].yyentier; }
break;
case 31:
#line 500 "src/anime.parser.y"
{ yyval.yyentier = yyvsp[-2].yyentier % yyvsp[0].yyentier; }
break;
case 32:
#line 501 "src/anime.parser.y"
{ yyval.yyentier = yyvsp[0].yyentier; }
break;
case 33:
#line 505 "src/anime.parser.y"
{ yyval.yyentier = yyvsp[0].yyentier; }
break;
case 34:
#line 506 "src/anime.parser.y"
{ yyval.yyentier = yyvsp[0].yyentier; }
break;
case 35:
#line 507 "src/anime.parser.y"
{ yyval.yyentier = - yyvsp[0].yyentier; }
break;
case 36:
#line 508 "src/anime.parser.y"
{ yyval.yyentier = yyvsp[-1].yyentier; }
break;
case 37:
#line 515 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel + yyvsp[0].yyreel; }
break;
case 38:
#line 516 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel + yyvsp[0].yyreel; }
break;
case 39:
#line 517 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel - yyvsp[0].yyreel; }
break;
case 40:
#line 518 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel - yyvsp[0].yyreel; }
break;
case 41:
#line 519 "src/anime.parser.y"
{ yyval.yyreel= yyvsp[0].yyreel; }
break;
case 42:
#line 523 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel * yyvsp[0].yyreel; }
break;
case 43:
#line 524 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel * yyvsp[0].yyreel; }
break;
case 44:
#line 525 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel / yyvsp[0].yyreel; }
break;
case 45:
#line 526 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel / yyvsp[0].yyreel; }
break;
case 46:
#line 527 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[0].yyreel; }
break;
case 47:
#line 531 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[0].yyreel; }
break;
case 48:
#line 532 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[0].yyentier; }
break;
case 49:
#line 533 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[0].yyreel; }
break;
case 50:
#line 534 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[0].yyreel; }
break;
case 51:
#line 535 "src/anime.parser.y"
{ yyval.yyreel = - yyvsp[0].yyreel; }
break;
case 52:
#line 536 "src/anime.parser.y"
{ yyval.yyreel = - yyvsp[0].yyreel; }
break;
case 53:
#line 537 "src/anime.parser.y"
{ yyval.yyreel = yyvsp[-1].yyreel; }
break;
case 54:
#line 543 "src/anime.parser.y"
{ yyval.yynom = yyvsp[0].yychaine; }
break;
case 55:
#line 544 "src/anime.parser.y"
{ yyval.yynom = yyvsp[0].yyident; }
break;
#line 838 "src/anime.parser.code.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return (1);
yyaccept:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return (0);
}
