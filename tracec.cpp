/* (c) Tudor Dumitras, 2006-2007 */
#include "tracec.h"
#include "interc_defs.h"
#include <limits.h>
#include <libgen.h>
#include <string.h>

/* 
   Assuming that the following functions are not intercepted:
   - sprintf
   - vsnprintf
   - open
   - signal
   - strcpy
   - basename
 */


/* Local variables of the trace client */
static int    fd = -1;                 /* named pipe */
static pid_t  my_pid = -1;             /* pid of the current process */
static char   my_name[NAME_MAX] = "";  /* name of the current process */


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

  update_trace();
}

void update_trace (void) 
{
  char path[PATH_MAX];
  char cmdline[BUF_SIZE];
  int file;

  /* Get the current process id */
  my_pid = real_getpid();
  
  /* Get the process name */
  (void) sprintf (path, "/proc/%d/cmdline", my_pid);
  file = open (path, O_RDONLY);
  (void) real_read (file, cmdline, BUF_SIZE);
  /* The path and arguments in cmdline are 
     separated by '\0' characters */
  (void) strcpy (my_name, basename(cmdline));
  (void) real_close (file);
}

void print_trace (const char* fmt, ...)
{
  va_list args;
  char buf[BUF_SIZE] = "";
  int cnt = 0, to_write = 0;;

  /* Format the output string */
  va_start(args, fmt);
  cnt += sprintf(buf, "%*d %s\t", PRE_CHAR-1, my_pid, my_name);
  cnt += vsnprintf(buf+cnt, BUF_SIZE-cnt, fmt, args);
  va_end(args);

  /* Output the trace message */
  to_write = cnt > BUF_SIZE ? BUF_SIZE : cnt; 
  cnt = 0;
  while ((cnt += real_write (fd, buf+cnt, to_write)) < to_write) {
    /* repeat */ ;
  }
}

void print_msg (const char* fmt, ...)
{
  va_list args;
  char buf[BUF_SIZE] = "";
  int cnt = 0, to_write = 0;;

  /* Format the output string */
  va_start(args, fmt);
  cnt += vsnprintf(buf, BUF_SIZE, fmt, args);
  va_end(args);

  /* Output the trace message */
  to_write = cnt > BUF_SIZE ? BUF_SIZE : cnt; 
  cnt = 0;
  while ((cnt += real_write (fd, buf+cnt, to_write-cnt)) < to_write) {
    /* repeat */ ;
  }
}
