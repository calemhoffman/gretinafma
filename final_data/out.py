#!/usr/bin/env python
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

from sklearn import preprocessing

import torch as torch
import torch.nn as nn
import torch.nn.functional as F
from torch.autograd import Variable
import torch.optim as optim

#look at data loaded
import matplotlib.pyplot as plt
import plotly.express as px

data_in = rnp.root2array("pyTreeAverageFatQ.root","pytree",
                         branches=['e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','ga','gid','glabel',
                                  'cre','ix','iy','iz'])
assert_equal(data_in.dtype.names, ('e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','ga','gid','glabel',
                                  'cre','ix','iy','iz'))
#print(data_in.dtype)
num_data_columns=19.0
#convert to pandas
df = pd.DataFrame(data=data_in)
#print(df)
x = df.values #returns a numpy array
min_max_scaler = preprocessing.MinMaxScaler(feature_range=(0,1))
x_scaled = min_max_scaler.fit_transform(x)
res_df = pd.DataFrame(x_scaled)
df_g1293 = df[(df['ge'] > 1285) & (df['ge'] < 1298)]
#print(df_g1293.size/num_data_columns)
#data to torch tensor
X = torch.from_numpy(res_df.values).float().to(torch.device('cpu'))
#Model D/K with AverageFatD_train data (mar31 9pm)
class Net(nn.Module):

    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(11, 40)
        self.relu1 = nn.ReLU()
        self.dout = nn.Dropout(0.2)
        self.fc2 = nn.Linear(40, 20)
        self.prelu = nn.PReLU(1)
        self.out = nn.Linear(20, 1)
        self.out_act = nn.Sigmoid()

    def forward(self, input_):
        a1 = self.fc1(input_)
        h1 = self.relu1(a1)
        dout = self.dout(h1)
        a2 = self.fc2(dout)
        h2 = self.prelu(a2)
        a3 = self.out(h2)
        y = self.out_act(a3)
        return y

net = Net()

save_path="./model_F.pt"
net = torch.load(save_path)
net.eval()

# Print model's state_dict & all the actual values
# print("Model's state_dict:")
# for param_tensor in net.state_dict():
#     print(param_tensor, "\t", net.state_dict()[param_tensor].size())
# print("Model's net.params:")
# for param in net.parameters():
#   print(param.data)
# print("Clean summary:")
# from torchvision import models
# from torchsummary import summary
# device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
# model = net.to(device)
# summary(model, (1, 1, 11))

evt_max_size=20000000
with torch.no_grad():
    result = net(X[0:evt_max_size,0:11])
    #result = torch.round(result)
print(torch.max(result))
print(torch.min(result))
torch.histc(result)
#print(result.data)
print(len(result))
df_F = pd.DataFrame(data=result.numpy())
#print(df_F)
df_F.columns = ["A"]
result_df = pd.concat([df, df_F], axis=1)
print(result_df)

# plt.figure(figsize=(4,2))
# fig = px.histogram(result_df, x="ge",nbins=8, color="glabel")
# fig.update_xaxes(range=[0, 1])
# fig.show()
