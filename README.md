# CS 3503 Assignment 2 - Data Representation & Mapping

## Author
Hemanth Rao

## Description
This project extends Assignment 1 by adding advanced data representation functions for Owl Tech’s CPU design team.  
It includes:
- Direct mapping functions (octal ↔ binary ↔ hex)
- Signed number representations (sign-magnitude, one’s complement, two’s complement)

## What’s New
- Implemented `oct_to_bin`, `oct_to_hex`, `hex_to_bin`
- Implemented `to_sign_magnitude`, `to_ones_complement`, `to_twos_complement`
- Reused the test harness from A1

## Build Instructions
```bash
gcc -o convert convert.c main.c
./convert
