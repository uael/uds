/*
 * MIT License
 *
 * Copyright (c) 2016-2017 Abel Lucas <www.github.com/uael>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!@file uds/err.h
 * @author uael
 */
#ifndef __UDS_ERR_H
# define __UDS_ERR_H

#include <errno.h>

enum err {
  SUCCESS = 0,
  ERR_PERM = EPERM,
  ERR_NOENT = ENOENT,
  ERR_SRCH = ESRCH,
  ERR_INTR = EINTR,
  ERR_IO = EIO,
  ERR_NXIO = ENXIO,
  ERR_2BIG = E2BIG,
  ERR_NOEXEC = ENOEXEC,
  ERR_BADF = EBADF,
  ERR_CHILD = ECHILD,
  ERR_AGAIN = EAGAIN,
  ERR_NOMEM = ENOMEM,
  ERR_ACCES = EACCES,
  ERR_FAULT = EFAULT,
  ERR_BUSY = EBUSY,
  ERR_EXIST = EEXIST,
  ERR_XDEV = EXDEV,
  ERR_NODEV = ENODEV,
  ERR_NOTDIR = ENOTDIR,
  ERR_ISDIR = EISDIR,
  ERR_INVAL = EINVAL,
  ERR_NFILE = ENFILE,
  ERR_MFILE = EMFILE,
  ERR_NOTTY = ENOTTY,
  ERR_FBIG = EFBIG,
  ERR_NOSPC = ENOSPC,
  ERR_SPIPE = ESPIPE,
  ERR_ROFS = EROFS,
  ERR_MLINK = EMLINK,
  ERR_PIPE = EPIPE,
  ERR_DOM = EDOM,
  ERR_RANGE = ERANGE,
  ERR_DEADLK = EDEADLK,
  ERR_DEADLOCK = EDEADLOCK,
  ERR_NAMETOOLONG = ENAMETOOLONG,
  ERR_NOLCK = ENOLCK,
  ERR_NOSYS = ENOSYS,
  ERR_NOTEMPTY = ENOTEMPTY,
  ERR_ILSEQ = EILSEQ,
  FAILURE = ERR_ILSEQ + 1
};

typedef enum err err_t;

#endif /* !__UDS_ERR_H */
