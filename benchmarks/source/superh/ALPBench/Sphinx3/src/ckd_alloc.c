/*
 * 
 * This file is part of the ALPBench Benchmark Suite Version 1.0
 * 
 * Copyright (c) 2005 The Board of Trustees of the University of Illinois
 * 
 * All rights reserved.
 * 
 * ALPBench is a derivative of several codes, and restricted by licenses
 * for those codes, as indicated in the source files and the ALPBench
 * license at http://www.cs.uiuc.edu/alp/alpbench/alpbench-license.html
 * 
 * The multithreading and SSE2 modifications for SpeechRec, FaceRec,
 * MPEGenc, and MPEGdec were done by Man-Lap (Alex) Li and Ruchira
 * Sasanka as part of the ALP research project at the University of
 * Illinois at Urbana-Champaign (http://www.cs.uiuc.edu/alp/), directed
 * by Prof. Sarita V. Adve, Dr. Yen-Kuang Chen, and Dr. Eric Debes.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal with the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimers.
 * 
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimers in the documentation and/or other materials provided
 *       with the distribution.
 * 
 *     * Neither the names of Professor Sarita Adve's research group, the
 *       University of Illinois at Urbana-Champaign, nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this Software without specific prior written permission.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE CONTRIBUTORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE
 * SOFTWARE.
 * 
 */


/* ====================================================================
 * Copyright (c) 1999-2001 Carnegie Mellon University.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * This work was supported in part by funding from the Defense Advanced 
 * Research Projects Agency and the National Science Foundation of the 
 * United States of America, and the CMU Sphinx Speech Consortium.
 *
 * THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND 
 * ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY
 * NOR ITS EMPLOYEES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ====================================================================
 *
 */
/*
 * ckd_alloc.c -- Memory allocation package.
 *
 * **********************************************
 * CMU ARPA Speech Project
 *
 * Copyright (c) 1999 Carnegie Mellon University.
 * ALL RIGHTS RESERVED.
 * **********************************************
 * 
 * HISTORY
 * 
 * 19-Jun-97	M K Ravishankar (rkm@cs.cmu.edu) at Carnegie Mellon University
 * 		Removed file,line arguments from free functions.
 * 		Removed debugging stuff.
 * 
 * 01-Jan-96	M K Ravishankar (rkm@cs.cmu.edu) at Carnegie Mellon University
 * 		Created.
 */


/*********************************************************************
 *
 * $Header: /cvsroot/cmusphinx/sphinx3/src/libutil/ckd_alloc.c,v 1.2 2001/12/11 04:40:56 lenzo Exp $
 *
 * Carnegie Mellon ARPA Speech Group
 *
 * Copyright (c) 1994 Carnegie Mellon University.
 * All rights reserved.
 *
 *********************************************************************
 *
 * file: ckd_alloc.c
 * 
 * traceability: 
 * 
 * description: 
 * 
 * author: 
 * 
 *********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "ckd_alloc.h"
#include "err.h"


void *__ckd_calloc__(size_t n_elem, size_t elem_size,
		     const char *caller_file, int caller_line)
{
    void *mem;

    if ((mem = calloc(n_elem, elem_size)) == NULL) {
	E_FATAL("calloc(%d,%d) failed from %s(%d)\n", n_elem, elem_size,
		caller_file, caller_line);
    }

    return mem;
}


void *__ckd_malloc__(size_t size,
		     const char *caller_file, int caller_line)
{
    void *mem;

    if ((mem = malloc(size)) == NULL)
	E_FATAL("malloc(%d) failed from %s(%d)\n", size, caller_file, caller_line);

    return mem;
}


void *__ckd_realloc__(void *ptr, size_t new_size,
		      const char *caller_file, int caller_line)
{
    void *mem;

    if ((mem = realloc(ptr, new_size)) == NULL) {
	E_FATAL("realloc(%d) failed from %s(%d)\n", new_size,
		caller_file, caller_line);
    }

    return mem;
}


char *__ckd_salloc__ (const char *orig, const char *caller_file, int32 caller_line)
{
    int32 len;
    char *buf;

    len = strlen(orig)+1;
    buf = (char *) __ckd_malloc__(len, caller_file, caller_line);

    strcpy (buf, orig);
    return (buf);
}

void **__ckd_calloc_2d__ (int32 d1, int32 d2, int32 elemsize,
			  const char *caller_file, int32 caller_line)
{
    char **ref, *mem;
    int32 i, offset;

    mem = (char *) __ckd_calloc__(d1*d2, elemsize, caller_file, caller_line);
    ref = (char **) __ckd_malloc__(d1 * sizeof(void *), caller_file, caller_line);

    for (i = 0, offset = 0; i < d1; i++, offset += d2*elemsize)
	ref[i] = mem + offset;

    return ((void **) ref);
}

void **__ckd_calloc_2d__a (int32 d1, int32 d2, int32 elemsize,
			  const char *caller_file, int32 caller_line)
{
    char **ref, *mem;
    int32 i, offset;
#ifdef USE_ICC
    mem = (char *) _mm_malloc(d1*d2*elemsize,16);
#else
    mem = (char *) __ckd_calloc__(d1*d2, elemsize, caller_file, caller_line);
#endif
    ref = (char **) __ckd_malloc__(d1 * sizeof(void *), caller_file, caller_line);

    for (i = 0, offset = 0; i < d1; i++, offset += d2*elemsize)
	ref[i] = mem + offset;

    return ((void **) ref);
}


void ckd_free_2da (void **ptr)
{
#ifdef USE_ICC
  _mm_free(ptr[0]);
#else
  ckd_free(ptr[0]);
#endif
    ckd_free(ptr);
}

void ckd_free_2d (void **ptr)
{
  ckd_free(ptr[0]);
  ckd_free(ptr);
}


void ***__ckd_calloc_3d__ (int32 d1, int32 d2, int32 d3, int32 elemsize,
			   const char *caller_file, int32 caller_line)
{
    char ***ref1, **ref2, *mem;
    int32 i, j, offset;

    mem = (char *) __ckd_calloc__(d1*d2*d3, elemsize, caller_file, caller_line);
    ref1 = (char ***) __ckd_malloc__(d1 * sizeof(void **), caller_file, caller_line);
    ref2 = (char **) __ckd_malloc__(d1*d2 * sizeof(void *), caller_file, caller_line);

    for (i = 0, offset = 0; i < d1; i++, offset += d2)
	ref1[i] = ref2+offset;

    offset = 0;
    for (i = 0; i < d1; i++) {
	for (j = 0; j < d2; j++) {
	    ref1[i][j] = mem + offset;
	    offset += d3*elemsize;
	}
    }

    return ((void ***) ref1);
}


void ckd_free_3d (void ***ptr)
{
    ckd_free(ptr[0][0]);
    ckd_free(ptr[0]);
    ckd_free(ptr);
}


/*
 * Structures for managing linked list elements of various sizes without wasting
 * memory.  A separate linked list for each element-size.  Element-size must be a
 * multiple of pointer-size.
 */
typedef struct mylist_s {
    char **freelist;		/* ptr to first element in freelist */
    struct mylist_s *next;	/* Next linked list */
    int32 elemsize;		/* #(char *) in element */
    int32 blocksize;		/* #elements to alloc if run out of free elments */
    int32 blk_alloc;		/* #Alloc operations before increasing blocksize */
} mylist_t;
static mylist_t *head = NULL;

#define MIN_MYALLOC	50	/* Min #elements to allocate in one block */


char *__mymalloc__ (int32 elemsize, char *caller_file, int32 caller_line)
{
    char *cp;
#if (! __PURIFY__)
    int32 j;
    char **cpp;
    mylist_t *prev, *list;
    
    /* Find list for elemsize, if existing */
    prev = NULL;
    for (list = head; list && (list->elemsize != elemsize); list = list->next)
	prev = list;

    if (! list) {
	/* New list element size encountered, create new list entry */
	if ((elemsize % sizeof(void *)) != 0)
	    E_FATAL("List item size (%d) not multiple of sizeof(void *)\n", elemsize);
	
	list = (mylist_t *) ckd_calloc (1, sizeof(mylist_t));
	list->freelist = NULL;
	list->elemsize = elemsize;
	list->blocksize = MIN_MYALLOC;
	list->blk_alloc = (1<<18) / (list->blocksize * elemsize);

	/* Link entry at head of list */
	list->next = head;
	head = list;
    } else if (prev) {
	/* List found; move entry to head of list */
	prev->next = list->next;
	list->next = head;
	head = list;
    }
    
    /* Allocate a new block if list empty */
    if (list->freelist == NULL) {
	/* Check if block size should be increased (if many requests for this size) */
	if (list->blk_alloc == 0) {
	    list->blocksize <<= 1;
	    list->blk_alloc = (1<<18) / (list->blocksize * elemsize);
	    if (list->blk_alloc <= 0)
		list->blk_alloc = (int32)0x70000000;	/* Limit blocksize to new value */
	}

	/* Allocate block */
	cpp = list->freelist = (char **) __ckd_calloc__ (list->blocksize, elemsize,
							 caller_file, caller_line);
	cp = (char *) cpp;
	for (j = list->blocksize - 1; j > 0; --j) {
	    cp += elemsize;
	    *cpp = cp;
	    cpp = (char **)cp;
	}
	*cpp = NULL;
	--(list->blk_alloc);
    }
    
    /* Unlink and return first element in freelist */
    cp = (char *)(list->freelist);
    list->freelist = (char **)(*(list->freelist));
#else
    if ((cp = (char *) malloc (elemsize)) == NULL) {
	E_FATAL("malloc(%d) failed from %s(%d)\n", elemsize, caller_file, caller_line);
    }
#endif

    return (cp);
}


void __myfree__ (char *elem, int32 elemsize, char *caller_file, int32 caller_line)
{
#if (! __PURIFY__)
    char **cpp;
    mylist_t *prev, *list;
    
    /* Find list for elemsize */
    prev = NULL;
    for (list = head; list && (list->elemsize != elemsize); list = list->next)
	prev = list;

    if (! list) {
	E_FATAL("Unknown list item size: %d; called from %s(%d)\n",
		elemsize, caller_file, caller_line);
    } else if (prev) {
	/* List found; move entry to head of list */
	prev->next = list->next;
	list->next = head;
	head = list;
    }

    /*
     * Insert freed item at head of list.
     * NOTE: skipping check for size being multiple of (void *).
     */
    cpp = (char **) elem;
    *cpp = (char *) list->freelist;
    list->freelist = cpp;
#else
    free (elem);
#endif
}
