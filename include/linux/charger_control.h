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

#ifndef _CHARGER_CONTROL_H
#define _CHARGER_CONTROL_H

#define CHRGCTRL_DEVICE_NAME		"charger-control"
#define CHRGCTRL_VERSION		"0.0.0"
#define CHRGCTRL_CHARGE_LIMIT		100

int chrgctrl_get_chargelimit(void);

#endif
