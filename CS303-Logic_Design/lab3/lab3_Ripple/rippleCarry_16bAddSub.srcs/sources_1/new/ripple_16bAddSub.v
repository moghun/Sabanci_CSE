`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Sabanci University
// Engineer: Muhammed Orhun Gale
// 
// Create Date: 28.11.2021 18:16:52
// Design Name: 
// Module Name: ripple_16bAddSub
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

module ripple_16bAddSub (A, B, Cin, control, Sum, Carry, overflow);

    input [15:0] A, B;
    input Cin;
    input control;

    output [15:0] Sum;
    output Carry;
    output overflow;

    wire [14:0] C; //There are 14 wires that connects carries of adders
    
    
    //fullAdder is in the fullAdder.v
    fullAdder FA0 (A[0], (B[0]^control), control, Sum[0], C[0]);
    fullAdder FA1 (.A(A[1]), .B((B[1]^control)), .Cin(C[0]), .Sum(Sum[1]),.Carry(C[1]));
    fullAdder FA2 (.A(A[2]), .B((B[2]^control)), .Cin(C[1]), .Sum(Sum[2]),.Carry(C[2]));
    fullAdder FA3 (.A(A[3]), .B((B[3]^control)), .Cin(C[2]), .Sum(Sum[3]),.Carry(C[3]));
    fullAdder FA4 (.A(A[4]), .B((B[4]^control)), .Cin(C[3]), .Sum(Sum[4]),.Carry(C[4]));
    fullAdder FA5 (.A(A[5]), .B((B[5]^control)), .Cin(C[4]), .Sum(Sum[5]),.Carry(C[5]));
    fullAdder FA6 (.A(A[6]), .B((B[6]^control)), .Cin(C[5]), .Sum(Sum[6]),.Carry(C[6]));
    fullAdder FA7 (.A(A[7]), .B((B[7]^control)), .Cin(C[6]), .Sum(Sum[7]),.Carry(C[7]));
    fullAdder FA8 (.A(A[8]), .B((B[8]^control)), .Cin(C[7]), .Sum(Sum[8]),.Carry(C[8]));
    fullAdder FA9 (.A(A[9]), .B((B[9]^control)), .Cin(C[8]), .Sum(Sum[9]),.Carry(C[9]));
    fullAdder FA10 (.A(A[10]), .B((B[10]^control)), .Cin(C[9]), .Sum(Sum[10]),.Carry(C[10]));
    fullAdder FA11 (.A(A[11]), .B((B[11]^control)), .Cin(C[10]), .Sum(Sum[11]),.Carry(C[11]));
    fullAdder FA12 (.A(A[12]), .B((B[12]^control)), .Cin(C[11]), .Sum(Sum[12]),.Carry(C[12]));
    fullAdder FA13 (.A(A[13]), .B((B[13]^control)), .Cin(C[12]), .Sum(Sum[13]),.Carry(C[13]));
    fullAdder FA14 (.A(A[14]), .B((B[14]^control)), .Cin(C[13]), .Sum(Sum[14]),.Carry(C[14]));
    fullAdder FA15 (.Sum(Sum[15]), .B((B[15]^control)), .Cin(C[14]),.Carry(Carry), .A(A[15]));

    assign overflow = (Carry^C[14]); //Detect overflow via comparing last adders' carryIn and carryOut
endmodule
