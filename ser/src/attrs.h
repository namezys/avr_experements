#ifndef SER_ATTRS_H
#define SER_ATTRS_H

#include <avr/io.h>

#define IO(mnemonic, value) __attribute__((io(value + __SFR_OFFSET)))
#define EXTERN_IO(mnemonic, value) __attribute__((io))
#define MEM(mnemonic, value) __attribute__((address(value)))
#define EXTERN_MEM(mnemonic, value)

#ifdef __JETBRAINS__IDE__

    #define __flash

#endif

#endif //SER_ATTRS_H
