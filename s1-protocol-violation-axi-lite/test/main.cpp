#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cassert>
#include <verilated_vcd_c.h>
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
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_AWVALID) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_ARESETN) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_WSTRB) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_WVALID) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_ARPROT) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_AWPROT) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_RREADY) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_ARADDR) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_ARVALID) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_AWADDR) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_WDATA) << ", ";
    o << static_cast<uint64_t>(tb->testbench->PI_S_AXI_BREADY) << ", ";
    o << static_cast<uint64_t>(tb->testbench->S_AXI_AWREADY) << ", ";
    o << static_cast<uint64_t>(tb->testbench->S_AXI_WREADY) << ", ";
    o << static_cast<uint64_t>(tb->testbench->S_AXI_RVALID) << ", ";
    o << static_cast<uint64_t>(tb->testbench->S_AXI_ARREADY) << ", ";
    o << static_cast<uint64_t>(tb->testbench->S_AXI_BRESP) << ", ";
    o << static_cast<uint64_t>(tb->testbench->S_AXI_BVALID) << ", ";
    o << static_cast<uint64_t>(tb->testbench->S_AXI_RDATA) << ", ";
    o << static_cast<uint64_t>(tb->testbench->S_AXI_RRESP) << ", ";
    
    
    
    
    o << std::endl;
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Vtestbench *tb = new Vtestbench;

    Verilated::traceEverOn(true);
    VerilatedVcdC *trace = new VerilatedVcdC;
    tb->trace(trace, 99);
    string waveform = string(argv[0])+".vcd";
    trace->open(waveform.c_str());

    string output_txt_name = string(argv[0]) + "_output.txt";
    std::ofstream output_txt;
    output_txt.open(output_txt_name);
    output_txt << "S_AXI_AWVALID, S_AXI_ARESETN, S_AXI_WSTRB, S_AXI_WVALID, ";
    output_txt << "S_AXI_ARPROT, S_AXI_AWPROT, S_AXI_RREADY, S_AXI_ARADDR, ";
    output_txt << "S_AXI_ARVALID, S_AXI_AWADDR, S_AXI_WDATA, S_AXI_BREADY, ";
    output_txt << "S_AXI_AWREADY, S_AXI_WREADY, S_AXI_RVALID, S_AXI_ARREADY, ";
    output_txt << "S_AXI_BRESP, S_AXI_BVALID, S_AXI_RDATA, S_AXI_RRESP" << std::endl;


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
