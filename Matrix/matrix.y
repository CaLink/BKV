%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include <dos.h>
int WE = 0;
extern char S[356];
extern char *pS;

extern int check;
extern matrix* ans;

double Val;
void init(void);
double Sqrt(double x);
int yylex();
   typedef struct matrix
           {
             char name;
             int cols;
             int rows;
             double elem[10][10];
           } matrix;
   matrix *pm[30];

double Det(matrix *);

  typedef struct Symbol
   {
    char *name; short type;
    union {
         double val;
         double (*ptr)();
         }u;
    struct Symbol *next;
  } Symbol;

Symbol *symlist =0;

static struct {
char *name;
double cval; } Const[]=
{
"PI", 3.1415926536,
"E", 2.718281828459,
"RAD",57.2958,
0,0
};

static struct {
    char *name;
   double (*func)(); }
Funcs[]=
{
"sin",sin,
"cos",cos,
"tan",tan,
"sqrt",Sqrt,
"exp",exp,
"abs",fabs,
 0,0
};

%}

%union    {
           double val;
           Symbol *sym;
           char Name;
          };
%token <Name> MAT
%token <val> NUM
%token INPUT OUTPUT DEFINE DETERM INVERSE RAND QUIT
%token <sym> VAR FUNC UNDF
%type  <val> expr assign
%type  <val> prog
%right '='
%left '+' '-'
%left '*' '/'
%right '^'
%left UNMIN
%left '@' '~'
%%
prog:  '\n'                                   { printf(">\n"); }
| expr '\n'                              { Val=$1; printf("=>%lf\n",$$);  }
| matop '\n'   {  printf("matop1\n"); fflush(stdout);      }
| defmat '\n'  {  printf ("defmat\n"); fflush(stdout); }
| prog matop '\n'   {  printf("matop2\n"); fflush(stdout);      }
| prog defmat '\n'  {  printf ("defmat\n"); fflush(stdout); }
| prog expr '\n'                         { Val=$2; printf("->%lf\n",$$);  }
| prog error '\n' {yyerrok; printf("Error!\n"); }
;
defmat: DEFINE matlist ';'
;
matelem : MAT '[' expr ']' '[' expr ']'
{{ int i,ind;
        ind=(char)$1-'a';   printf ("no=%o\n",ind); fflush(stdout);
        pm[ind]=(matrix *)malloc(sizeof(matrix));
        pm[ind]->cols=(int)$3;
        pm[ind]->rows=(int)$6;
        }}
  ;
matlist: matelem
| matelem ',' matlist
            ;

assign: VAR '=' expr                     {  $$=$1->u.val=$3; $1->type=VAR; }
;
expr:   NUM                              {  $$=$1; }
      |  VAR                             { $$= $1->u.val; }
      |  FUNC '(' expr ')'               {  $$=(($1->u.ptr)($3)); }
      |   expr '+' expr                  { $$=$1+$3; }
      |  expr '-' expr                   { $$=$1-$3; }
      |  expr '*' expr                   { $$=$1*$3; }
      |  expr '/' expr                   { if ($3!=0) $$=$1/$3;
                                          else
                            { printf(" Zero divide\n"); $$=$1; }
                                          }
      |  expr '^' expr                    { $$=pow($1,$3); }
      | '-' expr %prec UNMIN              {$$=-$2; }
      | assign
      | '(' expr ')'                      { $$=$2; }
      | QUIT {exit(0);}
      ;
matop :
    OUTPUT MAT {{int i;  int j; int ind;
        ind=(char)$2-'a';
        printf("matrix %c \n",$2);
        for(i=0;i<pm[ind]->cols;i++)
         {
           putchar( '\n');
            for(j=0; j<pm[ind]->rows; j++)
             printf("%13.5lf",pm[ind]->elem[i][j]);
           }
           putchar( '\n');
   }}
  | INPUT MAT
{{ int i,j,ind;
  ind = (char)$2-'a';

   printf("entering matrix %c ",$2);
   printf("size : %d x %d\n",pm[ind]->cols,pm[ind]->rows);
   for(i=0; i<pm[ind]->cols; i++)
        for(j=0; j<pm[ind]->rows; j++)
        {
        printf("[ %d][ %d]=",i,j);
        scanf("%lf",&pm[ind]->elem[i][j]);
        }
}}

| MAT'='MAT'+'MAT
{{int ind1,ind2,ind3;
ind1=(char)$1-'a';
ind2=(char)$3-'a';
ind3=(char)$5-'a';
if( (pm[ind1]->cols == pm[ind2]->cols) &&
    (pm[ind1]->cols == pm[ind3]->cols) &&
    (pm[ind1]->rows == pm[ind2]->rows)    )
 {
  int  i,j;
  for(i=0; i<pm[ind1]->cols; i++)
    for(j=0; j<pm[ind1]->rows; j++)
        pm[ind1]->elem[i][j] = pm[ind2]->elem[i][j] + pm[ind3]->elem[i][j];
 }
else printf("These matrixes are not equal by size\n");
}}
| MAT'='MAT'-'MAT
{{int ind1,ind2,ind3;
ind1=(char)$1-'a';
ind2=(char)$3-'a';
ind3=(char)$5-'a';
if((pm[ind1]->cols==pm[ind2]->cols)&&(pm[ind1]->cols==
         pm[ind3]->cols)&&(pm[ind1]->rows==pm[ind2]->rows))
{
int  i,j;
for(i=0;i<pm[ind1]->cols;i++)
   for(j=0;j<pm[ind1]->rows;j++)
        pm[ind1]->elem[i][j]=pm[ind2]->elem[i][j]-pm[ind3]->elem[i][j];
}
else printf("These matrixes are not equal by size\n");
}}
|MAT'='MAT'*'MAT
{{int ind1,ind2,ind3;
ind1=(char)$1-'a';
ind2=(char)$3-'a';
ind3=(char)$5-'a';
if((pm[ind1]->cols==pm[ind2]->cols)&&
(pm[ind1]->cols==pm[ind3]->rows)&&
(pm[ind1]->rows==pm[ind3]->rows))
{
int  i,j,k;
double temp=0;
for(k=0;k<pm[ind2]->cols;k++)
 for(i=0;i<pm[ind2]->rows;i++)
  for(j=0;j<pm[ind3]->rows;j++)
  {
   temp=+pm[ind2]->elem[i][j]*pm[ind3]->elem[k][j];
    pm[ind1]->elem[k][i]=temp;
    temp=0;
  }
}
else printf("These matrixes are not equal by size\n");
}}
|MAT'='MAT
{{int ind1,ind2;
ind1=(char)$1-'a';
ind2=(char)$3-'a';
if(pm[ind1] != NULL && pm[ind2] != NULL)
{
  int  i,j;
for(i=0;i<pm[ind1]->cols;i++)
   for(j=0;j<pm[ind1]->rows;j++)
        pm[ind1]->elem[i][j]=pm[ind2]->elem[i][j];
}
else yyerror("Таких матриц нет!");
}}

|RAND MAT
{{int ind;
ind = (char)$2-'a';
	{
	int i, j;
	for (i = 0; i<pm[ind]->cols; i++)
		for(j=0; j<pm[ind]->rows; j++)
			pm[ind]->elem[i][j]=rand()%1000;
	}
}}
|VAR'=' DETERM '('MAT')'
{{
  int ind;
  float num;
  ind=(char)$5-'a';
  num=$1->u.val;

  if(pm[ind]->rows==pm[ind]->cols)
  {
    num=Det(pm[ind]);
    printf("\ndet=%lf\n",num);
    $1->u.val=num;
  }
  else printf("This matrix isn't square\n");
}}	

|VAR'=''@''('MAT')'
{{
  int ind;
  float num;
  ind=(char)$5-'a';
  num=$1->u.val;

  if(pm[ind]->rows==pm[ind]->cols)
  {
    num=Det(pm[ind]);
    printf("\ndet=%lf\n",num);
    $1->u.val=num;
  }
  else printf("This matrix isn't square\n");
}}
|MAT'=' INVERSE '('MAT')'
{{int ind1,ind2;
  float det=0;
  int row,col,i,j;

ind1=(char)$1-'a';
ind2=(char)$5-'a';
if((pm[ind1]->cols==pm[ind1]->rows)&&(pm[ind2]->rows==pm[ind2]->cols))
  if((pm[ind1]->cols==pm[ind2]->cols)&&(pm[ind1]->rows==pm[ind2]->rows))
  {

        inverse(pm[ind2],pm[ind1]);

  }
  else printf("These matrixes are not equal by size\n");
else printf("These matrixes are not square\n");
}}
|MAT'=''~''('MAT')'
{{int ind1,ind2;
  float det=0;
  int row,col,i,j;

ind1=(char)$1-'a';
ind2=(char)$5-'a';
if((pm[ind1]->cols==pm[ind1]->rows)&&(pm[ind2]->rows==pm[ind2]->cols))
  if((pm[ind1]->cols==pm[ind2]->cols)&&(pm[ind1]->rows==pm[ind2]->rows))
  {

        inverse(pm[ind2],pm[ind1]);

  }
  else printf("These matrixes are not equal by size\n");
else printf("These matrixes are not square\n");
}}
|MAT'='MAT'*'expr
{{int ind1,ind2;
double dig;
dig=$5;
ind1=(char)$1-'a';
ind2=(char)$3-'a';
if((pm[ind1]->cols==pm[ind2]->cols)&&(pm[ind1]->rows==pm[ind2]->rows))
{
  int  i,j;
  for(i=0;i<pm[ind1]->cols;i++)
   for(j=0;j<pm[ind1]->rows;j++)
        pm[ind1]->elem[i][j]=dig*pm[ind2]->elem[i][j];

}
else printf("These matrixes are not equal by size\n");

}}
|
MAT'='MAT'/'expr
{{
int ind1,ind2;
double dig;
dig=$5;
ind1=(char)$1-'a';
ind2=(char)$3-'a';
if((pm[ind1]->cols==pm[ind2]->cols)&&(pm[ind1]->rows==pm[ind2]->rows))
{
  int  i,j;
  for(i=0;i<pm[ind1]->cols;i++)
   for(j=0;j<pm[ind1]->rows;j++)
        pm[ind1]->elem[i][j]=dig*pm[ind2]->elem[i][j];
}
else yyerror("Такой матрицы нет");
}}
;

%%
matrix *reduce(int row,int column, matrix *pm)
{
  matrix *reduced;
  int i,y, x, rc, rr,ind2,ind1;
  rc=rr=0;
  reduced=(matrix *)malloc(sizeof(matrix));

  reduced->rows = reduced->cols = pm->rows-1;

  for ( x=0 ; x<pm->rows ; x++)
  {
    for ( y=0, rc=0 ; y<pm->cols; y++)
           if( x==row || y==column);
           else
           {
              reduced->elem[rr][rc] = pm->elem[x][y];
              rc++;
           }

    if ( x!=row && y!=column)
         rr++;
  }

  return reduced;
}
//////////////
double Det(matrix *Matrix)
{
  double det=0;
  matrix *tmp;
  int i,j,k, sign=1;

  if (Matrix->rows == 1)
    return Matrix->elem[0][0];

  if (Matrix->rows == 2)
    return Matrix->elem[0][0]*Matrix->elem[1][1] -
                Matrix->elem[0][1]*Matrix->elem[1][0];

  else {
    for ( i=0 ; i < Matrix->rows ; i++, sign*=-1 )
    {
      tmp = reduce(0,i,Matrix);
      det+= sign * Matrix->elem[0][i]*Det(tmp);
      free(tmp);
    }
   return det;
  }
}
/////////////////////////////
void scalar_mult ( matrix *pm, float scalar )
{
  int row, col;

  for ( row=0 ; row < pm->rows ; row++ )
  {
    for ( col=0 ; col < pm->cols ; col++ )
    {
      pm->elem[row][col] *=1/scalar;
    }
  }
}

void inverse ( matrix *pm,matrix *inverse)
{
  float det=0;
  int row, col;


  det = Det(pm);
  printf("\ndet=%lf\n",det);
  if ( det != 0)
  {
     for ( row=0; row<pm->rows; row++ )
     {
      for ( col=0; col<pm->cols; col++ )
      {
        inverse->elem[row][col] = Det(reduce(row,col,pm));
      }
     }
   /*
    for ( row=0; row<inverse->rows; row++ )
    {
      for (col=0; col<inverse->cols; col++ )
      {
        inverse->elem[row][col] *=(int)pow(-1,row+col);
      }
    }
   */
    scalar_mult(inverse,det);
  }

}

Symbol *install(char *s, short t, double d)
{
  Symbol *sp;
   sp=(Symbol *) malloc(sizeof(Symbol));
   sp->name=(char *)malloc(strlen(s)+1);
   strcpy(sp->name,s);
   sp->type=t; sp->u.val=d; sp->next=symlist;
   symlist=sp;
   return sp;
}

Symbol *lookup(char *s)
{
  Symbol *sp;
  for (sp=symlist; sp!=(Symbol *)0; sp=sp->next)
    if (strcmp(sp->name,s)==0)
    {
      return sp;
    }
    return 0;
}

void init(void)
{
  int i; Symbol *s;

   for(i=0; Const[i].name; i++)
   install(Const[i].name,VAR,Const[i].cval);
   for(i=0; Funcs[i].name; i++)
   {
    s=install(Funcs[i].name,FUNC,0.0); 
    s->u.ptr=Funcs[i].func;
   };
}

int yylex()
{

  char c;
  Symbol *s;
  static  char sbuf[100], *p;
    p=sbuf;
//printf("bp0\n"); fflush(stdout);
  while(((c=*pS++)==' '));
 if (c==EOF) return 0;
 if(c=='#')
 {
     c=*pS++;
     yylval.Name=c;
     return MAT;
 }
//printf("bp1\n"); fflush(stdout);
 if(isalpha(c))
 {
     do
      { *p++=c; 
//printf("bp2 %c\n",c); fflush(stdout);
}
     while (((c=*pS++)!=EOF) && isalnum(c)) ;
   pS--; *p='\0';
   printf("ALPHA=%s\n",sbuf); fflush(stdout);
     if(strncmp(sbuf,"define", 3)==0||strncmp(sbuf,"DEFINE", 3)==0)
      return DEFINE;
     if(strncmp(sbuf,"determ", 3)==0||strncmp(sbuf,"DETERM", 3)==0)
      return DETERM;
     if(strncmp(sbuf,"inverse", 3)==0||strncmp(sbuf,"INVERSE", 3)==0)
      return INVERSE;
     if(strncmp(sbuf,"input", 2)==0||strncmp(sbuf,"INPUT", 2)==0)
      return INPUT;
     if(strncmp(sbuf,"output", 3)==0||strncmp(sbuf,"OUTPUT", 3)==0)
      return OUTPUT; 
     if(strncmp(sbuf,"quit", 3)==0||strncmp(sbuf,"QUIT", 3)==0)
      return QUIT; 
     if(strncmp(sbuf,"random", 3)==0||strncmp(sbuf,"RANDOM", 3)==0)
      return RAND;
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

double Sqrt(double x)
{
 if (x<0.0)
            {
              yyerror(" Sqrt from negative number. "); return (0.0);
            };
 return sqrt(x);
}

yyerror(char *s)
 {
   printf("Error: %s\n",s);
   printf("Error: %s\n",S);
   printf("Error: %s\n",pS);
 }
/*
int main()
 {
for(int i=0; i<30; i++)
	pm[i] = NULL;
    init();
    yyparse();
    free(pm);
    return 0;
 }

*/
