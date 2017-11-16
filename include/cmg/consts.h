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


}
}