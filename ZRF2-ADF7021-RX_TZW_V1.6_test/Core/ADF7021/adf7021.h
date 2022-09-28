/*
 * Copyright (c) 2008 Johan Christiansen
 * Copyright (c) 2012 Jeppe Ledet-Pedersen <jlp@satlab.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _ADF7021_H_
#define _ADF7021_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32l1xx_hal.h"
#include "cmsis_os.h"

#define ADF_IDLE_MODE		2
#define ADF_TX_MODE		1
#define ADF_RX_MODE		0
void Init_periph(uint8_t Mode);

#define SCKU_Pin GPIO_PIN_10
#define SCKU_GPIO_Port GPIOB
#define SCKU_EXTI_IRQn EXTI15_10_IRQn

#define SWD_Pin GPIO_PIN_0
#define SWD_GPIO_Port GPIOB
#define SWD_EXTI_IRQn EXTI0_IRQn

#define URTX_Pin GPIO_PIN_11
#define URTX_GPIO_Port GPIOB

#define PREAMBLE_MODE 1
#define STARTSTOP_MODE 2
#define PACKET_MODE 3
#define PACKET_IDLE_MODE 4


#pragma pack(1)

typedef union
{
	unsigned long whole_reg;
	struct {
		unsigned int lower;
		unsigned int upper;
	} word;
	unsigned char byte[4];
} adf_reg_t;

typedef struct {
	struct {
		double deviation;
		double data_rate;
		double mod_index;
		unsigned long freq;
	} desired;
	struct {
		double data_rate;
		double mod_index;
		unsigned long freq;
		unsigned int freq_dev;
	} real;
	union {
		adf_reg_t r0_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned int  frac_n : 15;
			unsigned int  int_n : 8;
			unsigned char rx_on : 1;
			unsigned char uart_mode : 1;
			unsigned char muxout : 3;
		} r0;
	};
	union {
		adf_reg_t r2_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned char modulation_scheme : 3;
			unsigned char pa_enable : 1;
			unsigned char pa_ramp : 3;
			unsigned char pa_bias : 2;
			unsigned char power_amplifier : 6;
			unsigned int  tx_frequency_deviation : 9;
			unsigned char tx_data_invert : 2;
			unsigned char rcosine_alpha : 1;
		} r2;
	};
	union {
		adf_reg_t r3_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned char bbos_clk_divide: 2;
			unsigned char dem_clk_divide : 4;
			unsigned char cdr_clk_divide : 8;
			unsigned char seq_clk_divide : 8;
			unsigned char agc_clk_divide : 6;
		} r3;
	};
	union {
		adf_reg_t r4_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned char demod_scheme : 3;
			unsigned char dot_product : 1;
			unsigned char rx_invert : 2;
			unsigned int  disc_bw : 10;
			unsigned int  post_demod_bw : 10;
			unsigned char if_bw : 2;
		} r4;
	};
	union {
		adf_reg_t r5_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned char if_cal_coarse : 1;
			unsigned int  if_filter_divider : 9;
			unsigned char if_filter_adjust : 6;
			unsigned char ir_phase_adjust_mag : 4;
			unsigned char ir_phase_adjust_direction : 1;
			unsigned char ir_gain_adjust_mac : 5;
			unsigned char ir_gain_adjust_iq : 1;
			unsigned char ir_gain_adjust_updn : 1;
		} r5;
	};
	union {
		adf_reg_t r6_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned char if_fine_cal : 1;
			unsigned char if_cal_lower_tone : 8;
			unsigned char if_cal_upper_tone : 8;
			unsigned char if_cal_dwell_time : 7;
			unsigned char ir_cal_source_drive : 2;
			unsigned char ir_cal_source_div_2 : 1;
		} r6;
	};
	union {
		adf_reg_t r8_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned char Synth_en : 1;
			unsigned char Reserv : 1;
			unsigned char Lna_mix_en : 1;
			unsigned char Filter_en : 1;
			unsigned char ADC_en : 1;
			unsigned char Demod_en : 1;
			unsigned char Log_amp_en : 1;
			unsigned char TxRx_en : 1;
			unsigned char Pa_en : 1;
			unsigned char Rx_reset : 2;
			unsigned char Cnt_reset : 1;

		} r8;
	};
} adf_conf_t;

typedef struct {
	unsigned long adf_xtal;
	union {
		adf_reg_t r1_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned char r_counter : 3;
			unsigned char clockout_divide : 4;
			unsigned char xtal_doubler : 1;
			unsigned char xosc_enable : 1;
			unsigned char xtal_bias : 2;
			unsigned char cp_current : 2;
			unsigned char vco_enable : 1;
			unsigned char rf_divide_by_2 : 1;
			unsigned char vco_bias : 4;
			unsigned char vco_adjust : 2;
			unsigned char vco_inductor : 1;
		} r1;
	};
	union {
		adf_reg_t r10_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned char afc_en : 1;
			unsigned int  afc_scaling_factor : 12;
			unsigned char ki : 4;
			unsigned char kp : 3;
			unsigned char afc_range : 8;
		} r10;
	};
	union {
		adf_reg_t r12_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned char lock_thres_mode : 2;
			unsigned char swd_mode : 2;
			unsigned char packet_length : 8;
		} r12;
	};
	union {
		adf_reg_t r14_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned char test_tdac_en : 1;
			unsigned int test_dac_offset : 16;
			unsigned char test_dac_gain : 4;
			unsigned char pulse_ext : 2;
			unsigned char leak_factor : 3;
			unsigned char ed_peak_resp : 2;
		} r14;
	};
	union {
		adf_reg_t r15_reg;
		struct {
			unsigned char address_bits : 4;
			unsigned char rx_test_mode : 4;
			unsigned char tx_test_mode : 3;
			unsigned char sd_test_mode : 3;
			unsigned char cp_test_mode : 3;
			unsigned char clk_mux : 3;
			unsigned char pll_test_mode : 4;
			unsigned char analog_test_mode : 4;
			unsigned char force_ld_high : 1;
			unsigned char reg1_pd : 1;
			unsigned char cal_override : 2;
		} r15;
	};
} adf_sysconf_t;

void adf_write_reg(adf_reg_t *reg);
adf_reg_t adf_read_reg(unsigned int readback_config);

void adf_set_power_on(unsigned long adf_xtal);
void adf_set_power_off(void);

uint32_t adf_init_rx_mode(unsigned int data_rate, uint8_t mod_index, unsigned long freq, uint8_t if_bw);
uint32_t adf_init_tx_mode(unsigned int data_rate, uint8_t mod_index, unsigned long freq);
void adf_set_rx_mode(void);
void adf_set_tx_mode(void);

void adf_afc_on(unsigned char range, unsigned char ki, unsigned char kp);
void adf_afc_off(void);
void adf_set_tx_power(char pasetting);

#define ADF_SYNC_WORD_LEN_12	        0
#define ADF_SYNC_WORD_LEN_16	        1
#define ADF_SYNC_WORD_LEN_20	        2
#define ADF_SYNC_WORD_LEN_24	        3

#define ADF_SYNC_WORD_ERROR_TOLERANCE_0	0
#define ADF_SYNC_WORD_ERROR_TOLERANCE_1	1
#define ADF_SYNC_WORD_ERROR_TOLERANCE_2	2
#define ADF_SYNC_WORD_ERROR_TOLERANCE_3	3

void adf_set_rx_sync_word(unsigned long word, unsigned char len, unsigned char error_tolerance);
void adf_set_threshold_free(void);

#define ADF_TEST_TX_MODE_CARRIER_ONLY	1
#define ADF_TEST_TX_MODE_TONE_HIGH	2
#define ADF_TEST_TX_MODE_TONE_LOW	3
#define ADF_TEST_TX_MODE_PATTERN_1010	4
#define ADF_TEST_TX_MODE_PATTERN_PN9	5
#define ADF_TEST_TX_MODE_SYNC_BYTE	6

void adf_test_tx(int mode);
void adf_test_off(void);

unsigned int adf_readback_version(void);
signed int adf_readback_rssi(void);
signed int adf_readback_afc(void);
signed int adf_readback_temp(void);
float adf_readback_voltage(void);
void adf_configure(void);
void adf_reset(void);
void adf_simple_init();

void set_channel(uint8_t CH,uint8_t TX_MODE);
void set_power(uint8_t PW);
uint8_t SEND_PACKET(uint8_t *PACKET, uint16_t Size, uint8_t Channel);
uint8_t REC_PACKET(uint16_t Size, uint8_t Channel, uint16_t timeout, uint8_t Search_EN);


#define CH_ARR_DIM 8	//wielkość tabeli kanałów

void Set_GP_OUT();
void Set_GP_IN();

uint8_t arr_chk_bit(uint8_t * const tab, const uint16_t bit);
void arr_set_bit(uint8_t * const tab, const uint16_t bit);
void arr_clr_bit(uint8_t * const tab, const uint16_t bit);

typedef struct {
	uint32_t TX[CH_ARR_DIM];
	uint32_t RX[CH_ARR_DIM];

} _ADF_Channels;











#endif /* _ADF7021_H_ */












/*

// reg 1


outreg=0x00575011;

// reg 3
outreg=0x2B1480A3;

// reg 2

outreg=0x1160be80;

// reg 5
outreg=0x00003155;

// reg 4
outreg=0x80556214;

// reg 6
outreg=0x050A4F66;

// reg 9
outreg=0x002231E9;
*/
