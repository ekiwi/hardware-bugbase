`ifndef VERILATOR
module testbench;
  reg [4095:0] vcdfile;
  reg clock;
`else
module testbench(input clock, output reg genclock);
  initial genclock = 1;
`endif
`ifndef VERILATOR
  reg genclock = 1;
`endif
  reg [31:0] cycle = 0;
  reg [0:0] PI_M_AXIS_ARESETN /*verilator public*/;
  reg [0:0] PI_M_AXIS_TREADY /*verilator public*/;
  // other outputs
  reg  [0:0] M_AXIS_TVALID /*verilator public*/;
  reg [31:0] M_AXIS_TDATA /*verilator public*/;
  reg  [3:0] M_AXIS_TSTRB /*verilator public*/;
  reg  [0:0] M_AXIS_TLAST /*verilator public*/;


  xlnxstream_2018_3 UUT (
    .M_AXIS_ACLK(clock),
    .M_AXIS_ARESETN(PI_M_AXIS_ARESETN),
    .M_AXIS_TREADY(PI_M_AXIS_TREADY),
    .M_AXIS_TVALID(M_AXIS_TVALID),
    .M_AXIS_TDATA(M_AXIS_TDATA),
    .M_AXIS_TSTRB(M_AXIS_TSTRB),
    .M_AXIS_TLAST(M_AXIS_TLAST)
  );
`ifndef VERILATOR
  initial begin
    if ($value$plusargs("vcd=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, testbench);
    end
    #5 clock = 0;
    while (genclock) begin
      #5 clock = 0;
      #5 clock = 1;
    end
  end
`endif
  initial begin
`ifndef VERILATOR
    #1;
`endif
    // state 0
    PI_M_AXIS_ARESETN = 1'b0;
    PI_M_AXIS_TREADY = 1'b0;
  end
  always @(posedge clock) begin
    // state 1
    if (cycle == 0) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 2
    if (cycle == 1) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 3
    if (cycle == 2) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 4
    if (cycle == 3) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 5
    if (cycle == 4) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 6
    if (cycle == 5) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 7
    if (cycle == 6) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 8
    if (cycle == 7) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 9
    if (cycle == 8) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 10
    if (cycle == 9) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 11
    if (cycle == 10) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 12
    if (cycle == 11) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 13
    if (cycle == 12) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 14
    if (cycle == 13) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 15
    if (cycle == 14) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 16
    if (cycle == 15) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 17
    if (cycle == 16) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 18
    if (cycle == 17) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 19
    if (cycle == 18) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 20
    if (cycle == 19) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 21
    if (cycle == 20) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 22
    if (cycle == 21) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 23
    if (cycle == 22) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 24
    if (cycle == 23) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 25
    if (cycle == 24) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 26
    if (cycle == 25) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 27
    if (cycle == 26) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 28
    if (cycle == 27) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 29
    if (cycle == 28) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 30
    if (cycle == 29) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 31
    if (cycle == 30) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 32
    if (cycle == 31) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 33
    if (cycle == 32) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 34
    if (cycle == 33) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 35
    if (cycle == 34) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 36
    if (cycle == 35) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 37
    if (cycle == 36) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 38
    if (cycle == 37) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 39
    if (cycle == 38) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 40
    if (cycle == 39) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b1;
    end

    // state 41
    if (cycle == 40) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 42
    if (cycle == 41) begin
      PI_M_AXIS_ARESETN <= 1'b1;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    // state 43
    if (cycle == 42) begin
      PI_M_AXIS_ARESETN <= 1'b0;
      PI_M_AXIS_TREADY <= 1'b0;
    end

    genclock <= cycle < 43;
    cycle <= cycle + 1;
  end
endmodule
