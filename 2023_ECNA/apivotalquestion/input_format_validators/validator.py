#!/usr/bin/env python3
from sys import stdin
import sys
import re

integer = "(0|-?[1-9]\d*)"
max_allowed_value = 1000000
max_n = 1000000

line = stdin.readline()[:-1]
n, *arr = line.split(' ')
assert re.match(integer, n)

n = int(n)
assert 1 <= n and n <= max_n, "%d  not in [1, %d]" % (n, max_n)
assert len(arr) == n

for val in arr:
  assert re.match(integer, val)
  v = int(val)
  assert 1 <= v and v <= max_allowed_value, "%s  not in [1, %d]" % (val, max_allowed_value)


for line in stdin:
  assert len(line) == 0

# Nothing to report
sys.exit(42)
