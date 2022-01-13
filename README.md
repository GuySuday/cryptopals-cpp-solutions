# Cryptopals Solutions in C++
## Introduction
[Cryptopals](https://cryptopals.com/) is a set of cryptographic challenges, which teach "how cryptosystems are built, but also how they're attacked".

I decided to implement them in C++.

## Code Layout
* `sets/`: The challenges' solutions, divided into sets
* `utils/`: The various utils I used in order to solve the challenges
* `tests/`: The challenges' tests and utils't tests

## Challenges progress

| Set #            | Challenges # | Solved | Total |
| :--------------- | :----------: | :----: | :---: |
| (1) Basics       |     1-8      |   8    |   8   |
| (2) Block Crypto |     9-16     |   3    |   8   |

## Setup
### Linux

* Install opessl:
    ```bash
    sudo apt install libssl-dev
    ```