#!/usr/bin/env python3

# dependencies
import sys
import csv
import re


def main(argv):
    check = get_input(argv)
    data = read_csv(check['file_csv'])
    sequence = read_txt(check['file_txt'])
    if type(check) == dict:
        print(cal_match(data, check_sequence(data, sequence[0])))
    else:
        print("Usage: python dna.py data.csv sequence.txt")


def get_input(argv) -> dict:
    ### get and validate input from command line arguments ###
    file_regex = r'^.*\/[\w,\s-]+\.[A-Za-z]{3}$'
    if len(argv) != 2:
        return 0
    elif re.match(file_regex, argv[0]) and re.match(file_regex, argv[1]):
        return {'file_csv': argv[0], 'file_txt': argv[1]}
    else:
        return 1


def read_csv(input_file: str) -> list:
    ### read csv file into memory ###
    output = []
    with open(input_file, mode='r') as csvfile:
        for row in csv.DictReader(csvfile):
            output.append(row)
    return output


def read_txt(input_file: str) -> list:
    ### read txt file into memory ###
    with open(input_file, mode='r') as txtfile:
        for row in csv.reader(txtfile):
            return row


def check_sequence(data: list, sequence: str) -> dict:
    ### check the dna sequence based on STRs ###
    keys = set()
    count = {}
    for entry in data:
        for k in entry.keys():
            keys.add(k)
    for item in keys:
        #define several helper variable for search algorithm
        start = counter = iteration = max_counter = 0
        sequence_temp = sequence
        while item in sequence_temp:
            start = sequence_temp.index(item)
            if (start == 0) or (iteration == 0):
                counter += 1
                #check if squence is longest until this point
                if counter > max_counter:
                    max_counter = counter
            else:
                #reset counter
                counter = 1
            sequence_temp = sequence_temp[start + len(item):]
            iteration += 1
        count[item] = max_counter
    return count


def cal_match(data: list, sequence_count: dict) -> str:
    ### match data with sequence count ###

    for list_item in data:
        match_counter = 0
        for k, v in list_item.items():
            #print(f"value: {k}:{v}, sequence: {k}:{sequence_count[k]}")
            if k == 'name':
                pass
            elif int(v) == sequence_count[k]:
                match_counter += 1
        if match_counter == len(sequence_count) - 1:
            return list_item['name']
    return "No match"


if __name__ == "__main__":
    main(sys.argv[1:])
