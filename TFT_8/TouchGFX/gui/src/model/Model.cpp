#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "../../../../Core/LIB/BUS.h"



extern UART_HandleTypeDef huart5;



Model::Model() : modelListener(0)
{

}

void Model::tick()
{


	//HAL_GPIO_WritePin(UA5_EN_GPIO_Port, UA5_EN_Pin, SET);
	//HAL_UART_Transmit(&huart5, datas, sizeof(datas), 10);
	//HAL_GPIO_WritePin(UA5_EN_GPIO_Port, UA5_EN_Pin, RESET);


}
