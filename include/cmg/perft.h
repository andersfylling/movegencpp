#pragma once

#include <cstdint>
#include <string>

namespace cmg {

// normal perft
void perft(const uint8_t max);
void perft(const uint8_t start, const uint8_t end, const std::string FEN = "");
//void perft(::david::type::gameState_t& gs, const uint8_t start, const uint8_t end);
//uint64_t perft(const uint8_t depth, ::david::type::gameState_t& gs);

// for testing
uint64_t perft_silent(const uint_fast8_t depth, const std::string FEN = "");
}