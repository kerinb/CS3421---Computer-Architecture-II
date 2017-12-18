import subprocess


def analyse_the_trace(trace_addresses, instruction_cache, data_cache):
    access_mask = int('11100000000000000000000000000000', 2)
    access_shift = 29
    address_mask = int('00000000011111111111111111111111', 2)

    for memory_address in trace_addresses:
        access_type = (memory_address & access_mask) >> access_shift
        address = memory_address & address_mask
        if access_type == 4:
            instruction_cache.read_instruction_from_addresses(address)
        elif access_type == 6:
            data_cache.read_instruction_from_addresses(address)
        else:
            pass


def read_trace_from_file():
    args = ['xxd', '-b', 'gcc1.trace']

    raw_trace = subprocess.run(
        args=args,
        stdout=subprocess.PIPE
    ).stdout.decode().split('\n')
    print("read in data from 'gcc1.trace'\n")
    split_trace = [row.split(' ')[1: 7] for row in raw_trace if row != '']
    flat_trace = ''
    for s in [item for sublist in split_trace for item in sublist]:
        flat_trace += s

    # Separate into 32 bit segments, leaving out every 2nd 32 bit segment
    trace = []
    for i in range(0, len(flat_trace), 64):
        trace.append(int(flat_trace[i:i + 32], 2))
    print("returning trace to use...")
    return trace