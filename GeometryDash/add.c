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

void add(void)
{
//printf("В конце объявления введите ;");
	  for (int i=0; i<NOBJ; i++)  // найдем команду
         {
			  if (StrCmp(lex[1],LEXOBJ[i],MINOBJ[i],MAXOBJ[i]))
			  {
//#ifdef DEBUG
			  // printf("найдена лексема %s \n",LEXOBJ[i]);
//#endif
        if (islower(lex[2][0])) 
	 {  printf("Имя объекта должно начинаться с заглавной буквы!\n"); return;};

          B[nobj].name=malloc(strlen(lex[2])+1);
          strcpy(B[nobj].name,lex[2]);
     
     switch(i) {
     case Point: 
          B[nobj].typ=Point;
          B[nobj].item=(void *)malloc(sizeof(POINT));

          sscanf(lex[3],"%lf", &((POINT *)(B[nobj].item))->x);
          sscanf(lex[4],"%lf", &((POINT *)(B[nobj].item))->y);
    //      if (isdigit(lex[5][0]))
	//	{
	//            sscanf(lex[5],"%lf", &((POINT *)(B[nobj].item))->z);
  	//	    ((POINT *)(B[nobj].item))->n=3;
	//	}
	//  else 
	//  {
		  ((POINT *)(B[nobj].item))->n=2;
	//		  ((POINT *)(B[nobj].item))->z=0.0;
	//  }
printf("ввели точку %s %d %lf %lf\n",
B[nobj].name,
((POINT *)(B[nobj].item))->n,
((POINT *)(B[nobj].item))->x,
((POINT *)(B[nobj].item))->y);

    nobj++;
          break; 
          
     case Line:
	  B[nobj].typ=Line;
          B[nobj].item=(void *)malloc(sizeof(LINE));
    
          sscanf(lex[3],"%lf", &((LINE *)(B[nobj].item))->p1);
          char *a = lex[3];
          for (int i = 0; i < nobj; i++)
          {
          	if ((B[i].typ == Point)&&(strcmp(B[i].name, a)==0))
          	{
          	((LINE *)(B[nobj].item))->p1 = (POINT*)B[i].item;
          	}
          }	
          sscanf(lex[4],"%lf", &((LINE *)(B[nobj].item))->p2);
          a = lex[4];
          for (int i = 0; i < nobj; i++)
          {
          	if ((B[i].typ == Point)&&(strcmp(B[i].name, a)==0))
          	{
          	((LINE *)(B[nobj].item))->p2 = (POINT *)B[i].item;
          	}
          }	
		     printf("ввели линию %s (%lf %lf) (%lf %lf) \n",
   B[nobj].name,
 (((LINE *)(B[nobj].item))->p1)->x,
 (((LINE *)(B[nobj].item))->p1)->y,
// (((LINE *)(B[nobj].item))->p1)->z,
 (((LINE *)(B[nobj].item))->p2)->x,
 (((LINE *)(B[nobj].item))->p2)->y
 //(((LINE *)(B[nobj].item))->p2)->z
 );

    nobj++; 
      	  break; 
     case Segm:  
     B[nobj].typ=Segm;
          B[nobj].item=(void *)malloc(sizeof(SEGM));
    
          sscanf(lex[3],"%lf", &((SEGM *)(B[nobj].item))->p1);
          a = lex[3];
          for (int i = 0; i < nobj; i++)
          {
          	if ((B[i].typ == Point)&&(strcmp(B[i].name, a)==0))
          	{
          	((SEGM  *)(B[nobj].item))->p1 = (POINT*)B[i].item;
          	}
          }	
          sscanf(lex[4],"%lf", &((SEGM *)(B[nobj].item))->p2);
          a = lex[4];
          for (int i = 0; i < nobj; i++)
          {
          	if ((B[i].typ == Point)&&(strcmp(B[i].name, a)==0))
          	{
          	((SEGM *)(B[nobj].item))->p2 = (POINT *)B[i].item;
          	}
          }	
		     printf("ввели линию %s P1 (%lf %lf) P2 (%lf %lf) \n",
   B[nobj].name,
 (((LINE *)(B[nobj].item))->p1)->x,
 (((LINE *)(B[nobj].item))->p1)->y,
 //(((LINE *)(B[nobj].item))->p1)->z,
 (((LINE *)(B[nobj].item))->p2)->x,
 (((LINE *)(B[nobj].item))->p2)->y
// (((LINE *)(B[nobj].item))->p2)->z
);

    nobj++; 
          break; 
     case Circle:  
          B[nobj].typ=Circle;
          B[nobj].item=(void *)malloc(sizeof(CIRCLE));
    
          sscanf(lex[3],"%lf", &((CIRCLE *)(B[nobj].item))->x);
          sscanf(lex[4],"%lf", &((CIRCLE *)(B[nobj].item))->y);
          sscanf(lex[5],"%lf", &((CIRCLE *)(B[nobj].item))->R);
		     printf("ввели окружность %s %lf %lf %lf\n",
   B[nobj].name,
 ((CIRCLE *)(B[nobj].item))->x,
 ((CIRCLE *)(B[nobj].item))->y,
 ((CIRCLE *)(B[nobj].item))->R);

    nobj++; 
    break;
     case Polyg:  
          B[nobj].typ=Polyg;
          B[nobj].item=(void *)malloc(sizeof(POLYG));
          a = "";
   printf("ввели полигон %s ", B[nobj].name);   
   ((POLYG *)(B[nobj].item))->n = 0; 
   double N = 0;
    sscanf(lex[3],"%lf", &N);
    ((POLYG *)(B[nobj].item))->P = malloc(sizeof(POINT)*N);
   // double N = &(((POLYG *)(B[nobj].item))->n);
  //  printf("%d", N);
 // printf("%d", (double)lex[3]);
 	
    for (int j = 4; j<4+N; j++)
    {
       //   sscanf(lex[j],"%lf", &((POLYG *)(B[nobj].item))->P[j-4]);
          a = lex[j];
          for (int i = 0; i < nobj; i++)
          {
          	if ((B[i].typ == Point)&&(strcmp(B[i].name, a)==0))
          	{
          		POINT te;
      		      	te.Point = 0;
         	     	te.x = ((POINT*)B[i].item)->x;
     	 	        te.y = ((POINT*)B[i].item)->y;
     	        	((POLYG*)(B[nobj].item))->P[j - 4] = te;
          	}
          }
          printf("P[%d] (%lf %lf) ", 
          j-3,
          (((POLYG *)(B[nobj].item))->P[j-4]).x,
 	  (((POLYG *)(B[nobj].item))->P[j-4]).y);	
 	  (((POLYG *)(B[nobj].item))->n)++;
     }  
        printf("%d",
        ((POLYG *)(B[nobj].item))->n);   

    nobj++; 
     break;
 /*  case Polyh:   break; 
   case Plane: 
          B[nobj].typ=Plane;
          B[nobj].item=(void *)malloc(sizeof(PLANE));
    
          sscanf(lex[3],"%lf", &((PLANE *)(B[nobj].item))->p1);
          a = lex[3];
          for (int i = 0; i < nobj; i++)
          {
          	if ((B[i].typ == Point)&&(strcmp(B[i].name, a)==0))
          	{
          	((PLANE *)(B[nobj].item))->p1 = (POINT*)B[i].item;
          	}
          }	
          sscanf(lex[4],"%lf", &((PLANE *)(B[nobj].item))->p2);
          a = lex[4];
          for (int i = 0; i < nobj; i++)
          {
          	if ((B[i].typ == Point)&&(strcmp(B[i].name, a)==0))
          	{
          	((PLANE*)(B[nobj].item))->p2 = (POINT *)B[i].item;
          	}
          }
          sscanf(lex[5],"%lf", &((PLANE *)(B[nobj].item))->p3);
          a = lex[5];
          for (int i = 0; i < nobj; i++)
          {
          	if ((B[i].typ == Point)&&(strcmp(B[i].name, a)==0))
          	{
          	   ((PLANE*)(B[nobj].item))->p3 = (POINT *)B[i].item;
          	}
          }	
		     printf("ввели линию %s P1 (%lf %lf %lf) P2 (%lf %lf %lf) P3 (%lf %lf %lf)\n",
   B[nobj].name,
 (((PLANE *)(B[nobj].item))->p1)->x,
 (((PLANE*)(B[nobj].item))->p1)->y,
 (((PLANE *)(B[nobj].item))->p1)->z,
 (((PLANE *)(B[nobj].item))->p2)->x,
 (((PLANE*)(B[nobj].item))->p2)->y,
 (((PLANE*)(B[nobj].item))->p2)->z,
 (((PLANE *)(B[nobj].item))->p3)->x,
 (((PLANE*)(B[nobj].item))->p3)->y,
 (((PLANE *)(B[nobj].item))->p3)->z);

    nobj++; 
       break; 
     case Sphere:
          B[nobj].typ=Sphere;
          B[nobj].item=(void *)malloc(sizeof(SPHERE));
    
          sscanf(lex[3],"%lf", &((SPHERE *)(B[nobj].item))->x);
          sscanf(lex[4],"%lf", &((SPHERE *)(B[nobj].item))->y);
          sscanf(lex[5],"%lf", &((SPHERE *)(B[nobj].item))->z);
          sscanf(lex[6],"%lf", &((SPHERE *)(B[nobj].item))->R);
		     printf("ввели сферу %s %lf %lf %lf R=%lf\n",
   B[nobj].name,
 ((SPHERE *)(B[nobj].item))->x,
 ((SPHERE *)(B[nobj].item))->y,
 ((SPHERE *)(B[nobj].item))->z,
 ((SPHERE *)(B[nobj].item))->R);

    nobj++; 
		   break; 
     case Ball: 
          B[nobj].typ=Ball;
          B[nobj].item=(void *)malloc(sizeof(BALL));
    
          sscanf(lex[3],"%lf", &((BALL *)(B[nobj].item))->x);
          sscanf(lex[4],"%lf", &((BALL *)(B[nobj].item))->y);
          sscanf(lex[5],"%lf", &((BALL *)(B[nobj].item))->z);
          sscanf(lex[6],"%lf", &((BALL *)(B[nobj].item))->R);
		     printf("ввели шар %s %lf %lf %lf R=%lf\n",
   B[nobj].name,
 ((BALL *)(B[nobj].item))->x,
 ((BALL *)(B[nobj].item))->y,
 ((BALL *)(B[nobj].item))->z,
 ((BALL *)(B[nobj].item))->R);
    nobj++; 
		   break; */
                default:;
   }; printf("\n");
  }
 }
}
