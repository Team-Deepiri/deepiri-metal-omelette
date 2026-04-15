# deepiri-metal-omelette

Deepiri's binary execution substrate - **100% Diva**.

## Overview

```
Diva Source → DBIS Bytecode → omelette VM → Execution
```

All components written entirely in Diva.

## Quick Start

```bash
# Run VM with comprehensive test suite (14 tests)
diva run vm/omelette.diva

# Show CLI help
diva run cli/omelette.diva

# Show assembler reference
diva run tools/assembler.diva

# Show disassembler reference
diva run tools/disassembler.diva
```

## Components

| Component | File | Status | Description |
|-----------|------|--------|-------------|
| VM | `vm/omelette.diva` | ✅ | 14 tests: ping, add, sub, mul, div, fib, fact, gcd, pow, prime, reverse, max, abs |
| CLI | `cli/omelette.diva` | ✅ | Help, usage, opcode reference |
| Assembler | `tools/assembler.diva` | ✅ | Bytecode reference with examples |
| Disassembler | `tools/disassembler.diva` | ✅ | Assembly listing with encoding docs |

## VM Test Suite

The VM runs 14 comprehensive tests:

```
String output: PING, HELLO
Arithmetic:    ADD (5+3=8), SUB (10-3=7), MUL (4*3=12), DIV (12/4=3)
Loops & Math:  LOOP (sum 1-10=55), FIB (fibonacci 10=55), FACT (5!=120)
Advanced:      GCD (48,18=6), POW (2^8=256), PRIME (17=yes)
Utils:         REVERSE (12345=54321), MAX (7,3=7), ABS (-5=5)
```

## DBIS v0.3 Opcodes

| Opcode | Name | Description |
|--------|------|-------------|
| 0x00 | NOP | No operation |
| 0x01 | HALT | Stop execution |
| 0x03 | MOVI | Move immediate |
| 0x10 | ADD | Add registers |
| 0x11 | SUB | Subtract |
| 0x12 | MUL | Multiply |
| 0x13 | DIV | Divide |
| 0x20 | CMP | Compare |
| 0x30 | JMP | Jump |
| 0x31 | JZ | Jump if zero |
| 0x32 | JNZ | Jump if not zero |
| 0x37 | CALL | Call |
| 0x38 | RET | Return |
| 0x40 | PUSH | Push to stack |
| 0x41 | POP | Pop from stack |
| 0x50 | IN | Input |
| 0x51 | OUT | Output |

## Architecture

- **16 registers** (R0-R15)
- **256 bytes RAM**
- **Stack pointer** at 255, grows downward

## Example Programs

### ping.dbis
```
MOVI R0 80
OUT R0
MOVI R0 105
OUT R0
MOVI R0 110
OUT R0
MOVI R0 103
OUT R0
HALT
```
Bytecode: `3 0 80 81 0 3 0 105 81 0 3 0 110 81 0 3 0 103 81 0 1`

### add.dbis
```
MOVI R0 5
MOVI R1 3
ADD R0 R1
OUT R0
HALT
```
Bytecode: `3 0 5 3 1 3 16 0 1 81 0 1` (outputs 8)

## File Structure

```
deepiri-metal-omelette/
├── dbis/
│   ├── spec.md              # DBIS v0.3 specification
│   └── examples/
│       ├── ping.dbis        # Print "Ping"
│       ├── add.dbis        # Add 5+3
│       ├── fib.dbis        # Fibonacci
│       ├── factorial.dbis  # Factorial
│       ├── gcd.dbis        # GCD
│       ├── prime.dbis      # Prime check
│       └── loop.dbis       # Loop sum
├── vm/
│   └── omelette.diva       # VM with test suite
├── cli/
│   └── omelette.diva       # CLI help
├── tools/
│   ├── assembler.diva      # Bytecode reference
│   └── disassembler.diva  # Disassembly reference
└── README.md
```

## Status

- ✅ VM in Diva - 14 comprehensive tests
- ✅ CLI in Diva - help and opcode reference
- ✅ Assembler reference in Diva - bytecode tables
- ✅ Disassembler reference in Diva - encoding docs
- ✅ DBIS spec v0.3
- ✅ Example programs (.dbis)

## Philosophy

- **No shell scripts**
- **No assembly**
- **No C code**
- **Everything in Diva**
