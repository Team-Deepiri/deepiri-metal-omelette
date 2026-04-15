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
    di_runtime_print_str("Ping program bytes:\\n");
    di_runtime_print_str("3 0 80 81 0 1\\n");
    di_runtime_print_str("\\nAdd program bytes:\\n");
    di_runtime_print_str("3 0 5 3 1 3 16 0 1 81 0 1\\n");
    di_runtime_print_str("\\nFibonacci program bytes:\\n");
    di_runtime_print_str("3 0 10 3 1 0 3 2 1 3 3 2 32 32 0 17 0 3 16 1 2 2 1 3 2 1 3 3 2 48 24 81 2 1\\n");
    di_runtime_print_str("\\n=== Ready ===\\n");
    return 0;
}

int di_user_main(void);
int main(int argc, char **argv) {
    di_runtime_set_argv(argc, argv);
    return di_user_main();
}
