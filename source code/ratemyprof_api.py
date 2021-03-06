import requests
import json
import math
import csv
import os
import pandas as pd

from professor import Professor
# This code has been tested using Python 3.6 interpreter and Linux (Ubuntu).
# It should run under Windows, if anything you may need to make some adjustments for the file paths of the CSV files.



class ProfessorNotFound(Exception):
    def __init__(self, search_argument, search_parameter: str = "Name"):

        # What the client is looking for. Ex: "Professor Pattis"
        self.search_argument = self.search_argument

        # The search criteria. Ex: Last Name
        self.search_parameter = search_parameter

    def __str__(self):

        return (
            f"Proessor not found"
            + f" The search argument {self.search_argument} did not"
            + f" match with any professor's {self.search_parameter}"
        )


class RateMyProfApi:
    def __init__(self, school_id: str = "124", testing: bool = False):
        self.UniversityId = school_id
        self.professorID = int
        if not os.path.exists("SchoolID_" + str(self.UniversityId)):
            os.mkdir("SchoolID_" + str(self.UniversityId))

        # dict of Professor
        self.professors= self.scrape_professors(testing)
        self.indexnumber = False

    def scrape_professors(
        self,
        testing: bool = False
    ):  # creates List object that include basic information on all Professors from the IDed University
        professors = dict()
        num_of_prof = self.get_num_of_professors(self.UniversityId)
        num_of_pages = math.ceil(num_of_prof / 20)

        for i in range(1, num_of_pages + 1):  # the loop insert all professor into list
            page = requests.get(
                "http://www.ratemyprofessors.com/filter/professor/?&page="
                + str(i)
                + "&filter=teacherlastname_sort_s+asc&query=*%3A*&queryoption=TEACHER&queryBy=schoolId&sid="
                + str(self.UniversityId)
            )
            json_response = json.loads(page.content)
            temp_list = json_response["professors"]


            for json_professor in json_response["professors"]:
                #print(json_professor)
                professor = Professor(
                    json_professor["tid"],
                    json_professor["tFname"],
                    json_professor["tLname"],
                    json_professor["tNumRatings"],
                    json_professor["overall_rating"],
                    json_professor["tDept"])

                professors[professor.ratemyprof_id] = professor

            # for test cases, limit to 2 iterations
            if testing and (i > 1): break

        return professors

    def get_num_of_professors(
        self, id
    ):  # function returns the number of professors in the university of the given ID.
        page = requests.get(
            "http://www.ratemyprofessors.com/filter/professor/?&page=1&filter=teacherlastname_sort_s+asc&query=*%3A*&queryoption=TEACHER&queryBy=schoolId&sid="
            + str(id)
        )  # get request for page
        temp_jsonpage = json.loads(page.content)
        num_of_prof = (
            temp_jsonpage["remaining"] + 20
        )  # get the number of professors at William Paterson University
        return num_of_prof

    def search_professor(self, ProfessorName):
        self.indexnumber = self.get_professor_index(ProfessorName)
        self.print_professor_info()
        return self.indexnumber



    def get_professor_by_last_name(
        self, last_name
    ) -> Professor:
        '''
        Return the first professor with the matching last name.
        Case insenstive.
        '''
        last_name = last_name.lower()
        for name in self.professors:
            if last_name == self.professors[name].last_name.lower():
                return self.professors[name]

        # Raise error if no matching professor found
        raise ProfessorNotFound(last_name, "Last Name")





    def WriteProfessorListToCSV(self):
        csv_columns = [
            "tDept",
            "tSid",
            "institution_name",
            "tFname",
            "tMiddlename",
            "tLname",
            "tid",
            "tNumRatings",
            "rating_class",
            "contentType",
            "categoryType",
            "overall_rating",
        ]
        csv_file = "SchoolID_" + str(self.UniversityId) + ".csv"
        with open(csv_file, "w") as csvfile:
            writer = csv.DictWriter(csvfile, fieldnames=csv_columns)
            writer.writeheader()
            for data in self.professorlist:
                writer.writerow(data)

    def create_reviews_list(self, tid):
        tempreviewslist = []
        num_of_reviews = self.get_num_of_reviews(tid)
        # RMP only loads 20 reviews per page,
        # so num_of_pages tells us how many pages we need to get all the reviews
        num_of_pages = math.ceil(num_of_reviews / 20)
        i = 1
        while i <= num_of_pages:
            page = requests.get(
                "https://www.ratemyprofessors.com/paginate/professors/ratings?tid="
                + str(tid)
                + "&filter=&courseCode=&page="
                + str(i)
            )
            temp_jsonpage = json.loads(page.content)
            temp_list = temp_jsonpage["ratings"]
            tempreviewslist.extend(temp_list)
            i += 1
        return tempreviewslist

    def get_num_of_reviews(self, id):
        page = requests.get(
            "https://www.ratemyprofessors.com/paginate/professors/ratings?tid="
            + str(id)
            + "&filter=&courseCode=&page=1"
        )
        temp_jsonpage = json.loads(page.content)
        num_of_reviews = temp_jsonpage["remaining"] + 20
        return num_of_reviews

    def WriteReviewsListToCSV(self, rlist, tid):
        csv_columns = [
            "attendance",
            "clarityColor",
            "easyColor",
            "helpColor",
            "helpCount",
            "id",
            "notHelpCount",
            "onlineClass",
            "quality",
            "rClarity",
            "rClass",
            "rComments",
            "rDate",
            "rEasy",
            "rEasyString",
            "rErrorMsg",
            "rHelpful",
            "rInterest",
            "rOverall",
            "rOverallString",
            "rStatus",
            "rTextBookUse",
            "rTimestamp",
            "rWouldTakeAgain",
            "sId",
            "takenForCredit",
            "teacher",
            "teacherGrade",
            "teacherRatingTags",
            "unUsefulGrouping",
            "usefulGrouping",
        ]
        csv_file = (
            "./SchoolID_" + str(self.UniversityId) + "/TeacherID_" + str(tid) + ".csv"
        )
        with open(csv_file, "w") as csvfile:
            writer = csv.DictWriter(csvfile, fieldnames=csv_columns)
            writer.writeheader()
            for data in rlist:
                writer.writerow(data)

    def GetID(self, ln):
        count = 0
        counter = 0
        departmentlist = []
        for profID in self.professors:
            if self.professors[profID].last_name == ln:
               self.professorID = profID
               count+=1

        if (count >1):
            print("Multiple professors found, please enter their department from the list")
            for profID in self.professors:
                if self.professors[profID].last_name == ln:
                    departmentlist.append(self.professors[profID].department)
                    print(self.professors[profID].department)

            
            department = input("Please enter department here (if the department is not listed above please enter it yourself): ")
            
            if (department not in departmentlist):
                return -1000
            
            for department_name in departmentlist:
                if (department_name == department):
                    counter = counter + 1
            
            if (counter > 1):
                return -1000
            
            for profID in self.professors:
                if self.professors[profID].last_name == ln and self.professors[profID].department == department:
                    self.professorID = profID
                    return self.professorID
        else:
            return self.professorID

    def GetAverageRating(self,name):
            
        if(self.GetID(name) != -1000):
            return self.professors[self.GetID(name)].overall_rating
        else:
            return 0






# Time for some examples!
if __name__ == '__main__':

    # Getting general professor info!
    bu = RateMyProfApi(124)
    #print(bu.professors[1553112].overall_rating)
    #professor_names = ["Lin", "Goh"]
    #for names in professor_names:
        #print(bu.GetAverageRating(names))
    #print(uci.GetAverageRating("Densmore"))


#Pranet - to get the libraries that support the data scraper
#Function to convert hours from 12 hour format to 24 hours format
def time_convert(t):
    am_or_pm = t.split(" ",1)
    if(am_or_pm[1] == "pm" and am_or_pm[0][:2] != "12"):
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
    ratings = []
    
    
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
                
    
    print(professor_name)
    for names in professor_name:
        print(names)
        print(bu.GetAverageRating(names))
        ratings.append(bu.GetAverageRating(names))
        #ratings[i] = bu.GetAverageRating(professor_name[i])
        
    
    
    filename = "test.csv"
    if(call_count == 0):
        call_count = call_count + 1
        with open(filename, 'w', newline ='') as csvfile:
            csvwriter = csv.writer(csvfile)
            for i in range(0,len(professor_name)):
                row = [course_name,professor_name[i],ratings[i],start_time[i], end_time[i],days[i]]
                csvwriter.writerow(row)
    else:
        with open(filename, 'a', newline ='') as csvfile:
            csvwriter = csv.writer(csvfile)
            for i in range(0,len(professor_name)):
                row = [course_name,professor_name[i],ratings[i],start_time[i], end_time[i],days[i]]
                csvwriter.writerow(row)