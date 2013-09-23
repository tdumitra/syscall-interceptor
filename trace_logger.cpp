/* (c) Tudor Dumitras, 2006-2007 */

#include "tracec.h"

void sigint_handler (int sig)
{
  /* Cleanup before exit */
  unlink (PIPE_NAME);
  exit(0);
}

int
main()
{
  FILE*     pipe = NULL;
  char      line[PIPE_BUF];

  /* Intercept signals */
  signal (SIGPIPE, SIG_IGN);    
  signal (SIGINT, sigint_handler);

  /* Create a named pipe and open it for reading */
  if (mkfifo(PIPE_NAME, 0666) < 0 && 
      errno != EEXIST) {
    perror ("Cannot create fifo");
    exit(-1);
  }
  if ((pipe = fopen(PIPE_NAME, "r")) == NULL) {
    perror ("Cannot open fifo for reading");
    exit(-1);
  }

  /* Read from pipe and print to screen */
  while (1) {
    if (fgets(line, PIPE_BUF, pipe) == NULL) {
      if (ferror(pipe)) {
	perror ("fgets");
      } else {  /* EOF */
	printf ("No clients connected.\n");
      }
      fclose(pipe);
      if ((pipe = fopen(PIPE_NAME, "r")) == NULL) {
	perror ("Cannot open fifo for reading");
	exit(-1);
      }
      continue;
    }
    printf ("%s", line);
  }

  /* Execution does not reach this point */
  return 0;
}
