# Native Linux build of the AVP2 OpenGL renderer: opengl.ren as a 32-bit ELF shared object.
#   make -j$(nproc)          (needs: g++-multilib libsdl2-dev:i386? no - only libgl1:i386 at runtime; imgui checked out in IMGUI)
IMGUI ?= ../imgui
CXX   ?= g++
OPT   ?= -O2
CXXFLAGS = -m32 -std=c++17 $(OPT) -fPIC -w -mstackrealign -fno-strict-aliasing -fno-delete-null-pointer-checks -DAVP2_LINUX=1 -DNDEBUG \
           -Iwinport -Isrc -I$(IMGUI) -I$(IMGUI)/backends -fvisibility=default
SRC  := $(shell find src -name '*.cpp' ! -name dllmain_win.cpp) winport/winport.cpp winport/imgui_impl_winport.cpp
IMG  := $(IMGUI)/imgui.cpp $(IMGUI)/imgui_draw.cpp $(IMGUI)/imgui_tables.cpp $(IMGUI)/imgui_widgets.cpp $(IMGUI)/backends/imgui_impl_opengl3.cpp
OBJ  := $(patsubst %.cpp,build/%.o,$(SRC)) $(patsubst $(IMGUI)/%.cpp,build/imgui/%.o,$(IMG))
all: opengl.ren
src/shader_table.cpp: gen_shaders.py src/resources/opengl.rc.in $(wildcard src/resources/shaders/*.glsl)
	python3 gen_shaders.py src
build/%.o: %.cpp src/shader_table.cpp
	@mkdir -p $(dir $@) && $(CXX) $(CXXFLAGS) -MMD -c $< -o $@
build/imgui/%.o: $(IMGUI)/%.cpp
	@mkdir -p $(dir $@) && $(CXX) $(CXXFLAGS) -c $< -o $@
# The engine looks up the three renderer entry points by their original names.
opengl.ren: $(OBJ)
	$(CXX) -m32 -shared -o $@ $(OBJ) -static-libstdc++ -static-libgcc -l:libGL.so.1 -ldl -lpthread \
	  -Wl,--defsym=GetSupportedModes=rdll_GetSupportedModes -Wl,--defsym=FreeModeList=rdll_FreeModeList -Wl,--defsym=RenderDLLSetup=rdll_RenderDLLSetup \
	  -Wl,-soname,opengl.ren
clean: ; rm -rf build opengl.ren
-include $(OBJ:.o=.d)
