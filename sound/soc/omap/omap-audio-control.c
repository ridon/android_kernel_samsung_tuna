/*
 * OMAP Audio Control
 *
 * This driver is meant to provide a universal method of tweaking
 * audio output on multiple OMAP (OMAP4, in particular) devices.
 *
 * Author: Kyle Repinski <repinski23@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 */

#include <linux/init.h>
#include <linux/device.h>
#include <linux/miscdevice.h>

#include "omap-audio-control.h"

/* Not ready yet. */
/* Set up EQ, stock value as 'nothing' */
/*
struct abe_equ_t omapaudctrl_eq = {
	.equ_length = 25;
	/* Gain set to 0dB by default. *//*
	.coef.type2.gain = { 0x00040000, 0x00040000, 0x00040000, 0x00040000,
		0x00040000, 0x00040000, 0x00040000, 0x00040000, 0x00040000,
		0x00040000, 0x00040000, 0x00040000, 0x00040000 };
	/* Default center frequencies are approx.:
	 * 31, 62, 125, 250, 500, 1000, 2000,
	 * 3000, 4000, 6000, 8000, 12000, 16000 *//*
	.coef.type2.freq = {
	};
};*/


static int omapaudctrl_version(struct device *dev, struct device_attribute *attr, char *buf) {
	return sprintf(buf, "%s\n", OMAPAUDCTRL_VERSION);
}

static DEVICE_ATTR(version, S_IRUGO, omapaudctrl_version, NULL);

static struct attribute *omapaudctrl_attributes[] = {
	&dev_attr_version.attr,
	NULL
};

static struct attribute_group omapaudctrl_group = {
	.attrs = omapaudctrl_attributes,
};

static struct miscdevice omapaudctrl_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "omap-audio-control",
};

static int __init omapaudctrl_init(void) {
	pr_info("%s %s: firing up.", omapaudctrl_device.name, OMAPAUDCTRL_VERSION);

	if (misc_register(&omapaudctrl_device)) {
		pr_err("%s %s: misc_register failure.", omapaudctrl_device.name, OMAPAUDCTRL_VERSION);
		return 1;
	}

	if (sysfs_create_group(&omapaudctrl_device.this_device->kobj, &omapaudctrl_group) < 0) {
		pr_err("%s %s: sysfs_create_group failure.", omapaudctrl_device.name, OMAPAUDCTRL_VERSION);
		return 1;
	}

	return 0;
}

device_initcall(omapaudctrl_init);
