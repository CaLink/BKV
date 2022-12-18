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
			inputA = new Fl_Input(1060, aiY, 155, 40);
     		inputA->value("0");
     		inputA->callback((Fl_Callback*)GetInput);
			inputB = new Fl_Input(1060, biY, 155, 40);
      		inputB->value("0");
			inputB->callback((Fl_Callback*)GetInput);
			inputC = new Fl_Input(1060, ciY, 155, 40);
      		inputC->value("0");
			inputC->callback((Fl_Callback*)GetInput);


			bitChanger = new Fl_Button(280, 145, 95, 35, "32");
			bitChanger->color((Fl_Color)29);
			bitChanger->labelsize(18);
			bitChanger->callback((Fl_Callback*)ChangeBit);

			sysChanger = new Fl_Button(825, 145, 95, 35, "10");
			sysChanger->labelsize(18);
			sysChanger->callback((Fl_Callback*)ChangeSystem);
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
			Fl_Button* o = new Fl_Button(30, 545, 105, 35, "Result");
			o->box(FL_NO_BOX);
			o->labelsize(18);
		}
		{
			Fl_Button* o = new Fl_Button(490, 450, 270, 45, "Operations");
			o->box(FL_NO_BOX);
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
    A[i][j] = new Fl_Button(65 + x,aY,15 + w,25,"0");
    A[i][j]->labelsize(16);
    A[i][j]->callback((Fl_Callback*)SetButtonValue);
    A[i][j]->hide();
    B[i][j] = new Fl_Button(65 + x,bY,15 + w,25,"0");
    B[i][j]->labelsize(16);
    B[i][j]->callback((Fl_Callback*)SetButtonValue);
    B[i][j]->hide();
    C[i][j] = new Fl_Button(65 + x,cY,15 + w,25,"0");
    C[i][j]->labelsize(16);
    C[i][j]->callback((Fl_Callback*)SetButtonValue);
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

void SetButtonValue(Fl_Button *but,void*)
{
	if (but->y()==cY)
		return;
	but->label() == "1"? but->label("0") : but->label("1");

	CountButton(but);
}

void CountButton(Fl_Button *but)
{
	
	switch (but->y())
	{
	case aY:Count(A[bitArr[bit+1]],inputA);break;
	case bY:Count(B[bitArr[bit+1]],inputB);break;
	//case cY:Count(C[bitArr[bit+1]],inputC);break;	

	}
	
}

void Count(Fl_Button*arr[], Fl_Input *who)
{
	
	char a= 0;
	short b=0;
	int c= 0;
	int64_t d=0;

	long long slider=1;

	for(int i = 0; i < bitArr[bit];i++)


	// все ещё не работает ссаные 64 бита
	switch (bit)
	{

	case 0: a+= arr[i]->label() =="1"? 1<<(bitArr[bit]-1-i):0;break;
	case 2:	b+= arr[i]->label() =="1"? 1<<(bitArr[bit]-1-i):0;break;
	case 4:	c+= arr[i]->label() =="1"? 1<<(bitArr[bit]-1-i):0;break;
	//case 6:	d+= arr[i]->label() =="1"? (long long)(slider<<(bitArr[bit]-1-i)):0;break;
	case 6:	
	int64_t temp = ((int64_t)(1)) << ((int64_t)(bitArr[bit] - 1 - i));
	d+= arr[i]->label() =="1"? temp : 0;break;


	}

	if(who != NULL)
	
	switch (bit)
	{
	case 0: RePrint(a,who);break;
	case 2:	RePrint(b,who);break;
	case 4:	RePrint(c,who);break;
	case 6:	RePrint(d,who);break;
	}

}

void ChangeBit()
{

  for (int i = 0; i < bitArr[bit]; i++)
  {
    A[bitArr[bit+1]][i]->hide();
    B[bitArr[bit+1]][i]->hide();
    C[bitArr[bit+1]][i]->hide();
  }

  bit = bit==6?0:bit+2;
  switch (bit)
  {
  case 0:bitChanger->label("8");break;
  case 2:bitChanger->label("16");break;
  case 4:bitChanger->label("32");break;
  case 6:bitChanger->label("64");break;
  
  }
  
    for (int i = 0; i < bitArr[bit]; i++)
  {
    A[bitArr[bit+1]][i]->show();
    B[bitArr[bit+1]][i]->show();
    C[bitArr[bit+1]][i]->show();
  }

  Count(A[bitArr[bit+1]],inputA);
  Count(B[bitArr[bit+1]],inputB);
  Count(C[bitArr[bit+1]],inputC);
	
};

void ChangeSystem()
{
	char str[50];
	char sys[2]={'%'};

	/*switch (syst)
	{
		case 8:	syst=10; sysChanger->label("10"); sys[1]='d'; break;
		case 10:syst=16; sysChanger->label("16"); sys[1]='x'; break;
		case 16:syst=8; sysChanger->label("8"); sys[1]='o'; break;
	}*/

	switch (syst)
	{
		case 8:	
		syst=10;
		sysChanger->label("10");
		sprintf(str, "%d", cA);inputA->value((const char*)str);
		sprintf(str, "%d", cB);inputB->value((const char*)str);
		sprintf(str, "%d", cC);inputC->value((const char*)str);
		break;
		case 10:
		syst=16;
		 sysChanger->label("16"); sys[1]='x';
		sprintf(str, "%x", cA);inputA->value((const char*)str);
		sprintf(str, "%x", cB);inputB->value((const char*)str);
		sprintf(str, "%x", cC);inputC->value((const char*)str);
		 break;
		case 16:
		syst=8;
		sysChanger->label("8"); sys[1]='o';
		sprintf(str, "%o", cA);inputA->value((const char*)str);
		sprintf(str, "%o", cB);inputB->value((const char*)str);
		sprintf(str, "%o", cC);inputC->value((const char*)str);
		break;
	}

}

void SetValue(Fl_Input*who, Fl_Button*arr[])
{

	char str[50];
	long long val = 0;

		switch (syst)
	{
	case 10: sscanf(who->value(),"%d",&val); break;
	case 16: sscanf(who->value(),"%x",&val); break;
	case 8: sscanf(who->value(),"%o",&val); break;
	}
	
	for (int i = 0; i < bitArr[bit]; i++)
	{
		
		(val&(1<<i))==0?arr[bitArr[bit]-1-i]->label("0"):arr[bitArr[bit]-1-i]->label("1");
	}
		

	

}

void DoOperation(Fl_Button* but, void*)
{

	long long ans=0;

switch (but->x())
{
case 240:ans=cA+cB;	break;
case 297:ans=cA-cB;	break;
case 355:ans=cA*cB;	break;
case 412:if(cB >0)ans=cA/cB;break;
case 470:ans=cA%cB;	break;
case 527:ans=cA<<cB;	break;
case 585:ans=cA>>cB;	break;
case 642:ans=~cA;	break;
case 700:ans=~cB;	break;
case 757:ans=cA&cB;	break;
case 815:ans=cA|cB;	break;
case 872:ans=cA^cB;	break;
}  

switch (bit)
{
case 0: RePrint((char)ans,inputC);break;
case 2: RePrint((short)ans,inputC);break;
case 4: RePrint((int)ans,inputC);break;
case 6: RePrint(ans,inputC);break;

}


SetValue(inputC,C[bitArr[bit+1]]);

/*
switch (bit)
{
case 0:SetValue(inputC,C[0]) ;break;
case 2:SetValue(inputC,C[1]) ;break;
case 4:SetValue(inputC,C[2]) ;break;
case 6:SetValue(inputC,C[3]) ;break;
}
*/

}

void GetInput(Fl_Input*inp)
{
	switch (inp->y())
	{
	case aiY:SetValue(inputA,A[bitArr[bit+1]]);break;
	case biY:SetValue(inputB,B[bitArr[bit+1]]);break;
	case ciY:RePrint(cC,inputC);break;
	}
}

/* swich-case(operation by (X;Y))
  char str[50];
  sprintf(str,"%d",but->x());
  inputA->value(str);
*/