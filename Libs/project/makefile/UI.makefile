# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_GLUT_Include_Path=-I"../../include" -I"../../../External/glew/include" -I"../../../External/freeglut/include" 

# Library paths...
Debug_GLUT_Library_Path=

# Additional libraries...
Debug_GLUT_Libraries=

# Preprocessor definitions...
Debug_GLUT_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _LIB -D __IZ_DEBUG__ -D __IZ_OGL__ -D __IZ_GLUT__ -D __IZANAGI_NO_USE_D3D__ 

# Implictly linked object files...
Debug_GLUT_Implicitly_Linked_Objects=

# Compiler flags...
Debug_GLUT_Compiler_Flags=-O0 

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Debug_GLUT 

# Builds the Debug_GLUT configuration...
.PHONY: Debug_GLUT
Debug_GLUT: create_folders gccDebug_GLUT/source/ui/GestureDetector.o gccDebug_GLUT/source/ui/VelocityTracker.o 
	ar rcs ../lib/gccDebug_GLUT/libUI.a gccDebug_GLUT/source/ui/GestureDetector.o gccDebug_GLUT/source/ui/VelocityTracker.o  $(Debug_GLUT_Implicitly_Linked_Objects)

# Compiles file ../../source/ui/GestureDetector.cpp for the Debug_GLUT configuration...
-include gccDebug_GLUT/source/ui/GestureDetector.d
gccDebug_GLUT/source/ui/GestureDetector.o: ../../source/ui/GestureDetector.cpp
	$(CPP_COMPILER) $(Debug_GLUT_Preprocessor_Definitions) $(Debug_GLUT_Compiler_Flags) -c ../../source/ui/GestureDetector.cpp $(Debug_GLUT_Include_Path) -o gccDebug_GLUT/source/ui/GestureDetector.o
	$(CPP_COMPILER) $(Debug_GLUT_Preprocessor_Definitions) $(Debug_GLUT_Compiler_Flags) -MM ../../source/ui/GestureDetector.cpp $(Debug_GLUT_Include_Path) > gccDebug_GLUT/source/ui/GestureDetector.d

# Compiles file ../../source/ui/VelocityTracker.cpp for the Debug_GLUT configuration...
-include gccDebug_GLUT/source/ui/VelocityTracker.d
gccDebug_GLUT/source/ui/VelocityTracker.o: ../../source/ui/VelocityTracker.cpp
	$(CPP_COMPILER) $(Debug_GLUT_Preprocessor_Definitions) $(Debug_GLUT_Compiler_Flags) -c ../../source/ui/VelocityTracker.cpp $(Debug_GLUT_Include_Path) -o gccDebug_GLUT/source/ui/VelocityTracker.o
	$(CPP_COMPILER) $(Debug_GLUT_Preprocessor_Definitions) $(Debug_GLUT_Compiler_Flags) -MM ../../source/ui/VelocityTracker.cpp $(Debug_GLUT_Include_Path) > gccDebug_GLUT/source/ui/VelocityTracker.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug_GLUT/source/ui
	mkdir -p ../lib/gccDebug_GLUT

# Cleans intermediate and output files (objects, libraries, executables)...
.PHONY: clean
clean:
	rm -f gccDebug_GLUT/source/ui/*.o
	rm -f gccDebug_GLUT/source/ui/*.d
	rm -f ../lib/gccDebug_GLUT/libUI.a

