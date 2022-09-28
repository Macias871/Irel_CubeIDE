
#include "stm32l1xx_hal.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "adf7021_Config.h"
#include "../threads/variables.h"
#include <math.h>


#include "adf7021.h"

extern UART_HandleTypeDef huart3;
static adf_conf_t rx_conf, tx_conf;
static adf_sysconf_t sys_conf;
static uint32_t adf_current_syncword;
static uint8_t ADF_TX_POWER=63;
extern struct RF_config conf;
//extern FlagStatus xTxDoneFlag;

_ADF_Channels ADF_Channels;

adf_reg_t Actual_R0_value;

GPIO_InitTypeDef GPIO_InitStruct = {0};

enum {
	ADF_OFF,
	ADF_ON,
	ADF_TX,
	ADF_RX
} adf_state;

enum {
	ADF_PA_OFF,
	ADF_PA_ON
} adf_pa_state;



void Init_periph(uint8_t Mode)
{


	  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
	  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);


	  if(Mode == ADF_TX_MODE){

	  }
	  if(Mode == ADF_RX_MODE){

	  }


}

volatile uint8_t SLE_FLAG = 0;



volatile uint32_t temp[10];
volatile uint8_t cnt = 0;

#define sdata_bit_time 1
void adf_write_reg(adf_reg_t *reg)
{
	temp[cnt] = reg->whole_reg;

	if(cnt < 10)
	{
	cnt++;
	}
	else
	{
		cnt = 0;

	}

	signed char i, j;
	unsigned char byte;

	HAL_GPIO_WritePin(SLE_GPIO_Port, SLE_Pin, 0);
	HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, 0);

	for(uint16_t i=0; i<100; i++)
		asm("NOP");

	/* Clock data out MSbit first */
	for (i=3; i>=0; i--) {
		byte = reg->byte[i];
		for(uint16_t i=0; i<sdata_bit_time; i++){asm("NOP");}

		for (j=8; j>0; j--) {
			HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, 0);
			if (byte & 0x80){
				HAL_GPIO_WritePin(SDATA_GPIO_Port, SDATA_Pin,1);
				for(uint16_t i=0; i<sdata_bit_time; i++){asm("NOP");}
			}
			else {
				HAL_GPIO_WritePin(SDATA_GPIO_Port, SDATA_Pin,0);
				for(uint16_t i=0; i<sdata_bit_time; i++){asm("NOP");}

			}
			HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, 1);
			byte += byte;

		}
		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, 0);
	}

	/* Strobe the latch */

	HAL_GPIO_WritePin(SLE_GPIO_Port, SLE_Pin, 1);




	for(uint16_t i=0; i<4; i++)
		asm("NOP");
	HAL_GPIO_WritePin(SDATA_GPIO_Port, SDATA_Pin,0);
	HAL_GPIO_WritePin(SLE_GPIO_Port, SLE_Pin, 0);


}

adf_reg_t adf_read_reg(unsigned int readback_config)
{
	adf_reg_t register_value;
	signed char i, j;

	/* Write readback and ADC control value */
	register_value.whole_reg = ((readback_config & 0x1F) << 4);

	/* Address the readback setup register */
	register_value.whole_reg |= 7; 
	adf_write_reg(&register_value);
	register_value.whole_reg = 0;

	/* Read back value */
	HAL_GPIO_WritePin(SDATA_GPIO_Port, SDATA_Pin,0);
	HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, 0);
	HAL_GPIO_WritePin(SLE_GPIO_Port, SLE_Pin, 1);


	/* Clock in first bit and discard (DB16 is not used) */
	HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, 1);
	unsigned char byte = 0;
	HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, 0);

	/* Clock in data MSbit first */
	for (i=1; i>=0; i--) {
		for (j=8; j>0; j--) {
			HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, 1);
			byte += byte;
			if (HAL_GPIO_ReadPin(SREAD_GPIO_Port, SREAD_Pin))
				byte |= 1;
			HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, 0);
		}
		register_value.byte[i] = byte;
	}

	HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, 1);
	HAL_GPIO_WritePin(SLE_GPIO_Port, SLE_Pin, 0);
	HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, 0);

	return register_value;
}

void adf_set_power_on(unsigned long adf_xtal)
{
	/* Store locally the oscillator frequency */
	sys_conf.adf_xtal = adf_xtal;
	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, 1);

	for(uint16_t i=0; i<500; i++)
		asm("NOP");

	/* Ensure the ADF GPIO port is correctly initialised */


	/* write R1, Turn on Internal VCO */
	sys_conf.r1.address_bits 	= 1;
	sys_conf.r1.r_counter 		= 1;
	sys_conf.r1.clockout_divide 	= 0;
	sys_conf.r1.xtal_doubler 	= 0;
	sys_conf.r1.xosc_enable 	= 1;
	sys_conf.r1.xtal_bias 		= 2;
	sys_conf.r1.cp_current 		= 2;
	sys_conf.r1.vco_enable 		= 1;
	sys_conf.r1.rf_divide_by_2	= 1;
	sys_conf.r1.vco_bias 		= 8;
	sys_conf.r1.vco_adjust 		= 0;
	sys_conf.r1.vco_inductor 	= 0;
	adf_write_reg(&sys_conf.r1_reg);
/*
	// write R15, set CLK_MUX to enable SPI
	sys_conf.r15.address_bits 	= 15;
	sys_conf.r15.rx_test_mode  	= 0;
	sys_conf.r15.tx_test_mode 	= 0;
	sys_conf.r15.sd_test_mode 	= 0;
	sys_conf.r15.cp_test_mode 	= 0;
	sys_conf.r15.clk_mux 		= 7;
	sys_conf.r15.pll_test_mode 	= 0;
	sys_conf.r15.analog_test_mode 	= 0;
	sys_conf.r15.force_ld_high 	= 0;
	sys_conf.r15.reg1_pd 		= 0;
	sys_conf.r15.cal_override 	= 0;
	adf_write_reg(&sys_conf.r15_reg);

	// write R14, enable test DAC
	sys_conf.r14.address_bits	= 14;
	sys_conf.r14.test_tdac_en 	= 0;
	sys_conf.r14.test_dac_offset 	= 0;
	sys_conf.r14.test_dac_gain 	= 0;
	sys_conf.r14.pulse_ext 		= 0;
	sys_conf.r14.leak_factor 	= 0;
	sys_conf.r14.ed_peak_resp 	= 0;
	adf_write_reg(&sys_conf.r14_reg);
*/
	adf_state = ADF_ON;
	adf_pa_state = ADF_PA_OFF;
}

void adf_set_power_off()
{
	/* Turn off chip enable */
	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, 0);

	adf_state = ADF_OFF;
	adf_pa_state = ADF_PA_OFF;


}

void adf_find_clocks(adf_conf_t *conf)
{
	/* Find desired F.dev. */
	conf->desired.deviation = DEVIATION;
	//unsigned char tx_freq_dev = ((unsigned char) round( ((double)conf->desired.mod_index * 0.5 * conf->desired.data_rate * 65536.0) / (0.5 * sys_conf.adf_xtal))); // / 1.33333;
	unsigned char tx_freq_dev = ((unsigned char) round( ((double)1  * conf->desired.deviation * 65536.0) / (0.5 * sys_conf.adf_xtal))); // / 1.33333;

	double freq_dev = 0.5 * (tx_freq_dev * sys_conf.adf_xtal) / 65536.0;


	/* Find K */
	unsigned int k = round(100000 / (freq_dev));


	/* Run a variable optimisation for Demod clock divider */
	int i_dem;
	int w_residual = INT16_MAX, residual;

	double demod_clk, data_rate_real;
	unsigned int cdr_clk_divide, disc_bw;

	for (i_dem = 1; i_dem < 15; i_dem++) {
		demod_clk = (double) sys_conf.adf_xtal / i_dem;
		disc_bw = round((k * demod_clk) / 400000);
		cdr_clk_divide = round(demod_clk / ((double)conf->desired.data_rate * 32));

		if (disc_bw > 660)
			continue;

		if (cdr_clk_divide > 255)
			continue;

		data_rate_real = (sys_conf.adf_xtal / ((double) i_dem * (double) cdr_clk_divide * 32.0));
		residual = abs((unsigned int) data_rate_real - conf->desired.data_rate);

		/* Search for a new winner */
		if (w_residual > residual) {
			w_residual = residual;
			conf->r3.dem_clk_divide = i_dem;


		}
	}

	/* Demodulator clock */
	demod_clk = (double) sys_conf.adf_xtal / conf->r3.dem_clk_divide;

	/* CDR clock */
	conf->r3.cdr_clk_divide = (unsigned int) round(demod_clk / ((double)conf->desired.data_rate * 32));

	/* Data rate and freq. deviation */
	conf->real.data_rate = (sys_conf.adf_xtal / ((double) conf->r3.dem_clk_divide * (double) conf->r3.cdr_clk_divide * 32.0));
	conf->real.freq_dev = (unsigned char) round( ((double)1 * conf->desired.deviation * 65536.0) / (0.5 * sys_conf.adf_xtal));

	/* Discriminator bandwidth */
	conf->r4.disc_bw = round((k * demod_clk) / 400000);

	/* Post demodulation bandwidth */
	conf->r4.post_demod_bw = round(((conf->real.data_rate * 0.75) * 3.141592654 * 2048.0) / demod_clk);

	/* K odd or even */



	if (k & 1) { 
		if (((k + 1) / 2) & 1) {
			conf->r4.rx_invert = 2;
			conf->r4.dot_product = 1;
		} else {
			conf->r4.rx_invert = 0;
			conf->r4.dot_product = 1;
		}
	} else {
		if ((k / 2) & 1) {
			conf->r4.rx_invert = 2;
			conf->r4.dot_product = 0;
		} else {
			conf->r4.rx_invert = 0;
			conf->r4.dot_product = 0;
		}
	}

}

uint32_t  adf_init_rx_mode(unsigned int data_rate, uint8_t mod_index, unsigned long freq, uint8_t if_bw)
{
	/* Calculate the RX clocks */
	rx_conf.desired.data_rate = data_rate;
	rx_conf.desired.mod_index = mod_index;
	rx_conf.desired.freq = freq;
	adf_find_clocks(&rx_conf);

	/* Setup RX Clocks */
	if((sys_conf.adf_xtal / 100000.0)>=255)
	{
		rx_conf.r3.seq_clk_divide = 255;
	}
	else
	{
		rx_conf.r3.seq_clk_divide = round(sys_conf.adf_xtal / 100000.0);
	}


	rx_conf.r3.agc_clk_divide = round((sys_conf.adf_xtal/rx_conf.r3.seq_clk_divide) / 10000.0);
	rx_conf.r3.bbos_clk_divide = 2; // 16
	rx_conf.r3.address_bits = 3;


	/* IF filter calibration */
	if((sys_conf.adf_xtal / 50000) >= 511)
	{
		rx_conf.r5.if_filter_divider = 511;
	}
	else
	{
	rx_conf.r5.if_filter_divider = (sys_conf.adf_xtal / 50000);
	}
	rx_conf.r5.if_cal_coarse = 1;
	rx_conf.r5.address_bits = 5;

	/* write R0, turn on PLL */
	double n = ((freq-100000) / (sys_conf.adf_xtal * 0.5));
	unsigned long n_int = floor(n);
	unsigned long n_frac = round((n - floor(n)) * 32768);

	rx_conf.r0.rx_on = 1;
	rx_conf.r0.uart_mode = 0;
	rx_conf.r0.muxout = 2;
	rx_conf.r0.int_n = n_int;
	rx_conf.r0.frac_n = n_frac;
	rx_conf.r0.address_bits = 0;

	/* write R4, turn on demodulation */
	rx_conf.r4.demod_scheme = DEMOD_SCHEME;// 1;	//Corelator
	rx_conf.r4.if_bw = if_bw;	// 0 = 12.5, 1 = 18.75, 2 = 25 KHz
	rx_conf.r4.address_bits = 4;

	return rx_conf.r0_reg.whole_reg;


}









uint32_t  adf_init_tx_mode(unsigned int data_rate, uint8_t mod_index, unsigned long freq)
{
	/* Calculate the RX clocks */
	tx_conf.desired.data_rate = data_rate;
	tx_conf.desired.mod_index = mod_index;
	tx_conf.desired.freq = freq;
	adf_find_clocks(&tx_conf);

	/* Setup default R3 values */
	if((sys_conf.adf_xtal / 100000.0)>=255)
	{
		tx_conf.r3.seq_clk_divide = 255;
	}
	else
	{
		tx_conf.r3.seq_clk_divide = round(sys_conf.adf_xtal / 100000.0);
	}

	tx_conf.r3.agc_clk_divide = round((tx_conf.r3.seq_clk_divide * sys_conf.adf_xtal) / 10000.0);
	tx_conf.r3.bbos_clk_divide = 2; // 16
	tx_conf.r3.address_bits = 3;

	/* write R0, turn on PLL */
	double n = (freq / (sys_conf.adf_xtal * 0.5));
	unsigned long n_int = floor(n);
	unsigned long n_frac = round((n - floor(n)) * 32768);

	tx_conf.r0.rx_on = 0;
	tx_conf.r0.uart_mode = 0;
	tx_conf.r0.muxout = 2;
	tx_conf.r0.int_n = n_int;
	tx_conf.r0.frac_n = n_frac;
	tx_conf.r0.address_bits = 0;

	/* Set the calcualted frequency deviation */
	tx_conf.r2.tx_frequency_deviation = tx_conf.real.freq_dev;

	/* Set PA and modulation type */
	tx_conf.r2.power_amplifier = ADF_TX_POWER;    // 0 = OFF, 63 = MAX (WARNING NON LINEAR)
	tx_conf.r2.pa_bias = 2;	            // 0 = 5uA, 1 = 7uA, 2 = 9uA, 3 = 11 uA
	tx_conf.r2.pa_ramp = 0;	            // 0 = OFF, 1 = LOWEST, 7 = HIGHEST
	tx_conf.r2.pa_enable = 1;           // 0 = OFF, 1 = ON
	tx_conf.r2.modulation_scheme = MOD_INDEX;   // 0 = FSK, 1 = GFSK, 5 = RCFSK
	tx_conf.r2.address_bits = 2;



	/* Ensure rewrite of PA register */
	adf_pa_state = ADF_PA_OFF;
	return tx_conf.r0_reg.whole_reg;
}

void adf_afc_on(unsigned char range, unsigned char ki, unsigned char kp)
{
	/* write R10, turn AFC on */
	sys_conf.r10.afc_en = 1;
	sys_conf.r10.afc_scaling_factor =  (2^24 * 500) / XTAL_FREQ;
	sys_conf.r10.ki = ki;
	sys_conf.r10.kp = kp;
	sys_conf.r10.afc_range = range;
	sys_conf.r10.address_bits = 10;
	adf_write_reg(&sys_conf.r10_reg);

}

void adf_afc_off(void)
{
	sys_conf.r10.afc_en = 0;
	adf_write_reg(&sys_conf.r10_reg);
}

void adf_set_tx_power(char pasetting)
{
	tx_conf.r2.power_amplifier = pasetting;
	adf_write_reg(&tx_conf.r2_reg);
}

void adf_set_rx_sync_word(unsigned long word, unsigned char len, unsigned char error_tolerance)
{
	adf_reg_t register_value;

	/* write R11, configure sync word detect */
	adf_current_syncword = word;
	register_value.whole_reg = 11;
	register_value.whole_reg |= word << 8;
	register_value.whole_reg |= error_tolerance << 6;
	register_value.whole_reg |= len << 4;
	adf_write_reg(&register_value);

	/* write R12, start sync word detect */
	adf_set_threshold_free();
}

void adf_set_threshold_free(void)
{
	/* write R12, start sync word detect */
	sys_conf.r12.packet_length = 3;
	sys_conf.r12.swd_mode = 2;
	sys_conf.r12.lock_thres_mode = 0;
	sys_conf.r12.address_bits = 12;
	adf_write_reg(&sys_conf.r12_reg);
}

void adf_set_rx_mode(void)
{
	//HAL_GPIO_WritePin(RXTX_GPIO_Port, RXTX_Pin, 1);
	if (adf_state == ADF_TX) {
		if (rx_conf.r3_reg.whole_reg != tx_conf.r3_reg.whole_reg)
			adf_write_reg(&rx_conf.r3_reg);
		adf_write_reg(&rx_conf.r0_reg);
	} else {
		adf_write_reg(&rx_conf.r3_reg);
		adf_write_reg(&rx_conf.r5_reg);
		adf_write_reg(&rx_conf.r0_reg);
		adf_write_reg(&rx_conf.r4_reg);
	}

	//led_off(LED_TRANSMIT);
	//ptt_low(conf.ptt_delay_low);

	adf_state = ADF_RX;
}

void adf_set_tx_mode(void)
{

	//HAL_GPIO_WritePin(RXTX_GPIO_Port, RXTX_Pin, 0);
	/* Turn on PA the first time we transmit */
	if (adf_pa_state == ADF_PA_OFF) {
		adf_write_reg(&tx_conf.r2_reg);
		adf_pa_state = ADF_PA_ON;
	}

	//ptt_high(conf.ptt_delay_high);
	//led_on(LED_TRANSMIT);

	if (adf_state == ADF_RX) {
		if (rx_conf.r3_reg.whole_reg != tx_conf.r3_reg.whole_reg)
			adf_write_reg(&tx_conf.r3_reg);
		adf_write_reg(&tx_conf.r0_reg);
	} else {
		adf_write_reg(&tx_conf.r3_reg);
		adf_write_reg(&tx_conf.r0_reg);
	}

	adf_state = ADF_TX;
}

unsigned int adf_readback_version(void)
{
	adf_reg_t readback = adf_read_reg(0x1C);
	return readback.word.lower;
}

signed int adf_readback_rssi(void)
{
	unsigned char gain_correction[] = { 86, 0, 0, 0, 58, 38, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	adf_reg_t readback = adf_read_reg(0x14);

	char rssi = readback.byte[0] & 0x7F;
	int gc = (readback.word.lower & 0x780) >> 7;
	double dbm = ((rssi + gain_correction[gc]) * 0.5) - 130;

	return round(dbm);
}

int adf_readback_afc(void)
{
	adf_reg_t readback = adf_read_reg(0x10);
	return 100000 - round(readback.word.lower * ((uint32_t)XTAL_FREQ >> 18));
}

signed int adf_readback_temp(void)
{
	/* Enable ADC */
	adf_reg_t register_value;
	register_value.whole_reg = 8;
	register_value.whole_reg &= 1 << 8;

	adf_reg_t readback = adf_read_reg(0x16);
	return round(-40 + ((68.4 - (readback.byte[0] & 0x7F)) * 9.32));
}

float adf_readback_voltage(void)
{
	/* Enable ADC */
	adf_reg_t register_value;
	register_value.whole_reg = 8;
	register_value.whole_reg &= 1 << 8;
	adf_write_reg(&register_value);

	adf_reg_t readback = adf_read_reg(0x15);
	return (readback.byte[0] & 0x7F) / 21.1;
}

void adf_test_tx(int mode)
{
	adf_reg_t register_value;
	register_value.whole_reg = 15;
	register_value.whole_reg |= mode << 8;
	adf_write_reg(&register_value);
}

void adf_test_off(void)
{
	adf_reg_t register_value;
	register_value.whole_reg = 15;
	adf_write_reg(&register_value);
	adf_state = ADF_RX;
}

void adf_configure(void)
{
	adf_set_rx_sync_word(conf.sw, conf.swlen, conf.swtol);
	adf_init_tx_mode(conf.bitrate, conf.modindex, conf.tx_freq);
	adf_init_rx_mode(conf.bitrate, conf.modindex, conf.rx_freq, conf.if_bw);
	adf_afc_on(conf.afc_range, conf.afc_ki, conf.afc_kp);

}

void adf_reset(void)
{

	adf_reg_t register_value;
	uint64_t setup_freq = 0;



	adf_set_power_on(XTAL_FREQ);

	for(uint8_t pos = 0; pos < 8; pos++)
	{
		setup_freq = 434500000; //FREQUENCY + rx_cfg.fr_rx[pos]*25000;
		conf.tx_freq = setup_freq;
		conf.rx_freq = setup_freq;

		ADF_Channels.RX[pos] = adf_init_rx_mode(conf.bitrate, conf.modindex, conf.rx_freq, conf.if_bw);
		ADF_Channels.TX[pos] = adf_init_tx_mode(conf.bitrate, conf.modindex, conf.tx_freq);

	}





	//adf_write_reg(&sys_conf.r1_reg);
	adf_write_reg(&tx_conf.r3_reg);
	adf_write_reg(&rx_conf.r5_reg);
	adf_set_rx_sync_word(conf.sw, conf.swlen, conf.swtol);



	register_value.whole_reg = ADF_Channels.RX[6];
	adf_write_reg(&register_value);

	adf_write_reg(&rx_conf.r4_reg);


	register_value.whole_reg = 0x3296286A; //10
	adf_write_reg(&register_value);

	rx_conf.r8.address_bits = 8;
	rx_conf.r8.TxRx_en = 1;
	//adf_write_reg(&rx_conf.r8_reg);

	//register_value.whole_reg = 0x002231E9; //9
	//adf_write_reg(&register_value);



	Init_periph(0);

}



void adf_simple_init()
{}



volatile uint8_t LAST_Ch_direction = 0;


void set_channel(uint8_t POS_ARR, uint8_t TX_MODE)
{

	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	//HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);

		if(TX_MODE == 1)
		{


			tx_conf.r0_reg.whole_reg = ADF_Channels.TX[POS_ARR];
			adf_write_reg(&tx_conf.r0_reg);

			osDelay(1);

			Set_GP_OUT();


			GPIO_InitStruct.Pin = SCKU_Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(SCKU_GPIO_Port, &GPIO_InitStruct);

			osDelay(1);




		}
		else
		{



			  Set_GP_IN();
			  osDelay(1);
			  rx_conf.r0_reg.whole_reg = ADF_Channels.RX[POS_ARR];
			  adf_write_reg(&rx_conf.r0_reg);




				osDelay(1);


			  GPIO_InitStruct.Pin = SCKU_Pin;
			  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
			  GPIO_InitStruct.Pull = GPIO_NOPULL;
			  HAL_GPIO_Init(SCKU_GPIO_Port, &GPIO_InitStruct);



			  GPIO_InitStruct.Pin = SWD_Pin;
			  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
			  GPIO_InitStruct.Pull = GPIO_NOPULL;
			  HAL_GPIO_Init(SWD_GPIO_Port, &GPIO_InitStruct);

			  HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
			  HAL_NVIC_EnableIRQ(EXTI0_IRQn);



		}



}




static uint8_t Serial_frame[40];
uint16_t byte_counter = 0;
//uint16_t tx_byte_counter = 0;
uint16_t bit_counter = 0;
uint8_t bit_in_byte = 0;
uint16_t frame_bit_lenght = 0;
static uint8_t Frame_byte_lenght = 0;
uint8_t serial_uart_seq = 1;
uint8_t seq_reset_flag = 0;
uint8_t first_bad_pre = 0;
uint8_t start_stop_bits = 0;

volatile uint8_t Actual_packet_mode = 0;
volatile uint8_t Actual_radio_mode = 0;
volatile uint8_t last_adf_state =0xff;



uint8_t SEND_PACKET(uint8_t *PACKET, uint16_t Size, uint8_t Channel)
{

	Actual_radio_mode = ADF_IDLE_MODE;

	if(last_adf_state != ADF_TX_MODE)
	{
	set_channel(Channel, ADF_TX_MODE);
	last_adf_state = ADF_TX_MODE;
	}


	frame_bit_lenght = 8 * Size;
	Frame_byte_lenght = Size;

	//Serial_frame[0] = 0xAA;
	//Serial_frame[1] = 0xAA;
	//Serial_frame[2] = 0x55;
	//Serial_frame[3] = 0x55;
	//Serial_frame[4] = 0x55;
	//Serial_frame[5] = 0x55;
	memcpy(&Serial_frame[0],&PACKET[0],Size);




	byte_counter = 0;
	Actual_radio_mode = ADF_TX_MODE;
	Actual_packet_mode = PREAMBLE_MODE;

	xTxDoneFlag= RESET;
	while(xTxDoneFlag == RESET)
	{
		osDelay(1);
	}
	HAL_GPIO_WritePin(URTX_GPIO_Port, URTX_Pin, 1);
	osDelay(1);
	Actual_radio_mode = ADF_IDLE_MODE;
//	HAL_GPIO_WritePin(PSCK_GPIO_Port, PSCK_Pin, RESET);
	return 1;
}

volatile uint16_t timeout_counter = 0;
extern uint8_t RX_RF_Frame_out[30];
uint8_t REC_PACKET(uint16_t Size, uint8_t Channel, uint16_t timeout, uint8_t Search_EN)
{
	//HAL_GPIO_WritePin(PSCK_GPIO_Port, PSCK_Pin, RESET);
	uint8_t ret_state = 0;

	memset(&Serial_frame[0],0,Size);

	timeout_counter = 0;
	Actual_radio_mode = ADF_IDLE_MODE;


	if(last_adf_state != ADF_RX_MODE  )
	{
	set_channel(Channel, ADF_RX_MODE);
	last_adf_state = ADF_RX_MODE;
	}


	if(Search_EN == 1)
	{
		  for(uint16_t i=0; i<500; i++){asm("NOP");}
		  timeout = timeout *2;
		  rx_conf.r0_reg.whole_reg = ADF_Channels.RX[Channel];
		  adf_write_reg(&rx_conf.r0_reg);
		  last_adf_state = ADF_RX_MODE;
		  for(uint16_t i=0; i<500; i++){asm("NOP");}

	}

	//Init_periph(ADF_RX_MODE);
	Frame_byte_lenght = Size-2;
	uint8_t Temp_rec_frame[Size];



	//HAL_GPIO_WritePin(URTX_GPIO_Port, URTX_Pin, 1);
	Actual_radio_mode = ADF_RX_MODE;
	Actual_packet_mode = 0xFF;
	xRxDoneFlag= RESET;
	//HAL_GPIO_WritePin(PSCK_GPIO_Port, PSCK_Pin, SET);
		while(timeout_counter < timeout)
		{

		osDelay(1);
		timeout_counter++;

			if(xRxDoneFlag == SET)
			{
				timeout_counter = timeout;
				break;
			}

		}

		if(xRxDoneFlag == RESET)
		{
			ret_state = 0;
			//HAL_GPIO_WritePin(PSCK_GPIO_Port, PSCK_Pin, RESET);

		}
		else
		{
			ret_state = 1;
		}



	memset(&Temp_rec_frame[0],0,Size);
	memcpy(&RX_RF_Frame_out[0],&Serial_frame[2],Size-3);
	Actual_radio_mode = ADF_IDLE_MODE;
//	HAL_GPIO_WritePin(PSCK_GPIO_Port, PSCK_Pin, RESET);




	return ret_state;
}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
/*
	if(GPIO_Pin == MUXOUT_Pin)
	{
		RSSI = 0;//adf_readback_rssi();
	}
*/
	if(GPIO_Pin == SWD_Pin)
	{
		//HAL_GPIO_WritePin(PSCK_GPIO_Port, PSCK_Pin, SET);
		seq_reset_flag = 0;
		//bit_counter = 0;
		//bit_in_byte = 0;
		//byte_counter = 0;
		timeout_counter = 0;
		Actual_packet_mode = PREAMBLE_MODE;
	}


	if(GPIO_Pin == SCKU_Pin){
		//for(uint16_t i=0; i<200; i++){asm("NOP");}
		//HAL_GPIO_WritePin(PSCK_GPIO_Port, PSCK_Pin, SET);






		seq_reset_flag = 1;


			if(byte_counter >= Frame_byte_lenght)
			{
				byte_counter = 0;

				if(Actual_radio_mode == ADF_RX_MODE)
				{
					xRxDoneFlag = SET;

				}
				if(Actual_radio_mode == ADF_TX_MODE)
				{
					xTxDoneFlag = SET;}
				Actual_radio_mode = ADF_IDLE_MODE;
				HAL_GPIO_WritePin(URTX_GPIO_Port, URTX_Pin, 1);

			}


			if(Actual_packet_mode == PREAMBLE_MODE && Actual_radio_mode == ADF_TX_MODE && seq_reset_flag == 1)
			{

				HAL_GPIO_WritePin(URTX_GPIO_Port, URTX_Pin, 0);
				Actual_packet_mode = PACKET_MODE;
				byte_counter = 0;
				bit_in_byte = 0;
				seq_reset_flag = 0;
			}

			if(Actual_packet_mode == PREAMBLE_MODE && Actual_radio_mode == ADF_RX_MODE && seq_reset_flag == 1)
			{




				if(first_bad_pre > 1)
				{

					first_bad_pre = 0;
				bit_counter = 0;
				byte_counter = 0;
				Actual_packet_mode = PACKET_MODE;
				seq_reset_flag = 0;

				}
				else
				{
					first_bad_pre++;

				}

			}

			if(Actual_radio_mode == ADF_TX_MODE && Actual_packet_mode == PACKET_MODE  && seq_reset_flag == 1 && bit_in_byte <= 7)
			{
				if(arr_chk_bit(&Serial_frame[byte_counter],bit_in_byte))
				{
					HAL_GPIO_WritePin(URTX_GPIO_Port, URTX_Pin, 1);
				}
				else
				{
					HAL_GPIO_WritePin(URTX_GPIO_Port, URTX_Pin, 0);
				}
				bit_in_byte++;
				seq_reset_flag = 0;
			}

			if(Actual_radio_mode == ADF_RX_MODE && Actual_packet_mode == PACKET_MODE  && seq_reset_flag == 1 && bit_in_byte <= 7)
			{


				if(HAL_GPIO_ReadPin( URTX_GPIO_Port, URTX_Pin) == GPIO_PIN_SET)
				{
					arr_set_bit(&Serial_frame[byte_counter],bit_in_byte);
					//HAL_GPIO_WritePin(PSCK_GPIO_Port, PSCK_Pin, SET);
				}
				else
				{
					arr_clr_bit(&Serial_frame[byte_counter],bit_in_byte);
					//HAL_GPIO_WritePin(PSCK_GPIO_Port, PSCK_Pin, RESET);
				}
				bit_in_byte++;
				seq_reset_flag = 0;


			}

			if(bit_in_byte == 8 && Actual_packet_mode == PACKET_MODE && seq_reset_flag == 1 )
			{
				HAL_GPIO_WritePin(URTX_GPIO_Port, URTX_Pin, 1);

				bit_in_byte++;
				seq_reset_flag = 0;
			}

			if(bit_in_byte == 9 && Actual_packet_mode == PACKET_MODE && seq_reset_flag == 1 )
			{
				HAL_GPIO_WritePin(URTX_GPIO_Port, URTX_Pin, 0);

				bit_in_byte = 0;
				seq_reset_flag = 0;
				byte_counter++;
			}



		bit_counter++;
		if(bit_counter >= 400){bit_counter = 0;}

		//HAL_GPIO_WritePin(PSCK_GPIO_Port, PSCK_Pin, RESET);
	}



}


void Set_GP_OUT()
{
	HAL_GPIO_WritePin(RXTX_GPIO_Port, RXTX_Pin, 0);
	HAL_GPIO_WritePin(URTX_GPIO_Port, URTX_Pin, 1);

	GPIO_InitStruct.Pin = URTX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(URTX_GPIO_Port, &GPIO_InitStruct);
}

void Set_GP_IN()
{
	HAL_GPIO_WritePin(RXTX_GPIO_Port, RXTX_Pin, 1);
	HAL_GPIO_WritePin(URTX_GPIO_Port, URTX_Pin, 1);
	GPIO_InitStruct.Pin = URTX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(URTX_GPIO_Port, &GPIO_InitStruct);
}


void arr_set_bit(uint8_t * const tab, const uint16_t bit) {
	tab[bit >> 3] |= (1 << (bit & 7));
}
void arr_clr_bit(uint8_t * const tab, const uint16_t bit) {
	tab[bit >> 3] &= ~(1 << (bit & 7));
}
uint8_t arr_chk_bit(uint8_t * const tab, const uint16_t bit) {
	return (tab[bit >> 3] & (1 << (bit & 7)));
}

void set_power(uint8_t PW)
{

ADF_TX_POWER = (PW*20) + 3;
	adf_set_tx_power(ADF_TX_POWER);


}
struct RF_config conf = {
	.flags = CONF_FLAG_NONE,
	.tx_freq = FREQUENCY,
	.rx_freq = FREQUENCY,
	.csma_rssi = CSMA_RSSI,
	.bitrate = BAUD_RATE,
	.modindex = MOD_INDEX,
	.pa_setting = PA_SETTING,
	.afc_range = AFC_RANGE,
	.afc_ki = AFC_KI,
	.afc_kp = AFC_KP,
	.afc_enable = AFC_ENABLE,
	.if_bw = IF_FILTER_BW,
	.sw = SYNC_WORD,
	.swtol = SYNC_WORD_TOLERANCE,
	.swlen = SYNC_WORD_BITS,
	.do_rs = true,
	.do_viterbi = true,
	.training_ms = TRAINING_MS,
	.training_inter_ms = TRAINING_INTER_MS,
	.training_symbol = TRAINING_SYMBOL,
	.ptt_delay_high = PTT_DELAY_HIGH,
	.ptt_delay_low = PTT_DELAY_LOW,
	.tx = 0,
	.rx = 0,
	.fw_revision = FW_REVISION,
};



