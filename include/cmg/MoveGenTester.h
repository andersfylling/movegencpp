#pragma once
#ifdef CMG_UNITTEST

#include "./MoveGen.h"
#include <iostream>


namespace cmg {

template<bool WHITE>
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
  
  constexpr MoveGen<WHITE>& getMoveGen()
  {
    return this->moveGen;
  }
  
  constexpr uint_fast64_t generatePawnSinglePush()
  {
    return this->moveGen.generatePawnSinglePush();
  }
  
  constexpr uint_fast64_t generatePawnDoublePush(const uint_fast64_t pawns = 16711680ull)
  {
    return this->moveGen.generatePawnDoublePush(pawns);
  }
 private:
  MoveGen<WHITE> moveGen;
  gameState state;
 protected:
};

}

#endif