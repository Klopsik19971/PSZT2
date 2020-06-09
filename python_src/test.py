from sklearn.ensemble import GradientBoostingRegressor
import numpy as np
import pandas as pd
import pickle
import sys
from numpy import loadtxt
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
from sklearn.datasets import load_boston
from sklearn.metrics import mean_absolute_error
from sklearn.metrics import max_error


if len(sys.argv) < 1 or  len(sys.argv) > 3:
    sys.exit("You must provide maximum 3 arguments, that is max amount of decission trees and learning rate Exit.")

def is_intstring(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

if len(sys.argv) == 3:
    try:
        float(sys.argv[2])
    except ValueError:
        sys.exit("Learning rate must be a number. Exit.")
    if float(sys.argv[2]) < 0 or float(sys.argv[2]) > 1:
        sys.exit("Learning rate must be from 0 to 1. Exit.")
    

if len(sys.argv) >= 2:
    if not is_intstring(sys.argv[1]):
        sys.exit("Number of decision trees must be integer. Exit.")
    if int(sys.argv[1]) < 0:
        sys.exit("Number of decision trees must be more than 0. Exit.")
    
boston_train = loadtxt('../data/boston_python.csv', delimiter=";")
boston_test = loadtxt('../data/tests_python.csv', delimiter=";")

X_train = boston_train[:,0:13]
y_train = boston_train[:,13]

X_test = boston_test[:,0:13]
y_test = boston_test[:,13]

if len(sys.argv) < 2:
    regressor = GradientBoostingRegressor(
    max_depth=13,
    n_estimators=10,
    learning_rate=0.5 
)

if len(sys.argv) == 2:
    regressor = GradientBoostingRegressor(
    max_depth=13,
    n_estimators=int(sys.argv[1]),
    learning_rate=0.5 
)

if len(sys.argv) == 3:
    regressor = GradientBoostingRegressor(
    max_depth=13,
    n_estimators=int(sys.argv[1]),
    learning_rate=float(sys.argv[2]) 
)

regressor.fit(X_train, y_train)

y_pred = regressor.predict(X_test)
print(mean_absolute_error(y_test, y_pred))
print(max_error(y_test, y_pred))
