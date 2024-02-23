#!/usr/bin/python3

import random

WORD_LEN_MAX = 20
WORDS_MAX = 1499

words = []
prefix = 'AAAA'
suffix = 'AAAA'
word_len = len(prefix) + 2 + len(suffix)
alphabet = [chr(i) for i in range(ord('A'), ord('Z') + 1)]
for ch_1 in alphabet:
    for ch_2 in alphabet:
        words.append(prefix + ch_1 + ch_2 + suffix)
while len(words) < WORDS_MAX:
    words.append(''.join([random.choice(alphabet) for _ in range(word_len)]))
print(len(words))
for word in words:
    print(word)

