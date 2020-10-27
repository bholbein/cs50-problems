#!/usr/bin/env python3

import sys
import sqlite3
import csv


def main(argv):
    if len(argv) != 2:
        print("Usage: python import.py file.csv")
    else:
        try:
            connection = sqlite3.connect("students.db")
        except:
            print("Could not connect to database.")
            return 1
        try:
            csv_file = open(argv[1])
        except:
            print("Could not open file.")
            return 2
        rows = list(map(explode_name, csv.reader(csv_file)))
        cursor = connection.cursor()
        cursor.execute("DELETE FROM students")
        cursor.executemany(
            "INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", rows[1:])
        connection.commit()
        connection.close()


def explode_name(entry: list) -> list:
    # explodes name in first-, middle- and last name
    new_list = []
    name = entry[0].split(" ", 2)
    # ToDo solve with for loop and short if statement
    new_list.append(name[0])
    if len(name) == 2:
        new_list.append(None)
        new_list.append(name[1])
    elif len(name) == 3:
        new_list.append(name[1])
        new_list.append(name[2])
    else:
        pass
    new_list.append(entry[1])
    new_list.append(entry[2])
    return new_list


if __name__ == "__main__":
    main(sys.argv)
