#ifndef TMC_API_H_
#define TMC_API_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t  run_current;    // Prąd podczas jazdy [0-31]
    uint8_t  hold_current;   // Prąd podczas postoju [0-31]
    uint32_t max_velocity;   // Prędkość maksymalna
    uint32_t acceleration;   // Przyspieszenie
    uint32_t decceleration;  // Hamowanie
    bool     enable_coolstep; //colstep
    uint16_t microsteps;
} Stepper_ConfigTypeDef;

void stepper_init(Stepper_ConfigTypeDef* config);
void stepper_SetTargetPosition(uint32_t position_step);
int32_t Stepper_GetActualPosition(void);
bool Stepper_isPositionReached(void);
void stepper_Stop(void);
void Stepper_SetCurrents(uint8_t run_current, uint8_t hold_current);

#endif /* TMC_API_H_ */
