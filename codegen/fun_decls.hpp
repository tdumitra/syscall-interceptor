/* Headers where the intercepted functions are declared */
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/poll.h>

/* The functions to intercept */
void exit(int status) throw();
int socket(int domain, int type, int protocol) throw();
pid_t getpid(void) throw();
ssize_t write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);
//int open(const char *pathname, int flags, ...);
ssize_t readv(int fd, const struct iovec *vector, int count);
ssize_t writev(int fd, const struct iovec *vector, int count);
int listen(int sockfd, int backlog) throw(); 
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen) throw();
int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
int select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
int pselect(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timespec *timeout, const sigset_t *sigmask);
int poll(struct pollfd *ufds, nfds_t nfds, int timeout);
int close(int fd);
int shutdown(int s, int how) throw();
struct hostent *gethostbyname(const char *name);
struct hostent *gethostbyaddr(const void *addr, unsigned int len, int type);
int getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen) throw();
int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen) throw();
int socketpair(int d, int type, int protocol, int sv[2]) throw();
ssize_t recv(int s, void *buf, size_t len, int flags);
ssize_t recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);
ssize_t recvmsg(int s, struct msghdr *msg, int flags);
ssize_t send(int s, const void *buf, size_t len, int flags);
ssize_t sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
ssize_t sendmsg(int s, const struct msghdr *msg, int flags);
int execve(const  char  *filename,  char  *const  argv[], char *const envp[]) throw();
pid_t fork(void) throw();
