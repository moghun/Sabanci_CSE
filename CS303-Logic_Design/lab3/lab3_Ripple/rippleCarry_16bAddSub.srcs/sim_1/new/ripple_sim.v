`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Sabanci University
// Engineer: Muhammed Orhun Gale
// 
// Create Date: 28.11.2021 21:14:37
// Design Name: 
// Module Name: ripple_sim
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module ripple_sim();

    reg [15:0] A;
    reg [15:0] B;
    reg control;
    reg Cin;
    wire [15:0] Sum;
    wire Carry;
    wire overflow;
    
    ripple_16bAddSub UUT(.A(A), .B(B), .control(control), .Cin(Cin), .Sum(Sum), .Carry(Carry), .overflow(overflow));
    
    
    initial begin
   
    //47 + 15 = 62
    control = 0;
    A = 47;
    B = 15;
    #10;
   
   //(-30577) - (-28671) = -1906
    control = 1;
   	A = -30577;
    B = -28671;
    #10;
    
    //1031 + 4099 = 5130
    control = 0;
    A = 1031;
    B = 4099;
    #10;
    
    //12321 + 30123 = 42444 OVERFLOW
    control = 0;
    A = 12321;
    B = 30123;
    #10;
   
    //1159 - 4131 = -2972
    control = 1;
    A = 1159;
    B = 4131;
    #10;
    
    end
endmodule
