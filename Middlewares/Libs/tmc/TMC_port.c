#include "TMC_port.h"
#include "main.h"
#include "cmsis_os.h"
#include "TMC5160.h"


extern SPI_HandleTypeDef hspi1;
extern osSemaphoreId_t spiDmaSemaphoreHandle;

void TMC_SPI_Transfer(uint8_t *tx_data, uint8_t *rx_data, size_t len) {
    HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_RESET);

    if(HAL_SPI_TransmitReceive_DMA(&hspi1, tx_data, rx_data, len) == HAL_OK) {

        osSemaphoreAcquire(spiDmaSemaphoreHandle, 100);
    }

    HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_SET);
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi->Instance == SPI1) {
        osSemaphoreRelease(spiDmaSemaphoreHandle);
    }
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi) {
    if (hspi->Instance == SPI1) {
        // Tutaj w przyszłości możesz dodać obsługę błędów
    }
}

TMC5160BusType tmc5160_getBusType(uint16_t icID) {
    return IC_BUS_SPI;
}


uint8_t tmc5160_getNodeAddress(uint16_t icID) {
    return 0;
}
