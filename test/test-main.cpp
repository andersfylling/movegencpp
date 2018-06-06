#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <chessmodule/movegencpp/MoveGenTester.h>
#include <string_view>
#include <string>

TEST_CASE("check the library in a typical setting") {
  const bool white = true;
  ::cmg::MoveGen<white> moveGen{}; // default board layout
  moveGen.generatePawnMoves();

  // For every generated move, print move, from, to, and flags
  for (const auto move : moveGen) {
    ::cmg::Move m{move};

    m.getFlags();
  }
}