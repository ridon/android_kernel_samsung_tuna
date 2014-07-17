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

#ifndef __OMAPAUDCTRL_H__
#define __OMAPAUDCTRL_H__

#include "abe/abe_main.h"

#define OMAPAUDCTRL_VERSION			"0.0.0"

/* This is pretty defensive, but it *is* possible to select multiple codecs.
 * That's not gonna fly with OMAP Audio Control. Also, if there isn't a
 * supported thing selected at all, that should be known so OMAP Audio
 * Control can just only stick to the TI ABE things.
 */
#if defined(CONFIG_SND_SOC_WM8962) && !defined(CONFIG_SND_SOC_TWL6040)
#define OMAPAUDCTRL_CODEC_WM8962
#elif defined(CONFIG_SND_SOC_TWL6040) && !defined(CONFIG_SND_SOC_WM8962)
#define OMAPAUDCTRL_CODEC_TWL6040
#else
#define OMAPAUDCTRL_CODEC_UNSUPPORTED
#endif

/* Not ready yet. */
/* extern struct abe_equ_t omapaudctrl_eq; */

/* Don't unnecessarily add anything that's codec-specific */
#if !defined(OMAPAUDCTRL_CODEC_UNSUPPORTED)


#if defined(OMAPAUDCTRL_CODEC_WM8962)

#define OMAPAUDCTRL_CODEC_OVERSAMPLING_SUPPORT

#endif /* OMAPAUDCTRL_CODEC_WM8962 */


#if defined(OMAPAUDCTRL_CODEC_TWL6040)

#define OMAPAUDCTRL_CODEC_POWER_SUPPORT

#endif /* OMAPAUDCTRL_CODEC_TWL6040 */


#endif /* !(OMAPAUDCTRL_CODEC_UNSUPPORTED) */

#endif /* !(__OMAPAUDCTRL_H__) */
