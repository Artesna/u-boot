/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2021 Wesion, Inc. All rights reserved.
 */

#ifndef __BOARD_CFG_H__
#define __BOARD_CFG_H__

#include <asm/arch/cpu.h>

/*
 * platform power init config
 */

/* config for khadas kbi */
#define CONFIG_KHADAS_KBI 1
#define AML_VCCK_A_INIT_VOLTAGE      1009       // VCCK A power up voltage
#define AML_VCCK_B_INIT_VOLTAGE      1009       // VCCK B power up voltage
#define AML_VDDEE_INIT_VOLTAGE       830       // VDDEE power up voltage
#define AML_VDDGPU_INIT_VOLTAGE      830       // VDDGPU power up voltage
#define AML_VDDNPU_INIT_VOLTAGE      830       // VDDNPU power up voltage
#define AML_VDDDDR_INIT_VOLTAGE      830       // VDDDDR power up voltage
/*Distinguish whether to use efuse to adjust vddee*/
#define CONFIG_PDVFS_ENABLE

#define CONFIG_PHY_REALTEK 1
/* SMP Definitinos */
#define CPU_RELEASE_ADDR        secondary_boot_func

/* Bootloader Control Block function
   That is used for recovery and the bootloader to talk to each other
  */
#if 0
#define CONFIG_BOOTLOADER_CONTROL_BLOCK
#endif

/* Serial config */
#define CONFIG_CONS_INDEX 2
#define CONFIG_BAUDRATE  115200

/*low console baudrate*/
#define CONFIG_LOW_CONSOLE_BAUD            0

/* Enable ir remote wake up for bl30 */
#define AML_IR_REMOTE_POWER_UP_KEY_VAL1 0xef10fe01 //amlogic tv ir --- power
#define AML_IR_REMOTE_POWER_UP_KEY_VAL2 0XBB44FB04 //amlogic tv ir --- ch+
#define AML_IR_REMOTE_POWER_UP_KEY_VAL3 0xF20DFE01 //amlogic tv ir --- ch-
#define AML_IR_REMOTE_POWER_UP_KEY_VAL4 0XBA45BD02 //amlogic small ir--- power
#define AML_IR_REMOTE_POWER_UP_KEY_VAL5 0xe51afb04
#define AML_IR_REMOTE_POWER_UP_KEY_VAL6 0xFFFFFFFF
#define AML_IR_REMOTE_POWER_UP_KEY_VAL7 0xFFFFFFFF
#define AML_IR_REMOTE_POWER_UP_KEY_VAL8 0xFFFFFFFF
#define AML_IR_REMOTE_POWER_UP_KEY_VAL9 0xFFFFFFFF

/*config the default parameters for adc power key*/
#define AML_ADC_POWER_KEY_CHAN   2  /*channel range: 0-7*/
#define AML_ADC_POWER_KEY_VAL    0  /*sample value range: 0-1023*/

//#define CONFIG_BOOTLOADER_CONTROL_BLOCK

#ifdef CONFIG_DTB_BIND_KERNEL    //load dtb from kernel, such as boot partition
#define CONFIG_DTB_LOAD  "imgread dtb ${boot_part} ${dtb_mem_addr}"
#else
#define CONFIG_DTB_LOAD  "imgread dtb _aml_dtb ${dtb_mem_addr}"
#endif//#ifdef CONFIG_DTB_BIND_KERNEL    //load dtb from kernel, such as boot partition

/* args/envs */
#define CONFIG_SYS_MAXARGS  64
#ifdef CONFIG_HDMITX_ONLY
#define CONFIG_EXTRA_ENV_SETTINGS \
        "firstboot=1\0"\
        "silent=1\0"\
        "upgrade_step=0\0"\
        "jtag=disable\0"\
        "loadaddr=0x00020000\0"\
        "os_ident_addr=0x00500000\0"\
        "loadaddr_rtos=0x00001000\0"\
        "loadaddr_kernel=0x01080000\0"\
		"dv_fw_addr=0xa00000\0"\
        "otg_device=1\0" \
        "panel_type=edp_0\0" \
        "lcd_ctrl=0x00000000\0" \
        "lcd_debug=0x00000000\0" \
		"outputmode=1080p60hz\0" \
        "hdmimode=1080p60hz\0" \
        "cvbsmode=576cvbs\0" \
        "display_width=1920\0" \
        "display_height=1080\0" \
		"hdmichecksum=0x00000000\0" \
		"dolby_status=0\0" \
		"dolby_vision_on=0\0" \
		"dv_fw_dir_odm_ext=/odm_ext/firmware/dovi_fw.bin\0" \
		"dv_fw_dir_vendor=/vendor/firmware/dovi_fw.bin\0" \
		"dv_fw_dir=/reserved/firmware/dovi_fw.bin\0" \
		"display_bpp=16\0" \
        "display_color_index=16\0" \
        "display_layer=osd0\0" \
        "display_color_fg=0xffff\0" \
        "display_color_bg=0\0" \
        "dtb_mem_addr=0x01000000\0" \
        "fb_addr=0x00300000\0" \
        "fb_width=1920\0" \
        "fb_height=1080\0" \
        "frac_rate_policy=1\0" \
        "hdr_policy=0\0" \
        "usb_burning=" CONFIG_USB_TOOL_ENTRY "\0" \
        "fdt_high=0x20000000\0"\
        "sdcburncfg=aml_sdc_burn.ini\0"\
        "EnableSelinux=permissive\0" \
        "recovery_part=recovery\0"\
        "lock=10101000\0"\
        "recovery_offset=0\0"\
        "cvbs_drv=0\0"\
        "osd_reverse=0\0"\
        "video_reverse=0\0"\
        "active_slot=normal\0"\
        "boot_part=boot\0"\
        "vendor_boot_part=vendor_boot\0"\
        "suspend=off\0"\
        "powermode=on\0"\
        "ffv_wake=off\0"\
        "ffv_freeze=off\0"\
        "board_logo_part=odm_ext\0" \
        "Irq_check_en=0\0"\
        "common_dtb_load=" CONFIG_DTB_LOAD "\0"\
        "get_os_type=if store read ${os_ident_addr} ${boot_part} 0 0x1000; then os_ident ${os_ident_addr}; fi\0"\
        "fatload_dev=usb\0"\
        "fs_type=""rootfstype=ramfs""\0"\
        "edid_14_dir=/odm/etc/tvconfig/hdmi/port1_14.bin\0" \
        "edid_20_dir=/odm/etc/tvconfig/hdmi/port1_20.bin\0" \
        "edid_select=0\0" \
        "port_map=0x4321\0" \
        "cec_fun=0x2F\0" \
        "logic_addr=0x0\0" \
        "cec_ac_wakeup=1\0" \
        "initargs="\
            "init=/init" CONFIG_KNL_LOG_LEVEL "console=ttyS0,921600 no_console_suspend earlycon=aml-uart,0xfe078000 "\
            "ramoops.pstore_en=1 ramoops.record_size=0x8000 ramoops.console_size=0x4000 loop.max_part=4 "\
            "\0"\
        "upgrade_check="\
            "echo recovery_status=${recovery_status};"\
            "if itest.s \"${recovery_status}\" == \"in_progress\"; then "\
                "run init_display;run storeargs; run recovery_from_flash;"\
            "else fi;"\
            "echo upgrade_step=${upgrade_step}; "\
            "if itest ${upgrade_step} == 3; then run init_display;run storeargs; run update; fi;"\
            "\0"\
        "storeargs="\
            "get_bootloaderversion;" \
            "setenv bootargs ${initargs} otg_device=${otg_device} "\
                "logo=${display_layer},loaded,${fb_addr} powermode=${powermode}  vout=${outputmode},enable "\
                "panel_type=${panel_type} lcd_ctrl=${lcd_ctrl} lcd_debug=${lcd_debug} "\
                "hdmimode=${hdmimode} outputmode=${outputmode} "\
			"hdmichecksum=${hdmichecksum} dolby_vision_on=${dolby_vision_on} "\
			"hdmitx=${cecconfig},${colorattribute} "\
			"frac_rate_policy=${frac_rate_policy} hdmi_read_edid=${hdmi_read_edid} "\
                "osd_reverse=${osd_reverse} video_reverse=${video_reverse} irq_check_en=${Irq_check_en}  "\
                "androidboot.selinux=${EnableSelinux} androidboot.firstboot=${firstboot} jtag=${jtag}; "\
            "setenv bootargs ${bootargs} androidboot.bootloader=${bootloader_version} androidboot.hardware=amlogic;"\
            "run cmdline_keys;"\
            "\0"\
	"cec_init="\
		"echo cec_ac_wakeup=${cec_ac_wakeup}; "\
		"if test ${cec_ac_wakeup} = 1; then "\
			"cec ${logic_addr} ${cec_fun}; "\
			"if test ${edid_select} = 1111; then "\
				"hdmirx init ${port_map} ${edid_20_dir}; "\
			"else "\
				"hdmirx init ${port_map} ${edid_14_dir}; "\
			"fi;"\
		"fi;"\
	"\0"\
        "ffv_freeze_action="\
            "run cec_init;"\
            "setenv ffv_freeze on;"\
            "setenv bootargs ${bootargs} ffv_freeze=on"\
            "\0"\
        "cold_boot_normal_check="\
            "setenv bootargs ${bootargs} ffv_freeze=off; "\
            /*"run try_auto_burn;uboot wake up "*/\
            "if test ${powermode} = on; then "\
                /*"run try_auto_burn; "*/\
            "else if test ${powermode} = standby; then "\
                "run cec_init;"\
                "systemoff; "\
            "else if test ${powermode} = last; then "\
                "echo suspend=${suspend}; "\
                "if test ${suspend} = off; then "\
                    /*"run try_auto_burn; "*/\
                "else if test ${suspend} = on; then "\
                    "run cec_init;"\
                    "systemoff; "\
                "else if test ${suspend} = shutdown; then "\
                    "run cec_init;"\
                    "systemoff; "\
                "fi; fi; fi; "\
            "fi; fi; fi; "\
            "\0"\
        "switch_bootmode="\
            "get_rebootmode;"\
            "setenv ffv_freeze off;"\
            "echo reboot_mode : ${reboot_mode};"\
            "if test ${reboot_mode} = factory_reset; then "\
                    "run recovery_from_flash;"\
            "else if test ${reboot_mode} = update; then "\
                    "run update;"\
            "else if test ${reboot_mode} = quiescent; then "\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
            "else if test ${reboot_mode} = recovery_quiescent; then "\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
                    "run recovery_from_flash;"\
            "else if test ${reboot_mode} = cold_boot; then "\
                    "echo cold boot: ffv_wake=${ffv_wake} "\
                    "powermode=${powermode} suspend=${suspend};"\
                    "if test ${ffv_wake} = on; then "\
                        "if test ${powermode} = on; then "\
                            "setenv bootargs ${bootargs} ffv_freeze=off; "\
                        "else if test ${powermode} = standby; then "\
                            "run ffv_freeze_action; "\
                        "else if test ${powermode} = last; then "\
                            "if test ${suspend} = off; then "\
                                "setenv bootargs ${bootargs} ffv_freeze=off; "\
                            "else if test ${suspend} = on; then "\
                                "run ffv_freeze_action; "\
                            "else if test ${suspend} = shutdown; then "\
                                "run ffv_freeze_action; "\
                            "fi; fi; fi; "\
                        "fi; fi; fi; "\
                    "else "\
                        "run cold_boot_normal_check;"\
                    "fi; "\
            "else if test ${reboot_mode} = ffv_reboot; then "\
                "if test ${ffv_wake} = on; then "\
                    "run ffv_freeze_action; "\
                "fi; "\
            "else if test ${reboot_mode} = fastboot; then "\
                "fastboot 1;"\
            "fi;fi;fi;fi;fi;fi;fi;"\
            "\0" \
        "reset_suspend="\
            "if test ${ffv_freeze} != on; then "\
                "if test ${suspend} = on || test ${suspend} = shutdown; then "\
                    "setenv suspend off;"\
                    "saveenv;"\
                "fi;"\
            "fi;"\
            "\0" \
        "storeboot="\
            "run get_os_type;"\
            "if test ${os_type} = rtos; then "\
                "setenv loadaddr ${loadaddr_rtos};"\
                "store read ${loadaddr} ${boot_part} 0 0x400000;"\
                "bootm ${loadaddr};"\
            "else if test ${os_type} = kernel; then "\
                "get_system_as_root_mode;"\
                "echo system_mode in storeboot: ${system_mode};"\
                "get_avb_mode;"\
                "echo active_slot in storeboot: ${active_slot};"\
                "if test ${system_mode} = 1; then "\
                    "setenv bootargs ${bootargs} ro rootwait skip_initramfs;"\
                "else "\
                    "setenv bootargs ${bootargs} androidboot.force_normal_boot=1;"\
                "fi;"\
                "if test ${active_slot} != normal; then "\
                    "setenv bootargs ${bootargs} androidboot.slot_suffix=${active_slot};"\
                "fi;"\
                "if fdt addr ${dtb_mem_addr}; then else echo retry common dtb; run common_dtb_load; fi;"\
                "setenv loadaddr ${loadaddr_kernel};"\
                "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
            "else echo wrong OS format ${os_type}; fi;fi;"\
            "echo try upgrade as booting failure; run update;"\
            "\0" \
         "update="\
            /*first usb burning, second sdc_burn, third ext-sd autoscr/recovery, last udisk autoscr/recovery*/\
            "run usb_burning; "\
            "run recovery_from_sdcard;"\
            "run recovery_from_udisk;"\
            "run recovery_from_flash;"\
            "\0"\
        "recovery_from_fat_dev="\
            "setenv loadaddr ${loadaddr_kernel};"\
            "if fatload ${fatload_dev} 0 ${loadaddr} aml_autoscript; then autoscr ${loadaddr}; fi;"\
            "if fatload ${fatload_dev} 0 ${loadaddr} recovery.img; then "\
                "if fatload ${fatload_dev} 0 ${dtb_mem_addr} dtb.img; then echo ${fatload_dev} dtb.img loaded; fi;"\
                "setenv bootargs ${bootargs} ${fs_type};"\
                "bootm ${loadaddr};fi;"\
            "\0"\
        "recovery_from_udisk="\
            "setenv fatload_dev usb;"\
            "if usb start 0; then run recovery_from_fat_dev; fi;"\
            "\0"\
        "recovery_from_sdcard="\
            "setenv fatload_dev mmc;"\
            "if mmcinfo; then run recovery_from_fat_dev; fi;"\
            "\0"\
        "recovery_from_flash="\
            "echo active_slot: ${active_slot};"\
            "setenv loadaddr ${loadaddr_kernel};"\
            "if test ${active_slot} = normal; then "\
                "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part={recovery_part} recovery_offset={recovery_offset};"\
                "if imgread dtb recovery ${dtb_mem_addr}; then "\
                    "else echo restore dtb; run common_dtb_load;"\
                "fi;"\
                "if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then bootm ${loadaddr}; fi;"\
            "else "\
                "if fdt addr ${dtb_mem_addr}; then else echo retry common dtb; run common_dtb_load; fi;"\
                "if test ${partiton_mode} = normal; then "\
                    "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${boot_part} recovery_offset=${recovery_offset};"\
                    "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
                "else "\
                    "if test ${vendor_boot_mode} = true; then "\
                        "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${boot_part} recovery_offset=${recovery_offset} androidboot.slot_suffix=${active_slot};"\
                        "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
                    "else "\
                        "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${recovery_part} recovery_offset=${recovery_offset} androidboot.slot_suffix=${active_slot};"\
                        "if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then wipeisb; bootm ${loadaddr}; fi;"\
                    "fi;"\
                "fi;"\
            "fi;"\
            "\0"\
        "bcb_cmd="\
            "get_avb_mode;"\
            "get_valid_slot;"\
            "if test ${vendor_boot_mode} = true; then "\
                "setenv loadaddr_kernel 0x3080000;"\
                "setenv dtb_mem_addr 0x1000000;"\
            "fi;"\
            "if test ${active_slot} != normal; then "\
                "echo ab mode, read dtb from kernel;"\
                "setenv common_dtb_load ""imgread dtb ${boot_part} ${dtb_mem_addr}"";"\
            "fi;"\
            "\0"\
        "load_bmp_logo="\
            "if rdext4pic ${board_logo_part} $loadaddr; then bmp display $logoLoadAddr; " \
            "else if imgread pic logo bootup $loadaddr; then bmp display $bootup_offset; fi; fi;" \
            "\0"\
        "init_display="\
            "hdmitx hpd;hdmitx get_preferred_mode;hdmitx get_parse_edid;dovi process;"\
			"osd open;osd clear;run load_bmp_logo;bmp scale;vout output ${outputmode};"\
			"dovi set;dovi pkg;vpp hdrpkt;"\
			"\0"\
        "check_display="\
            "echo check_display reboot_mode : ${reboot_mode} ,powermode : ${powermode};"\
            "if test ${reboot_mode} = ffv_reboot; then "\
                "if test ${ffv_wake} = on; then "\
                    "echo ffv reboot no display; "\
                "else "\
                    "run init_display; "\
                "fi; "\
            "else "\
                "run init_display; "\
            "fi; "\
            "\0"\
        "cmdline_keys="\
            "setenv region_code US;"\
            "if keyman init 0x1234; then "\
                "if keyman read usid ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.serialno=${usid};"\
                    "setenv serial ${usid}; setenv serial# ${usid};"\
                "else "\
                    "setenv bootargs ${bootargs} androidboot.serialno=an400${cpu_id};"\
                    "setenv serial an400${cpu_id}; setenv serial# an400${cpu_id};"\
                "fi;"\
                "if keyman read region_code ${loadaddr} str; then fi;"\
                "if keyman read mac ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} mac=${mac} androidboot.mac=${mac};"\
                "fi;"\
                "if keyman read deviceid ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.deviceid=${deviceid};"\
                "fi;"\
            "fi;"\
            "setenv bootargs ${bootargs} androidboot.wificountrycode=${region_code};"\
            "factory_provision init;"\
            "\0"\
        "upgrade_key="\
            "if gpio input GPIOD_3; then "\
            "echo detect upgrade key; run update;"\
            "fi;"\
            "\0"

#else
#define CONFIG_EXTRA_ENV_SETTINGS \
        "firstboot=1\0"\
        "silent=1\0"\
        "upgrade_step=0\0"\
        "jtag=disable\0"\
        "loadaddr=0x00020000\0"\
        "os_ident_addr=0x00500000\0"\
        "loadaddr_rtos=0x00001000\0"\
        "loadaddr_kernel=0x01080000\0"\
		"dv_fw_addr=0xa00000\0"\
        "otg_device=1\0" \
        "panel1_type=vbyone_1\0" \
        "panel2_type=lvds_1\0" \
        "lcd_ctrl=0x00000000\0" \
        "lcd1_ctrl=0x00000000\0" \
        "lcd2_ctrl=0x00000000\0" \
        "lcd_debug=0x00000000\0" \
        "ts050_output=panel\0" \
        "ts101_output=panel\0" \
        "vbo_output=panel1\0" \
        "outputmode2=1080p60hz\0" \
        "hdmimode=1080p60hz\0" \
        "cvbsmode=576cvbs\0" \
        "display_width=1920\0" \
        "display_height=1080\0" \
		"hdmichecksum=0x00000000\0" \
		"dolby_status=0\0" \
		"dolby_vision_on=0\0" \
		"dv_fw_dir_odm_ext=/odm_ext/firmware/dovi_fw.bin\0" \
		"dv_fw_dir_vendor=/vendor/firmware/dovi_fw.bin\0" \
		"dv_fw_dir=/reserved/firmware/dovi_fw.bin\0" \
        "display_bpp=16\0" \
        "display_color_index=16\0" \
        "display_layer=osd0\0" \
        "display_color_fg=0xffff\0" \
        "display_color_bg=0\0" \
        "dtb_mem_addr=0x01000000\0" \
        "fb_addr=0x00300000\0" \
        "fb_width=1920\0" \
        "fb_height=1080\0" \
        "frac_rate_policy=1\0" \
        "hdr_policy=0\0" \
        "usb_burning=" CONFIG_USB_TOOL_ENTRY "\0" \
        "fdt_high=0x20000000\0"\
        "sdcburncfg=aml_sdc_burn.ini\0"\
        "EnableSelinux=permissive\0" \
        "recovery_part=recovery\0"\
        "lock=10101000\0"\
        "recovery_offset=0\0"\
        "cvbs_drv=0\0"\
        "osd_reverse=0\0"\
        "video_reverse=0\0"\
        "active_slot=normal\0"\
        "boot_part=boot\0"\
        "vendor_boot_part=vendor_boot\0"\
        "suspend=off\0"\
        "powermode=on\0"\
        "ffv_wake=off\0"\
        "ffv_freeze=off\0"\
        "board_logo_part=odm_ext\0" \
	"boot_flag=0\0"\
        "Irq_check_en=0\0"\
        "common_dtb_load=" CONFIG_DTB_LOAD "\0"\
        "get_os_type=if store read ${os_ident_addr} ${boot_part} 0 0x1000; then os_ident ${os_ident_addr}; fi\0"\
        "fatload_dev=usb\0"\
        "fs_type=""rootfstype=ramfs""\0"\
        "edid_14_dir=/odm/etc/tvconfig/hdmi/port1_14.bin\0" \
        "edid_20_dir=/odm/etc/tvconfig/hdmi/port1_20.bin\0" \
        "edid_select=0\0" \
        "port_map=0x4321\0" \
        "cec_fun=0x2F\0" \
        "logic_addr=0x0\0" \
        "cec_ac_wakeup=1\0" \
	"disable_ir=0\0"\
        "initargs="\
            "init=/init" CONFIG_KNL_LOG_LEVEL "console=ttyS0,921600 no_console_suspend earlycon=aml-uart,0xfe078000 "\
            "ramoops.pstore_en=1 ramoops.record_size=0x8000 ramoops.console_size=0x4000 loop.max_part=4 "\
            "\0"\
        "upgrade_check="\
            "echo recovery_status=${recovery_status};"\
            "if itest.s \"${recovery_status}\" == \"in_progress\"; then "\
                "run init_display;run storeargs; run recovery_from_flash;"\
            "else fi;"\
            "echo upgrade_step=${upgrade_step}; "\
            "if itest ${upgrade_step} == 3; then run init_display;run storeargs; run update; fi;"\
            "\0"\
        "storeargs="\
            "get_bootloaderversion;" \
            "setenv bootargs ${initargs} otg_device=${otg_device} "\
                "logo=${display_layer},loaded,${fb_addr} powermode=${powermode}  vout=${outputmode},enable vout2=${outputmode2},enable "\
                "panel_type=${panel_type} lcd_ctrl=${lcd_ctrl} lcd_debug=${lcd_debug} "\
                "panel1_type=${panel1_type} lcd1_ctrl=${lcd1_ctrl} panel2_type=${panel2_type} lcd2_ctrl=${lcd2_ctrl} "\
                "hdmimode=${hdmimode} outputmode=${outputmode} "\
			"hdmichecksum=${hdmichecksum} dolby_vision_on=${dolby_vision_on} " \
			"hdmitx=${cecconfig},${colorattribute} "\
			"frac_rate_policy=${frac_rate_policy} hdmi_read_edid=${hdmi_read_edid} "\
                "hdr_policy=${hdr_policy} hdr_priority=${hdr_priority} "\
                "osd_reverse=${osd_reverse} video_reverse=${video_reverse} irq_check_en=${Irq_check_en}  "\
		"androidboot.selinux=${EnableSelinux} androidboot.firstboot=${firstboot} "\
		"jtag=${jtag} disable_ir=${disable_ir};"\
            "setenv bootargs ${bootargs} androidboot.bootloader=${bootloader_version} androidboot.hardware=amlogic;"\
            "run cmdline_keys;"\
            "\0"\
		"cec_init="\
			"echo cec_ac_wakeup=${cec_ac_wakeup}; "\
			"if test ${cec_ac_wakeup} = 1; then "\
				"cec ${logic_addr} ${cec_fun}; "\
				"if test ${edid_select} = 1111; then "\
					"hdmirx init ${port_map} ${edid_20_dir}; "\
				"else "\
					"hdmirx init ${port_map} ${edid_14_dir}; "\
				"fi;"\
			"fi;"\
		"\0"\
        "ffv_freeze_action="\
            "run cec_init;"\
            "setenv ffv_freeze on;"\
            "setenv bootargs ${bootargs} ffv_freeze=on"\
            "\0"\
        "cold_boot_normal_check="\
            "setenv bootargs ${bootargs} ffv_freeze=off; "\
            /*"run try_auto_burn;uboot wake up "*/\
            "if test ${powermode} = on; then "\
                /*"run try_auto_burn; "*/\
            "else if test ${powermode} = standby; then "\
                "run cec_init;"\
                "systemoff; "\
            "else if test ${powermode} = last; then "\
                "echo suspend=${suspend}; "\
                "if test ${suspend} = off; then "\
                    /*"run try_auto_burn; "*/\
                "else if test ${suspend} = on; then "\
                    "run cec_init;"\
                    "systemoff; "\
                "else if test ${suspend} = shutdown; then "\
                    "run cec_init;"\
                    "systemoff; "\
                "fi; fi; fi; "\
            "fi; fi; fi; "\
            "\0"\
        "switch_bootmode="\
            "get_rebootmode;"\
            "setenv ffv_freeze off;"\
            "echo reboot_mode : ${reboot_mode};"\
            "if test ${reboot_mode} = factory_reset; then "\
                    "run recovery_from_flash;"\
            "else if test ${reboot_mode} = update; then "\
                    "run update;"\
            "else if test ${reboot_mode} = quiescent; then "\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
            "else if test ${reboot_mode} = recovery_quiescent; then "\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
                    "run recovery_from_flash;"\
            "else if test ${reboot_mode} = cold_boot; then "\
                    "echo cold boot: ffv_wake=${ffv_wake} "\
                    "powermode=${powermode} suspend=${suspend};"\
                    "if test ${ffv_wake} = on; then "\
                        "if test ${powermode} = on; then "\
                            "setenv bootargs ${bootargs} ffv_freeze=off; "\
                        "else if test ${powermode} = standby; then "\
                            "run ffv_freeze_action; "\
                        "else if test ${powermode} = last; then "\
                            "if test ${suspend} = off; then "\
                                "setenv bootargs ${bootargs} ffv_freeze=off; "\
                            "else if test ${suspend} = on; then "\
                                "run ffv_freeze_action; "\
                            "else if test ${suspend} = shutdown; then "\
                                "run ffv_freeze_action; "\
                            "fi; fi; fi; "\
                        "fi; fi; fi; "\
                    "else "\
                        "run cold_boot_normal_check;"\
                    "fi; "\
            "else if test ${reboot_mode} = ffv_reboot; then "\
                "if test ${ffv_wake} = on; then "\
                    "run ffv_freeze_action; "\
                "fi; "\
            "else if test ${reboot_mode} = fastboot; then "\
                "fastboot 1;"\
            "fi;fi;fi;fi;fi;fi;fi;"\
            "\0" \
        "reset_suspend="\
            "if test ${ffv_freeze} != on; then "\
                "if test ${suspend} = on || test ${suspend} = shutdown; then "\
                    "setenv suspend off;"\
                    "saveenv;"\
                "fi;"\
            "fi;"\
            "\0" \
        "storeboot="\
            "kbi resetflag 0;"\
            "run get_os_type;"\
            "if test ${os_type} = rtos; then "\
                "setenv loadaddr ${loadaddr_rtos};"\
                "store read ${loadaddr} ${boot_part} 0 0x400000;"\
                "bootm ${loadaddr};"\
            "else if test ${os_type} = kernel; then "\
                "get_system_as_root_mode;"\
                "echo system_mode in storeboot: ${system_mode};"\
                "get_avb_mode;"\
                "echo active_slot in storeboot: ${active_slot};"\
                "if test ${system_mode} = 1; then "\
                    "setenv bootargs ${bootargs} ro rootwait skip_initramfs;"\
                "else "\
                    "setenv bootargs ${bootargs} androidboot.force_normal_boot=1;"\
                "fi;"\
                "if test ${active_slot} != normal; then "\
                    "setenv bootargs ${bootargs} androidboot.slot_suffix=${active_slot};"\
                "fi;"\
                "if fdt addr ${dtb_mem_addr}; then else echo retry common dtb; run common_dtb_load; fi;"\
                "setenv loadaddr ${loadaddr_kernel};"\
                "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
            "else echo wrong OS format ${os_type}; fi;fi;"\
            "echo try upgrade as booting failure; run update;"\
            "\0" \
         "update="\
            /*first usb burning, second sdc_burn, third ext-sd autoscr/recovery, last udisk autoscr/recovery*/\
            "run usb_burning; "\
            "run recovery_from_sdcard;"\
            "run recovery_from_udisk;"\
            "run recovery_from_flash;"\
            "\0"\
        "recovery_from_fat_dev="\
            "setenv loadaddr ${loadaddr_kernel};"\
            "if fatload ${fatload_dev} 0 ${loadaddr} aml_autoscript; then autoscr ${loadaddr}; fi;"\
            "if fatload ${fatload_dev} 0 ${loadaddr} recovery.img; then "\
                "if fatload ${fatload_dev} 0 ${dtb_mem_addr} dtb.img; then echo ${fatload_dev} dtb.img loaded; fi;"\
                "setenv bootargs ${bootargs} ${fs_type};"\
                "bootm ${loadaddr};fi;"\
            "\0"\
        "recovery_from_udisk="\
            "setenv fatload_dev usb;"\
            "if usb start 0; then run recovery_from_fat_dev; fi;"\
            "\0"\
        "recovery_from_sdcard="\
            "setenv fatload_dev mmc;"\
            "if mmcinfo; then run recovery_from_fat_dev; fi;"\
            "\0"\
        "recovery_from_flash="\
            "echo active_slot: ${active_slot};"\
            "setenv loadaddr ${loadaddr_kernel};"\
            "if test ${active_slot} = normal; then "\
                "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part={recovery_part} recovery_offset={recovery_offset};"\
                "if imgread dtb recovery ${dtb_mem_addr}; then "\
                    "else echo restore dtb; run common_dtb_load;"\
                "fi;"\
                "if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then bootm ${loadaddr}; fi;"\
            "else "\
                "if fdt addr ${dtb_mem_addr}; then else echo retry common dtb; run common_dtb_load; fi;"\
                "if test ${partiton_mode} = normal; then "\
                    "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${boot_part} recovery_offset=${recovery_offset};"\
                    "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
                "else "\
                    "if test ${vendor_boot_mode} = true; then "\
                        "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${boot_part} recovery_offset=${recovery_offset} androidboot.slot_suffix=${active_slot};"\
                        "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
                    "else "\
                        "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${recovery_part} recovery_offset=${recovery_offset} androidboot.slot_suffix=${active_slot};"\
                        "if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then wipeisb; bootm ${loadaddr}; fi;"\
                    "fi;"\
                "fi;"\
            "fi;"\
            "\0"\
        "wol_init="\
               "kbi powerstate;"\
               "kbi trigger wol r;"\
               "if test ${wol_enable} = 1; then "\
               "kbi trigger wol w 1;"\
               "fi;"\
               "if test ${power_state} = 1; then "\
                   "kbi poweroff;"\
               "else "\
                   "kbi wolreset;"\
               "fi;"\
            "\0"\
        "check_panel="\
				"fdt addr ${dtb_mem_addr}; "\
				"if test ${khadas_mipi_id} = 1; then "\
					"echo check T050 panel; outputmode=$ts050_output; setenv outputmode ${ts050_output};"\
					"fdt set /soc/apb4@fe000000/i2c@6c000/gt9xx@14 status disable;"\
					"fdt set /soc/apb4@fe000000/i2c@6c000/ft5336@38 status okay;"\
					"fdt set /fb display_size_default <0x00000870 0x00000f00 0x00000870 0x00001e00 0x00000020>;"\
				"else if test ${khadas_mipi_id} = 2; then "\
					"echo check T101 panel; outputmode=$ts101_output; setenv outputmode ${ts101_output};"\
					"fdt set /soc/apb4@fe000000/i2c@6c000/gt9xx@14 status okay;"\
					"fdt set /soc/apb4@fe000000/i2c@6c000/ft5336@38 status disable;"\
					"fdt set /fb display_size_default <0x00000f00 0x00000960 0x00000f00 0x000012c0 0x00000020>;"\
				"else "\
					"echo no check dsi panel; outputmode=$vbo_output; setenv outputmode ${vbo_output};"\
					"fdt set /fb display_size_default <0x00000f00 0x00000870 0x00000f00 0x000010e0 0x00000020>;"\
				"fi;fi;"\
				"echo $outputmode;"\
			"\0"\
        "check_vbo="\
				"fdt addr ${dtb_mem_addr}; "\
				"if gpio input GPIOY_11; then "\
					"echo check has vbo panel;"\
					"fdt set /backlight1 status okay;"\
					"fdt set /soc/apb4@fe000000/pwm@5c000 status okay;"\
				"else "\
					"echo check no vbo panel;"\
					"if test ${khadas_mipi_id} = 1; then "\
						"echo check T050 panel;"\
					"else if test ${khadas_mipi_id} = 2; then "\
						"echo check T101 panel;"\
					"else "\
						"fdt set /backlight1 status disable;"\
						"fdt set /soc/apb4@fe000000/pwm@5c000 status disable;"\
					"fi;fi;"\
				"fi;"\
			"\0"\
        "bcb_cmd="\
            "get_avb_mode;"\
            "get_valid_slot;"\
            "if test ${vendor_boot_mode} = true; then "\
                "setenv loadaddr_kernel 0x3080000;"\
                "setenv dtb_mem_addr 0x1000000;"\
            "fi;"\
            "if test ${active_slot} != normal; then "\
                "echo ab mode, read dtb from kernel;"\
                "setenv common_dtb_load ""imgread dtb ${boot_part} ${dtb_mem_addr}"";"\
            "fi;"\
            "\0"\
        "load_bmp_logo="\
            "if rdext4pic ${board_logo_part} $loadaddr; then bmp display $logoLoadAddr; " \
            "else if imgread pic logo bootup $loadaddr; then bmp display $bootup_offset; fi; fi;" \
            "\0"\
        "init_display="\
			"hdmitx hpd;hdmitx get_preferred_mode;hdmitx get_parse_edid;dovi process;"\
			"if test ${khadas_mipi_id} = 1; then "\
				"osd open;osd clear;imgread pic logo bootup_rotate_secondary $loadaddr;bmp display $bootup_rotate_secondary_offset;bmp scale;vout output ${outputmode};"\
			"else if test ${khadas_mipi_id} = 2; then "\
				"setenv display_layer osd0;osd open;osd clear;run load_bmp_logo;bmp scale;vout output ${outputmode};"\
			"else "\
			"fi;fi;"\
            "setenv outputmode2 ${hdmimode};"\
            "osd dual_logo;"\
			"dovi set;dovi pkg;vpp hdrpkt;"\
            "\0"\
        "check_display="\
            "echo check_display reboot_mode : ${reboot_mode} ,powermode : ${powermode};"\
            "if test ${reboot_mode} = ffv_reboot; then "\
                "if test ${ffv_wake} = on; then "\
                    "echo ffv reboot no display; "\
                "else "\
                    "run init_display; "\
                "fi; "\
            "else "\
                "run init_display; "\
            "fi; "\
            "\0"\
        "cmdline_keys="\
            "setenv region_code US;"\
            "setenv usid an400${cpu_id};"\
            "if keyman init 0x1234; then "\
                "if keyman read region_code ${loadaddr} str; then fi;"\
                "if keyman read deviceid ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.deviceid=${deviceid};"\
                "fi;"\
            "fi;"\
            "kbi usid noprint;"\
				"setenv bootargs ${bootargs} androidboot.serialno=${usid};"\
				"setenv serial ${usid}; setenv serial# ${usid};"\
            "kbi ethmac noprint;"\
				"setenv bootargs ${bootargs} mac=${eth_mac} androidboot.mac=${eth_mac};"\
            "setenv bootargs ${bootargs} androidboot.wificountrycode=${region_code};"\
			"setenv bootargs ${bootargs} khadas_mipi_id=${khadas_mipi_id};"\
			"setenv bootargs ${bootargs} wol_enable=${wol_enable};"\
            "factory_provision init;"\
            "\0"\
        "upgrade_key="\
            "if gpio input GPIOD_4; then "\
                  "echo detect upgrade key;"\
                  "if test ${boot_flag} = 0; then "\
                      "echo enter fastboot; setenv boot_flag 1; saveenv; fastboot 1;"\
                  "else if test ${boot_flag} = 1; then "\
                      "echo enter update; setenv boot_flag 2; saveenv; run update;"\
                  "else "\
                      "echo enter recovery; setenv boot_flag 0; saveenv; run recovery_from_flash;"\
                  "fi;fi;"\
            "fi;"\
            "\0"\
        "updateu="\
            "if tftp 1080000 u-boot.bin.signed; then "\
                "store boot_write bootloader 1080000 $filesize;"\
            "fi;"\
            "\0"
#endif

#define CONFIG_PREBOOT  \
            "run bcb_cmd; "\
            "run check_panel;"\
            "run upgrade_check;"\
            "run check_display;"\
            "run wol_init;"\
            "run check_vbo;"\
            "run storeargs;"\
            "run upgrade_key;" \
            "bcb uboot-command;" \
            "run switch_bootmode;" \
            "run reset_suspend;"

#ifndef CONFIG_HDMITX_ONLY
/* dual logo, normal boot */
/*
* logo image path: device/amlogic/$(proj_name)/logo_img_files/
*/
#define CONFIG_DUAL_LOGO \
    "setenv outputmode2 ${hdmimode};"\
    "setenv display_layer viu2_osd0;vout2 prepare ${outputmode2};"\
    "osd open;osd clear;run load_bmp_logo;vout2 output ${outputmode2};bmp scale;"\
	"if test ${khadas_mipi_id} = 1; then "\
        "setenv fb_width 1080;setenv fb_height 1920;"\
        "setenv display_width 1080;setenv display_height 1920;"\
        "setenv display_layer osd0;osd open;osd clear;imgread pic logo bootup_rotate_secondary $loadaddr;bmp display $bootup_rotate_secondary_offset;bmp scale;vout output ${outputmode};"\
	"else if test ${khadas_mipi_id} = 2; then "\
        "setenv fb_width 1920;setenv fb_height 1200;"\
        "setenv display_width 1920;setenv display_height 1200;"\
		"setenv display_layer osd0;osd open;osd clear;run load_bmp_logo;bmp scale;vout output ${outputmode};"\
	"else "\
        "setenv display_layer osd0;osd open;osd clear;run load_bmp_logo;bmp scale;vout output ${outputmode};"\
	"fi;fi;"\
    "\0"\

/* dual logo, factory_reset boot, recovery always displays on panel */
#define CONFIG_RECOVERY_DUAL_LOGO \
    "setenv outputmode2 ${hdmimode};"\
    "setenv display_layer viu2_osd0;vout2 prepare ${outputmode2};"\
    "osd open;osd clear;run load_bmp_logo;vout2 output ${outputmode2};bmp scale;"\
	"if test ${khadas_mipi_id} = 1; then "\
        "setenv fb_width 1080;setenv fb_height 1920;"\
        "setenv display_width 1080;setenv display_height 1920;"\
        "setenv display_layer osd0;osd open;osd clear;imgread pic logo bootup_rotate_secondary $loadaddr;bmp display $bootup_rotate_secondary_offset;bmp scale;vout output ${outputmode};"\
	"else if test ${khadas_mipi_id} = 2; then "\
        "setenv fb_width 1920;setenv fb_height 1200;"\
        "setenv display_width 1920;setenv display_height 1200;"\
		"setenv display_layer osd0;osd open;osd clear;run load_bmp_logo;bmp scale;vout output ${outputmode};"\
	"else "\
        "setenv display_layer osd0;osd open;osd clear;run load_bmp_logo;bmp scale;vout output ${outputmode};"\
	"fi;fi;"\
    "\0"\

/* single logo */
#define CONFIG_SINGLE_LOGO \
	"if test ${khadas_mipi_id} = 1; then "\
        "setenv fb_width 1080;setenv fb_height 1920;"\
        "setenv display_width 1080;setenv display_height 1920;"\
        "setenv display_layer osd0;osd open;osd clear;imgread pic logo bootup_rotate_secondary $loadaddr;bmp display $bootup_rotate_secondary_offset;bmp scale;vout output ${outputmode};"\
	"else if test ${khadas_mipi_id} = 2; then "\
        "setenv fb_width 1920;setenv fb_height 1200;"\
        "setenv display_width 1920;setenv display_height 1200;"\
		"setenv display_layer osd0;osd open;osd clear;run load_bmp_logo;bmp scale;vout output ${outputmode};"\
	"else "\
        "setenv display_layer osd0;osd open;osd clear;run load_bmp_logo;bmp scale;vout output ${outputmode};"\
	"fi;fi;"\
    "\0"
#endif

/* #define CONFIG_ENV_IS_NOWHERE  1 */
#define CONFIG_ENV_SIZE   (64*1024)
#define CONFIG_FIT 1
#define CONFIG_OF_LIBFDT 1
#define CONFIG_ANDROID_BOOT_IMAGE 1
#define CONFIG_SYS_BOOTM_LEN (64<<20) /* Increase max gunzip size*/

/* ATTENTION */
/* DDR configs move to board/amlogic/[board]/firmware/timing.c */

/* running in sram */
//#define UBOOT_RUN_IN_SRAM
#ifdef UBOOT_RUN_IN_SRAM
#define CONFIG_SYS_INIT_SP_ADDR                (0x00200000)
/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN                (256*1024)
#else
#define CONFIG_SYS_INIT_SP_ADDR                (0x00200000)
#define CONFIG_SYS_MALLOC_LEN                (96*1024*1024)
#endif

//#define CONFIG_NR_DRAM_BANKS            1
/* ddr functions */
#define DDR_FULL_TEST            0 //0:disable, 1:enable. ddr full test
#define DDR_LOW_POWER            0 //0:disable, 1:enable. ddr clk gate for lp
#define DDR_ZQ_PD                0 //0:disable, 1:enable. ddr zq power down
#define DDR_USE_EXT_VREF         0 //0:disable, 1:enable. ddr use external vref
#define DDR4_TIMING_TEST         0 //0:disable, 1:enable. ddr4 timing test function
#define DDR_PLL_BYPASS           0 //0:disable, 1:enable. ddr pll bypass function

/* storage: emmc/nand/sd */
#define CONFIG_ENV_OVERWRITE
/* #define     CONFIG_CMD_SAVEENV */
/* fixme, need fix*/

#if (defined(CONFIG_ENV_IS_IN_AMLNAND) || defined(CONFIG_ENV_IS_IN_MMC)) && defined(CONFIG_STORE_COMPATIBLE)
#error env in amlnand/mmc already be compatible;
#endif

/*
*                storage
*        |---------|---------|
*        |                    |
*        emmc<--Compatible-->nand
*                    |-------|-------|
*                    |        |
*                    MTD<-Exclusive->NFTL
*                    |
*            |***************|***************|
*            slc-nand    SPI-nand    SPI-nor
*            (raw nand)
*/
/* axg only support slc nand */
/* swither for mtd nand which is for slc only. */


#if defined(CONFIG_AML_NAND) && defined(CONFIG_MESON_NFC)
#error CONFIG_AML_NAND/CONFIG_MESON_NFC can not support at the sametime;
#endif

#if (defined(CONFIG_AML_NAND) || defined(CONFIG_MESON_NFC)) && defined(CONFIG_MESON_FBOOT)
#error CONFIG_AML_NAND/CONFIG_MESON_NFC CONFIG _MESON_FBOOT can not support at the sametime;
#endif

#if defined(CONFIG_SPI_NAND) && defined(CONFIG_MTD_SPI_NAND) && defined(CONFIG_MESON_NFC)
#error CONFIG_SPI_NAND/CONFIG_MTD_SPI_NAND/CONFIG_MESON_NFC can not support at the sametime;
#endif

/* #define        CONFIG_AML_SD_EMMC 1 */
#ifdef        CONFIG_AML_SD_EMMC
    #define     CONFIG_GENERIC_MMC 1
    #define     CONFIG_CMD_MMC 1
    #define CONFIG_CMD_GPT 1
    #define    CONFIG_SYS_MMC_ENV_DEV 1
    #define CONFIG_EMMC_DDR52_EN 0
    #define CONFIG_EMMC_DDR52_CLK 35000000
#endif
#define        CONFIG_PARTITIONS 1
#if 0
#define     CONFIG_SYS_NO_FLASH  1
#endif

#if defined CONFIG_MESON_NFC || defined CONFIG_SPI_NAND || defined CONFIG_MTD_SPI_NAND
    #define CONFIG_SYS_MAX_NAND_DEVICE  2
#endif

/* vpu */
#define AML_VPU_CLK_LEVEL_DFT 7
/* LCD */

/* osd */
#define OSD_SCALE_ENABLE
#define AML_OSD_HIGH_VERSION
#define AML_T7_DISPLAY

/* USB
 * Enable CONFIG_MUSB_HCD for Host functionalities MSC, keyboard
 * Enable CONFIG_MUSB_UDD for Device functionalities.
 */
/* #define CONFIG_MUSB_UDC        1 */
/* #define CONFIG_CMD_USB 1 */

#define USB_PHY2_PLL_PARAMETER_1    0x09400414
#define USB_PHY2_PLL_PARAMETER_2    0x927e0000
#define USB_PHY2_PLL_PARAMETER_3    0xAC5F49E5

#define USB_G12x_PHY_PLL_SETTING_1    (0xfe18)
#define USB_G12x_PHY_PLL_SETTING_2    (0xfff)
#define USB_G12x_PHY_PLL_SETTING_3    (0x78000)
#define USB_G12x_PHY_PLL_SETTING_4    (0xe0004)
#define USB_G12x_PHY_PLL_SETTING_5    (0xe000c)

#define AML_TXLX_USB        1
#define AML_USB_V2             1
#define USB_GENERAL_BIT         3
#define USB_PHY21_BIT           4

/* UBOOT fastboot config */


/* UBOOT Facotry usb/sdcard burning config */

/* net */
#define CONFIG_CMD_NET   1
#define CONFIG_ETH_DESIGNWARE
#if defined(CONFIG_CMD_NET)
    #define CONFIG_DESIGNWARE_ETH 1
    #define CONFIG_PHYLIB    1
    #define CONFIG_NET_MULTI 1
    #define CONFIG_CMD_PING 1
    #define CONFIG_CMD_DHCP 1
    #define CONFIG_CMD_RARP 1
    #define CONFIG_HOSTNAME        "arm_gxbb"
#if 0
    #define CONFIG_RANDOM_ETHADDR  1                   /* use random eth addr, or default */
#endif
    #define CONFIG_ETHADDR         00:15:18:01:81:31   /* Ethernet address */
	#define CONFIG_IPADDR          192.168.1.200          /* Our ip address */
	#define CONFIG_GATEWAYIP       192.168.1.1           /* Our getway ip address */
	#define CONFIG_SERVERIP        192.168.1.230         /* Tftp server ip address */
    #define CONFIG_NETMASK         255.255.255.0
#endif /* (CONFIG_CMD_NET) */

#define MAC_ADDR_NEW  1

/* other devices */
#define CONFIG_SHA1 1
#define CONFIG_MD5 1

/* commands */
/* #define CONFIG_CMD_PLLTEST 1 */

/*file system*/
#define CONFIG_DOS_PARTITION 1
#define CONFIG_EFI_PARTITION 1
/* #define CONFIG_MMC 1 */
#define CONFIG_FS_FAT 1
#define CONFIG_FS_EXT4 1
#define CONFIG_LZO 1

#define CONFIG_FAT_WRITE 1
#define CONFIG_AML_FACTORY_PROVISION 1

/* Cache Definitions */
/* #define CONFIG_SYS_DCACHE_OFF */
/* #define CONFIG_SYS_ICACHE_OFF */

/* other functions */
#define CONFIG_LIBAVB        1

/* define CONFIG_SYS_MEM_TOP_HIDE 8M space for free buffer */
#define CONFIG_SYS_MEM_TOP_HIDE        0x00800000

#define CONFIG_CPU_ARMV8

//use sha2 command
#define CONFIG_CMD_SHA2

//use startdsp command
#define CONFIG_CMD_STARTDSP

//use dache command
#define CONFIG_CMD_CACHE

//use remapset command
#define CONFIG_CMD_REMAPSET

//use hardware sha2
#define CONFIG_AML_HW_SHA2

#define CONFIG_MULTI_DTB    1
// use auto select DTB table
#ifdef CONFIG_MULTI_DTB
    #define CONFIG_T7_3G_SIZE   0xC0000000
    #define CONFIG_T7_4G_SIZE   0x100000000
    #define CONFIG_T7_6G_SIZE   0x180000000
    #define CONFIG_T7_8G_SIZE   0x200000000
#endif

#define CONFIG_RX_RTERM        1
#define CONFIG_CMD_HDMIRX   1
#define CONFIG_CMD_CEC        1
/* define CONFIG_UPDATE_MMU_TABLE for need update mmu */
#define    CONFIG_UPDATE_MMU_TABLE

/* support secure boot */
#define CONFIG_AML_SECURE_UBOOT   1

#if defined(CONFIG_AML_SECURE_UBOOT)

/* unify build for generate encrypted bootloader "u-boot.bin.encrypt" */
#define CONFIG_AML_CRYPTO_UBOOT   1
//#define CONFIG_AML_SIGNED_UBOOT   1
/* unify build for generate encrypted kernel image
   SRC : "board/amlogic/(board)/boot.img"
   DST : "fip/boot.img.encrypt" */
/* #define CONFIG_AML_CRYPTO_IMG       1 */

#endif /* CONFIG_AML_SECURE_UBOOT */

#define CONFIG_FIP_IMG_SUPPORT  1

#define BL32_SHARE_MEM_SIZE  0x800000

#endif