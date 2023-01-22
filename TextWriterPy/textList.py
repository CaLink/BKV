from tkinter import *
from tkinter import font
import filedialog as fd
from PIL import Image, ImageTk
from textwrap import wrap
import re

root = Tk()
root.title('TextDrawer')
root.geometry("700x550")
root.resizable(width=False, height=False)

pickPath = "bg.png"


# Change Font Size
def font_size_chooser(e):
	our_font.config(
		size=font_size_listbox.get(font_size_listbox.curselection()))

# Change Font Style
def font_style_chooser(e):
	style = font_style_listbox.get(font_style_listbox.curselection()).lower()

	if style == "bold":
		our_font.config(weight=style)
	if style == "regular":
		our_font.config(weight="normal", slant="roman", underline=0, overstrike=0)
	if style == "italic":
		our_font.config(slant=style)
	if style == "bold/italic":
		our_font.config(weight="bold", slant="italic")
	if style == "underline":
		our_font.config(underline=1)
	if style == "strike":
		our_font.config(overstrike=1)

# Create font chooser function
def font_chooser(e):
	our_font.config(
		family=my_listbox.get(my_listbox.curselection()))

def bgBut_command():
        filetypes = (
        ('text files', '*.txt'),
        ('All files', '*.*'))

        #pickPath = fd.askopenfilename()
        global pickPath
        pickPath = fd.askopenfilename()
        if not pickPath:
            pickPath = "bg.png"
            print(pickPath)

def windBut_command():

        text = my_text.get("1.0","end")

        newWindow = Toplevel()
        newWindow.title("JPEEEG")
        newWindow.geometry("700x600")
        newWindow.resizable(width=False, height=False)

        frame = Frame(newWindow, width=700, height=600)
        frame.pack()
        frame.place(anchor='center', relx=0.5, rely=0.5)

        image1 = Image.open(pickPath)
        image1=image1.resize((700,600))
        test = ImageTk.PhotoImage(image1)
        
        label1 = Label(frame,image=test)
        label1.image = test
        label1.pack()
        
        label = Label(newWindow,text=text,font=our_font,justify= LEFT)
        label.place(anchor='nw', relx=0.0, rely=0.0)
        
        newWindow.update()

        width = label.winfo_width()
        if label.winfo_width() > newWindow.winfo_width():
            # Вычисляем среднюю ширину символа
            average_char_width = label.winfo_width() / len(text)
            # Приблизительно рассчитываем количество символов, которое помещается в окне
            chars_per_line = int(newWindow.winfo_width() / average_char_width)
            # В цикле уменьшаем это количество, пока текст не станет помещаться
            while label.winfo_width() > newWindow.winfo_width():  
                wrapped_text = '\n'.join(wrap(text, chars_per_line))
                label['text'] = wrapped_text
                newWindow.update()
                chars_per_line -= 1

# Designate Our Font
our_font = font.Font(family="Helvetica", size="32")

# Add Frame
my_frame = Frame(root, width=510, height=275)
my_frame.pack(pady=10)
# Freeze Frame in place
my_frame.grid_propagate(False)
my_frame.columnconfigure(0, weight=10)

# Add Text Box
my_text = Text(my_frame, font=our_font)
my_text.grid(row=0, column=0)
my_text.grid_rowconfigure(0, weight=1)
my_text.grid_columnconfigure(0, weight=1)

# Bottom Frame
bottom_frame = Frame(root)
bottom_frame.pack()

#Buttons
bgBut=Button(root)
bgBut["bg"] = "#f0f0f0"
ft = font.Font(family='Times',size=10)
bgBut["font"] = ft
bgBut["fg"] = "#000000"
bgBut["justify"] = "center"
bgBut["text"] = "Background"
bgBut.place(x=250,y=510,width=70,height=25)
bgBut["command"] = bgBut_command

btDraw=Button(root)
btDraw["bg"] = "#f0f0f0"
ft = font.Font(family='Times',size=10)
btDraw["font"] = ft
btDraw["fg"] = "#000000"
btDraw["justify"] = "center"
btDraw["text"] = "Draw"
btDraw.place(x=330,y=510,width=70,height=25)
btDraw["command"] = windBut_command

# Add Labels
font_label = Label(bottom_frame, text="Choose Font", font=("Helvetica", 14))
font_label.grid(row=0, column=0, padx=10, sticky=W)

size_label = Label(bottom_frame, text="Font Size", font=("Helvetica", 14))
size_label.grid(row=0, column=1, sticky=W)

style_label = Label(bottom_frame, text="Font Style", font=("Helvetica", 14))
style_label.grid(row=0, column=2, padx=10, sticky=W)


# Add Listbox
my_listbox = Listbox(bottom_frame, selectmode=SINGLE, width=40)
my_listbox.grid(row=1, column=0, padx=10)

# Size Listbox
font_size_listbox = Listbox(bottom_frame, selectmode=SINGLE, width=20 )
font_size_listbox.grid(row=1, column=1)

# Style Listbox
font_style_listbox = Listbox(bottom_frame, selectmode=SINGLE, width=20 )
font_style_listbox.grid(row=1, column=2, padx=10)


# Add Font Families To Listbox
for f in font.families():
	my_listbox.insert('end', f)

# Add Sizes to Size Listbox
font_sizes = [8, 10, 12, 14, 16, 18, 20, 36, 48]
for size in font_sizes:
	font_size_listbox.insert('end', size)

# Add Styles To Style Listbox
font_styles = ["Regular", "Bold", "Italic", "Bold/Italic", "Underline", "Strike"]
for style in font_styles:
	font_style_listbox.insert('end', style)	


# Bind The Listbox
my_listbox.bind('<ButtonRelease-1>', font_chooser)
font_size_listbox.bind('<ButtonRelease-1>', font_size_chooser)
font_style_listbox.bind('<ButtonRelease-1>', font_style_chooser)

root.mainloop()
