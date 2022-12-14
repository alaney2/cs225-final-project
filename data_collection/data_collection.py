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
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities

chrome_options = Options()
chrome_options.add_argument("--wm-window-animations-disabled")
chrome_options.add_argument("--force-prefers-reduced-motion")
chrome_options.add_argument("--start-maximized");
driver = webdriver.Chrome(r"chromedriver.exe",options=chrome_options)


previous_url = "https://courses.engr.illinois.edu/cs225/fa2021/"

elems_to_explore = [previous_url]
explored_pages = set()

old_filename = "example2.txt"
new_filename = "example3.txt"

#When website rate limits, neeed to restore data
def restore_data():
    with open(old_filename) as f:
        temp_set_to_explore = set()
        lines = f.readlines()
        for line in lines[:-1]:
            main_info =  line.split(": ")
            explored_pages.add(main_info[0])
            linked_pages = main_info[1].split(", ")
            for linked_page in linked_pages:
                if linked_page.startswith("https://courses.engr.illinois.edu/cs225/fa2021"):
                    temp_set_to_explore.add(linked_page)
        for linked_page in temp_set_to_explore:
            if linked_page not in explored_pages:
                elems_to_explore.insert(0, linked_page)

restore_data()
print("Previously visted count: ", len(explored_pages))
print("Restore Data Done")

def check_any_to_click(driver):
    things_to_click = set(driver.find_elements_by_xpath("//a[@href]"))
    for clickable in things_to_click:
        att = clickable.get_attribute("href")
        if (att == "javascript:void(0)"):
            images = clickable.find_elements_by_tag_name("img")
            if (len(images) >= 1):
                if images[0].get_attribute("src").startswith("https://courses.engr.illinois.edu/cs225/fa2021/") and images[0].get_attribute("src").endswith("ftv2pnode.png"):
                    return True
            spans = clickable.find_elements_by_tag_name("span")
            if len(spans) >= 1:
                if spans[0].text == "???":
                    return True
    return False


done = False
with open(new_filename, "w") as f:
    while(len(elems_to_explore) != 0):
        current_url = elems_to_explore[-1]
        while current_url in explored_pages:
            elems_to_explore.pop()
            if len(elems_to_explore) == 0:
                done = True
                break
            current_url = elems_to_explore[-1]
        if done:
            break
        explored_pages.add(current_url)
        driver.get(current_url)

        while check_any_to_click(driver):
            new_clickable = set(driver.find_elements_by_xpath("//a[@href]"))
            for clickable in new_clickable:

                att = clickable.get_attribute("href")
                if (att == "javascript:void(0)"):
                    images = clickable.find_elements_by_tag_name("img")
                    if len(images) >= 1:
                        if images[0].get_attribute("src").startswith("https://courses.engr.illinois.edu/cs225/fa2021/") and images[0].get_attribute("src").endswith("ftv2pnode.png"):
                            if (clickable.is_displayed() and clickable.is_enabled()):
                                driver.execute_script("arguments[0].click();", clickable)
                    spans = clickable.find_elements_by_tag_name("span")
                    if len(spans) >= 1:
                        if spans[0].text == "???":
                            if (clickable.is_displayed() and clickable.is_enabled()):
                                driver.execute_script("arguments[0].click();", clickable)


        elems_to_explore.pop()
        print(current_url, end = ": ", file=f)
        all_elems = set(driver.find_elements_by_xpath("//a[@href]"))
        for elem in all_elems:
            address = elem.get_attribute("href")
            if (not address.startswith("javascript:") and len(address) > 0):
                print(address, end = ", ", file=f)
                if (address not in explored_pages and address.startswith("https://courses.engr.illinois.edu/cs225/fa2021")):
                    elems_to_explore.insert(0, address)


        print("", file=f)
        print("Done with: ", current_url)
                # else:

    driver.quit()
print("At the end")
