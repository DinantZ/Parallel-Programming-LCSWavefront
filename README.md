# LCSWavefront

Университетски проект за намиране на най-дългата обща подредица (LCS) чрез динамично програмиране.

## Структура

- `src/sequential.cpp` — последователна реализация и възстановяване на LCS.
- `src/openmp.cpp` — стартиране на OpenMP версията.
- `src/openmp_lcs.cpp` — OpenMP wavefront алгоритъмът с tiles по антидиагонали.
- `src/mpi.cpp` — разпределяне на колоните и предаване на гранични стойности между процесите.
- `analysis/benchmark.cpp` — Sequential сравнение и измерване на пет OpenMP tile размера.
- `analysis/README.md` — кратък анализ на pipeline fill/drain и MPI команди за различен брой процеси.
- `include/lcs.h` — общ Sequential алгоритъм.
- `include/lcs_openmp.h` — декларация на OpenMP алгоритъма.
- `include/test_input.h` — общ генератор за еднакви възпроизводими входни низове.
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

Sequential и OpenMP примерните програми използват низовете `ABCBDAB` и `BDCABA`. Benchmark и MPI програмите използват еднаква възпроизводима двойка низове с дължина 2000.

```text
.\build\Release\lcs_sequential.exe
.\build\Release\lcs_openmp.exe
.\build\Release\lcs_benchmark.exe
& "C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -n 4 .\build\Release\lcs_mpi.exe
```

Очакваната дължина на LCS за примерните низове е 4, а една възможна подредица е `BCBA`.

Sequential извежда дължината и подредицата. OpenMP извежда същия резултат и време за изпълнение. MPI извежда LCS дължината и времето на най-бавния процес. Benchmark сравнява Sequential времето с пет OpenMP tile размера върху еднакви низове с дължина 2000.

За Analysis на MPI pipeline fill/drain и командите с 1, 2 и 4 процеса виж `analysis/README.md`.

За да пробваш други примерни низове, промени `x` и `y` в `src/sequential.cpp` и `src/openmp.cpp`. Дължината на генерираните benchmark и MPI входове се задава чрез `input_length`.
