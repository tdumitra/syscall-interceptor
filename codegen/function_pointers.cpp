/* (c) Tudor Dumitras, 2006-2007 */

#include "interc_defs.h"
/* This is needed for RTLD_NEXT */
#ifndef __USE_GNU
#define __USE_GNU  
#endif
#include <dlfcn.h>


/* Function pointers -- definitions */
void (*FunctionPointers::fptr_exit)(int) = NULL;
int (*FunctionPointers::fptr_socket)(int, int, int) = NULL;
pid_t (*FunctionPointers::fptr_getpid)(void) = NULL;
ssize_t (*FunctionPointers::fptr_write)(int, const void *, size_t) = NULL;
ssize_t (*FunctionPointers::fptr_read)(int, void *, size_t) = NULL;
ssize_t (*FunctionPointers::fptr_readv)(int, const struct iovec *, int) = NULL;
ssize_t (*FunctionPointers::fptr_writev)(int, const struct iovec *, int) = NULL;
int (*FunctionPointers::fptr_listen)(int, int) = NULL;
int (*FunctionPointers::fptr_accept)(int, struct sockaddr *, socklen_t *) = NULL;
int (*FunctionPointers::fptr_bind)(int, const struct sockaddr *, socklen_t) = NULL;
int (*FunctionPointers::fptr_connect)(int, const struct sockaddr *, socklen_t) = NULL;
int (*FunctionPointers::fptr_select)(int, fd_set *, fd_set *, fd_set *, struct timeval *) = NULL;
int (*FunctionPointers::fptr_pselect)(int, fd_set *, fd_set *, fd_set *, const struct timespec *, const sigset_t *) = NULL;
int (*FunctionPointers::fptr_poll)(struct pollfd *, nfds_t, int) = NULL;
int (*FunctionPointers::fptr_close)(int) = NULL;
int (*FunctionPointers::fptr_shutdown)(int, int) = NULL;
struct hostent * (*FunctionPointers::fptr_gethostbyname)(const char *) = NULL;
struct hostent * (*FunctionPointers::fptr_gethostbyaddr)(const void *, unsigned int, int) = NULL;
int (*FunctionPointers::fptr_getsockopt)(int, int, int, void *, socklen_t *) = NULL;
int (*FunctionPointers::fptr_setsockopt)(int, int, int, const void *, socklen_t) = NULL;
int (*FunctionPointers::fptr_socketpair)(int, int, int, int*) = NULL;
ssize_t (*FunctionPointers::fptr_recv)(int, void *, size_t, int) = NULL;
ssize_t (*FunctionPointers::fptr_recvfrom)(int, void *, size_t, int, struct sockaddr *, socklen_t *) = NULL;
ssize_t (*FunctionPointers::fptr_recvmsg)(int, struct msghdr *, int) = NULL;
ssize_t (*FunctionPointers::fptr_send)(int, const void *, size_t, int) = NULL;
ssize_t (*FunctionPointers::fptr_sendto)(int, const void *, size_t, int, const struct sockaddr *, socklen_t) = NULL;
ssize_t (*FunctionPointers::fptr_sendmsg)(int, const struct msghdr *, int) = NULL;
int (*FunctionPointers::fptr_execve)(const  char  *, char  *const*, char *const*) = NULL;
pid_t (*FunctionPointers::fptr_fork)(void) = NULL;


/************************************************************/


/* Initilize the function pointers */
void
FunctionPointers::init_fptrs ()
     throw()
{

  /* exit() fptr */
  if (  (fptr_exit = 
	 (void (*)(int)) 
	 dlsym(RTLD_NEXT, "exit")) 
	== NULL) {
    /* Missing library; cannot continue */
    _exit(-1);
  }

  /* socket() fptr */
  if (  (fptr_socket = 
	 (int (*)(int, int, int)) 
	 dlsym(RTLD_NEXT, "socket")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* getpid() fptr */
  if (  (fptr_getpid = 
	 (pid_t (*)(void)) 
	 dlsym(RTLD_NEXT, "getpid")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* write() fptr */
  if (  (fptr_write = 
	 (ssize_t (*)(int, const void *, size_t)) 
	 dlsym(RTLD_NEXT, "write")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* read() fptr */
  if (  (fptr_read = 
	 (ssize_t (*)(int, void *, size_t)) 
	 dlsym(RTLD_NEXT, "read")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* readv() fptr */
  if (  (fptr_readv = 
	 (ssize_t (*)(int, const struct iovec *, int)) 
	 dlsym(RTLD_NEXT, "readv")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* writev() fptr */
  if (  (fptr_writev = 
	 (ssize_t (*)(int, const struct iovec *, int)) 
	 dlsym(RTLD_NEXT, "writev")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* listen() fptr */
  if (  (fptr_listen = 
	 (int (*)(int, int)) 
	 dlsym(RTLD_NEXT, "listen")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* accept() fptr */
  if (  (fptr_accept = 
	 (int (*)(int, struct sockaddr *, socklen_t *)) 
	 dlsym(RTLD_NEXT, "accept")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* bind() fptr */
  if (  (fptr_bind = 
	 (int (*)(int, const struct sockaddr *, socklen_t)) 
	 dlsym(RTLD_NEXT, "bind")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* connect() fptr */
  if (  (fptr_connect = 
	 (int (*)(int, const struct sockaddr *, socklen_t)) 
	 dlsym(RTLD_NEXT, "connect")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* select() fptr */
  if (  (fptr_select = 
	 (int (*)(int, fd_set *, fd_set *, fd_set *, struct timeval *)) 
	 dlsym(RTLD_NEXT, "select")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* pselect() fptr */
  if (  (fptr_pselect = 
	 (int (*)(int, fd_set *, fd_set *, fd_set *, const struct timespec *, const sigset_t *)) 
	 dlsym(RTLD_NEXT, "pselect")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* poll() fptr */
  if (  (fptr_poll = 
	 (int (*)(struct pollfd *, nfds_t, int)) 
	 dlsym(RTLD_NEXT, "poll")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* close() fptr */
  if (  (fptr_close = 
	 (int (*)(int)) 
	 dlsym(RTLD_NEXT, "close")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* shutdown() fptr */
  if (  (fptr_shutdown = 
	 (int (*)(int, int)) 
	 dlsym(RTLD_NEXT, "shutdown")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* gethostbyname() fptr */
  if (  (fptr_gethostbyname = 
	 (struct hostent * (*)(const char *)) 
	 dlsym(RTLD_NEXT, "gethostbyname")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* gethostbyaddr() fptr */
  if (  (fptr_gethostbyaddr = 
	 (struct hostent * (*)(const void *, unsigned int, int)) 
	 dlsym(RTLD_NEXT, "gethostbyaddr")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* getsockopt() fptr */
  if (  (fptr_getsockopt = 
	 (int (*)(int, int, int, void *, socklen_t *)) 
	 dlsym(RTLD_NEXT, "getsockopt")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* setsockopt() fptr */
  if (  (fptr_setsockopt = 
	 (int (*)(int, int, int, const void *, socklen_t)) 
	 dlsym(RTLD_NEXT, "setsockopt")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* socketpair() fptr */
  if (  (fptr_socketpair = 
	 (int (*)(int, int, int, int*)) 
	 dlsym(RTLD_NEXT, "socketpair")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* recv() fptr */
  if (  (fptr_recv = 
	 (ssize_t (*)(int, void *, size_t, int)) 
	 dlsym(RTLD_NEXT, "recv")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* recvfrom() fptr */
  if (  (fptr_recvfrom = 
	 (ssize_t (*)(int, void *, size_t, int, struct sockaddr *, socklen_t *)) 
	 dlsym(RTLD_NEXT, "recvfrom")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* recvmsg() fptr */
  if (  (fptr_recvmsg = 
	 (ssize_t (*)(int, struct msghdr *, int)) 
	 dlsym(RTLD_NEXT, "recvmsg")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* send() fptr */
  if (  (fptr_send = 
	 (ssize_t (*)(int, const void *, size_t, int)) 
	 dlsym(RTLD_NEXT, "send")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* sendto() fptr */
  if (  (fptr_sendto = 
	 (ssize_t (*)(int, const void *, size_t, int, const struct sockaddr *, socklen_t)) 
	 dlsym(RTLD_NEXT, "sendto")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* sendmsg() fptr */
  if (  (fptr_sendmsg = 
	 (ssize_t (*)(int, const struct msghdr *, int)) 
	 dlsym(RTLD_NEXT, "sendmsg")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* execve() fptr */
  if (  (fptr_execve = 
	 (int (*)(const  char  *, char  *const*, char *const*)) 
	 dlsym(RTLD_NEXT, "execve")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }

  /* fork() fptr */
  if (  (fptr_fork = 
	 (pid_t (*)(void)) 
	 dlsym(RTLD_NEXT, "fork")) 
	== NULL) {
    /* Missing library; cannot continue */
    real_exit(-1);
  }
}
