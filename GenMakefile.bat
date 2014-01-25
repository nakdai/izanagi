set MSBUILD="C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe"
set MAKEITSO="External\makeitso\output\MakeItSo.exe"

if not exist %MAKEITSO% (
    %MSBUILD% External\makeitso\MakeItSo.sln /t:Build /p:Configuration=Release || goto error
)

%MAKEITSO% -file=Libs\project\vs2010\izanagi.sln -config=MakeItSo.config

copy /Y Libs\project\vs2010\*.makefile Libs\project\makefile\
copy /Y Libs\project\vs2010\Makefile Libs\project\makefile\

@echo off
exit /b 1

:error
@echo off
echo "Error====="
pause
