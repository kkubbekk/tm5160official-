#include "main.h"      // Ta linijka naprawia błędy z "SPI_HandleTypeDef" i brakiem HALa
#include "TMC5160.h"

extern SPI_HandleTypeDef hspi1;

TMC5160BusType tmc5160_getBusType(uint16_t icID) {
    return IC_BUS_SPI;
}

void tmc5160_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength) {

    HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive(&hspi1, data, data, dataLength, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_SET);
}


bool tmc5160_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength) {
    return false;
}

uint8_t tmc5160_getNodeAddress(uint16_t icID) {
    return 0;
}

