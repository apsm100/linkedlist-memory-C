# Linked List Memory Simulator in C
Simulates OS memory with bases and nodes. Simulates merging of free blocks and compaction. 

# Output
```
---------MEMORY--------- 
Node 1: H (Hole), base = 0, limit = 1
Node 2: P78, base = 1, limit = 1
Node 3: H (Hole), base = 2, limit = 1
Node 4: H (Hole), base = 3, limit = 1
Node 5: H (Hole), base = 4, limit = 1
Node 6: P7, base = 5, limit = 6
Node 7: P2, base = 11, limit = 1
Node 8: P8, base = 12, limit = 16
Node 9: P12, base = 28, limit = 16
Node 10: H (Hole), base = 44, limit = 1
Node 11: P54, base = 45, limit = 16
Node 12: H (Hole), base = 61, limit = 1
Node 13: H (Hole), base = 62, limit = 1
Node 14: P3, base = 63, limit = 16
Node 15: H (Hole), base = 79, limit = 1
Node 16: H (Hole), base = 80, limit = 1
Node 17: H (Hole), base = 81, limit = 1
Node 18: H (Hole), base = 82, limit = 1
Node 19: H (Hole), base = 83, limit = 1
Node 20: H (Hole), base = 84, limit = 1
Node 21: P3, base = 85, limit = 16

---------AFTER MERGE FREE BLOCKS---------
Node 1: H (Hole), base = 0, limit = 1
Node 2: P78, base = 1, limit = 1
Node 3: H (Hole), base = 2, limit = 3
Node 4: P7, base = 5, limit = 6
Node 5: P2, base = 11, limit = 1
Node 6: P8, base = 12, limit = 16
Node 7: P12, base = 28, limit = 16
Node 8: H (Hole), base = 44, limit = 1
Node 9: P54, base = 45, limit = 16
Node 10: H (Hole), base = 61, limit = 2
Node 11: P3, base = 63, limit = 16
Node 12: H (Hole), base = 79, limit = 6
Node 13: P3, base = 85, limit = 16

---------AFTER COMPACTION---------
Node 1: P78, base = 0, limit = 1
Node 2: P7, base = 1, limit = 6
Node 3: P2, base = 7, limit = 1
Node 4: P8, base = 8, limit = 16
Node 5: P12, base = 24, limit = 16
Node 6: P54, base = 40, limit = 16
Node 7: P3, base = 56, limit = 16
Node 8: P3, base = 72, limit = 16
Node 9: H (Hole), base = 88, limit = 13

---------AFTER FREE---------


---------AFTER MERGE FREE BLOCKS---------


---------AFTER COMPACTION---------
```
