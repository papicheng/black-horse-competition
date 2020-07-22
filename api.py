#from sklearn.externals import joblib
import joblib
import pandas as pd
import numpy as np

#def score(arr):
def score(a1, b1, c1, d1, e1):
    arr = [[a1, b1, c1, d1, e1]]
    #load model
    model = joblib.load('./saved_model/model.pkl')
    df = pd.DataFrame(arr)
    y_predict = model.predict(df)
    #return list(y_predict)
    
    try:
        return y_predict[0]
    except:
        return 0
a1, b1, c1, d1, e1 = 1000, 2, 1, 0, 3
print(score(a1, b1, c1, d1, e1))
#arr = [[1000, 2, 1, 0, 3], [1000, 2, 1, 0, 4]]
#print(score(arr))