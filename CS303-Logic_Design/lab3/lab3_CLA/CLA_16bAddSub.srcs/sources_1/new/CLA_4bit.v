`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Sabanci University
// Engineer: Muhammed Orhun Gale
// 
// Create Date: 29.11.2021 01:32:21
// Design Name: 
// Module Name: CLA_4bit
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


module CLA_4Bit(A, B, control, Carry , Sum);
	
    input [3:0] A, B;
    input control;
    output [3:0] Carry;
    output [3:0] Sum;

    wire [3:0] P, G;

/////////////////////
    assign P[0] = A[0] ^ B[0];
    assign P[1] = A[1] ^ B[1];
    assign P[2] = A[2] ^ B[2];
    assign P[3] = A[3] ^ B[3];
   
    assign G[0] = A[0] & B[0];    
    assign G[1] = A[1] & B[1];    
    assign G[2] = A[2] & B[2];
    assign G[3] = A[3] & B[3];
    
/////////////////////////
    assign Carry[0] = (control & P[0]) | G[0];
    assign Carry[1] = (control & P[0] & P[1]) | (G[0] & P[1]) | G[1];
    assign Carry[2] = (control & P[0] & P[1] & P[2]) | (G[0] & P[1] & P[2]) | (G[1] & P[2]) | G[2];
    assign Carry[3] = (control & P[0] & P[1] & P[2] & P[3]) | (G[0] & P[1] & P[2] & P[3]) | (G[1] & P[2] & P[3]) | (G[2] & P[3]) | G[3];

///////////////////////////
    assign Sum[0] = control ^ P[0];
    assign Sum[1] = Carry[0] ^ P[1];
    assign Sum[2] = Carry[1] ^ P[2];
    assign Sum[3] = Carry[2] ^ P[3];
    
endmodule
