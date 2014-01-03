# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_GLES2_Include_Path=-I"include" -I"../../../External/pthreads/pthreads.2" -I"../../include" 
Release_GLES2_Include_Path=-I"include" -I"../../../External/pthreads/pthreads.2" -I"../../include" 

# Library paths...
Debug_GLES2_Library_Path=
Release_GLES2_Library_Path=

# Additional libraries...
Debug_GLES2_Libraries=
Release_GLES2_Libraries=

# Preprocessor definitions...
Debug_GLES2_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _LIB -D __IZ_DEBUG__ -D __IZ_GLES2__ -D __IZANAGI_NO_USE_D3D__ 
Release_GLES2_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _LIB -D __IZ_GLES2__ -D __IZANAGI_NO_USE_D3D__ 

# Implictly linked object files...
Debug_GLES2_Implicitly_Linked_Objects=
Release_GLES2_Implicitly_Linked_Objects=

# Compiler flags...
Debug_GLES2_Compiler_Flags=-O0 
Release_GLES2_Compiler_Flags=-O2 

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Debug_GLES2 Release_GLES2 

# Builds the Debug_GLES2 configuration...
.PHONY: Debug_GLES2
Debug_GLES2: create_folders gccDebug_GLES2/source/system/Pad.o gccDebug_GLES2/source/system/win32/SysEnvironment_win32 .o gccDebug_GLES2/source/system/win32/SysTimer_win32.o gccDebug_GLES2/source/system/win32/SysUtil_win32.o gccDebug_GLES2/source/system/win32/SysWindow_win32.o gccDebug_GLES2/source/system/win32/thread/SysEvent_win32.o gccDebug_GLES2/source/system/win32/thread/SysMutex_win32.o gccDebug_GLES2/source/system/win32/thread/SysSemaphore_win32.o gccDebug_GLES2/source/system/win32/thread/SysThread_win32.o gccDebug_GLES2/source/system/win32/device/DeviceUtil.o gccDebug_GLES2/source/system/win32/device/Pad_DInput.o gccDebug_GLES2/source/system/win32/device/Pad_XInput.o 
	ar rcs ../lib/gccDebug_GLES2/libSystem.a gccDebug_GLES2/source/system/Pad.o gccDebug_GLES2/source/system/win32/SysEnvironment_win32 .o gccDebug_GLES2/source/system/win32/SysTimer_win32.o gccDebug_GLES2/source/system/win32/SysUtil_win32.o gccDebug_GLES2/source/system/win32/SysWindow_win32.o gccDebug_GLES2/source/system/win32/thread/SysEvent_win32.o gccDebug_GLES2/source/system/win32/thread/SysMutex_win32.o gccDebug_GLES2/source/system/win32/thread/SysSemaphore_win32.o gccDebug_GLES2/source/system/win32/thread/SysThread_win32.o gccDebug_GLES2/source/system/win32/device/DeviceUtil.o gccDebug_GLES2/source/system/win32/device/Pad_DInput.o gccDebug_GLES2/source/system/win32/device/Pad_XInput.o  $(Debug_GLES2_Implicitly_Linked_Objects)

# Compiles file ../../source/system/Pad.cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/Pad.d
gccDebug_GLES2/source/system/Pad.o: ../../source/system/Pad.cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/Pad.cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/Pad.o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/Pad.cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/Pad.d

# Compiles file ../../source/system/win32/SysEnvironment_win32 .cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/win32/SysEnvironment_win32 .d
gccDebug_GLES2/source/system/win32/SysEnvironment_win32 .o: ../../source/system/win32/SysEnvironment_win32 .cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/win32/SysEnvironment_win32 .cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/win32/SysEnvironment_win32 .o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/win32/SysEnvironment_win32 .cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/win32/SysEnvironment_win32 .d

# Compiles file ../../source/system/win32/SysTimer_win32.cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/win32/SysTimer_win32.d
gccDebug_GLES2/source/system/win32/SysTimer_win32.o: ../../source/system/win32/SysTimer_win32.cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/win32/SysTimer_win32.cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/win32/SysTimer_win32.o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/win32/SysTimer_win32.cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/win32/SysTimer_win32.d

# Compiles file ../../source/system/win32/SysUtil_win32.cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/win32/SysUtil_win32.d
gccDebug_GLES2/source/system/win32/SysUtil_win32.o: ../../source/system/win32/SysUtil_win32.cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/win32/SysUtil_win32.cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/win32/SysUtil_win32.o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/win32/SysUtil_win32.cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/win32/SysUtil_win32.d

# Compiles file ../../source/system/win32/SysWindow_win32.cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/win32/SysWindow_win32.d
gccDebug_GLES2/source/system/win32/SysWindow_win32.o: ../../source/system/win32/SysWindow_win32.cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/win32/SysWindow_win32.cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/win32/SysWindow_win32.o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/win32/SysWindow_win32.cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/win32/SysWindow_win32.d

# Compiles file ../../source/system/win32/thread/SysEvent_win32.cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/win32/thread/SysEvent_win32.d
gccDebug_GLES2/source/system/win32/thread/SysEvent_win32.o: ../../source/system/win32/thread/SysEvent_win32.cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/win32/thread/SysEvent_win32.cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/win32/thread/SysEvent_win32.o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/win32/thread/SysEvent_win32.cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/win32/thread/SysEvent_win32.d

# Compiles file ../../source/system/win32/thread/SysMutex_win32.cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/win32/thread/SysMutex_win32.d
gccDebug_GLES2/source/system/win32/thread/SysMutex_win32.o: ../../source/system/win32/thread/SysMutex_win32.cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/win32/thread/SysMutex_win32.cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/win32/thread/SysMutex_win32.o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/win32/thread/SysMutex_win32.cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/win32/thread/SysMutex_win32.d

# Compiles file ../../source/system/win32/thread/SysSemaphore_win32.cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/win32/thread/SysSemaphore_win32.d
gccDebug_GLES2/source/system/win32/thread/SysSemaphore_win32.o: ../../source/system/win32/thread/SysSemaphore_win32.cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/win32/thread/SysSemaphore_win32.cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/win32/thread/SysSemaphore_win32.o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/win32/thread/SysSemaphore_win32.cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/win32/thread/SysSemaphore_win32.d

# Compiles file ../../source/system/win32/thread/SysThread_win32.cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/win32/thread/SysThread_win32.d
gccDebug_GLES2/source/system/win32/thread/SysThread_win32.o: ../../source/system/win32/thread/SysThread_win32.cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/win32/thread/SysThread_win32.cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/win32/thread/SysThread_win32.o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/win32/thread/SysThread_win32.cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/win32/thread/SysThread_win32.d

# Compiles file ../../source/system/win32/device/DeviceUtil.cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/win32/device/DeviceUtil.d
gccDebug_GLES2/source/system/win32/device/DeviceUtil.o: ../../source/system/win32/device/DeviceUtil.cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/win32/device/DeviceUtil.cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/win32/device/DeviceUtil.o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/win32/device/DeviceUtil.cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/win32/device/DeviceUtil.d

# Compiles file ../../source/system/win32/device/Pad_DInput.cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/win32/device/Pad_DInput.d
gccDebug_GLES2/source/system/win32/device/Pad_DInput.o: ../../source/system/win32/device/Pad_DInput.cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/win32/device/Pad_DInput.cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/win32/device/Pad_DInput.o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/win32/device/Pad_DInput.cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/win32/device/Pad_DInput.d

# Compiles file ../../source/system/win32/device/Pad_XInput.cpp for the Debug_GLES2 configuration...
-include gccDebug_GLES2/source/system/win32/device/Pad_XInput.d
gccDebug_GLES2/source/system/win32/device/Pad_XInput.o: ../../source/system/win32/device/Pad_XInput.cpp
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -c ../../source/system/win32/device/Pad_XInput.cpp $(Debug_GLES2_Include_Path) -o gccDebug_GLES2/source/system/win32/device/Pad_XInput.o
	$(CPP_COMPILER) $(Debug_GLES2_Preprocessor_Definitions) $(Debug_GLES2_Compiler_Flags) -MM ../../source/system/win32/device/Pad_XInput.cpp $(Debug_GLES2_Include_Path) > gccDebug_GLES2/source/system/win32/device/Pad_XInput.d

# Builds the Release_GLES2 configuration...
.PHONY: Release_GLES2
Release_GLES2: create_folders gccRelease_GLES2/source/system/Pad.o gccRelease_GLES2/source/system/win32/SysEnvironment_win32 .o gccRelease_GLES2/source/system/win32/SysTimer_win32.o gccRelease_GLES2/source/system/win32/SysUtil_win32.o gccRelease_GLES2/source/system/win32/SysWindow_win32.o gccRelease_GLES2/source/system/win32/thread/SysEvent_win32.o gccRelease_GLES2/source/system/win32/thread/SysMutex_win32.o gccRelease_GLES2/source/system/win32/thread/SysSemaphore_win32.o gccRelease_GLES2/source/system/win32/thread/SysThread_win32.o gccRelease_GLES2/source/system/win32/device/DeviceUtil.o gccRelease_GLES2/source/system/win32/device/Pad_DInput.o gccRelease_GLES2/source/system/win32/device/Pad_XInput.o 
	ar rcs ../lib/gccRelease_GLES2/libSystem.a gccRelease_GLES2/source/system/Pad.o gccRelease_GLES2/source/system/win32/SysEnvironment_win32 .o gccRelease_GLES2/source/system/win32/SysTimer_win32.o gccRelease_GLES2/source/system/win32/SysUtil_win32.o gccRelease_GLES2/source/system/win32/SysWindow_win32.o gccRelease_GLES2/source/system/win32/thread/SysEvent_win32.o gccRelease_GLES2/source/system/win32/thread/SysMutex_win32.o gccRelease_GLES2/source/system/win32/thread/SysSemaphore_win32.o gccRelease_GLES2/source/system/win32/thread/SysThread_win32.o gccRelease_GLES2/source/system/win32/device/DeviceUtil.o gccRelease_GLES2/source/system/win32/device/Pad_DInput.o gccRelease_GLES2/source/system/win32/device/Pad_XInput.o  $(Release_GLES2_Implicitly_Linked_Objects)

# Compiles file ../../source/system/Pad.cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/Pad.d
gccRelease_GLES2/source/system/Pad.o: ../../source/system/Pad.cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/Pad.cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/Pad.o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/Pad.cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/Pad.d

# Compiles file ../../source/system/win32/SysEnvironment_win32 .cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/win32/SysEnvironment_win32 .d
gccRelease_GLES2/source/system/win32/SysEnvironment_win32 .o: ../../source/system/win32/SysEnvironment_win32 .cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/win32/SysEnvironment_win32 .cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/win32/SysEnvironment_win32 .o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/win32/SysEnvironment_win32 .cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/win32/SysEnvironment_win32 .d

# Compiles file ../../source/system/win32/SysTimer_win32.cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/win32/SysTimer_win32.d
gccRelease_GLES2/source/system/win32/SysTimer_win32.o: ../../source/system/win32/SysTimer_win32.cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/win32/SysTimer_win32.cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/win32/SysTimer_win32.o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/win32/SysTimer_win32.cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/win32/SysTimer_win32.d

# Compiles file ../../source/system/win32/SysUtil_win32.cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/win32/SysUtil_win32.d
gccRelease_GLES2/source/system/win32/SysUtil_win32.o: ../../source/system/win32/SysUtil_win32.cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/win32/SysUtil_win32.cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/win32/SysUtil_win32.o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/win32/SysUtil_win32.cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/win32/SysUtil_win32.d

# Compiles file ../../source/system/win32/SysWindow_win32.cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/win32/SysWindow_win32.d
gccRelease_GLES2/source/system/win32/SysWindow_win32.o: ../../source/system/win32/SysWindow_win32.cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/win32/SysWindow_win32.cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/win32/SysWindow_win32.o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/win32/SysWindow_win32.cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/win32/SysWindow_win32.d

# Compiles file ../../source/system/win32/thread/SysEvent_win32.cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/win32/thread/SysEvent_win32.d
gccRelease_GLES2/source/system/win32/thread/SysEvent_win32.o: ../../source/system/win32/thread/SysEvent_win32.cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/win32/thread/SysEvent_win32.cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/win32/thread/SysEvent_win32.o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/win32/thread/SysEvent_win32.cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/win32/thread/SysEvent_win32.d

# Compiles file ../../source/system/win32/thread/SysMutex_win32.cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/win32/thread/SysMutex_win32.d
gccRelease_GLES2/source/system/win32/thread/SysMutex_win32.o: ../../source/system/win32/thread/SysMutex_win32.cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/win32/thread/SysMutex_win32.cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/win32/thread/SysMutex_win32.o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/win32/thread/SysMutex_win32.cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/win32/thread/SysMutex_win32.d

# Compiles file ../../source/system/win32/thread/SysSemaphore_win32.cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/win32/thread/SysSemaphore_win32.d
gccRelease_GLES2/source/system/win32/thread/SysSemaphore_win32.o: ../../source/system/win32/thread/SysSemaphore_win32.cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/win32/thread/SysSemaphore_win32.cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/win32/thread/SysSemaphore_win32.o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/win32/thread/SysSemaphore_win32.cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/win32/thread/SysSemaphore_win32.d

# Compiles file ../../source/system/win32/thread/SysThread_win32.cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/win32/thread/SysThread_win32.d
gccRelease_GLES2/source/system/win32/thread/SysThread_win32.o: ../../source/system/win32/thread/SysThread_win32.cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/win32/thread/SysThread_win32.cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/win32/thread/SysThread_win32.o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/win32/thread/SysThread_win32.cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/win32/thread/SysThread_win32.d

# Compiles file ../../source/system/win32/device/DeviceUtil.cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/win32/device/DeviceUtil.d
gccRelease_GLES2/source/system/win32/device/DeviceUtil.o: ../../source/system/win32/device/DeviceUtil.cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/win32/device/DeviceUtil.cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/win32/device/DeviceUtil.o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/win32/device/DeviceUtil.cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/win32/device/DeviceUtil.d

# Compiles file ../../source/system/win32/device/Pad_DInput.cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/win32/device/Pad_DInput.d
gccRelease_GLES2/source/system/win32/device/Pad_DInput.o: ../../source/system/win32/device/Pad_DInput.cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/win32/device/Pad_DInput.cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/win32/device/Pad_DInput.o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/win32/device/Pad_DInput.cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/win32/device/Pad_DInput.d

# Compiles file ../../source/system/win32/device/Pad_XInput.cpp for the Release_GLES2 configuration...
-include gccRelease_GLES2/source/system/win32/device/Pad_XInput.d
gccRelease_GLES2/source/system/win32/device/Pad_XInput.o: ../../source/system/win32/device/Pad_XInput.cpp
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -c ../../source/system/win32/device/Pad_XInput.cpp $(Release_GLES2_Include_Path) -o gccRelease_GLES2/source/system/win32/device/Pad_XInput.o
	$(CPP_COMPILER) $(Release_GLES2_Preprocessor_Definitions) $(Release_GLES2_Compiler_Flags) -MM ../../source/system/win32/device/Pad_XInput.cpp $(Release_GLES2_Include_Path) > gccRelease_GLES2/source/system/win32/device/Pad_XInput.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug_GLES2/source/system
	mkdir -p gccDebug_GLES2/source/system/win32
	mkdir -p gccDebug_GLES2/source/system/win32/thread
	mkdir -p gccDebug_GLES2/source/system/win32/device
	mkdir -p ../lib/gccDebug_GLES2
	mkdir -p gccRelease_GLES2/source/system
	mkdir -p gccRelease_GLES2/source/system/win32
	mkdir -p gccRelease_GLES2/source/system/win32/thread
	mkdir -p gccRelease_GLES2/source/system/win32/device
	mkdir -p ../lib/gccRelease_GLES2

# Cleans intermediate and output files (objects, libraries, executables)...
.PHONY: clean
clean:
	rm -f gccDebug_GLES2/source/system/*.o
	rm -f gccDebug_GLES2/source/system/*.d
	rm -f gccDebug_GLES2/source/system/win32/*.o
	rm -f gccDebug_GLES2/source/system/win32/*.d
	rm -f gccDebug_GLES2/source/system/win32/thread/*.o
	rm -f gccDebug_GLES2/source/system/win32/thread/*.d
	rm -f gccDebug_GLES2/source/system/win32/device/*.o
	rm -f gccDebug_GLES2/source/system/win32/device/*.d
	rm -f ../lib/gccDebug_GLES2/libSystem.a
	rm -f gccRelease_GLES2/source/system/*.o
	rm -f gccRelease_GLES2/source/system/*.d
	rm -f gccRelease_GLES2/source/system/win32/*.o
	rm -f gccRelease_GLES2/source/system/win32/*.d
	rm -f gccRelease_GLES2/source/system/win32/thread/*.o
	rm -f gccRelease_GLES2/source/system/win32/thread/*.d
	rm -f gccRelease_GLES2/source/system/win32/device/*.o
	rm -f gccRelease_GLES2/source/system/win32/device/*.d
	rm -f ../lib/gccRelease_GLES2/libSystem.a
