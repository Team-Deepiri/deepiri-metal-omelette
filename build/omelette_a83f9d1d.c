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
    di_runtime_print_str("=== deepiri-metal-omelette CLI ===\\n");
    di_runtime_print_str("DBIS v0.3 - All in Diva\\n\\n");
    di_runtime_print_str("Usage:\\n");
    di_runtime_print_str("  diva run vm/omelette.diva   - Run VM with tests\\n");
    di_runtime_print_str("  diva run cli/omelette.diva - Show this help\\n\\n");
    di_runtime_print_str("Example programs (.dbis):\\n");
    di_runtime_print_str("  ping.dbis       - Print 'Ping'\\n");
    di_runtime_print_str("  add.dbis       - Add 5+3=8\\n");
    di_runtime_print_str("  fib.dbis       - Fibonacci(10)=55\\n");
    di_runtime_print_str("  factorial.dbis - 5! = 120\\n");
    di_runtime_print_str("  gcd.dbis       - GCD(48,18)=6\\n");
    di_runtime_print_str("  prime.dbis     - Check if prime\\n\\n");
    di_runtime_print_str("VM Test Suite:\\n");
    di_runtime_print_str("  String: PING, HELLO\\n");
    di_runtime_print_str("  Math: ADD, SUB, MUL, DIV\\n");
    di_runtime_print_str("  Algo: FIB, FACT, GCD, POW\\n");
    di_runtime_print_str("  Utils: PRIME, REVERSE, MAX, ABS\\n\\n");
    di_runtime_print_str("DBIS v0.3 Opcodes:\\n");
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
