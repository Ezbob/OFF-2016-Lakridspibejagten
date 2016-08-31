VPATH=src
OS=$(shell uname)

ifeq ($(OS),Linux)
	CXXFLAGS=-std=c++14 -Os --whole-program -Wall -Wpedantic -m32
else
	CXXFLAGS=-std=c++14 -Wall -Wpedantic -m32
endif

tetris: tetris.cc data.h
	$(CXX) $(CXXFLAGS) -lsfml-graphics -lsfml-system -lsfml-window -o $@ $<
	strip tetris

clean:
	$(RM) tetris tetris.o
