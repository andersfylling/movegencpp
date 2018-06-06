#include "catch.hpp"

#include "chessmodule/movegencpp/Move.h"

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

TEST_CASE("Attacks", "[Move]") {
  cmg::Move move{0};
  
  // check all flags
  for(int i = 0; i <= 15; i++) {
    move.setFlags(i);
    REQUIRE(move.getFlags() == i);
  }
  
  int i = 0;
  
  // quiet move
  move.setFlags(i++);
  REQUIRE(move.isQuietMoves());
  
  // double pawn push
  move.setFlags(i++);
  REQUIRE(move.isDoublePawnPush());
  
  // king castle
  move.setFlags(i++);
  REQUIRE(move.isKingCastle());
  
  // queen castle
  move.setFlags(i++);
  REQUIRE(move.isQueenCastle());
  
  // captures
  move.setFlags(i++);
  REQUIRE(move.hasCapture());
  
  // ep-capture
  move.setFlags(i++); // 5
  REQUIRE(move.isEPCapture());
  // 6 and 7 isn't used by chessprogramming.com
  i += 2;
  
  // knight-promotion
  move.setFlags(i++);
  REQUIRE(move.isKnightPromotion());
  
  // bishop-promotion
  move.setFlags(i++);
  REQUIRE(move.isBishopPromotion());
  
  // rook-promotion
  move.setFlags(i++);
  REQUIRE(move.isRookPromotion());
  
  // queen-promotion
  move.setFlags(i++);
  REQUIRE(move.isQueenPromotion());
  
  // knight-promo capture
  move.setFlags(i++);
  REQUIRE(move.isKnightPromoCapture());
  
  // bishop-promo capture
  move.setFlags(i++);
  REQUIRE(move.isBishopPromoCapture());
  
  // rook-promo capture
  move.setFlags(i++);
  REQUIRE(move.isRookPromoCapture());
  
  // queen-promo capture
  move.setFlags(i++);
  REQUIRE(move.isQueenPromoCapture());
  
  // custom flags
  
  // check
  move.setFlags(7);
  REQUIRE(move.isCheck()); // when the moving piece has caused a check
}