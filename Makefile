CXXFLAGS=--std=c++14 -O3 -Wall -Wpedantic -Wextra 
SOURCE=$(shell find . -type f -iname *.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCE))
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
	
