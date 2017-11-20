#pragma once

#include <cstdint>
#include "cmg/consts.h"
#include "cmg/Move.h"
#include "cmg/utils.h"
#include "cmg/consts.h"

namespace cmg {
struct gameState{
  std::array<uint_fast64_t, 2> colours{
      consts::black::PIECES,
      consts::white::PIECES
  };
  uint_fast64_t taken{0ull};
  
  // same as version 2, just easier to loop through
  std::array<uint_fast64_t , 12> pieces{
      consts::black::PAWN,
      consts::black::ROOK,
      consts::black::KNIGHT,
      consts::black::BISHOP,
      consts::black::QUEEN,
      consts::black::KING,
    
      consts::white::PAWN,
      consts::white::ROOK,
      consts::white::KNIGHT,
      consts::white::BISHOP,
      consts::white::QUEEN,
      consts::white::KING
  };
  uint_fast8_t info{0b00011111}; //0:blackkingcast, 1:whitekingcast, 2:blackqueencast, 3:whitequeencast, 4:white
  uint_fast8_t ep{0};
};

#ifdef CMG_UNITTEST
template<bool>
class MoveGenTester;
#endif

template<bool WHITE>
class MoveGen
{
#ifdef CMG_UNITTEST
  friend class MoveGenTester<WHITE>;
#endif
 public:
  constexpr MoveGen()
      : state{} // TODO: default game board
      , move{0}
      , moves{{0}}
      , movesIndex{0}
  {}
  constexpr MoveGen(const ::cmg::gameState st)
      : state{st}
      , move{0}
      , moves{{0}}
      , movesIndex{0}
  {}
  
  constexpr void setState(const ::cmg::gameState st)
  {
    this->state = st;
    this->movesIndex = 0;
  }
  
  constexpr uint_fast16_t getMove(const uint_fast8_t index) const
  {
    return this->moves[index];
  }
  
  constexpr uint_fast16_t size() const
  {
    return this->movesIndex;
  }
  
  constexpr uint_fast64_t generatePawnMoves()
  {
    uint_fast64_t cache = this->generatePawnSinglePush();
    return cache | this->generatePawnDoublePush(cache);
  }
  
  // Iterator pattern
  class const_iterator
  {
    const MoveGen &mg;
    size_t m_Index;
   public:
    constexpr const_iterator(const MoveGen& mg) : mg(mg), m_Index(0) {}
    constexpr const_iterator(const MoveGen& mg, const size_t nSize) : mg(mg), m_Index(nSize) {}
    constexpr const_iterator(const const_iterator& other) : mg(other.mg), m_Index(other.m_Index) {}
    constexpr void operator++() { m_Index++; }
    constexpr void operator--() { m_Index++; }
    constexpr bool operator != (const const_iterator& other) const { return m_Index != other.m_Index; }
    constexpr uint_fast16_t  operator *() const { return this->mg.getMove(m_Index); }
  };
  
  constexpr const_iterator begin() const
  {
    const_iterator it(*this);
    return it;
  }
  
  constexpr const_iterator end() const
  {
    const_iterator it(*this, this->size());
    return it;
  }
 
 private:
 protected:
  ::cmg::gameState state;
  ::cmg::Move move;
  std::array<uint_fast16_t, ::cmg::consts::MAXMOVES> moves;
  uint_fast16_t movesIndex;
  
  /**
   * Generate pawn forward moves and attacks
   *
   * @param index
   * @param gs
   * @param hostile
   * @return
   */
  constexpr uint_fast64_t generatePawnSinglePush()
  {
    const uint_fast64_t pawns{this->state.pieces[WHITE * 6]};
    uint64_t to{0ull};
    
    if constexpr (WHITE) {
      to = (pawns << 8) & (~this->state.taken); // move all pawns up one square
    } else {
      to = (pawns >> 8) & (~this->state.taken); // move all pawns down one square
    }
    uint64_t cache{to};
    
    // remove promotion pieces
    to ^= this->generatePromotions(to);
    
    // single push
    this->move.setFlags(0b0000);
    for (uint_fast8_t i = utils::LSB(to); i != 0; i = utils::NLSB(to, i)) {
      if constexpr (WHITE) {
        this->move.setFrom(i - 8);
      } else {
        this->move.setFrom(i + 8);
      }
      this->move.setTo(i);
      this->moves[this->movesIndex++] = this->move.getMove();
    }
    
    return cache;
  } // end pawn generation
  
  /**
   * Generate legal double push pawn moves
   *
   * @param pawns All pawn positions after single legal push (move). eg. 16711680ull
   * @return All the new pawn positions
   */
  constexpr uint_fast64_t generatePawnDoublePush(const uint_fast64_t pawns)
  {
    uint_fast64_t to{0ull};
    
    if constexpr (WHITE) {
      to = ((pawns & 0xff0000) << 8) & ~(this->state.taken);
    } else {
      to = ((pawns & 0xff0000000000) >> 8) & ~(this->state.taken);
    }
    uint_fast64_t cache{to};
    this->move.setFlags(0b0001);
    for (uint_fast8_t i = utils::LSB(to); i != 0; i = utils::NLSB(to, i)) {
      if constexpr (WHITE) {
        this->move.setFrom(i - 16);
      } else {
        this->move.setFrom(i + 16);
      }
      this->move.setTo(i);
      this->moves[this->movesIndex++] = this->move.getMove();
    }
    
    return cache;
  }
  
  /**
   * Generate promotion pieces.
   *
   * @param pawns pawns that have been moved
   * @return the set bits of promoted pieces
   */
  constexpr uint_fast64_t generatePromotions(const uint_fast64_t pawns)
  {
    uint_fast64_t promotions{pawns & 0xff000000000000ff};
    for (uint_fast8_t i = utils::LSB(promotions); i != 0; i = utils::NLSB(promotions, i)) {
      if constexpr (WHITE) {
        this->move.setFrom(i - 8);
      } else {
        this->move.setFrom(i + 8);
      }
      this->move.setTo(i);
      for (uint_fast8_t flag = 8; flag < 12; flag++) {
        this->move.setFlags(flag);
        this->moves[this->movesIndex++] = this->move.getMove();
      }
    }
    
    return pawns & 0xff000000000000ff;
  }
};
}