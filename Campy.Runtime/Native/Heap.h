// Copyright (c) 2012 DotNetAnywhere
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#if !defined(__HEAP_H)
#define __HEAP_H

#include "MetaData.h"
#include "Types.h"

typedef struct tHeapRoots_ tHeapRoots;
typedef struct tHeapRootEntry_ tHeapRootEntry;

#ifdef DIAG_GC
extern U64 gcTotalTime;
#endif

struct tHeapRootEntry_ {
	U32 numPointers; // The number of pointers within this memory area
	void **pMem;
};

struct tHeapRoots_ {
	U32 capacity;
	U32 num;
	tHeapRootEntry *pHeapEntries;
};

__device__ void Heap_Init();
__device__ void Heap_SetRoots(tHeapRoots *pHeapRoots, void *pRoots, U32 sizeInBytes);
__device__ void Heap_UnmarkFinalizer(HEAP_PTR heapPtr);
__device__ void Heap_GarbageCollect();
__device__ U32 Heap_NumCollections();
__device__ U32 Heap_GetTotalMemory();

__device__ HEAP_PTR Heap_Alloc(tMD_TypeDef *pTypeDef, U32 size);
__device__ HEAP_PTR Heap_AllocType(tMD_TypeDef *pTypeDef);
__device__ void Heap_MakeUndeletable(HEAP_PTR heapEntry);
__device__ void Heap_MakeDeletable(HEAP_PTR heapEntry);

__device__ tMD_TypeDef* Heap_GetType(HEAP_PTR heapEntry);

__device__ HEAP_PTR Heap_Box(tMD_TypeDef *pType, PTR pMem);
__device__ HEAP_PTR Heap_Clone(HEAP_PTR obj);

__device__ U32 Heap_SyncTryEnter(HEAP_PTR obj);
__device__ U32 Heap_SyncExit(HEAP_PTR obj);

__device__ HEAP_PTR Heap_SetWeakRefTarget(HEAP_PTR target, HEAP_PTR weakRef);
__device__ HEAP_PTR* Heap_GetWeakRefAddress(HEAP_PTR target);
__device__ void Heap_RemovedWeakRefTarget(HEAP_PTR target);
#endif