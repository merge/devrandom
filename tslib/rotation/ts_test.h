/*
 * Purpose of this file:
 * Helper function for display-test-module. This file contains a function to
 * test a GE-touchscreen. The test provides three buttons.
 * Drag -> Drag a cross-hair by touching the display
 * Draw -> Draw lines by touching the display
 * Stop -> Stop the test
 * During a test a timestamp and the current touch-coordinates are printed on stdout.
 */
#ifndef __TS_TEST_H__
#define __TS_TEST_H__

/*
 * test touchscreen
 * parameters:
 * 	tsdevice .. touchscreen-device-name
 * 	tsconffile .. path to ts-config-file
 * 	tsplugindir .. path to ts-plugin-dir
 * 	calfile .. calfile
 * returns: 0 .. ok; -1 .. error
 */
int ts_test(char *tsdevice, char *tsconffile, char *tsplugindir, char *calfile);


#endif	/* __TS_TEST_H__ */
