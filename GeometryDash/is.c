#include "def.h"
#include "math.h"

extern char* LEXOBJ[];
extern short MINOBJ[];
extern short MAXOBJ[];
extern short NOBJ;
extern char* LEXCMD[];
extern short MINCMD[];
extern short MAXCMD[];
extern short NCMD;
extern OBJECT B[Nmax]; extern int nobj;
extern char* lex[];

double sas(POINT* p1, POINT* p2)
{
	return(((p2->x - p1->x) * (p2->y + p1->y)) / 2);
}

double distSpec(POINT* p1, POINT* p2)
{
	double t = 0,q=0;

	t = (p2->x - p1->x) * (p2->x - p1->x);
	q = (p2->y - p1->y) * (p2->y - p1->y);

	t = t + q;
	return t;
	
}

double detSpec(POINT* p1, POINT* p2, POINT* p3)
{
	return
		p1->x * p2->y + p3->x * p1->y + p2->x * p3->y - p3->x * p2->y - p2->x * p1->y - p1->x * p3->y;
}

int isInterSpec(POINT* p1, POINT* p2, POINT* p3, POINT* p4)
{
	if (((detSpec(p1, p2, p3) * detSpec(p1, p2, p4)) < 0) && ((detSpec(p3, p4, p1) * detSpec(p3, p4, p2)) < 0))
		return 1;
	return 0;
}


int is(char* what, char* who)
{
	POINT maxPoint;
	maxPoint.x = 10;
	maxPoint.y = 10;

	int count = 0;
	double S = 0;
	double S2 = 0;
	double S3 = 0;
	int N = 0;
	OBJECT PolTest;
	PolTest.item = (void*)malloc(sizeof(POLYG));

	double res = 0;
	int i = 0;

	void* obj = 0;
	POINT* pt = 0;
	Type q = -1;

	for (int i = 0; i < nobj; i++)
	{
		if (strcmp(B[i].name, what) == 0)
		{
			obj = B[i].item;
			q = B[i].typ;
		}
		if (strcmp(B[i].name, who) == 0)
			pt = (POINT*)B[i].item;

	}
	// PolTest->P = ((POINT*)B[j].item);

	switch (q) {
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
	{

		CIRCLE* temp = ((CIRCLE*)obj);
		
		maxPoint.x = temp->x;
		maxPoint.y = temp->y;



		S = distSpec(&maxPoint, pt);

		if (S>(temp->R* temp->R))
		{
			printf("Точка лежит вне окружности --- ");
		}
		else if(S==(temp->R* temp->R))
			printf("Точка находится на окружности +-+");
		else 
			printf("Точка находится внутри окружности +++");

	}
		break;
	case Polyg:

	{


		POLYG* temp = ((POLYG*)obj);
		N = temp->n;
		


		for (i = 0; i < N; i++)
		{
			
			count += isInterSpec(&(temp->P[i]), &(temp->P[(i + 1)%N]), pt, &maxPoint);
			printf("%lf \n", count);
		}

		// Проблема - Ломаеться, если проходит ПРЯМО СКВОЗЬ точку

		if (count%2==0)
		{
			printf("Точка лежит вне многоугольника");
		}
		else 
			printf("Точка лежит внутри многоугольника");
		

		/*
		for (i = 0; i < N - 1; i++)
		{
			S += sas(&(temp->P[i]), &(temp->P[i + 1]));

			S2 += sas(&(temp->P[i]), &(temp->P[i + 1]));
		}

		S += sas(&(temp->P[i]), &(temp->P[0]));

		S2 += sas(&(temp->P[i]), pt);
		S2 += sas(pt, &(temp->P[0]));




		if (S < S2)
		{
			printf("Точка лежит вне многоугольника");
		}
		else if (S > S2)
			printf("Точка лежит внутри многоугольника");
		else
			printf("Точка где-то на периметре");
		*/
	}
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
