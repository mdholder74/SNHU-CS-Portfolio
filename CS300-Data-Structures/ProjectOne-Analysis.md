# Project One: Data Structure Analysis
## ABCU Advising Program

**Course:** CS 300 - Data Structures and Algorithms  
**Student:** Moe  
**Date:** December 2025

---

## Executive Summary

This document analyzes three data structures for the ABCU Computer Science advising assistance program: **Vector**, **Hash Table**, and **Binary Search Tree (BST)**. The analysis evaluates runtime complexity, memory usage, and suitability for the program's core operations.

**Recommendation:** Binary Search Tree is the optimal choice for this application.

---

## Problem Statement

The ABCU Computer Science department requires a system to help academic advisors:
- Load course data from a file
- Display courses in alphanumeric order
- Search for specific courses
- Display course prerequisites

The system must handle approximately 50+ courses efficiently while maintaining data integrity.

---

## Data Structure Comparison

### 1. Vector (Dynamic Array)

**Description:** Sequential storage with contiguous memory allocation.

**Runtime Complexity:**
| Operation | Time Complexity | Explanation |
|-----------|----------------|-------------|
| Load Data | O(n) | Insert each course sequentially |
| Search | O(n) | Linear search through unsorted data |
| Sort | O(n log n) | Requires sorting algorithm (e.g., quicksort) |
| Display Sorted | O(n) | Iterate through sorted vector |
| Insert | O(1) amortized | Add to end (occasional resize) |

**Memory Usage:**
- Space Complexity: O(n)
- Memory overhead: Minimal (contiguous allocation)
- Dynamic resizing may cause temporary memory spikes

**Advantages:**
- Simple to implement
- Cache-friendly (contiguous memory)
- Fast iteration
- Good for small datasets

**Disadvantages:**
- Requires explicit sorting (O(n log n))
- Linear search is slow for large datasets
- Insertion in middle is expensive O(n)

---

### 2. Hash Table

**Description:** Key-value storage using hash function for O(1) average access.

**Runtime Complexity:**
| Operation | Time Complexity | Explanation |
|-----------|----------------|-------------|
| Load Data | O(n) | Hash and insert each course |
| Search | O(1) average | Direct access via hash key |
| Sort | O(n log n) | Must extract and sort separately |
| Display Sorted | O(n log n) | Extract keys, sort, then display |
| Insert | O(1) average | Hash and place in bucket |

**Memory Usage:**
- Space Complexity: O(n)
- Memory overhead: Higher (20-50% overhead for buckets/pointers)
- Load factor affects performance and memory

**Advantages:**
- Extremely fast search O(1)
- Fast insertion O(1)
- Excellent for lookup-heavy applications

**Disadvantages:**
- Does NOT maintain sorted order
- Requires separate sorting operation
- Hash collisions can degrade performance
- Higher memory overhead
- Not ideal when sorted output is frequently needed

---

### 3. Binary Search Tree (BST)

**Description:** Hierarchical structure maintaining sorted order through node relationships.

**Runtime Complexity:**
| Operation | Time Complexity | Explanation |
|-----------|----------------|-------------|
| Load Data | O(n log n) | Insert each course with O(log n) placement |
| Search | O(log n) average | Binary search through tree structure |
| Sort | O(n) | In-order traversal naturally sorted |
| Display Sorted | O(n) | In-order traversal visits nodes in order |
| Insert | O(log n) average | Navigate tree to correct position |

**Note:** Worst case (unbalanced tree) degrades to O(n), but average case with randomized data is O(log n).

**Memory Usage:**
- Space Complexity: O(n)
- Memory overhead: Moderate (two pointers per node)
- No wasted space from resizing

**Advantages:**
- Maintains sorted order automatically
- Fast search O(log n)
- Efficient insertion O(log n)
- In-order traversal provides sorted output naturally
- No explicit sorting needed

**Disadvantages:**
- More complex implementation
- Can become unbalanced (mitigated with balanced BST variants)
- Slightly higher memory per element (pointers)

---

## Comparative Analysis

### Performance Summary Table

| Criteria | Vector | Hash Table | BST |
|----------|--------|------------|-----|
| **Search Speed** | Slow O(n) | Fastest O(1) | Fast O(log n) |
| **Sorted Display** | Requires sort O(n log n) | Requires sort O(n log n) | Natural O(n) |
| **Memory Efficiency** | Best | Worst | Good |
| **Implementation Complexity** | Simple | Moderate | Complex |
| **Best Use Case** | Small datasets, rare searches | Lookup-heavy, no sorting needed | Frequent searches AND sorted output |

### Analysis by Operation Frequency

**For ABCU Advising Program:**
1. **Load data:** One-time operation (any structure works)
2. **Display sorted list:** FREQUENT requirement → BST advantage
3. **Search for course:** FREQUENT requirement → Hash Table or BST advantage
4. **Maintain order:** CONSTANT requirement → BST advantage

---

## Recommendation: Binary Search Tree

### Rationale

The BST is the optimal choice because:

1. **Sorted Output Efficiency:** The program frequently needs to display courses alphabetically. BST provides this in O(n) time through in-order traversal, while Vector and Hash Table require O(n log n) sorting.

2. **Search Performance:** O(log n) search is sufficiently fast for ~50 courses and scales well as the dataset grows.

3. **No Redundant Sorting:** Unlike Vector and Hash Table, BST maintains order automatically, eliminating the need for repeated sorting operations.

4. **Balanced Performance:** BST offers the best compromise between search speed, sorted display, and memory usage for this application's specific requirements.

5. **Data Integrity:** The tree structure naturally prevents duplicate course numbers and maintains consistency.

### Trade-offs Accepted

- Slightly more complex implementation than Vector
- Search is O(log n) instead of Hash Table's O(1) average
- Requires careful implementation to avoid unbalanced trees

These trade-offs are acceptable because:
- Implementation complexity is a one-time cost
- O(log n) is still very fast for the dataset size
- Proper insertion logic maintains reasonable balance

---

## Conclusion

After analyzing runtime complexity, memory usage, and operational requirements, the **Binary Search Tree** is the recommended data structure for the ABCU advising assistance program. Its ability to maintain sorted order naturally while providing efficient search operations makes it ideal for the application's frequent need to display courses alphabetically and search for specific courses.

The BST implementation successfully balances performance, memory efficiency, and functionality requirements, making it the optimal solution for this use case.
