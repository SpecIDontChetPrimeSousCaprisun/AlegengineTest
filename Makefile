CXX = g++
CXXFLAGS = -Wall -Wextra \
					 -std=c++17 \
					 -Iinclude \
					 -Iinclude/Alegengine/third-party \
					 -MMD -MP
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

OBJDIR = build

# Gather sources properly (see note below on wildcard)
MAIN_SRC = src/main.cpp
ENGINE_CPP_SRC = $(wildcard include/Alegengine/src/*.cpp)
ENGINE_C_SRC = $(wildcard include/Alegengine/src/*.c)

MAIN_OBJ = $(MAIN_SRC:src/%.cpp=$(OBJDIR)/src/%.o)
ENGINE_CPP_OBJ = $(ENGINE_CPP_SRC:include/Alegengine/src/%.cpp=$(OBJDIR)/AlegengineSrc/%.o)
ENGINE_C_OBJ = $(ENGINE_C_SRC:include/Alegengine/src/%.c=$(OBJDIR)/AlegengineSrc/%.o)

OBJ = $(MAIN_OBJ) $(ENGINE_CPP_OBJ) $(ENGINE_C_OBJ)
DEPS = $(OBJ:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LIBS)

$(OBJDIR)/src/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/AlegengineSrc/%.o: include/Alegengine/src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/AlegengineSrc/%.o: include/Alegengine/src/%.c
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Pull in auto-generated header dependencies, if they exist
-include $(DEPS)

test: CXXFLAGS += -DALEG_DEBUG
test: all
	./$(TARGET)

clean:
	rm -rf build
	rm -f $(TARGET)

.PHONY: all test clean
