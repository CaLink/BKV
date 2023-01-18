#include "II.h"
Fl_File_Chooser* fc, * fnt;
#define DEBUG 1
#undef DEBUG
Fl_Button* File, * Font, * Write;
Fl_Multiline_Input* IN;
Fl_Value_Input* Size;

short int imgH, imgW, SIZE = 4;
static int fcol = 0, odd = 0, first = 1, number = 1, snumber = 1, fumber = 1, k, kmin, K, i;
Fl_Double_Window* W1 = (Fl_Double_Window*)NULL, * w;

#define BG_COLOR 0
Fl_Group* box_group = (Fl_Group*)0;
Fl_Box* box = (Fl_Box*)0;
Fl_Shared_Image* img;

static void file_close(Fl_Box* box, Fl_Shared_Image* img) {
	img = (Fl_Shared_Image*)box->image();

	if (!img) return; // no image displayed
	box->image(0);
	while (img->refcount())
		img->release();
}

static void setpix(int x, int y, unsigned char c);

static void file_open(const char* fpath, Fl_Box** box, Fl_Shared_Image** img, Fl_Group** box_group) {

	file_close(*box, *img);

	*img = Fl_Shared_Image::get(fpath);
	if (!*img)
	{
		fl_alert("Ошибка загрузки изображения: %s", fpath);
		return;
	}
	(*box_group)->size(imgW = (*img)->w(), imgH = (*img)->h());

	(*box)->image(*img);
	(*box)->redraw();
	/*********************************/
  
	unsigned char c = 0;
	for (int i = 1; i < 200; i++)
		for (int j = 1; j < 200; j++)
		{
			if (((i % SIZE) == 0) || ((j % SIZE) == 0))
				setpix(i, j, rand()%255);
			else
				setpix(i, j, rand()%255);
			
		}
	(*box_group)->redraw();
  
	W1->show();
	Fl::redraw();
}


static void setpix(int x, int y, unsigned char c) {
	long index = (y * img->w() * img->d()) + (x * img->d()); // X/Y -> buf index  
	{
		unsigned char* buf = (unsigned char*)img->data()[0];
		switch (img->d()) {
		case 1: {                                    // 8bit
			*(buf + index) = c;
			break;
		}
		case 3:                                      // 24bit
			*(buf + index + 0) = c;
			*(buf + index + 1) = c;
			*(buf + index + 2) = c;
			break;
		default:                                     // ??
			printf("Not supported setpix: chans=%d\n", img->d());
			exit(1);
		}
	}
}

static void ReDraw()
{

file_close(box, img);

	img = Fl_Shared_Image::get(fc->value());
	if (!img)
	{
		fl_alert("Ошибка загрузки изображения: %s", fc->value());
		return;
	}
	
	(box_group)->size(imgW, imgH);

	(box)->image(img);
	(box)->redraw();
	/*********************************/
  
	unsigned char c = 0;
	for (int i = 1; i < imgW; i++)
		for (int j = 1; j < imgH; j++)
		{
      if(rand()%5 >2)
      {
			if (((i % SIZE) == 0) || ((j % SIZE) == 0))
				setpix(i, j, rand()%255);
			else
				setpix(i, j, rand()%255);
      }
		}
	(box_group)->redraw();
  
	W1->show();
	Fl::redraw();

};

static void cb_write(Fl_Button*, void*)
{
  ReDraw();
  //file_open(fc->value(), &box, &img, &box_group);
	box->redraw();
}


static Fl_Double_Window* make_window(Fl_Group** box_group, Fl_Box** box) {
	Fl_Double_Window* w;
	{
		w = new Fl_Double_Window(1024, 508);
		{
			Fl_Scroll* o = new Fl_Scroll(5, 5, 1014, 503, 0);
			o->box(FL_ENGRAVED_BOX);
			*box_group = new Fl_Group(5, 5, 1014, 503, 0);
			(*box_group)->box(FL_NO_BOX);
			*box = new Fl_Box(5, 5, 1014, 503, 0);
			(*box)->box(FL_FLAT_BOX);
			(*box)->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER);
			(*box_group)->end();
			o->end();
			Fl_Group::current()->resizable(o);
		}
		w->show();
	}
	return w;
}

static void cb_(Fl_Button*, void*) { // File load
	W1 = make_window(&box_group, &box);
	fc->show();
	while (fc->visible()) {
		Fl::wait();
	}
	W1->show();
	file_open(fc->value(), &box, &img, &box_group);
	box->redraw();
}

static void cb_fnt(Fl_Button*, void*) {
	fnt->show();
	while (fnt->visible()) {
		Fl::wait();
	}
	//   file_open(fnt->value(), &box, &img, &box_group);
	//    box->redraw();
}

static void cb_size(Fl_Value_Input*, void*) {
	SIZE = Size->value();
}


int main(int argc, char** argv) {
	Fl::visual(FL_DOUBLE | FL_INDEX);
	Fl::get_system_colors();
	fl_register_images();
	Fl::scheme("gtk+");

	{ w = new Fl_Double_Window(610, 375);

	w->label("Управление Табло");
	{ File = new Fl_Button(15, 25, 75, 40, "Файл");
	File->tooltip("Входной файл (файлы)");
	File->callback((Fl_Callback*)cb_);
	File->shortcut(FL_ALT + 'f');
	} // Fl_Button* File
	{ Font = new Fl_Button(15, 75, 75, 40, "Шрифт");
	Font->tooltip("Выбор шрифта");
	Font->callback((Fl_Callback*)cb_fnt);
	Font->shortcut(FL_ALT + 't');
	}
	// Fl_Button* Write
	{
		Write = new Fl_Button(15, 195, 75, 40, "Написать");
		Write->tooltip("write");
		Write->callback((Fl_Callback*)cb_write);
		//Write->shortcut(FL_ALT+'t');
	}
	// Fl_Button* Font
	{ Size = new Fl_Value_Input(15, 125, 75, 40, "Size");
	Size->tooltip("Размер элемента");
	Size->callback((Fl_Callback*)cb_size);
	Size->align(Fl_Align(FL_ALIGN_BOTTOM));
	Size->shortcut(FL_ALT + 's');
	Size->step(1);
	Size->minimum(1);
	Size->value(4);
	Size->maximum(12);
	} // Fl_Button* Font
	IN = new Fl_Multiline_Input(100, 25, 450, 350, "text");
	IN->align(Fl_Align(FL_ALIGN_TOP));

	w->end();
	} // Fl_Double_Window* w
	fc = new Fl_File_Chooser("./pages/", "*", Fl_File_Chooser::MULTI, "File_Chooser");
	fnt = new Fl_File_Chooser("./fnt/", "*", Fl_File_Chooser::SINGLE, "File_Chooser");

	w->show(argc, argv);
	return Fl::run();
}
