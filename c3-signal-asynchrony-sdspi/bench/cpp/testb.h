////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	testb.h
//
// Project:	SD-Card controller, using a shared SPI interface
//
// Purpose:	A wrapper for a common interface to a clocked FPGA core
//		begin exercised in Verilator.
//
// Creator:	Dan Gisselquist, Ph.D.
//		Gisselquist Technology, LLC
//
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016-2020, Gisselquist Technology, LLC
//
// This program is free software (firmware): you can redistribute it and/or
// modify it under the terms of  the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  (It's in the $(ROOT)/doc directory.  Run make with no
// target there if the PDF file isn't present.)  If not, see
// <http://www.gnu.org/licenses/> for a copy.
//
// License:	GPL, v3, as defined and found on www.gnu.org,
//		http://www.gnu.org/licenses/gpl.html
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
#ifndef	TESTB_H
#define	TESTB_H

#include <stdio.h>
#include <stdint.h>
#include <verilated_vcd_c.h>
#include <iostream>
#include <fstream>

#define	TBASSERT(TB,A) do { if (!(A)) { (TB).closetrace(); } assert(A); } while(0);

template <class VA>	class TESTB {
public:
	VA		*m_core;
	VerilatedVcdC*	m_trace;
	uint64_t	m_tickcount;
	std::ofstream trace;

	TESTB(void) : m_trace(NULL), m_tickcount(0l) {
		m_core = new VA;
		Verilated::traceEverOn(true);
		m_core->i_clk = 0;
		eval(); // Get our initial values set properly.
	}
	virtual ~TESTB(void) {
		closetrace();
		delete m_core;
		m_core = NULL;
	}

	virtual	void	opentrace(const char *vcdname) {
		if (!m_trace) {
			m_trace = new VerilatedVcdC;
			m_core->trace(m_trace, 99);
			m_trace->open(vcdname);

			// open output text file
			trace.open("output.txt");
			trace << "i_wb_cyc, i_wb_stb, i_wb_we, i_wb_addr, i_wb_data, o_wb_ack, o_wb_stall, o_wb_data, o_cs_n, o_sck, o_mosi, i_miso, o_int, i_bus_grant, o_debug" << std::endl;
		}
	}

	virtual	void	closetrace(void) {
		if (m_trace) {
			m_trace->close();
			delete m_trace;
			m_trace = NULL;
			trace.close();
		}
	}

	virtual	void	eval(void) {
		m_core->eval();
	}

	virtual	void	tick(void) {
		m_tickcount++;


		// Make sure we have our evaluations straight before the top
		// of the clock.  This is necessary since some of the
		// connection modules may have made changes, for which some
		// logic depends.  This forces that logic to be recalculated
		// before the top of the clock.
		eval();
		if (m_trace) m_trace->dump((vluint64_t)(10*m_tickcount-2));

		// sample expected values _before_ clock edge
		if (m_trace) {
			trace << static_cast<uint64_t>(m_core->i_wb_cyc) << ", ";
			trace << static_cast<uint64_t>(m_core->i_wb_stb) << ", ";
			trace << static_cast<uint64_t>(m_core->i_wb_we) << ", ";
			trace << static_cast<uint64_t>(m_core->i_wb_addr) << ", ";
			trace << static_cast<uint64_t>(m_core->i_wb_data) << ", ";
			trace << static_cast<uint64_t>(m_core->o_wb_ack) << ", ";
			trace << static_cast<uint64_t>(m_core->o_wb_stall) << ", ";
			trace << static_cast<uint64_t>(m_core->o_wb_data) << ", ";
			trace << static_cast<uint64_t>(m_core->o_cs_n) << ", ";
			trace << static_cast<uint64_t>(m_core->o_sck) << ", ";
			trace << static_cast<uint64_t>(m_core->o_mosi) << ", ";
			trace << static_cast<uint64_t>(m_core->i_miso) << ", ";
			trace << static_cast<uint64_t>(m_core->o_int) << ", ";
			trace << static_cast<uint64_t>(m_core->i_bus_grant) << ", ";
			trace << static_cast<uint64_t>(m_core->o_debug) << std::endl;
			trace.flush();
		}


		m_core->i_clk = 1;
		eval();
		if (m_trace) m_trace->dump((vluint64_t)(10*m_tickcount));
		m_core->i_clk = 0;
		eval();
		if (m_trace) {
			m_trace->dump((vluint64_t)(10*m_tickcount+5));
			m_trace->flush();
		}
	}

/*
	virtual	void	reset(void) {
		m_core->i_reset = 1;
		tick();
		m_core->i_reset = 0;
		// printf("RESET\n");
	}
*/

	unsigned long	tickcount(void) {
		return m_tickcount;
	}
};

#endif
