
/*
 * board/amlogic/txl_skt_v1/firmware/timing.c
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

#include <asm/arch/secure_apb.h>
#include <asm/arch/timing.h>
#include <asm/arch/ddr_define.h>

/* board clk defines */
#define CPU_CLK					1512
#define DSU_CLK					1200

/* ddr config support multiple configs for boards which use same bootloader:
 * config steps:
 * 1. add a new data struct in __ddr_setting[]
 * 2. config correct board_id, ddr_type, freq, etc..
 */


/* CAUTION!! */
/* Confirm ddr configs with hardware designer,
 * if you don't know how to config, then don't edit it
 */

/* Key configs */
/*
 * board_id: check hardware adc config
 * dram_rank_config:
 *            #define CONFIG_DDR_CHL_AUTO					0xF
 *            #define CONFIG_DDR0_16BIT_CH0				0x1
 *            #define CONFIG_DDR0_16BIT_RANK01_CH0		0x4
 *            #define CONFIG_DDR0_32BIT_RANK0_CH0			0x2
 *            #define CONFIG_DDR0_32BIT_RANK01_CH01		0x3
 *            #define CONFIG_DDR0_32BIT_16BIT_RANK0_CH0	0x5
 *            #define CONFIG_DDR0_32BIT_16BIT_RANK01_CH0	0x6
 * DramType:
 *            #define CONFIG_DDR_TYPE_DDR3				0
 *            #define CONFIG_DDR_TYPE_DDR4				1
 *            #define CONFIG_DDR_TYPE_LPDDR4				2
 *            #define CONFIG_DDR_TYPE_LPDDR3				3
 * DRAMFreq:
 *            {pstate0, pstate1, pstate2, pstate3} //more than one pstate means use dynamic freq
 *
 */


/* ddr configs */
#define DDR_RFC_TYPE_DDR3_512Mbx1				0
#define DDR_RFC_TYPE_DDR3_512Mbx2				1
#define DDR_RFC_TYPE_DDR3_512Mbx4				2
#define DDR_RFC_TYPE_DDR3_512Mbx8				3
#define DDR_RFC_TYPE_DDR3_512Mbx16				4
#define DDR_RFC_TYPE_DDR4_2Gbx1					5
#define DDR_RFC_TYPE_DDR4_2Gbx2					6
#define DDR_RFC_TYPE_DDR4_2Gbx4					7
#define DDR_RFC_TYPE_DDR4_2Gbx8					8

#define DDR_RFC_TYPE_LPDDR4_2Gbx1				9
#define DDR_RFC_TYPE_LPDDR4_3Gbx1				10
#define DDR_RFC_TYPE_LPDDR4_4Gbx1				11

#define ENABLE_LPDDR4X_MODE 1

ddr_set_t __ddr_setting[] __attribute__ ((section(".ddr_param"))) = {
	{
		//.fast_boot[0]=0x000000fd,// 253
		.board_id = CONFIG_BOARD_ID_MASK,
		.version = 1,
		//.dram_rank_config		= CONFIG_DDR0_32BIT_RANK0_CH0,
		.DramType					= CONFIG_DDR_TYPE_LPDDR4,
		.enable_lpddr4x_mode=ENABLE_LPDDR4X_MODE,
		.DRAMFreq ={1200,		       0,	0,	 0	 },
		.ddr_rfc_type = DDR_RFC_TYPE_LPDDR4_8Gbx1,
		.ddr_base_addr = CFG_DDR_BASE_ADDR,
		.ddr_start_offset = CFG_DDR_START_OFFSET,
		.DisabledDbyte[0] = 0xf0,                       //bit 0 -3 ch0 cs0 ,bit 4-7 ch0 cs1,
		.DisabledDbyte[1] = 0xf0,                       //bit 0 -3 ch1 cs0 ,bit 4-7 ch1 cs1,
		.Is2Ttiming = 0,
		.HdtCtrl = 0xc8,
		//.dram_ch0_size_MB		= 0xffff,
		//.dram_ch1_size_MB		= 0,
		.dram_ch0_size_MB =
			(DRAM_SIZE_ID_256MBX2 << CONFIG_CS0_BYTE_01_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX2 << CONFIG_CS0_BYTE_23_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX0 << CONFIG_CS1_BYTE_01_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX0 << CONFIG_CS1_BYTE_01_SIZE_256_ID_OFFSET),
		.dram_ch1_size_MB =
			(DRAM_SIZE_ID_256MBX2 << CONFIG_CS0_BYTE_01_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX2 << CONFIG_CS0_BYTE_23_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX0 << CONFIG_CS1_BYTE_01_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX0 << CONFIG_CS1_BYTE_01_SIZE_256_ID_OFFSET),
		.training_SequenceCtrl ={ 0x131f,		    0x61 },     //ddr3 0x21f 0x31f
		.phy_odt_config_rank ={ 0x23,			  0x13 }, //use 0x23 0x13  compatibility with 1rank and 2rank //targeting rank 0. [3:0] is used //for write ODT [7:4] is used for //read ODT
		.dfi_odt_config = 0x0d0d,               //use 0d0d compatibility with 1rank and 2rank  //0808
		.PllBypassEn = 0,                       //bit0-ps0,bit1-ps1
		.ddr_rdbi_wr_enable = 0x0,              //bit 0 read-dbi,bit 1 write dbi
		.clk_drv_ohm = 40,
		.cs_drv_ohm = 40,
		.ac_drv_ohm = 40,
		.soc_data_drv_ohm_p = 40,
		.soc_data_drv_ohm_n = 40,
		.soc_data_odt_ohm_p = 0,
		.soc_data_odt_ohm_n = 60,
		.dram_data_drv_ohm = 40,                //48, //34, //ddr4 sdram only 34 or 48, skt board use 34 better
		.dram_data_odt_ohm = 60,                //60,
		.dram_ac_odt_ohm = 255,
		.soc_clk_slew_rate = 0x3ff,
		.soc_cs_slew_rate = 0x3ff,
		.soc_ac_slew_rate = 0x3ff,
		.soc_data_slew_rate = 0x2ff,
		.vref_output_permil = 000,
		.vref_receiver_permil = 0,
		.vref_dram_permil = 0,
		//.vref_reverse			= 0,
		//.ac_trace_delay			={0x0,0x0},// {0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40},
		.ac_trace_delay ={ 32 + 0,		     32 + 0, 32 + 0, 32 + 0, 32, 32 + 0, 32 + 0, 32 + 0, 32 + 0, 32 + 0},
		.ddr_dmc_remap					=
		{
			[0] = (5 | 6 << 5 | 7 << 10 | 8 << 15 | 9 << 20 | 10 << 25),
			[1] = (11 | 0 << 5 | 0 << 10 | 15 << 15 | 16 << 20 | 17 << 25),
			[2] = (18 | 19 << 5 | 20 << 10 | 21 << 15 | 22 << 20 | 23 << 25),
			[3] = (24 | 25 << 5 | 26 << 10 | 27 << 15 | 28 << 20 | 29 << 25),
			[4] = (30 | 12 << 5 | 13 << 10 | 14 << 15 | 0 << 20 | 0 << 25),
		},
		.ddr_lpddr34_ca_remap				= { 00,			00 },
		.ddr_lpddr34_dq_remap				= { 7,1,5, 0, 2, 3, 4, 6,
			8, 15, 12, 13, 9, 10, 11, 14,
			22, 18, 21, 20, 17, 23, 16, 19,
			29, 30, 28, 31, 24, 27, 26, 25},

		.dram_rtt_nom_wr_park ={ 00,			   00 },

		/* pll ssc config:
		 *
		 *   pll_ssc_mode = (1<<20) | (1<<8) | ([strength] << 4) | [mode],
		 *      ppm = strength * 500
		 *      mode: 0=center, 1=up, 2=down
		 *
		 *   eg:
		 *     1. config 1000ppm center ss. then mode=0, strength=2
		 *        .pll_ssc_mode = (1<<20) | (1<<8) | (2 << 4) | 0,
		 *     2. config 3000ppm down ss. then mode=2, strength=6
		 *        .pll_ssc_mode = (1<<20) | (1<<8) | (6 << 4) | 2,
		 */
		//.pll_ssc_mode			= (1<<20) | (1<<8) | (2<<4) | 0,//center_ssc_1000ppm
		.ddr_func = 0,                          // DDR_FUNC,
		.magic = DRAM_CFG_MAGIC,
		.slt_test_function ={ 0x0,			0x0 }, //{0x1,0x0},enable slt 4 DRAMFreq test;{0x0,0x0},disable slt 4 DRAMFreq test;
		.fast_boot[0] = 0,
		.ac_pinmux = {2,3,1,0,5,4,0,0,0,0,
			1,3,5,2,4,0,0,0,0  },

		.dfi_pinmux =
		{
			1,
			2,
			3,
			4,
			5,
			6,
			7,
			8,
			0,
			10,
			11,
			12,
			13,
			14,
			15,
			16,
			17,
			18,
			19,
			20,
			21,
			22,
			23,
			0,
			0,
			0,
		},

	},
	{
		//.fast_boot[0]=0x000000fd,// 253
		.board_id = CONFIG_BOARD_ID_MASK,
		.version = 1,
		//.dram_rank_config		= CONFIG_DDR0_32BIT_RANK0_CH0,
		.DramType					= CONFIG_DDR_TYPE_LPDDR4,
		.enable_lpddr4x_mode=ENABLE_LPDDR4X_MODE,
		.DRAMFreq ={1200,		       0,	0,	 0	 },
		.ddr_rfc_type = DDR_RFC_TYPE_LPDDR4_8Gbx1,
		.ddr_base_addr = CFG_DDR_BASE_ADDR,
		.ddr_start_offset = CFG_DDR_START_OFFSET,
		.DisabledDbyte[0] = 0xf0,                       //bit 0 -3 ch0 cs0 ,bit 4-7 ch0 cs1,
		.DisabledDbyte[1] = 0xf0,                       //bit 0 -3 ch1 cs0 ,bit 4-7 ch1 cs1,
		.Is2Ttiming = 0,
		.HdtCtrl = 0xc8,
		//.dram_ch0_size_MB		= 0xffff,
		//.dram_ch1_size_MB		= 0,
		.dram_ch0_size_MB =
			(DRAM_SIZE_ID_256MBX2 << CONFIG_CS0_BYTE_01_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX2 << CONFIG_CS0_BYTE_23_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX0 << CONFIG_CS1_BYTE_01_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX0 << CONFIG_CS1_BYTE_01_SIZE_256_ID_OFFSET),
		.dram_ch1_size_MB =
			(DRAM_SIZE_ID_256MBX2 << CONFIG_CS0_BYTE_01_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX2 << CONFIG_CS0_BYTE_23_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX0 << CONFIG_CS1_BYTE_01_SIZE_256_ID_OFFSET) +
			(DRAM_SIZE_ID_256MBX0 << CONFIG_CS1_BYTE_01_SIZE_256_ID_OFFSET),
		.training_SequenceCtrl ={ 0x131f,		    0x61 },     //ddr3 0x21f 0x31f
		.phy_odt_config_rank ={ 0x23,			  0x13 }, //use 0x23 0x13  compatibility with 1rank and 2rank //targeting rank 0. [3:0] is used //for write ODT [7:4] is used for //read ODT
		.dfi_odt_config = 0x0d0d,               //use 0d0d compatibility with 1rank and 2rank  //0808
		.PllBypassEn = 0,                       //bit0-ps0,bit1-ps1
		.ddr_rdbi_wr_enable = 0x0,              //bit 0 read-dbi,bit 1 write dbi
		.clk_drv_ohm = 40,
		.cs_drv_ohm = 40,
		.ac_drv_ohm = 40,
		.soc_data_drv_ohm_p = 40,
		.soc_data_drv_ohm_n = 40,
		.soc_data_odt_ohm_p = 0,
		.soc_data_odt_ohm_n = 60,
		.dram_data_drv_ohm = 40,                //48, //34, //ddr4 sdram only 34 or 48, skt board use 34 better
		.dram_data_odt_ohm = 60,                //60,
		.dram_ac_odt_ohm = 255,
		.soc_clk_slew_rate = 0x3ff,
		.soc_cs_slew_rate = 0x3ff,
		.soc_ac_slew_rate = 0x3ff,
		.soc_data_slew_rate = 0x2ff,
		.vref_output_permil = 000,
		.vref_receiver_permil = 0,
		.vref_dram_permil = 0,
		//.vref_reverse			= 0,
		//.ac_trace_delay			={0x0,0x0},// {0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40},
		.ac_trace_delay ={ 32 + 0,		     32 + 0, 32 + 0, 32 + 0, 32, 32 + 0, 32 + 0, 32 + 0, 32 + 0, 32 + 0},
		.ddr_dmc_remap					=
		{
			[0] = (5 | 6 << 5 | 7 << 10 | 8 << 15 | 9 << 20 | 10 << 25),
			[1] = (11 | 0 << 5 | 0 << 10 | 15 << 15 | 16 << 20 | 17 << 25),
			[2] = (18 | 19 << 5 | 20 << 10 | 21 << 15 | 22 << 20 | 23 << 25),
			[3] = (24 | 25 << 5 | 26 << 10 | 27 << 15 | 28 << 20 | 29 << 25),
			[4] = (30 | 12 << 5 | 13 << 10 | 14 << 15 | 0 << 20 | 0 << 25),
		},
		.ddr_lpddr34_ca_remap				= { 00,			00 },
		.ddr_lpddr34_dq_remap				= { 4,6,5, 0, 7, 1, 2, 3,
			15, 11, 13, 14, 12, 9, 8, 10,
			21, 19, 22, 16, 18, 17, 23,20,
			29, 30, 26, 25, 24, 27, 31, 28},
		.dram_rtt_nom_wr_park ={ 00,			   00 },

		/* pll ssc config:
		 *
		 *   pll_ssc_mode = (1<<20) | (1<<8) | ([strength] << 4) | [mode],
		 *      ppm = strength * 500
		 *      mode: 0=center, 1=up, 2=down
		 *
		 *   eg:
		 *     1. config 1000ppm center ss. then mode=0, strength=2
		 *        .pll_ssc_mode = (1<<20) | (1<<8) | (2 << 4) | 0,
		 *     2. config 3000ppm down ss. then mode=2, strength=6
		 *        .pll_ssc_mode = (1<<20) | (1<<8) | (6 << 4) | 2,
		 */
		//.pll_ssc_mode			= (1<<20) | (1<<8) | (2<<4) | 0,//center_ssc_1000ppm
		.ddr_func = 0,                          // DDR_FUNC,
		.magic = DRAM_CFG_MAGIC,
		.slt_test_function ={ 0x0,			0x0 }, //{0x1,0x0},enable slt 4 DRAMFreq test;{0x0,0x0},disable slt 4 DRAMFreq test;
		.fast_boot[0] = 0,
		.ac_pinmux = {2,3,1,0,5,4,0,0,0,0,
			1,3,5,2,4,0,0,0,0  },

		.dfi_pinmux =
		{
			1,
			2,
			3,
			4,
			5,
			6,
			7,
			8,
			0,
			10,
			11,
			12,
			13,
			14,
			15,
			16,
			17,
			18,
			19,
			20,
			21,
			22,
			23,
			0,
			0,
			0,
		},
	},
};

board_clk_set_t __board_clk_setting
__attribute__ ((section(".clk_param"))) = {
	/* clock settings for bl2 */
	.cpu_clk				= CPU_CLK / 24 * 24,
	.dsu_clk				= DSU_CLK / 24 * 24,
#ifdef CONFIG_PXP_EMULATOR
	.pxp					= 1,
#else
	.pxp					= 0,
#endif
	.high_console_baud = CONFIG_HIGH_CONSOLE_BAUD,
};


#define VCCK_VAL				AML_VCCK_INIT_VOLTAGE
#define VDDEE_VAL				AML_VDDEE_INIT_VOLTAGE
/* VCCK PWM table */
#if   (VCCK_VAL == 1039)
	#define VCCK_VAL_REG	0x00000022
#elif (VCCK_VAL == 1029)
	#define VCCK_VAL_REG	0x00010021
#elif (VCCK_VAL == 1019)
	#define VCCK_VAL_REG	0x00020020
#elif (VCCK_VAL == 1009)
	#define VCCK_VAL_REG	0x0003001f
#elif (VCCK_VAL == 999)
	#define VCCK_VAL_REG	0x0004001e
#elif (VCCK_VAL == 989)
	#define VCCK_VAL_REG	0x0005001d
#elif (VCCK_VAL == 979)
	#define VCCK_VAL_REG	0x0006001c
#elif (VCCK_VAL == 969)
	#define VCCK_VAL_REG	0x0007001b
#elif (VCCK_VAL == 959)
	#define VCCK_VAL_REG	0x0008001a
#elif (VCCK_VAL == 949)
	#define VCCK_VAL_REG	0x00090019
#elif (VCCK_VAL == 939)
	#define VCCK_VAL_REG	0x000a0018
#elif (VCCK_VAL == 929)
	#define VCCK_VAL_REG	0x000b0017
#elif (VCCK_VAL == 919)
	#define VCCK_VAL_REG	0x000c0016
#elif (VCCK_VAL == 909)
	#define VCCK_VAL_REG	0x000d0015
#elif (VCCK_VAL == 899)
	#define VCCK_VAL_REG	0x000e0014
#elif (VCCK_VAL == 889)
	#define VCCK_VAL_REG	0x000f0013
#elif (VCCK_VAL == 879)
	#define VCCK_VAL_REG	0x00100012
#elif (VCCK_VAL == 869)
	#define VCCK_VAL_REG	0x00110011
#elif (VCCK_VAL == 859)
	#define VCCK_VAL_REG	0x00120010
#elif (VCCK_VAL == 849)
	#define VCCK_VAL_REG	0x0013000f
#elif (VCCK_VAL == 839)
	#define VCCK_VAL_REG	0x0014000e
#elif (VCCK_VAL == 829)
	#define VCCK_VAL_REG	0x0015000d
#elif (VCCK_VAL == 819)
	#define VCCK_VAL_REG	0x0016000c
#elif (VCCK_VAL == 809)
	#define VCCK_VAL_REG	0x0017000b
#elif (VCCK_VAL == 799)
	#define VCCK_VAL_REG	0x0018000a
#elif (VCCK_VAL == 789)
	#define VCCK_VAL_REG	0x00190009
#elif (VCCK_VAL == 779)
	#define VCCK_VAL_REG	0x001a0008
#elif (VCCK_VAL == 769)
	#define VCCK_VAL_REG	0x001b0007
#elif (VCCK_VAL == 759)
	#define VCCK_VAL_REG	0x001c0006
#elif (VCCK_VAL == 749)
	#define VCCK_VAL_REG	0x001d0005
#elif (VCCK_VAL == 739)
	#define VCCK_VAL_REG	0x001e0004
#elif (VCCK_VAL == 729)
	#define VCCK_VAL_REG	0x001f0003
#elif (VCCK_VAL == 719)
	#define VCCK_VAL_REG	0x00200002
#elif (VCCK_VAL == 709)
	#define VCCK_VAL_REG	0x00210001
#elif (VCCK_VAL == 699)
	#define VCCK_VAL_REG	0x00220000
#else
	#error "VCCK val out of range\n"
#endif

/* VDDEE_VAL_REG */
#if    (VDDEE_VAL == 710)
	#define VDDEE_VAL_REG	0x120000
#elif (VDDEE_VAL == 720)
	#define VDDEE_VAL_REG	0x110001
#elif (VDDEE_VAL == 730)
	#define VDDEE_VAL_REG	0x100002
#elif (VDDEE_VAL == 740)
	#define VDDEE_VAL_REG	0xf0003
#elif (VDDEE_VAL == 750)
	#define VDDEE_VAL_REG	0xe0004
#elif (VDDEE_VAL == 760)
	#define VDDEE_VAL_REG	0xd0005
#elif (VDDEE_VAL == 770)
	#define VDDEE_VAL_REG	0xc0006
#elif (VDDEE_VAL == 780)
	#define VDDEE_VAL_REG	0xb0007
#elif (VDDEE_VAL == 790)
	#define VDDEE_VAL_REG	0xa0008
#elif (VDDEE_VAL == 800)
	#define VDDEE_VAL_REG	0x90009
#elif (VDDEE_VAL == 810)
	#define VDDEE_VAL_REG	0x8000a
#elif (VDDEE_VAL == 820)
	#define VDDEE_VAL_REG	0x7000b
#elif (VDDEE_VAL == 830)
	#define VDDEE_VAL_REG	0x6000c
#elif (VDDEE_VAL == 840)
	#define VDDEE_VAL_REG	0x5000d
#elif (VDDEE_VAL == 850)
	#define VDDEE_VAL_REG	0x4000e
#elif (VDDEE_VAL == 860)
	#define VDDEE_VAL_REG	0x3000f
#elif (VDDEE_VAL == 870)
	#define VDDEE_VAL_REG	0x20010
#elif (VDDEE_VAL == 880)
	#define VDDEE_VAL_REG	0x10011
#elif (VDDEE_VAL == 890)
	#define VDDEE_VAL_REG	0x12
#else
	#error "VDDEE val out of range\n"
#endif

bl2_reg_t __bl2_reg[] __attribute__ ((section(".generic_param"))) = {
	//hxbao, need fine tune
	{0,			0,            		0xffffffff,   0, 0, 0},
};

/* gpio/pinmux/pwm init */
register_ops_t __bl2_ops_reg[MAX_REG_OPS_ENTRIES]
__attribute__ ((section(".misc_param"))) = {

	/*config vddee and vcck pwm - pwm_a and pwm_b*/
	/* PWM_A VDDEE_VAL_REG */
	{PWMAB_PWM_A,		VDDEE_VAL_REG,  	0xffffffff,	0, 0, 0},
	/* PWM_B VCCK_VAL_REG */
	{PWMAB_PWM_B,		VCCK_VAL_REG,  		0xffffffff,	0, 0, 0},
	{PWMAB_MISC_REG_AB,	(0x3 << 0), 		(0x3 << 0), 	0, 0, 0},
	/* enable vddcpu dc-dc, set TEST_N to high */
	{PADCTRL_TESTN_O,	(0x1 << 0), 		(0x1 << 0),	0, 0, 0},
	{PADCTRL_TESTN_OEN,	(0x0 << 0), 		(0x1 << 0), 0, 0, 0},
	/*enable pin,set gpiod_4,enable vddcpu*/
	{PADCTRL_GPIOD_O,	(0x1 << 4),		(0x1 << 4),	0, 0, 0},
	{PADCTRL_GPIOD_OEN,	(0x0 << 4),		(0x1 << 4),	0, 0, 0},
	/* set pwm a and pwm b clock rate to 24M, enable them */
	{CLKCTRL_PWM_CLK_AB_CTRL,((0x1 << 8) | (0x1 << 24)),0xffffffff,0,0, 0},
	/* set GPIOE_0 GPIOE_1 drive strength to 3 */
	{PADCTRL_GPIOE_DS,	0xf, 	0xf,		0, 0, 0},
	/* set GPIOE_0 GPIOE_1 mux to pwma pwmb */
	{PADCTRL_PIN_MUX_REGD,	(0x1 << 0),		(0xf << 0),	0, 0, 0},
	{PADCTRL_PIN_MUX_REGD,	(0x1 << 4),		(0xf << 4),	0, 0, 0},
};

/* for all the storage parameter */
storage_parameter_t __store_para __attribute__ ((section(".store_param"))) = {
	.common				= {
		.version = 0x01,
		.device_fip_container_size = 0x300000,
		.device_fip_container_copies = 4,
	},
	.nand				= {
		.version = 0x01,
		.bbt_pages = 0x1,
		.bbt_start_block = 0x20,
		.discrete_mode = 1,
		.setup_data.nand_setup_data = (2 << 20) |		\
					(0 << 19) |                     \
					(1 << 17) |                     \
					(4 << 14) |                     \
					(0 << 13) |                     \
					(64 << 6) |                     \
					(4 << 0),
		.reserved_area_blk_cnt = 48,
		.page_per_block = 128,
		.use_param_page_list = 0,
	},
};