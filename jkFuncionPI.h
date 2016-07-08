/*
 *Define la funcion para contar primos entre un grupo de partida inicial
 *y el cuadrado del máximo primo conocido.
 *Ademas se definen tipos propios para usar en operaciones diofánticas de suma, resta, division, multiplicacion.
 *Esto con el fin de que si se expande el rango de los tipos de entrada con tipos personales, la funcion final no cambie
 *si no la forma en que se manejan las operaciones básicas con estos nuevos tipos
 */
#ifndef __JK_FUNCION_PI__
#define __JK_FUNCION_PI__

#include <malloc.h>
typedef unsigned long NATURAL; //Tipo que encapsula un numero natural
typedef struct {
  JKE n;//Numero de primos consecutivos almacenados
  NATURAL *p;//Puntero a los primos respectivos
} JKS_PRIMOS_K;

#define BY_NATURAL sizeof(NATURAL)//Bytes que contiene el tipo natural.

JKB jkvr_desborde=0;//Indica si hay desborde
JKS_PRIMOS_K *jkvr_tp;//Tabla de primos
NATURAL jk_mxNatural(){
  NATURAL x=0;
  x= ~x;
  return x;
}
JKB jk_mayorQ(const NATURAL *a, const NATURAL *b){
  JKB v;
  v= *a > *b ? 1:0;
  return v;
} 

JKB  jk_igualQ(const NATURAL *a, const NATURAL *b){
  JKB v;
  v= *a == *b ? 1:0;
  return v;
}

NATURAL jk_suma(NATURAL *a, NATURAL *b){
  NATURAL r;
  r= *a + *b;
  //Premisa: *una suma de dos números naturales nunca puede dar de resultado un numero menor a cualquiera de sus dos operandos
  jkvr_desborde = jk_mayorQ(a,&r) | jk_mayorQ(b,&r);
  return r;
}

NATURAL jk_resta(const NATURAL *a, const NATURAL *b){
  NATURAL r;
  r= *a - *b;
  //Premisa: *una resta de dos números naturales nunca puede dar de resultado un numero mayor al minuendo
  jkvr_desborde = jk_mayorQ(&r,a);//Indica que ocurre un desborde por resta
  return r;
}

NATURAL jk_producto(const NATURAL *a, const NATURAL *b){
  NATURAL r;
  r= (*a)*(*b);
  jkvr_desborde = jk_mayorQ(a,&r) | jk_mayorQ(b,&r);
  return r;
}

NATURAL jk_division(const NATURAL *a, const NATURAL *b){
  NATURAL r;
  r= (*a)/(*b);
  return r;
}

NATURAL jk_rCarry(const NATURAL *a, const JKEC b){
  NATURAL r;
  r=BY_NATURAL >= b ? *a >> b: 0;
  return r;
}
NATURAL jk_lCarry(const NATURAL *a, const JKEC b){
  NATURAL r;
  r=BY_NATURAL >= b ? *a << b: 0;
  return r;
}

JKS_PRIMOS_K *jkfc_primos(const JKE n){
  JKS_PRIMOS_K *r;
 
  r= malloc(sizeof(JKS_PRIMOS_K ));//**asume que no hay desborde en la multiplicacion.
  r->p= malloc(n*sizeof(NATURAL));
  r->n=n;
  return r;
}

void jk_iniPrimos(){
  NATURAL primos[]= {1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,
		     103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,
		     199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,
		     331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,
		     457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,
		     607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,
		     751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,
		     911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1013 };
  JKE n=sizeof(primos)/sizeof(NATURAL);
  JKES i;
  printf("La tabla de primos contiene %i primos.\n",(JKES) n-1);
  
  jkvr_tp= jkfc_primos(n);
  for(i=0;i<n;i++){
    *(jkvr_tp->p+i)=primos[i];
  }
  jkvr_tp->n= n;
  printf("El rango máximo que permite trabajar es: %lu .\n", jk_producto(jkvr_tp->p+(n-1),jkvr_tp->p+(n-1)));
}
//Funcion que calcula la cantida de primos nuevos sobre el intervalo x dado un primo indicado por su indice i en
//la serie de primos 
NATURAL  jk_Heta(const NATURAL x, JKE ip){
  NATURAL fpNuevos;//factores primos nuevos
  NATURAL redundantes=0;//factores primos que se obtienen con los primos anteriores
  JKES i;
  if(jkvr_tp->n < ip){
    printf("Operación imposible, se requiere un numero primo que se desconoce\n");
    return 0;
  }
  fpNuevos= jk_division(&x,jkvr_tp->p + ip);
  if(ip==1){
    return fpNuevos;
  } else if(jk_producto(jkvr_tp->p+ip,jkvr_tp->p+ip) > x){
    return 1;
  }else{
    for(i=1;i<ip;i++){
      redundantes+= jk_Heta(fpNuevos,i);
    }
    fpNuevos-= redundantes;//***
  }
  return fpNuevos;
}
//Se pasa el argumento n como el indice del maximo primo que se desea evaluar
JKB jk_contadorPi(JKE n){
  JKES i;
  n= jkvr_tp->n > n? n: jkvr_tp->n;
  NATURAL x= jk_producto((jkvr_tp->p + n),(jkvr_tp->p + n));//intervalo a evaluar
  NATURAL nP=0;//Numero de primos;
  if(jkvr_desborde){
    printf("Imposible obtener un valor dado que el rango supera el maximo valor representable por un Natural computacional\n");
    return 1;
  }
  nP=0;
  for(i=1;i<= n;i++){
    nP+=jk_Heta(x,i);
  }
  nP= x+n-nP-1;
  
  printf("La cantidad de primos sobre los primeros %lu naturales es de %lu .\n",x,nP);
  return 0;
}
//Obtiene el indice del numero primo mas cercano por abajo a la raiz cuadrada de x
JKE jk_raizPrima(NATURAL x){
  
  JKE i;
  for(i=1;i< jkvr_tp->n;i++){
    if(jk_producto((jkvr_tp->p + i),(jkvr_tp->p+i)) > x)
      return (i-1);
  }
  printf("No se hallo la raíz prima, porque el rango excede los primos conocidos.\n");
  return 0;
}
//Cuenta los numeros primoesdado un intervalo x
NATURAL jk_contadorXPi(NATURAL x){
  JKES i;
  JKE n= jk_raizPrima(x);
  
  if(n==0)
    return 0;
  
  NATURAL nP=0;//Numero de primos;

  nP=0;
  for(i=1;i<= n;i++){
    nP+=jk_Heta(x,i);
  }
  nP= x+n-nP-1;
  
  printf("La cantidad de primos sobre los primeros %lu naturales es de %lu .\n",x,nP);
  return nP;
}

JKB jk_pruebaPrimo(NATURAL pp){
  if(pp<2){
    printf("El valor %lu no es primo.\n", pp);
    return 0;
  }
  NATURAL a= jk_contadorXPi(pp);
  NATURAL b= jk_contadorXPi(pp-1);
  if(a > b){
    printf("El valor %lu es primo.\n",pp);
    return 1;
  }
 printf("El valor %lu no es primo.\n", pp);
 return 0;
}
#endif 
