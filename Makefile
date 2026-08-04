CXX = g++
CXXFLAGS = -Wall -Wextra \
					 -std=c++17 \
					 -Iinclude \
					 -Iinclude/Alegengine/third-party \
					 -MMD -MP \
					 -I$(EMBED_DIR) \
					 -O2
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
MAIN_SRC = src/main.cpp src/WindowOpener.cpp
ENGINE_CPP_SRC = $(wildcard include/Alegengine/src/*.cpp)
ENGINE_C_SRC = $(wildcard include/Alegengine/src/*.c)

MAIN_OBJ = $(MAIN_SRC:src/%.cpp=$(OBJDIR)/src/%.o)
ENGINE_CPP_OBJ = $(ENGINE_CPP_SRC:include/Alegengine/src/%.cpp=$(OBJDIR)/AlegengineSrc/%.o)
ENGINE_C_OBJ = $(ENGINE_C_SRC:include/Alegengine/src/%.c=$(OBJDIR)/AlegengineSrc/%.o)

OBJ = $(MAIN_OBJ) $(ENGINE_CPP_OBJ) $(ENGINE_C_OBJ)
DEPS = $(OBJ:.o=.d)

# Embed stuff
EMBED_SCRIPT = include/Alegengine/tools/EmbedFile.py
EMBED_DIR = build/embedded

# Collect every asset you want embedded
SHADER_SOURCES = $(wildcard shaders/*.glsl)
TEXTURE_SOURCES = $(wildcard textures/*.png)
SOUND_SOURCES = $(wildcard sounds/*.wav)
FONT_SOURCES = $(wildcard fonts/*.ttf)

SHADER_HEADERS = $(patsubst shaders/%.glsl, $(EMBED_DIR)/shaders/%.h, $(SHADER_SOURCES))
TEXTURE_HEADERS = $(patsubst textures/%.png, $(EMBED_DIR)/textures/%.h, $(TEXTURE_SOURCES))
SOUND_HEADERS = $(patsubst sounds/%.wav, $(EMBED_DIR)/sounds/%.h, $(SOUND_SOURCES))
FONT_HEADERS = $(patsubst fonts/%.ttf, $(EMBED_DIR)/fonts/%.h, $(FONT_SOURCES))

EMBEDDED_HEADERS = $(SHADER_HEADERS) $(TEXTURE_HEADERS) $(SOUND_HEADERS) $(FONT_HEADERS)

$(EMBED_DIR)/shaders/%.h: shaders/%.glsl $(EMBED_SCRIPT)
	mkdir -p $(dir $@)
	python3 $(EMBED_SCRIPT) $< $(subst .,_,$(subst /,_,$*))_glsl $@

$(EMBED_DIR)/textures/%.h: textures/%.png $(EMBED_SCRIPT)
	mkdir -p $(dir $@)
	python3 $(EMBED_SCRIPT) $< $(subst .,_,$(subst /,_,$*))_png $@

$(EMBED_DIR)/sounds/%.h: sounds/%.wav $(EMBED_SCRIPT)
	mkdir -p $(dir $@)
	python3 $(EMBED_SCRIPT) $< $(subst .,_,$(subst /,_,$*))_wav $@

$(EMBED_DIR)/fonts/%.h: fonts/%.ttf $(EMBED_SCRIPT)
	mkdir -p $(dir $@)
	python3 $(EMBED_SCRIPT) $< $(subst .,_,$(subst /,_,$*))_ttf $@

all: $(EMBEDDED_HEADERS) $(TARGET)

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

test: CXXFLAGS += -DALEG_DEBUG -g
test: all
	gdb -q -batch -x debug.gdb --args ./$(TARGET)

clean:
	rm -rf build
	rm -f $(TARGET)

.PHONY: all test clean
