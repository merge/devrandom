/*
 *  tslib/src/ts_test.c
 *
 *  Copyright (C) 2001 Russell King.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 * $Id: ts_test.c,v 1.6 2004/10/19 22:01:27 dlowder Exp $
 *
 * Basic test program for touchscreen library.
 */

/*
 * Purpose of this file:
 * Helper function for display-test-module. This file contains a function to
 * test a GE-touchscreen. The test provides three buttons.
 * Drag -> Drag a cross-hair by touching the display
 * Draw -> Draw lines by touching the display
 * Stop -> Stop the test
 * During a test a timestamp and the current touch-coordinates are printed on stdout.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <errno.h>

#include <cmd_misc.h>
#include <fbutils.h>
#include"cmd_fbutils.h"
#include <tsutils.h>
#include <display_touch.h>
#include <button.h>

static int palette [] = {
	0x000000, 0xffe080, 0xffffff, 0xe0c0a0, 0x304050, 0x80b8c0
};
#define NR_COLORS (sizeof (palette) / sizeof (palette [0]))

#define NR_BUTTONS 3
struct button ts_test_buttons [NR_BUTTONS];

static void ts_test_refresh_screen (int mode)
{
	int i;

	disp_fillrect (0, 0, fb_xres - 1, fb_yres - 1, 0);

	switch (mode) {
	case 0:
		disp_put_string_center (fb_xres / 2, fb_yres / 4 + 20, "Touch screen to move crosshair", 2);
		break;
	case 1:
		disp_put_string_center (fb_xres / 2, fb_yres / 4 + 20, "Touch screen to draw lines", 2);
		break;
	case 2:
		/* simply clear screen */
		return;
		break;
	}
	disp_put_string_center (fb_xres / 2, fb_yres / 4,   "TSLIB test program", 1);

	for (i = 0; i < NR_BUTTONS; i++)
		button_draw (&ts_test_buttons [i]);
}

int ts_test(char *tsdevice, char *tsconffile, char *tsplugindir, char *calfile)
{
	struct tsdev *ts;
	int x, y;
	unsigned int i;
	unsigned int mode = 0;

	ts = tsutil_open(tsdevice, tsconffile, tsplugindir, calfile);
	if (!ts) {
		cmd_err_printf("%s: %s\n", tsdevice, strerror(errno));
		return -1;
	}

	x = fb_xres / 2;
	y = fb_yres / 2;

	for (i = 0; i < NR_COLORS; i++)
		disp_setcolor (i, palette [i]);
	button_init();

	/* Initialize buttons */
	memset (ts_test_buttons, 0, sizeof (ts_test_buttons));
	ts_test_buttons [0].w = ts_test_buttons [1].w = ts_test_buttons [2].w = fb_xres / 4;
	ts_test_buttons [0].h = ts_test_buttons [1].h = ts_test_buttons [2].h = 20;
	ts_test_buttons [0].x = fb_xres / 4 - ts_test_buttons [0].w / 2;
	ts_test_buttons [1].x = (2 * fb_xres) / 4 - ts_test_buttons [0].w / 2;
	ts_test_buttons [2].x = (3 * fb_xres) / 4 - ts_test_buttons [2].w / 2;
	ts_test_buttons [0].y = ts_test_buttons [1].y = ts_test_buttons [2].y = 10;
	ts_test_buttons [0].text = "Drag";
	ts_test_buttons [1].text = "Draw";
	ts_test_buttons [2].text = "Stop";

	ts_test_refresh_screen (mode);

	while (mode != 2) {
		struct ts_sample samp;
		int ret;

		/* Show the cross */
		if ((mode & 15) != 1)
			disp_put_cross(x, y, 2 | XORMODE);

		ret = tsutil_read(ts, &samp);

		/* Hide it */
		if ((mode & 15) != 1)
			disp_put_cross(x, y, 2 | XORMODE);

		if (ret < 0) {
			cmd_err_printf("tsutil_read: %s\n", strerror(errno));
			return -1;
		}

		if (ret != 1)
			continue;

		for (i = 0; i < NR_BUTTONS; i++)
			if (button_handle (&ts_test_buttons [i], &samp))
				switch (i) {
				case 0:
					mode = 0;
					ts_test_refresh_screen (mode);
					break;
				case 1:
					mode = 1;
					ts_test_refresh_screen (mode);
					break;
				case 2:
					mode = 2;
					ts_test_refresh_screen (mode);
					break;
				}

		cmd_printf("%ld.%06ld: %6d %6d %6d\n", samp.tv.tv_sec, samp.tv.tv_usec,
			   samp.x, samp.y, samp.pressure);

		if (samp.pressure > 0) {
			if (mode == 0x80000001)
				disp_line (x, y, samp.x, samp.y, 2);
			x = samp.x;
			y = samp.y;
			mode |= 0x80000000;
		} else
			mode &= ~0x80000000;
	}

	ts_close(ts);

	return 0;
}
