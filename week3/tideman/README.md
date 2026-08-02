# Tideman

Solution to the **Tideman** problem from Harvard's **CS50x: Introduction to Computer Science**.

## About the project

Tideman is a ranked-choice election program based on the **Ranked Pairs voting method**.

The program collects voters' preferences, determines the strongest victories between candidates, builds a directed graph while avoiding cycles, and finally finds the winner.

## My implementation

The starter code and program structure were provided by CS50. I implemented the required functions:

* `vote`
* `record_preferences`
* `add_pairs`
* `sort_pairs`
* `creates_cycle`
* `lock_pairs`
* `print_winner`

## Concepts practiced

This problem helped me practice:

* Arrays and matrices
* Structures (`struct`)
* Sorting algorithms
* Directed graphs
* Recursion and graph traversal

## Main challenge

Tideman was one of the most challenging problems I completed in CS50x because it required understanding graphs and recursion.

The most difficult part was implementing cycle detection, which required creating a recursive search through the locked graph before adding new edges.
