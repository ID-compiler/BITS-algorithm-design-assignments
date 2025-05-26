## Candy Distribution Problem

This repository implements a solution to the classic **Candy Distribution Problem** using a **two-pass greedy algorithm**.

## Problem Statement

Given a list of ratings for students standing in a line, distribute candies such that:

1. Every student must receive **at least one candy**.
2. A student with a **higher rating than an immediate neighbor** must receive **more candies** than that neighbor.

### Input

- A list of integers representing student ratings.

### Output

- The **minimum total number of candies** required.
- A list showing the **distribution of candies** among students.

---

## Approach: Two-Pass Greedy Algorithm

1. **Initialize** an array where each student gets 1 candy.
2. **Left to Right Pass**:
   - If the current student has a **higher rating than the left neighbor**, give one more candy than the left neighbor.
3. **Right to Left Pass**:
   - If the current student has a **higher rating than the right neighbor**, and has **not already been given more candies**, give one more than the right neighbor.

This ensures both rules are satisfied in an efficient manner.

---

## Example

### Input
