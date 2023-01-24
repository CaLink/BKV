#include "def.h"

extern char s[256], * lex[128];
extern int nlex;
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


char str[256];

void handleLine()
{
	int i;

	strcpy(s, str); nlex = 0;
	while (1)
	{
		if (nlex == 0)
			lex[nlex++] = strtok(s, " (),[]\n\r");
		else
			lex[nlex++] = strtok(NULL, " (),[]\n\r");
		if (lex[nlex - 1] == NULL) break;
#ifdef DEBUG
		// printf("[%d %s]  ",nlex-1,lex[nlex-1]);
#endif
	}
	putchar('\n');
	for (i = 0; i < NCMD; i++)  // найдем команду
	{
		if (StrCmp(lex[0], LEXCMD[i], MINCMD[i], MAXCMD[i]))
		{
#ifdef DEBUG
			//  printf("найдена команда %s \n",LEXCMD[i]);
#endif
			switch (i) {
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
				if (nlex = 0) usage();
				else convex(lex[1]);
				break;
			case Area:
				if (nlex = 0) usage();
				else area(lex[1]);
				break;
			case Simple:
				if (nlex = 0) usage();
				else simple(lex[1]);
				break;
				/*case Volume:
					if (nlex=0) usage();
					else volume(lex[1]);
				  break;
				case Centr:
					  break;*/
			default:
				printf("Ќе найдена команда %s \n", lex[0]);

			}
			break;
		}
	}
	if (i == NCMD)   printf("Ќе распознана команда %s \n", lex[0]);


}


void read(void)
{
	FILE* obj;
	obj = fopen("FILE.txt", "r");

	if (obj == NULL)
	{
		printf("Whoops, Smth wrong with file");
		return;
	}

	while (fgets(str, 256, obj) != NULL)
	{
		printf("%s", str);
		handleLine();
	}

	fclose(obj);


}