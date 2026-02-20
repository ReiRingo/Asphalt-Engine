:: A GUI programme
@echo off
call config.bat
echo Building Game (%ProgrammeName%)...
g++ %Target% -o %ProgrammeName%.exe -I./include -L./lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
if %ERRORLEVEL% EQU 0 (
    echo Build Successful! Running game...
    start %ProgrammeName%.exe
) else (
    echo Build Failed! Check your code.
    pause
)