#include <benchmark/benchmark.h>
#include "dmao.hpp"

static void BM_Sample(benchmark::State &state) {
    for (auto _ : state) {
        // benchmark code here
    }
}
BENCHMARK(BM_Sample);

BENCHMARK_MAIN();
