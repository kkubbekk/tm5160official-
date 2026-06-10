/*
 * TMC_api.c
 *
 *  Created on: Jun 10, 2026
 *      Author: jakub
 */


#include "TMC_api.h"
#include "TMC5160.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"

#define MOTOR_ID 0

void stepper_init(Stepper_ConfigTypeDef* config) {
    // -------------------------------------------------------------------------
    // 1. RESET STANU I FLAG
    // -------------------------------------------------------------------------
    tmc5160_writeRegister(MOTOR_ID, TMC5160_GSTAT, 0x07);  // Czyszczenie błędów zasilania
    tmc5160_writeRegister(MOTOR_ID, TMC5160_SWMODE, 0x00); // Wyłączenie wbudowanych krańcówek (obsługujemy je ręcznie)

    // -------------------------------------------------------------------------
    // 2. PRĄDY
    // -------------------------------------------------------------------------

    // Bity [0..4] = IHOLD, [8..12] = IRUN, [16..19] = IHOLDDELAY
    uint32_t ihold_irun = 0;
    ihold_irun |= (config->hold_current & 0x1F) << 0;
    ihold_irun |= (config->run_current & 0x1F) << 8;
    ihold_irun |= (6 & 0x0F) << 16;  // Domyślne łagodne opóźnienie przejścia z jazdy w postój

    tmc5160_writeRegister(MOTOR_ID, TMC5160_IHOLD_IRUN, ihold_irun);
    tmc5160_writeRegister(MOTOR_ID, TMC5160_TPOWERDOWN, 0x0A);

    // -------------------------------------------------------------------------
    // 3. MIKROKROKI I CHOPPER (SpreadCycle)
    // -------------------------------------------------------------------------
    // Tłumaczenie normalnej liczby (np. 64) na wartość MRES dla TMC
    uint32_t mres = 0;
    switch (config->microsteps) {
        case 256: mres = 0; break;
        case 128: mres = 1; break;
        case 64:  mres = 2; break;
        case 32:  mres = 3; break;
        case 16:  mres = 4; break;
        case 8:   mres = 5; break;
        case 4:   mres = 6; break;
        case 2:   mres = 7; break;
        case 1:   mres = 8; break;
        default:  mres = 0; break;
    }

    // silny tryb SpreadCycle (GCONF = 0x00 wyłącza  StealthChop)
    tmc5160_writeRegister(MOTOR_ID, TMC5160_GCONF, 0x00);

    // CHOPCONF: zachowujemy Twoje bazowe, dobre parametry (0x000100C3),
    // dodajemy wyliczone mikrokroki (przesunięcie o 24 bity) oraz
    // włączamy interpolację INTPOL (bit 28) - dzięki temu nawet jak ustawisz 16 mikrokroków,
    // układ sprzętowo wygładzi je do 256!
    uint32_t chopconf = 0x000100C3;
    chopconf |= (mres << 24);         // Ustawienie mikrokroków
    chopconf |= (1 << 28);            // Włączenie wbudowanej interpolacji (INTPOL)
    tmc5160_writeRegister(MOTOR_ID, TMC5160_CHOPCONF, chopconf);

    // -------------------------------------------------------------------------
    // 4. COOLSTEP (Inteligentne oszczędzanie energii)
    // -------------------------------------------------------------------------
    if(config->enable_coolstep) {
        // Włącza się dopiero powyżej pewnej prędkości (tu: >30% prędkości max)
        tmc5160_writeRegister(MOTOR_ID, TMC5160_TCOOLTHRS, config->max_velocity / 3);
        // Konfiguracja progów odczytu z wbudowanego StallGuarda
        tmc5160_writeRegister(MOTOR_ID, TMC5160_COOLCONF, 0x00020200);
    } else {
        // TCOOLTHRS = 0 fizycznie całkowicie odcina funkcję CoolStep
        tmc5160_writeRegister(MOTOR_ID, TMC5160_TCOOLTHRS, 0);
        tmc5160_writeRegister(MOTOR_ID, TMC5160_COOLCONF, 0x00000000);
    }

    // -------------------------------------------------------------------------
    // 5. RAMPY I PRĘDKOŚCI
    // -------------------------------------------------------------------------
    tmc5160_writeRegister(MOTOR_ID, TMC5160_VMAX, config->max_velocity);
    tmc5160_writeRegister(MOTOR_ID, TMC5160_AMAX, config->acceleration);
    tmc5160_writeRegister(MOTOR_ID, TMC5160_DMAX, config->decceleration);


    tmc5160_writeRegister(MOTOR_ID, TMC5160_A1, config->acceleration);
    tmc5160_writeRegister(MOTOR_ID, TMC5160_V1, config->max_velocity / 4);
    tmc5160_writeRegister(MOTOR_ID, TMC5160_D1, config->decceleration);
    tmc5160_writeRegister(MOTOR_ID, TMC5160_VSTOP, 10);

    // -------------------------------------------------------------------------
    // 6. STAN POCZĄTKOWY
    // -------------------------------------------------------------------------
    // Po resecie zawsze traktujemy aktualne miejsce jako umowne 0
    // Właściwe "0" ustawi dopiero funkcja bazująca (Homing)
    tmc5160_writeRegister(MOTOR_ID, TMC5160_RAMPMODE, TMC5160_MODE_POSITION);
    tmc5160_writeRegister(MOTOR_ID, TMC5160_XACTUAL, 0);
}
void stepper_SetTargetPosition(uint32_t position_step){
     tmc5160_writeRegister(0, TMC5160_XTARGET, position_step);
}

int32_t Stepper_GetActualPosition(void){
    return tmc5160_readRegister(0,TMC5160_XACTUAL);
}

bool Stepper_isPositionReached(void) {
    uint32_t ramp_stat = tmc5160_readRegister(0,TMC5160_RAMPSTAT);
    return (ramp_stat & TMC5160_RS_POSREACHED) != 0;
}
void Stepper_stop(void){
	tmc5160_writeRegister(0, TMC5160_RAMPMODE, TMC5160_MODE_HOLD);
	tmc5160_writeRegister(0, TMC5160_VMAX, 0);
}

void Stepper_SetCurrents(uint8_t run_current, uint8_t hold_current) {
    uint32_t ihold_irun = 0;
    ihold_irun |= (hold_current & 0x1F) << 0;
    ihold_irun |= (run_current & 0x1F) << 8;
    ihold_irun |= (6 & 0x0F) << 16;
    tmc5160_writeRegister(0, TMC5160_IHOLD_IRUN, ihold_irun);
}

void stepper_Home(void){

}

//TODO: dodac homing z krancowkiami, komendy ruchu,diagnostyke odczytywanie bledow z rejestrow i tak dalej,enkoder ktory sprawdza ile krokow zostalo zgubionych,hm
// przeliczac skok skok sroby jakos z krokami sprytnie trza sie popytac docelowo jak to ma dzialac bo nie ogarniam zbytnio co tutaj zbudowac

