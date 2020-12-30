#!/usr/bin/env python
# coding: utf-8
import ROOT
from sys import exit
import numpy as np
from numpy.testing import assert_array_equal
from nose.tools import (raises, assert_raises, assert_true,
                        assert_equal, assert_almost_equal)
import root_numpy as rnp
import pandas as pd
from pandas.plotting import scatter_matrix
ROOT.ROOT.EnableImplicitMT()
from sklearn import preprocessing, model_selection, feature_selection, ensemble, linear_model, metrics, decomposition
import torch as torch
import torch.nn as nn
import torch.nn.functional as F
from torch.autograd import Variable
import torch.optim as optim
import matplotlib.pyplot as plt
import plotly.express as px
import seaborn as sns
sns.set(font_scale=0.5)
#pull raw training data #clean up
df_orig = pd.read_csv('train_out.csv')
min_max_scaler = preprocessing.MinMaxScaler(feature_range=(0,1))
df = pd.DataFrame(min_max_scaler.fit_transform(df_orig.drop(["id"], axis=1).values))
df = df.rename(columns={0:'e0',1:'e1',2:'e2',3:'e3',4:'e4',5:'e5',6:'e6'})
df = df.rename(columns={7:'x',8:'m',9:'dt',10:'gmult',11:'ge',12:'gid',13:'glabel'})
#df = df.drop(["ge","glabel"], axis=1)
print(df_orig.head()) #original data
print(df.head()) #scaled

##search for top corr input params
corr_matrix = df.copy()
corr_matrix = corr_matrix.corr(method="pearson")
sns.heatmap(corr_matrix, vmin=-1., vmax=1.,
annot=True,fmt='.2f',cmap="YlGnBu",cbar=True,linewidths=0.5)
plt.title("pearson correlation")
plt.savefig("output.png")

X = df.drop(["ge","glabel","gid"], axis=1).values
y = df["gid"].values
feature_names = df.drop(["ge","glabel","gid"], axis=1).columns

## Anova
selector = feature_selection.SelectKBest(score_func=
feature_selection.f_classif, k=10).fit(X,y)
anova_selected_features = feature_names[selector.get_support()]
## Lasso regularization
selector = feature_selection.SelectFromModel(estimator=linear_model.LogisticRegression(C=1, penalty="l1",
solver='liblinear'), max_features=10).fit(X,y)
lasso_selected_features = feature_names[selector.get_support()]
## Plot
print(anova_selected_features)
print(lasso_selected_features)

## Importance
model = ensemble.RandomForestClassifier(n_estimators=100,
criterion="entropy", random_state=0)
model.fit(X,y)
importances = model.feature_importances_
print(importances)

# data to csv stuff
# data_in = rnp.root2array("pyTreeAverageFatF_train.root","pytree",
#                          branches=['e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','gid','glabel'])
# assert_equal(data_in.dtype.names, ('e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','gid','glabel'))
# df = pd.DataFrame(data=data_in)
# x = df.values #returns a numpy array
# min_max_scaler = preprocessing.MinMaxScaler(feature_range=(0,1))
# df_scaled = pd.DataFrame(min_max_scaler.fit_transform(df.values))
# df.to_csv('train_out.csv')
