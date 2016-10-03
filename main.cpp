#include "controlador.hpp"


int sc_main(int argc, char* argv[]) {
    
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