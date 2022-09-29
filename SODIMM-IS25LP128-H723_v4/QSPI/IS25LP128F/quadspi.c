
/* USER CODE BEGIN 0 */
#include "main.h"
#include "quadspi.h"
extern OSPI_HandleTypeDef hospi1;

static uint8_t QSPI_WriteEnable(void);
static uint8_t QSPI_AutoPollingMemReady(void);
static uint8_t QSPI_Configuration(void);
static uint8_t QSPI_ResetChip(void);
/* USER CODE END 0 */

/* USER CODE BEGIN 1 */

/* QUADSPI init function */
uint8_t CSP_QUADSPI_Init(void) {
	//prepare QSPI peripheral for ST-Link Utility operations


	if (HAL_OSPI_DeInit(&hospi1) != HAL_OK) {
		return HAL_ERROR;
	}



	OCTOSPI1_Init();

	if (QSPI_ResetChip() != HAL_OK) {
		return HAL_ERROR;
	}

	HAL_Delay(1);

	if (QSPI_AutoPollingMemReady() != HAL_OK) {
		return HAL_ERROR;
	}

	if (QSPI_WriteEnable() != HAL_OK) {

		return HAL_ERROR;
	}

	if (QSPI_Configuration() != HAL_OK) {
		return HAL_ERROR;
	}

	if (QSPI_AutoPollingMemReady() != HAL_OK) {
		return HAL_ERROR;
	}
	return HAL_OK;
}


void OCTOSPI1_Init(void)
{

  /* USER CODE BEGIN OCTOSPI1_Init 0 */

  /* USER CODE END OCTOSPI1_Init 0 */

  OSPIM_CfgTypeDef sOspiManagerCfg = {0};


  /* USER CODE BEGIN OCTOSPI1_Init 1 */

  /* USER CODE END OCTOSPI1_Init 1 */
  /* OCTOSPI1 parameter configuration*/
  hospi1.Instance = OCTOSPI1;
  hospi1.Init.FifoThreshold = 1;
  hospi1.Init.DualQuad = HAL_OSPI_DUALQUAD_DISABLE;
  hospi1.Init.MemoryType = HAL_OSPI_MEMTYPE_APMEMORY;
  hospi1.Init.DeviceSize = 24;
  hospi1.Init.ChipSelectHighTime = 1;
  hospi1.Init.FreeRunningClock = HAL_OSPI_FREERUNCLK_DISABLE;
  hospi1.Init.ClockMode = HAL_OSPI_CLOCK_MODE_0;
  hospi1.Init.WrapSize = HAL_OSPI_WRAP_NOT_SUPPORTED;
  hospi1.Init.ClockPrescaler = 2;
  hospi1.Init.SampleShifting = HAL_OSPI_SAMPLE_SHIFTING_NONE;
  hospi1.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_DISABLE;
  hospi1.Init.ChipSelectBoundary = 0;
  hospi1.Init.DelayBlockBypass = HAL_OSPI_DELAY_BLOCK_BYPASSED;
  hospi1.Init.MaxTran = 0;
  hospi1.Init.Refresh = 0;
  if (HAL_OSPI_Init(&hospi1) != HAL_OK)
  {
    Error_Handler();
  }
  sOspiManagerCfg.ClkPort = 1;
  sOspiManagerCfg.NCSPort = 1;
  sOspiManagerCfg.IOLowPort = HAL_OSPIM_IOPORT_1_LOW;
  if (HAL_OSPIM_Config(&hospi1, &sOspiManagerCfg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
}


uint8_t CSP_QSPI_Erase_Chip(void) {
	OSPI_RegularCmdTypeDef sCommand = {0};


	if (QSPI_WriteEnable() != HAL_OK) {
		return HAL_ERROR;
	}


	/* Erasing Sequence --------------------------------- */
	sCommand.Instruction = CHIP_ERASE_CMD;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;

	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.Address = 0;
	sCommand.DataMode = HAL_OSPI_DATA_NONE;
	sCommand.DummyCycles = 0;




	  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	  {
	  Error_Handler();
	  }

	if (QSPI_AutoPollingMemReady() != HAL_OK) {
				return HAL_ERROR;
			}

	return HAL_OK;
}

uint8_t QSPI_AutoPollingMemReady(void) {

	OSPI_RegularCmdTypeDef sCommand = {0};
	OSPI_AutoPollingTypeDef sConfig;


	/* Configure automatic polling mode to wait for memory ready ------ */
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = READ_FLAG_STATUS_REG_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	  {
	  Error_Handler();
	  }

	sConfig.Match = 0x00;
	sConfig.Mask = 0x01;
	sConfig.MatchMode = HAL_OSPI_MATCH_MODE_AND;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = HAL_OSPI_AUTOMATIC_STOP_ENABLE;



	if (HAL_OSPI_AutoPolling(&hospi1, &sConfig, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return HAL_ERROR;
	}

	return HAL_OK;
}

static uint8_t QSPI_WriteEnable(void) {
	OSPI_RegularCmdTypeDef sCommand = {0};
	OSPI_AutoPollingTypeDef sConfig;

	QSPI_AutoPollingMemReady();

	/* Enable write operations ------------------------------------------ */
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = WRITE_ENABLE_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_NONE;
	sCommand.DummyCycles = 0;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	  {
	  Error_Handler();
	  }

	/* Configure automatic polling mode to wait for write enabling ---- */
	sConfig.Match = 0x02;
	sConfig.Mask = 0x02;
	sConfig.MatchMode = HAL_OSPI_MATCH_MODE_AND;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = HAL_OSPI_AUTOMATIC_STOP_ENABLE;

	sCommand.Instruction = READ_STATUS_REG_CMD;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	if (HAL_OSPI_AutoPolling(&hospi1, &sConfig, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return HAL_ERROR;
	}

	return HAL_OK;
}
/*Enable quad mode and set dummy cycles count*/
uint8_t QSPI_Configuration(void) {

	OSPI_RegularCmdTypeDef sCommand = {0};
	uint8_t test_buffer[4] = { 0 };
	/*read status register*/
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = READ_STATUS_REG_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData = 1;

	  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	  {
	  Error_Handler();
	  }



	if (HAL_OSPI_Receive(&hospi1, test_buffer, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return HAL_ERROR;
	}
	/*read configuration register*/
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = READ_CONFIGURATION_REG_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData = 1;

	  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	  {
	  Error_Handler();
	  }

	if (HAL_OSPI_Receive(&hospi1, &(test_buffer[1]),
			HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return HAL_ERROR;
	}
	/*modify buffer to enable quad mode*/
	test_buffer[0] |= 0x40;

	/*set dummy cycles*/
	test_buffer[1] = 0x40;

	if (QSPI_WriteEnable() != HAL_OK) {
		return HAL_ERROR;
	}

	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.Instruction = WRITE_STATUS_REG_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
	sCommand.NbData = 1;

	  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	  {
	  Error_Handler();
	  }

	if (HAL_OSPI_Transmit(&hospi1, test_buffer,
			HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		Error_Handler();
		return HAL_ERROR;
	}

	if (QSPI_WriteEnable() != HAL_OK) {
		return HAL_ERROR;
	}

	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.Instruction = WRITE_CONFIGURATION_REG_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
	sCommand.NbData = 1;

	  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	  {
	  Error_Handler();
	  }

	if (HAL_OSPI_Transmit(&hospi1, &(test_buffer[1]),
			HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		Error_Handler();
		return HAL_ERROR;
	}
	return HAL_OK;
}

uint8_t CSP_QSPI_EraseSector(uint32_t EraseStartAddress, uint32_t EraseEndAddress) {

	OSPI_RegularCmdTypeDef sCommand = {0};

	EraseStartAddress = EraseStartAddress
			- EraseStartAddress % MEMORY_SECTOR_SIZE;

	/* Erasing Sequence -------------------------------------------------- */
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.Instruction = SECTOR_ERASE_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_1_LINE;

	sCommand.DataMode = HAL_OSPI_DATA_NONE;
	sCommand.DummyCycles = 0;

	while (EraseEndAddress >= EraseStartAddress) {
		sCommand.Address = (EraseStartAddress & 0x0FFFFFFF);

		if (QSPI_WriteEnable() != HAL_OK) {
			return HAL_ERROR;
		}

		  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		  {
		  Error_Handler();
		  }
		EraseStartAddress += MEMORY_SECTOR_SIZE;

		if (QSPI_AutoPollingMemReady() != HAL_OK) {
			return HAL_ERROR;
		}
	}

	return HAL_OK;
}

uint8_t CSP_QSPI_WriteMemory(uint8_t* buffer, uint32_t address,uint32_t buffer_size) {

	OSPI_RegularCmdTypeDef sCommand = {0};
	uint32_t end_addr, current_size, current_addr;

	/* Calculation of the size between the write address and the end of the page */
	current_addr = 0;


	//
	while (current_addr <= address) {
		current_addr += MEMORY_PAGE_SIZE;
	}
	current_size = current_addr - address;

	/* Check if the size of the data is less than the remaining place in the page */
	if (current_size > buffer_size) {
		current_size = buffer_size;
	}

	/* Initialize the adress variables */
	current_addr = address;
	end_addr = address + buffer_size;

	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.Instruction = QUAD_IN_FAST_PROG_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
	sCommand.DataMode = HAL_OSPI_DATA_4_LINES;
	sCommand.NbData = buffer_size;
	sCommand.Address = address;
	sCommand.DummyCycles = 0;

	/* Perform the write page by page */
	do {
		sCommand.Address = current_addr;
		sCommand.NbData = current_size;

		if (current_size == 0) {
			return HAL_OK;
		}

		/* Enable write operations */
		if (QSPI_WriteEnable() != HAL_OK) {
			return HAL_ERROR;
		}

		/* Configure the command */
		  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		  {
		  Error_Handler();
		  }

		/* Transmission of the data */
		if (HAL_OSPI_Transmit(&hospi1, buffer, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {

			return HAL_ERROR;
		}

		/* Configure automatic polling mode to wait for end of program */
		if (QSPI_AutoPollingMemReady() != HAL_OK) {
			return HAL_ERROR;
		}

		/* Update the address and size variables for next page programming */
		current_addr += current_size;
		buffer += current_size;
		current_size =
				((current_addr + MEMORY_PAGE_SIZE) > end_addr) ?
						(end_addr - current_addr) : MEMORY_PAGE_SIZE;
	} while (current_addr <= end_addr);

	return HAL_OK;

}


uint8_t CSP_QSPI_EnableMemoryMappedMode(void) {

	OSPI_RegularCmdTypeDef sCommand = {0};
	  OSPI_MemoryMappedTypeDef sMemMappedCfg = {0};





	/* Enable Memory-Mapped mode-------------------------------------------------- */

	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
	sCommand.DataMode = HAL_OSPI_DATA_4_LINES;
	sCommand.NbData = 0;
	sCommand.Address = 0;
	sCommand.Instruction = QUAD_OUT_FAST_READ_CMD;
	sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_READ_QUAD;

	  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	  {
	  Error_Handler();
	  }

	  sMemMappedCfg.TimeOutActivation = HAL_OSPI_TIMEOUT_COUNTER_DISABLE;


	if (HAL_OSPI_MemoryMapped(&hospi1, &sMemMappedCfg) != HAL_OK) {
		return HAL_ERROR;
	}
	return HAL_OK;
}

/*Send reset in 1,2 and 4 lines*/
uint8_t QSPI_ResetChip() {
	OSPI_RegularCmdTypeDef sCommand = {0};
	uint32_t temp = 0;
	/* Erasing Sequence -------------------------------------------------- */
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.Instruction = RESET_ENABLE_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.Address = 0;
	sCommand.DataMode = HAL_OSPI_DATA_NONE;
	sCommand.DummyCycles = 0;

	  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	  {
	  Error_Handler();
	  }
	for (temp = 0; temp < 0x2f; temp++) {
		__NOP();
	}

	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//	sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.Instruction = RESET_EXECUTE_CMD;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.Address = 0;
	sCommand.DataMode = HAL_OSPI_DATA_NONE;
	sCommand.DummyCycles = 0;

	  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	  {
	  Error_Handler();
	  }

	/* Erasing Sequence -------------------------------------------------- */
		sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_2_LINES;
		sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
		sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//		sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//		sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
		sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
		sCommand.Instruction = RESET_ENABLE_CMD;
		sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
		sCommand.Address = 0;
		sCommand.DataMode = HAL_OSPI_DATA_NONE;
		sCommand.DummyCycles = 0;

		  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		  {
		  Error_Handler();
		  }

		for (temp = 0; temp < 0x2f; temp++) {
			__NOP();
		}

		sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_2_LINES;
		sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
		sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//		sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//		sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
		sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
		sCommand.Instruction = RESET_EXECUTE_CMD;
		sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
		sCommand.Address = 0;
		sCommand.DataMode = HAL_OSPI_DATA_NONE;
		sCommand.DummyCycles = 0;

		  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		  {
		  Error_Handler();
		  }


		/* Erasing Sequence -------------------------------------------------- */
			sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_4_LINES;
			sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
			sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//			sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//			sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
			sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
			sCommand.Instruction = RESET_ENABLE_CMD;
			sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
			sCommand.Address = 0;
			sCommand.DataMode = HAL_OSPI_DATA_NONE;
			sCommand.DummyCycles = 0;

			  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
			  {
			  Error_Handler();
			  }
			for (temp = 0; temp < 0x2f; temp++) {
				__NOP();
			}

			sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_4_LINES;
			sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
			sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
//			sCommand.DdrMode = HAL_OSPI_DDR_MODE_DISABLE;
//			sCommand.DdrHoldHalfCycle = HAL_OSPI_DDR_HHC_ANALOG_DELAY;
			sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
			sCommand.Instruction = RESET_EXECUTE_CMD;
			sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
			sCommand.Address = 0;
			sCommand.DataMode = HAL_OSPI_DATA_NONE;
			sCommand.DummyCycles = 0;

			  if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
			  {
			  Error_Handler();
			  }


	return HAL_OK;
}




/* USER CODE END 1 */

