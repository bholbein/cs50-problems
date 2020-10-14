#!/usr/bin/env python3

import re


def main():
    print(grade(calc_coli_index(**calc_averages(**analyze_text(get_input())))))


def get_input() -> str:
    """Return string as user input"""
    while True:
        try:
            text = input("Your text: ")
        except ValueError:
            continue
        break
    return text


def calc_coli_index(L: float, S: float) -> float:
    """Calculate the Coleman-Liau Index for Readability"""
    return 0.0588 * L - 0.296 * S - 15.8


def analyze_text(text: str) -> dict:
    """
    Counts number of letters, words and sentences in a text.
    """
    letter_count = sentence_count = 0
    word_count = 1
    for letter in text:
        if re.match(r'[a-z]', letter, re.IGNORECASE):
            letter_count += 1
        elif letter == " ":
            word_count += 1
        elif re.match((r'\.|\!|\?'), letter):
            sentence_count = sentence_count + 1
    return {'letters': letter_count,
            'words': word_count, 'sentences': sentence_count}


def calc_averages(letters: int, words: int, sentences: int) -> dict:
    """
    Calculates L as avg. number of letters per 100 words.
    Calculates S as avg. number of sentences per 100 words
    """
    l = s = 0
    l = 100 * letters / words
    s = 100 * sentences / words
    return {'L': l, 'S': s}


def grade(coli_index: float) -> str:
    if coli_index <= 0:
        return "Before Grade 1"
    elif coli_index >= 16:
        return "Grade 16+"
    else:
        return f"Grade {round(coli_index)}"


if __name__ == "__main__":
    main()