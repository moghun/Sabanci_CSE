# -*- coding: utf-8 -*-
"""morhun_hw6

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1l9L6bs02ZwCq7ctabAsTlU_Z2aeCU94-
"""

#Muhammed Orhun Gale

def student_courses(coursefile):
  student_dictionary = {}
  elements = coursefile.readlines()
  for lines in elements:
    line = lines.strip("\n")
    words = line.split(" ")
    student_name = words[0]
    for idx in range(1,len(words)):
      if student_name in student_dictionary:
        student_dictionary[student_name].append(words[idx])
      else:
        student_dictionary[student_name] = [words[idx]]
  return student_dictionary

def time_finder(tablefile):
  course_dictionary = {}
  for lines in tablefile:
    line1 = lines.strip()
    line = line1.strip("\n")
    words = line.split("\t")
    crn = words[0]
    course_name = words[1]
    date = words[2]
    time = words[3]
    course_dictionary[crn] = [course_name]
    course_dictionary[crn].append(date)
    course_dictionary[crn].append(time)
  return course_dictionary

def time_sorter(exams):
  date_list = []
  full_list = []
  course_list = []
  for lines in exams:
    words = lines.split("\t")
    course = words[0]
    course_list.append(course)
    date = words[1]+"\t"+words[2]
    date_list.append(date)
  date_list.sort()
  for datez in date_list:
    for info in exams:
      if datez in info:
        a = info.split("\t")
        course2 = a[0]
        new_line = course2+"\t"+datez
        full_list.append(new_line)
  return full_list

course_name = input("Please enter filename for the courses list: ")
final_name = input("Please enter filename for the finals list: ")
student_id = input("Please enter a student ID: ")
coursefile = open(str(course_name),"r")
tablefile = open(str(final_name),"r")
students = student_courses(coursefile)
courses = time_finder(tablefile)

check2 = True

while check2:
  if student_id in students:
    check2 = False
    no_final = []
    exams = []
    print("Final exam schedule of student with ID "+str(student_id)+":")
    for ids, cs in students.items():
      if ids == student_id:
        taken_courses = cs
        for ders in taken_courses:
          if ders not in courses:
            no_final.append(ders)
          else:
            a = courses[ders]
            form = str(a[0]) +"\t"+str(a[1])+"\t"+str(a[2])
            exams.append(form)
      hebele = time_sorter(exams)
    for exam in hebele:
      print(exam)    
  else:
    print("There is no student with ID "+str(student_id))
    student_id = input("Please enter a student ID: ")

if len(no_final) != 0:
  beprinted = "Courses without a final exam: "
  for elem in no_final:
    if elem != no_final[len(no_final)-1]:
      beprinted += elem+", "
    else:
      beprinted += elem

if len(no_final) != 0:
  print(beprinted)