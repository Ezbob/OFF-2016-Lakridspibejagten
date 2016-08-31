CXXFLAGS=--std=c++14 -O3 -Wall -Wpedantic -Wextra
SOURCE=$(shell find . -type f -iname *.cc)
OBJECTS=$(patsubst %.cc,%.o,$(SOURCE))
EXE=$(shell basename `pwd`)

MACHINE=$(shell gcc -dumpmachine)

ifeq (linux,$(findstring linux,$(MACHINE)))
	EXTENSION=
endif

TARGET=$(EXE)$(EXTENSION)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

clean:
	$(RM) $(TARGET) $(OBJECTS)
