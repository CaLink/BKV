#include "def.h"

extern OBJECT B[Nmax]; extern int nobj;

void finish(void)
{    FILE *F;
	printf("Завершается работа программы!\n");
        if (nobj ==0)
         { 
          printf("Файл DATA.dat не изменен! \n");
          exit(0);
         }
	F=fopen("DATA.dat","w");
          printf("Все текущие объекты записываются в файл DATA.dat\n");
	  printf( "Предыдущие данные удаляются! \n");
	fwrite(&nobj, sizeof(int), 1, F);
	for (int i=0; i<nobj; i++)   // цикл по всем объектам
	{ int len;
          len=strlen(B[i].name)+1;  // запишем тип и имя
           fwrite(&B[i].typ, sizeof( short), 1, F);
           fwrite(&len, sizeof( short), 1, F);
           fwrite(B[i].name, 1, len, F);

         switch(B[i].typ) {
         case Point:
          fwrite((POINT *)B[i].item, sizeof( POINT ), 1, F);
                break;
         case Line:
          fwrite((LINE *)B[i].item, sizeof( LINE ), 1, F);
                break;
         case Segm:
          fwrite((SEGM *)B[i].item, sizeof( SEGM), 1, F);
                break;
         case Circle:
          fwrite((CIRCLE *)B[i].item, sizeof( CIRCLE ), 1, F);
                break;
         case Polyg:
          fwrite((POLYG *)B[i].item, sizeof( POLYG ), 1, F);
                break;
      /*   case Plane:
          fwrite((PLANE *)B[i].item, sizeof( PLANE ), 1, F);
      	        break;
         case Sphere: 
          fwrite((SPHERE *)B[i].item, sizeof( SPHERE ), 1, F);
	        break;
         case Ball:   
          fwrite((BALL *)B[i].item, sizeof( BALL ), 1, F);*/
	/////////////  Еще объекты ????        
         }
	  
	}
	exit(0);
}
