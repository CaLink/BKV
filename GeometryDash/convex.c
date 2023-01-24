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


double ugol(POINT p1, POINT p2, POINT p3)
     			{
				//printf("точки %lf %lf %lf %lf %lf %lf", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
     				//printf("cr %lf \n",sqrt((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y)));
     			//	printf("cr2 %lf \n",sqrt((p3.x-p1.x)*(p3.x-p1.x) + (p3.y-p1.y)*(p3.y-p1.y)));
     				return
     				((p2.x-p1.x)*(p3.x-p1.x) + (p2.y-p1.y)*(p3.y-p1.y))/
     				(sqrt((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y)) *
     				sqrt((p3.x-p1.x)*(p3.x-p1.x) + (p3.y-p1.y)*(p3.y-p1.y)));
     			}
     			
int convex(char *what)
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

				S = ugol(((((POLYG*)(B[i].item))->P[j])),
     				 ((((POLYG*)(B[i].item))->P[(j+1)%N])),
     				 ((((POLYG*)(B[i].item))->P[(j+(N-1))%N])));
     				//printf("S %lf \nS2 %lf \n", S, ((acos(S)*180)/3.14));
     				//if(((acos(S)*180)/3.14) > 180)
     				if(S<0)
     				{
     					//printf("%lf \n", S);
					break;
				}
			}
			if(S < 0)
				printf("Это не выпуклый многоугольник");
			else	
				printf("Это выпуклый многоугольник");
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
