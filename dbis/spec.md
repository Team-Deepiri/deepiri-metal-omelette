# DBIS - Deepiri Binary Instruction Set v0.3

## Design Goals
- Register-based (16 general purpose registers: R0-R15)
- Variable-length instruction encoding
- Agent/async support for Deepiri integration
- Stack-based fallback for compatibility

## Architecture

### Register Set
```
R0-R15    - General purpose registers (16)
PC        - Program counter
SP        - Stack pointer
FLAGS     - Condition flags (Z=Zero, C=Carry, N=Negative, P=Parity)
```

### Memory Model
- RAM: 256 bytes (expandable to 1024)
- Stack: Grows downward from SP
- Program: Loaded at address 0

### Instruction Encoding
- Opcode: 1 byte (0x00-0xFF)
- Register operands: 4 bits each (two registers fit in one byte)
- Immediate values: variable length (1, 2, or 4 bytes)

### Register Encoding
```
Lower 4 bits = register number (0-15)
Upper 4 bits in byte = second register (for two-reg instructions)
```

---

## Opcode Table v0.3

### Core Ops (0x00-0x0F)

| Opcode | Name | Operands | Description |
|--------|------|----------|-------------|
| 0x00 | NOP | - | No operation |
| 0x01 | HALT | - | Stop execution |
| 0x02 | MOV | Rd, Rs | Move: Rd = Rs |
| 0x03 | MOVI | Rd, imm | Move immediate: Rd = imm |
| 0x04 | LOAD | Rd, [Rs] | Load: Rd = memory[Rs] |
| 0x05 | STORE | [Rd], Rs | Store: memory[Rd] = Rs |
| 0x06 | LOADI | Rd, addr | Load indirect: Rd = memory[addr] |
| 0x07 | STOREI | addr, Rs | Store indirect: memory[addr] = Rs |

### Arithmetic (0x10-0x1B)

| Opcode | Name | Operands | Description |
|--------|------|----------|-------------|
| 0x10 | ADD | Rd, Rs | Add: Rd = Rd + Rs |
| 0x11 | SUB | Rd, Rs | Subtract: Rd = Rd - Rs |
| 0x12 | MUL | Rd, Rs | Multiply: Rd = Rd * Rs |
| 0x13 | DIV | Rd, Rs | Divide: Rd = Rd / Rs |
| 0x14 | MOD | Rd, Rs | Modulo: Rd = Rd % Rs |
| 0x15 | SHL | Rd, Rs | Shift left: Rd = Rd << Rs |
| 0x16 | SHR | Rd, Rs | Shift right: Rd = Rd >> Rs |
| 0x17 | AND | Rd, Rs | Bitwise AND: Rd = Rd & Rs |
| 0x18 | OR | Rd, Rs | Bitwise OR: Rd = Rd | Rs |
| 0x19 | XOR | Rd, Rs | Bitwise XOR: Rd = Rd ^ Rs |
| 0x1A | NOT | Rd | Bitwise NOT: Rd = ~Rd |
| 0x1B | NEG | Rd | Negate: Rd = -Rd |

### Compare (0x20-0x22)

| Opcode | Name | Operands | Description |
|--------|------|----------|-------------|
| 0x20 | CMP | Rd, Rs | Compare: flags = Rd - Rs |
| 0x21 | TEST | Rd, Rs | Test: flags = Rd & Rs |
| 0x22 | CMPI | Rd, imm | Compare immediate: flags = Rd - imm |

### Control Flow (0x30-0x38)

| Opcode | Name | Operands | Description |
|--------|------|----------|-------------|
| 0x30 | JMP | addr | Jump: PC = addr |
| 0x31 | JZ | addr | Jump if zero: if Z flag, PC = addr |
| 0x32 | JNZ | addr | Jump if not zero: if !Z flag, PC = addr |
| 0x33 | JG | addr | Jump if greater: if !Z && (N==P), PC = addr |
| 0x34 | JL | addr | Jump if less: if N != P, PC = addr |
| 0x35 | JGE | addr | Jump if greater or equal: if !N || Z, PC = addr |
| 0x36 | JLE | addr | Jump if less or equal: if N || Z, PC = addr |
| 0x37 | CALL | addr | Call: push(PC), PC = addr |
| 0x38 | RET | - | Return: PC = pop() |

### Stack (0x40-0x43)

| Opcode | Name | Operands | Description |
|--------|------|----------|-------------|
| 0x40 | PUSH | Rs | Push: SP--, memory[SP] = Rs |
| 0x41 | POP | Rd | Pop: Rd = memory[SP], SP++ |
| 0x42 | PUSHI | imm | Push immediate: SP--, memory[SP] = imm |
| 0x43 | PUSHF | - | Push flags: SP--, memory[SP] = FLAGS |

### I/O (0x50-0x53)

| Opcode | Name | Operands | Description |
|--------|------|----------|-------------|
| 0x50 | IN | Rd | Input: Rd = read_byte() |
| 0x51 | OUT | Rs | Output: write_byte(Rs) |
| 0x52 | OUTS | Rs, Rlen | Output string: write_n(Rs, Rlen) |
| 0x53 | SYS | id | System call: invoke(id) |

### Memory (0x60-0x62)

| Opcode | Name | Operands | Description |
|--------|------|----------|-------------|
| 0x60 | MALLOC | Rd, Rs | Allocate: Rd = alloc(Rs bytes) |
| 0x61 | FREE | Rs | Free: dealloc(Rs) |
| 0x62 | COPY | Rd, Rs, Rn | Copy: memory[Rd] = memory[Rs], n=Rn bytes |

### Agent/Async (0x70-0x74)

| Opcode | Name | Operands | Description |
|--------|------|----------|-------------|
| 0x70 | SPAWN | Rd, addr | Spawn: Rd = create_agent(addr) |
| 0x71 | YIELD | - | Yield: give up execution slice |
| 0x72 | JOIN | Rd, Rs | Join: Rd = wait_agent(Rs) |
| 0x73 | SEND | Rd, Rs | Send: send_message(Rd, Rs) |
| 0x74 | RECV | Rd | Receive: Rd = recv_message() |

---

## Binary Format

### Single Register Instruction
```
[opcode] [reg]        (2 bytes)
```
Example: `02 05` = MOV R0, R5

### Two Register Instruction
```
[opcode] [reg_byte]  (2 bytes, reg_byte = (Rd << 4) | Rs)
```
Example: `10 12` = ADD R1, R2

### Immediate Instruction
```
[opcode] [reg] [imm_bytes...]
```
Example: `03 00 2A` = MOVI R0, 42

### Jump/Call Instruction
```
[opcode] [addr_bytes...]
```
Example: `30 10 00` = JMP 16

---

## Flag Register

```
Bit 0: Z (Zero)
Bit 1: C (Carry) 
Bit 2: N (Negative)
Bit 3: P (Parity)
```

---

## Example Programs

### ping.bin (print "ping")
```
03 00 70     ; MOVI R0, 112 ('p')
51           ; OUT R0
03 00 6F     ; MOVI R0, 111 ('o')
51           ; OUT R0
03 00 6E     ; MOVI R0, 110 ('n')
51           ; OUT R0
03 00 67     ; MOVI R0, 103 ('g')
51           ; OUT R0
01           ; HALT
```

### add.bin (compute 5 + 3, output result)
```
03 00 05     ; MOVI R0, 5
03 01 03     ; MOVI R1, 3
10 01        ; ADD R0, R1
51           ; OUT R0
01           ; HALT
```

### fib.bin (compute fibonacci(5) = 5)
```
03 00 05     ; MOVI R0, 5    ; n = 5
03 01 00     ; MOVI R1, 0    ; a = 0
03 02 01     ; MOVI R2, 1    ; b = 1
20 00 01     ; CMP R0, R1    ; n == 0?
31 14 00     ; JZ 20          ; if zero, result is in R1
03 03 01     ; MOVI R3, 1    ; i = 1
15 03 00     ; SUB R3, R0    ; i - n
32 14 00     ; JNZ 20         ; if not zero, continue
30 1C 00     ; JMP 28         ; done
10 12        ; ADD R1, R2    ; tmp = a + b
02 21        ; MOV R2, R1    ; b = tmp
02 10        ; MOV R1, R0    ; a = tmp
15 03 01     ; SUB R3, R1    ; i++
30 EA FF     ; JMP -22       ; loop
51           ; OUT R1        ; output result
01           ; HALT
```

---

## Execution Model

1. Load program into memory at address 0
2. Set PC = 0, SP = 255, FLAGS = 0
3. Fetch: opcode = memory[PC], PC++
4. Decode: determine instruction type
5. Execute: perform operation
6. Repeat until HALT

---

## Version History

- v0.1: Stack-based, 1-byte opcodes, basic ops
- v0.2: Added control flow, I/O
- v0.3: Full register-based, agent/async ops, variable-length encoding