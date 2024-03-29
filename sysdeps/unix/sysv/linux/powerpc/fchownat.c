/* Copyright (C) 2005-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sysdep.h>
#include <stdlib.h>

#include <kernel-features.h>

/*
  In Linux 2.1.x the chown functions have been changed.  A new function lchown
  was introduced.  The new chown now follows symlinks - the old chown and the
  new lchown do not follow symlinks.
  This file emulates chown() under the old kernels.
*/

int
fchownat (int fd, const char *file, uid_t owner, gid_t group, int flag)
{
  int result;

#ifdef __NR_fchownat
# ifndef __ASSUME_ATFCTS
  if (__have_atfcts >= 0)
# endif
    {
      result = INLINE_SYSCALL (fchownat, 5, fd, file, owner, group, flag);
# ifndef __ASSUME_ATFCTS
      if (result == -1 && errno == ENOSYS)
	__have_atfcts = -1;
      else
# endif
	return result;
    }
#endif

#ifndef __ASSUME_ATFCTS
  if (flag & ~AT_SYMLINK_NOFOLLOW)
    {
      __set_errno (EINVAL);
      return -1;
    }

  char *buf = NULL;

  if (fd != AT_FDCWD && file[0] != '/')
    {
      size_t filelen = strlen (file);
      if (__glibc_unlikely (filelen == 0))
	{
	  __set_errno (ENOENT);
	  return -1;
	}

      static const char procfd[] = "/proc/self/fd/%d/%s";
      /* Buffer for the path name we are going to use.  It consists of
	 - the string /proc/self/fd/
	 - the file descriptor number
	 - the file name provided.
	 The final NUL is included in the sizeof.   A bit of overhead
	 due to the format elements compensates for possible negative
	 numbers.  */
      size_t buflen = sizeof (procfd) + sizeof (int) * 3 + filelen;
      buf = alloca (buflen);

      __snprintf (buf, buflen, procfd, fd, file);
      file = buf;
    }

  INTERNAL_SYSCALL_DECL (err);

  if (flag & AT_SYMLINK_NOFOLLOW)
    result = INTERNAL_SYSCALL (lchown, err, 3, file, owner, group);
  else
    result = INTERNAL_SYSCALL (chown, err, 3, file, owner, group);

  if (__glibc_unlikely (INTERNAL_SYSCALL_ERROR_P (result, err)))
    {
      __atfct_seterrno (INTERNAL_SYSCALL_ERRNO (result, err), fd, buf);
      return -1;
    }

  return result;

#endif
}
