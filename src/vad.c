#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "pav_analysis.h"
#include "vad.h"

const float FRAME_TIME = 10.0F; /* in ms. */
const int MAX_MAYBEVOICE = 5;
const int MAX_MAYBESILENCE = 8;

/* 
 * As the output state is only ST_VOICE, ST_SILENCE, or ST_UNDEF,
 * only this labels are needed. You need to add all labels, in case
 * you want to print the internal state in string format
 */

const char *state_str[] = {
    "UNDEF", "S", "V", "INIT"};

const char *state2str(VAD_STATE st)
{
  return state_str[st];
}

/* Define a datatype with interesting features */
typedef struct
{
  float zcr;
  float p;
  float am;
} Features;

/* 
 * TODO: Delete and use your own features!
 */
float medPot=0.0;
int contador=0;
float k2=0; float k0 = 0;

Features compute_features(const float *x, int N)
{
  /*
   * Input: x[i] : i=0 .... N-1 
   * Ouput: computed features
   */
  /* 
   * DELETE and include a call to your own functions
   *
   * For the moment, compute random value between 0 and 1 
   */
  Features feat;
  //feat.zcr = feat.p = feat.am = (float) rand()/RAND_MAX;
  feat.zcr = compute_zcr(x, N, 16000);
  feat.p = compute_power(x, N);
  feat.am = compute_am(x, N);

  return feat;
}

/* 
 * TODO: Init the values of vad_data
 */

VAD_DATA *vad_open(float rate, float alfa0)
{
  VAD_DATA *vad_data = malloc(sizeof(VAD_DATA));
  vad_data->state = ST_INIT;
  vad_data->alfa0 = alfa0;
  vad_data->sampling_rate = rate;
  vad_data->frame_length = rate * FRAME_TIME * 1e-3;
  return vad_data;
}

VAD_STATE vad_close(VAD_DATA *vad_data, VAD_STATE last_state)
{
  VAD_STATE state = last_state;

  free(vad_data);
  return state;
}

unsigned int vad_frame_size(VAD_DATA *vad_data)
{
  return vad_data->frame_length;
}

/* 
 * TODO: Implement the Voice Activity Detection 
 * using a Finite State Automata
 */

VAD_STATE vad(VAD_DATA *vad_data, float *x, VAD_STATE last_state)
{

  /* 
   * TODO: You can change this, using your own features,
   * program finite state automaton, define conditions, etc.
   */

  Features f = compute_features(x, vad_data->frame_length);
  vad_data->last_feature = f.p; /* save feature, in case you want to show */

  switch (vad_data->state)
  {
  case ST_INIT:
    medPot = medPot + pow(10,(f.p / 10));
    contador++;
    if (contador == 12)
    {
      k0 = medPot / contador;
      k0 = 10 * log10(k0);
      vad_data->k1 = k0 + 3;
      printf("He tardado %f en calcular k0\n y el valor de k1 es %f\n", contador * FRAME_TIME, vad_data->k1);
      k2 = vad_data->k1 + 7;
      vad_data->state = ST_SILENCE;
      printf("He cambiado de ST_INIT a ST_SILENCE");
      contador = 0;
    }
    break;

  case ST_SILENCE:
    if (f.p > vad_data->k1) {//f.p indica la potencia de la trama
      vad_data->state = ST_UNDEF;
      printf("He cambiado de ST_SILENCE a UNDEF (MAYBE VOICE)\n");
    }
    break;

  case ST_VOICE:
    if (f.p < vad_data->k1) {
      vad_data->state = ST_UNDEF;
      printf("He cambiado de ST_VOICE a UNDEF (MAYBE SILENCE)\n");
    }
    break;

  case ST_UNDEF:
        if (last_state == ST_SILENCE){
          // --------- MAYBE VOICE ------------
          if(f.p > k2) {
            vad_data->state = ST_VOICE;
            printf("He cambiado de UNDEF(MAYBE VOICE) a VOICE \n");
            contador = 0; 
          }
          else if(contador >= MAX_MAYBEVOICE || f.p < vad_data->k1){
            vad_data->state = ST_SILENCE;
            printf("He cambiado de UNDEF(MAYBE VOICE) a SILENCE \n");
            contador = 0;
          }
          else contador++;
        }
        else if(last_state == ST_VOICE){
          // ----------- MAYBE SILENCE -------------
          if(f.p >  k2){
            vad_data->state = ST_VOICE;
            printf("He cambiado de MAYBE SILENCE a VOICE\n");
            contador = 0;
          } else if (f.p < vad_data->k1 + 4 && contador >= MAX_MAYBESILENCE){
            vad_data->state = ST_SILENCE;
            printf("He cambiado de MAYBE SILENCE a SILENCE\n");
            contador = 0;
          }  else contador++;
          }
        

    break;
  }

  if (vad_data->state == ST_SILENCE ||
      vad_data->state == ST_VOICE || vad_data->state == ST_INIT)
    return vad_data->state;
  else
    return ST_UNDEF;
}

void vad_show_state(const VAD_DATA *vad_data, FILE *out)
{
  fprintf(out, "%d\t%f\n", vad_data->state, vad_data->last_feature);
}
