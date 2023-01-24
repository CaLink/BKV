#include "def.h"
#include "math.h"

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

double det(POINT p1, POINT p2, POINT p3)
     			{
     				return
     				p1.x*p2.y + p3.x*p1.y + p2.x*p3.y -
     				p3.x*p2.y - p2.x*p1.y - p1.x*p3.y;
     			}
     			
int isInter(POINT p1, POINT p2, POINT p3, POINT p4)
     			{
     				if (((det(p1, p2, p3) * det(p1, p2, p4)) < 0) &&
     				((det(p3, p4, p1) * det(p3, p4, p2)) < 0))
     				return 1;
     				return 0;
     			}
     			

int simple(char *what)
{
    double S = 0;
    int N = 0;
for (int i=0; i<nobj; i++)  // найдем команду
	{
	char *a = what;
	double res = 0;
        if(strcmp(B[i].name, a) == 0)
	        {
	        switch(B[i].typ) {
	     	case Point: 
     			printf("Нельзя вычислить выпуклость точки");
     		break;
     		case Line: 
     			printf("Нельзя вычислить выпуклость линии");
     		break;
     		case Segm: 
     			printf("Нельзя вычислить выпуклость отрезка");     
     		break;
     		case Circle: 
			printf("Нельзя вычислить выпуклость круга");
     		break;
     		case Polyg: 
     			
     			

                N = (((POLYG *)(B[i].item))->n);
     			 
     			for(int j = 0; j < N; j++)
     			{
				printf("%lf \n", S);
				S += isInter(((((POLYG*)(B[i].item))->P[j])),
     				 ((((POLYG*)(B[i].item))->P[(j+1)%N])),
     				 ((((POLYG*)(B[i].item))->P[(j+2)%N])),
     				 ((((POLYG*)(B[i].item))->P[(j+3)%N])));
			}
			if(S > 0)
			{
				printf("Это не простой многоугольник");
     			}
     			else
     				printf("Это простой многоугольник");
     		break;
     		/*case Plane: 
     			printf("Нельзя вычислить площадь линии");     
     		break;
     		case Sphere: 
  			
     		break;
     		case Ball: 

     		break;
     		case Polyh: 
     		
     		break;*/
	     	}
	     	printf("\n");
		}
	
	}

}
