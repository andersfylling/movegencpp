#pragma once

#include <cstdint>

namespace cmg {
struct gameState{}; // TODO


template<bool WHITE>
class MoveGen
{
 public:
  constexpr MoveGen()
      : state{} // TODO: default game board
      , moves{{0}}
      , movesIndex{0}
  {}
  constexpr MoveGen(const ::cmg::gameState st)
      : state{st}
      , moves{{0}}
      , movesIndex{0}
  {}
  
  constexpr void setState(const ::cmg::gameState st)
  {
    this->state = st;
  }
  
  constexpr uint_fast16_t getMove(const uint_fast8_t index) const
  {
    return this->moves[index];
  }
  
  constexpr uint_fast8_t getNrOfMoves() const
  {
    return this->movesIndex;
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
  std::array<uint_fast16_t, 250> moves;
  uint_fast8_t movesIndex;
  
};
}