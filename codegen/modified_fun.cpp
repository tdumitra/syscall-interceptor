/* (c) Tudor Dumitras, 2006-2007 */

#include "interceptor.h"
#include "interc_defs.h"
#include "tracec.h"

/* 
 * Define global state object.
 * Constructor will initialize the interceptor before 
 * any other code is executed.
 */
InterceptorState interceptorState;


static int indent = 0;



extern "C" 
void
exit(int status) throw()
{
  print_trace ("%*sexit(%d)...\n", indent, "",
	       status);
  indent+=2;

  /* call the real exit function */
  real_exit (status);

  indent-=2;
  print_trace ("%*sexit(%d)\n", indent, "", 
	       status);
}

extern "C" 
int
socket(int domain, int type, int protocol) throw()
{
  int retval;

  print_trace ("%*ssocket(%d, %d, %d)=...\n", indent, "",
	       domain, type, protocol);
  indent+=2;

  /* call the real socket function */
  retval = real_socket (domain, type, protocol);

  indent-=2;
  print_trace ("%*ssocket(%d, %d, %d)=%d\n", indent, "", 
	       domain, type, protocol, retval);

  return retval;
}

extern "C" 
pid_t
getpid(void) throw()
{
  pid_t retval;

  print_trace ("%*sgetpid()=...\n", indent, ""
	       );
  indent+=2;

  /* call the real getpid function */
  retval = real_getpid ();

  indent-=2;
  print_trace ("%*sgetpid()=%d\n", indent, "" 
	       , retval);

  return retval;
}

extern "C" 
ssize_t
write(int fd, const void *buf, size_t count) 
{
  ssize_t retval;

  print_trace ("%*swrite(%d, %p, %d)=...\n", indent, "",
	       fd, buf, count);
  indent+=2;

  /* call the real write function */
  retval = real_write (fd, buf, count);

  indent-=2;
  print_trace ("%*swrite(%d, %p, %d)=%d\n", indent, "", 
	       fd, buf, count, retval);

  return retval;
}

extern "C" 
ssize_t
read(int fd, void *buf, size_t count) 
{
  ssize_t retval;

  print_trace ("%*sread(%d, %p, %d)=...\n", indent, "",
	       fd, buf, count);
  indent+=2;

  /* call the real read function */
  retval = real_read (fd, buf, count);

  indent-=2;
  print_trace ("%*sread(%d, %p, %d)=%d\n", indent, "", 
	       fd, buf, count, retval);

  return retval;
}

extern "C" 
ssize_t
readv(int fd, const struct iovec *vector, int count) 
{
  ssize_t retval;

  print_trace ("%*sreadv(%d, %p, %d)=...\n", indent, "",
	       fd, vector, count);
  indent+=2;

  /* call the real readv function */
  retval = real_readv (fd, vector, count);

  indent-=2;
  print_trace ("%*sreadv(%d, %p, %d)=%d\n", indent, "", 
	       fd, vector, count, retval);

  return retval;
}

extern "C" 
ssize_t
writev(int fd, const struct iovec *vector, int count) 
{
  ssize_t retval;

  print_trace ("%*swritev(%d, %p, %d)=...\n", indent, "",
	       fd, vector, count);
  indent+=2;

  /* call the real writev function */
  retval = real_writev (fd, vector, count);

  indent-=2;
  print_trace ("%*swritev(%d, %p, %d)=%d\n", indent, "", 
	       fd, vector, count, retval);

  return retval;
}

extern "C" 
int
listen(int sockfd, int backlog) throw()
{
  int retval;

  print_trace ("%*slisten(%d, %d)=...\n", indent, "",
	       sockfd, backlog);
  indent+=2;

  /* call the real listen function */
  retval = real_listen (sockfd, backlog);

  indent-=2;
  print_trace ("%*slisten(%d, %d)=%d\n", indent, "", 
	       sockfd, backlog, retval);

  return retval;
}

extern "C" 
int
accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) 
{
  int retval;

  print_trace ("%*saccept(%d, %p, %p)=...\n", indent, "",
	       sockfd, addr, addrlen);
  indent+=2;

  /* call the real accept function */
  retval = real_accept (sockfd, addr, addrlen);

  indent-=2;
  print_trace ("%*saccept(%d, %p, %p)=%d\n", indent, "", 
	       sockfd, addr, addrlen, retval);

  return retval;
}

extern "C" 
int
bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen) throw()
{
  int retval;

  print_trace ("%*sbind(%d, %p, %d)=...\n", indent, "",
	       sockfd, my_addr, addrlen);
  indent+=2;

  /* call the real bind function */
  retval = real_bind (sockfd, my_addr, addrlen);

  indent-=2;
  print_trace ("%*sbind(%d, %p, %d)=%d\n", indent, "", 
	       sockfd, my_addr, addrlen, retval);

  return retval;
}

extern "C" 
int
connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen) 
{
  int retval;

  print_trace ("%*sconnect(%d, %p, %d)=...\n", indent, "",
	       sockfd, serv_addr, addrlen);
  indent+=2;

  /* call the real connect function */
  retval = real_connect (sockfd, serv_addr, addrlen);

  indent-=2;
  print_trace ("%*sconnect(%d, %p, %d)=%d\n", indent, "", 
	       sockfd, serv_addr, addrlen, retval);

  return retval;
}

extern "C" 
int
select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) 
{
  int retval;

  print_trace ("%*sselect(%d, %p, %p, %p, %p)=...\n", indent, "",
	       n, readfds, writefds, exceptfds, timeout);
  indent+=2;

  /* call the real select function */
  retval = real_select (n, readfds, writefds, exceptfds, timeout);

  indent-=2;
  print_trace ("%*sselect(%d, %p, %p, %p, %p)=%d\n", indent, "", 
	       n, readfds, writefds, exceptfds, timeout, retval);

  return retval;
}

extern "C" 
int
pselect(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timespec *timeout, const sigset_t *sigmask) 
{
  int retval;

  print_trace ("%*spselect(%d, %p, %p, %p, %p, %p)=...\n", indent, "",
	       n, readfds, writefds, exceptfds, timeout, sigmask);
  indent+=2;

  /* call the real pselect function */
  retval = real_pselect (n, readfds, writefds, exceptfds, timeout, sigmask);

  indent-=2;
  print_trace ("%*spselect(%d, %p, %p, %p, %p, %p)=%d\n", indent, "", 
	       n, readfds, writefds, exceptfds, timeout, sigmask, retval);

  return retval;
}

extern "C" 
int
poll(struct pollfd *ufds, nfds_t nfds, int timeout) 
{
  int retval;

  print_trace ("%*spoll(%p, %d, %d)=...\n", indent, "",
	       ufds, nfds, timeout);
  indent+=2;

  /* call the real poll function */
  retval = real_poll (ufds, nfds, timeout);

  indent-=2;
  print_trace ("%*spoll(%p, %d, %d)=%d\n", indent, "", 
	       ufds, nfds, timeout, retval);

  return retval;
}

extern "C" 
int
close(int fd) 
{
  int retval;

  print_trace ("%*sclose(%d)=...\n", indent, "",
	       fd);
  indent+=2;

  /* call the real close function */
  retval = real_close (fd);

  indent-=2;
  print_trace ("%*sclose(%d)=%d\n", indent, "", 
	       fd, retval);

  return retval;
}

extern "C" 
int
shutdown(int s, int how) throw()
{
  int retval;

  print_trace ("%*sshutdown(%d, %d)=...\n", indent, "",
	       s, how);
  indent+=2;

  /* call the real shutdown function */
  retval = real_shutdown (s, how);

  indent-=2;
  print_trace ("%*sshutdown(%d, %d)=%d\n", indent, "", 
	       s, how, retval);

  return retval;
}

extern "C" 
struct hostent *
gethostbyname(const char *name) 
{
  struct hostent * retval;

  print_trace ("%*sgethostbyname(%s)=...\n", indent, "",
	       name);
  indent+=2;

  /* call the real gethostbyname function */
  retval = real_gethostbyname (name);

  indent-=2;
  print_trace ("%*sgethostbyname(%p)=%s\n", indent, "", 
	       name, retval);

  return retval;
}

extern "C" 
struct hostent *
gethostbyaddr(const void *addr, unsigned int len, int type) 
{
  struct hostent * retval;

  print_trace ("%*sgethostbyaddr(%p, %d, %d)=...\n", indent, "",
	       addr, len, type);
  indent+=2;

  /* call the real gethostbyaddr function */
  retval = real_gethostbyaddr (addr, len, type);

  indent-=2;
  print_trace ("%*sgethostbyaddr(%p, %d, %d)=%d\n", indent, "", 
	       addr, len, type, retval);

  return retval;
}

extern "C" 
int
getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen) throw()
{
  int retval;

  print_trace ("%*sgetsockopt(%d, %d, %d, %p, %p)=...\n", indent, "",
	       s, level, optname, optval, optlen);
  indent+=2;

  /* call the real getsockopt function */
  retval = real_getsockopt (s, level, optname, optval, optlen);

  indent-=2;
  print_trace ("%*sgetsockopt(%d, %d, %d, %p, %p)=%d\n", indent, "", 
	       s, level, optname, optval, optlen, retval);

  return retval;
}

extern "C" 
int
setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen) throw()
{
  int retval;

  print_trace ("%*ssetsockopt(%d, %d, %d, %p, %d)=...\n", indent, "",
	       s, level, optname, optval, optlen);
  indent+=2;

  /* call the real setsockopt function */
  retval = real_setsockopt (s, level, optname, optval, optlen);

  indent-=2;
  print_trace ("%*ssetsockopt(%d, %d, %d, %p, %d)=%d\n", indent, "", 
	       s, level, optname, optval, optlen, retval);

  return retval;
}

extern "C" 
int
socketpair(int d, int type, int protocol, int sv[2]) throw()
{
  int retval;

  print_trace ("%*ssocketpair(%d, %d, %d, %d)=...\n", indent, "",
	       d, type, protocol, sv);
  indent+=2;

  /* call the real socketpair function */
  retval = real_socketpair (d, type, protocol, sv);

  indent-=2;
  print_trace ("%*ssocketpair(%d, %d, %d, %d)=%d\n", indent, "", 
	       d, type, protocol, sv, retval);

  return retval;
}

extern "C" 
ssize_t
recv(int s, void *buf, size_t len, int flags) 
{
  ssize_t retval;

  print_trace ("%*srecv(%d, %p, %d, %d)=...\n", indent, "",
	       s, buf, len, flags);
  indent+=2;

  /* call the real recv function */
  retval = real_recv (s, buf, len, flags);

  indent-=2;
  print_trace ("%*srecv(%d, %p, %d, %d)=%d\n", indent, "", 
	       s, buf, len, flags, retval);

  return retval;
}

extern "C" 
ssize_t
recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen) 
{
  ssize_t retval;

  print_trace ("%*srecvfrom(%d, %p, %d, %d, %p, %p)=...\n", indent, "",
	       s, buf, len, flags, from, fromlen);
  indent+=2;

  /* call the real recvfrom function */
  retval = real_recvfrom (s, buf, len, flags, from, fromlen);

  indent-=2;
  print_trace ("%*srecvfrom(%d, %p, %d, %d, %p, %p)=%d\n", indent, "", 
	       s, buf, len, flags, from, fromlen, retval);

  return retval;
}

extern "C" 
ssize_t
recvmsg(int s, struct msghdr *msg, int flags) 
{
  ssize_t retval;

  print_trace ("%*srecvmsg(%d, %p, %d)=...\n", indent, "",
	       s, msg, flags);
  indent+=2;

  /* call the real recvmsg function */
  retval = real_recvmsg (s, msg, flags);

  indent-=2;
  print_trace ("%*srecvmsg(%d, %p, %d)=%d\n", indent, "", 
	       s, msg, flags, retval);

  return retval;
}

extern "C" 
ssize_t
send(int s, const void *buf, size_t len, int flags) 
{
  ssize_t retval;

  print_trace ("%*ssend(%d, %p, %d, %d)=...\n", indent, "",
	       s, buf, len, flags);
  indent+=2;

  /* call the real send function */
  retval = real_send (s, buf, len, flags);

  indent-=2;
  print_trace ("%*ssend(%d, %p, %d, %d)=%d\n", indent, "", 
	       s, buf, len, flags, retval);

  return retval;
}

extern "C" 
ssize_t
sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen) 
{
  ssize_t retval;

  print_trace ("%*ssendto(%d, %p, %d, %d, %p, %d)=...\n", indent, "",
	       s, buf, len, flags, to, tolen);
  indent+=2;

  /* call the real sendto function */
  retval = real_sendto (s, buf, len, flags, to, tolen);

  indent-=2;
  print_trace ("%*ssendto(%d, %p, %d, %d, %p, %d)=%d\n", indent, "", 
	       s, buf, len, flags, to, tolen, retval);

  return retval;
}

extern "C" 
ssize_t
sendmsg(int s, const struct msghdr *msg, int flags) 
{
  ssize_t retval;

  print_trace ("%*ssendmsg(%d, %p, %d)=...\n", indent, "",
	       s, msg, flags);
  indent+=2;

  /* call the real sendmsg function */
  retval = real_sendmsg (s, msg, flags);

  indent-=2;
  print_trace ("%*ssendmsg(%d, %p, %d)=%d\n", indent, "", 
	       s, msg, flags, retval);

  return retval;
}

extern "C" 
int
execve(const  char  *filename,  char  *const  argv[], char *const envp[]) throw()
{
  int retval;

  print_trace ("%*sexecve(%s, %s, %s)=...\n", indent, "",
	       filename, argv, envp);
  indent+=2;

  /* call the real execve function */
  retval = real_execve (filename, argv, envp);

  indent-=2;
  print_trace ("%*sexecve(%p, %s, %s)=%d\n", indent, "", 
	       filename, argv, envp, retval);

  return retval;
}

extern "C" 
pid_t
fork(void) throw()
{
  pid_t retval;

  print_trace ("%*sfork()=...\n", indent, ""
	       );
  indent+=2;

  /* call the real fork function */
  retval = real_fork ();

  indent-=2;
  print_trace ("%*sfork()=%d\n", indent, "" 
	       , retval);

  return retval;
}
