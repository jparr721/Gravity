# Gravity
Simulated low-level software environments for high level analysis

## What is this?
Gravity allows you to constrain the runtime environment of an executable into a container of varying memory and processor size. The goal is to be a useful, robust tool for developing on memory constrained applications.

## Usage
```
Usage: grv [PROGRAM] [SOFT LIMIT] [HARD LIMIT] [FLAGS]
Run program in a memory constrained environment

Mandatory arguments to long options are mandatory for short options too.
  [SOFT LIMIT]                Set the soft limit for the designated program
  [HARD LIMIT]                Set the hard limit for the desginated program
  [FLAGS]                     Set the flags or positional arguments for the program

Exit status:
 0  if OK,
 1  if problem running program
```
