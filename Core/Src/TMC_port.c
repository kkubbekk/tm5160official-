#include "main.h"      // Ta linijka naprawia błędy z "SPI_HandleTypeDef" i brakiem HALa
#include "TMC5160.h"

extern SPI_HandleTypeDef hspi1;

TMC5160BusType tmc5160_getBusType(uint16_t icID) {
    return IC_BUS_SPI;
}

// void tmc5160_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength) {

//     HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_RESET);

//     HAL_SPI_TransmitReceive(&hspi1, data, data, dataLength, 100);

//     HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_SET);
// }
void tmc5160_readWriteSPI(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength) {
    size_t totalLength = (writeLength > readLength) ? writeLength : readLength;
    
      HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_RESET);
      HAL_TransmitReceive_DMA(&hspi,data,data,totalLength);

      ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

      HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_SET);

    
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    
    if(hspi->Instance == SPI1) {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        
        // Wyślij sygnał pobudki do taska z silnikiem
        vTaskNotifyGiveFromISR(defaultTaskHandle, &xHigherPriorityTaskWoken); 
       
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

bool tmc5160_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength) {
    return false;
}

uint8_t tmc5160_getNodeAddress(uint16_t icID) {
    return 0;
}

