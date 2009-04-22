/*   
	Custom IOS Module (SDHC)

	Copyright (C) 2008 neimod.
	Copyright (C) 2009 WiiGator.
	Copyright (C) 2009 Waninkoko.

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "syscalls.h"

/* Constants */
#define HEAP_ADDRESS	((void *)0x139A0000)
#define HEAP_SIZE	0x8000

/* Variables */
static s32 heap = -1;


s32 Mem_CreateHeap(void)
{
	/* Heap already created */
	if (heap > 0)
		return 0;

	/* Create heap */
	heap = os_heap_create(HEAP_ADDRESS, HEAP_SIZE);
	if (heap < 0)
		return -1;

	return 0;
} 

void *Mem_Alloc(u32 size)
{
	/* Allocate memory */
	return os_heap_alloc(heap, size);
}

void Mem_Free(void *ptr)
{
	/* Free memory */
	os_heap_free(heap, ptr);
}
