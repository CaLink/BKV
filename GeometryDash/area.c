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

double dist(POINT p1, POINT p2)
				{
					double t;
					return (
					( (t=(p1.x-p2.x))*t) +
					( (t=(p1.y-p2.y))*t) );
				}
double sqwe(POINT p1, POINT p2)
     			 {
     			 	//printf("%lf fewfs f \n", p2.x);
     			 	//printf("%lf \n", p2.y);
	     			//printf("%lf \n", p1.x);
     			 //	printf("%lf \n", p1.y);
     			 	return(((p2.x - p1.x)*(p2.y+p1.y))/2);
     			 }


int area(char *what)
{
    int N;	double S = 0;
for (int i=0; i<nobj; i++)  // найдем команду
	{
	char *a = what;
	double res = 0;
        if(strcmp(B[i].name, a) == 0)
	        {
	        switch(B[i].typ) {
	     	case Point: 
     			printf("Нельзя вычислить площадь точки");
     		break;
     		case Line: 
     			printf("Нельзя вычислить площадь линии");
     		break;
     		case Segm: 
     			printf("Нельзя вычислить площадь отрезка");     
     		break;
     		case Circle: 
			res = (((CIRCLE *)(B[i].item))->R)*(((CIRCLE *)(B[i].item))->R)*3.14;
     			printf("Площадь круга = %lf",
     			res);
     		break;
     		case Polyg: 
     		
     			N = (((POLYG *)(B[i].item))->n);
     			//printf("%d", 
     			//(((POLYG *)(B[i].item))->n));
     		      /*  for(int j = 0; j< N; j++)
     			{
     				S += dist(((((POLYG*)(B[i].item))->P[j])),
     				 ((((POLYG*)(B[i].item))->P[(j+1)%N])));
     			 }*/
     			 
     			for(int j = 0; j < N; j++)
     			{
     			       // printf("%lf", ((((POLYG *)(B[i].item))->P[(j+1)%N]).x));
				/*S += ( ( ( (((POLYG*)(B[i].item))->P[(j+1)%N]).x) -
				((((POLYG*)(B[i].item))->P[j]).x)) *
				(((((POLYG*)(B[i].item))->P[(j+1)%N]).y) +
				((((POLYG*)(B[i].item))->P[j]).y))
				);*/
			//	printf("%lf \n", S);
				S += sqwe(((((POLYG*)(B[i].item))->P[j])),
     				 ((((POLYG*)(B[i].item))->P[(j+1)%N])));
                }
     			printf("Площадь многоугольника = %lf \n",
     			S);
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
