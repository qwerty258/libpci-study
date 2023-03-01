#!/usr/bin/env python3

import sys
import operator
import json


def main():
    f = open(sys.argv[1])

    data = json.load(f)

    sorted_data = sorted(data, key=operator.itemgetter("DBDF"))

    print(json.dumps(sorted_data, indent=4))

    f.close()


if __name__ == "__main__":
    main()
