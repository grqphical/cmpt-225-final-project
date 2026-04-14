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

df = pd.read_csv("data.csv")

df.set_index("Name", inplace=True)

ax = df.plot(kind="bar", figsize=(10, 6))

plt.title("Skip Lists vs AVL Trees")
plt.xlabel("Test Cases")
plt.ylabel("Time (ms)")
plt.xticks(rotation=0)
plt.legend(title="Category")

plt.tight_layout()
plt.show()
