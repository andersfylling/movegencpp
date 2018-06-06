#pragma once

namespace cmg {
namespace consts {

// move generation
constexpr uint_fast16_t MAXMOVES{256};

// move constants
constexpr uint_fast16_t FLAG_PROMOTION {0b1000000000000000};
constexpr uint_fast16_t FLAG_CAPTURE   {0b0100000000000000};
constexpr uint_fast16_t FLAG_SPECIAL1  {0b0010000000000000};
constexpr uint_fast16_t FLAG_SPECIAL0  {0b0001000000000000};
constexpr uint_fast16_t RANGE_FLAG     {0b1111000000000000};
constexpr uint_fast16_t RANGE_FROM     {0b0000111111000000};
constexpr uint_fast16_t RANGE_TO       {0b0000000000111111};

// piece index


//! Bitboards default positions
//! For all the different black pieces
namespace black {
constexpr uint_fast64_t BISHOP  {2594073385365405696ull};
constexpr uint_fast64_t KING    {576460752303423488ull};
constexpr uint_fast64_t KNIGHT  {4755801206503243776ull};
constexpr uint_fast64_t PAWN    {71776119061217280ull};
constexpr uint_fast64_t QUEEN   {1152921504606846976ull};
constexpr uint_fast64_t ROOK    {9295429630892703744ull};
constexpr uint_fast64_t PIECES  {BISHOP | KNIGHT | PAWN | QUEEN | KING | ROOK};
}
//! For all the different white pieces
namespace white {
constexpr uint_fast64_t BISHOP  {36ull};
constexpr uint_fast64_t KNIGHT  {66ull};
constexpr uint_fast64_t PAWN    {65280ull};
constexpr uint_fast64_t QUEEN   {16ull};
constexpr uint_fast64_t KING    {8ull};
constexpr uint_fast64_t ROOK    {129ull};
constexpr uint_fast64_t PIECES  {BISHOP | KNIGHT | PAWN | QUEEN | KING | ROOK};
}

}
}