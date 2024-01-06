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

#include "Vtestbench.h"
#include "Vtestbench_testbench.h"

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

void dump_ios(Vtestbench *tb, std::ofstream &o) {
    o << static_cast<uint64_t>(tb->testbench->PI_M_AXIS_ARESETN) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_M_AXIS_TREADY) << ", ";
    o << static_cast<uint64_t>(tb->testbench->M_AXIS_TVALID) << ", ";
    o << static_cast<uint64_t>(tb->testbench->M_AXIS_TDATA) << ", ";
    o << static_cast<uint64_t>(tb->testbench->M_AXIS_TSTRB) << ", ";
    o << static_cast<uint64_t>(tb->testbench->M_AXIS_TLAST);
    o << std::endl;
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Vtestbench *tb = new Vtestbench;

    Verilated::traceEverOn(true);
    VerilatedFstC *trace = new VerilatedFstC;
    tb->trace(trace, 99);
    string waveform = string(argv[0])+".fst";
    trace->open(waveform.c_str());

    string output_txt_name = string(argv[0]) + "_output.txt";
    std::ofstream output_txt;
    output_txt.open(output_txt_name);
    output_txt << "M_AXIS_ARESETN, M_AXIS_TREADY, M_AXIS_TVALID, M_AXIS_TDATA, ";
    output_txt << "M_AXIS_TSTRB, M_AXIS_TLAST" << std::endl;


    if (setjmp(jmp_env) == 0) {
        signal(SIGABRT, &sig_handler);
        signal(SIGINT, &sig_handler);
    } else {
        goto save_trace_and_exit;
    }

    tb->eval();

    while (!Verilated::gotFinish() && (tb->genclock != 0)) {
        dump_ios(tb, output_txt);
        tb->clock = 1;
        tb->eval();
        trace->dump(timestamp);
        sc_time_step();

        tb->clock = 0;
        tb->eval();
        trace->dump(timestamp);
        sc_time_step();
    }
    dump_ios(tb, output_txt);

save_trace_and_exit:

    trace->flush();
    trace->close();
    output_txt.close();

    exit(EXIT_SUCCESS);
}
