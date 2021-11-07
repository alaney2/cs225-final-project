# Final Project Proposal

## Leading Question
What is the size of the largest strongly connected component of the digraph of domains starting with “https://courses.engr.illinois.edu/cs225/fa2021”?
A successful project will be if we can answer the above question with a finite exact number.
## Dataset Acquisition and Processing
To collect the data, we plan to create a script to collect all the URLs on a website, and visit each one of the websites, repeating the URL collection for each visited website. To start, we will collect the data from the Fall 2021 CS 225 website. Based on how much data we can collect from this, we may or may not need to look at other domains. Other options include the CS 126 website, CS 124 website, and other similar websites. 
When collecting the data, we may run across pages that do not exist. In this case, we won’t count them as erroneous or any as a missing entry, but as “end-nodes” for our graph.

## Graph Algorithms
### Traversal - Depth First Search

### Algorithm #1: Dijkstra's Algorithm - shortest path

### Algorithm #2 : 
Tarjan's strongly connected components algorithm or Kosaraju-Sharir's algorithm. 
                      We aim to have all algorithms run in at worst O(n^2) time. 
## Timeline

### Mid-Project Check In (Nov 29th – Dec 1): 
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

