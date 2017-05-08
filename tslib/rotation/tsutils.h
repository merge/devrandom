/*
 * Purpose of this file:
 * Low level functions for touch-screen. Uses tslib to get touch-information.
 */
#ifndef __TSUTILS_H__
#define __TSUTILS_H__

#include <tslib.h>

#define CALFILE		"/data/etc/ts_calib.save"
#define CALFILE_TMP	"/tmp/ts_calib_tmp"


struct tsdev *tsutil_open(char *tsdevice, char *tsconffile, char *tsplugindir, char *calfile);

void tsutil_close (struct tsdev *ts);

void tsutil_flush (struct tsdev *ts);

/*
 * read from touch(tslib) with calibration and rotation
 */
int tsutil_read(struct tsdev *ts, struct ts_sample *samp);

/*
 * read from touch(tslib) with calibration
 * TODO: using with display-rotation is not recommended yet
 */
int tsutil_read_raw(struct tsdev *ts, struct ts_sample *samp);

#endif /* __TSUTILS_H__ */
