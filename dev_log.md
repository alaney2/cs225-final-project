## Nov 8-14:

Draft team contract and project proposal

---

## Nov 15-21:

Data scraping script with the origin being https://courses.engr.illinois.edu/cs225/fa2021/

- Problem: Unlike normal webpages, each Doxygen page has buttons that need to be clicked in order to generate a new URL.
  We solved this by simulating button clicks in the Python script.

Make necessary changes to project proposal

---

## Nov 22-28:

Implement graph class - data processing

- Figure out what kind of data structures we should store the data in.

---

## Nov 29 - Dec 5:

Implement graph class - data processing Makefile, test cases: catch

---

## Dec 6-12:

#### Project Structure

- Parser (and helper function) Tests
- Rewrote Parser, there was an error with dealing with urls that had spaces, /, or \ at the front or back.
- MakeFile Adjustments

#### DFS Traversal

- Implemented the DFS traversal using a stack. Manually added the base URL, then had a while loop that ran on the
  condition that the stack is not empty. We have a "visited" vector booleans corresponding to urls, all of which are
  initially false, and are marked true when encountered in the while loop. If a URL in the neighbors already has been
  visited, it is not added to the stack. Whenever we process a node, we append it to the end of a string. In the future,
  we may implement saving of this string into a file.

#### Page-Rank Algorithm

- Implemented Standard PageRank. Calculate Adjacency Matrix, calculate standard pagerank matrix, create a starting state
  vector based on either current root or passed start node. Terminate steady state vector after 50 iterations, which
  should be plenty of iterations to reach a steady state. In the future might adjust this so that we terminate when the
  k-norm difference of the current vector with the previous vector is less than some bound.

#### Tarjan's Algorithm

### Main executable

- Created a graph object with the original dataset and called on algorithms that we have implemented. Output each final result.