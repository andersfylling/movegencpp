#pragma once

#include <cstdint>
#include <chessmodule/movegencpp/consts.h>
#include <chessmodule/movegencpp/Move.h>
#include <chessmodule/movegencpp/utils.h>

namespace cmg {
using namespace consts;

struct gameState{
  std::array<uint_fast64_t, NR_OF_COLORS> colours{
      black::PIECES,
      white::PIECES
  };
  uint_fast64_t taken{0ull};
  
  // same as version 2, just easier to loop through
  std::array<uint_fast64_t , NR_OF_ALL_PIECE_TYPES> pieces{
      black::PAWN,
      black::ROOK,
      black::KNIGHT,
      black::BISHOP,
      black::QUEEN,
      black::KING,
    
      white::PAWN,
      white::ROOK,
      white::KNIGHT,
      white::BISHOP,
      white::QUEEN,
      white::KING
  };
  uint_fast8_t info{0b00011111}; //0:blackkingcast, 1:whitekingcast, 2:blackqueencast, 3:whitequeencast, 4:white
  uint_fast8_t ep{0};
};

#ifdef MOVEGENCPP_UNITTEST
template<uint_fast8_t>
class MoveGenTester;
#endif

template<uint_fast8_t COLOR>
class MoveGen
{
#ifdef MOVEGENCPP_UNITTEST
  friend class MoveGenTester<COLOR>;
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
  
  /**
   * Update the game state of this class instance.
   *
   * @param st ::cmg::gameState the new state
   */
  constexpr void setState(const ::cmg::gameState st)
  {
    this->state = st;
    this->movesIndex = 0;
  }
  
  
  /**
   * Get a given move. Does not check for out of bounds.
   *
   * @param index from 0 and 255
   * @return uint16 that holds info about said encoded move
   * @warning Might be an outdated move, if above this->moveIndex.
   */
  constexpr uint_fast16_t getMove(const uint_fast8_t index) const
  {
    return this->moves[index];
  }
  
  constexpr uint_fast16_t size() const
  {
    return this->movesIndex;
  }
  
  constexpr void clear()
  {
    this->movesIndex = 0;
  }
  
  /**
   * Generate single push, double push, left and right attacks (including en passant).
   *
   * @return uint64 Attackable positions
   */
  constexpr uint_fast64_t generatePawnMoves()
  {
    
    uint_fast64_t pawns = this->state.pieces[COLOR * NR_OF_WHITE_PIECE_TYPES];
    
    // attack left
    uint_fast64_t attacksLeft = this->generatePawnLeftAttack(pawns);
    
    // attack right
    uint_fast64_t attacksRight = this->generatePawnRightAttack(pawns);
    
    // single push
    uint_fast64_t singlePush = this->generatePawnSinglePush();
    
    // double push
    this->generatePawnDoublePush(singlePush);
    
    // result with double pushes
    return attacksLeft | attacksRight;
  }
  
  /**
   * Iterator pattern for get all the created semi-legal moves.
   */
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
  
  /**
   * Get the first move element
   *
   * @return
   */
  constexpr const_iterator begin() const
  {
    const_iterator it(*this);
    return it;
  }
  
  /**
   * Get an out of bounds move element
   * @return
   */
  constexpr const_iterator end() const
  {
    const_iterator it(*this, this->size());
    return it;
  }
 
 private:
 protected:
  ::cmg::gameState state;
  ::cmg::Move move;
  std::array<uint_fast16_t, ::cmg::MAXMOVES> moves;
  uint_fast16_t movesIndex;
  
  /**
   * Move all the pawns forward once and do a promotion check.
   * Promotions are handled, and removed from the resulting bitboard.
   *
   * @return A bitboard for all the pawns that moved forward, without being promoted.
   */
  constexpr uint_fast64_t generatePawnSinglePush()
  {
    const uint_fast64_t pawns{this->state.pieces[COLOR * NR_OF_WHITE_PIECE_TYPES]};
    uint64_t to{0ull};
    
    if constexpr (COLOR) {
      to = (pawns << NR_OF_WHITE_PAWNS) & (~this->state.taken); // move all pawns up one square
    } else {
      to = (pawns >> NR_OF_BLACK_PAWNS) & (~this->state.taken); // move all pawns down one square
    }
    uint64_t cache{to};
    
    // remove promotion pieces
    to ^= this->generatePromotions<0>(to);
    
    // single push
    this->move.setFlags(0b0000);
    for (uint_fast8_t i = utils::LSB(to); i != 0; i = utils::NLSB(to, i)) {
      if constexpr (COLOR) {
        this->move.setFrom(i + ONE_ROW_DOWN);
      } else {
        this->move.setFrom(i + ONE_ROW_UP);
      }
      this->move.setTo(i);
      this->moves[this->movesIndex++] = this->move.getMove();
    }
    
    return cache;
  } // end pawn generation
  
  /**
   * Generate legal double push pawn moves.
   * This is a continuation on single pawn push, so the argument must be
   * the pawns that has already moved once for accurate results.
   *
   * @param pawns All pawn positions after single legal push (move). eg. 16711680ull
   * @return All the new pawn positions
   */
  constexpr uint_fast64_t generatePawnDoublePush(const uint_fast64_t pawns)
  {
    uint_fast64_t to{0ull};
    
    if constexpr (COLOR) {
      to = ((pawns & 0xff0000) << MOVE_ONE_ROW_UP) & ~(this->state.taken);
    } else {
      to = ((pawns & 0xff0000000000) >> MOVE_ONE_ROW_DOWN) & ~(this->state.taken);
    }
    uint_fast64_t cache{to};
    this->move.setFlags(0b0001);
    for (uint_fast8_t i = utils::LSB(to); i != 0; i = utils::NLSB(to, i)) {
      if constexpr (COLOR) {
        this->move.setFrom(i + TWO_ROWS_DOWN);
      } else {
        this->move.setFrom(i + TWO_ROWS_UP);
      }
      this->move.setTo(i);
      this->moves[this->movesIndex++] = this->move.getMove();
    }
    
    return cache;
  }
  
  /**
   * Generate all pawn attacks on the left side.
   * Promotions are handled as after movement.
   *
   * @param pawns uint64 over all pawns.
   * @return uint64 with positions reached.
   */
  constexpr uint_fast64_t generatePawnLeftAttack(const uint_fast64_t pawns)
  {
    constexpr uint_fast64_t area{0x7f7f7f7f7f7f7f7f};
    uint_fast64_t attacks{COLOR ? (pawns & area) << 9 : (pawns & area) >> 7};
    attacks &= this->state.colours[COLOR ? 0 : 1]; //TODO en passant
    uint_fast64_t cache{attacks};
  
    // promotions
    constexpr std::array<uint_fast8_t, NR_OF_COLORS> directions{-7, 9};
    attacks ^= this->generatePromotions<directions[COLOR]>(attacks);
    this->move.setFlags(0b0100); //capture
    for (uint_fast8_t i = utils::LSB(attacks); i != 0; i = utils::NLSB(attacks, i)) {
      this->move.setFrom(i + directions[COLOR]);
      this->move.setTo(i);
      this->moves[this->movesIndex++] = this->move.getMove();
    }
  
    return cache;
  }
  
  /**
   * Generate all pawn attacks on the right side.
   * Promotions are handled as after movement.
   *
   * @param pawns uint64 over all pawns.
   * @return uint64 with positions reached.
   */
  constexpr uint_fast64_t generatePawnRightAttack(const uint_fast64_t pawns)
  {
    uint_fast64_t area{0xfefefefefefefefe};
    uint_fast64_t attacks{COLOR ? (pawns & area) << 7 : (pawns & area) >> 9};
    attacks &= this->state.colours[COLOR ? 0 : 1]; //TODO en passant
    uint_fast64_t cache{attacks};
    
    // promotions
    constexpr std::array<uint_fast8_t, NR_OF_COLORS> directions{-9, 7};
    attacks ^= this->generatePromotions<directions[COLOR]>(attacks);
    this->move.setFlags(0b0100); //capture
    for (uint_fast8_t i = utils::LSB(attacks); i != 0; i = utils::NLSB(attacks, i)) {
      this->move.setFrom(i + directions[COLOR]);
      this->move.setTo(i);
      this->moves[this->movesIndex++] = this->move.getMove();
    }
    
    return cache;
  }
  
  /**
   * Generate promotion pieces.
   *
   * @tparam FROM the bitboard offset in int8, diff between from and to position index.
   * @param pawns
   * @return
   */
  template<int_fast8_t FROM>
  constexpr uint_fast64_t generatePromotions(const uint_fast64_t pawns)
  {
    uint_fast64_t promotions{pawns & 0xff000000000000ff};
    
    // single push has a FROM of 1. since this is an offset.
    uint_fast8_t flag{FROM != 8 && FROM != -8 ? 0b1100 : 0b1000}; // TODO: review 8
    
    for (uint_fast8_t i = utils::LSB(promotions); i != 0; i = utils::NLSB(promotions, i)) {
      this->move.setFrom(i + FROM);
      this->move.setTo(i);
      for (uint_fast8_t type = 0; type < 4; type++) {
        this->move.setFlags(flag + type);
        this->moves[this->movesIndex++] = this->move.getMove();
      }
    }
    
    return pawns & 0xff000000000000ff;
  }
};
}