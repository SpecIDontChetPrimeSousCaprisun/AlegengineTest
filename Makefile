CXX = g++
CXXFLAGS = -Wall -Wextra \
					 -std=c++17 \
					 -Iinclude \
					 -Iinclude/Alegengine/third-party

TARGET = game

LIBS = -lglfw \
  -lGL \
  -ldl \
  -lpthread \
  -lX11 \
  -lXrandr \
  -lXi \
  -lXxf86vm \
  -lXcursor \
  -lm

SRC = src/main.cpp \
			include/Alegengine/src/*

OBJDIR = build

OBJ = $(SRC:src/%.cpp=$(OBJDIR)/src/%.o)
OBJ := $(OBJ:include/Alegengine/src/glad.c=$(OBJDIR)/AlegengineSrc/glad.o)
OBJ := $(OBJ:include/Alegengine/src/%.cpp=$(OBJDIR)/AlegengineSrc/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LIBS)

$(OBJDIR)/src/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/AlegengineSrc/glad.o: include/Alegengine/src/glad.c
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/AlegengineSrc/%.o: include/Alegengine/src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: all
	./$(TARGET)

clean:
	rm -rf build
	rm $(TARGET)

.PHONY: all test clean
