%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
const double PI=M_PI;

int WE=0;

extern char S[256];
char *pS=S;

double Val;

int yylex();
double Sqrt(double x);
double fact(double x);
double arcsin(double x);
double arccos(double x);
typedef struct Symbol 
	{
	char *name; short type;
	union	{
		double val;
		double (*ptr)();
		}u;
	struct Symbol *next;
	} Symbol;
Symbol *symlist=0;
static struct {
char *name;
double cval; } Const[]=
{
"PI", 3.1415926536,
"E", 2.718281828459,
"RAD",57.2958,
0,0
};
static struct	{
		char *name;
		double (*func)();
		}
Funcs[]={
"sin",sin,
"cos",cos,
"tan",tan,
"arcsin",arcsin,
"arccos",arccos,
"arctan",atan,
"sqrt",Sqrt,
"Log",log,
"Lg",log10,
"exp", exp,
"J0",j0,
"J1",j1,
"Jn",jn,
"Y0",y0,
"Y1",y1,
"Yn",yn,
"!",fact,
"abs",fabs,
 0,0
	};
%}

%union	{
	double val;
	Symbol *sym;
	};

%token <val> NUM
%token <sym> VAR FUNC FUNC2 UNDF 
%type  <val> expr assign
%type  <val> prog 
%right '='
%left  '+' '-'
%left  '*' '/'
%right '^'
%left UNMIN
%left '!'

%%
prog:
{pS=S;/*printf (" >>parser!<< ");*/}
| prog '\n'        {  Val=$1; /* printf("%lf\n",Val); */  getchar(); /*WE=0;*/}
| prog expr '\n'   {  Val=$2; /* printf("%lf\n",Val); */ /*WE=0;*/}
| prog error '\n'  {  yyerrok; printf("\007\n") ;}
; 
assign: VAR '=' expr        {  $$ = $1->u.val=$3; $1->type=VAR; }
;
expr:    NUM                {  $$ = $1; }
      |  VAR                { $$ = $1->u.val; }
      |  FUNC '(' expr ')'  {  $$ = (($1->u.ptr)($3)); }
      |  FUNC2 '(' expr ',' expr ')'  { $$ = (($1->u.ptr)((int)$3,$5)); }
      |  expr '+' expr      { $$ = $1+$3; }
      |  expr '-' expr      { $$ = $1 - $3; }
      |  expr '*' expr      { $$ = $1*$3; }
      |  expr '/' expr      { if ($3!=0) $$ = $1/$3; 
                              else { WE=1; yyerror(" Деление на 0 "); $$=$1; }
                            }
      |  expr '^' expr      { $$ = pow($1,$3); }
      |  '-' expr %prec UNMIN { $$ = -$2; }
      |  assign
      |  '(' expr ')'       { $$ = $2; }
      | expr '!' {$$=fact($1);}
      ;
%%

Symbol *install(char *s, short t, double d)
{
Symbol *sp;
sp = (Symbol *) malloc(sizeof(Symbol));
sp->name = (char *)malloc(strlen(s)+1);    
strcpy(sp->name,s); 
sp->type = t; sp->u.val=d; sp->next=symlist;
symlist=sp; 
return sp;
}

Symbol *lookup(char *s)
{
Symbol *sp;
for (sp=symlist; sp!=(Symbol *)0; sp=sp->next)
	if (strcmp(sp->name,s)==0) 
		{return sp;}
return 0;
}

/*********** INIT ***********/
init()
{
	int i; Symbol *s;
for(i=0; Const[i].name; i++)
    install(Const[i].name,VAR,Const[i].cval);
for(i=0; Funcs[i].name; i++)
	{
        if((strcmp(Funcs[i].name,"Jn")==0) || (strcmp(Funcs[i].name,"Yn")==0))
        {
            s=install(Funcs[i].name,FUNC2,0.0);
            s->u.ptr=Funcs[i].func;
        }
        else
        {

        s=install(Funcs[i].name,FUNC,0.0);
        s->u.ptr=Funcs[i].func;
        };
    }
}

/*********** YYPARSE вызывает YYLEX ***********/
int yylex()
{
   char c;
   Symbol *s;
   char sbuf[100], *p=sbuf; 
   double buf;

while((c=*pS++)==' ');

if (c==EOF) {pS=S;printf("EOF");return 0; };
if(isalpha(c))
{
	do { *p++=c; } 

   while (((c=*pS++)!=EOF) && isalnum(c));
   pS--; *p='\0';
   if ((s=lookup(sbuf))==0)
	s=install(sbuf,UNDF,0.0);
   yylval.sym=s;
   return ((s->type==UNDF) ? VAR : s->type); 
}

if (c=='.' || isdigit(c))
	{ 
	pS--;
	sscanf(pS,"%lf",&yylval);
	while(*pS=='.' || isdigit(*pS)) pS++;
	return NUM; 
	};
return c; 
}

double Sqrt(double x) {
if (x<0.0) { yyerror(" Квадратный корень из отрицательного числа "); return (0.0); };
return sqrt(x);
}
double arcsin(double x) {
if (x<=-1 || x>=1) { yyerror("Аргумент для arcsin должен быть в диапазоне [-1;1] "); return (0.0);}
return asin(x);
}

double arccos(double x) {
if (x<=-1 || x>=1) { yyerror("Аргумент для arccos должен быть в диапазоне [-1;1] "); return (0.0);}
return acos(x);
}


double fact(double x) {
   if(x<=0) return 1;
   return x*fact(x-1);
}

/*********** YYERROR ***********/
yyerror(char *s)
 {
   printf("Ошибка: %s\n",s); WE=1;
 }


