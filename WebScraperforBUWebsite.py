# -*- coding: utf-8 -*-
"""
Created on Thu Nov 25 10:55:19 2021

@author: prane
"""
#Pranet - to get the libraries that support the data scraper
import pandas as pd
import csv

#Pranet- Testing URL logic for multiple websites

class_code = input("Enter the class you want to take with spaces: ")

#Pranet - Rishav and Aya require input in this form

course_name = (class_code.replace(" ","")).upper()

code = class_code.split()
if (code[0] == "qst"):
    college_name = "questrom"
elif (code[0] == "sed"):
    college_name = "wheelock"
else:
    college_name = code[0].lower()

college_code = code[0].lower()
class_name = code[1].lower()
class_code = code[2].lower()

P_URL = "https://www.bu.edu/academics/"
CollegeURL = college_name
C_URL = "/courses/"
Course_URL = college_code + "-" + class_name + "-" + class_code + "/"

URL = P_URL + CollegeURL + C_URL + Course_URL
print(URL)

#Pranet - Data scraped 
#URL = "https://www.bu.edu/academics/cas/courses/cas-ma-226/"
tables = pd.read_html(URL)
print("There are : ",len(tables)," tables")
#for i in range (0,len(tables)):
    #print(tables[i])

print(tables[0])
print(tables[0].loc[0,'Instructor'])
#professor_name = (tables[0]).loc[0,'Instructor']
#Pranet - Help us index into particular dataframe elements
professor_name = []
for i in range (0,len(tables)):
    professor_name.append((tables[i].loc[0,'Instructor']))
  
days = []
time = []
start_time = []
end_time = []  
#test_string = "MW 2:30 pm-4:15 pm"
#splitter = test_string.split(" ",1)
#print(splitter)
#day = splitter[0]
#print(day)
#time[0] = splitter[1]
#print(day[0]," and ", time[0])
for i in range(0,len(tables)):
    splitter = ((tables[i]).loc[0,'Schedule']).split(" ",1)
    start_end = splitter[1].split("-",1)
    days.append(splitter[0])
    time.append(splitter[1])
    start_time.append(start_end[0])
    end_time.append(start_end[1])
    
print(days)
print(time)
print(start_time)
print(end_time)
filename = "test.csv"
with open(filename, 'w') as csvfile:
    csvwriter = csv.writer(csvfile)
    for i in range(0,len(tables)):
        row = [professor_name[i],days[i],time[i]]
        csvwriter.writerow(row)
    
    
