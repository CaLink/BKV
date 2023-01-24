#include "def.h"
extern char *LEXOBJ[];
extern short MINOBJ[];
extern short MAXOBJ[];
extern short NOBJ;
extern char *LEXCMD[];
extern short MINCMD[];
extern short MAXCMD[];
extern short NCMD;
int topic(char *what)
{
	for (int i=0; i<NCMD; i++)  // найдем команду
        {
		 if (StrCmp(what,LEXCMD[i],MINCMD[i],MAXCMD[i]))
		{

       printf("помощь по команде %s :\n", LEXCMD[i]);  

        switch(i) {
		case Exit:
		 	printf("Использование команды exit: \n");
            break;
		case Help: 
		 	printf("Использование команды help: \n");
                            break;
		case Define: 
		  break;
		case Read:
		   break;
		case Is: 
		  break;
		case Convex: 
		  break;
		case Area: 
		  break;
		case Volume: 
		  break;
		case Centr: 
		  break;
			}
		}		       
 	}
	for (int i=0; i<NOBJ; i++)  // найдем команду
        {
		if (StrCmp(what,LEXOBJ[i],MINOBJ[i],MAXOBJ[i]))
		{
		#ifdef DEBUG
			   printf("найдена лексема %s \n",LEXOBJ[i]);
		#endif
       		 printf("помощь по объекту %s :\n", LEXOBJ[i]); 

        switch(i) {
     case Point: 
	   printf ("Объект точка (тип point) содержит запись n - размерность\n");
	   printf ("пространства, 2 - точка на плоскости, 3- точка в \n ");
	   printf ("трехмероном пространстве. Записи х и y задают вещественные\n ");
	   printf ("координаты, для 3-х мерного пространства добавляется z.\n");
	   printf ("Пример задания объекта Point:\n");
	   printf ("define point P1 (0.0, 0.0) ;\n\n");
	     break; 
     case Line:
     printf("Объект линия (тип line)");
         break; 
     case Segm:
          printf("Объект сегмент (тип segm)");
         break; 
     case Circle:
          printf("Объект окружность (тип circal)");
       break; 
     case Polyg:
          printf("Объект полигидрон (тип polyg)");
        break; 
     case Polyh:
          printf("Объект линия (тип line)");
        break; 
     case Plane:
          printf("Объект плоскость (тип plane)");
        break; 
     case Sphere:
          printf("Объект сфера (тип sphere)");
       break; 
     case Ball:
          printf("Объект шар (тип ball)");
         break; 
                default:;
				        }; printf("\n");
  }
 }
}
