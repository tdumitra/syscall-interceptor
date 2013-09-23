/* (c) Tudor Dumitras, 2006-2007 */

#ifndef __TRACEC_H_
#define __TRACEC_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>
#include <stdarg.h>
#include <fcntl.h>

#define PIPE_NAME    "/tmp/interceptor_trace.fifo"
#define BUF_SIZE     (8*PIPE_BUF)
#define PRE_CHAR     6

void init_trace ();
void update_trace (void);
void print_trace (const char* fmt, ...);
void print_msg (const char* fmt, ...);

#endif
