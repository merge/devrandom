/*
 * fbutils.c
 *
 * Utility routines for framebuffer interaction
 *
 * (C) 2007-2012 Ginzinger Electronic Systems; manfred.schlaegl@gmx.at
 *
 * Based on fbutils.h from ts_lib-1.0:
 * Copyright 2002 Russell King and Doug Lowder
 *
 * This file is placed under the GPL.  Please see the
 * file COPYING for details.
 *
 */

/*
 * Purpose of this file:
 * Low level functions like "set pixel", "draw char" to manipulate the frame buffer content. Only internally used.
 */
#ifndef _FBUTILS_H
#define _FBUTILS_H

#include <asm/types.h>

/* This constant, being ORed with the color index tells the library
 * to draw in exclusive-or mode (that is, drawing the same second time
 * in the same place will remove the element leaving the background intact).
 */
#define XORMODE	0x80000000

extern int fb_fd;
extern int fb_con_fd;
extern int fb_rotation;
extern __u32 fb_xres;
extern __u32 fb_yres;

/*
 * get and return console rotation
 * use default rotation 0 on error
 */
int fb_get_rotation(void);

/*
 * open framebuffer
 * 	fb_dev .. framebuffer to use
 *	con_dev .. console to use ("none" if no console)
 *	vbuffer_cnt .. number of virtual framebuffers (0 .. disabled, else number)
 * return: 0 .. ok; <0 .. error
 */
int fb_open(char *fb_dev, char *con_dev, int vbuffer_cnt);

/*
 * close framebuffer
 */
void fb_close(void);

/*
 * reset to black
 */
void fb_clear(void);

/*
 * show virtual framebuffer (if enabled in open)
 *	idx .. number of virtual framebuffer to use
 * return: 0 .. ok; <0 .. error
 */
int fb_vfbuffer_show(int idx);

/*
 * edit virtual framebuffer (if enabled in open)
 *	idx .. number of virtual framebuffer to use
 * return: 0 .. ok; <0 .. error
 */
int fb_vfbuffer_edit(int idx);

/*
 * set color in color-table
 *	colidx .. color-table-index
 *	value .. color-value (RGB888)
 */
void fb_setcolor(unsigned colidx, unsigned value);

/*
 * put char
 * 	x,y .. coords
 *	c .. character code
 *	colidx .. color-table-index
 */
void fb_put_char(int x, int y, int c, int colidx);

/*
 * put string
 * 	x,y .. coords
 *	s .. string
 *	colidx .. color-table-index
 */
void fb_put_string(int x, int y, char *s, unsigned colidx);

/*
 * put string centered
 * 	x,y .. coords of center
 *	s .. string
 *	colidx .. color-table-index
 */
void fb_put_string_center(int x, int y, char *s, unsigned colidx);

/*
 * draw pixel
 * 	x,y .. coords
 *	colidx .. color-table-index
 */
void fb_pixel (int x, int y, unsigned colidx);

/*
 * get pixel
 * 	x,y .. coords
 * return:
 *	color-value (RGB888)
 */
unsigned fb_get_pixel (int x, int y);

/*
 * draw line
 * 	x1,y1 .. start-coords
 * 	x2,y2 .. end-coords
 *	colidx .. color-table-index
 */
void fb_line (int x1, int y1, int x2, int y2, unsigned colidx);

/*
 * draw rect/fillrect
 * 	x1,y1 .. start-coords
 * 	x2,y2 .. end-coords
 *	colidx .. color-table-index
 */
void fb_rect (int x1, int y1, int x2, int y2, unsigned colidx);
void fb_fillrect (int x1, int y1, int x2, int y2, unsigned colidx);

#endif /* _FBUTILS_H */

