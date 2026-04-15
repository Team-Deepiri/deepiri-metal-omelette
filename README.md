# deepiri-metal-omelette

Deepiri's binary execution substrate - **100% Diva**.

## Overview

```
Diva Source → DBIS Bytecode → omelette VM → Execution
```

All components written entirely in Diva.

## Structure

```
deepiri-metal-omelette/
├── dbis/
│   ├── spec.md              # DBIS v0.3 specification
│   └── examples/
│       ├── ping.diva
│       └── add.diva
├── vm/
│   └── omelette.diva        # ✅ Working VM in Diva
├── tools/
│   ├── assembler.diva      # ✅ Working assembler in Diva
│   └── disassembler.diva   # ✅ Working disassembler in Diva
└── docs/
    └── implementation-plan.md
```

## Quick Start

```bash
# Run VM with built-in tests
diva run vm/omelette.diva

# Run assembler
diva run tools/assembler.diva

# Run disassembler  
diva run tools/disassembler.diva
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
| 0x20 | JMP | Jump |
| 0x21 | JZ | Jump if zero |
| 0x22 | JNZ | Jump if not zero |
| 0x37 | CALL | Call |
| 0x38 | RET | Return |
| 0x40 | PUSH | Push to stack |
| 0x41 | POP | Pop from stack |
| 0x50 | IN | Input |
| 0x51 | OUT | Output |

## Status

- ✅ VM in Diva (works)
- ✅ Assembler in Diva (works)
- ✅ Disassembler in Diva (works)
- ✅ DBIS spec v0.3
- ✅ Example programs

## Philosophy

- **No shell scripts** 
- **No assembly**
- **No C code**
- **Everything in Diva**