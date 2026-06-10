/*
 * TMC_port.h
 *
 *  Created on: Jun 9, 2026
 *      Author: jakub
 */
#ifndef INC_TMC_PORT_H_
#define INC_TMC_PORT_H_

#include <stdint.h>
#include <stddef.h>

void TMC_SPI_Transfer(uint8_t *tx_data, uint8_t *rx_data, size_t len);

#endif /* INC_TMC_PORT_H_ */
