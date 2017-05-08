/*
 * Purpose of this file:
 * Low level functions for touch-screen. Uses tslib to get touch-information.
 */
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<linux/ioctl.h>
#include<linux/input.h>
#include<fbutils.h>
#include"cmd_fbutils.h"
#include<tsutils.h>

#define TS_BUFFER_MAX 32768

int ts_xmin = 0;
int ts_xmax = 0;
int ts_ymin = 0;
int ts_ymax = 0;

struct tsdev *tsutil_open(char *tsdevice, char *tsconffile, char *tsplugindir, char *calfile)
{
	struct tsdev *ts;
	struct input_absinfo absinfo;

	/* set environment */
	setenv("TSLIB_CONFFILE", tsconffile, 1);
	setenv("TSLIB_PLUGINDIR", tsplugindir, 1);
	setenv("TSLIB_CALIBFILE", calfile, 1);

	ts = ts_open (tsdevice, 0);
	if (!ts) {
		return NULL;
	}

	if (ts_config(ts)) {
		ts_close(ts);
		return NULL;
	}

	/*
	 * this is only an information for tslib
	 * tslib itself performes no rotation!
	 */
	if (ts_option(ts, TS_SCREEN_ROT, fb_get_rotation())) {
		ts_close(ts);
		return NULL;
	}

	if ( ioctl(ts_fd(ts), EVIOCGABS(ABS_X), &absinfo) < 0 ) {
		ts_close(ts);
		return NULL;
	}
	ts_xmin = absinfo.minimum;
	ts_xmax = absinfo.maximum;
	if ( ioctl(ts_fd(ts), EVIOCGABS(ABS_Y), &absinfo) < 0 ) {
		ts_close(ts);
		return NULL;
	}
	ts_ymin = absinfo.minimum;
	ts_ymax = absinfo.maximum;

	return ts;
}

void tsutil_close (struct tsdev *ts)
{
	ts_close(ts);
	unsetenv("TS_CONFFILE");
	unsetenv("TS_PLUGINDIR");
	unsetenv("TSLIB_CALIBFILE");
}


void tsutil_flush (struct tsdev *ts)
{
	/* Read all unread touchscreen data,
	 * so that we are sure that the next data that we read
	 * have been input after this flushing.
	 */
	static char buffer [TS_BUFFER_MAX];
	read (ts_fd (ts), buffer, TS_BUFFER_MAX);
}

/*
 * read from touch(tslib) with calibration and rotation
 */
int tsutil_read(struct tsdev *ts, struct ts_sample *samp)
{
	int ret, tmp;

	if (disp_openfb()) {
		disp_closefb();
		return -1;
	}

	ret = ts_read(ts, samp, 1);
	if (ret < 0)
		return ret;

	/* do rotation */
	switch (fb_rotation) {
	default:
	case 0:
		/* nothing to do */
		break;
	case 1:
		tmp = samp->y;
		samp->y = fb_yres - samp->x - 1;
		samp->x = tmp;
		break;
	case 2:
		samp->x = fb_xres - samp->x - 1;
		samp->y = fb_yres - samp->y - 1;
		break;
	case 3:
		tmp = fb_xres - samp->y - 1;
		samp->y = samp->x;
		samp->x = tmp;
		break;
	}

	return ret;
}

/*
 * read from touch(tslib) with calibration
 * TODO: using with display-rotation is not recommended yet
 */
int tsutil_read_raw(struct tsdev *ts, struct ts_sample *samp)
{
	int ret, tmp;

	if (disp_openfb()) {
		disp_closefb();
		return -1;
	}

	ret = ts_read_raw(ts, samp, 1);
	if (ret < 0)
		return ret;

	/* do rotation
	 * using with display-rotation is not recommended yet
	 */
	switch (fb_rotation) {
	default:
	case 0:
		/* nothing to do */
		break;
	case 1:
		tmp = samp->y;
		samp->y = ts_xmax - samp->x;
		samp->x = tmp;
		break;
	case 2:
		/* ok */
		samp->x = ts_xmax - samp->x;
		samp->y = ts_ymax - samp->y;
		break;
	case 3:
		tmp = ts_ymax - samp->y;
		samp->y = samp->x;
		samp->x = tmp;
		break;
	}

	return ret;
}

