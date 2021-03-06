
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

CPPFLAGS = -I$(top_srcdir)/src/base \
	-I$(top_srcdir)/src/debug \
	-I$(top_srcdir)/src/kernel \
	-I$(top_srcdir)/src/net \
	-I$(top_srcdir)/src/sdk \
	-I$(top_srcdir)/src/user \
	-I$(top_srcdir)/src/utility
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS)

CWD_OBJS = __cwd.o getcwd.o __path_absolute.o __init_cwd.o

ERRNO_OBJS = __set_errno.o

FDMAN_OBJS = __descriptor_data_pool.o __descriptormap.o __fdman_init.o __fdman_get_new_descriptor.o __fdman_get_dup_descriptor.o \
	__fdman_release_descriptor.o

GLUE_OBJS = __fill_stat.o __psp_heap_blockid.o __psp_free_heap.o _fork.o _wait.o _open.o _close.o _read.o _write.o _fstat.o \
	_stat.o access.o _fcntl.o opendir.o readdir.o rewinddir.o closedir.o _lseek.o chdir.o mkdir.o rmdir.o _link.o _unlink.o \
	_rename.o _getpid.o _kill.o _sbrk.o _gettimeofday.o _times.o _platformDisableInterrupts.o _platformEnableInterrupts.o

INIT_OBJS = __psp_libc_init.o

NETDB_OBJS = h_errno.o gethostbyaddr.o gethostbyname.o

PIPE_OBJS = __pipe_peekmsgsize.o pipe.o __pipe_close.o __pipe_nonblocking_read.o __pipe_read.o __pipe_write.o \
	__pipe_nonblocking_write.o

SELECT_OBJS = select.o

SLEEP_OBJS = nanosleep.o

SOCKET_OBJS = socket.o __socket_close.o accept.o bind.o connect.o getsockopt.o listen.o recv.o recvfrom.o send.o sendto.o \
	setsockopt.o shutdown.o getpeername.o inet_ntoa.o

TERMINATE_OBJS = _exit.o abort.o exit.o

TIMEZONE_OBJS = __timezone_update.o

lib_LIBRARIES = libpsplibc.a

nobase_includedir = @PSPSDK_INCLUDEDIR@
nobase_include_HEADERS = netdb.h

netinet_nobase_includedir = @PSPSDK_INCLUDEDIR@/netinet
netinet_nobase_include_HEADERS = netinet/in.h netinet/tcp.h

arpa_nobase_includedir = @PSPSDK_INCLUDEDIR@/arpa
arpa_nobase_include_HEADERS = arpa/inet.h

sys_nobase_includedir = @PSPSDK_INCLUDEDIR@/sys
sys_nobase_include_HEADERS = sys/socket.h

libpsplibc_a_SOURCES = \
	cwd.o \
	errno.o \
	fdman.c \
	glue.c \
	init.c \
	netdb.c \
	pipe.c \
	select.c \
	sleep.c \
	socket.c \
	terminate.c \
	timezone.c

libpsplibc_a_LIBADD  = $(CWD_OBJS) $(ERRNO_OBJS) $(FDMAN_OBJS) $(INIT_OBJS) $(GLUE_OBJS) $(NETDB_OBJS) $(PIPE_OBJS) $(SELECT_OBJS) \
	$(SOCKET_OBJS) $(SLEEP_OBJS) $(TERMINATE_OBJS) $(TIMEZONE_OBJS)

$(CWD_OBJS): cwd.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@

$(ERRNO_OBJS): errno.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@

$(FDMAN_OBJS): fdman.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@

$(INIT_OBJS): init.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@

$(GLUE_OBJS): glue.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@

$(NETDB_OBJS): netdb.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@

$(PIPE_OBJS): pipe.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@

$(SELECT_OBJS): select.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@

$(SLEEP_OBJS): sleep.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@

$(SOCKET_OBJS): socket.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@

$(TERMINATE_OBJS): terminate.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@

$(TIMEZONE_OBJS): timezone.c
	$(AM_V_CC)$(COMPILE) -DF_$* $< -c -o $@
