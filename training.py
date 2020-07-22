import numpy as np
import pandas as pd

data = pd.read_csv("data/data.csv", index_col='Unnamed: 0')

tot_amount =  int(data.size / len(data.columns))
training_amount = int(tot_amount*0.7)

training_data = data[:training_amount]
test_data = data[training_amount:]

X_training = training_data[['price', 'room_num', 'transport', 'x_diff_abs', 'y_diff_abs']]
y_training = training_data['y']

X_test = test_data[['price', 'room_num', 'transport', 'x_diff_abs', 'y_diff_abs']]
y_test = test_data['y']


from sklearn import tree
clf = tree.DecisionTreeClassifier(max_depth=12)
clf = clf.fit(X_training, y_training)

y_predict = clf.predict(X_test)
print(sum(y_predict == y_test) / len(y_test))


from sklearn.externals import joblib
#save model
joblib.dump(clf, 'saved_model/model.pkl')