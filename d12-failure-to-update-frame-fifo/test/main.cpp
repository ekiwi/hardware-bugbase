#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cassert>
#include <verilated_fst_c.h>
#include <verilated.h>
#include <queue>
#include <map>
#include <tuple>
#include <exception>
#include <csetjmp>
#include <csignal>

#include "Vtest_axis_fifo.h"
#include "Vtest_axis_fifo_test_axis_fifo.h"

using namespace std;


jmp_buf jmp_env;
void sig_handler(int signum) {
    longjmp(jmp_env, 1);
}

const uint64_t psc = 2500; // 2500 ps per cycle
const uint64_t pst = 1250; // 1250 ps per tick (half cycle)
uint64_t timestamp = 0;
double sc_time_stamp() {
    return timestamp;
}
void sc_time_step() {
    timestamp += pst;
}

void dump_ios(Vtest_axis_fifo *tb, std::ofstream &o) {
    o << static_cast<uint64_t>(tb->test_axis_fifo->rst) << ", ";

    o << static_cast<uint64_t>(tb->test_axis_fifo->s_axis_tdata) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->s_axis_tkeep) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->s_axis_tvalid) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->s_axis_tready) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->s_axis_tlast) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->s_axis_tid) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->s_axis_tdest) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->s_axis_tuser) << ", ";

    o << static_cast<uint64_t>(tb->test_axis_fifo->m_axis_tdata) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->m_axis_tkeep) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->m_axis_tvalid) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->m_axis_tready) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->m_axis_tlast) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->m_axis_tid) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->m_axis_tdest) << ", ";
    o << static_cast<uint64_t>(tb->test_axis_fifo->m_axis_tuser) << std::endl;
    o.flush();
}

int main(int argc, char **argv) {
    

    Verilated::commandArgs(argc, argv);
    Vtest_axis_fifo *tb = new Vtest_axis_fifo;
    
    Verilated::traceEverOn(true);
    VerilatedFstC *trace = new VerilatedFstC;
    tb->trace(trace, 99);
    string waveform = string(argv[0])+".fst";
    trace->open(waveform.c_str());
    std::ofstream output_txt;
    output_txt.open("output.txt");
    output_txt << "rst, ";
    output_txt << "s_axis_tdata, s_axis_tkeep, s_axis_tvalid, s_axis_tready, s_axis_tlast, s_axis_tid, s_axis_tdest, s_axis_tuser, ";
    output_txt << "m_axis_tdata, m_axis_tkeep, m_axis_tvalid, m_axis_tready, m_axis_tlast, m_axis_tid, m_axis_tdest, m_axis_tuser";
    output_txt << std::endl;

    
    
    if (setjmp(jmp_env) == 0) {
        signal(SIGABRT, &sig_handler);
        signal(SIGINT, &sig_handler);
    } else {
        goto save_trace_and_exit;
    }
   
    while (!Verilated::gotFinish()) {
        dump_ios(tb, output_txt);
        tb->clk = 1;
        tb->eval();
        trace->dump(timestamp);
        sc_time_step();

        tb->clk = 0;
        tb->eval();
        trace->dump(timestamp);
        sc_time_step();
    }
    dump_ios(tb, output_txt);
    delete tb;


save_trace_and_exit:

    trace->flush();
    trace->close();
    output_txt.close();

    exit(EXIT_SUCCESS);
    

}
