/* (c) Tudor Dumitras, 2006-2007 */

#ifndef __INTERCEPTED_DEFS_
#define __INTERCEPTED_DEFS_

/* Headers where the intercepted sys calls are defined */
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/poll.h>


/************************************************************/


/* Wrappers for the real system calls -- declarations */
extern "C" void real_exit(int status) throw();
extern "C" int real_socket(int domain, int type, int protocol) throw();
extern "C" pid_t real_getpid(void) throw();
extern "C" ssize_t real_write(int fd, const void *buf, size_t count);
extern "C" ssize_t real_read(int fd, void *buf, size_t count);
extern "C" ssize_t real_readv(int fd, const struct iovec *vector, int count);
extern "C" ssize_t real_writev(int fd, const struct iovec *vector, int count);
extern "C" int real_listen(int sockfd, int backlog) throw(); 
extern "C" int real_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
extern "C" int real_bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen) throw();
extern "C" int real_connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
extern "C" int real_select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
extern "C" int real_pselect(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timespec *timeout, const sigset_t *sigmask);
extern "C" int real_poll(struct pollfd *ufds, nfds_t nfds, int timeout);
extern "C" int real_close(int fd);
extern "C" int real_shutdown(int s, int how) throw();
extern "C" struct hostent *real_gethostbyname(const char *name);
extern "C" struct hostent *real_gethostbyaddr(const void *addr, unsigned int len, int type);
extern "C" int real_getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen) throw();
extern "C" int real_setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen) throw();
extern "C" int real_socketpair(int d, int type, int protocol, int sv[2]) throw();
extern "C" ssize_t real_recv(int s, void *buf, size_t len, int flags);
extern "C" ssize_t real_recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);
extern "C" ssize_t real_recvmsg(int s, struct msghdr *msg, int flags);
extern "C" ssize_t real_send(int s, const void *buf, size_t len, int flags);
extern "C" ssize_t real_sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
extern "C" ssize_t real_sendmsg(int s, const struct msghdr *msg, int flags);
extern "C" int real_execve(const  char  *filename,  char  *const  argv[], char *const envp[]) throw();
extern "C" pid_t real_fork(void) throw();


/************************************************************/


class FunctionPointers {
 public:
  /* Initilize pointers to the default functions. */
  static void init_fptrs() throw();
  
 public: 
  /* Pointers to the default functions */
  static void (*fptr_exit) (int);
  static int (*fptr_socket) (int, int, int);
  static pid_t (*fptr_getpid) (void);
  static ssize_t (*fptr_write) (int, const void *, size_t);
  static ssize_t (*fptr_read) (int, void *, size_t);
  static ssize_t (*fptr_readv) (int, const struct iovec *, int);
  static ssize_t (*fptr_writev) (int, const struct iovec *, int);
  static int (*fptr_listen) (int, int);
  static int (*fptr_accept) (int, struct sockaddr *, socklen_t *);
  static int (*fptr_bind) (int, const struct sockaddr *, socklen_t);
  static int (*fptr_connect) (int, const struct sockaddr *, socklen_t);
  static int (*fptr_select) (int, fd_set *, fd_set *, fd_set *, struct timeval *);
  static int (*fptr_pselect) (int, fd_set *, fd_set *, fd_set *, const struct timespec *, const sigset_t *);
  static int (*fptr_poll) (struct pollfd *, nfds_t, int);
  static int (*fptr_close) (int);
  static int (*fptr_shutdown) (int, int);
  static struct hostent * (*fptr_gethostbyname) (const char *);
  static struct hostent * (*fptr_gethostbyaddr) (const void *, unsigned int, int);
  static int (*fptr_getsockopt) (int, int, int, void *, socklen_t *);
  static int (*fptr_setsockopt) (int, int, int, const void *, socklen_t);
  static int (*fptr_socketpair) (int, int, int, int*);
  static ssize_t (*fptr_recv) (int, void *, size_t, int);
  static ssize_t (*fptr_recvfrom) (int, void *, size_t, int, struct sockaddr *, socklen_t *);
  static ssize_t (*fptr_recvmsg) (int, struct msghdr *, int);
  static ssize_t (*fptr_send) (int, const void *, size_t, int);
  static ssize_t (*fptr_sendto) (int, const void *, size_t, int, const struct sockaddr *, socklen_t);
  static ssize_t (*fptr_sendmsg) (int, const struct msghdr *, int);
  static int (*fptr_execve) (const  char  *, char  *const*, char *const*);
  static pid_t (*fptr_fork) (void);
};


/************************************************************/


/* Wrappers for the real system calls -- definitions */
extern "C" {


inline
void 
real_exit(int status) throw()
{
  (void)(*FunctionPointers::fptr_exit) (status);
}

inline 
int 
real_socket(int domain, int type, int protocol) throw()
{
  int retval;
  retval = (*FunctionPointers::fptr_socket) (domain, type, protocol);
  return retval;
}

inline 
pid_t 
real_getpid(void) throw()
{
  pid_t retval;
  retval = (*FunctionPointers::fptr_getpid) ();
  return retval;
}

inline 
ssize_t 
real_write(int fd, const void *buf, size_t count) 
{
  ssize_t retval;
  retval = (*FunctionPointers::fptr_write) (fd, buf, count);
  return retval;
}

inline 
ssize_t 
real_read(int fd, void *buf, size_t count) 
{
  ssize_t retval;
  retval = (*FunctionPointers::fptr_read) (fd, buf, count);
  return retval;
}

inline 
ssize_t 
real_readv(int fd, const struct iovec *vector, int count) 
{
  ssize_t retval;
  retval = (*FunctionPointers::fptr_readv) (fd, vector, count);
  return retval;
}

inline 
ssize_t 
real_writev(int fd, const struct iovec *vector, int count) 
{
  ssize_t retval;
  retval = (*FunctionPointers::fptr_writev) (fd, vector, count);
  return retval;
}

inline 
int 
real_listen(int sockfd, int backlog) throw()
{
  int retval;
  retval = (*FunctionPointers::fptr_listen) (sockfd, backlog);
  return retval;
}

inline 
int 
real_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) 
{
  int retval;
  retval = (*FunctionPointers::fptr_accept) (sockfd, addr, addrlen);
  return retval;
}

inline 
int 
real_bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen) throw()
{
  int retval;
  retval = (*FunctionPointers::fptr_bind) (sockfd, my_addr, addrlen);
  return retval;
}

inline 
int 
real_connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen) 
{
  int retval;
  retval = (*FunctionPointers::fptr_connect) (sockfd, serv_addr, addrlen);
  return retval;
}

inline 
int 
real_select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) 
{
  int retval;
  retval = (*FunctionPointers::fptr_select) (n, readfds, writefds, exceptfds, timeout);
  return retval;
}

inline 
int 
real_pselect(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timespec *timeout, const sigset_t *sigmask) 
{
  int retval;
  retval = (*FunctionPointers::fptr_pselect) (n, readfds, writefds, exceptfds, timeout, sigmask);
  return retval;
}

inline 
int 
real_poll(struct pollfd *ufds, nfds_t nfds, int timeout) 
{
  int retval;
  retval = (*FunctionPointers::fptr_poll) (ufds, nfds, timeout);
  return retval;
}

inline 
int 
real_close(int fd) 
{
  int retval;
  retval = (*FunctionPointers::fptr_close) (fd);
  return retval;
}

inline 
int 
real_shutdown(int s, int how) throw()
{
  int retval;
  retval = (*FunctionPointers::fptr_shutdown) (s, how);
  return retval;
}

inline 
struct hostent * 
real_gethostbyname(const char *name) 
{
  struct hostent * retval;
  retval = (*FunctionPointers::fptr_gethostbyname) (name);
  return retval;
}

inline 
struct hostent * 
real_gethostbyaddr(const void *addr, unsigned int len, int type) 
{
  struct hostent * retval;
  retval = (*FunctionPointers::fptr_gethostbyaddr) (addr, len, type);
  return retval;
}

inline 
int 
real_getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen) throw()
{
  int retval;
  retval = (*FunctionPointers::fptr_getsockopt) (s, level, optname, optval, optlen);
  return retval;
}

inline 
int 
real_setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen) throw()
{
  int retval;
  retval = (*FunctionPointers::fptr_setsockopt) (s, level, optname, optval, optlen);
  return retval;
}

inline 
int 
real_socketpair(int d, int type, int protocol, int sv[2]) throw()
{
  int retval;
  retval = (*FunctionPointers::fptr_socketpair) (d, type, protocol, sv);
  return retval;
}

inline 
ssize_t 
real_recv(int s, void *buf, size_t len, int flags) 
{
  ssize_t retval;
  retval = (*FunctionPointers::fptr_recv) (s, buf, len, flags);
  return retval;
}

inline 
ssize_t 
real_recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen) 
{
  ssize_t retval;
  retval = (*FunctionPointers::fptr_recvfrom) (s, buf, len, flags, from, fromlen);
  return retval;
}

inline 
ssize_t 
real_recvmsg(int s, struct msghdr *msg, int flags) 
{
  ssize_t retval;
  retval = (*FunctionPointers::fptr_recvmsg) (s, msg, flags);
  return retval;
}

inline 
ssize_t 
real_send(int s, const void *buf, size_t len, int flags) 
{
  ssize_t retval;
  retval = (*FunctionPointers::fptr_send) (s, buf, len, flags);
  return retval;
}

inline 
ssize_t 
real_sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen) 
{
  ssize_t retval;
  retval = (*FunctionPointers::fptr_sendto) (s, buf, len, flags, to, tolen);
  return retval;
}

inline 
ssize_t 
real_sendmsg(int s, const struct msghdr *msg, int flags) 
{
  ssize_t retval;
  retval = (*FunctionPointers::fptr_sendmsg) (s, msg, flags);
  return retval;
}

inline 
int 
real_execve(const  char  *filename,  char  *const  argv[], char *const envp[]) throw()
{
  int retval;
  retval = (*FunctionPointers::fptr_execve) (filename, argv, envp);
  return retval;
}

inline 
pid_t 
real_fork(void) throw()
{
  pid_t retval;
  retval = (*FunctionPointers::fptr_fork) ();
  return retval;
}

}

#endif
