#include <stdint.h>
#include <string.h>
#include "variables.h"

#include "../threads/io_ctrl_thread.h"
#include "config.h"
#include "../lib/CRC.h"
#include "cmsis_os.h"
#include "stm32l1xx_hal.h"
#include "main.h"
#include "../threads/threads.h"
#include "../Src/pk_functions.h"



extern UART_HandleTypeDef huart1;
extern uint8_t txBuffer[30];
uint8_t progress = 0;
xTimerHandle io_timer_handle;
static uint8_t io_timer_id = 1;
extern SPI_HandleTypeDef hspi2;
static uint8_t bits_tab[128];
uint16_t outs = 0x0000;
uint8_t analog_out[8];
uint16_t temp_crc= 0xffff;


void io_ctrl_task(void const * argument)
{

	static uint16_t loop_counter = 0;
	volatile uint8_t spi_adres = 0;

	uint16_t counters_tab[65];
	uint8_t memory_tab[64];
	uint8_t analog_tab[8];
	uint8_t tmp_tab[8];
	uint8_t num = 0;


	if (system_errors.cfg_crc == 1 || rx_cfg.fb_len == 0){
		 for(;;){
			 vTaskDelay(100/portTICK_RATE_MS);
			 if(system_errors.cfg_crc == 0){break;}
		 }
	}
	init();

	system_errors.invalid_cfg = 0;
	memset(bits_tab, 0, 128U);
	memset(counters_tab, 0, 64U);
	memset(memory_tab, 0, 64U);
	memset(analog_tab, 0, 8U);

	vTaskDelay(100/portTICK_RATE_MS);


	/* check for relay driver short circuit */
	if (!(gpio_port_array[rx_cfg.pk_err]->IDR & (1 << gpio_pins_array[rx_cfg.pk_err]))) {
		system_errors.pks_ctrl = 1;
	}

	if(gpio_pins_array[rx_cfg.pk_err] == 0xff)
	{
		system_errors.pks_ctrl = 0;
	}


	while(system_errors.cfg_crc == 1)
	{
		vTaskDelay(10/portTICK_RATE_MS);
	}


	io_timer_handle = xTimerCreate(
		"io_tim", // name
		1 / portTICK_RATE_MS, // period
		pdTRUE, // autoreload
		&io_timer_id, // ID
		io_timer_callback // callback function
	);
	xTimerStart(io_timer_handle, 0);


for(;;)
{

	if ((gpio_port_array[rx_cfg.pk_err]->IDR & (1 << gpio_pins_array[rx_cfg.pk_err])) && gpio_pins_array[rx_cfg.pk_err] != 0xff) {
		system_errors.pks_ctrl = 0;
	}


		if(programmode == 1)
		{
			xTimerStop(io_timer_handle,0xffff);
			memset(bits_tab, 0, 128U);
			memset(counters_tab, 0, 64U);
			memset(memory_tab, 0, 64U);
			memset(analog_tab, 0, 8U);
			vTaskDelay(100/portTICK_RATE_MS);
		}

	if (system_errors.cfg_crc != 1 && programmode == 0){



	  			if (xSemaphoreTake(outputs_mutex, 1) == pdTRUE) {

		  			if (radio_status == 1) {

		  				memcpy(bits_tab, &rx_frame[rx_cfg.offset], RX_FRAME_LENGHT - (rx_cfg.offset));

		  				memcpy(&analog_tab[0], &rx_frame[1], rx_cfg.offset);



		  				if(rx_cfg.offset > 0)
		  				{
		  				for(uint8_t ana_counter = 0; ana_counter < 8; ana_counter++ )
		  				{


		  					if(rx_cfg.analog[ana_counter].n > 0 &&  rx_cfg.analog[ana_counter].size > 0)
		  					{

		  						//volatile uint8_t temp_ana = analog_tab[ana_counter];

		  						bits_tab[rx_cfg.analog[ana_counter].n] = analog_tab[ana_counter] >> (8 -rx_cfg.analog[ana_counter].size);
		  					}


		  				}
		  				}


		  			}
		  			else {

		  				memset(bits_tab, 0, 128U);
		  				memset(counters_tab, 0, 64U);
		  				memset(memory_tab, 0, 64U);
		  				memset(analog_tab, 0, 8U);
		  			}
		  		}
		  		xSemaphoreGive(outputs_mutex);

		  		//vTaskDelay(2/portTICK_RATE_MS);


	  		if (
	  			system_errors.cfg_crc ||
	  			system_errors.cfg_len ||
	  			system_errors.cfg_ver ||
	  			system_errors.invalid_cfg ||
	  			system_errors.main_ctrl ||
	  			system_errors.pks_ctrl
	  		) {
	  			memset(bits_tab, 0, 128U);
	  			memset(counters_tab, 0, 64U);
	  			memset(memory_tab, 0, 64U);
	  			memset(analog_tab, 0, 8U);
	  		}



	  		// pk_cfg execute //
	  		for (loop_counter = 0; loop_counter < 2048U; ) {
	  			if (rx_cfg.pk_cfg[loop_counter] == PK_EXIT) {

	  				vTaskDelay(2/portTICK_RATE_MS);
	  				break;
	  			}
	  			if (rx_cfg.pk_cfg[loop_counter] > 19U) {

	  				system_errors.invalid_cfg = 1;
	  				break;
	  			}
	  			switch (rx_cfg.pk_cfg[loop_counter]) {
	  			case PK_SET:
	  				pk_set_function(
	  					bits_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U]
	  				);
	  				loop_counter += 3U;
	  				break;
	  			case PK_CLR:
	  				pk_clr_function(
	  					bits_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U]
	  				);
	  				loop_counter += 3U;
	  				break;
	  			case PK_ASTAB:
	  				pk_astab_function(
	  					bits_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U]
	  				);
	  				loop_counter += 3U;
	  				break;
	  			case PK_BISTAB:
	  				pk_bistab_function(
	  					bits_tab,
	  					counters_tab,
	  					rx_cfg.tval_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U]
	  				);
	  				loop_counter += 5U;
	  				break;
	  			case PK_JOJ1:
	  				pk_joj1_function(
	  					bits_tab,
	  					counters_tab,
	  					rx_cfg.tval_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U],
	  					rx_cfg.pk_cfg[loop_counter + 5U]
	  				);
	  				loop_counter += 6U;
	  				break;
	  			case PK_JOJ2:
	  				pk_joj2_function(
	  					bits_tab,
	  					counters_tab,
	  					rx_cfg.tval_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U],
	  					rx_cfg.pk_cfg[loop_counter + 5U]
	  				);
	  				loop_counter += 6U;
	  				break;
	  			case PK_JOJ3:
	  				pk_joj3_function(
	  					bits_tab,
	  					counters_tab,
	  					rx_cfg.tval_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U]
	  				);
	  				loop_counter += 5U;
	  				break;
	  			case PK_JOJ4:
	  				pk_joj4_function(
	  					bits_tab,
	  					counters_tab,
	  					rx_cfg.tval_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U],
	  					rx_cfg.pk_cfg[loop_counter + 5U]
	  				);
	  				loop_counter += 6U;
	  				break;
	  			case PK_JOJ5:
	  				pk_joj5_function(
	  					bits_tab,
	  					counters_tab,
	  					rx_cfg.tval_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U],
	  					rx_cfg.pk_cfg[loop_counter + 5U],
	  					rx_cfg.pk_cfg[loop_counter + 6U],
	  					rx_cfg.pk_cfg[loop_counter + 7U]
	  				);
	  				loop_counter += 8U;
	  				break;
	  			case PK_ANGT:
	  				pk_angt_function(
	  					bits_tab,
	  					analog_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U]
	  				);
	  				loop_counter += 5U;
	  				break;
	  			case PK_ANLT:
	  				pk_anlt_function(
	  					bits_tab,
	  					analog_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U]
	  				);
	  				loop_counter += 5U;
	  				break;
	  			case PK_PULSE:
	  				pk_pulse_function(
	  					bits_tab,
	  					memory_tab,
	  					counters_tab,
	  					rx_cfg.tval_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U],
	  					rx_cfg.pk_cfg[loop_counter + 5U]
	  				);
	  				loop_counter += 6U;
	  				break;
	  			case PK_OR:
	  				pk_or_function(
	  					bits_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U]
	  				);
	  				loop_counter += 4U;
	  				break;
	  			case PK_AND:
	  				pk_and_function(
	  					bits_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U]
	  				);
	  				loop_counter += 4U;
	  				break;
	  			case PK_NOT:
	  				pk_not_function(
	  					bits_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U]
	  				);
	  				loop_counter += 3U;
	  				break;
	  			case PK_DEMUX3:
	  				pk_demux3_function(
	  					bits_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U]
	  				);
	  				loop_counter += 5U;
	  				break;
	  			case PK_ZERO:
	  				pk_zero_function(
	  					bits_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U]
	  				);
	  				loop_counter += 2U;
	  				break;
	  			case PK_ONE:
	  				pk_one_function(
	  					bits_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U]
	  				);
	  				loop_counter += 2U;
	  				break;
	  			case PK_JOJE:
	  				pk_joje_function(
	  					bits_tab,
	  					memory_tab,
	  					counters_tab,
	  					rx_cfg.tval_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U],
	  					rx_cfg.pk_cfg[loop_counter + 5U],
	  					rx_cfg.pk_cfg[loop_counter + 6U],
	  					rx_cfg.pk_cfg[loop_counter + 7U]
	  				);
	  				loop_counter += 8U;
	  				break;
	  			case PK_ASTABT:
	  				pk_astabt_function(
	  					bits_tab,
	  					counters_tab,
	  					rx_cfg.tval_tab,
	  					rx_cfg.pk_cfg[loop_counter + 1U],
	  					rx_cfg.pk_cfg[loop_counter + 2U],
	  					rx_cfg.pk_cfg[loop_counter + 3U],
	  					rx_cfg.pk_cfg[loop_counter + 4U]
	  				);
	  				loop_counter += 5U;
	  				break;
	  			default:
	  			case PK_EXIT:
	  				break;
	  			}
	  		}

	  		// outputs setup //
	  		if(programmode == 0)
	  		{

	  		for (loop_counter = 0U; loop_counter < 32U; loop_counter++) {
	  			if (rx_cfg.pk_out[loop_counter] == 0xFF) {
	  				break;
	  			}



	  			if ((loop_counter == 1U) || (loop_counter == 2U)) {
	  				if (tab_chk_bit(bits_tab, 128 + loop_counter)) {
	  					gpio_port_array[rx_cfg.pk_out[loop_counter]]->ODR ^= (1 << gpio_pins_array[rx_cfg.pk_out[loop_counter]]);
	  				}
	  				else {
	  					gpio_port_array[rx_cfg.pk_out[loop_counter]]->ODR &=~ (1 << gpio_pins_array[rx_cfg.pk_out[loop_counter]]);
	  				}
	  			}
	  			else {
	  				if (tab_chk_bit(bits_tab, 128 + loop_counter)) {
	  					gpio_port_array[rx_cfg.pk_out[loop_counter]]->ODR |= (1 << gpio_pins_array[rx_cfg.pk_out[loop_counter]]);
	  				}
	  				else {
	  					gpio_port_array[rx_cfg.pk_out[loop_counter]]->ODR &=~ (1 << gpio_pins_array[rx_cfg.pk_out[loop_counter]]);
	  				}
	  			}




	  		}

	  		}

/******************** Rozszerzenia  *************************************************/





	  		//for(uint8_t num = 0; num < 12; num = num +2)
	  		//{
/*
	  		if(num < 12)
	  		{
	  			progress = rx_cfg.spi_cfg[num];

	  			// ANA_USER_PRG.ARRAY[1].MaxDn[0];

	  			if(rx_cfg.spi_cfg[num] > 0 && rx_cfg.spi_cfg[num+1] == 23 )			//0x23 j6
	  			{


	  				volatile uint16_t directions[2];
	  				memset(tmp_tab,0,8);

	  				//bits_tab[rx_cfg.analog[ana_counter].n] = analog_tab[ana_counter];;

	  				//memcpy(&bits_tab[rx_cfg.spi_cfg[num] >> 3], &analog_tab[0], 6);


	  				tmp_tab[10] = 0x00;
	  				spi_adres = (num/2)+1;
	  				memcpy(&tmp_tab[0], &bits_tab[rx_cfg.spi_cfg[num] >> 3], 8);


	  				for(uint8_t channel = 0; channel < 6; channel ++)
	  				{
	  					//volatile uint8_t analog_temp = tmp_tab[channel]/(uint8_t)4;
	  					//directions[0] = (rx_cfg.spi_cfg[num] + (8*channel)) - 1;
	  					//directions[1] = (rx_cfg.spi_cfg[num] + (8*channel));

	  					analog_out[channel] = MAP_ANA(0x23,channel,tmp_tab[channel],1,rx_frame[0]);



	  				}

	  				memcpy(&analog_out[6], &tmp_tab[6], 2);
	  				memcpy( &bits_tab[rx_cfg.spi_cfg[num] >> 3],&analog_out[0], 8);



	  				if(spi_n(spi_adres,0x23,10,analog_out) == 1)
	  				{
	  					system_errors.spi_ext = 1;
	  				}
	  				else
	  				{
	  					system_errors.spi_ext = 0;
	  				}


	  			}

	  			if(rx_cfg.spi_cfg[num] > 0 && rx_cfg.spi_cfg[num+1] == 30 )			//0x30 tzw
	  			{
	  				spi_adres = (num/2)+1;
	  				memset(tmp_tab,0,8);
	  				tmp_tab[0] = 1;
	  				tmp_tab[1] = 2;
	  				tmp_tab[2] = 3;
	  				tmp_tab[3] = 4;
	  				tmp_tab[4] = 5;
	  		      //if(spi_n(s, 0x23, 7, t_buf) != 0) {

	  				if(spi_n(spi_adres,0x23,7,tmp_tab) == 1)
	  				{
	  					system_errors.spi_ext = 1;
	  					memset(tmp_tab,0,8);

	  				}
	  				else
	  				{
	  					memset(tmp_tab,0,8);
	  					memcpy(&tmp_tab[0],&sbi[3], 4);
	  					 temp_crc = 0xffff;
	  					 temp_crc = calc_crc(tmp_tab, 4);
	  					 memcpy(&tmp_tab[4], &temp_crc,2);
	  					system_errors.spi_ext = 0;
	  				}

	  				memcpy(txBuffer,tmp_tab, 6);


	  			}
	  			num = num + 2;
	  			}
	  		else
	  		{
	  			num = 0;
	  		}

	  		*/


	  		//}
/******************** Rozszerzenia  *************************************************/
	  		vTaskDelay(10/portTICK_RATE_MS);
	  	}
	else
	{
		vTaskDelay(2/portTICK_RATE_MS);
		//xTimerStop(io_timer_handle, 0);
	}
}
}


extern uint16_t rx_loop_counter;
void io_timer_callback(xTimerHandle timer_handle) {
	(void)timer_handle;



	static uint8_t generate_period_counter = 0;
	static uint8_t check_timeout_counter = 0;
	static uint8_t last_state = 0;
	static uint8_t curr_state = 0;
	static uint8_t err_counters[] = {0, 0};

	rx_loop_counter++;





	  	// generate signal at MAIN_CTRL_OUT pin //
	  	if (generate_period_counter < 5) {
	  		generate_period_counter++;
	  	}
	  	else {
	  		gpio_port_array[rx_cfg.sg_ctl_o]->ODR ^= (1 << CONTROL_pins_array[rx_cfg.sg_ctl_o]);
	  		generate_period_counter = 0;

	  	}

	  	// check for signal at MAIN_CTRL_IN pin (only when PK1 and PK2 are cleared) //
	  	if (!tab_chk_bit(bits_tab, 128 + 1) && !tab_chk_bit(bits_tab, 128 + 2)) {
	  		if (gpio_port_array[rx_cfg.sg_ctl_i]->IDR & (1 << CONTROL_pins_array[rx_cfg.sg_ctl_i])) {
	  			curr_state = 1;
	  		}
	  		else {
	  			curr_state = 0;
	  		}

	  		if (last_state != curr_state) {
	  			check_timeout_counter = 0;
	  			last_state = curr_state;
	  			system_errors.main_ctrl = 0;
	  		}
	  		else {
	  			if (check_timeout_counter < 100) { // 100ms timeout
	  				check_timeout_counter++;

	  			}
	  			else {
	  				system_errors.main_ctrl = 1;

	  			}
	  		}
	  	}
	  	else {
	  		system_errors.main_ctrl = 0;
	  	}

	  	// check relays supply transistor //
	  	if (gpio_port_array[rx_cfg.pk_out[0]]->ODR & (1 << CONTROL_pins_array[rx_cfg.pk_out[0]])) {
	  		if (!(gpio_port_array[rx_cfg.move_chk]->IDR & (1 << CONTROL_pins_array[rx_cfg.move_chk]))) {				//negacja
	  			if (err_counters[0] < 40) {
	  				err_counters[0]++;
	  			}
	  			else {
	  				system_errors.supply_short = 1;
	  			}
	  		}
	  		else {
	  			system_errors.supply_short = 0;
	  			err_counters[0] = 0;
	  		}
	  	}
	  	else {
	  		/*
	  		if (gpio_port_array[rx_cfg.move_chk]->IDR & (1 << CONTROL_pins_array[rx_cfg.move_chk])) {
	  			if (err_counters[1] < 40) {
	  				err_counters[1]++;
	  			}
	  			else {
	  				system_errors.supply_err = 1;
	  			}
	  		}
	  		else {
	  			system_errors.supply_err = 0;
	  			err_counters[1] = 0;
	  		}
	  		*/
	  	}

	  }


uint8_t spi_n(const uint8_t n, uint8_t t, uint8_t l, uint8_t *b)
{
// n - numer rozszerzenia SPI
// t - typ rozszerzenia SPI
// l - dlugosc ramki bez CRC
// b - wskaznik do tablicy z danymi

//	uint8_t rx_ok = 0;

	//RCC->APB1RSTR |= RCC_APB1RSTR_SPI2RST;
	//RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI2RST;

	memset(sbi,0,22);
	  sbo[0] = t;
	  sbo[1] = l;

	  for(int c = 0; c < l; c++)
	  {
		  sbo[c+2] = b[c];
	  }

	  uint16_t crc = 0xffff;
	  crc = calc_crc(sbo, l);
	  *(uint16_t *)&sbo[l] = crc;


	  if(SPI_numbers > 0)
	  {
	  if(n==1){HAL_GPIO_WritePin(SS_GPIO_Port,SS_Pin,RESET);}
//	  if(n==2){HAL_GPIO_WritePin(SS2_GPIO_Port,SS2_Pin,RESET);}
//	  if(n==2){HAL_GPIO_WritePin(P23_GPIO_Port,P23_Pin,RESET);}
//	  if(n==3){HAL_GPIO_WritePin(P22_GPIO_Port,P22_Pin,RESET);}
//	  if(n==4){HAL_GPIO_WritePin(P21_GPIO_Port,P21_Pin,RESET);}


	  for(uint16_t c = 0; c < 300; c++)
	  {
		  asm ("nop");
	  }
	  //HAL_SPI_TransmitReceive_DMA(&hspi2,sbo,sbi,l+4);


	  HAL_SPI_TransmitReceive(&hspi2,sbo,sbi,l+2,10);


	  for(uint16_t c = 0; c < 300; c++)
	  {
		  asm ("nop");
	  }

/*
	  for(int f = 0; f < l+2; f++)
	  {

		  HAL_SPI_TransmitReceive(&hspi2,&sbo[f],&sbi[f],1,20);
	  }
*/



   	  if(n==1){HAL_GPIO_WritePin(SS_GPIO_Port,SS_Pin,SET);}
   	 // if(n==2){HAL_GPIO_WritePin(SS2_GPIO_Port,SS2_Pin,SET);}
//   	  if(n==2){HAL_GPIO_WritePin(P23_GPIO_Port,P23_Pin,SET);}
//   	  if(n==3){HAL_GPIO_WritePin(P22_GPIO_Port,P22_Pin,SET);}
//   	  if(n==4){HAL_GPIO_WritePin(P21_GPIO_Port,P21_Pin,SET);}


   	  /*
   	  for(uint8_t rest = 0; rest < 8; rest++)
   	  {
   	  volatile uint8_t rest_me = 0;
   	  rest_me = SPI1->DR;

   	  }
   	  */

	  }

	 temp_crc = 0xffff;
	 temp_crc = calc_crc(sbi, l+2);

	  if((*(uint16_t *)&sbi[l+2]) != temp_crc )
	  {


	      return 1;
	  }
	  else
	  {


		  return 0;
	  }

}

volatile uint8_t srv_timer = 0;
volatile uint8_t srv_tim_speed = 50;


uint8_t MAP_ANA( uint8_t EXT_type,uint8_t CH, uint8_t Val_in, uint8_t ARR_num, uint8_t SRV)
{
	uint8_t out_val = 0;

	volatile uint8_t Dir1 = (Val_in >> 6) & 0x01;
	volatile uint8_t Dir2 = (Val_in >> 7) & 0x01;

	Val_in = Val_in & 0x3f;
	if(EXT_type == 0x23)
	{
		if(SRV & SRV_ACTIVE )
		{
			//srv_timer++;
			//if(srv_timer >= srv_tim_speed )
			//{
			//	srv_timer = 0;


			if(SRV & SRV_MIN )				//Minimum
			{
				if(SRV & SRV_MINUS)
				{
					if(Dir1 == 1 && Dir2 ==0)
					{
						if(ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinDn[CH] >= 1){
						ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinDn[CH]--;}


					}
					if(Dir2 == 1&& Dir1 ==0)
					{
						if(ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinUp[CH] >= 1){
						ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinUp[CH]--;}

					}


				}
				if(SRV & SRV_PLUS)
				{
					if(Dir1 == 1 && Dir2 ==0)
					{
						if(ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinDn[CH] < 63){
						ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinDn[CH]++;}


					}
					if(Dir2 == 1&& Dir1 ==0)
					{
						if(ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinUp[CH] < 63){
						ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinUp[CH]++;}


					}
				}

				if(Dir1 == 1 && Dir2 ==0)
				{

					out_val = ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinDn[CH];
					out_val = out_val | 0x80;
					out_val = out_val &~ 0x40;

				}
				if(Dir2 == 1&& Dir1 ==0)
				{

					out_val = ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinUp[CH];
					out_val = out_val | 0x40;
					out_val = out_val &~ 0x80;
				}

			}
			else							//maximum
			{

				if(SRV & SRV_MINUS)
			{
				if(Dir1 == 1 && Dir2 ==0)
				{
					if(ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxDn[CH] >= 1){
					ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxDn[CH]--;}


				}
				if(Dir2 == 1&& Dir1 ==0)
				{
					if(ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxUp[CH] >= 1){
					ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxUp[CH]--;}


				}
			}
			if(SRV & SRV_PLUS)
			{
				if(Dir1 == 1 && Dir2 ==0)
				{
					if(ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxDn[CH] < 63){
					ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxDn[CH]++;}


				}
				if(Dir2 == 1&& Dir1 ==0)
				{
					if(ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxUp[CH] < 63){
					ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxUp[CH]++;}


				}
			}

				if(Dir1 == 1 && Dir2 ==0)
				{

					out_val = ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxDn[CH];
					out_val = out_val | 0x80;
					out_val = out_val &~ 0x40;

				}
				if(Dir2 == 1&& Dir1 ==0)
				{

					out_val = ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxUp[CH];
					out_val = out_val | 0x40;
					out_val = out_val &~ 0x80;
				}

			}



			//}

		}
		else
		{

			out_val = 32;
			if(Dir1 == 1 && Dir2 == 0)
			{
				out_val = map(Val_in,0,63,ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinDn[CH],ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxDn[CH]);
				out_val = out_val | 0x80;
				out_val = out_val &~ 0x40;

			}



			if(Dir1 == 0 && Dir2 == 1)
			{
				out_val = map(Val_in,0,63,ANA_USER_PRG.ARRAY[ARR_num & 0x03].MinDn[CH],ANA_USER_PRG.ARRAY[ARR_num & 0x03].MaxDn[CH]);
				out_val = out_val | 0x40;
				out_val = out_val &~ 0x80;

			}


		}









	}



	if(EXT_type == 0x22)
	{

	}

	return out_val;


}



uint8_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max)
{

uint16_t temp = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
return temp;
}
