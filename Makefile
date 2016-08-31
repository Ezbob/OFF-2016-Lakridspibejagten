CXXFLAGS=--std=c++14 -O3 -Wall -Wpedantic -Wextra 
SOURCE=$(shell find . -type f -iname *.cc)
OBJECTS=$(patsubst %.cc,%.o,$(SOURCE))
EXE=$(shell basename `pwd`)
LIBS= -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio

MACHINE=$(shell gcc -dumpmachine)

ifeq (linux,$(findstring linux,$(MACHINE)))
	EXTENSION=
endif

TARGET=$(EXE)$(EXTENSION)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(LIBS)
	$(CXX) -o $@ $^

clean:
	$(RM) $(TARGET) $(OBJECTS)


clang++ -o breakout -std=c++11 -O3 -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio breakout.cpp