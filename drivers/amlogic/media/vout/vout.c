/*
 * drivers/amlogic/media/vout/vout.c
 *
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#include <common.h>
#include <asm/arch/io.h>
#include <asm/arch/secure_apb.h>
#include <amlogic/cpu_id.h>
#include <amlogic/media/vpp/vpp.h>
#include <amlogic/media/vout/aml_vmode.h>
#include <amlogic/media/vout/aml_vout.h>
#ifdef CONFIG_AML_LCD
#include <amlogic/media/vout/lcd/aml_lcd.h>
#endif
#include "vout.h"

#define VOUT_LOG_DBG 0
#define VOUT_LOG_TAG "[VOUT]"
#define vout_log(fmt, ...) printf(VOUT_LOG_TAG fmt, ##__VA_ARGS__)
#define vout_logl() \
	do { \
		if (VOUT_LOG_DBG > 0) \
			vout_log("%s:%d\n", __func__, __LINE__); \
	} while (0)

static int g_vmode = -1;
static struct vout_conf_s *vout_conf;
static int vout_conf_check(void);
#include "vout_reg.h"

static const struct vout_set_s vout_sets[] = {
	{ /* VMODE_480I */
		.name              = "480i",
		.mode              = VMODE_480I,
		.width             = 720,
		.height            = 480,
		.field_height      = 240,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCI,
	},
	{ /* VMODE_480CVBS*/
		.name              = "480cvbs",
		.mode              = VMODE_480CVBS,
		.width             = 720,
		.height            = 480,
		.field_height      = 240,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCI,
	},
	{ /* VMODE_480P */
		.name              = "480p",
		.mode              = VMODE_480P,
		.width             = 720,
		.height            = 480,
		.field_height      = 480,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_576I */
		.name              = "576i",
		.mode              = VMODE_576I,
		.width             = 720,
		.height            = 576,
		.field_height      = 288,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCI,
	},
	{ /* VMODE_576I */
		.name              = "576cvbs",
		.mode              = VMODE_576CVBS,
		.width             = 720,
		.height            = 576,
		.field_height      = 288,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCI,
	},
	{ /* VMODE_576P */
		.name              = "576p",
		.mode              = VMODE_576P,
		.width             = 720,
		.height            = 576,
		.field_height      = 576,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_720P */
		.name              = "720p",
		.mode              = VMODE_720P,
		.width             = 1280,
		.height            = 720,
		.field_height      = 720,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_768P */
		.name              = "768p",
		.mode              = VMODE_768P,
		.width             = 1366,
		.height            = 768,
		.field_height      = 768,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1080I */
		.name              = "1080i",
		.mode              = VMODE_1080I,
		.width             = 1920,
		.height            = 1080,
		.field_height      = 540,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1080P */
		.name              = "1080p",
		.mode              = VMODE_1080P,
		.width             = 1920,
		.height            = 1080,
		.field_height      = 1080,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_4K2K_60HZ */
		.name              = "2160p",
		.mode              = VMODE_4K2K_60HZ,
		.width             = 3840,
		.height            = 2160,
		.field_height      = 2160,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_4K2K_SMPTE */
		.name              = "smpte",
		.mode              = VMODE_4K2K_SMPTE,
		.width             = 4096,
		.height            = 2160,
		.field_height      = 2160,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_vga */
		.name              = "vga",
		.mode              = VMODE_VGA,
		.width             = 640,
		.height            = 480,
		.field_height      = 480,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_SVGA */
		.name              = "svga",
		.mode              = VMODE_SVGA,
		.width             = 800,
		.height            = 600,
		.field_height      = 600,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_XGA */
		.name              = "xga",
		.mode              = VMODE_XGA,
		.width             = 1024,
		.height            = 768,
		.field_height      = 768,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_sxga */
		.name              = "sxga",
		.mode              = VMODE_SXGA,
		.width             = 1280,
		.height            = 1024,
		.field_height      = 1024,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_wsxga */
		.name              = "wsxga",
		.mode              = VMODE_WSXGA,
		.width             = 1440,
		.height            = 900,
		.field_height      = 900,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_fhdvga */
		.name              = "fhdvga",
		.mode              = VMODE_FHDVGA,
		.width             = 1920,
		.height            = 1080,
		.field_height      = 1080,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_LCD */
		.name              = "panel",
		.mode              = VMODE_LCD,
		.width             = 1920,
		.height            = 1080,
		.field_height      = 1080,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_640x480p60hz */
		.name              = "640x480p60hz",
		.mode              = VMODE_640x480p60hz,
		.width             = 640,
		.height            = 480,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_800x480p60hz */
		.name              = "800x480p60hz",
		.mode              = VMODE_800x480p60hz,
		.width             = 800,
		.height            = 480,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_800x600p60hz */
		.name              = "800x600p60hz",
		.mode              = VMODE_800x600p60hz,
		.width             = 800,
		.height            = 600,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_852x480p60hz */
		.name              = "852x480p60hz",
		.mode              = VMODE_852x480p60hz,
		.width             = 852,
		.height            = 480,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_854x480p60hz */
		.name              = "854x480p60hz",
		.mode              = VMODE_854x480p60hz,
		.width             = 854,
		.height            = 480,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1024x768p60hz */
		.name              = "1024x768p60hz",
		.mode              = VMODE_1024x768p60hz,
		.width             = 1024,
		.height            = 768,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1152x864p75hz */
		.name              = "1152x864p75hz",
		.mode              = VMODE_1152x864p75hz,
		.width             = 1152,
		.height            = 864,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1280x600p60hz */
		.name              = "1280x600p60hz",
		.mode              = VMODE_1280x600p60hz,
		.width             = 1280,
		.height            = 600,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1280x768p60hz */
		.name              = "1280x768p60hz",
		.mode              = VMODE_1280x768p60hz,
		.width             = 1280,
		.height            = 768,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1280x800p60hz */
		.name              = "1280x800p60hz",
		.mode              = VMODE_1280x800p60hz,
		.width             = 1280,
		.height            = 800,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1280x960p60hz */
		.name              = "1280x960p60hz",
		.mode              = VMODE_1280x960p60hz,
		.width             = 1280,
		.height            = 960,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1280x1024p60hz */
		.name              = "1280x1024p60hz",
		.mode              = VMODE_1280x1024p60hz,
		.width             = 1280,
		.height            = 1024,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1360x768p60hz */
		.name              = "1360x768p60hz",
		.mode              = VMODE_1360x768p60hz,
		.width             = 1360,
		.height            = 768,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1366x768p60hz */
		.name              = "1366x768p60hz",
		.mode              = VMODE_1366x768p60hz,
		.width             = 1366,
		.height            = 768,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1400x1050p60hz */
		.name              = "1400x1050p60hz",
		.mode              = VMODE_1400x1050p60hz,
		.width             = 1400,
		.height            = 1050,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1440x900p60hz */
		.name              = "1440x900p60hz",
		.mode              = VMODE_1440x900p60hz,
		.width             = 1440,
		.height            = 900,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1440x2560p60hz */
		.name              = "1440x2560p60hz",
		.mode              = VMODE_1440x2560p60hz,
		.width             = 1440,
		.height            = 2560,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1440x2560p70hz */
		.name              = "1440x2560p70hz",
		.mode              = VMODE_1440x2560p70hz,
		.width             = 1440,
		.height            = 2560,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1600x900p60hz */
		.name              = "1600x900p60hz",
		.mode              = VMODE_1600x900p60hz,
		.width             = 1600,
		.height            = 900,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1600x1200p60hz */
		.name              = "1600x1200p60hz",
		.mode              = VMODE_1600x1200p60hz,
		.width             = 1600,
		.height            = 1200,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1680x1050p60hz */
		.name              = "1680x1050p60hz",
		.mode              = VMODE_1680x1050p60hz,
		.width             = 1680,
		.height            = 1050,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_1920x1200p60hz */
		.name              = "1920x1200p60hz",
		.mode              = VMODE_1920x1200p60hz,
		.width             = 1920,
		.height            = 1200,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_2160x1200p90hz */
		.name			= "2160x1200p90hz",
		.mode	 		= VMODE_2160x1200p90hz,
		.width	 		= 2160,
		.height 		= 1200,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
	{ /* VMODE_2560x1080p60hz */
		.name              = "2560x1080p60hz",
		.mode              = VMODE_2560x1080p60hz,
		.width             = 2560,
		.height            = 1080,
		.viu_color_fmt     = VPP_CM_YUV,
		.viu_mux           = VIU_MUX_ENCP,
	},
};

static struct vinfo_s vout_info = {
	.width  = 1920,              /* Number of columns (i.e. 160) */
	.height = 1080,               /* Number of rows (i.e. 100) */
	.field_height = 1080,

	.vl_bpix = 24,               /* Bits per pixel */
	.vd_base = NULL,             /* Start of framebuffer memory */
	.vd_console_address = NULL,  /* Start of console buffer	*/
	.console_col = 0,
	.console_row = 0,

	.vd_color_fg = 0xffff,
	.vd_color_bg = 0,
	.cmap = NULL,                /* Pointer to the colormap */
	.priv = NULL,                /* Pointer to driver-specific data */
};

static int vout_conf_check(void)
{
	if (vout_conf)
		return 0;

	vout_probe();
	if (!vout_conf) {
		vout_log("error: %s: no vout_conf\n", __func__);
		return -1;
	}

	return 0;
}

static int vout_find_mode_by_name(const char *name)
{
	int mode = -1;
	int i = 0;

	for (i = 0; i < sizeof(vout_sets) / sizeof(struct vout_set_s); i++) {
		if (strncmp(name, vout_sets[i].name, strlen(vout_sets[i].name)) == 0) {
			mode = vout_sets[i].mode;
			return mode;
		}
	}

	vout_log("mode: %s not found\n", name);
	return -1;
}

static int vout_find_width_by_name(const char* name)
{
	int i = 0;
	ulong width = 0;

	for (i = 0; i < sizeof(vout_sets) / sizeof(struct vout_set_s); i++) {
		if (strncmp(name, vout_sets[i].name, strlen(vout_sets[i].name)) == 0) {
			width = vout_sets[i].width;
			return width;
		}
	}

	return width;
}

static int vout_find_height_by_name(const char* name)
{
	int height = 0;
	int i = 0;

	for (i = 0; i < sizeof(vout_sets) / sizeof(struct vout_set_s); i++) {
		if (strncmp(name, vout_sets[i].name, strlen(vout_sets[i].name)) == 0) {
			height = vout_sets[i].height;
			return height;
		}
	}

	return height;
}

static int vout_find_field_height_by_name(const char* name)
{
	int height = 0;
	int i = 0;

	for (i = 0; i < sizeof(vout_sets) / sizeof(struct vout_set_s); i++) {
		if (strncmp(name, vout_sets[i].name, strlen(vout_sets[i].name)) == 0) {
			height = vout_sets[i].field_height;
			return height;
		}
	}

	return height;
}

static unsigned int vout_env2uint(const char *name, int base)
{
	return (unsigned int)env_get_ulong(name, base, 0);
}

static void vout_vinfo_init(ulong width, ulong height, ulong field_height)
{
	vout_info.width = width;
	vout_info.height = height;
	vout_info.field_height = field_height;
	vout_info.vd_base = (void *)get_fb_addr();
	vout_info.vl_bpix = (unsigned char)vout_env2uint("display_bpp", 10);
	vout_info.vd_color_fg = vout_env2uint("display_color_fg", 0);
	vout_info.vd_color_bg = vout_env2uint("display_color_bg", 0);
}

static void vout_axis_init(ulong w, ulong h)
{
	ulong width = w;
	ulong height = h;

	env_set_ulong("display_width", width);
	env_set_ulong("display_height", height);
}

static void vout_vmode_init(void)
{
	char *outputmode = NULL;
	int vmode = -1;
	ulong width = 0;
	ulong height = 0;
	ulong field_height = 0;
#ifdef CONFIG_AML_LCD
	struct lcd_drv_s *lcd_drv;
#endif

	outputmode = env_get("outputmode");
	vmode = vout_find_mode_by_name(outputmode);
	vout_set_current_vmode(vmode);
	switch (vmode) {
#ifdef CONFIG_AML_LCD
	case VMODE_LCD:
		lcd_drv = lcd_get_driver();
		width = lcd_drv->lcd_config->lcd_basic.h_active;
		height = lcd_drv->lcd_config->lcd_basic.v_active;
		field_height = lcd_drv->lcd_config->lcd_basic.v_active;
		break;
#endif
	default:
		width = vout_find_width_by_name(outputmode);
		height = vout_find_height_by_name(outputmode);
		field_height = vout_find_field_height_by_name(outputmode);
		break;
	}
	vout_axis_init(width, height);

	vout_vinfo_init(width, height, field_height);
}

static int my_atoi(const char *str)
{
	int result = 0;
	int signal = 1;

	if ((*str >= '0' && *str <= '9') || *str == '-' || *str == '+') {
		if (*str == '-' || *str == '+') {
			if (*str == '-')
				signal = -1;
			str++;
		}
	} else
		return 0;

	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ -'0');

	return signal * result;
}

static int getenv_int(char *env, int def)
{
	if (env_get(env) == NULL)
		return def;
	else
		return my_atoi(env_get(env));
}

static int get_window_axis(int *axis)
{
	int ret = 0;
	char *mode = env_get("outputmode");
	int def_x, def_y, def_w, def_h;

	def_x = 0;
	def_y = 0;
	def_w = vout_info.width;
	def_h = vout_info.height;

	/* adjust reproduction ratio */
	if (strncmp(mode, "480i", 4) == 0 || strcmp(mode, "480cvbs") == 0) {
		axis[0] = getenv_int("480i_x", def_x);
		axis[1] = getenv_int("480i_y", def_y);
		axis[2] = getenv_int("480i_w", def_w);
		axis[3] = getenv_int("480i_h", def_h);
	} else if (strncmp(mode, "480p", 4) == 0) {
		axis[0] = getenv_int("480p_x", def_x);
		axis[1] = getenv_int("480p_y", def_y);
		axis[2] = getenv_int("480p_w", def_w);
		axis[3] = getenv_int("480p_h", def_h);
	} else if (strncmp(mode, "576i", 4) == 0 || strcmp(mode, "576cvbs") == 0) {
		axis[0] = getenv_int("576i_x", def_x);
		axis[1] = getenv_int("576i_y", def_y);
		axis[2] = getenv_int("576i_w", def_w);
		axis[3] = getenv_int("576i_h", def_h);
	} else if (strncmp(mode, "576p", 4) == 0) {
		axis[0] = getenv_int("576p_x", def_x);
		axis[1] = getenv_int("576p_y", def_y);
		axis[2] = getenv_int("576p_w", def_w);
		axis[3] = getenv_int("576p_h", def_h);
	} else if (strncmp(mode, "720p", 4) == 0) {
		axis[0] = getenv_int("720p_x", def_x);
		axis[1] = getenv_int("720p_y", def_y);
		axis[2] = getenv_int("720p_w", def_w);
		axis[3] = getenv_int("720p_h", def_h);
	} else if (strncmp(mode, "768p", 4) == 0) {
		axis[0] = getenv_int("768p_x", def_x);
		axis[1] = getenv_int("768p_y", def_y);
		axis[2] = getenv_int("768p_w", def_w);
		axis[3] = getenv_int("768p_h", def_h);
	} else if (strncmp(mode, "1080i", 5) == 0) {
		axis[0] = getenv_int("1080i_x", def_x);
		axis[1] = getenv_int("1080i_y", def_y);
		axis[2] = getenv_int("1080i_w", def_w);
		axis[3] = getenv_int("1080i_h", def_h);
	} else if (strncmp(mode, "1080p", 5) == 0) {
		axis[0] = getenv_int("1080p_x", def_x);
		axis[1] = getenv_int("1080p_y", def_y);
		axis[2] = getenv_int("1080p_w", def_w);
		axis[3] = getenv_int("1080p_h", def_h);
	} else if (strncmp(mode, "2160p", 5) == 0) {
		axis[0] = getenv_int("2160p_x", def_x);
		axis[1] = getenv_int("2160p_y", def_y);
		axis[2] = getenv_int("2160p_w", def_w);
		axis[3] = getenv_int("2160p_h", def_h);
	} else if (strncmp(mode, "smpte",5) == 0) {
		axis[0] = getenv_int("4k2ksmpte_x", def_x);
		axis[1] = getenv_int("4k2ksmpte_y", def_y);
		axis[2] = getenv_int("4k2ksmpte_w", def_w);
		axis[3] = getenv_int("4k2ksmpte_h", def_h);
	} else if (strncmp(mode, "panel",5) == 0) {
		axis[0] = getenv_int("panel_x", def_x);
		axis[1] = getenv_int("panel_y", def_y);
		axis[2] = getenv_int("panel_w", def_w);
		axis[3] = getenv_int("panel_h", def_h);
	} else {
		axis[0] = getenv_int("1080p_x", def_x);
		axis[1] = getenv_int("1080p_y", def_y);
		axis[2] = getenv_int("1080p_w", def_w);
		axis[3] = getenv_int("1080p_h", def_h);
	}

	return ret;
}

void vout_set_current_vmode(int mode)
{
	g_vmode = mode;
}

int vout_get_current_vmode(void)
{
	vout_logl();
	return g_vmode;
}

struct vinfo_s *vout_get_current_vinfo(void)
{
	struct vinfo_s *info = &vout_info;

	vout_logl();

	return info;
}

int vout_get_current_axis(int *axis)
{
	return get_window_axis(axis);
}

void vout_vinfo_dump(void)
{
	struct vinfo_s *info = NULL;

	vout_logl();
	info = vout_get_current_vinfo();
	vout_log("vinfo.vd_base: 0x%p\n", info->vd_base);
	vout_log("vinfo.width: %d\n", info->width);
	vout_log("vinfo.height: %d\n", info->height);
	vout_log("vinfo.field_height: %d\n", info->field_height);
	vout_log("vinfo.vl_bpix: %d\n", info->vl_bpix);
	vout_log("vinfo.vd_color_fg: %d\n", info->vd_color_fg);
	vout_log("vinfo.vd_color_bg: %d\n", info->vd_color_bg);

	if (vout_conf_check())
		return;
	if (vout_conf->reg_dump)
		vout_conf->reg_dump();
}

static void vout_reg_dump(void)
{
	vout_log("venc_mux: 0x%x = 0x%08x\n",
		 vout_conf->venc_mux_reg,
		 vout_reg_read(0, vout_conf->venc_mux_reg));
}

static void vout_reg_dump_t7(void)
{
	unsigned int i;

	for (i = 0; i < 3; i++) {
		vout_log("venc_mux: 0x%08x = 0x%08x\n",
			 vout_conf->venc_mux_reg + vout_conf->offset[i],
			 vout_reg_read(i, vout_conf->venc_mux_reg));
	}
}

static unsigned int vout_viu1_mux = VIU_MUX_MAX;
static unsigned int vout_viu2_mux = VIU_MUX_MAX;
static void vout_viu_mux_default(int viu_sel, int venc_sel)
{
	unsigned int clk_bit = 0xff, clk_sel = 0;
	unsigned int vout_viu_sel = 0xf;

	switch (viu_sel) {
	case VOUT_VIU2_SEL:
		if (vout_conf->viu_valid[1]) {
			/* set cts_vpu_clkc to 200MHz*/
			vout_clk_setb(HHI_VPU_CLKC_CNTL, 2, 9, 3);
			vout_clk_setb(HHI_VPU_CLKC_CNTL, 1, 0, 1);
			vout_clk_setb(HHI_VPU_CLKC_CNTL, 1, 8, 3);
			clk_sel = 1;
		}
		if (venc_sel == vout_viu1_mux)
			vout_viu1_mux = VIU_MUX_MAX;
		vout_viu2_mux = venc_sel;
		break;
	case VOUT_VIU1_SEL:
		clk_sel = 0;
		if (venc_sel == vout_viu2_mux) {
			if (vout_conf->viu_valid[1])
				vout_clk_setb(HHI_VPU_CLKC_CNTL, 0, 8, 1);
			vout_viu2_mux = VIU_MUX_MAX;
		}
		vout_viu1_mux = venc_sel;
		break;
	default:
		break;
	}
	vout_viu_sel = (vout_viu1_mux | (vout_viu2_mux << 2));

	switch (venc_sel) {
	case VIU_MUX_ENCL:
		clk_bit = 1;
		break;
	case VIU_MUX_ENCI:
		clk_bit = 2;
		break;
	case VIU_MUX_ENCP:
		clk_bit = 0;
		break;
	default:
		break;
	}

	vout_reg_setb(0, VPU_VIU_VENC_MUX_CTRL, vout_viu_sel, 0, 4);
	if (vout_conf->viu_valid[1]) {
		if (clk_bit < 0xff)
			vout_reg_setb(0, VPU_VENCX_CLK_CTRL, clk_sel, clk_bit, 1);
	}
}

static void vout_viu_mux_t7(int viu_sel, int venc_sel)
{
	unsigned int index = 3, mux_val = 3;

	switch (viu_sel) {
	case VOUT_VIU3_SEL:
		index = 2;
		break;
	case VOUT_VIU2_SEL:
		index = 1;
		break;
	case VOUT_VIU1_SEL:
		index = 0;
		break;
	default:
		break;
	}
	if (index > 2) {
		vout_log("error: %s: invalid index %d\n", __func__, index);
		return;
	}

	switch (venc_sel) {
	case VIU_MUX_ENCL:
		mux_val = 2;
		break;
	case VIU_MUX_ENCI:
		mux_val = 0;
		break;
	case VIU_MUX_ENCP:
		mux_val = 1;
		break;
	default:
		break;
	}

	vout_reg_write(index, VPU_VENC_CTRL, mux_val);
}

void vout_viu_mux(int viu_sel, int venc_sel)
{
	if (vout_conf_check())
		return;

	if (vout_conf->viu_mux)
		vout_conf->viu_mux(viu_sel, venc_sel);
}

void vout_init(void)
{
	vout_logl();
	vout_vmode_init();
}

/* **********************************
 * vout match data
 * **********************************
 */
static struct vout_conf_s vout_config_single = {
	.viu_valid[0] = 1,
	.viu_valid[1] = 0,
	.viu_valid[2] = 0,

	.offset[0] = 0,
	.offset[1] = 0,
	.offset[2] = 0,

	.venc_mux_reg = VPU_VIU_VENC_MUX_CTRL,

	.viu_mux = vout_viu_mux_default,
	.reg_dump = vout_reg_dump,
};

static struct vout_conf_s vout_config_dual = {
	.viu_valid[0] = 1,
	.viu_valid[1] = 1,
	.viu_valid[2] = 0,

	.offset[0] = 0,
	.offset[1] = 0,
	.offset[2] = 0,

	.venc_mux_reg = VPU_VIU_VENC_MUX_CTRL,

	.viu_mux = vout_viu_mux_default,
	.reg_dump = vout_reg_dump,
};

static struct vout_conf_s vout_config_triple = {
	.viu_valid[0] = 1,
	.viu_valid[1] = 1,
	.viu_valid[2] = 1,

	.offset[0] = 0x0,
	.offset[1] = 0x600,
	.offset[2] = 0x800,

	.venc_mux_reg = VPU_VENC_CTRL,

	.viu_mux = vout_viu_mux_t7,
	.reg_dump = vout_reg_dump_t7,
};

void vout_probe(void)
{
	switch (get_cpu_id().family_id) {
	case MESON_CPU_MAJOR_ID_G12A:
	case MESON_CPU_MAJOR_ID_G12B:
	case MESON_CPU_MAJOR_ID_TL1:
	case MESON_CPU_MAJOR_ID_TM2:
	case MESON_CPU_MAJOR_ID_SM1:
	case MESON_CPU_MAJOR_ID_T5:
	case MESON_CPU_MAJOR_ID_T5D:
		vout_conf = &vout_config_dual;
		break;
	case MESON_CPU_MAJOR_ID_T7:
		vout_conf = &vout_config_triple;
		break;
	default:
		vout_conf = &vout_config_single;
		break;
	}
}