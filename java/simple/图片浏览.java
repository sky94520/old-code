import tkinter as tk, os
class Application(tk.Frame):
    def __init__(self, master=None):
        self.files = os.listdir(r'F:\imgk')
        self.index = 0
        self.img = tk.PhotoImage(file=r'F:\imgk' + '\\' + self.files[self.index])
        tk.Frame.__init__(self, master)
        self.pack()
        self.createWidgets()

    def createWidgets(self):
        self.lblImage = tk.Label(self, width=300, height=300)
        self.lblImage['image'] = self.img
        self.lblImage.pack()
        self.f = tk.Frame()
        self.f.pack()
        self.btnPrev = tk.Button(self.f, text='��һ��', command=self.prev)
        self.btnPrev.pack(side=tk.LEFT)
        self.btnNext = tk.Button(self.f, text='��һ��', command=self.next)
        self.btnNext.pack(side=tk.LEFT)

    def prev(self):
        self.showfile(-1)

    def next(self):
        self.showfile(1)

    def showfile(self, n):
        self.index += n
        if self.index < 0:
            self.index = len(self.files) - 1
        if self.index > (len(self.files) - 1):
            self.index = 0
        self.img = tk.PhotoImage(file=r'F:\imgk' + '\\' + self.files[self.index])
        self.lblImage['image'] = self.img


root = tk.Tk()
root.title('����ͼƬ�����')
app = Application(master=root)
app.mainloop()