#include "BinCalc.h"
#include <math.h>

Fl_Input* inputA = (Fl_Input*)0;
Fl_Input* inputB = (Fl_Input*)0;
Fl_Input* inputC = (Fl_Input*)0;
Fl_Button* bitChanger = (Fl_Button*)0;
Fl_Button* sysChanger = (Fl_Button*)0;

int main(int argc, char** argv) {
	Fl_Double_Window* w;
	{
		Fl_Double_Window* o = new Fl_Double_Window(1245, 675);
		w = o; if (w) {/* empty */ }
		o->color((Fl_Color)23);
		{
			inputA = new Fl_Input(1060, 250, 155, 40);
      inputA->value("0");
			inputB = new Fl_Input(1060, 375, 155, 40);
      inputB->value("0");
			inputC = new Fl_Input(1070, 575, 155, 40);
      inputC->value("0");

			bitChanger = new Fl_Button(280, 145, 95, 35, "32");
			bitChanger->color((Fl_Color)29);
			bitChanger->labelsize(18);

			sysChanger = new Fl_Button(825, 145, 95, 35, "10");
			sysChanger->labelsize(18);
		}
		{
			Fl_Button* o = new Fl_Button(0, 265, 80, 25, "A");
			o->box(FL_NO_BOX);
			o->labelsize(24);
		}
		{
			Fl_Button* o = new Fl_Button(0, 380, 80, 40, "B");
			o->box(FL_NO_BOX);
			o->labelsize(24);
		}
		{
			Fl_Button* o = new Fl_Button(0, 585, 80, 40, "C");
			o->box(FL_NO_BOX);
			o->labelsize(24);
		}
		{
			Fl_Button* o = new Fl_Button(5, 330, 70, 20, "+");
			o->box(FL_NO_BOX);
			o->labelsize(24);
		}
		{
			Fl_Button* o = new Fl_Button(440, 20, 345, 35, "Bit Calc");
			o->box(FL_NO_BOX);
			o->labelsize(26);
		}
		{
			Fl_Button* o = new Fl_Button(205, 80, 230, 50, "Bit");
			o->box(FL_NO_BOX);
			o->labelsize(18);
		}
		{
			Fl_Button* o = new Fl_Button(710, 80, 305, 50, "System");
			o->box(FL_NO_BOX);
			o->labelsize(18);
		}
		{
			Fl_Button* o = new Fl_Button(30, 545, 105, 35, "Operations");
			o->box(FL_NO_BOX);
			o->labelsize(18);
		}
		{
			Fl_Button* o = new Fl_Button(490, 450, 270, 45, "Result");
			o->box(FL_NO_BOX);
			o->labelsize(18);
		}
		{
			Fl_Button* o = new Fl_Button(930, 495, 50, 35, "~A");
			o->labelsize(18);
		}
		{
			Fl_Button* o = new Fl_Button(240, 495, 50, 35, "+");
			o->labelsize(18);
		}

    init();

		o->end();
	}
	w->show(argc, argv);
	return Fl::run();
}

void init()
{
  double scale[]={108.5714+25,37.3333+25,5.1612+25,15};
  int x=0,w=0,t=0;

  for(int i=0;i<4;i++)
  {
   w = i<3?10:0;
   
  
    for(int j=0;j<pow(2,i+3);j++)
  {
    x = j*scale[i];
    A[i][j] = new Fl_Button(65 + x,265,15 + w,25,"0");
    A[i][j]->labelsize(16);
    A[i][j]->callback((Fl_Callback*)cbCountButton);
    A[i][j]->hide();
    B[i][j] = new Fl_Button(65 + x,385,15 + w,25,"0");
    B[i][j]->labelsize(16);
    B[i][j]->callback((Fl_Callback*)cbCountButton);
    B[i][j]->hide();
    C[i][j] = new Fl_Button(65 + x,590,15 + w,25,"0");
    C[i][j]->labelsize(16);
    C[i][j]->callback((Fl_Callback*)cbCountButton);
    C[i][j]->hide();
  }
  }

// пример обращения к нужному массиву

  for (int i = 0; i < bitArr[bit]; i++)
  {
    A[bitArr[bit+1]][i]->show();
    B[bitArr[bit+1]][i]->show();
    C[bitArr[bit+1]][i]->show();
  }
  
  for (int i = 0; i < 12; i++)
  {
    opArr[i] = new Fl_Button(240 + 57.5*i,495,50,35,op[i]);
    opArr[i]->callback((Fl_Callback*)DoOperation);
  }
  

}

void cbCountButton(Fl_Button *but,void*)
{
  char str[50];
  sprintf(str,"%d",but->x());
  inputA->value(str);
}

void DoOperation(Fl_Button* but, void*)
{
  // swich-case(operation by (X;Y))
  char str[50];
  sprintf(str,"%d",but->x());
  inputA->value(str);

}
