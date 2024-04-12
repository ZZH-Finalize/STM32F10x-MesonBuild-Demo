#! env python
from argparse import ArgumentParser
import os
import regex

search_dirs = []
search_format:regex.Pattern = None

def process_args():
    global search_dirs, search_format

    parser = ArgumentParser('list_files', description='search file under dirs')
    parser.add_argument('dirs', help='search dirs', nargs='+', type=str)
    parser.add_argument('-f', '--format', help='search format (regex)', dest='format', type=str, required=True)

    parse_res = parser.parse_args()
    search_dirs.extend(parse_res.dirs)
    search_format = regex.compile(parse_res.format)

def list_files_by_format(path: str):

    for curdir, _, files in os.walk(path):
        for fn in files:
            if search_format.match(fn):
                print(os.path.join(curdir, fn))
            

if __name__ == '__main__':
    process_args()

    # print('search_format: ', search_format)
    # print('search_dirs: ', search_dirs)

    for dir in search_dirs:
        if os.path.isdir(dir):
            list_files_by_format(dir)
