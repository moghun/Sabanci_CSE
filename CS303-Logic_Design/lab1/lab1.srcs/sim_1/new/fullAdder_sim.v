`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.10.2021 23:33:36
// Design Name: 
// Module Name: fullAdder_sim
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


module fullAdder_sim(

    );
    
    reg A;
    reg B;
    reg Cin;
    
    wire Sum;
    wire Carry;
    
    full_adder UUT(
    .A(A),
    .B(B),
    .Cin(Cin),
    .Sum(Sum),
    .Carry(Carry)
    );
    
    initial begin
        A = 0; 
        B = 0;
        Cin = 0;
        #10  // 0 0 0
        A = 1;
        #10  // 1 0 0
        B = 1;
        #10  // 1 1 0
        Cin = 1;
        #10  // 1 1 1
        A = 0;
        #10  // 0 1 1
        B = 0;
        #10  // 0 0 1
        A = 1; 
        #10 // 1 0 1
        A = 0;
        Cin = 0;
        B = 1; 
            // 0 1 0
     end
        
endmodule
