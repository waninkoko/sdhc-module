#ifndef _IOS_SYSCALLS_H_
#define _IOS_SYSCALLS_H_

#include "ipc.h"
#include "types.h"

/* Prototypes */
void  os_thread_set_priority(u32 priority);
u32   os_message_queue_create(void *ptr, u32 id);
u32   os_message_queue_receive(u32 queue, u32 *message, u32 flags);
u32   os_heap_create(void *ptr, u32 size);
u32   os_heap_destroy(u32 heap);
u32   os_device_register(const char *devicename, u32 queuehandle);
void  os_message_queue_ack(void *message, s32 result);
void *os_heap_alloc(u32 heap, u32 size);
void  os_heap_free(u32 heap, void *ptr);
void  os_sync_before_read(void *ptr, u32 size);
void  os_sync_after_write(void *ptr, u32 size);
void  os_syscall_50(u32 unknown);
s32   os_open(char *device, s32 mode);
s32   os_close(s32 fd);
s32   os_ioctl(s32 fd, s32 request, void *buffer_in, s32 bytes_in, void *buffer_io, s32 bytes_io);
s32   os_ioctlv(s32 fd, s32 request, s32 bytes_in, s32 bytes_out, ioctlv *vector);

#endif
