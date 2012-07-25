set MSBUILD="C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe"
set TARGET=Rebuild

%MSBUILD% External\Preproc\Preproc_VC10.sln /t:%TARGET% /p:Configuration=Release || goto error
%MSBUILD% External\NvTriStrip\src\NvTriStrip\NvTriStrip_VC10.sln /t:%TARGET% /p:Configuration=Release || goto error
%MSBUILD% External\xerces\projects\Win32\VC10\xerces-all\xerces-all.sln /t:XercesLib:%TARGET% /p:Configuration=Release || goto error
%MSBUILD% External\squish\vs10\squish.sln /t:squish:%TARGET% /p:Configuration=Release || goto error
%MSBUILD% External\collada-dom-2.4.0\dom\projects\vc10-1.4\dom.sln /t:dom-static:%TARGET% /p:Configuration=Release || goto error

@echo off
exit /b 1

:error
@echo off
echo "Error====="
pause