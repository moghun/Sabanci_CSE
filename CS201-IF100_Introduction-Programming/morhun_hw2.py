# -*- coding: utf-8 -*-
"""Untitled3.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1yX10zmitIuVjKkxkbLhs__VEiXwyJ9S8
"""

#Muhammed Orhun Gale

to_speed = float(input("Please enter the average take-off velocity (m/s): "))
fl_speed = float(input("Please enter the average flight velocity (m/s): "))
ld_speed = float(input("Please enter the average landing velocity (m/s): "))

to_time = 300000/to_speed
fl_time = 384400000/fl_speed
ld_time = 100000/ld_speed

total_time = to_time + fl_time + ld_time

d = int(total_time/(24*60*60))
h = int((total_time - (d*24*60*60))/(60*60))
m = int((total_time - (d*24*60*60) - (h*60*60))/(60))
s = float(total_time - (d*24*60*60) - (h*60*60) - (m*60))

print("The mission will take", d,"day(s),", h, "hour(s),", m,"minute(s),", format(s,".2f"),"second(s).")