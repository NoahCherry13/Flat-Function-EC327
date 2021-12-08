
# Flat-Function
Team Members - Aya Kassem, Noah Cherry, Rishav De, Pranet Sharma  
Team Member Emails - ayak@bu.edu, ncherry@bu.edu, rishavde@bu.edu, pranetsh@bu.edu  

Overview-  
Our project is an automatic class scheduling program that selects the best possible lecture sections for a student using RateMyProfessor ratings and ensures that there is no time conflict.   

Technical Overview-  
Our project utilizes a web scraper built in Python to obtain class information from the BU website. We also utlize a RateMyProfessor API in Python to obtain the ratings for all Professors who do have a review. All relevant information is then stored in the form of a csv and then used by a scheduling algorithm in C++ that finds out all possible schedules without time conflicst and displays them in descending order of total average rating.  

Youtube video link -  (NIL)

Relevant information -  
Link to RateMyProfessor API (certain modifications were made to the source code) - https://github.com/tisuela/ratemyprof-api  
Link to GUI -   https://github.com/friedmud/variadic_table  
The bashscript successfully runs on a few of our systems. However it may not work on some systems. The video shows the program working without the bashscript.
