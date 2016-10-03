#include "systemc.h"
#include "controlador.hpp"

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
  
  controlador::SC_CTOR(controlador) 
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


  void controlador_tb::do_test() {
    cout << "@" << sc_time_stamp() <<" Starting test"<<endl;
    wait(256);
    cout << "@" << sc_time_stamp() <<" Starting test"<<endl;
    c1->pulse_width = 127;
    wait(257);
    cout << "@" << sc_time_stamp() <<" Terminating simulation"<<endl;
    sc_stop();
  }

  controlador_tb::SC_CTOR(controlador_tb) {
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


// sc_main in top level function like in C++ main
/*int sc_main(int argc, char* argv[]) {
    
    sc_clock clock ("my_clock",1,0.5);
    controlador_tb c1("c1");
    c1.clock(clock);
    
    sc_trace_file *wf = sc_create_vcd_trace_file("controlador");
    sc_trace(wf, c1.clock, "clock");
    sc_trace(wf, c1.reset, "reset");
    sc_trace(wf, c1.enc_sig_A, "enc_sig_A");
    sc_trace(wf, c1.enc_sig_B, "enc_sig_B");
    sc_trace(wf, c1.pwm_out, "pwm_out");
    
    sc_start();
    sc_close_vcd_trace_file(wf);
    
  return(0);
}
*/
