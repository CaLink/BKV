#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DEBUG
//#undef DEBUG

#define Nmax 10000
typedef enum { Point=0, Line, Segm, Circle, Polyg, Polyh, Plane, Sphere, Ball, Set } OBJ;
typedef enum { Exit=0, Help=1, Define, Read, Is, Convex, Area, Volume, Centr, Add, Simple } CMD;

int StrCmp(char *lex, char *full, int Min, int Max);
void finish(void);
int volume(char *);
int convex(char *);
int topic(char *);
int is(char*, char*);
int area(char *);
int usage(void);
void add (void);
void read(void);
int simple(char *);




#define Type int

typedef struct Obj {
	char *name;
	short int typ;
	void *item;
 } OBJECT;

typedef struct point
{
	Type Point;
	int n;
	double x; double y;
	// double z;
}  POINT;

typedef struct line
{
	Type Line;
	POINT *p1; POINT *p2;
 } LINE;

typedef struct segm
{
	Type Segm;
	POINT *p1; POINT* p2;
} SEGM;

typedef struct polyg
{
	Type Polyg;
	int n;
	POINT *P;
} POLYG;

typedef struct circle
{
	Type Circle;
	double x; double y; double R;
} CIRCLE;

/*typedef struct sphere
{
	Type Sphere;
	double x; double y; double z; double R;
} SPHERE;

typedef struct ball
{
	Type Ball;
	double x; double y; double z; double R;
} BALL;


typedef struct plane
{
	Type Plane;
	POINT *p1; POINT *p2; POINT *p3;
} PLANE;
*/

