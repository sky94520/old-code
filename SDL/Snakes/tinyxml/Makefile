CPP_FILES := $(wildcard *.cpp)
OBJ := $(subst .cpp,.o,$(CPP_FILES))

libtinyxml.a:$(OBJ)
	 ar rs $@ $^
$(OBJ):$(CPP_FILES)
	 $(CXX) -c $^
.PHONY : clean
clean :
	 rm -f libtinyxml.a
	 rm -f *.o 