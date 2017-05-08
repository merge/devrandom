/*
 *  tslib/tests/ts_calibrate.c
 *
 *  Copyright (C) 2001 Russell King.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 * $Id: ts_calibrate.c,v 1.8 2004/10/19 22:01:27 dlowder Exp $
 *
 * Basic test program for touchscreen library.
 */
//#include "config.h"

/*
 * Purpose of this file:
 * Helper functions for display-test-module. This file contains functions to
 * calibrate and validate a GE-touchscreen.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <errno.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <linux/fb.h>
#include <cmd_misc.h>

#include <fbutils.h>
#include <tsutils.h>
#include "cmd_fbutils.h"
#include "display_touch.h"

/* distance of crosses to display-bounds */
#define CROSS_BOUND_DISTANCE	50

static int palette [] = {
	0x000000, 0xffe080, 0xffffff, 0xe0c0a0, 0xff0000, 0x00ff00
};
#define NR_COLORS (sizeof (palette) / sizeof (palette [0]))

typedef struct {
	int x[5], xfb[5];
	int y[5], yfb[5];
	int a[7];
} calibration;
int ts_calibrate_last_x;
int ts_calibrate_last_y;

/*
 * get ts-coords
 * parameters:
 * 	ts .. touchscreen descriptor
 * 	x .. pointer to read x
 *  y .. pointer to read y
 *  raw .. raw-mode-enable
 * returns: 0 .. ok; -1 .. error
 */

static int sort_by_x(const void* a, const void *b)
{
	return (((struct ts_sample *)a)->x - ((struct ts_sample *)b)->x);
}

static int sort_by_y(const void* a, const void *b)
{
	return (((struct ts_sample *)a)->y - ((struct ts_sample *)b)->y);
}

int getxy(struct tsdev *ts, int *x, int *y, int raw)
{
#define MAX_SAMPLES 128
	struct ts_sample samp[MAX_SAMPLES];
	int index, middle;
	int ret;

	do {
		if (raw) {
			ret = tsutil_read_raw(ts, &samp[0]);
		} else {
			ret = tsutil_read(ts, &samp[0]);
		}
		if (ret < 0) {
			cmd_err_printf("tsutil_read: %s\n", strerror(errno));
			return -1;
		}
	} while (samp[0].pressure == 0);

	/* Now collect up to MAX_SAMPLES touches into the samp array. */
	index = 0;
	do {
		if (index < MAX_SAMPLES - 1)
			index++;
		if (raw) {
			ret = tsutil_read_raw(ts, &samp[index]);
		} else {
			ret = tsutil_read(ts, &samp[index]);
		}
		if (ret < 0) {
			cmd_err_printf("tsutil_read: %s\n", strerror(errno));
			return -1;
		}
	} while (samp[index].pressure > 0);
	cmd_printf("Took %d samples...\n", index);

	if (raw) {
		/*
		 * At this point, we have samples in indices zero to (index-1)
		 * which means that we have (index) number of samples.  We want
		 * to calculate the median of the samples so that wild outliers
		 * don't skew the result.  First off, let's assume that arrays
		 * are one-based instead of zero-based.  If this were the case
		 * and index was odd, we would need sample number ((index+1)/2)
		 * of a sorted array; if index was even, we would need the
		 * average of sample number (index/2) and sample number
		 * ((index/2)+1).  To turn this into something useful for the
		 * real world, we just need to subtract one off of the sample
		 * numbers.  So for when index is odd, we need sample number
		 * (((index+1)/2)-1).  Due to integer division truncation, we
		 * can simplify this to just (index/2).  When index is even, we
		 * need the average of sample number ((index/2)-1) and sample
		 * number (index/2).  Calculate (index/2) now and we'll handle
		 * the even odd stuff after we sort.
		 */
		middle = index / 2;
		if (x) {
			qsort(samp, index, sizeof(struct ts_sample), sort_by_x);
			if (index & 1)
				*x = samp[middle].x;
			else
				*x = (samp[middle - 1].x + samp[middle].x) / 2;
		}
		if (y) {
			qsort(samp, index, sizeof(struct ts_sample), sort_by_y);
			if (index & 1)
				*y = samp[middle].y;
			else
				*y = (samp[middle - 1].y + samp[middle].y) / 2;
		}
	} else {
		if (x)
			*x = samp[index - 1].x;
		if (y)
			*y = samp[index - 1].y;
	}
	return 0;
}

/*
 * flush tsbuffer
 * parameters:
 * 	ts .. touchscreen descriptor
 */

/*
 * calibration
 * parameters:
 * 	cal .. calibration
 * returns: 0 .. ok; -1 .. failed
 */
int perform_calibration(calibration *cal)
{
	int j;
	float n, x, y, x2, y2, xy, z, zx, zy;
	float det, a, b, c, e, f, i;
	float scaling = 65536.0;

// Get sums for matrix
	n = x = y = x2 = y2 = xy = 0;
	for (j = 0; j < 5; j++) {
		n += 1.0;
		x += (float)cal->x[j];
		y += (float)cal->y[j];
		x2 += (float)(cal->x[j] * cal->x[j]);
		y2 += (float)(cal->y[j] * cal->y[j]);
		xy += (float)(cal->x[j] * cal->y[j]);
	}

// Get determinant of matrix -- check if determinant is too small
	det = n * (x2 * y2 - xy * xy) + x * (xy * y - x * y2) + y * (x * xy - y * x2);
	if (det < 0.1 && det > -0.1) {
		cmd_printf("ts_calibrate: determinant is too small -- %f\n", det);
		return -1;
	}

// Get elements of inverse matrix
	a = (x2 * y2 - xy * xy) / det;
	b = (xy * y - x * y2) / det;
	c = (x * xy - y * x2) / det;
	e = (n * y2 - y * y) / det;
	f = (x * y - n * xy) / det;
	i = (n * x2 - x * x) / det;

// Get sums for x calibration
	z = zx = zy = 0;
	for (j = 0; j < 5; j++) {
		z += (float)cal->xfb[j];
		zx += (float)(cal->xfb[j] * cal->x[j]);
		zy += (float)(cal->xfb[j] * cal->y[j]);
	}

// Now multiply out to get the calibration for framebuffer x coord
	cal->a[0] = (int)((a * z + b * zx + c * zy) * (scaling));
	cal->a[1] = (int)((b * z + e * zx + f * zy) * (scaling));
	cal->a[2] = (int)((c * z + f * zx + i * zy) * (scaling));

	cmd_printf("%f %f %f\n", (a * z + b * zx + c * zy),
		   (b * z + e * zx + f * zy),
		   (c * z + f * zx + i * zy));

// Get sums for y calibration
	z = zx = zy = 0;
	for (j = 0; j < 5; j++) {
		z += (float)cal->yfb[j];
		zx += (float)(cal->yfb[j] * cal->x[j]);
		zy += (float)(cal->yfb[j] * cal->y[j]);
	}

// Now multiply out to get the calibration for framebuffer y coord
	cal->a[3] = (int)((a * z + b * zx + c * zy) * (scaling));
	cal->a[4] = (int)((b * z + e * zx + f * zy) * (scaling));
	cal->a[5] = (int)((c * z + f * zx + i * zy) * (scaling));

	cmd_printf("%f %f %f\n", (a * z + b * zx + c * zy),
		   (b * z + e * zx + f * zy),
		   (c * z + f * zx + i * zy));

// If we got here, we're OK, so assign scaling to a[6] and return
	cal->a[6] = (int)scaling;
	return 0;
	/*
	// This code was here originally to just insert default values
		for(j=0;j<7;j++) {
			c->a[j]=0;
		}
		c->a[1] = c->a[5] = c->a[6] = 1;
		return 1;
	*/

}

/*
 * get calibration sample
 * parameters:
 * 	ts .. touchscreen descriptor
 * 	cal .. calibration
 * 	index .. cal-index
 * 	x .. x-cross-position
 * 	y .. y-cross-position
 * 	name .. name of point
 * returns: 0 .. ok; -1 .. error
 */
static int get_sample (struct tsdev *ts, calibration *cal,
		       int index, int x, int y, char *name)
{
	if (ts_calibrate_last_x != -1) {
#define NR_STEPS 10
		int dx = ((x - ts_calibrate_last_x) << 16) / NR_STEPS;
		int dy = ((y - ts_calibrate_last_y) << 16) / NR_STEPS;
		int i;
		ts_calibrate_last_x <<= 16;
		ts_calibrate_last_y <<= 16;
		for (i = 0; i < NR_STEPS; i++) {
			disp_put_cross (ts_calibrate_last_x >> 16, ts_calibrate_last_y >> 16, 2 | XORMODE);
			usleep (1000);
			disp_put_cross (ts_calibrate_last_x >> 16, ts_calibrate_last_y >> 16, 2 | XORMODE);
			ts_calibrate_last_x += dx;
			ts_calibrate_last_y += dy;
		}
	}

	disp_put_cross(x, y, 2 | XORMODE);
	if (getxy(ts, &cal->x [index], &cal->y [index], 1) == -1)
		return -1;
	disp_put_cross(x, y, 2 | XORMODE);

	ts_calibrate_last_x = cal->xfb [index] = x;
	ts_calibrate_last_y = cal->yfb [index] = y;

	cmd_printf("%s : X = %4d Y = %4d\n", name, cal->x [index], cal->y [index]);
	return 0;
}

/*
 * validate calibration sample
 * parameters:
 * 	ts .. touchscreen descriptor
 * 	x .. x-cross-position
 * 	y .. y-cross-position
 * 	name .. name of point
 *  bound .. number of pixels where detection is valid
 * returns: 0 .. valid; 1 .. invalid; -1 .. error;
 */
static int validate_sample(struct tsdev *ts, int x, int y, char *name, int bound)
{
	int ret;
	int press_x, press_y;

	if (ts_calibrate_last_x != -1) {
#define NR_STEPS 10
		int dx = ((x - ts_calibrate_last_x) << 16) / NR_STEPS;
		int dy = ((y - ts_calibrate_last_y) << 16) / NR_STEPS;
		int i;
		ts_calibrate_last_x <<= 16;
		ts_calibrate_last_y <<= 16;
		for (i = 0; i < NR_STEPS; i++) {
			disp_put_cross (ts_calibrate_last_x >> 16, ts_calibrate_last_y >> 16, 2 | XORMODE);
			usleep (1000);
			disp_put_cross (ts_calibrate_last_x >> 16, ts_calibrate_last_y >> 16, 2 | XORMODE);
			ts_calibrate_last_x += dx;
			ts_calibrate_last_y += dy;
		}
	}

	disp_put_cross(x, y, 2 | XORMODE);
	if (getxy(ts, &press_x, &press_y, 0) == -1)
		return -1;

	/* check hit */
	if ((press_x > x - bound) && (press_x < x + bound) && (press_y > y - bound) && (press_y < y + bound)) {
		/* hit -> valid */
		ret = 0;
	} else {
		/* miss -> invalid */
		ret = 1;
	}
	disp_put_cross(x, y, 2 | XORMODE);

	ts_calibrate_last_x = x;
	ts_calibrate_last_y = y;

	cmd_printf("%s : X = %4d(%4d) Y = %4d(%4d) -> %s\n", name, press_x, x, press_y, y, ret ? "missed" : "hit");
	return ret;
}

/*
 * save calibration
 * parameters:
 * 	calfile .. file to save (atomic)
 * 	cal .. calibration to save
 * returns: -1 .. error; 0 .. ok
 */
int ts_save(char *calfile, calibration cal)
{
	int i;
	int cal_fd;
	char cal_buffer[256];
	char calfile_invalid[512];

	cmd_printf ("Saving calibration constants: ");
	for (i = 0; i < 7; i++)
		cmd_printf("%d ", cal.a [i]);
	cmd_printf("\nto %s\n", calfile);

	/* save to temp-file */
	sprintf(calfile_invalid, "%s_INVALID", calfile);
	cal_fd = open(
			 calfile_invalid,
			 O_CREAT | O_TRUNC | O_RDWR,
			 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
		 );
	if (cal_fd < 0) {
		cmd_err_printf("error open inv-calfile: %s\n", strerror(errno));
		return -1;
	}
	sprintf (cal_buffer, "%d %d %d %d %d %d %d",
		 cal.a[1], cal.a[2], cal.a[0],
		 cal.a[4], cal.a[5], cal.a[3], cal.a[6]);

	i = strlen (cal_buffer) + 1;
	if (write (cal_fd, cal_buffer, i) != i) {
		cmd_err_printf("error writing to inv-calfile: %s\n", strerror(errno));
		close (cal_fd);
		return -1;
	}
	close(cal_fd);

	/* set valid */
	if (rename(calfile_invalid, calfile) < 0) {
		cmd_err_printf("error renaming inv-calfile to calfile: %s\n", strerror(errno));
		return -1;
	}

	/* set env */
	setenv("TSLIB_CALIBFILE", calfile, 1);

	/* save to flash */
	sync();

	return 0;
}

int ts_validate_raw(int bound, char *tsdevice, char *tsconffile, char *tsplugindir, char *calfile)
{
	int ret;
	struct tsdev *ts;
	char buff[64];

	/* prepare display message */
	snprintf(buff, 64, "GE-Touchscreen-Validierung. Bound: %d", bound);

	/* open touchscreen */
	ts = tsutil_open(tsdevice, tsconffile, tsplugindir, calfile);
	if (!ts) {
		cmd_err_printf("tsutil_open: %s\n", strerror(errno));
		ret = -1;
		goto __ret;
	}

	/* clear screen */
	disp_fillrect(0, 0, fb_xres, fb_yres, 0);

	/* output message */
	disp_put_string_center (fb_xres / 2, fb_yres / 4, buff, 1);

	disp_put_string_center (fb_xres / 2, fb_yres / 4 + 20,
				"Zum Validieren der Kalibrierung Kreuze betätigen", 2);

	/* reset cross-display */
	ts_calibrate_last_x = -1;
	ts_calibrate_last_y = -1;

	ret = validate_sample (ts, CROSS_BOUND_DISTANCE, CROSS_BOUND_DISTANCE, "Top left", bound);
	if (ret == -1)
		goto __ret_close;
	if (ret) {
		cmd_printf("Validation failed.\n");
		goto __ret_close;
	}

	ret = validate_sample (ts, fb_xres - CROSS_BOUND_DISTANCE, CROSS_BOUND_DISTANCE, "Top right", bound);
	if (ret == -1)
		goto __ret_close;
	if (ret) {
		cmd_printf("Validation failed.\n");
		goto __ret_close;
	}

	ret = validate_sample (ts, fb_xres - CROSS_BOUND_DISTANCE, fb_yres - CROSS_BOUND_DISTANCE, "Bot right", bound);
	if (ret == -1)
		goto __ret_close;
	if (ret) {
		cmd_printf("Validation failed.\n");
		goto __ret_close;
	}

	ret = validate_sample (ts, CROSS_BOUND_DISTANCE, fb_yres - CROSS_BOUND_DISTANCE, "Bot left", bound);
	if (ret == -1)
		goto __ret_close;
	if (ret) {
		cmd_printf("Validation failed.\n");
		goto __ret_close;
	}

	/* close touchscreen */
	tsutil_close(ts);
	ret = 0;
	goto __ret;

__ret_close:
	tsutil_close(ts);
__ret:
	/* clear screen */
	disp_fillrect(0, 0, fb_xres, fb_yres, 0);
	return ret;
}

int ts_validate(int bound, char *tsdevice, char *tsconffile, char *tsplugindir, char *calfile)
{
	int ret;
	unsigned int i;
	char buff[64];

	/* prepare display message */
	snprintf(buff, 64, "GE-Touchscreen-Validierung. Bound: %d", bound);

	/* init colors */
	for (i = 0; i < NR_COLORS; i++)
		disp_setcolor (i, palette [i]);

	/* validate */
	ret = ts_validate_raw(bound, tsdevice, tsconffile, tsplugindir, calfile);

	/* clear screen */
	disp_fillrect(0, 0, fb_xres, fb_yres, 0);

	/* output message */
	disp_put_string_center (fb_xres / 2, fb_yres / 4, buff, 1);

	if (ret == 0) {
		cmd_printf("Validation done!\n");
		disp_put_string_center (fb_xres / 2, fb_yres / 4 + 20,
					"Validierung gültig!", 5);
	} else if (ret == 1) {
		cmd_printf("Validation invalid!\n");
		disp_put_string_center (fb_xres / 2, fb_yres / 4 + 20,
					"Validierung ungültig!", 4);
	} else {
		cmd_printf("Validation failed!\n");
		disp_put_string_center (fb_xres / 2, fb_yres / 4 + 20,
					"Fehler beim Validieren!", 4);
	}

	return ret;
}

int ts_calibrate(int bound, char *tsdevice, char *tsconffile, char *tsplugindir, char *calfile, char *calfile_tmp)
{
	int ret;
	struct tsdev *ts;
	calibration cal;
	unsigned int i;
	char buff[64];

	/* init colors */
	for (i = 0; i < NR_COLORS; i++)
		disp_setcolor (i, palette [i]);

	/* prepare display message */
	snprintf(buff, 64, "GE-Touchscreen-Kalibrierung");

	/* open touchscreen for calibration */
	ts = tsutil_open(tsdevice, tsconffile, tsplugindir, calfile_tmp);
	if (!ts) {
		cmd_err_printf("tsutil_open: %s\n", strerror(errno));
		ret = -1;
		goto __ret;
	}

	/* START CALIBRATION */

	/* clear screen */
	disp_fillrect(0, 0, fb_xres, fb_yres, 0);

	/* output message */
	disp_put_string_center (fb_xres / 2, fb_yres / 4, buff, 1);

	disp_put_string_center (fb_xres / 2, fb_yres / 4 + 20,
				"Zum Kalibrieren Kreuze betätigen", 2);

	cmd_printf("fb_xres = %d, fb_yres = %d\n", fb_xres, fb_yres);

	/* reset cross-display */
	ts_calibrate_last_x = -1;
	ts_calibrate_last_y = -1;

// Read a touchscreen event to clear the buffer
	//getxy_raw(ts, 0, 0);

	ret = get_sample (ts, &cal, 0, CROSS_BOUND_DISTANCE, CROSS_BOUND_DISTANCE, "Top left");
	if (ret == -1)
		goto __ret_close;

	ret = get_sample (ts, &cal, 1, fb_xres - CROSS_BOUND_DISTANCE, CROSS_BOUND_DISTANCE, "Top right");
	if (ret == -1)
		goto __ret_close;

	ret = get_sample (ts, &cal, 2, fb_xres - CROSS_BOUND_DISTANCE, fb_yres - CROSS_BOUND_DISTANCE, "Bot right");
	if (ret == -1)
		goto __ret_close;

	ret = get_sample (ts, &cal, 3, CROSS_BOUND_DISTANCE, fb_yres - CROSS_BOUND_DISTANCE, "Bot left");
	if (ret == -1)
		goto __ret_close;

	ret = get_sample (ts, &cal, 4, fb_xres / 2,  fb_yres / 2,  "Center");
	if (ret == -1)
		goto __ret_close;

	/* close touchscreen */
	tsutil_close(ts);

	/* calibrate */
	if (perform_calibration (&cal) == 0) {
		/* save & use temporary calibration */
		ret = ts_save(calfile_tmp, cal);
		if (ret)
			goto __ret;
	} else {
		cmd_printf("Calibration failed.\n");
		ret = 1;
		goto __ret;
	}

	/* validate */
	ret = ts_validate_raw(bound, tsdevice, tsconffile, tsplugindir, calfile_tmp);
	if (ret)
		goto __ret;

	/* save & use system calibration */
	ret = ts_save(calfile, cal);
	if (ret)
		goto __ret;

	goto __ret;

__ret_close:
	tsutil_close(ts);
__ret:
	/* clear screen */
	disp_fillrect(0, 0, fb_xres, fb_yres, 0);

	/* output message */
	disp_put_string_center (fb_xres / 2, fb_yres / 4, buff, 1);

	if (ret == 0) {
		cmd_printf("Calibration done!\n");
		disp_put_string_center (fb_xres / 2, fb_yres / 4 + 20,
					"Kalibrierung gültig!", 5);
	} else if (ret == 1) {
		cmd_printf("Calibration invalid!\n");
		disp_put_string_center (fb_xres / 2, fb_yres / 4 + 20,
					"Kalibrierung ungültig!", 4);
	} else {
		cmd_printf("Calibration failed!\n");
		disp_put_string_center (fb_xres / 2, fb_yres / 4 + 20,
					"Fehler beim Kalibrieren!", 4);
	}

	return ret;
}

/*
 * display a calibration and validation test-picture with crosses
 * parameters:
 * returns: -0 .. error; 0 .. ok
 */
int ts_calibrate_test_picture(void)
{
	int i;

	/* init colors */
	for (i = 0; i < NR_COLORS; i++)
		disp_setcolor (i, palette [i]);
	/* clear */
	disp_clear(0);
	/* msg */
	disp_put_string_center (fb_xres / 2, fb_yres / 4,
				"GE-Touchscreen-Kalibrierung - Testbild", 1);
	/* display crosses */
	disp_put_cross (CROSS_BOUND_DISTANCE, CROSS_BOUND_DISTANCE, 2);
	disp_put_cross (fb_xres - CROSS_BOUND_DISTANCE, CROSS_BOUND_DISTANCE, 2);
	disp_put_cross (fb_xres - CROSS_BOUND_DISTANCE, fb_yres - CROSS_BOUND_DISTANCE, 2);
	disp_put_cross (CROSS_BOUND_DISTANCE, fb_yres - CROSS_BOUND_DISTANCE, 2);
	disp_put_cross (fb_xres / 2, fb_yres / 2, 2);
	/* ok */
	return 0;
}
