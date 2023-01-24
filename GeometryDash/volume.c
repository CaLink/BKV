#include "def.h"

extern char *LEXOBJ[];
extern short MINOBJ[];
extern short MAXOBJ[];
extern short NOBJ;
extern char *LEXCMD[];
extern short MINCMD[];
extern short MAXCMD[];
extern short NCMD;
extern OBJECT B[Nmax]; extern int nobj;
extern char *lex[];

int volume(char *what)
{
for (int i=0; i<nobj; i++)  // найдем команду
	{
	char *a = what;
        if(strcmp(B[i].name, a) == 0)
	        {
	        switch(B[i].typ) {
	     	case Point: 
     			printf("Нельзя найти объём точки \n");
     		break;
     		case Line: 
     			printf("Нельзя найти объём линии \n");
     		break;
     		case Segm: 
     			printf("Нельзя найти объём линии \n");
     		break;
     		case Circle: 
     		     	printf("Нельзя найти объём линии \n");
     		break;
     		case Polyg: 
     		     	printf("Нельзя найти объём линии \n");
     		break;
     		case Plane: 
     		     	printf("Нельзя найти объём линии \n");
     		break;
     /*		case Sphere: 
     		     	printf("Нельзя найти объём линии \n");     			
     		break;
     		case Ball: 
     			double res = (((BALL *)(B[i].item))->R)*(((BALL *)(B[i].item))->R)*(((BALL *)(B[i].item))->R)*(4/3)*3.14;
     			printf("Объём шара = %lf",
     			res);
     		break;
     		case Polyh: 
     		
     		break;*/
	     			}

		}
	
	}

}
