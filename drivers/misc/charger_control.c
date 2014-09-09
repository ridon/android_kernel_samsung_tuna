/*
 * Charger Control
 *
 * This driver is meant to provide advanced, unified control
 * of the battery and charger of tuna (or similar) devices.
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
#include <linux/charger_control.h>

static int chrgctrl_chargelimit = CHRGCTRL_CHARGE_LIMIT;

static ssize_t chrgctrl_version(struct device *dev, struct device_attribute *attr, char *buf) {
	return sprintf(buf, "%s\n", CHRGCTRL_VERSION);
}

static ssize_t chrgctrl_chargelimit_read(struct device *dev, struct device_attribute *attr, char *buf) {
	return sprintf(buf, "%u\n", chrgctrl_chargelimit);
}

static ssize_t chrgctrl_chargelimit_write(struct device *dev, struct device_attribute *attr, const char *buf, size_t count) {
	unsigned int data;

	if (sscanf(buf, "%u\n", &data) == 1) {
		if (data >= 0 && data <= CHRGCTRL_CHARGE_LIMIT) {
			chrgctrl_chargelimit = data;
			pr_info("%s: %s: limit set to: %u\n", CHRGCTRL_DEVICE_NAME, __FUNCTION__, chrgctrl_chargelimit);
		} else {
			pr_info("%s: %s: input out of range: %u\n", CHRGCTRL_DEVICE_NAME, __FUNCTION__, data);
		}
	} else {
		pr_info("%s: %s: invalid input!\n", CHRGCTRL_DEVICE_NAME, __FUNCTION__);
	}

	return count;
}

static DEVICE_ATTR(version, S_IRUGO, chrgctrl_version, NULL);
static DEVICE_ATTR(charge_limit, S_IRUGO | S_IWUGO, chrgctrl_chargelimit_read, chrgctrl_chargelimit_write);

static struct attribute *chrgctrl_attributes[] = {
	&dev_attr_version.attr,
	&dev_attr_charge_limit.attr,
	NULL
};

static struct attribute_group chrgctrl_group = {
	.attrs = chrgctrl_attributes,
};

static struct miscdevice chrgctrl_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = CHRGCTRL_DEVICE_NAME,
};

int chrgctrl_get_chargelimit(void) {
    return chrgctrl_chargelimit;
}
EXPORT_SYMBOL(chrgctrl_get_chargelimit);

static int __init chrgctrl_init(void) {
	pr_info("%s %s: firing up.", chrgctrl_device.name, CHRGCTRL_VERSION);

	if (misc_register(&chrgctrl_device)) {
		pr_err("%s %s: misc_register failure.", chrgctrl_device.name, CHRGCTRL_VERSION);
		return 1;
	}

	if (sysfs_create_group(&chrgctrl_device.this_device->kobj, &chrgctrl_group) < 0) {
		pr_err("%s %s: sysfs_create_group failure.", chrgctrl_device.name, CHRGCTRL_VERSION);
		return 1;
	}

	return 0;
}

device_initcall(chrgctrl_init);
