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
extern YYSTYPE yyanimelval;
