# deepiri-metal-omelette Implementation Plan

## Overview

Build complete DBIS VM and toolchain entirely in Diva - register-based, variable-length encoding, full opcode set v0.3.

---

## Current State

- `deepiri-metal-omelette/` exists with shell-based VM
- `diva/` compiler fully functional
- Need: complete DBIS spec + full Diva VM

---

## Architecture

### Register-Based VM Design

```
Registers: R0-R15 (16 general purpose)
PC        - Program counter
SP        - Stack pointer  
Flags     - Condition flags (Z, C, N, P)
RAM       - 256 bytes (expandable)
```

### Variable-Length Encoding

- Opcode: 1 byte
- Operands: variable (register bits + immediate values)
- Register encoding: 4 bits per register (two registers = 1 byte)

---

## DBIS v0.3 Opcode Table (Full Featured)

### Core Ops (0x00-0x0F)

| Opcode | Name | Args | Description |
|--------|------|------|-------------|
| 0x00 | NOP | - | No operation |
| 0x01 | HALT | - | Stop execution |
| 0x02 | MOV | Rdest, Rsrc | Move register |
| 0x03 | MOVI | Rdest, imm | Move immediate |
| 0x04 | LOAD | Rdest, [Rsrc] | Load from memory |
| 0x05 | STORE | [Rdest], Rsrc | Store to memory |
| 0x06 | LOADI | Rdest, [imm] | Load from address |
| 0x07 | STOREI | [Rdest], imm | Store to address |

### Arithmetic (0x10-0x1F)

| Opcode | Name | Args | Description |
|--------|------|------|-------------|
| 0x10 | ADD | Rd, Rs | Rd = Rd + Rs |
| 0x11 | SUB | Rd, Rs | Rd = Rd - Rs |
| 0x12 | MUL | Rd, Rs | Rd = Rd * Rs |
| 0x13 | DIV | Rd, Rs | Rd = Rd / Rs |
| 0x14 | MOD | Rd, Rs | Rd = Rd % Rs |
| 0x15 | SHL | Rd, Rs | Rd = Rd << Rs |
| 0x16 | SHR | Rd, Rs | Rd = Rd >> Rs |
| 0x17 | AND | Rd, Rs | Rd = Rd & Rs |
| 0x18 | OR | Rd, Rs | Rd = Rd | Rs |
| 0x19 | XOR | Rd, Rs | Rd = Rd ^ Rs |
| 0x1A | NOT | Rd | Rd = ~Rd |
| 0x1B | NEG | Rd | Rd = -Rd |

### Compare (0x20-0x2F)

| Opcode | Name | Args | Description |
|--------|------|------|-------------|
| 0x20 | CMP | Rd, Rs | Set flags from Rd - Rs |
| 0x21 | TEST | Rd, Rs | Set flags from Rd & Rs |
| 0x22 | CMPI | Rd, imm | CMP with immediate |

### Control Flow (0x30-0x3F)

| Opcode | Name | Args | Description |
|--------|------|------|-------------|
| 0x30 | JMP | addr | Jump to address |
| 0x31 | JZ | addr | Jump if zero |
| 0x32 | JNZ | addr | Jump if not zero |
| 0x33 | JG | addr | Jump if greater |
| 0x34 | JL | addr | Jump if less |
| 0x35 | JGE | addr | Jump if greater or equal |
| 0x36 | JLE | addr | Jump if less or equal |
| 0x37 | CALL | addr | Call subroutine |
| 0x38 | RET | - | Return from subroutine |

### Stack (0x40-0x4F)

| Opcode | Name | Args | Description |
|--------|------|------|-------------|
| 0x40 | PUSH | Rs | Push register to stack |
| 0x41 | POP | Rd | Pop from stack to register |
| 0x42 | PUSHI | imm | Push immediate |
| 0x43 | PUSHF | - | Push flags |

### I/O (0x50-0x5F)

| Opcode | Name | Args | Description |
|--------|------|------|-------------|
| 0x50 | IN | Rd | Read input byte |
| 0x51 | OUT | Rs | Output byte |
| 0x52 | OUTS | Rs, len | Output string |
| 0x53 | SYS | id | System call |

### Memory (0x60-0x6F)

| Opcode | Name | Args | Description |
|--------|------|------|-------------|
| 0x60 | MALLOC | Rd, size | Allocate memory |
| 0x61 | FREE | Rs | Free memory |
| 0x62 | COPY | Rd, Rs, n | Copy n bytes |

### Agent/Async (0x70-0x7F)

| Opcode | Name | Args | Description |
|--------|------|------|-------------|
| 0x70 | SPAWN | Rd, addr | Spawn new agent |
| 0x71 | YIELD | - | Yield execution |
| 0x72 | JOIN | Rd, id | Wait for agent |
| 0x73 | SEND | id, Rs | Send message |
| 0x74 | RECV | Rd | Receive message |

---

## Implementation Plan

### Phase 1: DBIS Specification (dbis/spec.md)

Update spec.md with:
- Register architecture
- Variable-length encoding rules
- Complete opcode table v0.3
- Binary format specification

### Phase 2: VM Core (vm/omelette.diva)

Create `vm/omelette.diva`:
```
class VM {
    var registers :: int[]     // 16 registers
    var ram :: int[]           // 256 bytes
    var pc :: int              // program counter
    var sp :: int              // stack pointer  
    var flags :: int           // condition flags
    
    func run(program: int[]): void
    func fetch(): int
    func decode(opcode: int): void
    func execute(op: int, args: int[]): void
    func set_flags(result: int): void
}
```

### Phase 3: Assembler (tools/assembler.diva)

Create assembler in Diva:
```
class Assembler {
    func assemble(source: str): int[]
    func parse_opcode(name: str): int
    func parse_register(name: str): int
    func parse_immediate(val: str): int
}
```

### Phase 4: Disassembler (tools/disassembler.diva)

Create disassembler in Diva:
```
class Disassembler {
    func disassemble(program: int[]): str
    func decode_opcode(op: int): str
    func format_register(r: int): str
}
```

### Phase 5: Example Programs

Create Diva source examples in `dbis/examples/`:
- ping.diva (assembles to ping.bin)
- add.diva (add two numbers)
- fib.diva (fibonacci)
- echo.diva (I/O test)

---

## File Structure After Implementation

```
deepiri-metal-omelette/
├── dbis/
│   ├── spec.md              # DBIS v0.3 spec (updated)
│   └── examples/
│       ├── ping.diva        # Source examples
│       ├── add.diva
│       ├── fib.diva
│       └── echo.diva
│
├── vm/
│   └── omelette.diva        # VM in Diva (NEW)
│
├── tools/
│   ├── assembler.diva       # Assembler in Diva (NEW)
│   ├── disassembler.diva   # Disassembler in Diva (NEW)
│   ├── assembler.sh        # Keep for compatibility
│   └── disassembler.sh
│
├── bin/
│   └── *.bin                # Compiled programs
│
├── cli/
│   └── omelette             # Shell wrapper
│
└── README.md
```

---

## Execution Flow

```
User writes: ping.diva
       ↓
assembler.diva compiles to: ping.bin (raw bytes)
       ↓
omelette.diva VM executes: ping.bin
       ↓
Output: "ping"
```