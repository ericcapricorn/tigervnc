/* Copyright (C) 2002-2005 RealVNC Ltd.  All Rights Reserved.
 * Copyright 2011-2015 Pierre Ossman for Cendio AB
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 */
#ifndef __VNCEXTINIT_H__
#define __VNCEXTINIT_H__

#include <stdint.h>
#include <stddef.h>
#include <sys/select.h>

// Only from C++
#ifdef __cplusplus
namespace rfb { class StringParameter; };

extern rfb::StringParameter httpDir;
#endif

#ifdef __cplusplus
extern "C" {
#endif

// vncExt.c
extern int vncNoClipboard;

int vncAddExtension(void);

int vncNotifyQueryConnect(void);

// vncExtInit.cc
extern void* vncFbptr[];
extern int vncFbstride[];

extern int vncInetdSock;

void vncExtensionInit(void);
int vncExtensionIsActive(int scrIdx);

void vncCallReadBlockHandlers(fd_set * fds, struct timeval ** timeout);
void vncCallReadWakeupHandlers(fd_set * fds, int nfds);
void vncCallWriteBlockHandlers(fd_set * fds, struct timeval ** timeout);
void vncCallWriteWakeupHandlers(fd_set * fds, int nfds);

int vncGetAvoidShiftNumLock(void);

int vncGetSetPrimary(void);
int vncGetSendPrimary(void);

void vncUpdateDesktopName(void);

void vncServerCutText(const char *text, size_t len);

int vncConnectClient(const char *addr);

void vncGetQueryConnect(uint32_t *opaqueId, const char**username,
                        const char **address, int *timeout);
void vncApproveConnection(uint32_t opaqueId, int approve);

void vncBell(void);

// Must match rfb::ShortRect in common/rfb/Region.h, and BoxRec in the
// Xorg source.
struct UpdateRect {
  short x1, y1, x2, y2;
};

void vncAddChanged(int scrIdx, const struct UpdateRect *extents,
                   int nRects, const struct UpdateRect *rects);
void vncAddCopied(int scrIdx, const struct UpdateRect *extents,
                  int nRects, const struct UpdateRect *rects,
                  int dx, int dy);

void vncSetCursor(int width, int height, int hotX, int hotY,
                  const unsigned char *rgbaData);

void vncPreScreenResize(int scrIdx);
void vncPostScreenResize(int scrIdx, int success, int width, int height);
void vncRefreshScreenLayout(int scrIdx);

int vncOverrideParam(const char *nameAndValue);

#ifdef __cplusplus
}
#endif

#endif
