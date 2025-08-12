# Push_swap

## 📌 Overview
**Push_swap** is a sorting algorithm project from [42 School](https://42.fr/).  
The goal is to sort a stack of integers with the fewest possible operations using a restricted set of stack manipulation instructions.  
This project tests your ability to design efficient algorithms, manage complexity, and implement robust C code.

---

## 🎯 Objective
Given a list of integers as arguments, your program must output a sequence of predefined operations that will sort the numbers in ascending order.  
You’ll also write a **checker** program to verify the correctness of the output.

---

## ⚙️ Allowed Operations
- `sa` — swap the first 2 elements of stack **A**
- `sb` — swap the first 2 elements of stack **B**
- `ss` — `sa` and `sb` at the same time
- `pa` — push the first element of **B** onto **A**
- `pb` — push the first element of **A** onto **B**
- `ra` — rotate **A** upwards
- `rb` — rotate **B** upwards
- `rr` — `ra` and `rb` at the same time
- `rra` — reverse rotate **A** downwards
- `rrb` — reverse rotate **B** downwards
- `rrr` — `rra` and `rrb` at the same time

---

## 🛠️ Implementation Details
- **Language:** C
- **Paradigm:** Algorithmic problem-solving with complexity optimization
- **Algorithm choice:** 
  - Small datasets: simple swap/rotate strategy
  - Large datasets: chunk-based or radix sort inspired method
- **Error handling:** Detects duplicates, non-numeric arguments, and integer overflow

---

## 📦 Installation & Compilation

If your project uses `libft` as a submodule:
```bash
git clone --recurse-submodules <repo-url>
cd push_swap
make

---

## 🚀 Usage
Sorting

./push_swap 4 67 3 87 23

---

📈 Performance

The efficiency of your program is measured by:

    Number of operations (fewer is better)

    Correctness (always sorted at the end)

    Handling of edge cases (empty input, already sorted, duplicates, etc.)

---

🧠 Key Learnings

    Designing algorithms with time and space complexity in mind

    Managing two stacks with minimal operations

    Writing clean, modular, and maintainable C code

    Implementing robust input validation
