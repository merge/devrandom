/*
 * fbutils.c
 *
 * Utility routines for framebuffer interaction
 *
 * (C) 2007-2015 Ginzinger Electronic Systems; manfred.schlaegl@gmx.at
 *
 * Based on fbutils.c from ts_lib-1.0:
 * Copyright 2002 Russell King and Doug Lowder
 *
 * This file is placed under the GPL.  Please see the
 * file COPYING for details.
 *
 */

/***********************************************************************
 *  @History:
 *	2012KW12 - manfred.schlaegl:
 *		* implemented vfbuffer support
 *		* corrected rotation
 *		* improved interface for linrpcd2
 *	2012KW10 - manfred.schlaegl:
 *		* support for display-rotation and -autodetection
 *	2011KW50 - manfred.schlaegl:
 *		* support for 24bit framebuffer (3 bytes per pixel)
 ***********************************************************************/

/*
 * Purpose of this file:
 * Low level functions like "set pixel", "draw char" to manipulate the frame buffer content. Only internally used.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>

#include <linux/vt.h>
#include <linux/kd.h>
#include <linux/fb.h>
#include "font.h"
#include "fbutils.h"

union fb_multiptr {
	unsigned char *p8;
	unsigned short *p16;
	unsigned long *p32;
};

static int fb_last_vt = -1;
static struct fb_fix_screeninfo fb_fix;
static struct fb_var_screeninfo fb_var;
static unsigned char *fb_fbuffer;
static unsigned char **fb_line_addr;
static int fb_bytes_per_pixel;
static unsigned fb_colormap [256];

/* external */
int fb_fd = 0;
int fb_con_fd = 0;
int fb_rotation = 0;
__u32 fb_xres = 0;
__u32 fb_yres = 0;

int fb_vfbuffer_count = 0;
static int fb_vfbuffer_cur_nr;
static unsigned char *fb_vfbuffer_cur;
static unsigned char **fb_vline_addr_cur;
static unsigned char **fb_vfbuffer;
static unsigned char ***fb_vline_addr;

/*
 * show virtual framebuffer
 */
int fb_vfbuffer_show(int idx)
{
	if (idx >= fb_vfbuffer_count)
		return -1;

	/* copy buffer to screen */
	memcpy(fb_fbuffer, fb_vfbuffer[idx], fb_fix.smem_len);

	return 0;
}

/*
 * edit virtual framebuffer
 */
int fb_vfbuffer_edit(int idx)
{
	if (idx >= fb_vfbuffer_count)
		return -1;

	/* copy screen to buffer */
	memcpy(fb_vfbuffer[idx], fb_fbuffer, fb_fix.smem_len);
	fb_vfbuffer_cur_nr = idx;
	fb_vline_addr_cur = fb_vline_addr[idx];
	fb_vfbuffer_cur = fb_vfbuffer[idx];

	return 0;
}

/*
 * init virtual framebuffers
 * return: <0 .. error; 0 .. ok
 */
int fb_vfbuffer_init(int vfbuffer_cnt)
{
	int i, ret;
	unsigned int y, addr;

	fb_vfbuffer_count = 0;

	/* init working */
	if (vfbuffer_cnt) {
		fb_vfbuffer = malloc(vfbuffer_cnt * sizeof(unsigned char *));
		if (!fb_vfbuffer) {
			perror("error allocate vfbuffer array");
			ret = -1;
			goto __ret;
		}

		fb_vline_addr = malloc(vfbuffer_cnt * sizeof(unsigned char **));
		if (!fb_vline_addr) {
			perror("error allocate line-buffer-array");
			ret = -1;
			goto __ret_fb_vline_addr;
		}


		for (i = 0; i < vfbuffer_cnt; i++) {
			fb_vfbuffer[i] = malloc(fb_fix.smem_len * sizeof(unsigned char));
			if (!fb_vfbuffer[i]) {
				perror("error allocate vfbuffer");
				while (--i)
					free(fb_vfbuffer[i]);
				ret = -1;
				goto __ret_fb_vfbuffer;
			}

			fb_vline_addr[i] = malloc(fb_var.yres_virtual * sizeof(unsigned char*));
			if (!fb_vline_addr[i]) {
				perror("error allocate line-buffer-array");
				free(fb_vfbuffer[i]);
				while (--i) {
					free(fb_vfbuffer[i]);
					free(fb_vline_addr[i]);
				}
				ret = -1;
				goto __ret_fb_vfbuffer;
			}

			addr = 0;
			for (y = 0; y < fb_var.yres_virtual; y++, addr += fb_fix.line_length)
				fb_vline_addr[i] [y] = fb_vfbuffer[i] + addr;
		}

		/* enable use of virtutal frame-buffer */
		fb_vfbuffer_edit(0);
	} else {
		/* no virtual frame-buffer */
		fb_vfbuffer_cur_nr = 0;
		fb_vline_addr_cur = fb_line_addr;
		fb_vfbuffer_cur = fb_fbuffer;
	}

	/* ok */
	fb_vfbuffer_count = vfbuffer_cnt;
	ret = 0;
	goto __ret;

__ret_fb_vfbuffer:
	free(fb_vline_addr);
__ret_fb_vline_addr:
	free(fb_vfbuffer);
__ret:
	return ret;
}

/*
 * free virtual framebuffers
 */
void fb_vfbuffer_free(void)
{
	int i;

	if (fb_vfbuffer_count) {
		/* free vbuffers */
		for (i = 0; i < fb_vfbuffer_count; i++) {
			free (fb_vline_addr[i]);
			free (fb_vline_addr);
			free (fb_vfbuffer[i]);
			free (fb_vfbuffer);
		}
	}
	fb_vfbuffer_count = 0;
}


/*
 * get and return console rotation
 * use default rotation 0 on error
 */
int fb_get_rotation(void)
{
	int ret, fd;
	unsigned char c = 0;

	fd = open("/sys/class/graphics/fbcon/rotate", O_RDONLY);
	if (fd < 0) {
		perror("open /sys/class/graphics/fbcon/rotate -> use default");
		return 0;
	}

	ret = read(fd, &c, 1);
	close(fd);

	c = c - '0';
	if (c > 3)
		c = 0;

	if (ret < 0 || c > 3) {
		perror("read /sys/class/graphics/fbcon/rotate -> use default");
		return 0;
	}

	return c;
}

int fb_open(char *fb_dev, char *con_dev, int vbuffer_cnt)
{
	struct vt_stat vts;
	char vtname[128];
	int fd, nr;
	unsigned y, addr;

	fb_rotation = fb_get_rotation();
	fb_con_fd = -1;
	if (strcmp (con_dev, "none") != 0) {
		sprintf (vtname, "%s%d", con_dev, 1);
		fd = open (vtname, O_WRONLY);
		if (fd < 0) {
			perror("open consoledevice");
			return -1;
		}

		if (ioctl(fd, VT_OPENQRY, &nr) < 0) {
			perror("ioctl VT_OPENQRY");
			close(fd);
			return -1;
		}
		close(fd);

		sprintf(vtname, "%s%d", con_dev, nr);
		fb_con_fd = open(vtname, O_RDWR | O_NDELAY);
		if (fb_con_fd < 0) {
			perror("open tty");
			return -1;
		}

		if (ioctl(fb_con_fd, VT_GETSTATE, &vts) == 0)
			fb_last_vt = vts.v_active;

		if (ioctl(fb_con_fd, VT_ACTIVATE, (char*)nr) < 0) {
			perror("VT_ACTIVATE");
			close(fb_con_fd);
			return -1;
		}

		if (ioctl(fb_con_fd, VT_WAITACTIVE, (char*)nr) < 0) {
			perror("VT_WAITACTIVE");
			close(fb_con_fd);
			return -1;
		}

		if (ioctl(fb_con_fd, KDSETMODE, (char*)KD_GRAPHICS) < 0) {
			perror("KDSETMODE");
			close(fb_con_fd);
			return -1;
		}
	}

	fb_fd = open(fb_dev, O_RDWR);
	if (fb_fd == -1) {
		perror("open fbdevice");
		fb_fd = -1;
		if (fb_con_fd >= 0)
			close(fb_con_fd);
		return -1;
	}

	if (ioctl(fb_fd, FBIOGET_FSCREENINFO, &fb_fix) < 0) {
		perror("ioctl FBIOGET_FSCREENINFO");
		if (fb_con_fd >= 0)
			close(fb_con_fd);
		close(fb_fd);
		return -1;
	}

	if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &fb_var) < 0) {
		perror("ioctl FBIOGET_VSCREENINFO");
		if (fb_con_fd >= 0)
			close(fb_con_fd);
		close(fb_fd);
		return -1;
	}

	fb_fbuffer = mmap(NULL, fb_fix.smem_len, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, fb_fd, 0);
	if (fb_fbuffer == (unsigned char *) - 1) {
		perror("mmap framebuffer");
		if (fb_con_fd >= 0)
			close(fb_con_fd);
		close(fb_fd);
		return -1;
	}

	fb_bytes_per_pixel = (fb_var.bits_per_pixel + 7) / 8;
	fb_line_addr = malloc (sizeof (__u32) * fb_var.yres_virtual);
	if (!fb_line_addr) {
		perror("malloc line_addr");
		if (fb_con_fd >= 0)
			close(fb_con_fd);
		close(fb_fd);
	}
	addr = 0;
	for (y = 0; y < fb_var.yres_virtual; y++, addr += fb_fix.line_length)
		fb_line_addr [y] = fb_fbuffer + addr;

	/* correct resolutions for rotated fb */
	if (fb_rotation & 1) {
		/* 1,3 */
		y = fb_var.yres;
		fb_var.yres = fb_var.xres;
		fb_var.xres = y;
	}
	fb_xres = fb_var.xres;
	fb_yres = fb_var.yres;

	if (fb_vfbuffer_init(vbuffer_cnt) < 0) {
		fb_close();
		return -1;
	}

	return 0;
}

void fb_close(void)
{
	munmap(fb_fbuffer, fb_fix.smem_len);
	if (fb_con_fd >= 0) {
		if (ioctl(fb_con_fd, KDSETMODE, KD_TEXT) < 0)
			perror("KDSETMODE");

		if (fb_last_vt >= 0)
			if (ioctl(fb_con_fd, VT_ACTIVATE, (char*)fb_last_vt))
				perror("VT_ACTIVATE");

		close(fb_con_fd);
	}
	free (fb_line_addr);
	close(fb_fd);

	fb_vfbuffer_free();

	/* reset data */
	fb_fd = 0;
	fb_con_fd = 0;
	fb_rotation = 0;
	fb_xres = 0;
	fb_yres = 0;
	fb_last_vt = -1;
	memset(&fb_colormap, 0, 256 * sizeof(unsigned));
}

void fb_clear(void)
{
	memset(fb_vfbuffer_cur, 0, fb_fix.smem_len);
}

void fb_put_char(int x, int y, int c, int colidx)
{
	int i, j, bits;

	for (i = 0; i < font_vga_8x8.height; i++) {
		bits = font_vga_8x8.data [font_vga_8x8.height * c + i];
		for (j = 0; j < font_vga_8x8.width; j++, bits <<= 1)
			if (bits & 0x80)
				fb_pixel (x + j, y + i, colidx);
	}
}

void fb_put_string(int x, int y, char *s, unsigned colidx)
{
	int i;
	for (i = 0; *s; i++, x += font_vga_8x8.width, s++)
		fb_put_char (x, y, *s, colidx);
}

void fb_put_string_center(int x, int y, char *s, unsigned colidx)
{
	size_t sl = strlen (s);
	fb_put_string (x - (sl / 2) * font_vga_8x8.width,
		       y - font_vga_8x8.height / 2, s, colidx);
}

void fb_setcolor(unsigned colidx, unsigned value)
{
	unsigned res;
	unsigned short red, green, blue;
	struct fb_cmap cmap;

	if (colidx > 255)
		return;

	switch (fb_bytes_per_pixel) {
	default:
	case 1:
		res = colidx;
		red = (value >> 8) & 0xff00;
		green = value & 0xff00;
		blue = (value << 8) & 0xff00;
		cmap.start = colidx;
		cmap.len = 1;
		cmap.red = &red;
		cmap.green = &green;
		cmap.blue = &blue;
		cmap.transp = NULL;

		if (ioctl (fb_fd, FBIOPUTCMAP, &cmap) < 0)
			perror("ioctl FBIOPUTCMAP");
		break;
	case 2:
	case 3:
	case 4:
		red = (value >> 16) & 0xff;
		green = (value >> 8) & 0xff;
		blue = value & 0xff;
		res = ((red >> (8 - fb_var.red.length)) << fb_var.red.offset) |
		      ((green >> (8 - fb_var.green.length)) << fb_var.green.offset) |
		      ((blue >> (8 - fb_var.blue.length)) << fb_var.blue.offset);
		break;
	}
	fb_colormap [colidx] = res;
}



static void __fb_pixel_loc (int x, int y, union fb_multiptr *loc)
{
	switch (fb_rotation) {
	case 0:
	default:
		loc->p8 = fb_vline_addr_cur [y] + x * fb_bytes_per_pixel;
		break;
	case 1:
		loc->p8 = fb_vline_addr_cur [x] + (fb_yres - y - 1) * fb_bytes_per_pixel;
		break;
	case 2:
		loc->p8 = fb_vline_addr_cur [fb_yres - y - 1] + (fb_xres - x - 1) * fb_bytes_per_pixel;
		break;
	case 3:
		loc->p8 = fb_vline_addr_cur [fb_xres - x - 1] + y * fb_bytes_per_pixel;
		break;
	}
}

static inline void __fb_setpixel (union fb_multiptr loc, unsigned xormode, unsigned color)
{
	switch (fb_bytes_per_pixel) {
	case 1:
	default:
		if (xormode)
			*loc.p8 ^= color;
		else
			*loc.p8 = color;
		break;
	case 2:
		if (xormode)
			*loc.p16 ^= color;
		else
			*loc.p16 = color;
		break;
	case 3:
		if (xormode) {
			*(loc.p8 + 0) ^= ((color >> 0) & 0xff);
			*(loc.p8 + 1) ^= ((color >> 8) & 0xff);
			*(loc.p8 + 2) ^= ((color >> 16) & 0xff);
		} else {
			*(loc.p8 + 0) = ((color >> 0) & 0xff);
			*(loc.p8 + 1) = ((color >> 8) & 0xff);
			*(loc.p8 + 2) = ((color >> 16) & 0xff);
		}
		break;
	case 4:
		if (xormode)
			*loc.p32 ^= color;
		else
			*loc.p32 = color;
		break;
	}
}

void fb_pixel (int x, int y, unsigned colidx)
{
	unsigned xormode;
	union fb_multiptr loc;

	if ((x < 0) || ((__u32)x >= fb_xres) ||
	    (y < 0) || ((__u32)y >= fb_yres))
		return;

	xormode = colidx & XORMODE;
	colidx &= ~XORMODE;

	if (colidx > 255)
		return;

	__fb_pixel_loc (x, y, &loc);
	__fb_setpixel (loc, xormode, fb_colormap [colidx]);
}

/*
 * get pixel
 * 	x,y .. coords
 * return:
 *	color-value (RGB888)
 */
unsigned fb_get_pixel (int x, int y)
{
	union fb_multiptr loc;

	if ((x < 0) || ((__u32)x >= fb_xres) ||
	    (y < 0) || ((__u32)y >= fb_yres))
		return 0;

	__fb_pixel_loc (x, y, &loc);

	unsigned int red, green, blue;
	unsigned int color;

	switch (fb_bytes_per_pixel) {
	case 1:
	default:
		fprintf(stderr, "unsupported color format\n");
		return 0;
		break;
	case 2:
		color = *loc.p16;
		break;
	case 3:
		color = (
				((*(loc.p8 + 2)) << 16) |
				((*(loc.p8 + 1)) << 8) |
				((*(loc.p8 + 0)) << 0)
			);
		break;
	case 4:
		color = *loc.p32;
		break;
	}

	red = (((color >> fb_var.red.offset) << (8 - fb_var.red.length)) & 0xff);
	green = (((color >> fb_var.green.offset) << (8 - fb_var.green.length)) & 0xff);
	blue = (((color >> fb_var.blue.offset) << (8 - fb_var.blue.length)) & 0xff);
	return (red << 16) | (green << 8) | (blue);
}

void fb_line (int x1, int y1, int x2, int y2, unsigned colidx)
{
	int tmp;
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (abs (dx) < abs (dy)) {
		if (y1 > y2) {
			tmp = x1;
			x1 = x2;
			x2 = tmp;
			tmp = y1;
			y1 = y2;
			y2 = tmp;
			dx = -dx;
			dy = -dy;
		}
		x1 <<= 16;
		/* dy is apriori >0 */
		dx = (dx << 16) / dy;
		while (y1 <= y2) {
			fb_pixel (x1 >> 16, y1, colidx);
			x1 += dx;
			y1++;
		}
	} else {
		if (x1 > x2) {
			tmp = x1;
			x1 = x2;
			x2 = tmp;
			tmp = y1;
			y1 = y2;
			y2 = tmp;
			dx = -dx;
			dy = -dy;
		}
		y1 <<= 16;
		dy = dx ? (dy << 16) / dx : 0;
		while (x1 <= x2) {
			fb_pixel (x1, y1 >> 16, colidx);
			y1 += dy;
			x1++;
		}
	}
}

void fb_rect (int x1, int y1, int x2, int y2, unsigned colidx)
{
	fb_line (x1, y1, x2, y1, colidx);
	fb_line (x2, y1, x2, y2, colidx);
	fb_line (x2, y2, x1, y2, colidx);
	fb_line (x1, y2, x1, y1, colidx);
}

void fb_fillrect (int x1, int y1, int x2, int y2, unsigned colidx)
{
	int tmp, trans_x1, trans_y1, trans_x2, trans_y2;
	unsigned xormode;
	union fb_multiptr loc;

	/* Clipping and sanity checking */
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	if (x1 < 0) x1 = 0;
	if ((__u32)x1 >= fb_xres) x1 = fb_xres - 1;
	if (x2 < 0) x2 = 0;
	if ((__u32)x2 >= fb_xres) x2 = fb_xres - 1;
	if (y1 < 0) y1 = 0;
	if ((__u32)y1 >= fb_yres) y1 = fb_yres - 1;
	if (y2 < 0) y2 = 0;
	if ((__u32)y2 >= fb_yres) y2 = fb_yres - 1;

	if ((x1 > x2) || (y1 > y2))
		return;

	xormode = colidx & XORMODE;
	colidx &= ~XORMODE;

	if (colidx > 255)
		return;
	colidx = fb_colormap [colidx];


	switch (fb_rotation) {
	default:
	case 0:
		trans_x1 = x1;
		trans_y1 = y1;
		trans_x2 = x2;
		trans_y2 = y2;
		break;
	case 1:
		trans_y1 = x1;
		trans_x2 = fb_yres - y1 - 1;
		trans_y2 = x2;
		trans_x1 = fb_yres - y2 - 1;
		break;
	case 2:
		trans_x2 = fb_xres - x1 - 1;
		trans_y2 = fb_yres - y1 - 1;
		trans_x1 = fb_xres - x2 - 1;
		trans_y1 = fb_yres - y2 - 1;
		break;
	case 3:
		trans_y2 = fb_xres - x1 - 1;
		trans_x1 = y1;
		trans_y1 = fb_xres - x2 - 1;
		trans_x2 = y2;
		break;
	}

	if (1) {
		if (trans_x1 > trans_x2) {
			fprintf (stderr, "WARNING: fb_fillrect trans_x1>trans_x2 -> swap\n");
			tmp = trans_x1;
			trans_x1 = trans_x2;
			trans_x2 = tmp;
		}
		if (trans_y1 > trans_y2) {
			fprintf (stderr, "WARNING: fb_fillrect trans_y1>trans_y2 -> swap\n");
			tmp = trans_y1;
			trans_y1 = trans_y2;
			trans_y2 = tmp;
		}
	}

	for (; trans_y1 <= trans_y2; trans_y1++) {
		loc.p8 = fb_vline_addr_cur [trans_y1] + trans_x1 * fb_bytes_per_pixel;
		for (tmp = trans_x1; tmp <= trans_x2; tmp++) {
			__fb_setpixel (loc, xormode, colidx);
			loc.p8 += fb_bytes_per_pixel;
		}
	}
}

