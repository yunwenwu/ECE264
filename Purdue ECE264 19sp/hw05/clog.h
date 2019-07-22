#ifndef __CLOG_H__
#define __CLOG_H__

const char* ANSI_RED = "\x1b[31m";
const char* ANSI_GREEN = "\x1b[32m";
const char* ANSI_YELLOW = "\x1b[33m";
const char* ANSI_BLUE = "\x1b[34m";
const char* ANSI_MAGENTA = "\x1b[35m";
const char* ANSI_CYAN = "\x1b[36m";
const char* ANSI_RESET = "\x1b[0m";

#ifdef DEBUG
#define log_msg(msg) fprintf(stderr, "%s\n", (msg))
#else
#define log_msg(msg)
#endif

#ifdef DEBUG
#define log_int(n) fprintf(stderr, "%s == %d\n", (#n), (n))
#else
#define log_int(n)
#endif

#ifdef DEBUG
#define log_str(str) fprintf(stderr, "str == %s\n", str)
#else
#define log_str(str)
#endif

#ifdef DEBUG
#define log_char(ch) fprintf(stderr, "ch == '%c'\n", ch)
#else
#define log_char(ch)
#endif

#ifdef DEBUG
#define log_addr(addr) fprintf(stderr, "addr == %p\n", addr)
#else
#define log_addr(addr)
#endif

#ifdef DEBUG
#define log_red(...) \
fprintf(stderr, "%s", ANSI_RED); \
fprintf(stderr, __VA_ARGS__); \
fprintf(stderr, "%s", ANSI_RESET);
#else
#define log_red(...)
#endif

#ifdef DEBUG
#define log_green(...) \
fprintf(stderr, "%s", ANSI_GREEN); \
fprintf(stderr, __VA_ARGS__); \
fprintf(stderr, "%s", ANSI_RESET);
#else
#define log_green(...)
#endif

#ifdef DEBUG
#define log_yellow(...) \
fprintf(stderr, "%s", ANSI_YELLOW); \
fprintf(stderr, __VA_ARGS__); \
fprintf(stderr, "%s", ANSI_RESET);
#else
#define log_yellow(...)
#endif

#ifdef DEBUG
#define log_blue(...) \
fprintf(stderr, "%s", ANSI_BLUE); \
fprintf(stderr, __VA_ARGS__); \
fprintf(stderr, "%s", ANSI_RESET);
#else
#define log_blue(...)
#endif

#ifdef DEBUG
#define log_magenta(...) \
fprintf(stderr, "%s", ANSI_MAGENTA); \
fprintf(stderr, __VA_ARGS__); \
fprintf(stderr, "%s", ANSI_RESET);
#else
#define log_magenta(...)
#endif

#ifdef DEBUG
#define log_cyan(...) \
fprintf(stderr, "%s", ANSI_CYAN); \
fprintf(stderr, __VA_ARGS__); \
fprintf(stderr, "%s", ANSI_RESET);
#else
#define log_cyan(...)
#endif

#endif
