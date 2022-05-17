# Deadlock-DETECTER

## Basic command
-f filename specifies the path to the file describing requests.

-e is an optional parameter, which when provided requires your code to compute execution time. If this
option is not given, your code should identify presence or absence of deadlocks and which processes
need to be terminated to resolve deadlock(s).

-c identify it deadlock breaking is required. Once input -c, all process will be re-scheduled to avoid deadlock.

#Example:
Resourc.txt:

Time| Process id | Lock file 1| Lock file 2 |
--- | --- | --- | --- |
(1) |      0     |      1     |       2     | 
(2) |      1     |      2     |       3     |
(3) |      2     |      3     |       4     |
(4) |      3     |      4     |       1     |


Input: "./detect resources.txt -c"

Output: 
Time| Process id | Lock file 1| Lock file 2 |
--- | --- | --- | --- |
0 |      0     |      1     |       2     | 
0 |      2     |      3     |       4     |
1 |      1     |      2     |       3     |
1 |      3     |      4     |       1     |
Simulation time 2\n`
