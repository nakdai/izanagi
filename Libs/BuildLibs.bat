@echo off

set CURDIR=%CD%

cd /d %~dp0

set MSBUILD="C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe"
set TARGET=Build
set CONFIG=%1
set GFX=%2

if %GFX%==GLES2 (
    %MSBUILD% ..\External\ANGLE\projects\src\ANGLE.sln /t:%TARGET% /p:Configuration=%CONFIG% /p:Platform=Win32 || goto error

    cd ..\Tools
    cd External
    call BuildMojoShader.bat Release
    cd ..
    %MSBUILD% External\Preproc\Preproc_VC10.sln /t:%TARGET% /p:Configuration=Release || goto error
    %MSBUILD% projects\vs2010\ShaderCompiler.sln /t:%TARGET% /p:Configuration=Release || goto error

    cd ..\Libs
)

if %GFX%==OGL (
    %MSBUILD% ..\External\glew\build\vc10\glew.sln /t:%TARGET% /p:Configuration=%CONFIG% /p:Platform=Win32 || goto error
    %MSBUILD% ..\External\freeglut\VisualStudio\2010\freeglut.sln /t:%TARGET% /p:Configuration=%CONFIG% /p:Platform=Win32 || goto error

    cd ..\Tools
    cd External
    call BuildMojoShader.bat Release
    cd ..
    %MSBUILD% External\Preproc\Preproc_VC10.sln /t:%TARGET% /p:Configuration=Release || goto error
    %MSBUILD% projects\vs2010\ShaderCompiler.sln /t:%TARGET% /p:Configuration=Release || goto error

    cd ..\Libs

    set GFX=GLUT
)

%MSBUILD% ..\External\freetype\builds\win32\vc2010\freetype.sln /t:%TARGET% /p:Configuration="%CONFIG% Multithreaded" || goto error

%MSBUILD% project\vs2010\izanagi.sln /t:%TARGET% /p:Configuration=%CONFIG%_%GFX% || goto error

set CURDIR=%CD%

exit /b 1

:error
set CURDIR=%CD%
echo "Error====="
pause
