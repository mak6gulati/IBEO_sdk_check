@echo off
set baseFolder=%cd%
set cmakeArgs=-DCMAKE_GENERATOR_PLATFORM=x64
set configuration=Debug

rem some requirement checks
if "%BOOST_ROOT%"=="" (
    echo 'BOOST_ROOT' environment variable not set!
    exit /b
)
if "%LIBJPEG_ROOT%"=="" (
    echo 'LIBJPEG_ROOT' environment variable not set!
    exit /b
)
where /q msbuild
IF ERRORLEVEL 1 (
    ECHO msbuild is missing. Ensure you run this script in a msbuild or native command prompt.
    EXIT /B
)

rem Create target folder.
set targetFolder=%baseFolder%\target

if not exist %targetFolder% md %targetFolder%
cd %targetFolder%

rem tinyxml2
md tinyxml2-6.2.0
cd tinyxml2-6.2.0
cmake %cmakeArgs% %baseFolder%\tinyxml2-6.2.0
msbuild tinyxml2.sln /p:Configuration=%configuration%
set tinyxml2_DIR=%targetFolder%\tinyxml2-6.2.0
cd ..

rem cmake-extensions
set cmakeExtDir=%baseFolder%\ibeo-cmake-extensions

rem logging
md logging
cd logging
cmake %cmakeArgs% -D tinyxml2_DIR=$tinyxml2_DIR %baseFolder%\logging\source -D ibeo-cmake-extensions_DIR=%cmakeExtDir%
msbuild ibeo-common-logging.sln /p:Configuration=%configuration%
set logging_DIR=%targetFolder%\logging
cd ..

rem pause
echo Please wait ...
@ping -n 10 localhost> nul

rem sdk
md sdk
cd sdk
cmake %cmakeArgs% -D JPEG_INCLUDE_DIR="%LIBJPEG_ROOT%\include" -D JPEG_LIBRARY="%LIBJPEG_ROOT%\lib\jpeg.lib" -D tinyxml2_DIR="%tinyxml2_DIR%" -D ibeo-common-logging_DIR="%logging_DIR%" -D ibeo-cmake-extensions_DIR="%cmakeExtDir%" "%baseFolder%\sdk\source"
msbuild ibeo-common-sdk.sln /p:Configuration=%configuration%
set sdk_DIR=%targetFolder%\sdk
cd ..

rem pause
echo Please wait ...
@ping -n 10 localhost> nul

rem sdk_demos
mkdir sdk_demos
cd sdk_demos
cmake %cmakeArgs% -D JPEG_INCLUDE_DIR="%LIBJPEG_ROOT%\include" -D JPEG_LIBRARY="%LIBJPEG_ROOT%\lib\jpeg.lib" -D tinyxml2_DIR="%tinyxml2_DIR%" -D ibeo-common-logging_DIR="%logging_DIR%" -D ibeo-common-sdk_DIR="%sdk_DIR%" -D ibeo-cmake-extensions_DIR="%cmakeExtDir%" "%baseFolder%\sdk_demos\source"
msbuild ibeo-common-sdk_demos.sln /p:Configuration=%configuration%
cd ..

rem pause
echo Please wait ...
@ping -n 10 localhost> nul

rem sdk_tools
mkdir sdk_tools
cd sdk_tools
cmake %cmakeArgs% -D JPEG_INCLUDE_DIR="%LIBJPEG_ROOT%\include" -D JPEG_LIBRARY="%LIBJPEG_ROOT%\lib\jpeg.lib" -D tinyxml2_DIR="%tinyxml2_DIR%" -D ibeo-common-logging_DIR="%logging_DIR%" -D ibeo-common-sdk_DIR="%sdk_DIR%" -D ibeo-cmake-extensions_DIR="%cmakeExtDir%" "%baseFolder%\sdk_tools\source"
msbuild ibeo-common-sdk_tools.sln /p:Configuration=%configuration%
cd ..


cd %baseFolder%
