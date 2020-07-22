import pandas as pd
import numpy as np

df = pd.read_csv("data/train_data.csv", encoding='gbk')

df['x_diff'] = df['x坐标'] - df['用户:x坐标']
df['y_diff'] = df['y坐标'] - df['用户:y坐标']

df['transport'] = df['交通']
df['room_num'] = df['居室数量']
df['price'] = df['价格']

X = df[['price', 'room_num', 'transport', 'x_diff', 'y_diff']]

y = df['评分优先级 满分5']

from sklearn import tree
clf = tree.DecisionTreeClassifier(max_depth=4)
clf = clf.fit(X, y)
from sklearn.externals import joblib
#save model
joblib.dump(clf, 'saved_model/model.pkl')

