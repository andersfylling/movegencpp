#include "catch.hpp"

#include "cmg/Move.h"

TEST_CASE("Check to and from de/encoding", "[Move]") {
  cmg::Move move{0};
  
  move.setFrom(8);
  REQUIRE(move.getFrom() == 8);
  REQUIRE(move.getTo() == 0);
  REQUIRE(move.getFlags() == 0);
  
  move.setTo(16);
  REQUIRE(move.getFrom() == 8);
  REQUIRE(move.getTo() == 16);
  REQUIRE(move.getFlags() == 0);
  
  move.setTo(0);
  REQUIRE(move.getFrom() == 8);
  REQUIRE(move.getTo() == 0);
  REQUIRE(move.getFlags() == 0);
  
  move.setTo(24);
  REQUIRE(move.getFrom() == 8);
  REQUIRE(move.getTo() == 24);
  REQUIRE(move.getFlags() == 0);
  
  move.setFrom(0);
  REQUIRE(move.getFrom() == 0);
  REQUIRE(move.getTo() == 24);
  REQUIRE(move.getFlags() == 0);
  
  move.setTo(3);
  REQUIRE(move.getFrom() == 0);
  REQUIRE(move.getTo() == 3);
  REQUIRE(move.getFlags() == 0);
  
  // move using constructor
  cmg::Move m2{8, 24, 0};
  REQUIRE(m2.getFrom() == 8);
  REQUIRE(m2.getTo() == 24);
  REQUIRE(m2.getFlags() == 0);
  
}

TEST_CASE("Check flag de/encoding", "[Move]") {
  //flags
  cmg::Move m3{8, 24, 15};
  REQUIRE(m3.getFrom() == 8);
  REQUIRE(m3.getTo() == 24);
  REQUIRE(m3.getFlags() == 15);
  
  m3.setFlags(7);
  REQUIRE(m3.getFrom() == 8);
  REQUIRE(m3.getTo() == 24);
  REQUIRE(m3.getFlags() == 7);
  
  m3.setFlags(0);
  REQUIRE(m3.getFrom() == 8);
  REQUIRE(m3.getTo() == 24);
  REQUIRE(m3.getFlags() == 0);
  
  m3.setFlags(7);
  m3.setFrom(4);
  m3.setTo(62);
  REQUIRE(m3.getFrom() == 4);
  REQUIRE(m3.getTo() == 62);
  REQUIRE(m3.getFlags() == 7);
}


TEST_CASE("Check comparisons", "[Move]") {
  cmg::Move move{0};
  move.setFrom(8);
  move.setTo(24);
  
  // move using constructor
  cmg::Move m2{8, 24, 0};
  
  //flags
  cmg::Move m3{8, 24, 15};
  
  m3.setFlags(7);
  m3.setFrom(4);
  m3.setTo(62);
  REQUIRE(m3.getFrom() == 4);
  REQUIRE(m3.getTo() == 62);
  REQUIRE(m3.getFlags() == 7);
  
  REQUIRE(m2 != m3);
  REQUIRE(!(m2 == m3));
  
  m2 = m3;
  REQUIRE(m2 == m3);
  REQUIRE(m2.getFrom() == 4);
  REQUIRE(m2.getTo() == 62);
  REQUIRE(m2.getFlags() == 7);
  
  m3.setMove(move);
  REQUIRE(m3 == move);
  REQUIRE(m2 != move);
  
  m2.setMove(move.getMove());
  REQUIRE(m2 == move);
}