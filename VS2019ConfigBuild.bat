call cmake -B build_MSVC -G "Visual Studio 16 2019" -A x64
call cmake --build build_MSVC --config Release
PAUSE