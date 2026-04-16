"""
Expects data in the form:

Name,Skip List,AVL Tree
Random Insertion,1000,1500
Ordered Insertion,1200,800
Searching,400,600
Removal,380,240
"""

import pandas as pd
import matplotlib.pyplot as plt
import argparse

parser = argparse.ArgumentParser(usage="Generates charts from CSV files")
parser.add_argument("--title", "-t", required=True)
parser.add_argument("--output", "-o", default="output.png")
parser.add_argument("file")

args = parser.parse_args()

df = pd.read_csv(args.file)

df.set_index("Name", inplace=True)

ax = df.plot(kind="bar", figsize=(10, 6))

plt.title(args.title)
plt.xlabel("Test Cases")
plt.ylabel("Time (ms)")
plt.xticks(rotation=0)
plt.legend(title="Data Structure")

plt.tight_layout()
plt.savefig(args.output)
print(f"Saved chart to {args.output}")
