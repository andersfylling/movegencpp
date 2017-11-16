#pragma once

#include <cstdint>
#include "cmg/consts.h"
#include "cmg/Move.h"
#include "cmg/utils.h"

namespace cmg {
struct gameState{
  std::array<uint_fast64_t, 2> colours{0ull};
  uint_fast64_t taken{0ull};
  
  // same as version 2, just easier to loop through
  std::array<uint_fast64_t , 12> pieces = {{0}}; // fixed positions
  uint_fast8_t info = 0b00011111; //0:blackkingcast, 1:whitekingcast, 2:blackqueencast, 3:whitequeencast, 4:white
  uint_fast8_t ep = 0;
};


template<bool WHITE>
class MoveGen
{
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
  
  constexpr uint_fast16_t getNrOfMoves() const
  {
    return this->movesIndex;
  }
  
  
  constexpr uint_fast64_t generatePawnMoves()
  {
    return this->generatePawnSinglePush() | this->generatePawnDoublePush();
  }
  
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
      
    // remove promotion pieces
    to ^= this->generatePromotions(to);
  
    // single push
    this->move.setFlags(0b0000);
    for (uint_fast8_t i = utils::LSB(to); i != 0; i = utils::NSB(to, i)) {
      if constexpr (WHITE) {
        this->move.setFrom(i - 8);
      } else {
        this->move.setFrom(i + 8);
      }
      this->move.setTo(i);
      this->moves[this->movesIndex++] = this->move.getMove();
    }
    
    return to;
  } // end pawn generation
  
  /**
   * Generate legal double push pawn moves
   *
   * @return All the new pawn positions
   */
  constexpr uint_fast64_t generatePawnDoublePush()
  {
    const uint_fast64_t pawns{this->state.pieces[WHITE * 6]};
    uint64_t to{0ull};
    
    if constexpr (WHITE) {
      to = ((pawns & 0xff00) << 16) & ~(this->state.taken | (this->state.taken << 8));
    } else {
      to = ((pawns & 0xff00) >> 16) & ~(this->state.taken | (this->state.taken >> 8));
    }
    this->move.setFlags(0b0001);
    for (uint_fast8_t i = utils::LSB(to); i != 0; i = utils::NSB(to, i)) {
      if constexpr (WHITE) {
        this->move.setFrom(i - 16);
      } else {
        this->move.setFrom(i + 16);
      }
      this->move.setTo(i);
      this->moves[this->movesIndex++] = this->move.getMove();
    }
    
    return to;
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
    for (uint_fast8_t i = utils::LSB(promotions); i != 0; i = utils::NSB(promotions, i)) {
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
  
  // Iterator pattern
  class iterator
  {
    const MoveGen &mg;
    size_t m_Index;
   public:
    constexpr iterator(const MoveGen& mg)
        : mg(mg)
        , m_Index(0)
    {}
    constexpr iterator(const MoveGen& mg, const size_t nSize)
        : mg(mg)
        , m_Index(nSize)
    {}
    constexpr iterator(const iterator& other)
        : mg(other.mg)
        , m_Index(other.m_Index)
    {}
    constexpr void operator++()
    {
      m_Index++;
    }
  
    constexpr void operator--()
    {
      m_Index++;
    }
  
    constexpr bool operator != (const iterator& other) const
    {
      return m_Index != other.m_Index;
    }
  
    constexpr int operator *() const
    {
      return this->mg.getMove(m_Index);
    }
  };
  
  constexpr iterator begin() const
  {
    iterator it(*this);
    return it;
  }
  
  constexpr iterator end() const
  {
    iterator it(*this, this->getNrOfMoves());
    return it;
  }
 
 protected:
  ::cmg::gameState state;
  ::cmg::Move move;
  std::array<uint_fast16_t, ::cmg::consts::MAXMOVES> moves;
  uint_fast16_t movesIndex;
  
};
}