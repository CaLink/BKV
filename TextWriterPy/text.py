import tkinter as tk
import tkinter.font as tkFont
import filedialog as fd
from PIL import Image, ImageTk
from textwrap import wrap
import re

class App:

    font = "Arial"
    size = "5"
    fontSize = ""
    textIn = ""
    pickPath =""
    fontPath = ""

    def __init__(self, root):
        #setting title
        root.title("TextWriter")
        #setting window size
        width=433
        height=345
        screenwidth = root.winfo_screenwidth()
        screenheight = root.winfo_screenheight()
        alignstr = '%dx%d+%d+%d' % (width, height, (screenwidth - width) / 2, (screenheight - height) / 2)
        root.geometry(alignstr)
        root.resizable(width=False, height=False)

        bgBut=tk.Button(root)
        bgBut["bg"] = "#f0f0f0"
        ft = tkFont.Font(family='Times',size=10)
        bgBut["font"] = ft
        bgBut["fg"] = "#000000"
        bgBut["justify"] = "center"
        bgBut["text"] = "Background"
        bgBut.place(x=20,y=30,width=70,height=25)
        bgBut["command"] = self.bgBut_command

        fontBut=tk.Button(root)
        fontBut["bg"] = "#f0f0f0"
        ft = tkFont.Font(family='Times',size=10)
        fontBut["font"] = ft
        fontBut["fg"] = "#000000"
        fontBut["justify"] = "center"
        fontBut["text"] = "Font"
        fontBut.place(x=20,y=70,width=70,height=25)
        fontBut["command"] = self.fontBut_command

        self.textIn = tk.Text(width=35,height=15,wrap="word")
        self.textIn.place(x=110,y=30)

        

        def is_valid(newval):
            return re.match("\d{0,2}$",newval) is not None

        check = (root.register(is_valid), "%P")
        self.fontSize = tk.Entry(validate="key",validatecommand=check,width=8)
        self.fontSize.pack(padx=20, pady=105, anchor=tk.NW)
        self.fontSize.insert(0,"14")

        windBut=tk.Button(root)
        windBut["bg"] = "#f0f0f0"
        ft = tkFont.Font(family='Times',size=10)
        windBut["font"] = ft
        windBut["fg"] = "#000000"
        windBut["justify"] = "center"
        windBut["text"] = "Print"
        windBut.place(x=20,y=140,width=70,height=25)
        windBut["command"] = self.windBut_command
        



    def bgBut_command(self):
        filetypes = (
        ('text files', '*.txt'),
        ('All files', '*.*'))

        self.pickPath = fd.askopenfilename()
        



    def fontBut_command(self):
        filetypes = (
        ('text files', '*.txt'),
        ('All files', '*.*'))

        self.fontPath = fd.askopenfilename()

    def windBut_command(self):

        path = "bg.png"
        

        newWindow = tk.Toplevel()
        newWindow.title("JPEEEG")
        newWindow.geometry("700x600")
        newWindow.resizable(width=False, height=False)

        frame = tk.Frame(newWindow, width=700, height=600)
        frame.pack()
        frame.place(anchor='center', relx=0.5, rely=0.5)

        image1 = Image.open(self.pickPath)
        image1=image1.resize((700,600))
        test = ImageTk.PhotoImage(image1)
        
        label1 = tk.Label(frame,image=test)
        label1.image = test
        label1.pack()
        
        text = self.textIn.get("1.0","end")
        label = tk.Label(frame,text=text,font=(self.font,self.fontSize.get()))
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


if __name__ == "__main__":
    root = tk.Tk()
    app = App(root)
    root.mainloop()
