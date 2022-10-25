#include "BUS.h"
#include <string.h>
#include "main.h"
#include "cmsis_os.h"
#include "globals.h"

extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
#define USE_NEW

#define sys_enabled_slaves 1
#define PWM_enable 1
#define TEMP_PT_NTC

uint8_t received_bytes[50];
uint8_t received_bytes_PWM[20];


_slaveFrame slaveFrameRaw;
#ifdef PWMSlave
_slavePWMFrame slavePWMFrameRaw;
#endif

#define USE_DEBUG_MODE
#define M_FRAME_DATA_LEN 7U
#define M_FRAME_MAX_LEN 22U
#define S_FRAME_DATA_LEN 5U
#define S_FRAME_LEN 18U
#define MASTER_STATUS_ALARM_OCCURED 0x01
#ifdef PWMSlave
// Tu opcjonalne definicje
#endif
extern uint8_t sys_program_heat_curve_calculate(
    int8_t * const system_hc,
    const uint8_t arrays_size,
    const int8_t program_value,
    const int8_t multipiler_value,
    const int8_t user_offset,
    const uint8_t room_temperature,
    const uint8_t room_sensor_active_condition,
    const int8_t max_possition,
    const int8_t min_possition,
    int8_t * const output_hc,
    int8_t * const output_hc_full
);

uint16_t crc_add_value(uint16_t crc, uint8_t data) {
    data ^= (uint8_t) (crc & 0xFF);
    data ^= data << 4;
    return ((((uint16_t) data << 8) | (crc >> 8)) ^ (uint8_t) (data >> 4) ^ ((uint16_t) data << 3));
}


volatile uint8_t send_uart_nr =0;
/**
 * @brief Uart char receive interrupt function
 * @details When char occured in uart buffer this function is triggered.
 */
/*
void __ISR(_UART_1_VECTOR, IPL2) _UART1Handler(void) {
    uint8_t uart_byte = 0;
    if (UART1GetErrors()) {
        UART1ClearAllErrors();
    }
    uart_byte = UARTGetDataByte(UART1);
    xQueueSendFromISR(uart_rx_data_queue, (void*)&uart_byte, pdFALSE);
    IFS0bits.U1RXIF = 0;

}
*/
void task_bus (void) {
    static char masterFrame[] = {'m','A','A','O','O','C','C','C','C','z'};
    static char slaveFrame[] = {'s','A','A','0','0','0','0','1','1','1','1','2','2','2','2','3','3','3','3','4','4','4','4','5','5','5','5','6','6','6','6','7','7','7','7','I','I','C','C','C','C','z'};
#ifdef PWMSlave
    static char masterPWMFrame[] = {'t','A','A','0','1','1','1','2','2','C','C','C','C','z'};
    static char slavePWMFrame[] = {'r','A','A','1','0','1','1','2','2','t','t','t','t','i','i','C','C','C','C','z'};
#endif
    uint16_t slaveCnt, crc, i, j;
    uint8_t uart_rx_queue_byte;
    int8_t tmp_room_correction = 0;
    uint8_t tmp_room_temperature = 0;

    uint8_t m_frame_data[M_FRAME_DATA_LEN];
    uint8_t frame_counter = 0;



SPWM[0].PWM1z = 40;
SPWM[0].PWM2z = 60;



    struct {
        union {
            struct {
                uint8_t address;
                uint8_t room_temperature;
                uint8_t room_correction;
                uint16_t outside_temperature;
                uint8_t status;
                uint8_t time;
            } fields;
            uint8_t tab[M_FRAME_DATA_LEN];
        } data;
        uint8_t raw[50];
    } m_frame;
    struct {
        union {
            struct {
                uint8_t address;
                uint8_t room_temperature;
                uint16_t inside_temperature;
                uint8_t status;
            } fields;
            uint8_t tab[S_FRAME_DATA_LEN];
        } data;
        uint8_t raw[S_FRAME_LEN];
    } s_frame;
    uint8_t m_frame_len = 0;
    uint8_t status = 0;
    uint16_t s_frame_out_temp = 0;

    while (1) {

    	vTaskDelay(20 / portTICK_RATE_MS);
			if (xSemaphoreTake(refresh_data_mutex, 10) == pdTRUE) {


        // <editor-fold defaultstate="collapsed" desc="SLAVES comunication">
        for (slaveCnt = 0; slaveCnt < sys_enabled_slaves; slaveCnt++) {
            /* CRC ---------------------------------------------------------- */
            crc = 0xFFFF;
            for (i = 0; i < 2; i++) {
                sprintf(masterFrame, "m%2X%2X%4Xz", slaveCnt, S[slaveCnt].DigitalOutputs, crc);
                for (j = 0; j < sizeof (masterFrame); j++) {
                    if (masterFrame[j] == ' ') masterFrame[j] = '0';
                    if ((j > 0) && (j < (sizeof (masterFrame) - 5))) crc = crc_add_value(crc, masterFrame[j]);
                }
            }
            swap(masterFrame[5], masterFrame[8]);
            swap(masterFrame[6], masterFrame[7]);
            /* TRANSMITT ---------------------------------------------------- */


            UARTSendDataByte(&huart5, masterFrame,10);
            send_uart_nr = 1;
            //BusDriverDisable();




            /* DELAY -------------------------------------------------------- */

            vTaskDelay(20 / portTICK_RATE_MS);
            /* RECEIVE ------------------------------------------------------ */




            crc = 0xFFFF;
            for (i = 0; i < sizeof (slaveFrame); i++) {
                    slaveFrame[i] = received_bytes[i];
                    if ((i > 0) && (i < (sizeof (slaveFrame) - 5))) crc = crc_add_value(crc, slaveFrame[i]);
                    if (slaveFrame[i] == 'z') break;

            }

            frame_convert(slaveFrame, sizeof (slaveFrame), &slaveFrameRaw);
            if (slaveFrameRaw.Crc == crc) {
                if (frame_get_data(&slaveFrameRaw, slaveCnt, 0, 0) == 1) {
//                    gui_refresh_bits_0 |= (1 << (10 - slaveCnt));
                }
            } else {
                if (frame_get_data(&slaveFrameRaw, slaveCnt, 0, 1) == 1) {
//                    gui_refresh_bits_0 |= (1 << (10 - slaveCnt));
                }
            }
            vTaskDelay(10 / portTICK_RATE_MS);
        }// </editor-fold>
        // <editor-fold defaultstate="collapsed" desc="SLAVES PWM comunication">
#ifdef PWMSlave
      if (PWM_enable) { // tu flaga uzywania modulu PWM
        for (slaveCnt = 0; slaveCnt < sys_enabled_slaves; slaveCnt++) {
            /* CRC ---------------------------------------------------------- */
            crc = 0xFFFF;
            for (i = 0; i < 2; i++) {
                sprintf(masterPWMFrame, "t%2X%2X%2X%2X%4Xz", slaveCnt + 0x30, 0x01, SPWM[slaveCnt].PWM1z,SPWM[slaveCnt].PWM2z, crc);
                for (j = 0; j < sizeof (masterPWMFrame); j++) {
                    if (masterPWMFrame[j] == ' ') masterPWMFrame[j] = '0';
                    if ((j > 0) && (j < (sizeof (masterPWMFrame) - 5))) crc = crc_add_value(crc, masterPWMFrame[j]);
                }
            }
            swap(masterPWMFrame[9], masterPWMFrame[12]);
            swap(masterPWMFrame[10], masterPWMFrame[11]);
            /* TRANSMITT ---------------------------------------------------- */

            UARTSendDataByte(&huart5, masterPWMFrame,14);
            send_uart_nr = 2;





            /* DELAY -------------------------------------------------------- */

            vTaskDelay(20 / portTICK_RATE_MS);
            /* RECEIVE ------------------------------------------------------ */

uint8_t swaping_crc[4];



            //swap(slavePWMFrame[15], slavePWMFrame[18]);
            //swap(slavePWMFrame[16], slavePWMFrame[17]);


            crc = 0xFFFF;
            for (i = 0; i < sizeof (slavePWMFrame); i++) {
                    slavePWMFrame[i] = received_bytes_PWM[i];
                    if ((i > 0) && (i < (sizeof (slavePWMFrame) - 5)))
                    	{
                    	crc = crc_add_value(crc, slavePWMFrame[i]);
                    	}
                    if (slavePWMFrame[i] == 'z')
                    {
                    	break;
                    }


            }

            swaping_crc[3] = slavePWMFrame[15];
            swaping_crc[2] = slavePWMFrame[16];
            swaping_crc[1] = slavePWMFrame[17];
            swaping_crc[0] = slavePWMFrame[18];

            slavePWMFrame[15] = swaping_crc[0];
            slavePWMFrame[16] = swaping_crc[1];
            slavePWMFrame[17] = swaping_crc[2];
            slavePWMFrame[18] = swaping_crc[3];

            PWMframe_convert(slavePWMFrame, sizeof (slavePWMFrame), &slavePWMFrameRaw);
            if (slavePWMFrameRaw.Crc == crc) {
            	//snprintf(&PWMS.PWM1[0],"%3u",slavePWMFrameRaw[0].PWM1);
            	//snprintf(&PWMS.PWM2[0],"%3u",slavePWMFrameRaw[0].PWM2);

                sprintf(PWM1,"%u",SPWM[0].PWM1o/4);
                sprintf(PWM2,"%u",SPWM[0].PWM2o/4);

                if (PWMframe_get_data(&slavePWMFrameRaw, slaveCnt, 0, 0) == 1)  {
                	//snprintf(PWMS.PWM1,"%3u",slavePWMFram)



                					//                    gui_refresh_bits_0 |= (1 << (10 - slaveCnt));
                }
            } else {
                if (PWMframe_get_data(&slavePWMFrameRaw, slaveCnt, 0, 1) == 1)  {
 //                   gui_refresh_bits_0 |= (1 << (10 - slaveCnt));

                }
            }
            vTaskDelay(10 / portTICK_RATE_MS);
        }
      }
#endif
        // </editor-fold>
        // <editor-fold defaultstate="collapsed" desc="ROOM_SENS comunication">
      xSemaphoreGive(refresh_data_mutex);
    }


}


}


void debug_byte_send(uint8_t val) {
    //while (!UARTTransmitterIsReady(UART2B));
    //UARTSendDataByte(&huart1, val);
    return;
}



float temperature_convert_to_normal(float prec, float cmpns, int16_t minValue, int16_t maxValue, int16_t conditionToZero){
    float normal = (prec + cmpns); // / 10;
    if (conditionToZero) return 0;
    if (prec == T_NULL) return T_NULL;
    return normal;
}

int8_t frame_convert(char* frame, uint8_t size, _slaveFrame *slave) {
    static char clipped2[3];
    static char clipped4[5];
    if ((frame[0] != 's') || (frame[size - 1] != 'z')) return -1;
    slave->Address = frame_get_item(frame, 1, clipped2, 2);
    slave->Analog0 = frame_get_item(frame, 3, clipped4, 4);
    slave->Analog1 = frame_get_item(frame, 7, clipped4, 4);
    slave->Analog2 = frame_get_item(frame, 11, clipped4, 4);
    slave->Analog3 = frame_get_item(frame, 15, clipped4, 4);
    slave->Analog4 = frame_get_item(frame, 19, clipped4, 4);
    slave->Analog5 = frame_get_item(frame, 23, clipped4, 4);
    slave->Analog6 = frame_get_item(frame, 27, clipped4, 4);
    slave->Analog7 = frame_get_item(frame, 31, clipped4, 4);
    slave->Inputs = frame_get_item(frame, 35, clipped2, 2);
    slave->Crc = frame_get_item(frame, 37, clipped4, 4);
    return 0;
}
#ifdef PWMSlave
int8_t PWMframe_convert(char* frame, uint8_t size,  _slavePWMFrame *slave) {
    static char clipped2[4];
    static char clipped4[1];
    if ((frame[0] != 'r') || (frame[size - 1] != 'z')) return -1;
    slave->Address = frame_get_item(frame, 1, clipped2, 2);
    slave->St = frame_get_item(frame, 3, clipped2, 2);
    slave->PWM1 = frame_get_item(frame, 5, clipped2, 2);
    slave->PWM2 = frame_get_item(frame, 7, clipped2, 2);
    slave->temp = frame_get_item(frame, 9, clipped4, 4);
    slave->inp = frame_get_item(frame, 13, clipped2, 2);
    slave->Crc = frame_get_item(frame, 15, clipped4, 4);
    return 0;
}
#endif
uint16_t frame_get_item(char* frame, uint8_t start, char* clipped, uint8_t size){
    int32_t result = 0;
    uint8_t i = 0;
    for (i = 0; i < size; i++)
        clipped[i] = frame[start + i];
    if (sscanf(clipped, "%x", &result) < 1) return 0;
    return (uint16_t)result;
}

uint8_t frame_get_data(_slaveFrame * raw, uint8_t slaveIndex, uint8_t cmpnsStart, uint8_t clrFlag) {
    uint8_t tmpInputs;
    uint8_t eventLog = 0;
    if (clrFlag == 1) {
        if (S[slaveIndex].AbsenceCnt < MAX_ABSENCE) {
            if (S[slaveIndex].AbsenceCnt == MAX_ABSENCE - 1) eventLog = 1;
            S[slaveIndex].AbsenceCnt++;
        }
        else {
            S[slaveIndex].PT[1] = T_NULL;
            S[slaveIndex].PT[2] = T_NULL;
            S[slaveIndex].PT[3] = T_NULL;
            S[slaveIndex].PT[4] = T_NULL;
            S[slaveIndex].PT[5] = T_NULL;
            S[slaveIndex].PT[6] = T_NULL;
            S[slaveIndex].PT[7] = T_NULL;
            S[slaveIndex].PT[0] = T_NULL;
            S[slaveIndex].DigitalInputs = 0x00;
        }
    }
    else {
        if (S[slaveIndex].AbsenceCnt == MAX_ABSENCE) eventLog = 1;
        S[slaveIndex].AbsenceCnt = 0;
#ifdef TEMP_NTC
// stare czujniki
        if ((raw->Analog0 < NTC80_MAX) && (raw->Analog0 > NTC80_MIN)) S[slaveIndex].PT[1] = TempTab080[clip_max_value(raw->Analog0, 4095)];
        else S[slaveIndex].PT[1] = T_NULL;
        if ((raw->Analog1 < NTC80_MAX) && (raw->Analog1 > NTC80_MIN)) S[slaveIndex].PT[2] = TempTab080[clip_max_value(raw->Analog1, 4095)];
        else S[slaveIndex].PT[2] = T_NULL;
        if ((raw->Analog2 < NTC30_MAX) && (raw->Analog2 > NTC30_MIN)) S[slaveIndex].PT[3] = TempTabm2030[clip_max_value(raw->Analog2, 4095)];
        else S[slaveIndex].PT[3] = T_NULL;
        if ((raw->Analog3 < NTC30_MAX) && (raw->Analog3 > NTC30_MIN)) S[slaveIndex].PT[4] = TempTabm2030[clip_max_value(raw->Analog3, 4095)];
        else S[slaveIndex].PT[4] = T_NULL;
        if ((raw->Analog4 < NTC80_MAX) && (raw->Analog4 > NTC80_MIN)) S[slaveIndex].PT[5] = TempTab080[clip_max_value(raw->Analog4, 4095)];
        else S[slaveIndex].PT[5] = T_NULL;
        if ((raw->Analog5 < NTC80_MAX) && (raw->Analog5 > NTC80_MIN)) S[slaveIndex].PT[6] = TempTab080[clip_max_value(raw->Analog5, 4095)];
        else S[slaveIndex].PT[6] = T_NULL;
        if ((raw->Analog6 < NTC80_MAX) && (raw->Analog6 > NTC80_MIN)) S[slaveIndex].PT[7] = TempTab080[clip_max_value(raw->Analog6, 4095)];
        else S[slaveIndex].PT[7] = T_NULL;
        if ((raw->Analog7 < NTC60_MAX) && (raw->Analog7 > NTC60_MIN)) S[slaveIndex].PT[0] = TempTabm4060[clip_max_value(raw->Analog7, 4095)];
        else S[slaveIndex].PT[0] = T_NULL;
//
#endif
#ifdef TEMP_PT
// Pt1000
        if ((raw->Analog0 < PT1000_MAX) && (raw->Analog0 > PT1000_MIN)) S[slaveIndex].PT[1] = ADCPT1000_to_temp(clip_max_value(raw->Analog0, 4095));
        else S[slaveIndex].PT[1] = T_NULL;
        if ((raw->Analog1 < PT1000_MAX) && (raw->Analog1 > PT1000_MIN)) S[slaveIndex].PT[2] = ADCPT1000_to_temp(clip_max_value(raw->Analog1, 4095));
        else S[slaveIndex].PT[2] = T_NULL;
        if ((raw->Analog2 < PT1000_MAX) && (raw->Analog2 > PT1000_MIN)) S[slaveIndex].PT[3] = ADCPT1000_to_temp(clip_max_value(raw->Analog2, 4095));
        else S[slaveIndex].PT[3] = T_NULL;
        if ((raw->Analog3 < PT1000_MAX) && (raw->Analog3 > PT1000_MIN)) S[slaveIndex].PT[4] = ADCPT1000_to_temp(clip_max_value(raw->Analog3, 4095));
        else S[slaveIndex].PT[4] = T_NULL;
        if ((raw->Analog4 < PT1000_MAX) && (raw->Analog4 > PT1000_MIN)) S[slaveIndex].PT[5] = ADCPT1000_to_temp(clip_max_value(raw->Analog4, 4095));
        else S[slaveIndex].PT[5] = T_NULL;
        if ((raw->Analog5 < PT1000_MAX) && (raw->Analog5 > PT1000_MIN)) S[slaveIndex].PT[6] = ADCPT1000_to_temp(clip_max_value(raw->Analog5, 4095));
        else S[slaveIndex].PT[6] = T_NULL;
        if ((raw->Analog6 < PT1000_MAX) && (raw->Analog6 > PT1000_MIN)) S[slaveIndex].PT[7] = ADCPT1000_to_temp(clip_max_value(raw->Analog6, 4095));
        else S[slaveIndex].PT[7] = T_NULL;
        if ((raw->Analog7 < PT1000_MAX) && (raw->Analog7 > PT1000_MIN)) S[slaveIndex].PT[0] = ADCPT1000_to_temp(clip_max_value(raw->Analog7, 4095));
        else S[slaveIndex].PT[0] = T_NULL;
#endif
#ifdef TEMP_PT_NTC
// Pt1000 + TZ NTC
        if ((raw->Analog0 < PT1000_MAX) && (raw->Analog0 > PT1000_MIN)) S[slaveIndex].PT[1] = ADCPT1000_to_temp(clip_max_value(raw->Analog0, 4095));
        else S[slaveIndex].PT[1] = T_NULL;
        if ((raw->Analog1 < PT1000_MAX) && (raw->Analog1 > PT1000_MIN)) S[slaveIndex].PT[2] = ADCPT1000_to_temp(clip_max_value(raw->Analog1, 4095));
        else S[slaveIndex].PT[2] = T_NULL;
        if ((raw->Analog2 < PT1000_MAX) && (raw->Analog2 > PT1000_MIN)) S[slaveIndex].PT[3] = ADCPT1000_to_temp(clip_max_value(raw->Analog2, 4095));
        else S[slaveIndex].PT[3] = T_NULL;
        if ((raw->Analog3 < PT1000_MAX) && (raw->Analog3 > PT1000_MIN)) S[slaveIndex].PT[4] = ADCPT1000_to_temp(clip_max_value(raw->Analog3, 4095));
        else S[slaveIndex].PT[4] = T_NULL;
        if ((raw->Analog4 < PT1000_MAX) && (raw->Analog4 > PT1000_MIN)) S[slaveIndex].PT[5] = ADCPT1000_to_temp(clip_max_value(raw->Analog4, 4095));
        else S[slaveIndex].PT[5] = T_NULL;
        if ((raw->Analog5 < PT1000_MAX) && (raw->Analog5 > PT1000_MIN)) S[slaveIndex].PT[6] = ADCPT1000_to_temp(clip_max_value(raw->Analog5, 4095));
        else S[slaveIndex].PT[6] = T_NULL;
        if ((raw->Analog6 < PT1000_MAX) && (raw->Analog6 > PT1000_MIN)) S[slaveIndex].PT[7] = ADCPT1000_to_temp(clip_max_value(raw->Analog6, 4095));
        else S[slaveIndex].PT[7] = T_NULL;
//        if ((raw->Analog7 < NTC60_MAX) && (raw->Analog7 > NTC60_MIN)) S[slaveIndex].PT[0] = TempTabm4060[clip_max_value(raw->Analog7, 4095)];
        if ((raw->Analog7 < NTC60_MAX) && (raw->Analog7 > NTC60_MIN)) S[slaveIndex].PT[0] = ADCNTCZ_to_temp(clip_max_value(raw->Analog7, 4095));
        else S[slaveIndex].PT[0] = T_NULL;
#endif
        S[slaveIndex].DigitalInputs = raw->Inputs;
    }
    S[slaveIndex].PPT[1] = check_to_update(S[slaveIndex].PPT[1], S[slaveIndex].PT[1], 13);
    S[slaveIndex].T[1] = temperature_convert_to_normal(S[slaveIndex].PT[1], S[slaveIndex].Cmpns[1], -99, 99, 0);

    S[slaveIndex].PPT[2] = check_to_update(S[slaveIndex].PPT[2], S[slaveIndex].PT[2], 14);
    S[slaveIndex].T[2] = temperature_convert_to_normal(S[slaveIndex].PT[2], S[slaveIndex].Cmpns[2], -99, 99, 0);

    S[slaveIndex].PPT[3] = check_to_update(S[slaveIndex].PPT[3], S[slaveIndex].PT[3], 15);
    S[slaveIndex].T[3] = temperature_convert_to_normal(S[slaveIndex].PT[3], S[slaveIndex].Cmpns[3], -99, 99, 0);

    S[slaveIndex].PPT[4] = check_to_update(S[slaveIndex].PPT[4], S[slaveIndex].PT[4], 16);
    S[slaveIndex].T[4] = temperature_convert_to_normal(S[slaveIndex].PT[4], S[slaveIndex].Cmpns[4], -99, 99, 0);

    S[slaveIndex].PPT[5] = check_to_update(S[slaveIndex].PPT[5], S[slaveIndex].PT[5], 17);
    S[slaveIndex].T[5] = temperature_convert_to_normal(S[slaveIndex].PT[5], S[slaveIndex].Cmpns[5], -99, 99, 0);

    S[slaveIndex].PPT[6] = check_to_update(S[slaveIndex].PPT[6], S[slaveIndex].PT[6], 18);
    S[slaveIndex].T[6] = temperature_convert_to_normal(S[slaveIndex].PT[6], S[slaveIndex].Cmpns[6], -99, 99, 0);

    S[slaveIndex].PPT[7] = check_to_update(S[slaveIndex].PPT[7], S[slaveIndex].PT[7], 19);
    S[slaveIndex].T[7] = temperature_convert_to_normal(S[slaveIndex].PT[7], S[slaveIndex].Cmpns[7], -99, 99, 0);

    S[slaveIndex].PPT[0] = check_to_update(S[slaveIndex].PPT[0], S[slaveIndex].PT[0], 20);
    S[slaveIndex].T[0] = temperature_convert_to_normal(S[slaveIndex].PT[0]/10, S[slaveIndex].Cmpns[0], -99, 99, (S[slaveIndex].PT[0] == T_NULL));

    tmpInputs = S[slaveIndex].PrvDI^S[slaveIndex].DigitalInputs;
    S[slaveIndex].PrvDI = S[slaveIndex].DigitalInputs;


    temp_to_xchar_3(S[0].T[1], Temperatures.T1, 0);
    temp_to_xchar_3(S[0].T[2], Temperatures.T2, 0);
    temp_to_xchar_3(S[0].T[3], Temperatures.T3, 0);
    temp_to_xchar_3(S[0].T[4], Temperatures.T4, 0);
    temp_to_xchar_3(S[0].T[5], Temperatures.T5, 0);
    temp_to_xchar_3(S[0].T[6], Temperatures.T6, 0);
    temp_to_xchar_3(S[0].T[7], Temperatures.T7, 0);
    temp_to_xchar_3(S[0].T[0] * 10, Temperatures.TZ, 0);


    return eventLog;
}

int16_t check_to_update(int16_t prvVal, int16_t actVal, uint8_t _bit) {
    if (prvVal != actVal)
//        gui_refresh_bits_0 |= (1 << _bit);
    return actVal;
}

uint16_t clip_max_value(uint16_t value, uint16_t max) {
    if (value > max) return max;
    return value;
}
#ifdef PWMSlave
uint16_t PWMframe_get_item(char* frame, uint8_t start, char* clipped, uint8_t size){
    int32_t result = 0;
    uint8_t i = 0;
    for (i = 0; i < size; i++)
        clipped[i] = frame[start + i];
    if (sscanf(clipped, "%x", &result) < 1) return 0;
    return (uint16_t)result;
}

uint8_t PWMframe_get_data(_slavePWMFrame * raw, uint8_t slaveIndex, uint8_t cmpnsStart, uint8_t clrFlag) {
    uint8_t eventLog = 0;
    if (clrFlag == 1) {
        if (SPWM[slaveIndex].AbsenceCnt < MAX_ABSENCE) {
            if (SPWM[slaveIndex].AbsenceCnt == MAX_ABSENCE - 1) eventLog = 1;
            SPWM[slaveIndex].AbsenceCnt++;
        }
        else {
            SPWM[slaveIndex].PWM1o = 0;
            SPWM[slaveIndex].PWM2o = 0;
        }
    }
    else {
        if (SPWM[slaveIndex].AbsenceCnt == MAX_ABSENCE) eventLog = 1;
        SPWM[slaveIndex].AbsenceCnt = 0;
        if ((raw->PWM1 < 201) && (raw->PWM1 > 0)) SPWM[slaveIndex].PWM1o = raw->PWM1;
        else SPWM[slaveIndex].PWM1o = 0;
        if ((raw->PWM2 < 201) && (raw->PWM2 > 0)) SPWM[slaveIndex].PWM2o = raw->PWM2;
        else SPWM[slaveIndex].PWM2o = 0;
        SPWM[slaveIndex].Temp = raw->St;
    }





    return eventLog;
}
#endif



void BusDriverEnable(void)
{
	 //HAL_GPIO_WritePin(UA5_EN_GPIO_Port, UA5_EN_Pin, SET);
}


void BusDriverDisable(void)
{
	//HAL_GPIO_WritePin(UA5_EN_GPIO_Port, UA5_EN_Pin, RESET);
}


 void UARTSendDataByte(UART_HandleTypeDef * UART, char * datas, uint8_t len)
 {

	 HAL_GPIO_WritePin(UA5_EN_GPIO_Port, UA5_EN_Pin, SET);
	 osDelay(1);
	 HAL_UART_Transmit_DMA(UART, &datas[0], len);

	// HAL_UART_Transmit(&huart1, &datas[0], len, 100);

 }

 void UARTReadDataByte(UART_HandleTypeDef * UART, char * datas, uint8_t len)
 {

	 //HAL_UART_Receive_IT(UART, &datas[0], len);
	 //HAL_UART_Transmit(&huart1, &datas[0], len, 100);

 }
volatile uint32_t cccc= 0;
 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 {
	 cccc++;
 }

 void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
 {
	 HAL_GPIO_WritePin(UA5_EN_GPIO_Port, UA5_EN_Pin, RESET);

	 if(send_uart_nr == 1)
	 {
         memset(received_bytes,' ',42);
         HAL_UART_Receive_DMA(&huart5, &received_bytes[0], 42);

         send_uart_nr = 11;
	 }

	 if(send_uart_nr == 2)
	 {
         memset(received_bytes_PWM,' ',20);
         HAL_UART_Receive_DMA(&huart5, &received_bytes_PWM[0], 20);
         send_uart_nr = 12;
	 }

 }
