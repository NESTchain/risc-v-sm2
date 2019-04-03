/*
 * Copyright 2004-2018 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

/*
 * This file is dual-licensed and is also available under the following
 * terms:
 *
 * Copyright (c) 2004, 2018, Richard Levitte <richard@levitte.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
//#include <dirent.h>
#include <errno.h>
#ifndef LPDIR_H
# include "LPdir.h"
#endif
#ifdef __VMS
# include <ctype.h>
#endif

/*
 * The POSIX macro for the maximum number of characters in a file path is
 * NAME_MAX.  However, some operating systems use PATH_MAX instead.
 * Therefore, it seems natural to first check for PATH_MAX and use that, and
 * if it doesn't exist, use NAME_MAX.
 */
#if defined(PATH_MAX)
# define LP_ENTRY_SIZE PATH_MAX
#elif defined(NAME_MAX)
# define LP_ENTRY_SIZE NAME_MAX
#endif

/*
 * Of course, there's the possibility that neither PATH_MAX nor NAME_MAX
 * exist.  It's also possible that NAME_MAX exists but is define to a very
 * small value (HP-UX offers 14), so we need to check if we got a result, and
 * if it meets a minimum standard, and create or change it if not.
 */
#if !defined(LP_ENTRY_SIZE) || LP_ENTRY_SIZE<255
# undef LP_ENTRY_SIZE
# define LP_ENTRY_SIZE 255
#endif

struct __dirstream
   {
void *__fd; /* `struct hurd_fd' pointer for descriptor.   */
char *__data; /* Directory block.   */
int __entry_data; /* Entry number `__data' corresponds to.   */
char *__ptr; /* Current pointer into the block.   */
int __entry_ptr; /* Entry number `__ptr' corresponds to.   */
size_t __allocation; /* Space allocated for the block.   */
size_t __size; /* Total valid data in the block.   */
   };

typedef struct __dirstream DIR;

struct LP_dir_context_st {
    DIR *dir;
    char entry_name[LP_ENTRY_SIZE + 1];
#ifdef __VMS
    int expect_file_generations;
    char previous_entry_name[LP_ENTRY_SIZE + 1];
#endif
};

const char *LP_find_file(LP_DIR_CTX **ctx, const char *directory)
{
    return NULL;
}

int LP_find_file_end(LP_DIR_CTX **ctx)
{
    return 0;
}
