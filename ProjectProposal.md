# Final Project Proposal

## Leading Question
What is the size of the largest strongly connected component of the digraph of domains starting with “https://courses.engr.illinois.edu/cs225/fa2021”?
A successful project will be if we can answer the above question with a finite exact number.
## Dataset Acquisition and Processing
1. To collect the data, we plan to create a script to collect all the URLs on a website, and visit each one of the websites, repeating the URL collection for each visited website. To start, we will collect the data from the Fall 2021 CS 225 website. Based on how much data we can collect from this, we may or may not need to look at other domains. Other options include the CS 126 website, CS 124 website, and other similar websites. 
2. When collecting the data, we may run across pages that do not exist. In this case, we won’t count them as erroneous or any as a missing entry, but as “end-nodes” for our graph.
3. Ben will write a Selenium browser emulation scraper which is described below:
    - The scraper will visit a start page, in this case “https://courses.engr.illinois.edu/cs225/fa2021/” and will collect the text content of all clickable, visible, and enabled elements with an end xpath of “//a@[href]” (urls of clickable links). This data collection method will be followed on all pages
    - This scraper cannot be a headless scraper or a simple page request with a regex filter for links due to the structure of Doxygen which requires user interactions on dropdowns in order to load all possible links into the DOM. These user interactions will be simulated using selenium.
    - The scraper will output in the form “<current_url>: <url_on_page>, <url_on_page>, <url_on_page>, <url_on_page>, “. This output should be easily importable to c++ due to the lack of spaces in urls, making the ability to split on the two delimiters “, “ and “: “ straightforward. Once data on page is collected and outputted to file for storage, all previous unseen links that have a valid start of their URI’s (only traversing CS225 website for the fall 2021 semester), will be added to a structure to be visited later.
    - If during collection we are rate-limited by the website server, the program will terminate and will be manually restarted after a cool down time or after changing to a VPN.
    - Progress will not be lost between separate scraper runs due to the addition of the ability of the scraper to read previously scraped information and continue where left off.
    - This web scraper will be written in python. 


## Graph Algorithms
### Traversal
Depth First Search to visit all the nodes in our graph. The input to this algorithm will be our graph and the output of the traversal will be the number of nodes in the graph. The time complexity of this traversal is expected to be O(v), where v is the number of vertices in the graph.

### Algorithm #1
Pagerank. We will implement the standard pagerank algorithm to determine which are the most important sites on the class webpage. The starting weights will be determined by the number of times a link appears on a given page. The runtime complexity should be O(v+e), where v and e are vertices and edges respectively. We will use this method to determine the steady state probability vector if you start on the main course homepage. The input will be our graph and the output will be the steady state starting from the main course page.

### Algorithm #2
Algorithm #2 : Tarjan's strongly connected components algorithm. Our input to this algorithm will be our graph of the cs225 website and the output will be the sizes of the strongly connected components of the site and a representative from that component. We expect the runtime of this algorithm to be O(v+e), where v and e are vertices and edges respectively.

## Timeline

### Mid-Project Check In (Nov 29th – Dec 4): 
Finish data collection and processing

### Week 1-2: Nov. 7th - Nov. 20th

Collect the data outlined in point # 2

Figure out how to process the data (i.e write some data processing class, possibly using an existing library)

### Week 3-4.5: Nov. 21st - Dec. 8th

Work on algorithms

Finish all algorithms by December 8th

### Until Due Date

Work on final project report

Goals, Development, Results files finished by Dec. 10th. Leave a day for revision on Dec. 11th. 

Record final presentation on Dec. 12th

