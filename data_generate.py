import pandas as pd
import numpy as np

import random
totNum = 100000
price = [random.randint(100, 800)*10 for i in range(totNum)]
x_diff_abs = [random.randint(0, 6) for i in range(totNum)]
y_diff_abs = [random.randint(0, 6) for i in range(totNum)]
transport = [random.randint(0, 3) for i in range(totNum)]
room_num = [random.randint(1, 4) for i in range(totNum)]

df = pd.DataFrame([price, room_num, transport, x_diff_abs, y_diff_abs]).T
df.columns = ["price", "room_num", "transport", "x_diff_abs", "y_diff_abs"]

def get_y(data):
    arr = list(data)
#     print(arr)
    y =  -0.1 * arr[0]/100 + 0.1 * arr[1] + 0.3 * arr[2] - 0.2 * arr[3] - 0.2 * arr[4] + random.randint(0, 5) / 3
    return y

y = np.array([get_y(df.iloc[i]) for i in range(len(df))])

ticks = [5, 15, 40, 75, 100]
percentile = [np.percentile(y, ticks[i]) for i in range(len(ticks))]

def get_score(x):
    for i in range(len(percentile)):
        if (percentile[i] >= x):
            return i+1
    
y = pd.Series(y).apply(get_score)

df['y'] = y
df.to_csv("data/data.csv")