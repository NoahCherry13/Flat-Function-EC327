# -*- coding: utf-8 -*-
"""
Created on Thu Nov 25 10:55:19 2021

@author: prane
"""
#Pranet - to get the libraries that support the data scraper
import pandas as pd
import csv


#Function to convert hours from 12 hour format to 24 hours format
def time_convert(t):
    am_or_pm = t.split(" ",1)
    if(am_or_pm[1] == "pm"):
        time = am_or_pm[0].replace(":","")
        time = int(time)
        return (time+1200)
    else:
        time = am_or_pm[0].replace(":","")
        time = int(time)
        return time       
    
    
#Pranet- Testing URL logic for multiple websites

class_code = input("Enter the class you want to take with spaces: ")
semester = input("Please enter the semester: ")

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
#print(URL)

#Pranet - Data scraped 
tables = pd.read_html(URL)
#Pranet - Help us index into particular dataframe elements
professor_name = []
days = []
time = []
start_time = []
end_time = [] 
section = []


for i in range(0, len(tables)):
    section.append(tables[i].loc[0,'Section'])  
fall_index = section.index("A1")
spring_index = section.index("A1",(fall_index+1))

#print(fall_index)
#print(spring_index)


if(semester == "F"):
    for i in range (0,spring_index):
        if(tables[i].loc[0,'Instructor'] not in professor_name):    #Implemented check to ensure only lecture sections are caught.(Still needs some more work)
            professor_name.append((tables[i].loc[0,'Instructor'] ))
            splitter = ((tables[i]).loc[0,'Schedule']).split(" ",1)
            start_end = splitter[1].split("-",1)
            days.append(splitter[0])
            start_time.append(time_convert(start_end[0]))
            end_time.append(time_convert(start_end[1]))
else:
    for i in range (spring_index,len(tables)):
        if(tables[i].loc[0,'Instructor'] not in professor_name):    #Implemented check to ensure only lecture sections are caught.(Still needs some more work)
            professor_name.append((tables[i].loc[0,'Instructor'] ))
            splitter = ((tables[i]).loc[0,'Schedule']).split(" ",1)
            start_end = splitter[1].split("-",1)
            days.append(splitter[0])
            start_time.append(time_convert(start_end[0]))
            end_time.append(time_convert(start_end[1]))
            
               
#for i in range (0,len(tables)):
    #if(tables[i].loc[0,'Instructor'] not in professor_name):    #Implemented check to ensure only lecture sections are caught.(Still needs some more work)
        #professor_name.append((tables[i].loc[0,'Instructor'] ))
        #splitter = ((tables[i]).loc[0,'Schedule']).split(" ",1)
        #start_end = splitter[1].split("-",1)
        #days.append(splitter[0])
        #start_time.append(time_convert(start_end[0]))
        #end_time.append(time_convert(start_end[1]))
        #section.append(tables[i].loc[0,'Section'])
  
#print(section)
#print(start_time)
#print(end_time)



    
    
filename = "test.csv"
with open(filename, 'w') as csvfile:
    csvwriter = csv.writer(csvfile)
    for i in range(0,len(professor_name)):
        row = [course_name,professor_name[i],days[i],start_time[i], end_time[i]]
        csvwriter.writerow(row)
    
