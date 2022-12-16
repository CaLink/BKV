#include "BinCalc.h"
#include <math.h>

Fl_Input *inputA=(Fl_Input *)0;
Fl_Input *inputB=(Fl_Input *)0;
Fl_Input *inputC=(Fl_Input *)0;
Fl_Button *bitChanger=(Fl_Button *)0;
Fl_Button *sysChanger=(Fl_Button *)0;

int main(int argc, char **argv) 
{

  Fl_Double_Window* w;
  Fl_Double_Window* o = new Fl_Double_Window(1000, 400);
  
  w = o; if (w) {/* empty */}
  inputA = new Fl_Input(50, 60, 155, 40, "A");
  inputB = new Fl_Input(50, 120, 155, 40, "B");
  inputC = new Fl_Input(50, 180, 155, 40, "C");
  bitChanger = new Fl_Button(240, 25, 70, 20, "bit");
  sysChanger = new Fl_Button(335, 25, 140, 20, "Numeral system");

  init();

  o->end();
  
  w->show(argc, argv);
  return Fl::run();

}

void init()
{
  
  for(int i=0;i<4;i++)
  for(int j=0;j<pow(2,i+3);j++)
  {
    A[i][j] = new Fl_Button(235 + 25*j*(4-i),70,20,20,"0");
    A[i][j]->callback((Fl_Callback*)cbCountButton);
    A[i][j]->hide();
    B[i][j] = new Fl_Button(235 + 25*j*(4-i),130,20,20,"0");
    B[i][j]->callback((Fl_Callback*)cbCountButton);
    B[i][j]->hide();
    C[i][j] = new Fl_Button(235 + 25*j*(4-i),190,20,20,"0");
    C[i][j]->callback((Fl_Callback*)cbCountButton);
    C[i][j]->hide();
  }

// пример обращения к нужному массиву

  for (int i = 0; i < bitArr[bit]; i++)
  {
    A[bitArr[bit+1]][i]->show();
  }
  
  for (int i = 0; i < 12; i++)
  {
    opArr[i] = new Fl_Button(220 + 31*i,245,30,30,op[i]);
    opArr[i]->callback((Fl_Callback*)DoOperation);
  }
  

}

void cbCountButton()
{
  inputA->value("test");
}

void DoOperation(Fl_Button* but, void*)
{
  // swich-case(operation by (X;Y))
  char str[50];
  sprintf(str,"%d",but->x());
  inputA->value(str);

}