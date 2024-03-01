## Description

``` The uniq utility reads the specified input_file comparing adjacent lines, and
writes a copy of each unique input line to the output_file.  If input_file is a
single dash (‘-’) or absent, the standard input is read.  If output_file is
absent, standard output is used for output.  The second and succeeding copies
of identical adjacent input lines are not written.  Repeated lines in the input
will not be detected if they are not adjacent, so it may be necessary to sort
the files first.
```
This code is part of the challenges located here: 
[Coding Challenges](https://codingchallenges.fyi/challenges/challenge-uniq)

Compile with ```clang++ -std=c++17  main.cpp```
