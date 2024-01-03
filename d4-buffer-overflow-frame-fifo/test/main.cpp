#include <stdlib.h>
#include <iostream>
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
#include <fstream>

#include "Vaxis_fifo_wrapper.h"

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

void dump_ios(Vaxis_fifo_wrapper *tb, std::ofstream &o) {
    o << static_cast<uint64_t>(tb->s_axis_tdata) << ", ";
    o << static_cast<uint64_t>(tb->s_axis_tvalid) << ", ";
    o << static_cast<uint64_t>(tb->s_axis_tready) << ", ";
    o << static_cast<uint64_t>(tb->s_axis_tlast) << ", ";
    o << static_cast<uint64_t>(tb->s_axis_tuser) << ", ";

    o << static_cast<uint64_t>(tb->m_axis_tdata) << ", ";
    o << static_cast<uint64_t>(tb->m_axis_tvalid) << ", ";
    o << static_cast<uint64_t>(tb->m_axis_tready) << ", ";
    o << static_cast<uint64_t>(tb->m_axis_tlast) << ", ";
    o << static_cast<uint64_t>(tb->m_axis_tuser) << ", ";

    o << static_cast<uint64_t>(tb->status_overflow) << ", ";
    o << static_cast<uint64_t>(tb->status_bad_frame) << ", ";
    o << static_cast<uint64_t>(tb->status_good_frame) << std::endl;
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Vaxis_fifo_wrapper *tb = new Vaxis_fifo_wrapper;

    Verilated::traceEverOn(true);
    VerilatedFstC *trace = new VerilatedFstC;
    tb->trace(trace, 99);
    trace->open("axis_fifo.fst");
    std::ofstream output_txt;
    output_txt.open("output.txt");
    output_txt << "s_axis_tdata, s_axis_tvalid, s_axis_tready, s_axis_tlast, s_axis_tuser, ";
    output_txt << "m_axis_tdata, m_axis_tvalid, m_axis_tready, m_axis_tlast, m_axis_tuser, ";
    output_txt << "status_overflow, status_bad_frame, status_good_frame" << std::endl;

    if (setjmp(jmp_env) == 0) {
        signal(SIGABRT, &sig_handler);
        signal(SIGINT, &sig_handler);
    } else {
        goto save_trace_and_exit;
    }

    tb->rst = 1;
    tb->s_axis_tdata = 0;
    tb->s_axis_tvalid = 0;
    tb->s_axis_tlast = 0;
    tb->s_axis_tuser = 0;
    tb->m_axis_tready = 0;
    tb->eval();

    for (int i = 0; i < 10; i++) {
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

    tb->rst = 0;
    tb->eval();
    for (int i = 0; i < 5; i++) {
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

    for (int k = 0; k < 10; k++) {
        for (int i = 0; i < 10; i++) {
            tb->s_axis_tdata = i;
            tb->s_axis_tvalid = 1;
            tb->s_axis_tlast = 0;
            tb->s_axis_tuser = 0;
            tb->eval();

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

        tb->s_axis_tdata = 233;
        tb->s_axis_tvalid = 1;
        tb->s_axis_tlast = 1;
        tb->s_axis_tuser = 0;
        tb->eval();

        dump_ios(tb, output_txt);
        tb->clk = 1;
        tb->eval();
        trace->dump(timestamp);
        sc_time_step();
        tb->clk = 0;
        tb->eval();
        trace->dump(timestamp);
        sc_time_step();

        tb->s_axis_tdata = 0;
        tb->s_axis_tvalid = 0;
        tb->s_axis_tlast = 0;
        tb->s_axis_tuser = 0;
        tb->eval();
        for (int i = 0; i < 5; i++) {
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
    }

save_trace_and_exit:

    trace->flush();
    trace->close();
    output_txt.close();

    exit(EXIT_SUCCESS);
}