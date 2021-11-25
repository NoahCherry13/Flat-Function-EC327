# -*- coding: utf-8 -*-
"""
Created on Thu Nov 25 10:55:19 2021

@author: prane
"""
#Pranet - to get the libraries that support the data scraper
import pandas as pd


#Pranet- Testing URL logic for multiple websites

class_code = input("Enter the class you want to take with spaces: ")

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
for i in range (0,len(tables)):
    print(tables[i])


    
    

