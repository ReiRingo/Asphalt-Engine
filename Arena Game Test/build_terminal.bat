:: A console programme
@echo off
call config.bat
echo Building Game (%ProgrammeName%)...
g++ %Target% -o %ProgrammeName%.exe -I./include -L./lib -lraylib -lopengl32 -lgdi32 -lwinmm
if %ERRORLEVEL% EQU 0 (
    echo Build Successful! Running game...
    %ProgrammeName%.exe
) else (
    echo Build Failed! Check your code.
    pause
)