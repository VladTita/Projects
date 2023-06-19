CXX := g++
#CPPFLAGS := preprocessor flags, e.g. -I and -D
CXXFLAGS := -g -Wall -pedantic -Wextra -Wfatal-errors -std=c++11 -MD -MP -O0

SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
DEPFILES:= $(OBJECTS:.o=.d)

all: run

# Link the executable
run: $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o run $(LIBS)

launch:
	./run

-include $(DEPFILES)