`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Sabanci University
// Engineer: 
// 
// Create Date: 28.11.2021 20:02:49
// Design Name: 
// Module Name: fullAdder
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



module fullAdder (A, B, Cin, Sum, Carry);
    input A, B, Cin;
    output Sum, Carry;
    assign {Carry,Sum} = A + B + Cin;
endmodule
