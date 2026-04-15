#include <string.h>
extern void di_runtime_set_argv(int argc, char **argv);
extern int di_runtime_argc(void);
extern const char *di_runtime_argv(int i);
extern const char *di_runtime_getenv(const char *name);
extern int di_runtime_system(const char *cmd);
extern const char *di_runtime_read_file(const char *path);
extern int di_runtime_file_size(const char *path);
extern int di_runtime_str_len(const char *s);
extern int di_runtime_str_byte(const char *s, int i);
extern const char *di_runtime_str_slice(const char *s, int start, int len);
extern int di_runtime_str_eq(const char *a, const char *b);
extern const char *di_runtime_int_to_str(int x);
extern int di_runtime_int_vec_new(void);
extern int di_runtime_int_vec_len(int handle);
extern int di_runtime_int_vec_get(int handle, int index);
extern int di_runtime_int_vec_push(int handle, int value);
extern void di_runtime_int_vec_free(int handle);
extern int di_runtime_str_builder_new(void);
extern void di_runtime_str_builder_append(int handle, const char *s);
extern int di_runtime_str_builder_len(int handle);
extern const char *di_runtime_str_builder_to_str(int handle);
extern void di_runtime_str_builder_free(int handle);
extern void di_runtime_print_int(int x);
extern void di_runtime_print_str(const char *x);
extern void di_runtime_print_hex(int x);
extern int di_runtime_write(int fd, const char *x);
extern void di_runtime_exit(int status);
extern void di_runtime_abort(void);
static int di_runtime_write_stdout(const char *s) { return di_runtime_write(1, s); }
static int di_runtime_write_stderr(const char *s) { return di_runtime_write(2, s); }

int di_user_main();

int di_user_main() {
    di_runtime_print_str("=== DBIS Assembler v0.3 ===\\n");
    di_runtime_print_str("Full assembler in Diva\\n\\n");
    di_runtime_print_str("Ping program ('Ping'):\\n");
    di_runtime_print_str("  MOVI R0, 80; OUT R0\\n");
    di_runtime_print_str("  MOVI R0, 105; OUT R0\\n");
    di_runtime_print_str("  MOVI R0, 110; OUT R0\\n");
    di_runtime_print_str("  MOVI R0, 103; OUT R0\\n");
    di_runtime_print_str("  HALT\\n");
    di_runtime_print_str("  Bytes: 3 0 80 81 0 3 0 105 81 0 3 0 110 81 0 3 0 103 81 0 1\\n\\n");
    di_runtime_print_str("Add program (5+3=8):\\n");
    di_runtime_print_str("  MOVI R0, 5\\n");
    di_runtime_print_str("  MOVI R1, 3\\n");
    di_runtime_print_str("  ADD R0, R1\\n");
    di_runtime_print_str("  OUT R0\\n");
    di_runtime_print_str("  HALT\\n");
    di_runtime_print_str("  Bytes: 3 0 5 3 1 3 16 0 1 81 0 1\\n\\n");
    di_runtime_print_str("Sub program (10-3=7):\\n");
    di_runtime_print_str("  MOVI R0, 10\\n");
    di_runtime_print_str("  MOVI R1, 3\\n");
    di_runtime_print_str("  SUB R0, R1\\n");
    di_runtime_print_str("  OUT R0\\n");
    di_runtime_print_str("  HALT\\n");
    di_runtime_print_str("  Bytes: 3 0 10 3 1 3 17 0 1 81 0 1\\n\\n");
    di_runtime_print_str("Mul program (4*3=12):\\n");
    di_runtime_print_str("  MOVI R0, 4\\n");
    di_runtime_print_str("  MOVI R1, 3\\n");
    di_runtime_print_str("  MUL R0, R1\\n");
    di_runtime_print_str("  OUT R0\\n");
    di_runtime_print_str("  HALT\\n");
    di_runtime_print_str("  Bytes: 3 0 4 3 1 3 18 0 1 81 0 1\\n\\n");
    di_runtime_print_str("Div program (12/4=3):\\n");
    di_runtime_print_str("  MOVI R0, 12\\n");
    di_runtime_print_str("  MOVI R1, 4\\n");
    di_runtime_print_str("  DIV R0, R1\\n");
    di_runtime_print_str("  OUT R0\\n");
    di_runtime_print_str("  HALT\\n");
    di_runtime_print_str("  Bytes: 3 0 12 3 1 4 19 0 1 81 0 1\\n\\n");
    di_runtime_print_str("Loop program (sum 1-10=55):\\n");
    di_runtime_print_str("  MOVI R0, 0\\n");
    di_runtime_print_str("  MOVI R1, 1\\n");
    di_runtime_print_str("  CMP R1, 10\\n");
    di_runtime_print_str("  JZ DONE\\n");
    di_runtime_print_str("  ADD R0, R1\\n");
    di_runtime_print_str("  ADD R1, 1\\n");
    di_runtime_print_str("  JMP LOOP\\n");
    di_runtime_print_str("DONE:\\n");
    di_runtime_print_str("  OUT R0\\n");
    di_runtime_print_str("  HALT\\n");
    di_runtime_print_str("  Bytes: 3 0 0 3 1 1 3 2 10 32 1 4 16 0 1 3 1 1 3 2 10 48 2 81 0 1\\n\\n");
    di_runtime_print_str("Opcode reference:\\n");
    di_runtime_print_str("  0x00 NOP   0x01 HALT  0x03 MOVI  0x10 ADD\\n");
    di_runtime_print_str("  0x11 SUB   0x12 MUL   0x13 DIV   0x20 CMP\\n");
    di_runtime_print_str("  0x30 JMP   0x31 JZ    0x32 JNZ  0x37 CALL\\n");
    di_runtime_print_str("  0x38 RET   0x40 PUSH  0x41 POP   0x50 IN\\n");
    di_runtime_print_str("  0x51 OUT\\n\\n");
    di_runtime_print_str("=== Ready ===\\n");
    return 0;
}

int di_user_main(void);
int main(int argc, char **argv) {
    di_runtime_set_argv(argc, argv);
    return di_user_main();
}
