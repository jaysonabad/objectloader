projdir := ..\ObjectLoader
appname := objectloader
include := $(projdir)\include
source := $(projdir)\source
build_objects := $(projdir)\build\objects
build_debug := $(projdir)\build\debug

c_flags := -O3 -Wall -std=c++1z -static-libstdc++ -static-libgcc
windows_flag := -mwindows
link := -lglew32 -lglfw3dll -lopengl32 -lglu32 -lglut32 -lgdi32 -luser32 -lkernel32

objects := main.o objectloader.o

debug: $(objects)
	g++ -s $(c_flags) \
			$(build_objects)/objectloader.o \
			$(build_objects)/main.o \
			-o $(build_debug)/$(appname)


objectloader.o:
	g++ -c -I $(include) $(source)/objectloader.cpp -o $(build_objects)/objectloader.o

main.o:
	g++ -c -I $(include) $(source)/main.cpp -o $(build_objects)/main.o


test:
	$(build_debug)/$(appname)

clean:
	del $(build_objects)\*.o
	del $(build_debug)\*.exe
