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
    di_runtime_print_str("=== deepiri-metal-omelette ===\\n");
    di_runtime_print_str("DBIS v0.3 CLI and Disassembler\\n");
    di_runtime_print_str("Written entirely in Diva\\n\\n");
    di_runtime_print_str("Ping program opcodes:\\n");
    di_runtime_print_str("0: MOVI\\n");
    di_runtime_print_str("2: OUT\\n");
    di_runtime_print_str("4: MOVI\\n");
    di_runtime_print_str("6: OUT\\n");
    di_runtime_print_str("8: MOVI\\n");
    di_runtime_print_str("10: OUT\\n");
    di_runtime_print_str("12: MOVI\\n");
    di_runtime_print_str("14: OUT\\n");
    di_runtime_print_str("16: HALT\\n");
    di_runtime_print_str("\\nAdd program opcodes:\\n");
    di_runtime_print_str("0: MOVI R0, 5\\n");
    di_runtime_print_str("3: MOVI R1, 3\\n");
    di_runtime_print_str("6: ADD R0, R1\\n");
    di_runtime_print_str("8: OUT R0\\n");
    di_runtime_print_str("10: HALT\\n");
    di_runtime_print_str("\\n=== CLI Help ===\\n");
    di_runtime_print_str("Commands: run, asm, dis, test, help\\n");
    di_runtime_print_str("DBIS v0.3: 16 regs, 256 bytes RAM\\n\\n");
    di_runtime_print_str("=== All done ===\\n");
    return 0;
}

int di_user_main(void);
int main(int argc, char **argv) {
    di_runtime_set_argv(argc, argv);
    return di_user_main();
}
