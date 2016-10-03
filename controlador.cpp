//#include "controlador.hpp"
#include "systemc.h"
#include "controlador.hpp"
/*
SC_MODULE (controlador)  {
  //SC_HAS_PROCESS(controlador);
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
*/
  void controlador::enc_sig_A_counter()
  {
    sig_A_counter = sig_A_counter + 1;
  }
  
  void controlador::speed()
  {
    while(true)
    {
        wait(100);
        cout << "oi";
        revolutions = sig_A_counter/encoder_resolution;// numero de rotacoes em 100/(freq. clock) segundos
        sig_A_counter = 0;
    }
  }
  
  void controlador::pwm()
  {
    if(pwm_counter <= pulse_width && pulse_width != 0)
        pwm_out.write(true);
    else
        pwm_out.write(false);
    pwm_counter = pwm_counter + 1;

  }
  
  void controlador::print_pwm () 
  {
    cout<<"@" << sc_time_stamp() << " :: PWM_OUT "<< pwm_out.read()<<endl;
    cout<<"@" << sc_time_stamp() << " :: PWM_COUNTER "<< pwm_counter<<endl;
    cout<<"@" << sc_time_stamp() << " :: PULSE_WIDTH "<< pulse_width <<endl;
  } 
  
  controlador::controlador(sc_core::sc_module_name)
  {
    pulse_width  = 32;
    p_counter = 0;
    sig_A_counter = 0;
    encoder_resolution = 256;
    
    SC_METHOD(pwm);
    sensitive << clock.pos();
    SC_METHOD(print_pwm);
    sensitive << clock.pos();
    SC_METHOD(enc_sig_A_counter);
    sensitive << enc_sig_A.pos();
    SC_THREAD(speed);
    sensitive << clock.pos();
  } 
/*
  SC_MODULE (controlador_tb){
  sc_in<bool> clock;
 
  sc_signal <bool> enc_sig_A,enc_sig_B, reset  ;
  sc_signal   <bool> pwm_out;
  controlador *c1;

  void do_test();

  SC_CTOR(controlador_tb);
};
*/
  void controlador_tb::do_test() {
    cout << "@" << sc_time_stamp() <<" Starting test"<<endl;
    wait(256);
    cout << "@" << sc_time_stamp() <<" Starting test"<<endl;
    c1->pulse_width = 127;
    wait(257);
    cout << "@" << sc_time_stamp() <<" Terminating simulation"<<endl;
    sc_stop();
  }

  controlador_tb::controlador_tb(sc_core::sc_module_name) {
    c1 = new controlador ("Control");
    c1->clock       (clock);
    c1->reset       (reset);
    c1->enc_sig_A   (enc_sig_A);
    c1->enc_sig_B   (enc_sig_B);
    c1->pwm_out     (pwm_out);
    SC_THREAD (do_test);
      dont_initialize();
      sensitive << clock.pos();
  }


