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
#include "types.h"

/* Syscalls */
extern void syscall_9(void);
extern void syscall_a(void);
extern void syscall_e(void);
extern void syscall_16(void);
extern void syscall_17(void);
extern void syscall_18(void);
extern void syscall_1a(void);
extern void syscall_1b(void);
extern void syscall_2a(void);
extern void syscall_2f(void);
extern void syscall_37(void);
extern void syscall_3c(void);
extern void syscall_3f(void);
extern void syscall_40(void);
extern void syscall_44(void);
extern void syscall_45(void);
extern void syscall_46(void);
extern void syscall_4e(void);
extern void syscall_50(void);
extern void syscall_52(void);
extern void syscall_1c(void);
extern void syscall_1d(void);
extern void syscall_21(void);
extern void syscall_22(void);


void os_thread_set_priority(u32 priority)
{
	void (*syscall)(u32) = (void (*)(u32))syscall_9;

	syscall(priority);
}

u32 os_message_queue_create(void *ptr, u32 id)
{
	u32 (*syscall)(void *, u32) = (u32 (*)(void *, u32))syscall_a;

	return syscall(ptr, id);
}

u32 os_message_queue_receive(u32 queue, u32* message, u32 flags)
{
	u32 (*syscall)(u32, u32*, u32) = (u32 (*)(u32, u32*, u32))syscall_e;

	return syscall(queue, message, flags);
}

u32 os_heap_create(void *ptr, u32 size)
{
	u32 (*syscall)(void *, u32) = (u32 (*)(void *, u32))syscall_16;

	return syscall(ptr, size);
}

u32 os_heap_destroy(u32 heap)
{
	u32 (*syscall)( u32) = (u32 (*)(u32))syscall_17;

	return syscall(heap);
}

void *os_heap_alloc(u32 heap, u32 size)
{
	void* (*syscall)(u32, u32) = (void *(*)(u32, u32))syscall_18;

	return syscall(heap, size);
}

void os_heap_free(u32 heap, void *ptr)
{
	void* (*syscall)(u32, void *) = (void* (*)(u32, void *))syscall_1a;

	if (ptr)
		syscall(heap, ptr);
}

u32 os_device_register(const char *devicename, u32 queuehandle)
{
	u32 (*syscall)(const char *, u32) = (u32 (*)(const char *, u32))syscall_1b;

	return syscall(devicename, queuehandle);
}

void os_message_queue_ack(void *message, s32 result)
{
	void (*syscall)(void *, s32) = (void (*)(void *, s32))syscall_2a;

	syscall(message, result);
}

void os_sync_before_read(void *ptr, u32 size)
{
	void (*syscall)(void *, u32) = (void (*)(void *, u32))syscall_3f;

	syscall(ptr, size);
}

void os_sync_after_write(void *ptr, u32 size)
{
	void (*syscall)(void *, u32) = (void (*)(void *, u32))syscall_40;

	syscall(ptr, size);
}

void os_syscall_50(u32 unknown)
{
	void (*syscall)(u32) = (void (*)(u32))syscall_50;

	syscall(unknown);
}

s32 os_open(char *device, s32 mode)
{
        s32 (*syscall)(char *, s32 ) = (s32 (*)(char *, s32 ))syscall_1c;

	return syscall(device,mode);
}

s32 os_close(s32 fd)
{
        s32 (*syscall)(s32 ) = (s32 (*)(s32 ))syscall_1d;

	return syscall(fd);
}

s32 os_ioctl(s32 fd, s32 request, void *buffer_in, s32 bytes_in, void *buffer_io, s32 bytes_io)
{
        s32 (*syscall)(s32, s32, void *, s32, void *, s32) = (s32 (*)(s32, s32, void *, s32, void *, s32))syscall_21;

        return syscall(fd, request, buffer_in, bytes_in, buffer_io, bytes_io);
}

s32 os_ioctlv(s32 fd, s32 request, s32 bytes_in, s32 bytes_out, ioctlv *vector)
{
        s32 (*syscall)(s32, s32, s32, s32, ioctlv *) = (s32 (*)(s32 , s32 , s32, s32, ioctlv *))syscall_22;

        return syscall(fd, request, bytes_in, bytes_out, vector);
}
