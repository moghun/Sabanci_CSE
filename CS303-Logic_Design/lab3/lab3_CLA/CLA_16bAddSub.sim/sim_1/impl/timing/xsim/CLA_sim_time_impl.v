// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.2 (win64) Build 2258646 Thu Jun 14 20:03:12 MDT 2018
// Date        : Mon Nov 29 04:03:14 2021
// Host        : DESKTOP-S1796RL running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               C:/Users/hp/CLA_16bAddSub/CLA_16bAddSub.sim/sim_1/impl/timing/xsim/CLA_sim_time_impl.v
// Design      : CLA_16bAddSub
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

(* ECO_CHECKSUM = "af7e037c" *) 
(* NotValidForBitStream *)
module CLA_16bAddSub
   (A,
    B,
    control,
    Sum,
    overflow,
    Carry);
  input [15:0]A;
  input [15:0]B;
  input control;
  output [15:0]Sum;
  output overflow;
  output Carry;

  wire [15:0]A;
  wire [15:0]A_IBUF;
  wire [15:0]B;
  wire [11:2]BT;
  wire [15:0]B_IBUF;
  wire [11:3]C;
  wire \CLA0/Carry_1__1 ;
  wire \CLA1/Carry_1__1 ;
  wire \CLA1/Carry_2__2 ;
  wire \CLA1/P_0__0 ;
  wire \CLA2/Carry_0__0 ;
  wire \CLA2/Carry_1__1 ;
  wire \CLA2/Carry_2__2 ;
  wire \CLA2/P_1__0 ;
  wire \CLA3/Carry_0__0 ;
  wire \CLA3/Carry_1__1 ;
  wire Carry;
  wire Carry_OBUF;
  wire [15:0]Sum;
  wire [15:0]Sum_OBUF;
  wire \Sum_OBUF[12]_inst_i_5_n_0 ;
  wire \Sum_OBUF[12]_inst_i_6_n_0 ;
  wire \Sum_OBUF[15]_inst_i_4_n_0 ;
  wire \Sum_OBUF[15]_inst_i_5_n_0 ;
  wire control;
  wire control_IBUF;
  wire overflow;
  wire overflow_OBUF;

initial begin
 $sdf_annotate("CLA_sim_time_impl.sdf",,,,"tool_control");
end
  IBUF \A_IBUF[0]_inst 
       (.I(A[0]),
        .O(A_IBUF[0]));
  IBUF \A_IBUF[10]_inst 
       (.I(A[10]),
        .O(A_IBUF[10]));
  IBUF \A_IBUF[11]_inst 
       (.I(A[11]),
        .O(A_IBUF[11]));
  IBUF \A_IBUF[12]_inst 
       (.I(A[12]),
        .O(A_IBUF[12]));
  IBUF \A_IBUF[13]_inst 
       (.I(A[13]),
        .O(A_IBUF[13]));
  IBUF \A_IBUF[14]_inst 
       (.I(A[14]),
        .O(A_IBUF[14]));
  IBUF \A_IBUF[15]_inst 
       (.I(A[15]),
        .O(A_IBUF[15]));
  IBUF \A_IBUF[1]_inst 
       (.I(A[1]),
        .O(A_IBUF[1]));
  IBUF \A_IBUF[2]_inst 
       (.I(A[2]),
        .O(A_IBUF[2]));
  IBUF \A_IBUF[3]_inst 
       (.I(A[3]),
        .O(A_IBUF[3]));
  IBUF \A_IBUF[4]_inst 
       (.I(A[4]),
        .O(A_IBUF[4]));
  IBUF \A_IBUF[5]_inst 
       (.I(A[5]),
        .O(A_IBUF[5]));
  IBUF \A_IBUF[6]_inst 
       (.I(A[6]),
        .O(A_IBUF[6]));
  IBUF \A_IBUF[7]_inst 
       (.I(A[7]),
        .O(A_IBUF[7]));
  IBUF \A_IBUF[8]_inst 
       (.I(A[8]),
        .O(A_IBUF[8]));
  IBUF \A_IBUF[9]_inst 
       (.I(A[9]),
        .O(A_IBUF[9]));
  IBUF \B_IBUF[0]_inst 
       (.I(B[0]),
        .O(B_IBUF[0]));
  IBUF \B_IBUF[10]_inst 
       (.I(B[10]),
        .O(B_IBUF[10]));
  IBUF \B_IBUF[11]_inst 
       (.I(B[11]),
        .O(B_IBUF[11]));
  IBUF \B_IBUF[12]_inst 
       (.I(B[12]),
        .O(B_IBUF[12]));
  IBUF \B_IBUF[13]_inst 
       (.I(B[13]),
        .O(B_IBUF[13]));
  IBUF \B_IBUF[14]_inst 
       (.I(B[14]),
        .O(B_IBUF[14]));
  IBUF \B_IBUF[15]_inst 
       (.I(B[15]),
        .O(B_IBUF[15]));
  IBUF \B_IBUF[1]_inst 
       (.I(B[1]),
        .O(B_IBUF[1]));
  IBUF \B_IBUF[2]_inst 
       (.I(B[2]),
        .O(B_IBUF[2]));
  IBUF \B_IBUF[3]_inst 
       (.I(B[3]),
        .O(B_IBUF[3]));
  IBUF \B_IBUF[4]_inst 
       (.I(B[4]),
        .O(B_IBUF[4]));
  IBUF \B_IBUF[5]_inst 
       (.I(B[5]),
        .O(B_IBUF[5]));
  IBUF \B_IBUF[6]_inst 
       (.I(B[6]),
        .O(B_IBUF[6]));
  IBUF \B_IBUF[7]_inst 
       (.I(B[7]),
        .O(B_IBUF[7]));
  IBUF \B_IBUF[8]_inst 
       (.I(B[8]),
        .O(B_IBUF[8]));
  IBUF \B_IBUF[9]_inst 
       (.I(B[9]),
        .O(B_IBUF[9]));
  OBUF Carry_OBUF_inst
       (.I(Carry_OBUF),
        .O(Carry));
  LUT6 #(
    .INIT(64'hB2FFFFE800E8B200)) 
    Carry_OBUF_inst_i_1
       (.I0(\CLA3/Carry_1__1 ),
        .I1(B_IBUF[14]),
        .I2(A_IBUF[14]),
        .I3(control_IBUF),
        .I4(B_IBUF[15]),
        .I5(A_IBUF[15]),
        .O(Carry_OBUF));
  OBUF \Sum_OBUF[0]_inst 
       (.I(Sum_OBUF[0]),
        .O(Sum[0]));
  LUT2 #(
    .INIT(4'h6)) 
    \Sum_OBUF[0]_inst_i_1 
       (.I0(A_IBUF[0]),
        .I1(B_IBUF[0]),
        .O(Sum_OBUF[0]));
  OBUF \Sum_OBUF[10]_inst 
       (.I(Sum_OBUF[10]),
        .O(Sum[10]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT4 #(
    .INIT(16'h6996)) 
    \Sum_OBUF[10]_inst_i_1 
       (.I0(A_IBUF[10]),
        .I1(control_IBUF),
        .I2(B_IBUF[10]),
        .I3(\CLA2/Carry_1__1 ),
        .O(Sum_OBUF[10]));
  OBUF \Sum_OBUF[11]_inst 
       (.I(Sum_OBUF[11]),
        .O(Sum[11]));
  LUT6 #(
    .INIT(64'h6966999699699666)) 
    \Sum_OBUF[11]_inst_i_1 
       (.I0(A_IBUF[11]),
        .I1(B_IBUF[11]),
        .I2(A_IBUF[10]),
        .I3(B_IBUF[10]),
        .I4(control_IBUF),
        .I5(\CLA2/Carry_1__1 ),
        .O(Sum_OBUF[11]));
  LUT6 #(
    .INIT(64'hB2FFFFE800E8B200)) 
    \Sum_OBUF[11]_inst_i_2 
       (.I0(C[7]),
        .I1(B_IBUF[8]),
        .I2(A_IBUF[8]),
        .I3(control_IBUF),
        .I4(B_IBUF[9]),
        .I5(A_IBUF[9]),
        .O(\CLA2/Carry_1__1 ));
  OBUF \Sum_OBUF[12]_inst 
       (.I(Sum_OBUF[12]),
        .O(Sum[12]));
  LUT6 #(
    .INIT(64'h6966999699699666)) 
    \Sum_OBUF[12]_inst_i_1 
       (.I0(A_IBUF[12]),
        .I1(B_IBUF[12]),
        .I2(A_IBUF[11]),
        .I3(B_IBUF[11]),
        .I4(control_IBUF),
        .I5(\CLA2/Carry_2__2 ),
        .O(Sum_OBUF[12]));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \Sum_OBUF[12]_inst_i_10 
       (.I0(control_IBUF),
        .I1(B_IBUF[2]),
        .O(BT[2]));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'h96)) 
    \Sum_OBUF[12]_inst_i_11 
       (.I0(B_IBUF[4]),
        .I1(control_IBUF),
        .I2(A_IBUF[4]),
        .O(\CLA1/P_0__0 ));
  LUT6 #(
    .INIT(64'hB2FFFFE800E8B200)) 
    \Sum_OBUF[12]_inst_i_2 
       (.I0(\CLA2/Carry_0__0 ),
        .I1(B_IBUF[9]),
        .I2(A_IBUF[9]),
        .I3(control_IBUF),
        .I4(B_IBUF[10]),
        .I5(A_IBUF[10]),
        .O(\CLA2/Carry_2__2 ));
  LUT6 #(
    .INIT(64'hB2FFFFE800E8B200)) 
    \Sum_OBUF[12]_inst_i_3 
       (.I0(\CLA1/Carry_2__2 ),
        .I1(B_IBUF[7]),
        .I2(A_IBUF[7]),
        .I3(control_IBUF),
        .I4(B_IBUF[8]),
        .I5(A_IBUF[8]),
        .O(\CLA2/Carry_0__0 ));
  LUT6 #(
    .INIT(64'hFFFFFEE0FEE00000)) 
    \Sum_OBUF[12]_inst_i_4 
       (.I0(\Sum_OBUF[12]_inst_i_5_n_0 ),
        .I1(\Sum_OBUF[12]_inst_i_6_n_0 ),
        .I2(BT[5]),
        .I3(A_IBUF[5]),
        .I4(BT[6]),
        .I5(A_IBUF[6]),
        .O(\CLA1/Carry_2__2 ));
  LUT6 #(
    .INIT(64'hEEE8E88800000000)) 
    \Sum_OBUF[12]_inst_i_5 
       (.I0(A_IBUF[3]),
        .I1(BT[3]),
        .I2(A_IBUF[2]),
        .I3(BT[2]),
        .I4(\CLA0/Carry_1__1 ),
        .I5(\CLA1/P_0__0 ),
        .O(\Sum_OBUF[12]_inst_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'h28)) 
    \Sum_OBUF[12]_inst_i_6 
       (.I0(A_IBUF[4]),
        .I1(B_IBUF[4]),
        .I2(control_IBUF),
        .O(\Sum_OBUF[12]_inst_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \Sum_OBUF[12]_inst_i_7 
       (.I0(control_IBUF),
        .I1(B_IBUF[5]),
        .O(BT[5]));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \Sum_OBUF[12]_inst_i_8 
       (.I0(control_IBUF),
        .I1(B_IBUF[6]),
        .O(BT[6]));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \Sum_OBUF[12]_inst_i_9 
       (.I0(control_IBUF),
        .I1(B_IBUF[3]),
        .O(BT[3]));
  OBUF \Sum_OBUF[13]_inst 
       (.I(Sum_OBUF[13]),
        .O(Sum[13]));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT4 #(
    .INIT(16'h6996)) 
    \Sum_OBUF[13]_inst_i_1 
       (.I0(A_IBUF[13]),
        .I1(control_IBUF),
        .I2(B_IBUF[13]),
        .I3(\CLA3/Carry_0__0 ),
        .O(Sum_OBUF[13]));
  OBUF \Sum_OBUF[14]_inst 
       (.I(Sum_OBUF[14]),
        .O(Sum[14]));
  LUT6 #(
    .INIT(64'h6966999699699666)) 
    \Sum_OBUF[14]_inst_i_1 
       (.I0(A_IBUF[14]),
        .I1(B_IBUF[14]),
        .I2(A_IBUF[13]),
        .I3(B_IBUF[13]),
        .I4(control_IBUF),
        .I5(\CLA3/Carry_0__0 ),
        .O(Sum_OBUF[14]));
  LUT6 #(
    .INIT(64'hB2FFFFE800E8B200)) 
    \Sum_OBUF[14]_inst_i_2 
       (.I0(\CLA2/Carry_2__2 ),
        .I1(B_IBUF[11]),
        .I2(A_IBUF[11]),
        .I3(control_IBUF),
        .I4(B_IBUF[12]),
        .I5(A_IBUF[12]),
        .O(\CLA3/Carry_0__0 ));
  OBUF \Sum_OBUF[15]_inst 
       (.I(Sum_OBUF[15]),
        .O(Sum[15]));
  LUT6 #(
    .INIT(64'h6966999699699666)) 
    \Sum_OBUF[15]_inst_i_1 
       (.I0(A_IBUF[15]),
        .I1(B_IBUF[15]),
        .I2(A_IBUF[14]),
        .I3(B_IBUF[14]),
        .I4(control_IBUF),
        .I5(\CLA3/Carry_1__1 ),
        .O(Sum_OBUF[15]));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'h96)) 
    \Sum_OBUF[15]_inst_i_10 
       (.I0(B_IBUF[9]),
        .I1(control_IBUF),
        .I2(A_IBUF[9]),
        .O(\CLA2/P_1__0 ));
  LUT6 #(
    .INIT(64'hB2FFFFE800E8B200)) 
    \Sum_OBUF[15]_inst_i_2 
       (.I0(C[11]),
        .I1(B_IBUF[12]),
        .I2(A_IBUF[12]),
        .I3(control_IBUF),
        .I4(B_IBUF[13]),
        .I5(A_IBUF[13]),
        .O(\CLA3/Carry_1__1 ));
  LUT6 #(
    .INIT(64'hFFFFFEE0FEE00000)) 
    \Sum_OBUF[15]_inst_i_3 
       (.I0(\Sum_OBUF[15]_inst_i_4_n_0 ),
        .I1(\Sum_OBUF[15]_inst_i_5_n_0 ),
        .I2(BT[10]),
        .I3(A_IBUF[10]),
        .I4(BT[11]),
        .I5(A_IBUF[11]),
        .O(C[11]));
  LUT6 #(
    .INIT(64'hEEE8E88800000000)) 
    \Sum_OBUF[15]_inst_i_4 
       (.I0(A_IBUF[8]),
        .I1(BT[8]),
        .I2(A_IBUF[7]),
        .I3(BT[7]),
        .I4(\CLA1/Carry_2__2 ),
        .I5(\CLA2/P_1__0 ),
        .O(\Sum_OBUF[15]_inst_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'h28)) 
    \Sum_OBUF[15]_inst_i_5 
       (.I0(A_IBUF[9]),
        .I1(B_IBUF[9]),
        .I2(control_IBUF),
        .O(\Sum_OBUF[15]_inst_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \Sum_OBUF[15]_inst_i_6 
       (.I0(control_IBUF),
        .I1(B_IBUF[10]),
        .O(BT[10]));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \Sum_OBUF[15]_inst_i_7 
       (.I0(control_IBUF),
        .I1(B_IBUF[11]),
        .O(BT[11]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \Sum_OBUF[15]_inst_i_8 
       (.I0(control_IBUF),
        .I1(B_IBUF[8]),
        .O(BT[8]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \Sum_OBUF[15]_inst_i_9 
       (.I0(control_IBUF),
        .I1(B_IBUF[7]),
        .O(BT[7]));
  OBUF \Sum_OBUF[1]_inst 
       (.I(Sum_OBUF[1]),
        .O(Sum[1]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h69669666)) 
    \Sum_OBUF[1]_inst_i_1 
       (.I0(A_IBUF[1]),
        .I1(B_IBUF[1]),
        .I2(A_IBUF[0]),
        .I3(B_IBUF[0]),
        .I4(control_IBUF),
        .O(Sum_OBUF[1]));
  OBUF \Sum_OBUF[2]_inst 
       (.I(Sum_OBUF[2]),
        .O(Sum[2]));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT4 #(
    .INIT(16'h6996)) 
    \Sum_OBUF[2]_inst_i_1 
       (.I0(A_IBUF[2]),
        .I1(control_IBUF),
        .I2(B_IBUF[2]),
        .I3(\CLA0/Carry_1__1 ),
        .O(Sum_OBUF[2]));
  OBUF \Sum_OBUF[3]_inst 
       (.I(Sum_OBUF[3]),
        .O(Sum[3]));
  LUT6 #(
    .INIT(64'h6966999699699666)) 
    \Sum_OBUF[3]_inst_i_1 
       (.I0(A_IBUF[3]),
        .I1(B_IBUF[3]),
        .I2(A_IBUF[2]),
        .I3(B_IBUF[2]),
        .I4(control_IBUF),
        .I5(\CLA0/Carry_1__1 ),
        .O(Sum_OBUF[3]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'hDFF808D0)) 
    \Sum_OBUF[3]_inst_i_2 
       (.I0(B_IBUF[0]),
        .I1(A_IBUF[0]),
        .I2(control_IBUF),
        .I3(B_IBUF[1]),
        .I4(A_IBUF[1]),
        .O(\CLA0/Carry_1__1 ));
  OBUF \Sum_OBUF[4]_inst 
       (.I(Sum_OBUF[4]),
        .O(Sum[4]));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT4 #(
    .INIT(16'h6996)) 
    \Sum_OBUF[4]_inst_i_1 
       (.I0(A_IBUF[4]),
        .I1(control_IBUF),
        .I2(B_IBUF[4]),
        .I3(C[3]),
        .O(Sum_OBUF[4]));
  OBUF \Sum_OBUF[5]_inst 
       (.I(Sum_OBUF[5]),
        .O(Sum[5]));
  LUT6 #(
    .INIT(64'h6966999699699666)) 
    \Sum_OBUF[5]_inst_i_1 
       (.I0(A_IBUF[5]),
        .I1(B_IBUF[5]),
        .I2(A_IBUF[4]),
        .I3(B_IBUF[4]),
        .I4(control_IBUF),
        .I5(C[3]),
        .O(Sum_OBUF[5]));
  LUT6 #(
    .INIT(64'hB2FFFFE800E8B200)) 
    \Sum_OBUF[5]_inst_i_2 
       (.I0(\CLA0/Carry_1__1 ),
        .I1(B_IBUF[2]),
        .I2(A_IBUF[2]),
        .I3(control_IBUF),
        .I4(B_IBUF[3]),
        .I5(A_IBUF[3]),
        .O(C[3]));
  OBUF \Sum_OBUF[6]_inst 
       (.I(Sum_OBUF[6]),
        .O(Sum[6]));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT4 #(
    .INIT(16'h6996)) 
    \Sum_OBUF[6]_inst_i_1 
       (.I0(A_IBUF[6]),
        .I1(control_IBUF),
        .I2(B_IBUF[6]),
        .I3(\CLA1/Carry_1__1 ),
        .O(Sum_OBUF[6]));
  OBUF \Sum_OBUF[7]_inst 
       (.I(Sum_OBUF[7]),
        .O(Sum[7]));
  LUT6 #(
    .INIT(64'h6966999699699666)) 
    \Sum_OBUF[7]_inst_i_1 
       (.I0(A_IBUF[7]),
        .I1(B_IBUF[7]),
        .I2(A_IBUF[6]),
        .I3(B_IBUF[6]),
        .I4(control_IBUF),
        .I5(\CLA1/Carry_1__1 ),
        .O(Sum_OBUF[7]));
  LUT6 #(
    .INIT(64'hB2FFFFE800E8B200)) 
    \Sum_OBUF[7]_inst_i_2 
       (.I0(C[3]),
        .I1(B_IBUF[4]),
        .I2(A_IBUF[4]),
        .I3(control_IBUF),
        .I4(B_IBUF[5]),
        .I5(A_IBUF[5]),
        .O(\CLA1/Carry_1__1 ));
  OBUF \Sum_OBUF[8]_inst 
       (.I(Sum_OBUF[8]),
        .O(Sum[8]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT4 #(
    .INIT(16'h6996)) 
    \Sum_OBUF[8]_inst_i_1 
       (.I0(A_IBUF[8]),
        .I1(control_IBUF),
        .I2(B_IBUF[8]),
        .I3(C[7]),
        .O(Sum_OBUF[8]));
  OBUF \Sum_OBUF[9]_inst 
       (.I(Sum_OBUF[9]),
        .O(Sum[9]));
  LUT6 #(
    .INIT(64'h6966999699699666)) 
    \Sum_OBUF[9]_inst_i_1 
       (.I0(A_IBUF[9]),
        .I1(B_IBUF[9]),
        .I2(A_IBUF[8]),
        .I3(B_IBUF[8]),
        .I4(control_IBUF),
        .I5(C[7]),
        .O(Sum_OBUF[9]));
  LUT6 #(
    .INIT(64'hB2FFFFE800E8B200)) 
    \Sum_OBUF[9]_inst_i_2 
       (.I0(\CLA1/Carry_1__1 ),
        .I1(B_IBUF[6]),
        .I2(A_IBUF[6]),
        .I3(control_IBUF),
        .I4(B_IBUF[7]),
        .I5(A_IBUF[7]),
        .O(C[7]));
  IBUF control_IBUF_inst
       (.I(control),
        .O(control_IBUF));
  OBUF overflow_OBUF_inst
       (.I(overflow_OBUF),
        .O(overflow));
  LUT6 #(
    .INIT(64'h4244111822421888)) 
    overflow_OBUF_inst_i_1
       (.I0(A_IBUF[15]),
        .I1(B_IBUF[15]),
        .I2(A_IBUF[14]),
        .I3(B_IBUF[14]),
        .I4(control_IBUF),
        .I5(\CLA3/Carry_1__1 ),
        .O(overflow_OBUF));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
