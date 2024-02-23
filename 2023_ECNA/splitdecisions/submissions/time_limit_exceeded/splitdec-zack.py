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
for let in range(1,MAXLEN+1):
    for fl in range(0,let-1):
        for w in words[let]:
            pat = w[:fl]+'[^]'+w[fl]+'][^'+w[fl+1]+']'+w[fl+2:]
            cpat = re.compile(pat)
            matches = []
            for w2 in words[let]:
                if cpat.match(w2) and w < w2:
                    # using < rather than != to avoid double-count
                    #print(w,w2)
                    # now we have a set of possible clues
                    # for each clue, what words match the first option
                    match1pat = '.'*fl + w[fl:fl+2] + '.'*(len(w)-fl-2)
                    c1mp = re.compile(match1pat)
                    fail = False
                    for m1w in words[let]:
                        if c1mp.match(m1w) and m1w != w:
                            # this is a match for word w
                            # what would it be with the w2 letters in it?
                            m2w = m1w[:fl]+w2[fl:fl+2]+m1w[fl+2:]
                            #print(m1w,m2w)
                            if m2w in words[let]:
                                #print(w,w2,'fail',m1w,m2w)
                                fail = True
                                break
                    if not fail:
                        numclues += 1

print(numclues)


