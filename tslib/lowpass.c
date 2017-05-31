/*
 * This file is placed under the LGPL.  Please see the file
 * COPYING for more details.
 * 
 * Very stupid lowpass dejittering filter
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "tslib.h"
#include "tslib-filter.h"

struct tslib_lowpass {
	struct tslib_module_info module;
        struct ts_sample last;
        struct ts_sample ideal;
	float factor;
	unsigned int flags;
	unsigned char threshold;
#define VAR_PENUP		0x00000001
};



static int lowpass_read(struct tslib_module_info *info, struct ts_sample *samp, int nr)
{
	struct tslib_lowpass *var = (struct tslib_lowpass *)info;
	struct ts_sample current;
	int count = 0;
	int delta;

	while (count < nr) {
		if (info->next->ops->read(info->next, &current, 1) < 1)
			return count;

		if (current.pressure == 0) {
			var->flags |= VAR_PENUP;
			samp [count++] = current;
		} else if (var->flags & VAR_PENUP) {
			var->flags &= ~VAR_PENUP;
			var->last = current;
			samp [count++] = current;
		} else {
			var->ideal = current;

			var->ideal.x = var->last.x;
			delta = current.x - var->last.x;
			if (delta <= var->threshold && 
					delta >= -var->threshold)
				delta = 0;
			delta *= var->factor;
			var->ideal.x += delta;
			
			var->ideal.y = var->last.y;
			delta = current.y - var->last.y;
			if (delta <= var->threshold && 
					delta >= -var->threshold)
				delta = 0;
			delta *= var->factor;
			var->ideal.y += delta;

			var->last = var->ideal;
			samp [count++] = var->ideal;
		}
	}
	return count;
}

static int lowpass_fini(struct tslib_module_info *info)
{
	free(info);
        return 0;
}

static const struct tslib_ops lowpass_ops =
{
	.read	= lowpass_read,
	.fini	= lowpass_fini,
};

static int lowpass_factor(struct tslib_module_info *inf, char *str, void *data)
{
	struct tslib_lowpass *var = (struct tslib_lowpass *)inf;
	long double v;
	int err = errno;

	v = strtod(str, NULL);

	if (v > 1 || v < 0)
		return -1;

	errno = err;
	switch ((int)data) {
	case 1:
		var->factor = v;
		break;

	default:
		return -1;
	}
	return 0;
}

static int lowpass_threshold(struct tslib_module_info *inf, char *str, 
		void *data)
{
	struct tslib_lowpass *var = (struct tslib_lowpass *)inf;
	long result;
	int err = errno;

	result = strtol(str,NULL,0);
	if (errno == ERANGE)
	       return -1;

	errno = err;

	switch ((int)data) {
	case 1:
		printf("threshold is now %d\n",result);
		var->threshold = result;
		break;
	default:
		return -1;
	}
	return 0;
}


static const struct tslib_vars lowpass_vars[] =
{
	{ "factor",	(void *)1, lowpass_factor },
	{ "threshold",  (void*) 1, lowpass_threshold },
};

#define NR_VARS (sizeof(lowpass_vars) / sizeof(lowpass_vars[0]))

TSAPI struct tslib_module_info *mod_init(struct tsdev *dev, const char *params)
{
	struct tslib_lowpass *var;

	var = malloc(sizeof(struct tslib_lowpass));
	if (var == NULL)
		return NULL;

	memset(var, 0, sizeof *var);
	var->module.ops = &lowpass_ops;

	var->factor = 0.4;
	var->threshold = 2;
	var->flags = VAR_PENUP;

	if (tslib_parse_vars(&var->module, lowpass_vars, NR_VARS, params)) {
		free(var);
		return NULL;
	}


	return &var->module;
}
