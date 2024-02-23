#!/bin/python3
import re,sys

'''
Code used if we are only interested in a given pattern
basepat = None
setfl = None
if len(sys.argv) > 1:
    basepat = re.compile(sys.argv[1])
if len(sys.argv) > 2:
    setfl = int(sys.argv[2])
'''
MAXLEN = 25

# load wordlist
words = [set() for _ in range(MAXLEN+1)]
numwds = int(input())
for _ in range(numwds):
    w = input().strip().lower()
    words[len(w)].add(w)

# change this loop depending on problem version
numclues = 0
for let in range(3,MAXLEN+1):
    for w in words[let]:
        for w2 in words[let]:
            if w < w2:
                for fl in range(0,let-1):
                    if w[fl:fl+2] in w2:
                        # what matches ..w[fl]w[fl+1]..
                        fail = False
                        for m1w in words[let]:
                            if m1w != w and m1w[fl] == w[fl] and m1w[fl+1] == w[fl+1]:
                                # this also matches w clue, what would match w2 clue?
                                m2w = m1w[:fl]+w2[fl:fl+2]+m1w[fl+2:]
                                if m2w in words[let]:
                                    fail = True
                                    break
                        if not fail:
                            numclues += 1

print(numclues)


