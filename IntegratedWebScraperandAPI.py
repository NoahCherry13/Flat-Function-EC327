# -*- coding: utf-8 -*-
"""
Created on Tue Nov 30 12:48:08 2021

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


call_count = 0

while True:
    class_code = input("Enter the class you want to take with spaces (if you want to exit enter q): ")
    if(class_code == "q"):
        break
    semester = input("Please enter the semester (F or S): ")
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
    #Pranet - Data scraped 
    tables = pd.read_html(URL)
    #Pranet - Help us index into particular dataframe elements
    professor_name = []
    days = []
    time = []
    start_time = []
    end_time = [] 
    section = []
    location = []
    
    
    for i in range(0, len(tables)):
        section.append(tables[i].loc[0,'Section'])  
    fall_index = section.index("A1")
    spring_index = section.index("A1",(fall_index+1))
    
    if(semester == "F" or semester == "f"):
        for i in range (0,spring_index):
            if(tables[i].loc[0,'Instructor'] not in professor_name):    #Implemented check to ensure only lecture sections are caught.(Still needs some more work)
                professor_name.append((tables[i].loc[0,'Instructor'] ))
                splitter = ((tables[i]).loc[0,'Schedule']).split(" ",1)
                start_end = splitter[1].split("-",1)
                days.append(splitter[0])
                start_time.append(time_convert(start_end[0]))
                end_time.append(time_convert(start_end[1]))
                location.append(tables[i].loc[0,'Location'])
            else:
                if(tables[i].loc[0,'Location'] in location):
                    professor_name.append((tables[i].loc[0,'Instructor'] ))
                    splitter = ((tables[i]).loc[0,'Schedule']).split(" ",1)
                    start_end = splitter[1].split("-",1)
                    days.append(splitter[0])
                    start_time.append(time_convert(start_end[0]))
                    end_time.append(time_convert(start_end[1]))
                    location.append(tables[i].loc[0,'Location'])
                    
    
    else:       
        for i in range (spring_index,len(tables)):
            if(tables[i].loc[0,'Instructor'] not in professor_name):    #Implemented check to ensure only lecture sections are caught.(Still needs some more work)
                professor_name.append((tables[i].loc[0,'Instructor'] ))
                splitter = ((tables[i]).loc[0,'Schedule']).split(" ",1)
                start_end = splitter[1].split("-",1)
                days.append(splitter[0])
                start_time.append(time_convert(start_end[0]))
                end_time.append(time_convert(start_end[1]))
                location.append(tables[i].loc[0,'Location'])
            else:
                if(tables[i].loc[0,'Location'] in location):
                    professor_name.append((tables[i].loc[0,'Instructor'] ))
                    splitter = ((tables[i]).loc[0,'Schedule']).split(" ",1)
                    start_end = splitter[1].split("-",1)
                    days.append(splitter[0])
                    start_time.append(time_convert(start_end[0]))
                    end_time.append(time_convert(start_end[1]))
                    location.append(tables[i].loc[0,'Location'])
                
    filename = "test.csv"
    if(call_count == 0):
        call_count = call_count + 1
        with open(filename, 'w', newline ='') as csvfile:
            csvwriter = csv.writer(csvfile)
            for i in range(0,len(professor_name)):
                row = [course_name,professor_name[i],start_time[i], end_time[i],days[i]]
                csvwriter.writerow(row)
    else:
        with open(filename, 'a', newline ='') as csvfile:
            csvwriter = csv.writer(csvfile)
            for i in range(0,len(professor_name)):
                row = [course_name,professor_name[i],start_time[i], end_time[i],days[i]]
                csvwriter.writerow(row)
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    