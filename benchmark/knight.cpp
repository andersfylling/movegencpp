#include <benchmark/benchmark.h>
#include <chessmodule/movegencpp/utils.h>

//
// Look up table
// ##############
constexpr std::array<uint64_t, 64> generateKnightLookupTable() {
    ::std::array<uint64_t, 64> attacks{};

    // directions a rook can move
    const std::array<int8_t, 4> directions = {1, -1};

    for (uint8_t i = 0; i < 64; i++) {

        // the different board limits related to directions
        uint8_t row = i / 8;
        uint8_t col = i % 8;
        //const std::array<uint8_t, 4> limitations = {/*up*/7 - row, /*right*/col, /*down*/row, /*left*/7 - col};

        uint64_t result = 0ULL;

        for (uint8_t ii = 0; ii < 2; ii++) {
            const int8_t directionY = directions[ii];
            // up / down
            for (uint8_t y = 1; y < 3; y++) {
                // make sure the knight doesnt go too high or too "low"
                const auto heightPush = row + (directionY * y);
                if (heightPush > 7 || heightPush < 0) {
                    continue;
                }

                // how far to the side should the knight move, based on its desired height move
                uint8_t colOffset = 3 - y; // if y == 1, then move 2 pos to the side, y == 2 move 1 pos to the side

                for (uint8_t x = 0; x < 2; x++) {
                    const int8_t directionX = directions[x];
                    // make sure it doesn't go too far to the sides
                    const auto sidePush = col + (directionX * colOffset);
                    if (sidePush > 7 || sidePush < 0) {
                        continue;
                    }

                    // add it to the possible moves
                    result |= cmg::utils::indexToBitboard(i + (directionX * colOffset) + (directionY * 8 * y));
                }
            }
        }

        attacks[i] = result;
    }

    return attacks;
}

static void BM_KnightLookupTable(benchmark::State& state) {
    uint64_t hostiles = 0x89274ed10a904618;

    std::array<uint64_t, 64> table = generateKnightLookupTable();
    for (auto _ : state) {
        for (int i = 0; i < 64; i++) {
            uint64_t attacked = hostiles & table[i++];
        }
    }
}
BENCHMARK(BM_KnightLookupTable);