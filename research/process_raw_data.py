"""
Takes my raw samples from the serial monitor (multiple files ending in .data)
and formats them into a single JSON file.
"""

import os.path
import json
import sys
from os import listdir
from os.path import isfile, join

outfile = 'data.json'


def read_hex_data(file):
    data = []
    with open(file) as f:
        lines = f.readlines()

    count = 0
    for l in lines:
        count = count +1
        vals = l.split(',')
        for v in vals:
            # Filter out newlines and garbage
            if v.isalnum():
                int_val = int(v, base=16)
                data.append(int_val)
        if count > 100:
            break
    return data


def get_data_width(fname):
    """
    This is hokey. I know what I named these files, so I know that certain files
    have only 12-bit data. I use the file names to decide how to process the data.
    """
    width = 12;
    if 'motion' in fname or 'accel' in fname:
        width = 16
    return width


if __name__ == '__main__':
    data_dir = sys.argv[1]
    print('Scanning data directory: {}'.format(data_dir))

    data_dict = {}
    data_files = [f for f in listdir(data_dir) if f.endswith('.data') and isfile(join(data_dir, f))]

    for df in data_files:
        file_basename = os.path.basename(df).replace('.data', '')
        print('  - processing {}'.format(file_basename))

        values = read_hex_data(join(data_dir, df))
        file_json = {'bits': get_data_width(file_basename), 'samples': values}
        data_dict[file_basename] = file_json

    with open(outfile, 'w') as of:
        json.dump(data_dict, of)

