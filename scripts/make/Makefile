EXE = .exe
OBJ := main.o
#以SDL2进行编译
SDL2FLAGS := -lSDL2_gfx -lSDL2_image -lSDL2_image.dll -lSDL2_draw \
-lSDL2_ttf -lSDL2_ttf.dll -lSDL2_mixer -lSDL2_mixer.dll -lSDL2_net \
-lSDL2_net.dll -lmingw32 -lSDL2main -lSDL2 -lSDL2.dll
#SDL2链接库路径
SDL2LIBRARIES := -L F:\local\lib -L F:\local\bin
#SDL2头文件搜索路径
INCLUDES := -I F:\local\include

.PHONY:all
all : main$(EXE)
main$(EXE) : $(OBJ)
	$(CXX) $(SDL2LIBRARIES) $(SDL2FLAGS) $^ -o $@
$(OBJ) : %.o : %.cpp
	$(CXX) $(INCLUDES) -c $<

