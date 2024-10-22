# Chess Move Generator (CMG) 
IS a Chess project written in C++17. It aims to create a Move Generator with C++ features and proper unit testing.

This generates moves that are stored in a `uint_fast16_t`. These can be iterated after generation.
```c++
const bool white = true;
::cmg::MoveGen<white> moveGen{}; // default board layout
moveGen.generatePawnSinglePush(); // This method is not public. This is just for explaining the behavior.

// For every generated move, print move, from, to, and flags
for (const auto move : moveGen) {
  ::cmg::Move m{move};
  std::printf("Move{%lu} => from{%u}, to{%u}, flags(%d)", move, m.getFrom(), m.getTo(), m.getFlags());
}
```

This will give the output:
```markdown
528 => from{ 8}, to{16}, flags{0}
593 => from{ 9}, to{17}, flags{0}
658 => from{10}, to{18}, flags{0}
723 => from{11}, to{19}, flags{0}
788 => from{12}, to{20}, flags{0}
853 => from{13}, to{21}, flags{0}
918 => from{14}, to{22}, flags{0}
983 => from{15}, to{23}, flags{0}
```

