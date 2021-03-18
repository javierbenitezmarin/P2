#include <math.h>
#include "pav_analysis.h"
#include <stdio.h>

float compute_power(const float *x, unsigned int N)
{
  float aux = 0;
  int n=0;
//  printf("el valor de N es %d ", N);
  for (n = 0; n < N; n++)
  {
    aux = aux + pow((double)x[n],(double)2);
  }
  aux = aux / N;
  aux = 10 * log10((double)aux);
 // printf("El valor de P: %f\n", aux);
  return aux; //tenemos la Potencia en dB
}

float compute_am(const float *x, unsigned int N)
{
  float aux = 0;
  int n = 0;
  for ( n = 0; n < N; n++)
  {
    aux += fabs(x[n]);
  }
  aux = aux / N;
//  printf("El valor de AM %f\n", aux);
  return aux; //tenemos la Amplitud Media
}

float compute_zcr(const float *x, unsigned int N, float fm)
{
  float aux = 0;
  int n=1;
  for (n=1; n<N ; n++){
    if (x[n]*x[n-1]<=0){
     aux = aux + 1;}
  }
 // printf(" El valor de aux de ZCR es %f \n" , aux);
  aux = aux * (fm/2);
 // printf(" El valor de aux de ZCR es %f \n" , aux);
  aux = aux /(N-1)  ;
 // printf("El valor de ZCR %f\n", aux);
  return aux;
}
