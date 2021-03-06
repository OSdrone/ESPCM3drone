/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

#include "gpio.h"
#include "dma.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2C_HandleTypeDef hi2c2;
DMA_HandleTypeDef hdma_i2c2_rx;
DMA_HandleTypeDef hdma_i2c2_tx;

/* I2C2 init function */
void MX_I2C2_Init(void)
{

  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 400000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  hi2c2.MutexI2C = xSemaphoreCreateMutex();
  hi2c2.Syncro = xSemaphoreCreateMutex();
  xSemaphoreGive(hi2c2.MutexI2C);
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(i2cHandle->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspInit 0 */

  /* USER CODE END I2C2_MspInit 0 */
  
    /**I2C2 GPIO Configuration    
    PB10     ------> I2C2_SCL
    PB11     ------> I2C2_SDA 
    */
    GPIO_InitStruct.Pin = SCL_Pin|SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C2_CLK_ENABLE();

    /* Peripheral DMA init*/
  
    hdma_i2c2_rx.Instance = DMA1_Channel5;
    hdma_i2c2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_i2c2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_i2c2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_i2c2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_i2c2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_i2c2_rx.Init.Mode = DMA_NORMAL;
    hdma_i2c2_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    if (HAL_DMA_Init(&hdma_i2c2_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(i2cHandle,hdmarx,hdma_i2c2_rx);

    hdma_i2c2_tx.Instance = DMA1_Channel4;
    hdma_i2c2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_i2c2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_i2c2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_i2c2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_i2c2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_i2c2_tx.Init.Mode = DMA_NORMAL;
    hdma_i2c2_tx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    if (HAL_DMA_Init(&hdma_i2c2_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(i2cHandle,hdmatx,hdma_i2c2_tx);

    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(I2C2_ER_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
  /* USER CODE BEGIN I2C2_MspInit 1 */

  /* USER CODE END I2C2_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspDeInit 0 */

  /* USER CODE END I2C2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C2_CLK_DISABLE();
  
    /**I2C2 GPIO Configuration    
    PB10     ------> I2C2_SCL
    PB11     ------> I2C2_SDA 
    */
    HAL_GPIO_DeInit(GPIOB, SCL_Pin|SDA_Pin);

    /* Peripheral DMA DeInit*/
    HAL_DMA_DeInit(i2cHandle->hdmarx);
    HAL_DMA_DeInit(i2cHandle->hdmatx);

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(I2C2_ER_IRQn);

  }
  /* USER CODE BEGIN I2C2_MspDeInit 1 */

  /* USER CODE END I2C2_MspDeInit 1 */
} 

HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA_MUTEX(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size){
	HAL_StatusTypeDef HAL_StatusTypeDef_var;

	xSemaphoreTake(hi2c->MutexI2C, portMAX_DELAY);
	HAL_StatusTypeDef_var = HAL_I2C_Master_Transmit_DMA(hi2c, DevAddress, pData, Size);
	//Esperamos a la interrupcion
	xSemaphoreTake(hi2c->Syncro, portMAX_DELAY);
	xSemaphoreGive(hi2c->MutexI2C);

	return HAL_StatusTypeDef_var;
}

HAL_StatusTypeDef  HAL_I2C_Master_Receive_DMA_MUTEX(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size){
	HAL_StatusTypeDef HAL_StatusTypeDef_var;

	xSemaphoreTake(hi2c->MutexI2C, portMAX_DELAY);
	HAL_StatusTypeDef_var = HAL_I2C_Master_Receive_DMA(hi2c, DevAddress, pData, Size);
	//Esperamos a la interrupcion
	xSemaphoreTake(hi2c->Syncro, portMAX_DELAY);
	xSemaphoreGive(hi2c->MutexI2C);

	return HAL_StatusTypeDef_var;
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c){
	static BaseType_t xHigherPriorityTaskWoken = pdTRUE;
	
	xSemaphoreGiveFromISR(hi2c->Syncro, &xHigherPriorityTaskWoken);
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c){
	static BaseType_t xHigherPriorityTaskWoken = pdTRUE;
	xSemaphoreGiveFromISR(hi2c->Syncro, &xHigherPriorityTaskWoken);
}

void MandarDatosI2C(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pDataTX, uint8_t *pDataRX,
		uint16_t SizeTX, uint16_t SizeRX){

	xSemaphoreTake(hi2c->MutexI2C, portMAX_DELAY);
	HAL_I2C_Master_Transmit_DMA(hi2c, DevAddress, pDataTX, SizeTX);
	xSemaphoreTake(hi2c->Syncro, portMAX_DELAY);
	HAL_I2C_Master_Receive_DMA(hi2c, DevAddress, pDataRX, SizeRX);
	xSemaphoreTake(hi2c->Syncro, portMAX_DELAY);
	xSemaphoreGive(hi2c->MutexI2C);

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
