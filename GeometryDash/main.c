#include "def.h"

char s[256], *lex[128]; int nlex;
OBJECT B[Nmax]; int nobj=0;
char *LEXOBJ[]= { "point","line","segment","circle","polygon","polyhedron","plane","sphere","ball","set"};
short MINOBJ[]= {  3,      3,     4,        4,       5,         5,           4,      3,       4,     3};
short MAXOBJ[]= {  5,      4,     7,        6,       7,        10,           5,      6,       4,     3};
short NOBJ=10;
char *LEXCMD[]={ "exit", "help","define","read", "is","convex", "area","volume","centroid","add", "simple"  };
short MINCMD[]= { 2,      1,     3,       2,      2,   4,        4,     3,       5,         3,     3};
short MAXCMD[]= { 4,      4,     6,       4,      2,   6,        4,     6,       8,         3,     6};
short NCMD=11;

int StrCmp(char *lex, char *full, int Min, int Max)
{   int n=strlen(lex);
	if ( n > Max) return 0;
	if ( n < Min) return 0;
	if (strncmp( lex, full, n)==0) return 1;
	return 0;
}

int main(int argc, char **argv)
{
#ifdef DEBUG
           //  printf("Всего  OBJ=%d объектов ;  CMD=%d команд\n",
		//	     sizeof(MINOBJ)/sizeof(short),sizeof(MINCMD)/sizeof(short));
	 //    printf("Включен режим отладки\n");
#endif
 int i;
	while(1)
	{
		fgets( s,256,stdin); nlex=0;
		while(1)
		{
			if(nlex==0)
		     lex[nlex++]=strtok(s," (),[]\n\r");
			else
		     lex[nlex++]=strtok(NULL," (),[]\n\r");
		     if(lex[nlex-1]==NULL) break;
#ifdef DEBUG
            // printf("[%d %s]  ",nlex-1,lex[nlex-1]);
#endif
       }
       putchar('\n');
       for ( i=0; i<NCMD; i++)  // найдем команду
         {
			  if (StrCmp(lex[0],LEXCMD[i],MINCMD[i],MAXCMD[i]))
			  {
#ifdef DEBUG
			 //  printf("найдена команда %s \n",LEXCMD[i]);
#endif
        switch(i) {
		case Exit: finish();   break;
		case Help: 
			   if (lex[0] = Help) usage();
			   // (nlex=0) usage();
                           else topic(lex[1]); 
			    break;
		case Define: 
		  add();
		  break;
		case Read:
		read();
	       	  break;
		case Is: 
			if (nlex=0) usage();
			else is(lex[1], lex[2]); 
		  break;
		case Convex:
			if (nlex=0) usage();
			else convex(lex[1]); 
	       	  break;
		case Area: 
		      	if (nlex=0) usage();
			else area(lex[1]); 
		  break;
		 case Simple:
		 	if (nlex=0) usage();
			else simple(lex[1]); 
		 break;
		/*case Volume:
		 	if (nlex=0) usage();
			else volume(lex[1]); 
		  break;
		case Centr:
	       	  break;*/
                default:
			   printf("Не найдена команда %s \n",lex[0]);

		        }
              break;
		      }
		 }
		 			if (i==NCMD)   printf("Не распознана команда %s \n",lex[0]);

              
	}
	return 0;
}
