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
    di_runtime_print_str("=== DBIS VM v0.3 - Test Suite ===\\n\\n");
    di_runtime_print_str("String output:\\n");
    di_runtime_print_str("PING: Ping!\\n");
    di_runtime_print_str("HELLO: Hello World!\\n");
    di_runtime_print_str("\\nArithmetic:\\n");
    di_runtime_print_str("ADD (5+3): ");
    di_runtime_print_int((5 + 3));
    di_runtime_print_str("\\n");
    di_runtime_print_str("SUB (10-3): ");
    di_runtime_print_int((10 - 3));
    di_runtime_print_str("\\n");
    di_runtime_print_str("MUL (4*3): ");
    di_runtime_print_int((4 * 3));
    di_runtime_print_str("\\n");
    di_runtime_print_str("DIV (12/4): ");
    di_runtime_print_int((12 / 4));
    di_runtime_print_str("\\n");
    di_runtime_print_str("\\nLoops & Math:\\n");
    di_runtime_print_str("LOOP (sum 1-10): ");
    int sum = 0;
    int i = 1;
    while ((i <= 10)) {
        sum = (sum + i);
        i = (i + 1);
    }
    di_runtime_print_int(sum);
    di_runtime_print_str("\\n");
    di_runtime_print_str("FIB (10): ");
    int n = 10;
    int a = 0;
    int b = 1;
    int j = 2;
    while ((j <= n)) {
        int tmp = (a + b);
        a = b;
        b = tmp;
        j = (j + 1);
    }
    di_runtime_print_int(b);
    di_runtime_print_str("\\n");
    di_runtime_print_str("FACT (5): ");
    int fn = 5;
    int result = 1;
    while ((fn > 1)) {
        result = (result * fn);
        fn = (fn - 1);
    }
    di_runtime_print_int(result);
    di_runtime_print_str("\\n");
    di_runtime_print_str("GCD (48,18): ");
    int ga = 48;
    int gb = 18;
    while (((ga - gb) != 0)) {
        if ((ga > gb)) {
            ga = (ga - gb);
        } else {
            gb = (gb - ga);
        }
    }
    di_runtime_print_int(ga);
    di_runtime_print_str("\\n");
    di_runtime_print_str("POW (2^8): ");
    int base = 2;
    int exp = 8;
    int pow = 1;
    while ((exp > 0)) {
        pow = (pow * base);
        exp = (exp - 1);
    }
    di_runtime_print_int(pow);
    di_runtime_print_str("\\n");
    di_runtime_print_str("PRIME (17): ");
    int pn = 17;
    int prime = 1;
    int pi = 2;
    while (((pi * pi) <= pn)) {
        if (((pn - ((pn / pi) * pi)) == 0)) {
            prime = 0;
        }
        pi = (pi + 1);
    }
    if ((prime == 1)) {
        di_runtime_print_str("yes");
    } else {
        di_runtime_print_str("no");
    }
    di_runtime_print_str("\\n");
    di_runtime_print_str("REVERSE (12345): ");
    int rn = 12345;
    int rev = 0;
    while ((rn > 0)) {
        int d = (rn - ((rn / 10) * 10));
        rev = ((rev * 10) + d);
        rn = (rn / 10);
    }
    di_runtime_print_int(rev);
    di_runtime_print_str("\\n");
    di_runtime_print_str("MAX (7,3): ");
    int x = 7;
    int y = 3;
    if ((x >= y)) {
        di_runtime_print_int(x);
    } else {
        di_runtime_print_int(y);
    }
    di_runtime_print_str("\\n");
    di_runtime_print_str("ABS (-5): ");
    int neg = (0 - 5);
    if ((neg < 0)) {
        neg = (0 - neg);
    }
    di_runtime_print_int(neg);
    di_runtime_print_str("\\n");
    di_runtime_print_str("COUNTDIGITS (12345): ");
    int cd = 12345;
    int count = 0;
    while ((cd > 0)) {
        count = (count + 1);
        cd = (cd / 10);
    }
    di_runtime_print_int(count);
    di_runtime_print_str("\\n");
    di_runtime_print_str("\\n=== All tests complete ===\\n");
    return 0;
}

int di_user_main(void);
int main(int argc, char **argv) {
    di_runtime_set_argv(argc, argv);
    return di_user_main();
}
