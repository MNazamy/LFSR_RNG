# Linear Feedback Shift Register


## Overview

Modern cryptography is not only required to be computationally infeasible to break, but also **fast**.

Linear Feeback Shift Registers (or LFSR's) contain a set of bits flipped to '1' or '0'. They have a certain logical pattern to shift the pattern down, and produce an output.
This output is what will be sent out over a communication channel.

With some hard-wired logic, and multiple LFSR's in combination, one can create an extremely fast and simple LFSR.

----

The NIST Statistical test suite will look at the output of our LFSR-based random number generator and determine how 'random' it looks based on a variety of a statistical tests.

The source code for my RNG and NIST output are included in this repo
