
import subprocess
import datetime
from reportlab.pdfgen import canvas
from reportlab.lib.units import inch
import reportlab.pdfbase.ttfonts
def disk_report():
    p = subprocess.Popen("df -h", shell=True, stdout=subprocess.PIPE)
#   print p.stdout.readlines()
    return p.stdout.readlines()

def create_pdf(input, output="disk2.pdf"):
    reportlab.pdfbase.pdfmetrics.registerFont(reportlab.pdfbase.ttfonts.TTFont('song', 'C:/Windows/Fonts/simfang.ttf'))
    #pdfmetrics.registerFont(reportlab.pdfbase.ttfonts.TTFont('song', 'C:/Windows/Fonts/simfang.ttf'))  # ×¢²á×ÖÌå
    c = canvas.Canvas(output)
    c.setFont('song', 10)  # ÉèÖÃ×ÖÌå×ÖºÅ
    textobject = c.beginText()
    textobject.setTextOrigin(inch, 11*inch)
    with open("F://1.txt", "r", encoding='gbk', errors='ignore') as f:
        content = f.readlines()
    for i in content:
        textobject.textLines(i+"\n")
    for line in input:
        line = line.decode("utf8")
        textobject.textLine(line.strip())
    c.drawText(textobject)
    c.showPage()
    c.save()

if __name__ == '__main__':
    report = disk_report()
    create_pdf(report)