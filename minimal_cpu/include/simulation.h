//
// Created by daniel on 26.1.23.
//

#ifndef MYSIM_SIMULATION_H
#define MYSIM_SIMULATION_H
#ifdef SIMULATION
#define SLEEP_SIM() {usleep(100);}
#else
#define SLEEP_SIM() {}
#endif
#endif //MYSIM_SIMULATION_H
