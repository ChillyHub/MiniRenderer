call cmake -B build_MSVC -G "Visual Studio 17 2022" -A x64
call cmake --build build_MSVC --config Release
PAUSE