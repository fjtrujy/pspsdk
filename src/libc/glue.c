/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * libcglue.c - Newlib-compatible system calls.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Jim Paris <jim@jtan.com>
 * Copyright (c) 2021 Francisco J Trujillo <fjtrujy@gmail.com>
 *
 */

#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <psptypes.h>
#include <pspiofilemgr.h>
#include <pspmodulemgr.h>
#include <pspsysmem.h>
#include <pspthreadman.h>
#include <psputils.h>
#include <pspsdk.h>

#include "fdman.h"

#define DEFAULT_PRX_HEAP_SIZE_KB 64

/* If defined it specifies the desired size of the heap, in KB. */
extern unsigned int sce_newlib_heap_kb_size __attribute__((weak));
extern int __pspsdk_is_prx __attribute__((weak));

/* Functions from cwd.c */
extern char __cwd[MAXNAMLEN + 1];
int __path_absolute(const char *in, char *out, int len);

/* Fuctions from errno.c */
int __set_errno(int code);

/* Functions from pipe.c */
int __pipe_read(int fd, void *buf, size_t len);
int __pipe_close(int fd);
int __pipe_write(int fd, const void *buf, size_t len);
int __pipe_nonblocking_read(int fd, void *buf, size_t len);
int __pipe_nonblocking_write(int fd, const void *buf, size_t len);

/* Functions from socket.c */
int __socket_close(int sock);

#ifdef F___fill_stat
static time_t psp_to_posix_time(ScePspDateTime psp_time)
{
	struct tm conv_time;
	conv_time.tm_year = psp_time.year;
	conv_time.tm_mon = psp_time.month;
	conv_time.tm_mday = psp_time.day;
	conv_time.tm_hour = psp_time.hour;
	conv_time.tm_min = psp_time.minute;
	conv_time.tm_sec = psp_time.second;
	conv_time.tm_isdst = -1;
	return mktime(&conv_time);
}

static mode_t io_to_posix_mode(SceMode sceMode)
{
        mode_t posixmode = 0;
        if (sceMode & FIO_SO_IFREG) posixmode |= S_IFREG;
        if (sceMode & FIO_SO_IFDIR) posixmode |= S_IFDIR;
        if (sceMode & FIO_SO_IROTH) posixmode |= S_IRUSR|S_IRGRP|S_IROTH;
        if (sceMode & FIO_SO_IWOTH) posixmode |= S_IWUSR|S_IWGRP|S_IWOTH;
        if (sceMode & FIO_SO_IXOTH) posixmode |= S_IXUSR|S_IXGRP|S_IXOTH;
        return posixmode;
}


void __fill_stat(struct stat *stat, const SceIoStat *sce_stat)
{
        stat->st_dev = 0;
        stat->st_ino = 0;
        stat->st_mode = io_to_posix_mode(sce_stat->st_mode);
        stat->st_nlink = 0;
        stat->st_uid = 0;
        stat->st_gid = 0;
        stat->st_rdev = 0;
        stat->st_size = sce_stat->st_size;
        stat->st_atime = psp_to_posix_time(sce_stat->sce_st_atime);
        stat->st_mtime = psp_to_posix_time(sce_stat->sce_st_mtime);
        stat->st_ctime = psp_to_posix_time(sce_stat->sce_st_ctime);
        stat->st_blksize = 16*1024;
        stat->st_blocks = stat->st_size / 512;
}
#else
void __fill_stat(struct stat *stat, const SceIoStat *sce_stat);
#endif

#ifdef F___psp_heap_blockid
/* UID of the memory block that represents the heap. */
SceUID __psp_heap_blockid;
#else
extern SceUID __psp_heap_blockid;
#endif

#ifdef F___psp_free_heap
/* Free the heap. */
int __psp_free_heap(void)
{
	if (__psp_heap_blockid > 0) {
		return sceKernelFreePartitionMemory(__psp_heap_blockid);
	}

	return __psp_heap_blockid;
}
#endif

#ifdef F__open
int _open(const char *buf, int flags, int mode) {
	int scefd, fd, sce_flags;
	char dest[MAXNAMLEN + 1];

	if(__path_absolute(buf, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	/* O_RDONLY starts at 0, where PSP_O_RDONLY starts at 1, so remap the read/write
	   flags by adding 1. */
	sce_flags = (flags & O_ACCMODE) + 1;

	/* Translate standard open flags into the flags understood by the PSP kernel. */
	if (flags & O_APPEND) {
		sce_flags |= PSP_O_APPEND;
	}
	if (flags & O_CREAT) {
		sce_flags |= PSP_O_CREAT;
	}
	if (flags & O_TRUNC) {
		sce_flags |= PSP_O_TRUNC;
	}
	if (flags & O_EXCL) {
		sce_flags |= PSP_O_EXCL;
	}
	if (flags & O_NONBLOCK) {
		sce_flags |= PSP_O_NBLOCK;
	}

	scefd = sceIoOpen(dest, sce_flags, mode);
	if (scefd >= 0) {
		fd = __fdman_get_new_descriptor();
		if (fd != -1) {
			__descriptormap[fd]->descriptor = scefd;
			__descriptormap[fd]->type = __DESCRIPTOR_TYPE_FILE;
			__descriptormap[fd]->flags = flags;
			__descriptormap[fd]->filename = strdup(dest);
			return fd;
		}
		else {
			sceIoClose(scefd);
			errno = ENOMEM;
			return -1;
		}
	} 
	else {
		return __set_errno(scefd);
	}
}

#endif

#ifdef F__close
int _close(int fd) {
	int ret = 0;

	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch(__descriptormap[fd]->type)
	{
		case __DESCRIPTOR_TYPE_FILE:
		case __DESCRIPTOR_TYPE_TTY:
			if (__descriptormap[fd]->ref_count == 1) {
				ret = __set_errno(sceIoClose(__descriptormap[fd]->descriptor));
			}
			__fdman_release_descriptor(fd);
			return ret;
			break;
		case __DESCRIPTOR_TYPE_PIPE:
			return __pipe_close(fd);
			break;
		case __DESCRIPTOR_TYPE_SOCKET:
			return __socket_close(fd);
			break;
		default:
			break;
	}

	errno = EBADF;
	return -1;
}
#endif

#ifdef F__read
int _read(int fd, void *buf, size_t nbytes) {
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch(__descriptormap[fd]->type)
	{
		case __DESCRIPTOR_TYPE_FILE:
		case __DESCRIPTOR_TYPE_TTY:
			return __set_errno(sceIoRead(__descriptormap[fd]->descriptor, buf, nbytes));
			break;
		case __DESCRIPTOR_TYPE_PIPE:
			if (__descriptormap[fd]->flags & O_NONBLOCK) {
				return __pipe_nonblocking_read(fd, buf, nbytes);
			}
			else {
				return __pipe_read(fd, buf, nbytes);
			}
			break;
		case __DESCRIPTOR_TYPE_SOCKET:
			return recv(fd, buf, nbytes, 0);
			break;
		default:
			break;
	}

	errno = EBADF;
	return -1;
}
#endif

#ifdef F__write
int _write(int fd, const void *buf, size_t nbytes) {
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch(__descriptormap[fd]->type)
	{
		case __DESCRIPTOR_TYPE_FILE:
		case __DESCRIPTOR_TYPE_TTY:
			return __set_errno(sceIoWrite(__descriptormap[fd]->descriptor, buf, nbytes));
			break;
		case __DESCRIPTOR_TYPE_PIPE:
			if (__descriptormap[fd]->flags & O_NONBLOCK) {
				return __pipe_nonblocking_write(fd, buf, nbytes);
			}
			else {
				return __pipe_write(fd, buf, nbytes);
			}
			break;
			break;
		case __DESCRIPTOR_TYPE_SOCKET:
			return send(fd, buf, nbytes, 0);
			break;
		default:
			break;
	}

	errno = EBADF;
	return -1;
}
#endif

#ifdef F__stat
int _stat(const char *filename, struct stat *buf)
{
	SceIoStat psp_stat;
	char dest[MAXNAMLEN + 1];
	int ret;

	if(__path_absolute(filename, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	memset(buf, '\0', sizeof(struct stat));
	ret = sceIoGetstat(dest, &psp_stat);
	if (ret < 0) {
		return __set_errno(ret);
	}

	__fill_stat(buf, &psp_stat);
	return 0;
}
#else
int _stat(const char *filename, struct stat *buf);
#endif

#ifdef F__fstat
int _fstat(int fd, struct stat *buf) {
	int ret;
	SceOff oldpos;
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch(__descriptormap[fd]->type)
	{
		case __DESCRIPTOR_TYPE_TTY:
			memset(buf, '\0', sizeof(struct stat));
			buf->st_mode = S_IFCHR;
			return 0;
			break;		
		case __DESCRIPTOR_TYPE_FILE:
			if (__descriptormap[fd]->filename != NULL) {
				ret = _stat(__descriptormap[fd]->filename, buf);
				
				/* Find true size of the open file */
				oldpos = sceIoLseek(__descriptormap[fd]->descriptor, 0, SEEK_CUR);
				if (oldpos != (off_t) -1) {
					buf->st_size = (off_t) sceIoLseek(__descriptormap[fd]->descriptor, 0, SEEK_END);
					sceIoLseek(__descriptormap[fd]->descriptor, oldpos, SEEK_SET);
				}
				return ret;
			}
			break;
		case __DESCRIPTOR_TYPE_PIPE:
		case __DESCRIPTOR_TYPE_SOCKET:
		default:
			break;
	}

	errno = EBADF;
	return -1;
}
#endif

#ifdef F_access
int access(const char *fn, int flags)
{
	struct stat s;
	if (stat(fn, &s))
		return -1;
	if (s.st_mode & S_IFDIR)
		return 0;
	if (flags & W_OK)
	{
		if (s.st_mode & S_IWRITE)
			return 0;
		errno = EACCES;
		return -1;
	}
	return 0;
}
#endif

#ifdef F__fcntl
int _fcntl(int fd, int cmd, ...)
{
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch (cmd)
	{
		case F_DUPFD:
		{
			return __fdman_get_dup_descriptor(fd);
			break;
		}
		case F_GETFL:
		{
			return __descriptormap[fd]->flags;
			break;
		}
		case F_SETFL:
		{
			int newfl;
			va_list args;
	
			va_start (args, cmd);         /* Initialize the argument list. */
			newfl =  va_arg(args, int);
			va_end (args);                /* Clean up. */

			__descriptormap[fd]->flags = newfl;

			switch(__descriptormap[fd]->type)
			{
				case __DESCRIPTOR_TYPE_FILE:
					break;
				case __DESCRIPTOR_TYPE_PIPE:
					break;
				case __DESCRIPTOR_TYPE_SOCKET:
					if (newfl & O_NONBLOCK)
					{
						int one = 1;
						return setsockopt(fd, SOL_SOCKET, SO_NONBLOCK, (char *)&one, sizeof(one));
					}
					else
					{
						int zero = 0;
						return setsockopt(fd, SOL_SOCKET, SO_NONBLOCK, (char *)&zero, sizeof(zero));
					}
					break;
				default:
					break;
			}
			return 0;
			break;
		}
	}

	errno = EBADF;
	return -1;
}
#endif /* F__fcntl */

#ifdef F_opendir
DIR *opendir(const char *filename)
{
	char dest[MAXNAMLEN + 1];
	DIR *dirp;
	SceUID uid;

	/* Normalize pathname so that opendir(".") works */
	if(__path_absolute(filename, dest, MAXNAMLEN) < 0) {
		errno = ENOENT;
		return NULL;
	}

	dirp = (DIR *)malloc(sizeof(DIR));

	uid = sceIoDopen(dest);

	if (uid < 0)
	{
		free(dirp);
		(void) __set_errno(uid);
		return NULL;
	}

	dirp->dd_fd = uid;

	return dirp;
}
#endif

#ifdef F_readdir
struct dirent *readdir(DIR *dir)
{
	int rv;
	struct dirent *de;
	SceIoDirent sceiode;

	if(dir == NULL) {
		errno = EBADF;
		return NULL;
	}

	de = (struct dirent *)dir->dd_buf;
	rv = sceIoDread(dir->dd_fd, &sceiode);
	if (rv <= 0) {
		(void) __set_errno(rv);
		return NULL;
	}

	__fill_stat(&de->d_stat, &sceiode.d_stat);
	strcpy(de->d_name, sceiode.d_name);
	de->d_name[MAXNAMLEN] = 0;

	return de;
}
#endif

#ifdef F_rewinddir
void rewinddir(DIR *dir)
{
	printf("rewinddir not implemented\n");
}
#endif

#ifdef F_closedir
int closedir(DIR *dir)
{
	if (dir != NULL)
	{
		int uid;
		uid = dir->dd_fd;
		free(dir);
		return __set_errno(sceIoDclose(uid));
	}

	errno = EBADF;
	return -1; 
}
#endif

#ifdef F__lseek
off_t _lseek(int fd, off_t offset, int whence)
{
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch(__descriptormap[fd]->type)
	{
		case __DESCRIPTOR_TYPE_FILE:
			/* We don't have to do anything with the whence argument because SEEK_* == PSP_SEEK_*. */
			return (off_t) __set_errno(sceIoLseek(__descriptormap[fd]->descriptor, offset, whence));
			break;
		case __DESCRIPTOR_TYPE_PIPE:
			break;
		case __DESCRIPTOR_TYPE_SOCKET:
			break;
		default:
			break;
	}

	errno = EBADF;
	return -1;
}
#endif

#ifdef F_chdir
int chdir(const char *path)
{
	char dest[MAXNAMLEN + 1];
	SceUID uid;

	if(__path_absolute(path, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	/* sceIoChdir doesn't give an indication of whether it worked,
	   so test for existence by attempting to open the dir */
	uid = sceIoDopen(dest);
	if(uid < 0) {
		errno = ENOTDIR;
		return -1;
	}
	sceIoDclose(uid);

	sceIoChdir(dest);
	strcpy(__cwd, dest);
	return 0;
}
#endif

#ifdef F_mkdir
int mkdir(const char *pathname, mode_t mode)
{
	char dest[MAXNAMLEN + 1];

	if(__path_absolute(pathname, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	return __set_errno(sceIoMkdir(dest, mode));
}
#endif

#ifdef F_rmdir
int rmdir(const char *pathname)
{
	char dest[MAXNAMLEN + 1];

	if(__path_absolute(pathname, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	return __set_errno(sceIoRmdir(dest));
}
#endif

#ifdef F__link
int _link(const char *old, const char *new) {
    errno = ENOSYS;
	return -1; /* not supported */
}
#endif

#ifdef F__unlink
int _unlink(const char *path) {
    errno = ENOSYS;
	return -1; /* not supported */
}
#endif

#ifdef F__rename
int _rename(const char *old, const char *new)
{
   char oldname[MAXNAMLEN + 1];
   char newname[MAXNAMLEN + 1];

   if(__path_absolute(old, oldname, MAXNAMLEN) < 0) {
       errno = ENAMETOOLONG;
       return -1;
   }

   if(__path_absolute(new, newname, MAXNAMLEN) < 0) {
       errno = ENAMETOOLONG;
       return -1;
   }

   return __set_errno(sceIoRename(oldname, newname));
}
#endif

#ifdef F__getpid
pid_t _getpid(void)
{
	errno = ENOSYS;
	return (pid_t) -1;
}
#endif

#ifdef F__kill
int _kill(int unused, int unused2)
{
	errno = ENOSYS;
	return -1;
}
#endif

#ifdef F__fork
pid_t _fork(void)
{
	errno = ENOSYS;
	return (pid_t) -1;
}
#endif

#ifdef F__wait
pid_t _wait(int *unused)
{
	errno = ENOSYS;
	return (pid_t) -1;
}
#endif

#ifdef F__sbrk
void * _sbrk(ptrdiff_t incr)
{
	static void * heap_bottom = NULL;
	static void * heap_top = NULL;
	static void * heap_ptr = NULL;

	/* Has our heap been initialized? */
	if (heap_bottom == NULL) {
		/* No, initialize the heap. */
		SceSize heap_size = (SceSize) -1;

		if (&sce_newlib_heap_kb_size != NULL) {
			heap_size = sce_newlib_heap_kb_size;
		} else if(&__pspsdk_is_prx != NULL) {
			heap_size = DEFAULT_PRX_HEAP_SIZE_KB;
		}

		heap_size *= 1024;
		if ((int)heap_size < 0) {
			heap_size += sceKernelMaxFreeMemSize();
		}

		if (heap_size != 0) {
			__psp_heap_blockid = sceKernelAllocPartitionMemory(2, "block", PSP_SMEM_Low, heap_size, NULL);
			if (__psp_heap_blockid > 0) {
				heap_bottom = sceKernelGetBlockHeadAddr(__psp_heap_blockid);
				heap_ptr = heap_bottom;
				heap_top = (unsigned char *) heap_bottom + heap_size;
			}
		}
	}

	void * heap_addr = (void *) -1;
	void * next_heap_ptr = (void *) ((ptrdiff_t) heap_ptr + incr);
	if ((heap_bottom != NULL) && (next_heap_ptr >= heap_bottom) && (next_heap_ptr < heap_top)) {
		heap_addr = heap_ptr;
		heap_ptr = next_heap_ptr;
	}

	return heap_addr;
}
#endif

#ifdef F__gettimeofday
int _gettimeofday(struct timeval *tp, struct timezone *tzp)
{
	int ret;
	time_t t;
	struct timeval tv1, tv2;

	/* The kernel sceKernelLibcGettimeofday only returns time
	   since midnight.  To get a proper timeval return value, we
	   get seconds using sceKernelLibcTime and microseconds using
	   sceKernelLibcGettimeofday.  Since we are reading the time
	   with two different function calls, we need to be careful 
	   to avoid glitches when the time changes between calls. */

 retry:
	/* Get seconds and microseconds since midnight */
	ret = __set_errno(sceKernelLibcGettimeofday(&tv1, tzp));
	if (ret < 0)
		return ret;

	/* Get seconds since epoch */
	ret = __set_errno(sceKernelLibcTime(&t));
	if (ret < 0)
		return ret;

	/* Get seconds and microseconds since midnight, again */
	ret = __set_errno(sceKernelLibcGettimeofday(&tv2, tzp));
	if (ret < 0)
		return ret;

	/* Retry if microseconds wrapped around */
	if (tv2.tv_usec < tv1.tv_usec)
		goto retry;

	/* Return the actual time since epoch */
	tp->tv_sec = t;
	tp->tv_usec = tv2.tv_usec;

	return 0;
}
#endif

#ifdef F__times
clock_t _times(struct tms *buffer) 
{
	clock_t clk = sceKernelGetSystemTimeWide();

	if (buffer != NULL) {
		buffer->tms_utime  = clk;
		buffer->tms_stime  = 0;
		buffer->tms_cutime = clk;
		buffer->tms_cstime = 0;
	}

	return clk;
}
#endif

#ifdef F__platformDisableInterrupts
unsigned int _platformDisableInterrupts(void) {
	return pspSdkDisableInterrupts();
}
#endif

#ifdef F__platformEnableInterrupts
void _platformEnableInterrupts(unsigned int istate) 
{
	return pspSdkEnableInterrupts(istate);
}
#endif
