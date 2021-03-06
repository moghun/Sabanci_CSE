# -*- coding: utf-8 -*-
"""mainProgram.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1D2Zf4L5DOcnKDiRZyGxWWd_kkYIRT-sh
"""

#Muhammed Orhun Gale

def getInput(inp):
  
  if inp == "puzzle":
    ppiece = input("Please enter the puzzle: ")
    p_list = ppiece.split("-")
    return p_list
  elif inp == "words":
    words = input("Please enter the words: ")
    w_list = words.split(",")
    return w_list

def checkInput(obj):
  resp1 = False
  resp2 = True

  lenlist = []
  if len(obj) < 2:
    return resp1
  
  else:
    for elem in obj:
      if elem.isalpha() == False:
        return resp1
      else:
        length = len(elem)
        lenlist.append(length)
        idx = 1
      
        while idx < len(lenlist):
          if lenlist[0] == lenlist[idx]:
            idx += 1
            if idx == len(lenlist):
              return resp2
          else:
            idx = len(lenlist)
            return resp1
          

def row_maker(puzzle,words):
  lrll = puzzle
  rlll = []
  udll = []
  dull = []  
  
  row_length = len(puzzle[0])
  column_length = len(puzzle)
  
  for line1 in puzzle:
    nrll = ""
    for letter1 in range(row_length-1,-1,-1):
      nrll += line1[letter1]
    rlll.append(nrll)
  
  times = row_length-1
  for repeat in range(times):
    nudl = ""
    for line2 in puzzle:
      nudl += line2[times]
    times -= 1
    udll.append(nudl)

  for line3 in udll:
    ndul = ""
    for letter2 in range(column_length-1,-1,-1):
      ndul += line3[letter2]
    dull.append(ndul)
  
  return lrll,rlll,udll,dull 

def word_finder(a,b,c,d):
  apwordlist = []
  for lines1 in a:
    for word1 in words:
      if word1 in lines1:
        apwordlist.append(word1)
  for lines2 in b:
    for word2 in words:
      if word2 in lines2:
        apwordlist.append(word2)
  for lines3 in c:
    for word3 in words:
      if word3 in lines3:
        apwordlist.append(word3)
  for lines4 in d:
    for word4 in words:
      if word4 in lines4:
        apwordlist.append(word4)
  return apwordlist

def printPuzzle(lines):
  for line in lines:
    new_form = line.lower()
    print(new_form)    

def findWords(puzzle,words):
  a,b,c,d =  row_maker(puzzle,words)
  wls = word_finder(a,b,c,d)

  for word in words:
    if word in wls:
      idx = 0
      check1 = True
      while check1:
        if word in a[idx]:
          sp = a[idx].find(word)
          wl = len(word)
          ep = sp+wl-1
          vertical = idx
          tword = word.lower()
          print("Found "+tword+" at ("+ str(vertical)+","+str(sp)+")-("+str(vertical)+","+str(ep)+")")
          check1 = False
          idx=0
        elif word in b[idx]:
          sp = len(b[0])-b[idx].find(word)-1
          wl = len(word)
          ep = sp-wl+1
          vertical = idx
          tword = word.lower()
          print("Found "+tword+" at ("+ str(vertical)+","+str(sp)+")-("+str(vertical)+","+str(ep)+")")
          check1 = False
          idx = 0
        elif word in c[idx]:
          horizontal = idx
          wl = len(word)
          sp = c[idx].find(word)
          ep = wl+sp-1
          tword = word.lower()
          print("Found "+tword+" at ("+ str(sp)+","+str(horizontal)+")-("+str(ep)+","+str(horizontal)+")")
          check1 = False
          idx = 0     
        elif word in d[idx]:
          sp = len(d[0])-d[idx].find(word)-1
          wl = len(word)
          ep = sp-wl+1
          horizontal = idx
          tword = word.lower()
          print("Found "+tword+" at ("+ str(sp)+","+str(horizontal)+")-("+str(ep)+","+str(horizontal)+")")
          check1 = False
          idx = 0

        else:
          if idx < len(a)-1:
            idx += 1
          else:
            print(word+" does not exist.")
            check1 = False
            idx = 0


# DO NOT MODIFY THIS CELL
puzzle = getInput("puzzle")
while not checkInput(puzzle):
  print("Wrong input format.")
  puzzle = getInput("puzzle")

words = getInput("words")
printPuzzle(puzzle)

findWords(puzzle,words)