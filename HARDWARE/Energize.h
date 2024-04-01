#ifndef __ENERGIZE_H
#define __ENERGIZE_H

typedef enum {
  ENERGIZE_ENABLE,
  ENERGIZE_DISENABLE
} SETENA;

void Energize_Init(void);
void SetENA(SETENA energize);




#endif

