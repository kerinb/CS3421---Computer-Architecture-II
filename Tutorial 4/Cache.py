#!/usr/bin/python3

from math import log2
from collections import deque


class Cache:
    def __init__(self, l, k, n):
        print("Initialising Cache...")
        self.L = l
        self.K = k
        self.N = n
        self.lru_queue = [deque() for _ in range(n)]
        self.cache_sets = [[None for _ in range(k)] for _ in range(n)]
        self.directories = [[[False for _ in range(l)] for _ in range(k)] for _ in range(n)]
        self.tag_mask, self.set_mask, self.offset_mask = self.calculating_masks()
        self.set_shift = int(log2(l))
        self.tag_shift = int(log2(n) + self.set_shift)
        self.hits = 0
        self.misses = 0

    def calculating_masks(self):
        print("Calculating masks...")
        offset = int(log2(self.L))
        set_num = int(log2(self.N))
        tag = 27 - offset - set_num

        offset_mask = int((27 - offset) * '0' + offset * '1', 2)
        set_mask = int((27 - set_num) * '0' + set_num * '1' + offset * '0', 2)
        tag_mask = int(tag * '1' + (set_num + offset) * '0', 2)

        return tag_mask, set_mask, offset_mask

    def read_instruction(self, address):
        offset = (address & self.offset_mask)
        set_num = (address & self.set_mask) >> self.set_shift
        tag = (address & self.tag_mask) >> self.tag_shift

        if tag not in self.cache_sets[set_num]:
            self.read_tag_miss(tag, set_num, offset)
            return

        tag_index = self.cache_sets[set_num].index(tag)
        if not self.directories[set_num][tag_index][offset]:
            self.read_offset_miss(set_num, tag_index, offset)
            return

        self.lru_queue[set_num].remove(tag)
        self.lru_queue[set_num].append(tag)
        self.hits += 1

    def read_tag_miss(self, tag, set_num, offset):
        try:
            new_tag_index = self.cache_sets[set_num].index(None)
        except ValueError:
            evicted_tag = self.lru_queue[set_num].popleft()
            evicted_tag_index = self.cache_sets[set_num].index(evicted_tag)
            new_tag_index = evicted_tag_index
        self.cache_sets[set_num][new_tag_index] = tag
        self.directories[set_num][new_tag_index][offset] = True
        self.lru_queue[set_num].append(tag)
        self.misses += 1

    def read_offset_miss(self, set_num, tag_index, offset):
        self.directories[set_num][tag_index][offset] = True
        self.misses += 1

    def print_results(self):
        print('Number of Hits: {}'.format(self.hits))
        print('Number of Misses: {}'.format(self.misses))
        print('Total Hit Rate: {}%'.format(self.hits / (self.hits + self.misses) * 100))
