# LCSWavefront

Университетски проект за намиране на най-дългата обща подредица (LCS) чрез динамично програмиране.

## Структура

- `src/sequential.cpp` — последователна реализация и възстановяване на LCS.
- `src/openmp.cpp` — обработка на DP таблицата по антидиагонали от плочки.
- `src/mpi.cpp` — разпределяне на колоните и предаване на гранични стойности между процесите.
- `analysis/benchmark.cpp` — измерване на Sequential изпълнението за генерирани входове.
- `include/lcs.h` — общ Sequential алгоритъм.
- `CMakeLists.txt` — конфигурация за компилация.

Проектът изисква налични OpenMP и MPI библиотеки.

## Компилиране

Отвори от Start менюто `Developer PowerShell for VS 2022` и изпълни:

```text
cd "$env:USERPROFILE\Desktop\LCSWavefront"
cmake -S . -B build
cmake --build build --config Release
```

Готовите програми се намират в `build/Release`.

## Стартиране и проверка

Примерните низове са зададени директно в изходния код: `ABCBDAB` и `BDCABA`.

```text
.\build\Release\lcs_sequential.exe
.\build\Release\lcs_openmp.exe
.\build\Release\lcs_benchmark.exe
& "C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -n 4 .\build\Release\lcs_mpi.exe
```

Очакваната дължина на LCS за примерните низове е 4, а една възможна подредица е `BCBA`.

Sequential извежда дължината и подредицата. OpenMP извежда същия резултат и време за изпълнение. MPI извежда дължината и време за изпълнение. Benchmark измерва Sequential алгоритъма върху генерирани низове с дължина 2000.

За да пробваш други входни низове, промени стойностите на `x` и `y` в `src/sequential.cpp`, `src/openmp.cpp` и `src/mpi.cpp`, след което отново изпълни командата за компилиране.
