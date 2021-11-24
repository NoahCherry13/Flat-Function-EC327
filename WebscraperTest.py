# -*- coding: utf-8 -*-
"""
Created on Wed Nov 24 11:39:00 2021

@author: prane
"""

from selenium import webdriver # allow launching browser
from selenium.webdriver.common.by import By # allow search with parameters
from selenium.webdriver.support.ui import WebDriverWait # allow waiting for page to load
from selenium.webdriver.support import expected_conditions as EC # determine whether the web page has loaded
from selenium.common.exceptions import TimeoutException # handling timeout situation
#Fixes error while extracting data
import pandas as pd

driver_option = webdriver.ChromeOptions()
driver_option.add_argument(" — incognito")
chromedriver_path = 'C:/Users/prane/Documents/chromedriver_win32/chromedriver.exe' # Change this to your own chromedriver path!
def create_webdriver():
 return webdriver.Chrome(executable_path=chromedriver_path, chrome_options=driver_option)

#We will need to generate the browser URL by ourself
#Pranet - This URL is simply a test
browser = create_webdriver()
browser.get("https://github.com/collections/machine-learning")

# Extract all projects
# Pranet - We will need to analyze the HTML code of a website and find out which element we need to find based on that
projects = browser.find_elements_by_xpath("//h1[@class='h3 lh-condensed']") #Pranet - For ther BU website I belive the hpath is h4

# Extract information for each project
# Pranet - We will need to initialize our own variables and store information according to that
project_list = {}
for proj in projects:
 proj_name = proj.text # Project name
 proj_url = proj.find_elements_by_xpath("a")[0].get_attribute('href') # Project URL
 project_list[proj_name] = proj_url
 
 # Close connection
browser.quit()

# Extracting data
# Pranet- We will probably need to modify all of this because our information will be quite different in format
project_df = pd.DataFrame.from_dict(project_list, orient = 'index')

# Manipulate the table
project_df['project_name'] = project_df.index
project_df.columns = ['project_url', 'project_name']
project_df = project_df.reset_index(drop=True)

# Export project dataframe to CSV
project_df.to_csv('project_list.csv')


