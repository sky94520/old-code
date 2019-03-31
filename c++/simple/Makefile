libs := libtinyxml.a libzlib.a
LDFLAGS = -L. -ltinyxml -L. -lzlib
SDL2lib := -lSDL2_image -lSDL2 -ljpeg -lpng
cpp_flags := -std=c++11
#files
CPP_FILES := $(wildcard *.cpp)
HEAD_FILES := $(subst .cpp,.h , $(CPP_FILES))
OBJ_FILES := $(filter-out main.o ,$(subst .cpp,.o ,$(CPP_FILES)))

all:$(libs) main
.PHONY:all

main : main.o $(OBJ_FILES)
	 $(CXX) $(SDL2lib) $^ -o $@ $(LDFLAGS)
main.o : main.cpp
	 $(CXX) $(cpp_flags) -c $<
$(OBJ_FILES) : %.o : %.h %.cpp
	 $(CXX) $(cpp_flags) -c $^
$(libs):
	 cd tinyxml;$(MAKE)
	 cd tinyxml;mv -f libtinyxml.a ../
	 cd zlib;$(MAKE)
	 cd zlib;mv -f libzlib.a ../