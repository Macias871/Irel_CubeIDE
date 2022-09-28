
#define PK_EXIT 0xffff
#define PK_SET 0
#define PK_CLR 1
#define PK_ASTAB 2
#define PK_BISTAB 3
#define PK_JOJ1 4
#define PK_JOJ2 5
#define PK_JOJ3 6
#define PK_JOJ4 7
#define PK_JOJ5 8
#define PK_ANGT 9
#define PK_ANLT 10
#define PK_PULSE 11
#define PK_OR 12
#define PK_AND 13
#define PK_NOT 14
#define PK_DEMUX3 15
#define PK_ZERO 16
#define PK_ONE 17
#define PK_JOJE 18
#define PK_ASTABT 19


uint8_t tab_chk_bit(uint8_t * const tab, const uint16_t bit);

/**
 * @brief Realization of PK_SET function
 * @details Set pk_no bit if bit_no bit is 1
 * @param bits_tab Array of available input bits
 * @param pk_no Index of output in pk_tab
 * @param bit_no Index of input bit in bits_tab
 */
void pk_set_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_no
);

/**
 * @brief Realization of PK_CLR function
 * @details Clear pk_no bit if bit_no bit is 1
 * @param bits_tab Array of available input bits
 * @param pk_no Index of output in pk_tab
 * @param bit_no Index of input bit in bits_tab
 */
void pk_clr_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_no
);

/**
 * @brief Realization of PK_ASTAB function
 * @details Set pk_no bit bit_no bit is 1 and clear when is 0
 * @param bits_tab Array of available input bits
 * @param pk_no Index of output in pk_tab
 * @param bit_no Index of input bit in bits_tab
 */
void pk_astab_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_no
);

/**
 * @brief Realization of PK_BISTAB function
 * @details Set pk_no bit when bit_no is 1 and pk_no is 0
 * Clear pk_no bit when bit_no = 1 and pk_no = 1
 * @param bits_tab Array of available input bits
 * @param counters_tab Array of available counters
 * @param time_tab Array of available time values
 * @param pk_no Index of output in pk_tab
 * @param bit_no Index of input bit in bits_tab
 * @param counter_no Index of counter in counters_tab
 * @param time_no Index of time value in time_tab
 */
void pk_bistab_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_no,
	const uint16_t counter_no,
	const uint16_t time_no
);

/**
 * @brief Realization of PK_JOJ1 function
 * @details First gear with change direction delay.
 * @param bits_tab Array of available input bits
 * @param counters_tab Array of available counters
 * @param time_tab Array of available time values
 * @param pk_no Index of output in pk_tab
 * @param bit_1_no Index of input bit in bits_tab
 * @param bit_2_no Index of input bit in bits_tab
 * @param counter_no Index of counter in counters_tab
 * @param time_no Index of time value in time_tab
 */
void pk_joj1_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no,
	const uint16_t counter_no,
	const uint16_t time_no
);

/**
 * @brief Realization of PK_JOJ2 function
 * @details Second gear with turn on delay.
 * @param bits_tab Array of available input bits
 * @param counters_tab Array of available counters
 * @param time_tab Array of available time values
 * @param pk_no Index of output in pk_tab
 * @param bit_1_no Index of input bit in bits_tab
 * @param bit_2_no Index of input bit in bits_tab
 * @param counter_no Index of counter in counters_tab
 * @param time_no Index of time value in time_tab
 */
void pk_joj2_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no,
	const uint16_t counter_no,
	const uint16_t time_no
);

/**
 * @brief Realization of PK_JOJ3 function
 * @details Second gear with turn on delay.
 * @param bits_tab Array of available input bits
 * @param counters_tab Array of available counters
 * @param time_tab Array of available time values
 * @param pk_no Index of output in pk_tab
 * @param bit_no Index of input bit in bits_tab
 * @param counter_no Index of counter in counters_tab
 * @param time_no Index of time value in time_tab
 */
void pk_joj3_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_no,
	const uint16_t counter_no,
	const uint16_t time_no
);

/**
 * @brief Realization of PK_JOJ4 function
 * @details Second gear with turn on delay.
 * @param bits_tab Array of available input bits
 * @param counters_tab Array of available counters
 * @param time_tab Array of available time values
 * @param pk_no Index of output in pk_tab
 * @param bit_1_no Index of input bit in bits_tab
 * @param bit_2_no Index of input bit in bits_tab
 * @param counter_no Index of counter in counters_tab
 * @param time_no Index of time value in time_tab
 */
void pk_joj4_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no,
	const uint16_t counter_no,
	const uint16_t time_no
);

/**
 * @brief Realization of PK_JOJ5 function
 * @details Second gear with turn on delay.
 * @param bits_tab Array of available input bits
 * @param counters_tab Array of available counters
 * @param time_tab Array of available time values
 * @param pk_no Index of output in pk_tab
 * @param bit_1_no Index of input bit in bits_tab
 * @param bit_2_no Index of input bit in bits_tab
 * @param bit_3_no Index of input bit in bits_tab
 * @param bit_4_no Index of input bit in bits_tab
 * @param counter_no Index of counter in counters_tab
 * @param time_no Index of time value in time_tab
 */
void pk_joj5_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no,
	const uint16_t bit_3_no,
	const uint16_t bit_4_no,
	const uint16_t counter_no,
	const uint16_t time_no
);

/**
 * @brief Realization of PK_ANGT function
 * @details Set pk_no when analog value is greaten than analog_value_1
 * Clear pk_no when analog value is lower than analog_value_2
 * @param bits_tab Array of available input bits
 * @param analog_tab Array of available analog values
 * @param pk_no Index of output in pk_tab
 * @param analog_no Index of analog value in analog_tab
 * @param analog_value_1 Minimum edge of analog value
 * @param analog_value_2 Maximum edge of analog value
 */
void pk_angt_function(
		uint8_t * const bits_tab,
		uint8_t * const analog_tab,
		const uint16_t pk_no,
		const uint8_t analog_no,
		const uint8_t analog_value_1,
		const uint8_t analog_value_2
);

/**
 * @brief Realization of PK_ANLT function
 * @details Clear pk_no when analog value is greaten than analog_value_1
 * Set pk_no when analog value is lower than analog_value_2
 * @param bits_tab Array of available input bits
 * @param analog_tab Array of available analog values
 * @param pk_no Index of output in pk_tab
 * @param analog_no Index of analog value in analog_tab
 * @param analog_value_1 Minimum edge of analog value
 * @param analog_value_2 Maximum edge of analog value
 */
void pk_anlt_function(
		uint8_t * const bits_tab,
		uint8_t * const analog_tab,
		const uint16_t pk_no,
		const uint8_t analog_no,
		const uint8_t analog_value_1,
		const uint8_t analog_value_2
);

/**
 * @brief Realization of PK_PULSE function
 * @details Set pk_no for time_no time when bit_no change his state from 0 to 1
 * @param bits_tab Array of available input bits
 * @param memory_tab Array of available memory bits
 * @param counters_tab Array of available counters
 * @param time_tab Array of available time values
 * @param pk_no Index of output in pk_tab
 * @param bit_no Index of input bit in bits_tab
 * @param memory_no Index of memory bit in memory_tab
 * @param counter_no Index of counter in counters_tab
 * @param time_no Index of time value in time_tab
 */
void pk_pulse_function(
	uint8_t * const bits_tab,
	uint8_t * const memory_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_no,
	const uint16_t memory_no,
	const uint16_t counter_no,
	const uint16_t time_no
);

/**
 * @brief Realization of PK_OR function
 * @details pk_no = bit_1_no | bit_2_no
 * @param bits_tab Array of available input bits
 * @param pk_no Index of output in pk_tab
 * @param bit_1_no Index of input bit in bits_tab
 * @param bit_2_no Index of input bit in bits_tab
 */
void pk_or_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no
);

/**
 * @brief Realization of PK_AND function
 * @details pk_no = bit_1_no & bit_2_no
 * @param bits_tab Array of available input bits
 * @param pk_no Index of output in pk_tab
 * @param bit_1_no Index of input bit in bits_tab
 * @param bit_2_no Index of input bit in bits_tab
 */
void pk_and_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no
);

/**
 * @brief Realization of PK_NOT function
 * @details pk_no = ~bit_no
 * @param bits_tab Array of available input bits
 * @param pk_no Index of output in pk_tab
 * @param bit_no Index of input bit in bits_tab
 */
void pk_not_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_no
);

/**
 * @brief Realization of PK_DEMUX3 function
 * @details Examples:
 * bit_1_no = 0, bit_2_no = 0, bit_3_no = 0 => pk_no_0,1,2,3,4,5,6,7 = 0
 * bit_1_no = 1, bit_2_no = 0, bit_3_no = 0 => pk_no_0 = 1, pk_no_1,2,3,4,5,6,7 = 0
 * bit_1_no = 1, bit_2_no = 1, bit_3_no = 1 => pk_no_0,1,2,3,4,5,6,7 = 1
 * @param bits_tab Array of available input bits
 * @param pk_no Index of output in pk_tab
 * @param bit_1_no Index of input bit in bits_tab
 * @param bit_2_no Index of input bit in bits_tab
 * @param bit_3_no Index of input bit in bits_tab
 */
void pk_demux3_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no,
	const uint16_t bit_3_no
);

/**
 * @brief Realization of PK_ZERO function
 * @details Clear pk_no bit.
 * @param bits_tab Array of available input bits
 * @param pk_no Index of output in pk_tab
 */
void pk_zero_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no
);

/**
 * @brief Realization of PK_ONE function
 * @details Set pk_no bit.
 * @param pk_tab Array of available bits
 * @param pk_no Index of output in pk_tab
 */
void pk_one_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no
);

/**
 * @brief Realization of PK_JOJE function
 * @details Block set of pk_no for time_no time when bit_1_no = 1 and bit_2_no = 1
 * @param bits_tab Array of available input bits
 * @param memory_tab Array of available memory bits
 * @param counters_tab Array of available counters
 * @param time_tab Array of available time values
 * @param pk_1_no Index of output in pk_tab
 * @param pk_2_no Index of output in pk_tab
 * @param bit_1_no Index of input bit in bits_tab
 * @param bit_2_no Index of input bit in bits_tab
 * @param memory_no Index of memory bit in memory_tab
 * @param counter_no Index of counter in counters_tab
 * @param time_no Index of time value in time_tab
 */
void pk_joje_function(
	uint8_t * const bits_tab,
	uint8_t * const memory_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_1_no,
	const uint16_t pk_2_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no,
	const uint16_t memory_no,
	const uint16_t counter_no,
	const uint16_t time_no
);

/**
 * @brief Realization of PK_ASTABT function
 * @details PK_ASTAB with delay.
 * @param bits_tab Array of available input bits
 * @param counters_tab Array of available counters
 * @param time_tab Array of available time values
 * @param pk_no Index of output in pk_tab
 * @param bit_no Index of input bit in bits_tab
 * @param counter_no Index of counter in counters_tab
 * @param time_no Index of time value in time_tab
 */
void pk_astabt_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_no,
	const uint16_t counter_no,
	const uint16_t time_no
);


