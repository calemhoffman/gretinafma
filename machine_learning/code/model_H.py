#!/usr/bin/env python
# coding: utf-8

# In[ ]:


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

data_in = rnp.root2array("../data/pyTreeAverageFatH_train.root","pytree",
                         branches=['e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','gid','glabel'])
assert_equal(data_in.dtype.names, ('e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','gid','glabel'))

#convert to pandas
df = pd.DataFrame(data=data_in)
x = df.values #returns a numpy array
min_max_scaler = preprocessing.MinMaxScaler(feature_range=(0,1))
x_scaled = min_max_scaler.fit_transform(x)
res_df = pd.DataFrame(x_scaled)
df_g1293 = df[(df['ge'] > 1280) & (df['ge'] < 1305)]
g1293_tot = df_g1293.size/14
#print(g1293_tot)
#print(df)
#print(res_df)

#data to torch tensor
X = torch.from_numpy(res_df.values).float().to(torch.device('cpu'))
print(X.shape)
#print(X)


# In[ ]:


#look at data loaded
import matplotlib.pyplot as plt
import plotly.express as px

plt.figure(figsize=(5,2))
fig = px.histogram(df, x="glabel",nbins=8, color="glabel")
fig.update_xaxes(range=[-1, 5])
fig.show()

fig = px.histogram(df, x="ge",nbins=3400, color="glabel")
fig.update_xaxes(range=[100, 3500])
fig.show()

fig = px.scatter(df, x="e4",y="e0",color="glabel",opacity=0.5)
fig.show()


# In[ ]:


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
opt = optim.Adam(net.parameters(), lr=0.001, betas=(0.9, 0.999))
criterion = nn.BCELoss()


# In[ ]:


def train_epoch(model, opt, criterion, batch_size=500):
    model.train()
    losses = []
    correct = 0
    total = 0
    for beg_i in range(0, X.size(0), batch_size):
        x_batch = X[beg_i:beg_i + batch_size, 0:11]
        #print(x_batch)
        y_batch = X[beg_i:beg_i + batch_size, 12:13]
        #print(y_batch.shape)
        x_batch = Variable(x_batch)
        y_batch = Variable(y_batch)
        
        opt.zero_grad()
        # (1) Forward
        y_hat = net(x_batch)
        #
        # (2) Percent test on batch
        with torch.no_grad():
            y_round = torch.round(y_hat)
            total += y_batch.size(0)
            correct += (y_round == y_batch).sum().item()
            
                
        # (3) Compute diff
        loss = criterion(y_hat, y_batch)
        
        # (3) Compute gradients
        loss.backward()
        
        # (4) update weights
        opt.step()        
        losses.append(loss.data.numpy())
    
    print('Accuracy of the network on the current batch of data: %f %%' % (
        100 * correct / total))
    return losses


# In[ ]:


e_losses = []
num_epochs = 200
for e in range(num_epochs):
    e_losses += train_epoch(net, opt, criterion)


# In[ ]:


plt.plot(e_losses)
#uncomment below for real python script save
torch.save(net, "./model_saves/model_H.pt")


# In[ ]:


net.eval()
with torch.no_grad():
    result = net(X[0:1000000,0:11])


# In[ ]:


#plt.plot(result.data)
print(torch.max(result))
print(torch.min(result))
torch.histc(result)
df_F = pd.DataFrame(data=result.numpy())
df_F.columns = ["A"]
fig = px.histogram(df_F,x="A",nbins=100)
fig.update_xaxes(range=[0.0,1.0])
fig.show()


# In[ ]:


#pull out events from model decision
result_df = pd.concat([df, df_F], axis=1)
#dump to csv
result_df.to_csv("output/pyTreeAverageFatH_train.csv",sep=" ",header=False)


# In[ ]:


#print(result_df)
s38_low=0.8
cl38_high=0.3
s38 = result_df[(result_df['A'] > s38_low) & (result_df['A'] < 1)]
cl38 = result_df[(result_df['A'] < cl38_high) & (result_df['A'] < 1)]
misc = result_df[(result_df['A'] > cl38_high) & (result_df['A'] < s38_low)]

g1293a = result_df[(result_df['A'] > s38_low) & (result_df['ge'] >1280) 
                   & (result_df['ge'] < 1300)]
g1293_s38 = g1293a.size/15
g1293b = result_df[(result_df['A'] < cl38_high) & (result_df['ge'] >1280) 
                   & (result_df['ge'] < 1300)]
g1293_cl38 = g1293b.size/15
g1293c = result_df[(result_df['A'] > cl38_high) & (result_df['A'] < s38_low)
                   & (result_df['ge'] >1280) & (result_df['ge'] < 1300)]
g1293_misc = g1293c.size/15

#print(s38.size/10)
print("1293 gamma rays for 38S: %d/%d*100.0 = %2.1f %%" 
      % (g1293_s38,g1293_tot,g1293_s38/g1293_tot*100.0))
print("1293 gamma rays for 38Cl: %d/%d*100.0 = %2.1f %%" 
      % (g1293_cl38,g1293_tot,g1293_cl38/g1293_tot*100.0))
print("1293 gamma rays for Misc: %d/%d*100.0 = %2.1f %%" 
      % (g1293_misc,g1293_tot,g1293_misc/g1293_tot*100.0))
print("Sum 1293 gamma rays: %d" % (g1293_s38+g1293_cl38+g1293_misc))


plt.figure(figsize=(10,4))
fig = px.histogram(s38, x="ge", nbins=3400, color = "glabel")
fig.update_xaxes(range=[100, 3500])
fig.show()

plt.figure(figsize=(10,4))
fig = px.histogram(cl38, x="ge", nbins=3400, color = "glabel")
fig.update_xaxes(range=[100, 3500])
fig.show()

plt.figure(figsize=(10,4))
fig = px.histogram(misc, x="ge", nbins=3400, color = "glabel")
fig.update_xaxes(range=[100, 3500])
fig.show()


# In[ ]:




