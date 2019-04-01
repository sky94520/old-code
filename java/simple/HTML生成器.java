import webbrowser
def textTohtml(target,txtpath):
    GEN_HTML = "%s.html" %target
    f = open(GEN_HTML, 'w')
    with open(txtpath,'r',encoding='gbk', errors='ignore') as ff:
        content = ff.readlines()
    for i in content:
            f.write(i+"\n")
    f.close()
# 运行完自动在网页中显示
    webbrowser.open(GEN_HTML, new=1)

if __name__ == '__main__':
    textTohtml("test","F://1.txt")