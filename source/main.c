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

#include <string.h>

#include "ipc.h"
#include "mem.h"
#include "sdio.h"
#include "syscalls.h"
#include "types.h"
#include "wbfs.h"

#define WBFS_BASE		(('W'<<24)|('F'<<16)|('S'<<8))

/* IOCTL commands */
#define IOCTL_SDHC_INIT		0x01
#define IOCTL_SDHC_READ		0x02
#define IOCTL_SDHC_WRITE	0x03
#define IOCTL_SDHC_ISINSERTED	0x04
#define IOCTL_WBFS_OPEN_DISC	(WBFS_BASE + 0x1)
#define IOCTL_WBFS_READ_DISC	(WBFS_BASE + 0x2)

/* Device name */
#define DEVICE_NAME		"/dev/sdio/sdhc"

/* Heap space */
static u32 heapspace[0x800] ATTRIBUTE_ALIGN(32);


s32 Ioctlv_Parse(ipcmessage *message)
{
	ioctlv *vector = message->ioctlv.vector;

	s32 ret = IPC_EINVAL;

	/* Parse IOCTL command */
	switch (message->ioctl.command) {
	case IOCTL_SDHC_INIT: {
		/* Initialize SDIO */
		ret = !sdio_Startup();

		break;
	}

	case IOCTL_SDHC_READ: {
		u32   sector     = *(u32 *)(vector[0].data);
		u32   numSectors = *(u32 *)(vector[1].data);
		void *buffer     = vector[2].data;

		/* Read sectors */
		ret = !sdio_ReadSectors(sector, numSectors, buffer);

		break;
	}

	case IOCTL_SDHC_WRITE: {
		u32   sector     = *(u32 *)(vector[0].data);
		u32   numSectors = *(u32 *)(vector[1].data);
		void *buffer     = vector[2].data;

		/* Write sectors */
		ret = !sdio_WriteSectors(sector, numSectors, buffer);

		break;
	}

	case IOCTL_SDHC_ISINSERTED: {
		/* Check if SD card is inserted */
		ret = !sdio_IsInserted();

		break;
	}

	case IOCTL_WBFS_OPEN_DISC: {
		u8 *discid = (u8 *)(vector[0].data);

		/* Open WBFS disc */
		ret = WBFS_OpenDisc(discid);

		break;
	}

	case IOCTL_WBFS_READ_DISC: {
		u32   offset = *(u32 *)(vector[0].data);
		u32   len    = *(u32 *)(vector[1].data);
		void *buffer = vector[2].data;

		/* Read WBFS disc */
		ret = WBFS_Read(buffer, len, offset);
		if (ret)
			ret = 0x8000;

		break;
	}

	default:
		break;
	}

	return ret;
}

int main(void)
{
	void *queuespace = NULL;
	u32   heaphandle, queuehandle;

	/* Create heap */
	Mem_CreateHeap();

	/* Create main heap */
	heaphandle = os_heap_create(heapspace, sizeof(heapspace));

	/* Create queue */
	queuespace  = os_heap_alloc(heaphandle, 0x20);
	queuehandle = os_message_queue_create(queuespace, 8);

	/* Register device */
	os_device_register(DEVICE_NAME, queuehandle);

	/* Main loop */
	while (1) {
		ipcmessage *message = NULL;

		s32 ack = 1, ret = IPC_EINVAL;

		/* Wait for message */
		os_message_queue_receive(queuehandle, (void *)&message, 0);

		switch (message->command) {
		case IOS_OPEN: {
			/* Check device path */
			if (!strcmp(message->open.device, DEVICE_NAME))
				ret = message->open.resultfd;
			else
				ret = IPC_ENOENT;

			break;
		}

		case IOS_CLOSE: {
			/* Close SDIO */
			ret = !sdio_Shutdown();

			break;
		}

		case IOS_IOCTLV: {
			/* Parse IOCTLV message */
			ret = Ioctlv_Parse(message);
		}

		default:
			break;
		}

		if (ack)
			os_message_queue_ack((void *)message, ret);
	}
   
	return 0;
}
