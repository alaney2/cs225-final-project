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
Depth First Search to visit all the nodes in our graph. 

### Algorithm #1
Kirchhoff's Theorem to find the number of spanning trees in the graph. The input would be a graph, and the output would be a number that shows how many spanning trees there are in the input graph. The expected runtime is O(v) for a complete graph, and O(v^3) for a not complete graph. 

### Algorithm #2
Tarjan's strongly connected components algorithm or Kosaraju-Sharir's algorithm to find strongly connected components. Our input to this algorithm will be a series of nodes (URLs) and the output will be whether it is a strongly connected component or not. We expect the runtime of this algorithm to be linear (O(v+e)), where v and e are vertices and edges respectively.
We aim to have all algorithms run in at worst O(n2) time, for both Dijkstra’s Algorithm as well as Tarjan’s strongly connected components algorithm or 
Kosaraju-Sharir’s algorithm.

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

