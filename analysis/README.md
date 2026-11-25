# Analysis

## OpenMP tile size

Run `lcs_benchmark.exe` to compare the Sequential time with OpenMP tile sizes 16, 32, 64, 128, and 256. The program uses the same reproducible pair of 2,000-character strings for every run.

The fastest tile size in this list is the best tested size for this input and computer. It is not a universal optimum.

One sample run on this computer used 6 OpenMP threads and found 128 to be the fastest tested tile size:

| Run | Time (seconds) |
|---|---:|
| Sequential | 0.01774 |
| OpenMP, tile 16 | 0.01358 |
| OpenMP, tile 32 | 0.01268 |
| OpenMP, tile 64 | 0.01203 |
| OpenMP, tile 128 | 0.01190 |
| OpenMP, tile 256 | 0.01219 |

These are single-run example measurements; timing can vary between runs.

## MPI pipeline fill and drain

Each MPI process is one pipeline stage and each DP row is one work item. A row starts at rank 0 and its boundary values pass through the remaining column blocks. While later ranks process that row, earlier ranks can begin the next row.

With `P` ranks, the first row needs about `P - 1` stage delays to reach the last rank. This is the pipeline fill. After rank 0 sends the final row, that row still needs about `P - 1` stage delays to reach the last rank. This is the drain.

For four ranks, fill and drain each take about three stage delays. This is a simple model; actual times also include message and scheduling overhead.

Run MPI with different rank counts from PowerShell:

```powershell
& "C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -n 1 .\build\Release\lcs_mpi.exe
& "C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -n 2 .\build\Release\lcs_mpi.exe
& "C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -n 4 .\build\Release\lcs_mpi.exe
```

The program reports the maximum elapsed time across the MPI processes, so rank counts can be compared using the same input length.

One sample run gave these MPI times:

| MPI ranks | Time (seconds) | LCS length |
|---:|---:|---:|
| 1 | 0.00957 | 642 |
| 2 | 0.00595 | 642 |
| 4 | 0.00395 | 642 |

This table shows how the MPI version scaled across rank counts on this computer. MPI reports the LCS length only, while Sequential and OpenMP also restore the sequence, so compare MPI timings across rank counts rather than directly against their times.
