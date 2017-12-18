from time import time
import Cache as cache
import CacheFunctions as cacheFunctions


def print_final_results(time_taken, instruction_cache, data_cache):
    print('Execution time: {}ms'.format(time_taken * 1000))
    print("---Instruction Cache---")
    instruction_cache.print_results()
    print('---Data Cache---')
    data_cache.print_results()


def main():
    instruction_cache = cache.Cache(16, 1, 1024)
    data_cache = cache.Cache(16, 8, 256)

    trace_addresses = cacheFunctions.read_trace_from_file()

    print("Starting timer now")
    start = time()
    cacheFunctions.analyse_the_trace(trace_addresses, instruction_cache, data_cache)
    end = time()
    print("Timer ended..")

    time_taken = end - start
    print_final_results(time_taken, instruction_cache, data_cache)


if __name__ == '__main__':
    main()
