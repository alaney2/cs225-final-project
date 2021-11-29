import time
import json
from os.path import dirname
import os
import sys

sys.path.append(dirname(r"c:\users\becla\appdata\local\programs\python\python38\lib\site-packages\."))
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.support import expected_conditions
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities


previous_url = "https://courses.engr.illinois.edu/cs225/fa2021/"
elems_to_explore = [previous_url]
explored_pages = set()

driver = webdriver.Chrome(r"chromedriver.exe")
driver.set_window_size(1920, 1140)

while(len(elems_to_explore) != 0):
    driver.get(current_url)


    for elem in click_stack: #get back to previous state
        elem.click()
        time.sleep(0.05)

    do_not_click = set()
    new_clickable = set(driver.find_elements_by_xpath("//a[@href]"))
    things_to_click = new_clickable.difference(current_things_to_click)
    # print(things_to_  click)
    for clickable in things_to_click:
        if clickable in do_not_click:
            continue
        num_clickable = len(driver.find_elements_by_xpath("//a[@href]"))
        att = clickable.get_attribute("href")
        if (att == "javascript:void(0)"):
            # print(clickable.find_elements_by_tag_name("img"))
            if (len(clickable.find_elements_by_tag_name("img"))):
                if clickable.find_elements_by_tag_name("img")[0].get_attribute("src") == "https://courses.engr.illinois.edu/cs225/fa2021/doxygen/mp_mazes/ftv2pnode.png":
                    clickable.click()
                    do_not_click.add(clickable)


            new_elems = driver.find_elements_by_xpath("//a[@href]")
            print("num_clickable", num_clickable)
            print("new_num_click", len(new_elems))
            if (num_clickable > len(new_elems)):
                do_not_click.add(clickable)
            else:
                break
        if not explored_pages.contains(link):
            #check if url or not
            elems_to_explore.append(link)



driver.quit()

# num_elems = len(elems)
# for elem in elems:
#     att = elem.get_attribute("href")
#     if (att == "javascript:void(0)"):
#         if (elem.is_displayed() and elem.is_enabled()):
#             elem.click()
#         # new_elems = elems = driver.find_elements_by_xpath("//a[@href]")
#         # if (num_elems < len(new_elems)):
#         #     elem.click()
#
#     print(elem.get_attribute("href"))
