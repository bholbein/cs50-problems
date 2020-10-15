#!/usr/bin/env python3

# dependencies
import sys
import csv
import re

# constants
folder_db = 'databases/'
folder_seq = 'sequences/'


def main(argv):
    print(read_csv(get_input(argv)['file_csv']))
    print(read_txt(get_input(argv)['file_txt']))


def get_input(argv) -> dict:
    ### get and validate input from command line arguments ###
    file_regex = r'^[\w,\s-]+\.[A-Za-z]{3}$'
    if len(argv) != 2:
        return "Please specify 2 filenames."
    elif re.match(file_regex, argv[0]) and re.match(file_regex, argv[1]):
        return {'file_csv': folder_db + argv[0], 'file_txt': folder_seq + argv[1]}
    else:
        return "Please specify 2 filenames."


def read_csv(input_file: str) -> dict:
    ### read files into memory ###
    with open(input_file, newline='') as csvfile:
        for row in csv.DictReader(csvfile):
            return row


def read_txt(input_file: str) -> list:
    ### read txt file into memory ###
    with open(input_file, newline='') as txtfile:
        for row in csv.reader(txtfile):
            return row


if __name__ == "__main__":
    main(sys.argv[1:])
