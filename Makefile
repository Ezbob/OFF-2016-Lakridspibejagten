VPATH=src src/states
CXXFLAGS=-std=c++14 -O3 -Wall -Wpedantic -Wextra -Isrc/states -Isrc 
SOURCE=$(wildcard src/*.cpp)
STATES=$(wildcard src/states/*.cpp)
OBS=$(patsubst src/%,%,$(SOURCE)) $(patsubst src/states/%,%,$(STATES))
OBJECTS=$(patsubst %.cpp,%.o,$(OBS))
EXE=$(shell basename `pwd`)
LIBS= -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio

MACHINE=$(shell gcc -dumpmachine)

ifeq (linux,$(findstring linux,$(MACHINE)))
	EXTENSION=
endif

TARGET=$(EXE)$(EXTENSION)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

clean:
	$(RM) $(TARGET) $(OBJECTS)

deps:
	cc -MM $(SOURCE) > deps

-include deps
