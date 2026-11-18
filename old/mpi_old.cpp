#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, processes;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);

    const std::string x = "ABCBDAB";
    const std::string y = "BDCABA";
    int m = static_cast<int>(x.size()), n = static_cast<int>(y.size());

    const int start_col = 1 + (n * rank) / processes;
    const int end_col = (n * (rank + 1)) / processes;
    const int width = end_col - start_col + 1;
    std::vector<int> dp(static_cast<size_t>(m + 1) * (width + 1), 0);
    auto at = [&](int i, int local_j) -> int& { return dp[static_cast<size_t>(i) * (width + 1) + local_j]; };
    const double start = MPI_Wtime();

    for (int i = 1; i <= m; ++i) {
        int left = 0, diagonal = 0;
        if (rank > 0) {
            int boundary[2];
            MPI_Recv(boundary, 2, MPI_INT, rank - 1, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            left = boundary[0]; diagonal = boundary[1];
        }
        for (int local_j = 1; local_j <= width; ++local_j) {
            const int j = start_col + local_j - 1;
            const int top = at(i - 1, local_j);
            const int top_left = local_j == 1 ? diagonal : at(i - 1, local_j - 1);
            at(i, local_j) = x[i - 1] == y[j - 1] ? top_left + 1 : std::max(top, left);
            left = at(i, local_j);
        }
        if (rank + 1 < processes) {
            int boundary[2] = {at(i, width), at(i - 1, width)};
            MPI_Send(boundary, 2, MPI_INT, rank + 1, i, MPI_COMM_WORLD);
        }
    }

    int length = 0;
    if (rank == processes - 1) length = at(m, width);
    MPI_Bcast(&length, 1, MPI_INT, processes - 1, MPI_COMM_WORLD);
    if (rank == 0) {
        std::cout << "LCS length: " << length << "\nTime: " << MPI_Wtime() - start << " s\n";
    }
    MPI_Finalize();
}
