libs := libtinyxml.a libzlib.a
#加载的额外库和路径
LDFLAGS = -L $(CURDIR)/tinyxml -ltinyxml -L $(CURDIR)/zlib -lzlib
#以SDL2选项编译
SDL2lib := -lSDL2_image -lSDL2 -ljpeg -lpng
#以c++11运行
c++11 := -std=c++11
#VPATH = tinyxml zlib
#增加头文件搜索路径
CPPFLAGS = -I tinyxml -I zlib
#files
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(subst .cpp,.o ,$(CPP_FILES))

all:$(libs) main
.PHONY:all

main : $(OBJ_FILES)
	 $(CXX) $(SDL2lib) $^ -o $@ $(LDFLAGS)

$(OBJ_FILES) : %.o : %.cpp
	 $(CXX) $(c++11) $(CPPFLAGS) -c $^
$(libs):
	cd $(CURDIR)/tinyxml;$(MAKE)
	 cd zlib;$(MAKE)
.PNONY : clean
clean:
	 rm -f *.o
	 rm -f main
	 cd tinyxml;make clean
	 cd zlib;make clean
