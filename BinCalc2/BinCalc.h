#ifndef BinCalc_h
#define BinCalc_h

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>

extern Fl_Input *inputA;
extern Fl_Input *inputB;
extern Fl_Input *inputC;
extern Fl_Button *bitChanger;
extern Fl_Button *sysChanger;

void init();

void cbCountButton();
void CountButton();
void SetButtonValue();
void ChangeBit();
void ChangeSystem();
void DoOperation(Fl_Button* but, void*);

Fl_Button* opArr[12];
const char *op[]={"+","-","*","/","%","<<",">>","~A","~B","&","|","^"};

Fl_Button* A[4][64], *B[4][64], *C[4][64];

int bit = 4;                            //система равна 0-2-4-6
int bitArr[8] = {8,0,16,1,32,2,64,3};   //система +1 - обращение к нужному массиву
int syst = 10;


#endif
