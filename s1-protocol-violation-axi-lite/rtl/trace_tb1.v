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
  reg [0:0] PI_S_AXI_AWVALID /*verilator public*/;
  reg [0:0] PI_S_AXI_ARESETN /*verilator public*/;
  reg [3:0] PI_S_AXI_WSTRB /*verilator public*/;
  reg [0:0] PI_S_AXI_WVALID /*verilator public*/;
  reg [2:0] PI_S_AXI_ARPROT /*verilator public*/;
  reg [2:0] PI_S_AXI_AWPROT /*verilator public*/;
  reg [0:0] PI_S_AXI_RREADY /*verilator public*/;
  reg [6:0] PI_S_AXI_ARADDR /*verilator public*/;
  reg [0:0] PI_S_AXI_ARVALID /*verilator public*/;
  reg [6:0] PI_S_AXI_AWADDR /*verilator public*/;
  reg [31:0] PI_S_AXI_WDATA /*verilator public*/;
  reg [0:0] PI_S_AXI_BREADY /*verilator public*/;

  // outputs that were missing from original testbench
  wire  [0:0] S_AXI_AWREADY /*verilator public*/;
  wire  [0:0] S_AXI_WREADY /*verilator public*/;
  wire  [0:0] S_AXI_RVALID /*verilator public*/;
  wire  [0:0] S_AXI_ARREADY /*verilator public*/;
  wire  [1:0] S_AXI_BRESP /*verilator public*/;
  wire  [0:0] S_AXI_BVALID /*verilator public*/;
  wire [31:0] S_AXI_RDATA /*verilator public*/;
  wire  [1:0] S_AXI_RRESP /*verilator public*/;


  xlnxdemo UUT (
    .S_AXI_AWVALID(PI_S_AXI_AWVALID),
    .S_AXI_ARESETN(PI_S_AXI_ARESETN),
    .S_AXI_ACLK(clock),
    .S_AXI_WSTRB(PI_S_AXI_WSTRB),
    .S_AXI_WVALID(PI_S_AXI_WVALID),
    .S_AXI_ARPROT(PI_S_AXI_ARPROT),
    .S_AXI_AWPROT(PI_S_AXI_AWPROT),
    .S_AXI_RREADY(PI_S_AXI_RREADY),
    .S_AXI_ARADDR(PI_S_AXI_ARADDR),
    .S_AXI_ARVALID(PI_S_AXI_ARVALID),
    .S_AXI_AWADDR(PI_S_AXI_AWADDR),
    .S_AXI_WDATA(PI_S_AXI_WDATA),
    .S_AXI_BREADY(PI_S_AXI_BREADY),
    .S_AXI_AWREADY(S_AXI_AWREADY),
    .S_AXI_WREADY(S_AXI_WREADY),
    .S_AXI_RVALID(S_AXI_RVALID),
    .S_AXI_ARREADY(S_AXI_ARREADY),
    .S_AXI_BRESP(S_AXI_BRESP),
    .S_AXI_BVALID(S_AXI_BVALID),
    .S_AXI_RDATA(S_AXI_RDATA),
    .S_AXI_RRESP(S_AXI_RRESP)
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
    PI_S_AXI_AWVALID = 1'b0;
    PI_S_AXI_ARESETN = 1'b0;
    PI_S_AXI_WSTRB = 4'b1000;
    PI_S_AXI_WVALID = 1'b0;
    PI_S_AXI_ARPROT = 3'b000;
    PI_S_AXI_AWPROT = 3'b000;
    PI_S_AXI_RREADY = 1'b0;
    PI_S_AXI_ARADDR = 7'b1000000;
    PI_S_AXI_ARVALID = 1'b0;
    PI_S_AXI_AWADDR = 7'b1000000;
    PI_S_AXI_WDATA = 32'b10000000000000000000000000000000;
    PI_S_AXI_BREADY = 1'b0;
  end
  always @(posedge clock) begin
    // state 1
    if (cycle == 0) begin
      PI_S_AXI_AWVALID <= 1'b0;
      PI_S_AXI_ARESETN <= 1'b1;
      PI_S_AXI_WSTRB <= 4'b0000;
      PI_S_AXI_WVALID <= 1'b0;
      PI_S_AXI_ARPROT <= 3'b000;
      PI_S_AXI_AWPROT <= 3'b000;
      PI_S_AXI_RREADY <= 1'b0;
      PI_S_AXI_ARADDR <= 7'b0000000;
      PI_S_AXI_ARVALID <= 1'b0;
      PI_S_AXI_AWADDR <= 7'b0000000;
      PI_S_AXI_WDATA <= 32'b00000000000000000000000000000000;
      PI_S_AXI_BREADY <= 1'b0;
    end

    // state 2
    if (cycle == 1) begin
      PI_S_AXI_AWVALID <= 1'b1;
      PI_S_AXI_ARESETN <= 1'b1;
      PI_S_AXI_WSTRB <= 4'b1000;
      PI_S_AXI_WVALID <= 1'b1;
      PI_S_AXI_ARPROT <= 3'b000;
      PI_S_AXI_AWPROT <= 3'b000;
      PI_S_AXI_RREADY <= 1'b0;
      PI_S_AXI_ARADDR <= 7'b1000100;
      PI_S_AXI_ARVALID <= 1'b1;
      PI_S_AXI_AWADDR <= 7'b1000000;
      PI_S_AXI_WDATA <= 32'b10000000000000000000000000000000;
      PI_S_AXI_BREADY <= 1'b1;
    end

    // state 3
    if (cycle == 2) begin
      PI_S_AXI_AWVALID <= 1'b1;
      PI_S_AXI_ARESETN <= 1'b1;
      PI_S_AXI_WSTRB <= 4'b1000;
      PI_S_AXI_WVALID <= 1'b1;
      PI_S_AXI_ARPROT <= 3'b000;
      PI_S_AXI_AWPROT <= 3'b000;
      PI_S_AXI_RREADY <= 1'b0;
      PI_S_AXI_ARADDR <= 7'b1000100;
      PI_S_AXI_ARVALID <= 1'b1;
      PI_S_AXI_AWADDR <= 7'b1000000;
      PI_S_AXI_WDATA <= 32'b10000000000000000000000000000000;
      PI_S_AXI_BREADY <= 1'b1;
    end

    // state 4
    if (cycle == 3) begin
      PI_S_AXI_AWVALID <= 1'b0;
      PI_S_AXI_ARESETN <= 1'b1;
      PI_S_AXI_WSTRB <= 4'b1000;
      PI_S_AXI_WVALID <= 1'b1;
      PI_S_AXI_ARPROT <= 3'b000;
      PI_S_AXI_AWPROT <= 3'b000;
      PI_S_AXI_RREADY <= 1'b0;
      PI_S_AXI_ARADDR <= 7'b1000100;
      PI_S_AXI_ARVALID <= 1'b1;
      PI_S_AXI_AWADDR <= 7'b1000000;
      PI_S_AXI_WDATA <= 32'b10000000000000000000000000000000;
      PI_S_AXI_BREADY <= 1'b1;
    end

    // state 5
    if (cycle == 4) begin
      PI_S_AXI_AWVALID <= 1'b0;
      PI_S_AXI_ARESETN <= 1'b1;
      PI_S_AXI_WSTRB <= 4'b1000;
      PI_S_AXI_WVALID <= 1'b1;
      PI_S_AXI_ARPROT <= 3'b000;
      PI_S_AXI_AWPROT <= 3'b000;
      PI_S_AXI_RREADY <= 1'b1;
      PI_S_AXI_ARADDR <= 7'b1000100;
      PI_S_AXI_ARVALID <= 1'b1;
      PI_S_AXI_AWADDR <= 7'b1000000;
      PI_S_AXI_WDATA <= 32'b10000000000000000000000000000000;
      PI_S_AXI_BREADY <= 1'b1;
    end

    // state 6
    if (cycle == 5) begin
      PI_S_AXI_AWVALID <= 1'b0;
      PI_S_AXI_ARESETN <= 1'b1;
      PI_S_AXI_WSTRB <= 4'b1000;
      PI_S_AXI_WVALID <= 1'b1;
      PI_S_AXI_ARPROT <= 3'b000;
      PI_S_AXI_AWPROT <= 3'b000;
      PI_S_AXI_RREADY <= 1'b0;
      PI_S_AXI_ARADDR <= 7'b1000000;
      PI_S_AXI_ARVALID <= 1'b0;
      PI_S_AXI_AWADDR <= 7'b0000000;
      PI_S_AXI_WDATA <= 32'b10000000000000000000000000000000;
      PI_S_AXI_BREADY <= 1'b1;
    end

    genclock <= cycle < 8;
    cycle <= cycle + 1;
  end
endmodule
