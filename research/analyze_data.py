"""
This file takes the raw data in my custom JSON format (data.json) and outputs a series of
PNG files. This will create a LOT of files and takes a little time. Basically, for each
data set in the JSON file, it will make a plot of the histogram and the cumulative distribution
function (CDF) of the data - not just the data as given, but for every possible subset of that
data that can be created by lopping off one significant bit. So... for a data set with 16-bit
samples, it will generate 16 pairs of graphs.

NOTE: This script requires a directory at its same level called "out", to put all the PNG
files in.
"""

import json
import copy
import os.path

import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import kstest

# I've included my raw data as an example, but you can use your own. Just put it in the same
# JSON dictionary format. See process_raw_data.py for more info.
input_json_file = 'data.json'


def generate_text_histogram(seq):
    """
    Not currently used, but can be handy way to get a sneak peek at your data.
    Just print the resulting lines to console or to a text file.
    """
    values, counts = np.unique(seq, return_counts=True)
    mydict = {values[i]: counts[i] for i in range(len(values))}
    hist_lines = []
    for k in mydict.keys():
        line = '{:6d}: {:6d}  {}\n'.format(k, mydict[k], '-' * mydict[k])
        hist_lines.append(line)
    return hist_lines


def generate_graphs(samples, outfile, title, max_val):
    # Set up all the data we need to plot the graphs.
    keys, counts = np.unique(samples, return_counts=True)
    count, bins_count = np.histogram(samples, bins='auto')
    pdf = count / sum(count)
    cdf = np.cumsum(pdf)
    stat, p = kstest(cdf, 'uniform')

    # Clear out any previous data, set overall title
    plt.clf()
    plt.suptitle(title)

    # 1) Plot the histogram
    plt.subplot(211)
    plt.vlines(keys, 0, counts, lw=2)
    plt.grid(axis='y', alpha=0.75)
    plt.title('Histogram')
    plt.ylim(0, max(counts) * 1.06)

    # Create nice x-axis labels, using powers of 2
    plt.xlim(0, max_val)
    ticks = np.arange(0, max_val, max_val/8).tolist()
    ticks.append(max_val)
    plt.xticks(ticks)

    # 2) Plot the CDF
    plt.subplot(212)
    plt.title('Cumulative Distribution Function (CDF)'.format(p))
    color = 'green'
    if p <= 0.25:
        color = 'red'
    plt.text(max_val/8.0, 0.8, 'p={:.8f}'.format(p), color=color, fontsize=18)
    plt.xticks(ticks)
    plt.xlim(0, max_val)
    plt.plot(bins_count[1:], cdf)

    plt.subplots_adjust(hspace=0.4)

    # Create the PNG file
    plt.savefig(outfile)


def truncate_data(input_samples, bits):
    # Lop off "bits" most significant bits from each sample
    # Return a new array with the truncated samples.
    mask = (1 << bits) - 1
    truncated_samples = []
    for s in input_samples:
        truncated_samples.append(s & mask)
    return truncated_samples


def generate_plot_suite(name):
    """
    For a given data set - chosen using the 'name' as the index to the data.json map -
    loop through the data, truncating one bit and then plotting the results, and repeat.
    """
    bit_resolution = data[name]['bits']
    orig_samples = data[name]['samples']

    # Force the dataset to have the full range of possible values
    padded_data = pad_data(orig_samples, bit_resolution)

    for x in range(1, bit_resolution+1):
        trunc_samples = truncate_data(padded_data, x)
        max_value = (2**x)

        # NOTE! Be sure to have a directory here called "out"
        png_file = os.path.join('out', '{}-{}-bits.png'.format(name, x))
        title = '{}: {} samples, {} of {} bits'.format(name,
                                                       len(orig_samples),
                                                       x,
                                                       bit_resolution)
        generate_graphs(trunc_samples, png_file, title, max_value)


def pad_data(in_samples, bits):
    """
    The NumPy functions we're going to use don't know the true upper and
    lower bounds of the possible sample values. We have several data sets
    with highly-clustered results. So we're going to add two dummy samples
    at each end of the spectrum: zero and 2^bits-1. Given that our datasets
    have 10k samples, this shouldn't throw things off much.
    """
    padded_samples = copy.deepcopy(in_samples)
    padded_samples.append(0)
    padded_samples.append((2**bits)-1)
    return padded_samples


if __name__ == '__main__':
    with open(input_json_file) as df:
        data = json.load(df)

    for dataset in data:
        print("Processing dataset '{}' with {} samples".format(dataset, len(data[dataset]['samples'])))
        generate_plot_suite(dataset)