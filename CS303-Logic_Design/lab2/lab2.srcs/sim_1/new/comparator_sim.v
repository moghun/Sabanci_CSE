`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 14.11.2021 21:05:20
// Design Name: 
// Module Name: comparator_sim
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


module comparator_sim(

    );
    
    integer i; 
    reg [1:0] X, Y;
    wire LT, EQ, GT;
    
    
    comparator UUT(.X(X), .Y(Y), .LT(LT), .EQ(EQ), .GT(GT));
      
    
    initial begin
        for (i = 0; i < 4; i = i + 1)
        begin
            X = i;
            Y = i + 1;
            #10;
        end
        
        for (i = 0; i < 4; i = i + 1)
        begin
            X = i;
            Y = i;
            #10;
        end
        
        for (i = 0; i < 4; i = i + 1)
        begin
            X = i + 1;
            Y = i;
            #10;
        end
        
    end
endmodule
