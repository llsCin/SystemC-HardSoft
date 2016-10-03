#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "systemc.h"

SC_MODULE (controlador)  {
  sc_in_clk     clock ;      // Clock
  sc_in<bool>   reset ;      // Reset, ativo em Alto
  sc_in<bool>   enc_sig_A ;  // Sinal A do encoder
  sc_in<bool>   enc_sig_B ;  // Sinal B do encoder
  sc_out<bool>  pwm_out;     // PWM para controlar potencia do motor
  
  sc_uint<8>  pwm_counter;
  sc_uint<8>  pulse_width;  //A largura do pulso varia entre 0 a 255. 0 significa motor desligado e 255 significa motor em maxima potencia
  sc_uint<16> p_counter;
  sc_uint<16> sig_A_counter;
  unsigned revolutions;
  sc_uint<16> encoder_resolution;
  sc_bit direction;
  
  void enc_sig_A_counter();
  
  void speed();
  
  void pwm();
  
  void print_pwm ();
  
  SC_CTOR(controlador);

}; 


SC_MODULE (controlador_tb){
  sc_in<bool> clock;
  sc_signal <bool> enc_sig_A,enc_sig_B, reset  ;
  sc_signal   <bool> pwm_out;
  controlador *c1;

  void do_test();

  SC_CTOR(controlador_tb);
};

#endif