#include <stdio.h>
#include "jkDefiniciones.h"
#include "jkFuncionPI.h"
JKES main()
{
  NATURAL x=0;
  NATURAL k;
  x= ~x;
  printf("Cantidad de bits del tipo NATURAL: %i bits.\n", ((JKES) sizeof(NATURAL))<<3);
  printf("Numero máximo: %lu .\n",x);

  jk_iniPrimos();
  jk_contadorPi(3);
  JKE n=2;
  x= 14;
  k=jk_Heta(x,n);
  printf("Intervalo x: %lu  . Primo numero %i: %lu. Cantidad factores: %lu \n", x, (JKES) n, *(jkvr_tp->p+n),k);
 

  x= 1000000;
  jk_contadorXPi(x);
  jk_pruebaPrimo(2017);

  printf("\nEjecucion terminada\n");
  return 0;
}
