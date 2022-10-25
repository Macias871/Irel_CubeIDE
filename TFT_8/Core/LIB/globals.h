#ifndef GLOBALS_H
#define GLOBALS_H

#include <string.h>
#include "main.h"
#include "cmsis_os.h"
#include "BUS.h"

extern xSemaphoreHandle refresh_data_mutex;

#define DELAY_1S (1000 / portTICK_RATE_MS)
#define swap(a, b)  a ^= b; b ^= a; a ^= b;

#define MON 0
#define TUE 1
#define WEN 2
#define THU 3
#define FRI 4
#define SAT 5
#define SUN 6
#define TYPE_CO 0
#define TYPE_CWU 1
#define TYPE_CIRC 2
#define ALARMSH_SIZE 12
#define EVENTS_SIZE 69
#define ALARMS_SIZE 69

#define plA	0x0104
#define pla	0x0105
#define plC	0x0106
#define plc	0x0107
#define plE	0x0118
#define ple	0x0119
#define plL	0x0141
#define pll	0x0142
#define plN	0x0143
#define pln	0x0144
#define plO	0x00D3
#define plo	0x00F3
#define plS	0x015A
#define pls	0x015B
#define plX	0x0179
#define plx	0x017A
#define plZ	0x017B
#define plz	0x017C
#define stC	0x00B0

#define deA     0x00C4
#define dea     0x00E4
#define deO     0x00D6
#define deo     0x00F6
#define deU     0x00DC
#define deu     0x00FC
#define deB     0x00DF



#define hcm30c	55
#define hcm29c	54
#define hcm28c	53
#define hcm27c	52
#define hcm26c	51
#define hcm25c	50
#define hcm24c	49
#define hcm23c	48
#define hcm22c	47
#define hcm21c	46
#define hcm20c	45
#define hcm19c	44
#define hcm18c	43
#define hcm17c	42
#define hcm16c	41
#define hcm15c	40
#define	hcm14c	39
#define hcm13c	38
#define hcm12c	37
#define hcm11c	36
#define hcm10c	35
#define hcm09c	34
#define hcm08c	33
#define hcm07c	32
#define hcm06c	31
#define hcm05c	30
#define hcm04c	29
#define hcm03c	28
#define hcm02c	27
#define hcm01c	26
#define hc0c	25
#define hcp01c	24
#define hcp02c	23
#define hcp03c	22
#define hcp04c	21
#define hcp05c	20
#define hcp06c	19
#define hcp07c	18
#define hcp08c	17
#define hcp09c	16
#define hcp10c	15
#define hcp11c	14
#define hcp12c	13
#define hcp13c	12
#define hcp14c	11
#define hcp15c	10
#define hcp16c	9
#define hcp17c	8
#define hcp18c	7
#define hcp19c	6
#define hcp20c	5
#define hcp21c	4
#define hcp22c	3
#define hcp23c	2
#define hcp24c	1
#define hcp25c	0

#define numberOfWeekDays		3
#define coHeating			0
#define cwuHeating			1
#define maxInsideTemp			35
#define minInsideTemp			13

#define WD_MON				0
#define WD_TUE				1
#define WD_WEN				2
#define WD_THU				3
#define WD_FRI				4
#define WD_SAT				5
#define WD_SUN				6

#define WD_PR1 0
#define WD_PR2 1
#define WD_PR3 2
#define WD_PR4 3
#define WD_PR5 4
#define WD_PR6 5
#define WD_PR7 6

#define T_NULL 5000

#define globalsCo 0
#define globalsCwuOn 1
#define globalsCwuOff 2

#define legionellaMaxTemp 60

#define UPDATE_ITEM0	0x00000001
#define UPDATE_ITEM1	0x00000002
#define UPDATE_ITEM2	0x00000004
#define UPDATE_ITEM3	0x00000008
#define UPDATE_ITEM4	0x00000010
#define UPDATE_ITEM5	0x00000020
#define UPDATE_ITEM6	0x00000040
#define UPDATE_ITEM7	0x00000080
#define UPDATE_ITEM8	0x00000100
#define UPDATE_ITEM9	0x00000200
#define UPDATE_ITEM10	0x00000400
#define UPDATE_ITEM11	0x00000800
#define UPDATE_ITEM12	0x00001000
#define UPDATE_ITEM13	0x00002000
#define UPDATE_ITEM14	0x00004000
#define UPDATE_ITEM15	0x00008000
#define UPDATE_ITEM16	0x00010000
#define UPDATE_ITEM17	0x00020000
#define UPDATE_ITEM18	0x00040000
#define UPDATE_ITEM19	0x00080000
#define UPDATE_ITEM20	0x00100000
#define UPDATE_ITEM21	0x00200000
#define UPDATE_ITEM22	0x00400000
#define UPDATE_ITEM23	0x00800000
#define UPDATE_ITEM24	0x01000000
#define UPDATE_ITEM25	0x02000000
#define UPDATE_ITEM26	0x04000000
#define UPDATE_ITEM27	0x08000000
#define UPDATE_ITEM28	0x10000000
#define UPDATE_ITEM29	0x20000000
#define UPDATE_ITEM30	0x40000000
#define UPDATE_ITEM31	0x80000000

// ak ograniczenia
#define MAXTDZ 40
#define MINTDZ -15
#define MINTGDZ 15
#define MAXDCWU 10
#define MINDCWU 5

extern xQueueHandle xEthParamsQueue;
extern xQueueHandle uart_rx_data_queue;
extern xQueueHandle xDebugQueueHandle;
extern xTaskHandle xBusTaskHandle;
extern xTaskHandle xEthTaskHandle;

extern uint8_t PWMy[2];

extern char PWM1[5];
extern char PWM2[5];

typedef struct {
    unsigned WP:    1;
    unsigned PNC:   1;
    unsigned POP:   1;
    unsigned PWC:   1;
    unsigned ZZ:    1;
    unsigned WS:    1;
    unsigned IH:    1;
    unsigned :      1;
} _inputs;
#if 0
typedef struct {
    unsigned ZZC:   1;
    unsigned DO2:   1;
    unsigned DO1:   1;
    unsigned Z3D:   1;
    unsigned PCWU:  1;
    unsigned PSG:   1;
    unsigned PDZ:   1;
    unsigned SP:    1;
} _outputs;
#else
typedef struct {
    uint8_t ZZC:   1;
    uint8_t DO2:   1;
    uint8_t DO1:   1;
    uint8_t Z3D:   1;
    uint8_t PCWU:  1;
    uint8_t PSG:   1;
    uint8_t PDZ:   1;
    uint8_t SP:    1;
} _outputs;
#endif
typedef struct {
    float T[8];           // Temperatury z dokladnoscia do 1 stopnia
    int16_t PT[8];          // Temperatury z dokladnoscia do 0.1 stopnia
    int16_t PPT[8];         // Poprzednie temperatury z dokladnoscia do 0.1 stopnia
    int8_t Cmpns[8];        // Odchylki temperatur
    uint8_t DigitalInputs;  // Wejscia cyfrowe w stanie surowym
    uint8_t PrvDI;          // Poprzednia wartosc wejsc cyfrowych w stanie surowym
    uint8_t InDelay[8];     // Opoznienia wejsc
    uint8_t InOffCnt[8];    // Liczniki zalaczenia wejsc
    uint8_t InOnCnt[8];     // Liczniki wylaczenia wejsc
    union {
        uint8_t DigitalOutputs;
        _outputs Out;
    };           // Struktura wyjsc
    union {
        uint8_t Inputs;
        _inputs In;
    };           // Struktura wejsc
    uint8_t AbsenceCnt;     // Licznik czasu nieobecnosci
    uint8_t programBits;    // Ustawienia modulu
    uint8_t SprOnDelay;     // Licznik do zalaczenia sprezarki
    uint16_t SprOffTime;    // Minimalny czas przerwy sprezarki
    uint16_t SprOffCnt;     // Licznik do wylaczenia sprezarki
    uint8_t PsgOffDelay;    // Licznik wylaczenia pompy SG
    uint8_t PdzOffDelay;    // Licznik wylaczenia pompy DZ
    uint8_t CwuTempOff;     // Temperatura CWU
    uint32_t Alarms_L;      // Flagi alarmow
    uint32_t Alarms_H;      // Flagi alarmow
    uint8_t PdzAlarmCnt;    // Licznik do uaktywnienia alarmu temparetury DZ
    uint8_t InputsStates;   // Stany normalne wejsc
} SlaveModule;
#ifdef PWMSlave
typedef struct {
    uint8_t Fk;             // Flagi kontrolne
    uint8_t PWM1z;          // Zadana wartość PWM1
    uint8_t PWM1o;          // Odczytana wartość PWM1
    uint8_t PWM2z;          // Zadana wartość PWM2
    uint8_t PWM2o;          // Odczytana wartość PWM2
    uint8_t PWM1i;          // Obliczona wartość PWM1
    uint8_t PWM2i;          // Obliczona wartość PWM2
    uint8_t St1;            // Status wyjścia 1
    uint8_t St2;            // Status wyjścia 2
    uint8_t Temp;           // temperatura
    uint16_t CntInterval1;  // licznik interwal 1
    uint16_t CntInterval2;  // licznik interwal 2
    uint16_t CntCzasSkoku;  // Czas skoku PSG
    uint16_t CntFullVPDZ;  // Czas pracy z maksymalną szybkością
    uint16_t CntFullVPSG;  // Czas pracy z maksymalną szybkością
    uint8_t AbsenceCnt;     // Licznik czasu nieobecnosci
} SlavePWMModule;
#endif
typedef struct {
    uint8_t Hour;       // godzina rozpoczÄ™cia <0, 23>, rozdzielczosc: 1
    uint8_t Minute;     // minuta rozpoczÄ™cia <0, 55>, rozdzielczosc: 5
    uint8_t T;          // temperatura <5, 30>, rozdzielczosc: 1
} _prgLev;
typedef struct {
    _prgLev Levels[7];
} _prgDay;
typedef struct {
    _prgDay Days[7];
    uint8_t LevelsCount;
} _prgWeek;
typedef struct {
    union {
        _prgWeek Data;
        uint8_t Tab[167];
    };
    uint16_t Address;
} prgWeek;
typedef struct {
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t type;
} structAlarm;
typedef struct {
    uint8_t WP;
    uint8_t PNC;
    uint8_t POP;
    uint8_t PWC;
    uint8_t ZZ;
    uint8_t WS;
} inBytes;
typedef struct {
    uint8_t p1;
    uint8_t p2;
    uint8_t p3;
    uint8_t p4;
    uint8_t p5;
    uint8_t p6;
    uint8_t p7;
} prgLev;
typedef struct {
    unsigned ParamNo: 8;
    unsigned SlaveNo: 4;
    unsigned Event: 8;
    unsigned Hour: 8;
    unsigned Minute: 8;
    unsigned ProgramType: 2;
    unsigned WeekDay: 3;
    unsigned Lenght: 8;
    unsigned Lp: 8;
    unsigned First: 8;
} _ethParam;
typedef struct {
    unsigned alarms: 1;
    unsigned alarm_logs: 1;
    unsigned basic: 1;
    unsigned circ: 1;
    unsigned counters: 1;
    unsigned events: 1;
    unsigned info: 1;
    unsigned integral: 1;
    unsigned kg: 1;
    unsigned logs: 1;
    unsigned ord: 1;
    unsigned ovh: 1;
    unsigned prg: 1;
    unsigned programs: 1;
    unsigned reg: 1;
    unsigned slave: 1;
    unsigned time: 1;
    unsigned urlop: 1;
    unsigned wtime: 1;
    unsigned pwm: 1;

} eth_to_log_t;

typedef struct {
    char T1[5];
    char T2[5];
    char T3[5];
    char T4[5];
    char T5[5];
    char T6[5];
    char T7[5];
    char TZ[5];

} _temperatures;



extern  _temperatures Temperatures;


extern volatile _ethParam ethParam;
extern volatile SlaveModule S[7];
#ifdef PWMSlave
extern volatile SlavePWMModule SPWM[7];
#endif
extern volatile uint8_t dey_chg_f;
extern volatile prgWeek P[3];
extern volatile structAlarm alarmItem[ALARMSH_SIZE];
extern volatile eth_to_log_t eth_to_log;
extern volatile uint32_t gui_refresh_bits_0;
extern volatile uint32_t gui_refresh_bits_1;
extern volatile uint32_t updateBits0;
extern volatile uint8_t sys_work_mode;
extern volatile uint8_t sys_work_mode_prv;
extern volatile uint8_t overheating_work_mode;
extern volatile uint8_t urlop_work_mode;
extern volatile int8_t global_temperature_tab[];
extern volatile int8_t global_room_temp_down;
extern volatile int8_t tmp_room_temp_down;
extern volatile uint8_t global_room_temp_ordered;
extern volatile uint8_t global_cwu_temp_cwu_on[];
extern volatile int8_t tmp_cwu_temp_cwu_on;
extern volatile uint8_t tmp_cwu_temp_cwu_off;
extern volatile uint8_t tmp_cwu_temp_readed;
extern volatile int8_t global_cwu_temp_offset_tab[];
extern volatile uint8_t global_prev_temperature_co;
extern volatile int16_t sys_integral_prv;
extern volatile uint8_t sys_room_temperature;
//extern volatile uint16_t sys_inside_temperature;
extern volatile uint8_t refresh_kg;
extern volatile uint16_t integral_delay_time;

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t week_day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} _datetime_struct;
extern volatile _datetime_struct global_time;
/*extern volatile uint8_t sys_date_actual_year;
extern volatile uint8_t sys_date_actual_month;
extern volatile uint8_t sys_date_actual_day;
extern volatile uint8_t sys_date_actual_week_day;
extern volatile uint8_t sys_time_actual_hour;
extern volatile uint8_t sys_time_actual_minute;
extern volatile uint8_t sys_time_actual_second;*/
extern volatile uint8_t sp_have_to_set_flag;
extern volatile uint8_t psg_on_delay;
extern volatile uint8_t spr_on_cnt_local[];
extern volatile uint8_t pdz_off_cnt_local[];
extern volatile uint8_t kg_mul;
extern volatile int16_t sys_integral;
extern volatile uint8_t integral_delay;
extern volatile uint8_t integral_spring;
extern volatile uint32_t integral_set_counter;
extern volatile long long_integral;
extern volatile int16_t delta_temp;
extern volatile int16_t delta_time;
extern volatile uint8_t sys_integral_time;
extern volatile uint8_t integral_period_time;
extern volatile uint8_t integral_period_counter;
extern volatile int16_t integral_levels[];
extern volatile int8_t heating_on_temperature;
extern volatile int8_t heating_off_temperature;
extern volatile uint16_t cwuTime;
extern volatile uint16_t cntCwu;
extern volatile uint16_t coTime;
extern volatile uint16_t cntCo;

/* legionella */
extern volatile uint16_t legionellaCnt;
extern volatile uint8_t legionellaDay;
extern volatile uint8_t legionellaHour;
extern volatile uint8_t legionella_down_counter;
extern volatile uint8_t prvTimeToLegionella;
extern volatile uint8_t legionella_interval;
extern volatile uint8_t legTime;

extern volatile uint8_t sys_time_hour;
extern volatile uint8_t sys_time_minute;
extern volatile uint8_t sys_date_day;
extern volatile uint8_t sys_date_month;
extern volatile uint8_t sys_date_year;

extern volatile uint8_t legionellaFlags;
#define legionellaEnSet()	legionellaFlags |= (1<<0)
#define legionellaEnClr()	legionellaFlags &=~ (1<<0)
#define legionellaEnChk()	legionellaFlags & 0x01

extern volatile int8_t act_state;
extern volatile uint8_t event_register_length;
extern volatile uint8_t event_register_start_address;

/* czas bezczynnoĹ›ci */
#define systemIdleState()	(S[0].Out.PSG == 0)
extern volatile uint16_t system_idle_counter;

/* alarmy */
#define ALARM_PWC	1	// alarm wysokiego cisnienia
#define ALARM_PNC	2	// alarm niskiego cisnienia
#define ALARM_ZZ	3	// alarm zasilania
#define ALARM_T2	4	// zbyt wysoka T2
#define ALARM_TZ	5	// brak czujnika Tz
#define ALARM_T1	6	// brak czujnika T1
#define ALARM_DZ	7	// zbyt niska temp dolnego Zrodla
#define ALARM_WP	8	// zbyt wysoki powrot
#define ALARM_BM	9	// brak modulu wykonawczego
#define ALARM_IWP	10	// wylacznik przeplywowy

extern volatile uint8_t alarmFirst;

/* czasy zwloki */
#define restorePopDelay() S[0].InDelay[2] = prvPopDelay
extern volatile uint8_t prvModuleIn;

#define USER_1		1
#define USER_2		2
#define SERVICE_1	3

/* Deklaracje jezykow */
#define LANG_PL 0
#define LANG_DE 1

extern volatile uint8_t cntBreakPer;

extern volatile uint16_t gui_idle_time;
extern volatile uint16_t gui_idle_counter;
extern volatile uint16_t tft_flash_counter;
extern volatile uint8_t markedDay;
extern volatile uint8_t markedPr;
extern volatile uint8_t prgPrevHourToChange;
extern volatile uint8_t prgHourToChange;
extern volatile int8_t prgMinuteToChange;
extern volatile uint8_t prgNextHourToChange;
extern volatile uint8_t prgTempToChange;
extern volatile uint8_t prgType;
extern volatile uint8_t prgWeekDayIndex;
extern volatile uint8_t prgLevelIndex;
extern volatile uint8_t serviceError;
#define serviceErrorSet() (serviceError |= (1<<0))
#define serviceErrorClr() (serviceError &=~ (1<<0))
#define serviceErrorChk() (serviceError & 0x01)
//extern uint8_t prgTab[196];
//#define TEMP_CTRL 2
#define TIME_CTRL 1
extern volatile uint8_t sys_cwu_mode;
extern volatile uint8_t circulation_enabled;
extern volatile uint8_t circCwuTemp;
extern volatile uint8_t circCwuTimeOn;
extern volatile uint8_t circCwuTimeOff;
extern volatile uint8_t tmpTabU8[10];
extern volatile int8_t tmpTab8[10];
extern volatile uint16_t tmpTabU16[10];
extern volatile int16_t tmpTab16[10];
extern volatile uint8_t backlightInt;
extern volatile uint8_t startCnt;
extern const int16_t TempTab080[];
extern const int16_t TempTabm2030[];
extern const int16_t TempTabm4060[];
extern volatile uint8_t sysMaxTemp;
extern volatile uint8_t sysMinTemp;
extern volatile uint8_t delta_CWU;
extern volatile uint8_t sysLegTemp;
extern volatile int8_t sysMaxDZ;
extern volatile int8_t sysMinDZ;
extern volatile uint8_t urlop_days_number;
extern volatile uint8_t urlop_co_temp;
extern volatile uint8_t urlop_cwu_temp;
extern volatile uint8_t urlop_is_cwu;
extern volatile uint8_t urlop_enable_down_counter;
extern volatile uint8_t annealing[5];
extern volatile uint8_t overheating_down_counter;
extern volatile uint8_t prvAnnealingCnt;
extern volatile uint8_t system_log_ready;
//extern double kgOffset[10];
extern volatile uint8_t kgOffset[10];
extern volatile int16_t kgPrvArray[12];
extern volatile int8_t kgAngle;
extern volatile uint16_t display_orientation;
extern uint8_t sys_language;

#define EVENT_ALARM_WC			0x01
#define EVENT_ALARM_NC			0x02
#define EVENT_ALARM_ZZ			0x03
#define EVENT_ALARM_WS			0x04
#define EVENT_ALARM_WP                  0x05
#define EVENT_ALARM_T1			0x06
#define EVENT_ALARM_T2			0x07
#define EVENT_ALARM_T3			0x08
#define EVENT_ALARM_T4			0x09
#define EVENT_ALARM_T5			0x0A
#define EVENT_ALARM_T6			0x0B
#define EVENT_ALARM_T7			0x0C
#define EVENT_ALARM_TZ			0x0D
#define EVENT_ALARM_T2ZW                0x0E
#define EVENT_ALARM_TDZ                 0x0F
#define EVENT_ZWP                       0x10
#define EVENT_S01_DISABLE		0x11

#define EVENT_SP_ON			0x13
#define EVENT_SP_OFF			0x14
#define EVENT_PDZ_ON			0x15
#define EVENT_PDZ_OFF			0x16
#define EVENT_PSG_ON			0x17
#define EVENT_PSG_OFF			0x18
#define EVENT_PCWU_ON			0x19
#define EVENT_PCWU_OFF			0x1A
#define EVENT_Z3D_CO			0x1B
#define EVENT_Z3D_CWU			0x1C
#define EVENT_DO1_ON			0x1D
#define EVENT_DO1_OFF			0x1E
#define EVENT_DO2_ON			0x1F
#define EVENT_DO2_OFF			0x20
#define EVENT_LEG_BREAK			0x21
#define EVENT_ZZC_ON			0x22
#define EVENT_ZZC_OFF			0x23
#define EVENT_CRITICAL_ENTER            0x24
#define EVENT_CRITICAL_EXIT		0x25
#define EVENT_POWER_ON                  0x26
#define EVENT_WM_CHANGED                0x27
#define EVENT_BATTERY_ERROR             0x28

#define ITEM0           0x0000000000000001
#define ITEM1           0x0000000000000002
#define ITEM2           0x0000000000000004
#define ITEM3           0x0000000000000008
#define ITEM4           0x0000000000000010
#define ITEM5           0x0000000000000020
#define ITEM6           0x0000000000000040
#define ITEM7           0x0000000000000080
#define ITEM8           0x0000000000000100
#define ITEM9           0x0000000000000200
#define ITEM10          0x0000000000000400
#define ITEM11          0x0000000000000800
#define ITEM12          0x0000000000001000
#define ITEM13          0x0000000000002000
#define ITEM14          0x0000000000004000
#define ITEM15          0x0000000000008000
#define ITEM16          0x0000000000010000
#define ITEM17          0x0000000000020000
#define ITEM18          0x0000000000040000
#define ITEM19          0x0000000000080000
#define ITEM20          0x0000000000100000
#define ITEM21          0x0000000000200000
#define ITEM22          0x0000000000400000
#define ITEM23          0x0000000000800000
#define ITEM24          0x0000000001000000
#define ITEM25          0x0000000002000000
#define ITEM26          0x0000000004000000
#define ITEM27          0x0000000008000000
#define ITEM28          0x0000000010000000
#define ITEM29          0x0000000020000000
#define ITEM30          0x0000000040000000
#define ITEM31          0x0000000080000000
#define ITEM32          0x0000000100000000
#define ITEM33          0x0000000200000000
#define ITEM34          0x0000000400000000
#define ITEM35          0x0000000800000000
#define ITEM36          0x0000001000000000
#define ITEM37          0x0000002000000000
#define ITEM38          0x0000004000000000
#define ITEM39          0x0000008000000000
#define ITEM40          0x0000010000000000
#define ITEM41          0x0000020000000000
#define ITEM42          0x0000040000000000
#define ITEM43          0x0000080000000000
#define ITEM44          0x0000100000000000
#define ITEM45          0x0000200000000000
#define ITEM46          0x0000400000000000
#define ITEM47          0x0000800000000000
#define ITEM48          0x0001000000000000
#define ITEM49          0x0002000000000000
#define ITEM50          0x0004000000000000
#define ITEM51          0x0008000000000000
#define ITEM52          0x0010000000000000
#define ITEM53          0x0020000000000000
#define ITEM54          0x0040000000000000
#define ITEM55          0x0080000000000000
#define ITEM56          0x0100000000000000
#define ITEM57          0x0200000000000000
#define ITEM58          0x0400000000000000
#define ITEM59          0x0800000000000000
#define ITEM60          0x1000000000000000
#define ITEM61          0x2000000000000000
#define ITEM62          0x4000000000000000
#define ITEM63          0x8000000000000000

extern volatile uint8_t circEn;
extern volatile uint16_t prvScreenNumber;
extern volatile uint16_t tmpScreenNumber;
extern volatile uint8_t act_page;
extern volatile uint8_t overheating_enable_flag;
extern volatile uint8_t urlop_enable_flag;
extern volatile uint8_t system_state;
extern volatile uint16_t integral_flags;
extern volatile int16_t temp_result[];
extern volatile uint8_t sys_enabled_slaves;
extern volatile uint8_t sys_room_t_sensor_cfg;
extern volatile uint8_t PWM_enable;
extern volatile uint8_t PWM_optym_en;
extern volatile uint8_t PWM_optym_page;
extern volatile uint8_t PWM_vc_pdz;
extern volatile uint8_t PWM_vc_pco;
extern volatile uint8_t PWM_i_co;
extern volatile uint8_t PWM_i_cwu;
extern volatile uint8_t PWM_i_pdz;
extern volatile uint8_t PWM_vs_pco;
extern volatile uint8_t PWM_vs_pdz;
extern volatile uint8_t PWM_rt_co;
extern volatile uint8_t PWM_rt_dz;
extern volatile uint8_t PWM_vj_pco;
extern volatile uint8_t PWM_cs_pco;
extern volatile uint8_t PWM_ws_pco;
extern volatile uint8_t tft_reinitialize_flag;
extern volatile uint16_t tft_reinitialize_counter;
extern volatile uint8_t system_wait_flag;
extern volatile uint8_t log_lock;
extern volatile uint8_t act_view;
extern char debMsg[200];
extern volatile uint32_t battery_voltage;
extern volatile uint8_t tpIdleTime;
extern volatile uint8_t delayCnt;
extern volatile uint8_t alarmsLenght;
extern volatile uint8_t alarmsStart;
extern volatile uint8_t gvar_is_connected;
extern volatile uint8_t gvar_get_ping;

extern int8_t basic_hc_default_wall[];
extern int8_t basic_hc_default_floor[];
extern int8_t basic_hc[];
extern int8_t offset_hc[];
extern int8_t tmp_offset_hc[];
extern int8_t user_hc[];
extern int8_t tmp_user_hc[];
extern int8_t system_hc[];
extern int8_t tmp_system_hc[];
extern int8_t program_hc[];
extern int8_t program_full_hc[60];
extern int8_t hc_actual_possition;
extern int8_t tmp_hc_actual_possition;

#define DEV_BASIC_R     30
#define DEV_INFO        31
#define DEV_LOGS        32
#define DEV_ORD_R       33
#define DEV_OVH_R       34
#define DEV_SLAVE_R     35
#define DEV_TIME_R      36
#define DEV_URLOP_R     37
#define DEV_WTIME_R     38
#define DEV_PRG_R       39
#define DEV_INTEGRAL_R  40
#define DEV_EVENTS      41
#define DEV_REG         42
#define DEV_ALARMS_R    43
#define DEV_COUNTERS_R  44
#define DEV_KG_R        45
#define DEV_PROGRAMS_R  46
#define DEV_CIRC_R      47
#define DEV_ALARM_LOGS  48
#define DEV_PWM_R       49
#define DEV_UPDATE      100

#define ETH_LOG_TIME()      eth_queue_add(DEV_TIME_R, 0, 0U, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_TIME_FAST() eth_queue_add(DEV_TIME_R, 0, 0U, 0U, 0U, 0U, 0U, 1U)

#define ETH_LOG_BASIC()         eth_queue_add(DEV_BASIC_R, 0U, 0U, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_BASIC_FAST()    eth_queue_add(DEV_BASIC_R, 0U, 0U, 0U, 0U, 0U, 0U, 1U)

#define ETH_LOG_INFO() eth_queue_add(DEV_INFO, 0U, 0U, 0U, 0U, 0U, 0U, 0U)

#define ETH_LOG_LOG(e)      eth_queue_add(DEV_LOGS, 0U, e, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_LOG_FAST(e) eth_queue_add(DEV_LOGS, 0U, e, 0U, 0U, 0U, 0U, 1U)

#define ETH_LOG_ALARM(e)        eth_queue_add(DEV_ALARM_LOGS, 0U, e, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_ALARM_FAST(e)   eth_queue_add(DEV_ALARM_LOGS, 0U, e, 0U, 0U, 0U, 0U, 1U)

#define ETH_LOG_SLAVE(e)        eth_queue_add(DEV_SLAVE_R, e, 0U, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_SLAVE_FAST(e)   eth_queue_add(DEV_SLAVE_R, e, 0U, 0U, 0U, 0U, 0U, 1U)

#define ETH_LOG_WTIME()         eth_queue_add(DEV_WTIME_R, 0U, 0U, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_WTIME_FAST()    eth_queue_add(DEV_WTIME_R, 0U, 0U, 0U, 0U, 0U, 0U, 1U)

#define ETH_LOG_PRG(no, wd)         eth_queue_add(DEV_PRG_R, 0, 0U, 0U, 0U, no, wd, 0U)
#define ETH_LOG_PRG_FAST(no, wd)    eth_queue_add(DEV_PRG_R, 0, 0U, 0U, 0U, no, wd, 1U)

#define ETH_LOG_URLOP()         eth_queue_add(DEV_URLOP_R, 0U, 0U, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_URLOP_FAST()    eth_queue_add(DEV_URLOP_R, 0U, 0U, 0U, 0U, 0U, 0U, 1U)

#define ETH_LOG_OVH()           eth_queue_add(DEV_OVH_R, 0U, 0U, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_OVH_FAST()      eth_queue_add(DEV_OVH_R, 0U, 0U, 0U, 0U, 0U, 0U, 1U)

#define ETH_LOG_INTEGRAL()      eth_queue_add(DEV_INTEGRAL_R, 0U, 0U, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_INTEGRAL_FAST() eth_queue_add(DEV_INTEGRAL_R, 0U, 0U, 0U, 0U, 0U, 0U, 1U)

#define ETH_LOG_REG(e)  eth_queue_add(DEV_REG, e, 0U, 0U, 0U, 0U, 0U, 0U)

#define ETH_LOG_ALARMS(e)   eth_queue_add(DEV_ALARMS_R, e, 0U, 0U, 0U, 0U, 0U, 0U)

#define ETH_LOG_COUNTERS()  eth_queue_add(DEV_COUNTERS_R, 0U, 0U, 0U, 0U, 0U, 0U, 0U)

#define ETH_LOG_KG(e)       eth_queue_add(DEV_KG_R, 0U, 0U, 0U, 0U, e, 0U, 0U)
#define ETH_LOG_KG_FAST(e)  eth_queue_add(DEV_KG_R, 0U, 0U, 0U, 0U, e, 0U, 1U)

#define ETH_LOG_PROGRAMS()      eth_queue_add(DEV_PROGRAMS_R, 0U, 0U, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_PROGRAMS_FAST() eth_queue_add(DEV_PROGRAMS_R, 0U, 0U, 0U, 0U, 0U, 0U, 1U)

#define ETH_LOG_CIRC()      eth_queue_add(DEV_CIRC_R, 0U, 0U, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_CIRC_FAST() eth_queue_add(DEV_CIRC_R, 0U, 0U, 0U, 0U, 0U, 0U, 1U)

#define ETH_LOG_PWM()      eth_queue_add(DEV_PWM_R, 0U, 0U, 0U, 0U, 0U, 0U, 0U)
#define ETH_LOG_PWM_FAST() eth_queue_add(DEV_PWM_R, 0U, 0U, 0U, 0U, 0U, 0U, 1U)

#define SET_TO_UPDATE_DATE_TIME()       gui_refresh_bits_0 |= (1 << 0)
#define SET_TO_UPDATE_WORK_MODE()       gui_refresh_bits_0 |= (1 << 1)
#define SET_TO_UPDATE_ITNEGRAL()        gui_refresh_bits_0 |= (1 << 2)
#define SET_TO_UPDATE_CURVE()           gui_refresh_bits_0 |= (1 << 3)
#define SET_TO_UPDATE_INPUTS()          gui_refresh_bits_0 |= (1 << 4)
#define SET_TO_UPDATE_MODULE_6()        gui_refresh_bits_0 |= (1 << 5)
#define SET_TO_UPDATE_MODULE_5()        gui_refresh_bits_0 |= (1 << 6)
#define SET_TO_UPDATE_MODULE_4()        gui_refresh_bits_0 |= (1 << 7)
#define SET_TO_UPDATE_MODULE_3()        gui_refresh_bits_0 |= (1 << 8)
#define SET_TO_UPDATE_MODULE_2()        gui_refresh_bits_0 |= (1 << 9)
#define SET_TO_UPDATE_MODULE_1()        gui_refresh_bits_0 |= (1 << 10)
#define SET_TO_UPDATE_ROOM_TEMP()       gui_refresh_bits_0 |= (1 << 11)
#define SET_TO_UPDATE_COUNTED_CO_TEMP() gui_refresh_bits_0 |= (1 << 12)
#define SET_TO_UPDATE_T1()              gui_refresh_bits_0 |= (1 << 13)
#define SET_TO_UPDATE_T2()              gui_refresh_bits_0 |= (1 << 14)
#define SET_TO_UPDATE_T3()              gui_refresh_bits_0 |= (1 << 15)
#define SET_TO_UPDATE_T4()              gui_refresh_bits_0 |= (1 << 16)
#define SET_TO_UPDATE_T5()              gui_refresh_bits_0 |= (1 << 17)
#define SET_TO_UPDATE_T6()              gui_refresh_bits_0 |= (1 << 18)
#define SET_TO_UPDATE_T7()              gui_refresh_bits_0 |= (1 << 19)
#define SET_TO_UPDATE_TZ()              gui_refresh_bits_0 |= (1 << 20)
#define SET_TO_UPDATE_IWP()             gui_refresh_bits_0 |= (1 << 21)
#define SET_TO_UPDATE_IPNC()            gui_refresh_bits_0 |= (1 << 22)
#define SET_TO_UPDATE_IPOP()            gui_refresh_bits_0 |= (1 << 23)
#define SET_TO_UPDATE_IPWC()            gui_refresh_bits_0 |= (1 << 24)
#define SET_TO_UPDATE_IZZ()             gui_refresh_bits_0 |= (1 << 25)
#define SET_TO_UPDATE_IWS()             gui_refresh_bits_0 |= (1 << 26)
#define SET_TO_UPDATE_IIH()             gui_refresh_bits_0 |= (1 << 27)
#define SET_TO_UPDATE_OSP()             gui_refresh_bits_0 |= (1 << 28)
#define SET_TO_UPDATE_ODZ()             gui_refresh_bits_0 |= (1 << 29)
#define SET_TO_UPDATE_OSG()             gui_refresh_bits_0 |= (1 << 30)
#define SET_TO_UPDATE_OCWU()            gui_refresh_bits_0 |= (1 << 31)
#define SET_TO_UPDATE_OZ3D()            gui_refresh_bits_1 |= (1 << 0)
#define SET_TO_UPDATE_ODO1()            gui_refresh_bits_1 |= (1 << 1)
#define SET_TO_UPDATE_ODO2()            gui_refresh_bits_1 |= (1 << 2)
#define SET_TO_UPDATE_OZZC()            gui_refresh_bits_1 |= (1 << 3)
#define SET_TO_UPDATE_IP()              gui_refresh_bits_1 |= (1 << 4)
#define SET_TO_UPDATE_V_BATT()          gui_refresh_bits_1 |= (1 << 5)
#define SET_TO_UPDATE_OSP_BLINK()       gui_refresh_bits_1 |= (1 << 6)
#define SET_TO_UPDATE_EVENTS()          gui_refresh_bits_1 |= (1 << 7)
#define SET_TO_UPDATE_INTEGRAL_CNT()    gui_refresh_bits_1 |= (1 << 8)
#define SET_TO_UPDATE_WORKTIMES()       gui_refresh_bits_1 |= (1 << 9)

void beep(void);
void error_beep(void);

int16_t ADCPT1000_to_temp(uint16_t adc);
int16_t ADCPT1000_to_temp_old(uint16_t adc);
int16_t ADCNTCZ_to_temp(uint16_t adc);
#define XCHAR   char


void out_do_1_set(void);
void out_do_2_set(void);
void out_zzc_set(void);
void out_zzc_clr(void);
void out_p_cwu_set(void);
void out_p_cwu_clr(void);
void out_do_1_clr(void);
void out_do_2_clr(void);
void out_sp_clr(uint8_t module);
uint8_t out_sp_set(uint8_t module);
void out_p_dz_set(uint8_t module);
void out_p_dz_clr(uint8_t module);
void out_p_sg_set(uint8_t module);
void out_p_sg_clr(uint8_t module);
void out_z3d_set(uint8_t module);
void out_z3d_clr(uint8_t module);
void ext_ram_save_integral(void);
void ext_ram_save_basic(void);
void ext_ram_save_circ(void);
void ext_ram_save_ovh(void);
void ext_ram_save_programs(void);
void ext_ram_save_slave(uint8_t slave_no);
void ext_ram_save_kg(uint8_t kg_id);
void temp_to_xchar_3(int16_t integer, XCHAR *result, uint8_t startIndex);
#endif
