`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Sabanci University
// Engineer: Muhammed Orhun Gale
// 
// Create Date: 14.11.2021 21:02:17
// Design Name: 
// Module Name: comparator
// Project Name: 2-Bit Comparator
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


module comparator(input [1:0] X, input [1:0] Y, output LT, output EQ, output GT

    );
    
    wire lt1, lt2, lt3, eq1, eq2, gt1, gt2, gt3;
    
    assign lt1 = (~X[1]) & (Y[1]);
    assign lt2 = (~X[0]) & (Y[1]) & (Y[0]);
    assign lt3 = (~X[1]) & (~X[0]) & (Y[0]);
    
    assign LT = lt1 | lt2 | lt3;
    
    ////////////////////////
    xnor u1(eq1, X[1], Y[1]);
    xnor u2(eq2, X[0], Y[0]);
    
    assign EQ = eq1 & eq2;
    
   //////////////////////// 
    assign gt1 = (X[1]) & (~Y[1]);
    assign gt2 = (X[0]) & (~Y[1]) & (~Y[0]);
    assign gt3 = (X[1]) & (X[0]) & (~Y[0]);
   
    assign GT = gt1 | gt2 | gt3;
endmodule
