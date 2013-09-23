/* (c) Tudor Dumitras, 2006-2007 */
#include "tracec.h"
#include "interc_defs.h"

static int fd = -1;

/* 
   Assuming that the following functions are not intercepted:
   - sprintf
   - vsnprintf
   - open
   - signal
 */

void init_trace ()
{
  /* Open a pipe to the trace-logging process */
  signal (SIGPIPE, SIG_IGN); 
  if (fd == -1) {
    if ((fd = open(PIPE_NAME, O_WRONLY)) == -1) {
      /* The pipe does not exist; use stdout */
      fd = STDOUT_FILENO;
    }
  }
}

void print_trace (const char* fmt, ...)
{
  va_list args;
  char buf[BUF_SIZE] = "smeu";
  int cnt = 0, to_write = 0;;

  /* Format the output string */
  va_start(args, fmt);
  cnt += sprintf(buf, "%*d ", PRE_CHAR-1, real_getpid());
  cnt += vsnprintf(buf+PRE_CHAR, BUF_SIZE-PRE_CHAR, fmt, args);
  va_end(args);

  /* Output the trace message */
  to_write = cnt > BUF_SIZE ? BUF_SIZE : cnt; 
  cnt = 0;
  while ((cnt += real_write (fd, buf+cnt, to_write)) < to_write) {
    /* repeat */ ;
  }
}
