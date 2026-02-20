@echo off
set /p projName="Enter New Project Name: "

echo Creating Asphalt Project: %projName%...

:: 1. Create Folder Structure
mkdir "%projName%"
mkdir "%projName%\assets"
mkdir "%projName%\include"
mkdir "%projName%\lib"

:: 2. Copy Engine Cores
:: copy "engine_base\actors" "%projName%\include\"
copy "engine_base\build.bat" "%projName%\"
copy "engine_base\build_terminal.bat" "%projName%\"
copy "engine_base\config.bat" "%projName%\"
copy "engine_base\main.cpp" "%projName%\"

:: 3. Copy Raylib
xcopy "engine_base\lib" "%projName%\lib" /E /I /Y
xcopy "engine_base\include" "%projName%\include\" /Y

echo.
echo Project %projName% is ready! 
echo (Edit the config.bat file)
pause