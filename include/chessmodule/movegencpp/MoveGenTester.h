#pragma once
#ifdef MOVEGENCPP_UNITTEST

#include <chessmodule/movegencpp/MoveGen.h>
#include <iostream>


namespace cmg {

template<uint_fast8_t COLOR>
class MoveGenTester
{
 public:
  constexpr MoveGenTester()
      : moveGen{}
      , state{}
  {}
  constexpr MoveGenTester(const ::cmg::gameState st)
      : moveGen{st}
      , state{st}
  {}
  
  constexpr void setState(const ::cmg::gameState st)
  {
    this->moveGen.setState(st);
    this->state = st;
  }
  
  constexpr MoveGen<COLOR>& getMoveGen()
  {
    return this->moveGen;
  }
  
  constexpr uint_fast16_t size()
  {
    return this->moveGen.size();
  }
  
  constexpr void clear()
  {
    this->moveGen.clear();
  }
  
  constexpr uint_fast64_t generatePawnSinglePush()
  {
    return this->moveGen.generatePawnSinglePush();
  }
  
  constexpr uint_fast64_t generatePawnDoublePush(const uint_fast64_t pawns = 16711680ull)
  {
    return this->moveGen.generatePawnDoublePush(pawns);
  }
  
  constexpr uint_fast64_t generatePawnRightAttack(const uint_fast64_t pawns)
  {
    return this->moveGen.generatePawnRightAttack(pawns);
  }
  
  constexpr uint_fast64_t generatePawnLeftAttack(const uint_fast64_t pawns)
  {
    return this->moveGen.generatePawnLeftAttack(pawns);
  }
  
  template<uint_fast8_t DIRECTION = 0>
  constexpr uint_fast64_t generatePromotions(const uint_fast64_t pawns = 0ull)
  {
    return this->moveGen.template generatePromotions<DIRECTION>(pawns);
  }
 private:
  MoveGen<COLOR> moveGen;
  gameState state;
 protected:
};

}

#endif