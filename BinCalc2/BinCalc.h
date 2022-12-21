#ifndef BinCalc_h
#define BinCalc_h

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>

extern Fl_Input* inputA;
extern Fl_Input* inputB;
extern Fl_Input* inputC;
extern Fl_Button* bitChanger;
extern Fl_Button* sysChanger;

void init();

void SetButtonValue(Fl_Button*, void*);
void ChangeButton(Fl_Button*, bool);
void CountButton(Fl_Button*);
void Count(Fl_Button* [], Fl_Input*);
//void RePrint
void ChangeBit();
void ChangeSystem();
void DoOperation(Fl_Button*, void*);
void SetValue(Fl_Input*, Fl_Button* []);
void SetValue(Fl_Input* who, Fl_Button* arr[], bool);
void GetInput(Fl_Input*);

Fl_Color zero = FL_LIGHT3;
Fl_Color one = (Fl_Color)18;

Fl_Button* opArr[12];
const char* op[] = { "+","-","*","/","%","<<",">>","~A","~B","&","|","^" };

Fl_Button* A[4][64], * B[4][64], * C[4][64];

const int aY = 265, bY = 385, cY = 590;   //для распознования ряда кнопок
const int aiY = 250, biY = 375, ciY = 575;
int bit = 4;                            //система равна 0-2-4-6
int bitArr[8] = { 8,0,16,1,32,2,64,3 };   //система +1 - обращение к нужному массиву
int syst = 10;

long long cA = 0, cB = 0, cC = 0;

template<class T>
void RePrint(T ans, Fl_Input* who)
{
	char str[50];

	switch (syst)
	{
	case 8: 
        sprintf(str, "%o", ans); 
        who->value((const char*)str); break;
	case 10: 
        sprintf(str, "%d", ans); 
        who->value((const char*)str); break;
	case 16:
        sprintf(str, "%x", ans); 
        who->value((const char*)str); break;

	}

	switch (who->y())
	{
	case aiY: 
        cA = ans; break;
	case biY: 
        cB = ans; break;
	case ciY: 
        cC = ans; break;
	}


}
template<class T>
void RePrint(T ans, Fl_Input* who, bool q)
{
	char str[50];

	switch (syst)
	{
	case 8: 
        sprintf(str, "%o", ans);
        who->value((const char*)str); break;
	case 10:
        sprintf(str, "%lld", ans);
        who->value((const char*)str); break;
	case 16:
        sprintf(str, "%x", ans);
        who->value((const char*)str); break;

	}

	switch (who->y())
	{
	case aiY: 
        cA = ans; break;
	case biY:
        cB = ans; break;
	case ciY:
        cC = ans; break;

	}


}

#endif
