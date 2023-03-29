`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Sabanci University
// Engineer: Muhammed Orhun Gale
// 
// Create Date: 29.11.2021 01:31:57
// Design Name: 
// Module Name: CLA_16bitAddSub
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


module CLA_16bAddSub(A, B, control, Sum, overflow, Carry);

	input [15:0] A;
	input [15:0] B;
	
	wire [15:0] C;
	input control;
	
	output [15:0] Sum;
	output overflow;
	output Carry;
 
	///////////////////////////
	//In order to pass XOR values
	wire [15:0] BT;
 
	assign BT[15] = B[15] ^ control;
	assign BT[14] = B[14] ^ control;
	assign BT[13] = B[13] ^ control;
	assign BT[12] = B[12] ^ control;
	assign BT[11] = B[11] ^ control;
	assign BT[10] = B[10] ^ control;
	assign BT[9] = B[9] ^ control;
	assign BT[8] = B[8] ^ control;
	assign BT[7] = B[7] ^ control;
	assign BT[6] = B[6] ^ control;
	assign BT[5] = B[5] ^ control;
	assign BT[4] = B[4] ^ control;
	assign BT[3] = B[3] ^ control;
	assign BT[2] = B[2] ^ control;
	assign BT[1] = B[1] ^ control;
	assign BT[0] = B[0] ^ control;
 
 //Call CLA function
 
	CLA_4Bit CLA0 (.A(A[3:0]), .B(BT[3:0]), .control(control), .Carry(C[3:0]), .Sum(Sum[3:0]));
	CLA_4Bit CLA1 (.A(A[7:4]), .B(BT[7:4]), .control(C[3]), .Carry(C[7:4]), .Sum(Sum[7:4]));
	CLA_4Bit CLA2 (.A(A[11:8]), .B(BT[11:8]), .control(C[7]), .Carry(C[11:8]), .Sum(Sum[11:8]));
	CLA_4Bit CLA3 (.A(A[15:12]), .B(BT[15:12]), .control(C[11]), .Carry(C[15:12]), .Sum(Sum[15:12]));
 
 //Detect ooverflowerflow overflow via comparing last adders' carryIn and carryOut
	assign Carry = C[15];
	assign overflow = C[14] ^ Carry;
endmodule
