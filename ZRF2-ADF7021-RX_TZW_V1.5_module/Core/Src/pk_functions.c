

#include <stdint.h>
#include "pk_functions.h"

static void tab_clr_bit(uint8_t * const tab, const uint16_t bit) {
	tab[bit >> 3] &= ~(1 << (bit & 7));
}

static void tab_set_bit(uint8_t * const tab, const uint16_t bit) {
	tab[bit >> 3] |= (1 << (bit & 7));
}

static void tab_neg_bit(uint8_t * const tab, const uint16_t bit) {
	tab[bit >> 3] ^= (1 << (bit & 7));
}

uint8_t tab_chk_bit(uint8_t * const tab, const uint16_t bit) {
uint8_t c = 1;
	if(bit == 128+13)
	{
		c = bit;
	}
	return (tab[bit >> 3] & (1 << (bit & 7)));
}

static void counter_set(
	uint16_t * const counters_tab,
	const uint8_t counter_no,
	const uint8_t value
) {
	counters_tab[counter_no] = value;
}

static uint8_t counter_action(
	uint16_t * const counters_tab,
	const uint8_t counter_no
) {
	if (counters_tab[counter_no] == 0) {
		return 0;
	}
	counters_tab[counter_no] = counters_tab[counter_no] - 1;
	return 1;
}

void pk_set_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_no
) {
	if (tab_chk_bit(bits_tab, bit_no) != 0) {
		tab_set_bit(bits_tab, pk_no);
	}
}

void pk_clr_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_no
) {
	if (tab_chk_bit(bits_tab, bit_no) != 0) {
		tab_clr_bit(bits_tab, pk_no);
	}
}

void pk_astab_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_no
) {
	if (tab_chk_bit(bits_tab, bit_no) == 0) {
		tab_clr_bit(bits_tab, pk_no);
	}
	else {
		tab_set_bit(bits_tab, pk_no);
	}
}

void pk_bistab_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_no,
	const uint16_t counter_no,
	const uint16_t time_no
) {
	if (tab_chk_bit(bits_tab, bit_no) == 0) {
		counter_action(counters_tab, counter_no);
	}
	else {
		if (counter_action(counters_tab, counter_no) == 0) {
			tab_neg_bit(bits_tab, pk_no);
		}
		counter_set(counters_tab, counter_no, time_tab[time_no]);
	}

}

void pk_joj1_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no,
	const uint16_t counter_no,
	const uint16_t time_no
) {
	if (tab_chk_bit(bits_tab, bit_2_no) != 0) {
		counter_set(counters_tab, counter_no, time_tab[time_no]);
		tab_clr_bit(bits_tab, pk_no);
		return;
	}
	if (counter_action(counters_tab, counter_no) != 0) {
		tab_clr_bit(bits_tab, pk_no);
		return;
	}
	if (tab_chk_bit(bits_tab, bit_1_no) == 0) {
		tab_clr_bit(bits_tab, pk_no);
		return;
	}
	tab_set_bit(bits_tab, pk_no);
}

void pk_joj2_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no,
	const uint16_t counter_no,
	const uint16_t time_no
) {
	if (tab_chk_bit(bits_tab, bit_2_no) != 0) {
		if (counter_action(counters_tab, counter_no) != 0) {
			tab_clr_bit(bits_tab, pk_no);
			return;
		}
		if (tab_chk_bit(bits_tab, bit_1_no) != 0) {
			tab_set_bit(bits_tab, pk_no);
		}
		else {
			tab_clr_bit(bits_tab, pk_no);
		}
		return;
	}
	tab_clr_bit(bits_tab, pk_no);
	counter_set(counters_tab, counter_no, time_tab[time_no]);
}

void pk_joj3_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_no,
	const uint16_t counter_no,
	const uint16_t time_no
) {
	if (tab_chk_bit(bits_tab, bit_no) != 0) {
		if (counter_action(counters_tab, counter_no) != 0) {
			tab_clr_bit(bits_tab, pk_no);
			return;
		}
		tab_set_bit(bits_tab, pk_no);
		return;
	}
	tab_clr_bit(bits_tab, pk_no);
	counter_set(counters_tab, counter_no, time_tab[time_no]);
}

void pk_joj4_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no,
	const uint16_t counter_no,
	const uint16_t time_no
) {
	if ((tab_chk_bit(bits_tab, bit_1_no) != 0) || (tab_chk_bit(bits_tab, bit_2_no) != 0)) {
		if (counter_action(counters_tab, counter_no) != 0) {
			tab_clr_bit(bits_tab, pk_no);
			return;
		}
		tab_set_bit(bits_tab, pk_no);
		return;
	}
	tab_clr_bit(bits_tab, pk_no);
	counter_set(counters_tab, counter_no, time_tab[time_no]);
}

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
) {
	if (tab_chk_bit(bits_tab, bit_3_no) != 0) {
		if (counter_action(counters_tab, counter_no) != 0) {
			tab_clr_bit(bits_tab, pk_no);
			return;
		}
		if (tab_chk_bit(bits_tab, bit_1_no) != 0) {
			tab_set_bit(bits_tab, pk_no);
		}
		else {
			tab_clr_bit(bits_tab, pk_no);
		}
		return;
	}
	if (tab_chk_bit(bits_tab, bit_4_no) != 0) {
		if (counter_action(counters_tab, counter_no) != 0) {
			tab_clr_bit(bits_tab, pk_no);
			return;
		}
		if (tab_chk_bit(bits_tab, bit_2_no) != 0) {
			tab_set_bit(bits_tab, pk_no);
		}
		else {
			tab_clr_bit(bits_tab, pk_no);
		}
		return;
	}
	tab_clr_bit(bits_tab, pk_no);
	counter_set(counters_tab, counter_no, time_tab[time_no]);
}

void pk_angt_function(
	uint8_t * const bits_tab,
	uint8_t * const analog_tab,
	const uint16_t pk_no,
	const uint8_t analog_no,
	const uint8_t analog_value_1,
	const uint8_t analog_value_2
) {
	if (tab_chk_bit(bits_tab, pk_no) == 0) {
		if (analog_tab[analog_no] > analog_value_2) {
			tab_set_bit(bits_tab, pk_no);
		}
	}
	else {
		if (analog_tab[analog_no] < analog_value_1) {
			tab_clr_bit(bits_tab, pk_no);
		}
	}
}

void pk_anlt_function(
	uint8_t * const bits_tab,
	uint8_t * const analog_tab,
	const uint16_t pk_no,
	const uint8_t analog_no,
	const uint8_t analog_value_1,
	const uint8_t analog_value_2
) {
	if (tab_chk_bit(bits_tab, pk_no) == 0) {
		if (analog_tab[analog_no] < analog_value_2) {
			tab_set_bit(bits_tab, pk_no);
		}
	}
	else {
		if (analog_tab[analog_no] > analog_value_1) {
			tab_clr_bit(bits_tab, pk_no);
		}
	}
}

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
) {
	if (tab_chk_bit(bits_tab, bit_no) == 0) {
		tab_clr_bit(memory_tab, memory_no);
	}
	if (counter_action(counters_tab, counter_no) != 0) {
		tab_set_bit(bits_tab, pk_no);
		return;
	}
	tab_clr_bit(bits_tab, pk_no);
	if (tab_chk_bit(memory_tab, memory_no) != 0) {
		return;
	}
	if (tab_chk_bit(bits_tab, bit_no) != 0) {
		tab_set_bit(bits_tab, pk_no);
		tab_set_bit(memory_tab, memory_no);
		counter_set(counters_tab, counter_no, time_tab[time_no]);
		return;
	}
}

void pk_or_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no
) {
	if ((tab_chk_bit(bits_tab, bit_1_no) != 0) || (tab_chk_bit(bits_tab, bit_2_no) != 0)) {
		tab_set_bit(bits_tab, pk_no);
		return;
	}
	tab_clr_bit(bits_tab, pk_no);
}

void pk_and_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no
) {
	if ((tab_chk_bit(bits_tab, bit_1_no) != 0) && (tab_chk_bit(bits_tab, bit_2_no) != 0)) {
		tab_set_bit(bits_tab, pk_no);
		return;
	}
	tab_clr_bit(bits_tab, pk_no);
}

void pk_not_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_no
) {
	if (tab_chk_bit(bits_tab, bit_no) != 0) {
		tab_clr_bit(bits_tab, pk_no);
		return;
	}
	tab_set_bit(bits_tab, pk_no);
}

void pk_demux3_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no,
	const uint16_t bit_1_no,
	const uint16_t bit_2_no,
	const uint16_t bit_3_no
) {
	uint8_t n = 0;
	uint8_t i = 0;

	if (tab_chk_bit(bits_tab, bit_1_no) != 0) {
		n += 1;
	}
	if (tab_chk_bit(bits_tab, bit_2_no) != 0) {
		n += 2;
	}
	if (tab_chk_bit(bits_tab, bit_3_no) != 0) {
		n += 4;
	}
	for(i = 0; i < 8; i += 1) {
		tab_clr_bit(bits_tab, pk_no + i);
	}
	tab_set_bit(bits_tab, pk_no + n);
}


void pk_zero_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no
) {
	tab_clr_bit(bits_tab, pk_no);
}


void pk_one_function(
	uint8_t * const bits_tab,
	const uint16_t pk_no
) {
	tab_set_bit(bits_tab, pk_no);
}

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
) {
	if (tab_chk_bit(memory_tab, memory_no) != 0) {
		if (counter_action(counters_tab, counter_no) != 0) {
			if ((tab_chk_bit(bits_tab, bit_1_no) != 0) || (tab_chk_bit(bits_tab, bit_2_no) != 0)) {
				counter_set(counters_tab, counter_no, time_tab[time_no]);
			}
		} else {
			tab_clr_bit(memory_tab, memory_no);
		}
		tab_clr_bit(bits_tab, pk_1_no);
		tab_clr_bit(bits_tab, pk_2_no);
		return;
	}
	if ((tab_chk_bit(bits_tab, bit_1_no) != 0) && (tab_chk_bit(bits_tab, bit_2_no) != 0)) {
		tab_set_bit(memory_tab, memory_no);
		counter_set(counters_tab, counter_no, time_tab[time_no]);
		tab_clr_bit(bits_tab, pk_1_no);
		tab_clr_bit(bits_tab, pk_2_no);
	}
}

void pk_astabt_function(
	uint8_t * const bits_tab,
	uint16_t * const counters_tab,
	const uint16_t * const time_tab,
	const uint16_t pk_no,
	const uint16_t bit_no,
	const uint16_t counter_no,
	const uint16_t time_no
) {
	/*if (tab_chk_bit(bits_tab, bit_no) == 0) {
		if (tab_chk_bit(bits_tab))

		if(test_bit(par(2)) != 0) {
			clr_bit(par(2));
			set_cnt(par(3), par(4));
		}
	}
	else {
		if(test_bit(par(2)) == 0) {
			set_bit(par(2));
			set_cnt(par(3), par(4));
		}
	}
	if(td_cnt(par(3)) == 0) {
		if(test_bit(par(2)) == 0) {
			clr_bit(par(0));
		}
		else {
			set_bit(par(0));
		}
	}*/
}
