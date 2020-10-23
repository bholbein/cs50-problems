#!/usr/bin/env python3
import sys
import sqlite3


def main(argv):
    if len(argv) != 2:
        print("Usage: python roster.py house")
    else:
        try:
            connection = sqlite3.connect("students.db")
        except:
            print("Could not connect to database.")
            return 1
        cursor = connection.cursor()
        result = cursor.execute(
            "SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", (argv[1],))
        for item in result:
            if item[1] == None:
                print(f"{item[0]} {item[2]}, born {item[3]}")
            else:
                print(f"{item[0]} {item[1]} {item[2]}, born {item[3]}")


if __name__ == "__main__":
    main(sys.argv)
