/*
 * Purpose of this file:
 * Helper functions for display-test-module. This file contains functions to
 * calibrate and validate a GE-touchscreen.
 */
#ifndef __TS_CALIBRATE_H__
#define __TS_CALIBRATE_H__

/*
 * do validation
 * parameters:
 *  bound .. boundary for validation
 * 	tsdevice .. touchscreen-device-name
 * 	tsconffile .. path to ts-config-file
 * 	tsplugindir .. path to ts-plugin-dir
 * 	calfile .. calfile
 * returns: 0 .. ok; 1 .. calibration invalid; -1 .. error
 */
int ts_validate(int bound, char *tsdevice, char *tsconffile, char *tsplugindir, char *calfile);

/*
 * do calibration and validation
 * parameters:
 *  bound .. boundary for validation
 * 	tsdevice .. touchscreen-device-name
 * 	tsconffile .. path to ts-config-file
 * 	tsplugindir .. path to ts-plugin-dir
 * 	calfile .. real calfile
 *  calfile_tmp .. temporary calfile
 * returns: 0 .. ok; 1 .. calibration invalid; -1 .. error
 */
int ts_calibrate(int bound, char *tsdevice, char *tsconffile, char *tsplugindir, char *calfile, char *calfile_tmp);

/*
 * display a calibration and validation test-picture with crosses
 * parameters:
 * returns: -0 .. error; 0 .. ok
 */
int ts_calibrate_test_picture(void);

#endif /* __TS_CALIBRATE_H__ */
