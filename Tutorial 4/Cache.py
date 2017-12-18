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
        self.cache_directories = [[[False for _ in range(l)] for _ in range(k)] for _ in range(n)]
        self.tag_mask, self.set_mask, self.offset_mask = self.calculating_masks()
        self.set_shift = int(log2(l))
        self.tag_shift = int(log2(n) + self.set_shift)
        self.total_hits = 0
        self.total_misses = 0

    def calculating_masks(self):
        print("Calculating masks...")

        offset = int(log2(self.L))
        set_num = int(log2(self.N))
        tag = 27 - offset - set_num

        offset_mask = int((27 - offset) * '0' + offset * '1', 2)
        set_mask = int((27 - set_num) * '0' + set_num * '1' + offset * '0', 2)
        tag_mask = int(tag * '1' + (set_num + offset) * '0', 2)

        return tag_mask, set_mask, offset_mask

    def read_instruction_from_addresses(self, address):
        offset = (address & self.offset_mask)
        set_number = (address & self.set_mask) >> self.set_shift
        tag = (address & self.tag_mask) >> self.tag_shift

        if tag in self.cache_sets[set_number]:
            self.lru_queue[set_number].remove(tag)
            self.lru_queue[set_number].append(tag)
            self.total_hits += 1
            return
        else:
            try:
                new_tag = self.cache_sets[set_number].index(None)
            except ValueError:
                evicted_tag = self.lru_queue[set_number].popleft()
                new_tag = self.cache_sets[set_number].index(evicted_tag)
                print('evict_Tag: {}\nnew_tag: {}\ncache_set:{}'.format(evicted_tag, new_tag, self.cache_sets[set_number]))

            self.cache_sets[set_number][new_tag] = tag
            self.cache_directories[set_number][new_tag][offset] = True
            self.lru_queue[set_number].append(tag)
            self.total_misses += 1
            return

    def print_results(self):
        print('Total Number of Hits: {}'.format(self.total_hits))
        print('Total Number of Misses: {}'.format(self.total_misses))
        print('Total Hit Rate: {}%'.format(self.total_hits / (self.total_hits + self.total_misses) * 100))
        print('Total Miss Rate: {}%'.format(self.total_misses / (self.total_hits + self.total_misses) * 100))