/* Set flags signalling availability of kernel features based on given
   kernel version number.
   Copyright (C) 1999-2014 Free Software Foundation, Inc.
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

/* This file must not contain any C code.  At least it must be protected
   to allow using the file also in assembler files.  */

#ifndef __LINUX_KERNEL_VERSION
/* We assume the worst; all kernels should be supported.  */
# define __LINUX_KERNEL_VERSION	0
#endif

/* We assume for __LINUX_KERNEL_VERSION the same encoding used in
   linux/version.h.  I.e., the major, minor, and subminor all get a
   byte with the major number being in the highest byte.  This means
   we can do numeric comparisons.

   In the following we will define certain symbols depending on
   whether the describes kernel feature is available in the kernel
   version given by __LINUX_KERNEL_VERSION.  We are not always exactly
   recording the correct versions in which the features were
   introduced.  If somebody cares these values can afterwards be
   corrected.  */

/* The sendfile syscall was introduced in 2.2.0.  */
#define __ASSUME_SENDFILE		1

/* Some architectures use the socketcall multiplexer for some or all
   socket-related operations, via a socket.S file in glibc, instead of
   separate syscalls.  __ASSUME_SOCKETCALL is defined for such
   architectures.  */
#if defined __i386__ \
    || defined __powerpc__ \
    || defined __s390__ \
    || defined __sh__ \
    || defined __sparc__
# define __ASSUME_SOCKETCALL		1
#endif

/* Linux 2.3.39 introduced IPC64.  Except for powerpc.  Linux 2.4.0 on
   PPC introduced a correct IPC64.  But PowerPC64 does not support a
   separate 64-bit syscall, already 64-bit.  */
#ifndef __powerpc64__
# define __ASSUME_IPC64		1
#endif

/* The changed st_ino field appeared in 2.4.0-test6.  However, SH is lame,
   and still does not have a 64-bit inode field.  */
#ifndef __sh__
# define __ASSUME_ST_INO_64_BIT		1
#endif

/* The getdents64 syscall was introduced in 2.4.0-test7 (but later for
   MIPS n32).  */
#define __ASSUME_GETDENTS64_SYSCALL	1

/* The statfs64 syscalls are available in 2.5.74 (but not for alpha).  */
#define __ASSUME_STATFS64	1

/* The utimes syscall has been available for some architectures
   forever.  For x86 it was introduced after 2.5.75, for x86-64,
   ppc, and ppc64 it was introduced in 2.6.0-test3, for s390 it was
   introduced in 2.6.21-rc5.  */
#define __ASSUME_UTIMES	1

/* pselect/ppoll were introduced just after 2.6.16-rc1.  On x86_64 and
   SH this appeared first in 2.6.19-rc1, on ia64 in 2.6.22-rc1.  */
#define __ASSUME_PSELECT	1
#define __ASSUME_PPOLL		1

/* The *at syscalls were introduced just after 2.6.16-rc1.  On PPC
   they were introduced in 2.6.17-rc1, on SH in 2.6.19-rc1.  */
#define __ASSUME_ATFCTS	1

/* Support for inter-process robust mutexes was added in 2.6.17 (but
   some architectures lack futex_atomic_cmpxchg_inatomic in some
   configurations).  */
#if !(defined __sparc__ && !defined __arch64__ && !defined __sparc_v9__)
# define __ASSUME_SET_ROBUST_LIST	1
#endif

/* Pessimistically assume that 2.6.18 introduced real handling of
   large numbers of requests to readv and writev and that we don't
   need a fallback.  It likely worked for much longer.  */
#define __ASSUME_COMPLETE_READV_WRITEV	1

/* Support for PI futexes was added in 2.6.18 (but some architectures
   lack futex_atomic_cmpxchg_inatomic in some configurations).  */
#if !(defined __sparc__ && !defined __arch64__ && !defined __sparc_v9__)
# define __ASSUME_FUTEX_LOCK_PI	1
#endif

/* Support for utimensat syscall was added in 2.6.22, on SH
   only after 2.6.22-rc1.  */
#define __ASSUME_UTIMENSAT	1

/* Support for private futexes was added in 2.6.22.  */
#define __ASSUME_PRIVATE_FUTEX	1

/* Support for fallocate was added in 2.6.23, on s390
   only after 2.6.23-rc1.  */
#define __ASSUME_FALLOCATE	1

/* Support for various CLOEXEC and NONBLOCK flags was added in
   2.6.23.  */
#define __ASSUME_O_CLOEXEC	1

/* Support for ADJ_OFFSET_SS_READ was added in 2.6.24.  */
#define __ASSUME_ADJ_OFFSET_SS_READ	1

/* Support for various CLOEXEC and NONBLOCK flags was added in
   2.6.27.  */
#define __ASSUME_SOCK_CLOEXEC	1
#define __ASSUME_IN_NONBLOCK	1
#define __ASSUME_PIPE2		1
#define __ASSUME_EVENTFD2	1
#define __ASSUME_SIGNALFD4	1
#define __ASSUME_DUP3		1

/* Support for accept4 functionality was added in 2.6.28, but for some
   architectures using a separate syscall rather than socketcall that
   syscall was only added later, and some architectures first had
   socketcall support then a separate syscall.  Define
   __ASSUME_ACCEPT4_SOCKETCALL if glibc uses socketcall on this
   architecture and accept4 is available through socketcall,
   __ASSUME_ACCEPT4_SYSCALL if it is available through a separate
   syscall, __ASSUME_ACCEPT4_SYSCALL_WITH_SOCKETCALL if it became
   available through a separate syscall at the same time as through
   socketcall, and __ASSUME_ACCEPT4 if the accept4 function is known
   to work.  */
#ifdef __ASSUME_SOCKETCALL
# define __ASSUME_ACCEPT4_SOCKETCALL	1
#endif

/* The accept4 syscall was added for x86_64 and SPARC in 2.6.28, and
   for PowerPC and SH in 2.6.37.  */
#if (defined __x86_64__ || defined __sparc__)		\
    || (__LINUX_KERNEL_VERSION >= 0x020625		\
	&& (defined __powerpc__ || defined __sh__))
# define __ASSUME_ACCEPT4_SYSCALL	1
#endif
#ifdef __sparc__
# define __ASSUME_ACCEPT4_SYSCALL_WITH_SOCKETCALL	1
#endif

#if defined __ASSUME_ACCEPT4_SOCKETCALL || defined __ASSUME_ACCEPT4_SYSCALL
# define __ASSUME_ACCEPT4	1
#endif

/* Support for the FUTEX_CLOCK_REALTIME flag was added in 2.6.29.  */
#define __ASSUME_FUTEX_CLOCK_REALTIME	1

/* Support for the AT_RANDOM auxiliary vector entry was added in 2.6.29.  */
#define __ASSUME_AT_RANDOM	1

/* Support for preadv and pwritev was added in 2.6.30.  */
#define __ASSUME_PREADV	1
#define __ASSUME_PWRITEV	1

/* Support for FUTEX_*_REQUEUE_PI was added in 2.6.31 (but some
   architectures lack futex_atomic_cmpxchg_inatomic in some
   configurations).  */
#if !(defined __sparc__ && !defined __arch64__ && !defined __sparc_v9__)
# define __ASSUME_REQUEUE_PI	1
#endif

/* Support for F_GETOWN_EX was introduced in 2.6.32.  */
#define __ASSUME_F_GETOWN_EX	1

/* Support for recvmmsg functionality was added in 2.6.33.  The macros
   defined correspond to those for accept4.  */
#if __LINUX_KERNEL_VERSION >= 0x020621 && defined __ASSUME_SOCKETCALL
# define __ASSUME_RECVMMSG_SOCKETCALL	1
#endif

/* The recvmmsg syscall was added for i386, x86_64 and SPARC in
   2.6.33, and for PowerPC and SH in 2.6.37.  */
#if (__LINUX_KERNEL_VERSION >= 0x020621			\
     && (defined __i386__ || defined __x86_64__ || defined __sparc__))	\
    || (__LINUX_KERNEL_VERSION >= 0x020625		\
	&& (defined __powerpc__ || defined __sh__))
# define __ASSUME_RECVMMSG_SYSCALL	1
#endif
#if defined __i386__ || defined __sparc__
# define __ASSUME_RECVMMSG_SYSCALL_WITH_SOCKETCALL	1
#endif

#if defined __ASSUME_RECVMMSG_SOCKETCALL || defined __ASSUME_RECVMMSG_SYSCALL
# define __ASSUME_RECVMMSG	1
#endif

/* Support for /proc/self/task/$tid/comm and /proc/$pid/task/$tid/comm was
   added in 2.6.33.  */
#if __LINUX_KERNEL_VERSION >= 0x020621
# define __ASSUME_PROC_PID_TASK_COMM	1
#endif

/* statfs fills in f_flags since 2.6.36.  */
#if __LINUX_KERNEL_VERSION >= 0x020624
# define __ASSUME_STATFS_F_FLAGS	1
#endif

/* prlimit64 is available in 2.6.36.  */
#if __LINUX_KERNEL_VERSION >= 0x020624
# define __ASSUME_PRLIMIT64	1
#endif

/* Support for sendmmsg functionality was added in 3.0.  The macros
   defined correspond to those for accept4 and recvmmsg.  */
#if __LINUX_KERNEL_VERSION >= 0x030000 && defined __ASSUME_SOCKETCALL
# define __ASSUME_SENDMMSG_SOCKETCALL	1
#endif

/* The sendmmsg syscall was added for i386, x86_64, PowerPC, SH and
   SPARC in 3.0.  */
#if __LINUX_KERNEL_VERSION >= 0x030000					\
    && (defined __i386__ || defined __x86_64__ || defined __powerpc__	\
	|| defined __sh__ || defined __sparc__)
# define __ASSUME_SENDMMSG_SYSCALL	1
#endif
#if defined __i386__ || defined __powerpc__ || defined __sh__ \
    || defined __sparc__
# define __ASSUME_SENDMMSG_SYSCALL_WITH_SOCKETCALL	1
#endif

#if defined __ASSUME_SENDMMSG_SOCKETCALL || defined __ASSUME_SENDMMSG_SYSCALL
# define __ASSUME_SENDMMSG	1
#endif

/* getcpu is a syscall for x86-64 since 3.1.  */
#if defined __x86_64__ && __LINUX_KERNEL_VERSION >= 0x030100
# define __ASSUME_GETCPU_SYSCALL	1
#endif

/* 2.6.29 removed the XFS restricted_chown sysctl, so it is pointless looking
   for it in newer kernels.  */
#define __ASSUME_XFS_RESTRICTED_CHOWN 1
