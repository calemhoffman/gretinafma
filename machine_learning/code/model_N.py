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

data_in = rnp.root2array("../data/pyTreeAverageSkinN_train.root","pytree",
                         branches=['e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','gid','glabel'])
assert_equal(data_in.dtype.names, ('e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','gid','glabel'))

#convert to pandas
df = pd.DataFrame(data=data_in)
ncol=df.columns.size
x = df.values #returns a numpy array
min_max_scaler = preprocessing.MinMaxScaler(feature_range=(0,1))
x_scaled = min_max_scaler.fit_transform(x)
res_df = pd.DataFrame(x_scaled)
df_g1293 = df[(df['ge'] > 1280) & (df['ge'] < 1305)]
g1293_tot = df_g1293.size/ncol
#print(g1293_tot)
#print(df)
#print(res_df)

#data to torch tensor
X = torch.from_numpy(res_df.values).float().to(torch.device('cpu'))
print(X.shape)
print(len(X))
#print(X)


# In[ ]:


#look at data loaded
import matplotlib.pyplot as plt
import plotly.express as px

plt.figure(figsize=(3,1))
fig = px.histogram(df, x="glabel",nbins=8, color="glabel")
fig.update_xaxes(range=[-1, 5])
fig.show()
plt.figure(figsize=(3,1))
fig = px.histogram(df, x="gid",nbins=8, color="gid")
fig.update_xaxes(range=[-1, 5])
fig.show()

fig = px.histogram(df, x="ge",nbins=3400, color="glabel")
fig.update_xaxes(range=[100, 3500])
fig.show()

#fig = px.scatter(df, x="e4",y="e0",color="glabel",opacity=0.5)
#fig.show()


# In[ ]:


#epochs/batch is only diff from D .
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


def train_epoch(model, opt, criterion, epoch, batch_size):
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

    print('Accuracy of the network on the current batch of data (epoch %d): %f %%' % (
        epoch,100 * correct / total))
    return losses


# In[ ]:


e_losses = []
num_epochs = 2000
batches = 5000
for e in range(num_epochs):
    e_losses += train_epoch(net, opt, criterion, e, batches)


# In[ ]:


plt.plot(e_losses)
#uncomment below for real python script save
torch.save(net, "./model_saves/model_N.pt")


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
result_df = pd.concat([df, df_F], axis=1)
ncol_result=result_df.columns.size
fig = px.histogram(df_F,x="A",nbins=100)
fig.update_xaxes(range=[0.0,1.0])
fig.show()


# In[ ]:


from sklearn import metrics
from sklearn.metrics import ConfusionMatrixDisplay
#fpr, tpr, thresholds = metrics.roc_curve(y, scores, pos_label=2)
#y = true labels so for me it is gid [0,1] so no pos_label needed
#scores are output from model
scores=result_df['A'].values
y=result_df['gid'].values
#print(y)
#print(scores)
fpr, tpr, thresholds = metrics.roc_curve(y, scores)
roc_auc = metrics.auc(fpr, tpr)
#metrics.roc_auc_score(y, scores)

#metrics that need binary so using >0.5
scores_round=np.round_(scores,0)
print(metrics.classification_report(y, scores_round))
confusion_matrix=metrics.confusion_matrix(y, scores_round)
confusion_matrix_norm=metrics.confusion_matrix(y, scores_round,normalize='true')
print(confusion_matrix)
print(confusion_matrix_norm)
display_labels=['0','1']
disp = ConfusionMatrixDisplay(confusion_matrix_norm, display_labels)
disp = disp.plot()
plt.show()

lw = 2
plt.plot(fpr, tpr, color='darkorange',
         lw=lw, label='ROC curve (area = %0.2f)' % roc_auc)
plt.plot([0, 1], [0, 1], color='navy', lw=lw, linestyle='--')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('Receiver operating characteristic example')
plt.legend(loc="lower right")
plt.show()


# In[ ]:


#dump to csv
#result_df.to_csv("output/pyTreeAverageFatI_train.csv",sep=" ",header=False)


# In[ ]:


#print("cut tot% g1293 % g1535 % g383 % g639 % g1190 % g2044 % g2279 % g2978 % g3142 % g1848 %")
total = []
ml_return = []
g1293 = [] #1280-1300
g1535 = [] #1525-1545
g848 = [] #840-860
g383 = [] #380-390
g292 = [] #285-298
g639 = [] # 630-645
g1190 = [] #1180-1200
g2044 = [] #2035-2055
g2279 = [] #2260-2290
g2978 = [] #2960-2990
g3142 = [] #3130-3160
g1848 = [] #1835-1855
g1430 = [] #1420-1440
g2378 = [] #2370-2385
g136 = [] #130-145
g170 = [] #165-175
g1293t = [] #1280-1300
g1535t = [] #1525-1545
g848t = [] #840-860
g383t = [] #380-390
g292t = [] #285-298
g639t = [] # 630-645
g1190t = [] #1180-1200
g2044t = [] #2035-2055
g2279t = [] #2260-2290
g2978t = [] #2960-2990
g3142t = [] #3130-3160
g1848t = [] #1835-1855
g1430t = [] #1420-1440
g2378t = [] #2370-2385
g136t = [] #130-145
g170t = [] #165-175
ratio1 = []
ratio2 = []
ratio3 = []
for cut_val in range(50):
    cut_low=cut_val*0.02
    ml_return.append(cut_low)
    #total count stuff
    total_counts = result_df[(result_df['A'] > 0)]
    total_counts_frac = result_df[(result_df['A'] > cut_low)]
    if (total_counts.size>0):
        total.append(total_counts_frac.size/total_counts.size)
    #g3142 stuff
    g3142_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >3130)
                   & (result_df['ge'] < 3160) ]
    g3142_tot = result_df[(result_df['ge'] >3130)
                   & (result_df['ge'] < 3160) ]
    if (g3142_tot.size>0):
        g3142.append(g3142_counts.size/g3142_tot.size)
    g3142t.append(g3142_counts.size/15)
#g848 stuff
    g848_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >845)
                   & (result_df['ge'] < 855) ]
    g848_tot = result_df[(result_df['ge'] >845)
                   & (result_df['ge'] < 855) ]
    if (g848_tot.size>0):
        g848.append(g848_counts.size/g848_tot.size)
    g848t.append(g848_counts.size/15)

    #g2978 stuff
    g2978_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >2960)
                   & (result_df['ge'] < 2990) ]
    g2978_tot = result_df[(result_df['ge'] >2960)
                   & (result_df['ge'] < 2990) ]
    if (g2978_tot.size>0):
        g2978.append(g2978_counts.size/g2978_tot.size)
    g2978t.append(g2978_counts.size/15)
    #g2279 stuff
    g2279_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >2260)
                   & (result_df['ge'] < 2290) ]
    g2279_tot = result_df[(result_df['ge'] >2260)
                   & (result_df['ge'] < 2290) ]
    if (g2279_tot.size>0):
        g2279.append(g2279_counts.size/g2279_tot.size)
    g2279t.append(g2279_counts.size/15)
    #g2044 stuff
    g2044_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >2035)
                   & (result_df['ge'] < 2055) ]
    g2044_tot = result_df[(result_df['ge'] >2035)
                   & (result_df['ge'] < 2055) ]
    if (g2044_tot.size>0):
        g2044.append(g2044_counts.size/g2044_tot.size)
    g2044t.append(g2044_counts.size/15)
    #g1293 stuff
    g1293_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >1280)
                   & (result_df['ge'] < 1300) ]
    g1293_tot = result_df[(result_df['ge'] >1280)
                   & (result_df['ge'] < 1300) ]
    if (g1293_tot.size>0):
        g1293.append(g1293_counts.size/g1293_tot.size)
    g1293t.append(g1293_counts.size/15)
    #g1535 stuff #1525-1545
    g1535_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >1525)
                   & (result_df['ge'] < 1545) ]
    g1535_tot = result_df[(result_df['ge'] >1525)
                   & (result_df['ge'] < 1545) ]
    if (g1535_tot.size>0):
        g1535.append(g1535_counts.size/g1535_tot.size)
    #g383 stuff
    g383_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >380)
                   & (result_df['ge'] < 390) ]
    g383_tot = result_df[(result_df['ge'] >380)
                   & (result_df['ge'] < 390) ]
    if (g383_tot.size>0):
        g383.append(g383_counts.size/g383_tot.size)
    #g292 - 285-298
    g292_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >285)
                       & (result_df['ge'] < 298) ]
    g292_tot = result_df[(result_df['ge'] >285)
                       & (result_df['ge'] < 298) ]
    if (g292_tot.size>0):
        g292.append(g292_counts.size/g292_tot.size)
    #g639 - 630-645
    g639_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >630)
                       & (result_df['ge'] < 645) ]
    g639_tot = result_df[(result_df['ge'] >630)
                       & (result_df['ge'] < 645) ]
    if (g639_tot.size>0):
        g639.append(g639_counts.size/g639_tot.size)
    #g1190
    g1190_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >1170)
                       & (result_df['ge'] < 1210) ]
    g1190_tot = result_df[(result_df['ge'] >1170)
                       & (result_df['ge'] < 1210) ]
    if (g1190_tot.size>0):
        g1190.append(g1190_counts.size/g1190_tot.size)
    g1190t.append(g1190_counts.size/15)
    #g1848
    g1848_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >1830)
                       & (result_df['ge'] < 1850) ]
    g1848_tot = result_df[(result_df['ge'] >1830)
                       & (result_df['ge'] < 1850) ]
    if (g1848_tot.size>0):
        g1848.append(g1848_counts.size/g1848_tot.size)
    #g1848
    g1430_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >1420)
                       & (result_df['ge'] < 1440) ]
    g1430_tot = result_df[(result_df['ge'] >1420)
                       & (result_df['ge'] < 1440) ]
    if (g1430_tot.size>0):
        g1430.append(g1430_counts.size/g1430_tot.size)
    #g2378
    g2378_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >2370)
                       & (result_df['ge'] < 2390) ]
    g2378_tot = result_df[(result_df['ge'] >2370)
                       & (result_df['ge'] < 2390) ]
    if (g2378_tot.size>0):
        g2378.append(g2378_counts.size/g2378_tot.size)
    #g136
    g136_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >130)
                       & (result_df['ge'] < 145) ]
    g136_tot = result_df[(result_df['ge'] >130)
                       & (result_df['ge'] < 145) ]
    if (g136_tot.size>0):
        g136.append(g136_counts.size/g136_tot.size)
    #g170
    g170_counts = result_df[(result_df['A'] > cut_low) & (result_df['ge'] >160)
                       & (result_df['ge'] < 185) ]
    g170_tot = result_df[(result_df['ge'] >160)
                       & (result_df['ge'] < 185) ]
    if (g170_tot.size>0):
        g170.append(g170_counts.size/g170_tot.size)
    ratio1.append(g1190_counts.size/g1293_counts.size)
    ratio2.append(g639_counts.size/g383_counts.size)
    ratio3.append(g3142_counts.size/g1535_counts.size)

df_ratio=pd.DataFrame(ratio1, columns=['1190/1293'])
df_ratio2=pd.DataFrame(ratio2, columns=['639/383'])
df_ratio3=pd.DataFrame(ratio3, columns=['3142/1535'])

df_ratio=pd.concat([df_ratio, df_ratio2], axis=1)
df_ratio=pd.concat([df_ratio, df_ratio3], axis=1)

df_frac=pd.DataFrame(ml_return, columns=['ml_return'])
df_tot=pd.DataFrame(ml_return, columns=['ml_return'])

df1293t=pd.DataFrame(g1293t, columns=['g1293t'])
df1190t=pd.DataFrame(g1190t, columns=['g1190t'])
df3142t=pd.DataFrame(g3142t, columns=['g3142t'])

df_tot=pd.concat([df_tot, df1293t], axis=1)
df_tot=pd.concat([df_tot, df1190t], axis=1)
df_tot=pd.concat([df_tot, df3142t], axis=1)

print(df_tot)
df1293=pd.DataFrame(g1293, columns=['1293'])
df1535=pd.DataFrame(g1535, columns=['1535'])
df383=pd.DataFrame(g383, columns=['383'])
df848=pd.DataFrame(g848, columns=['848'])
df639=pd.DataFrame(g639, columns=['639'])
df1190=pd.DataFrame(g1190, columns=['1190'])
df2044=pd.DataFrame(g2044, columns=['2044'])
df2279=pd.DataFrame(g2279, columns=['2279'])
df2978=pd.DataFrame(g2978, columns=['2978'])
df3142=pd.DataFrame(g3142, columns=['3142'])
df1848=pd.DataFrame(g1848, columns=['1848'])
df1430=pd.DataFrame(g1430, columns=['1430'])
df2378=pd.DataFrame(g2378, columns=['2378'])
df136=pd.DataFrame(g136, columns=['136'])
df170=pd.DataFrame(g170, columns=['170'])

df_frac = pd.concat([df_frac, df1293], axis=1)
df_frac = pd.concat([df_frac, df1535], axis=1)
df_frac = pd.concat([df_frac, df383], axis=1)
df_frac = pd.concat([df_frac, df848], axis=1)
df_frac = pd.concat([df_frac, df639], axis=1)
df_frac = pd.concat([df_frac, df1190], axis=1)
df_frac = pd.concat([df_frac, df2044], axis=1)
df_frac = pd.concat([df_frac, df2279], axis=1)
df_frac = pd.concat([df_frac, df2978], axis=1)
df_frac = pd.concat([df_frac, df3142], axis=1)
df_frac = pd.concat([df_frac, df1848], axis=1)
df_frac = pd.concat([df_frac, df1430], axis=1)
df_frac = pd.concat([df_frac, df2378], axis=1)
df_frac = pd.concat([df_frac, df136], axis=1)
df_frac = pd.concat([df_frac, df170], axis=1)

df_plot = df_frac.set_index('ml_return').T
#print(df_frac)
print(df_ratio)


# In[ ]:


Headers = df_frac.columns.values.tolist()
import plotly.graph_objs as go
from plotly import tools

df_ratio.plot(figsize=(15,7), xticks=range(0, 50)).legend(bbox_to_anchor=(1, 1))
df_frac.plot.line(x='ml_return',figsize=(15,7)).legend(bbox_to_anchor=(1, 1))


# In[ ]:


#print(total_counts)
ndim_result=result_df.columns.size
#print(result_df)
s38_low=0.5
cl38_high=0.0
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

plt.figure(figsize=(10,4))
fig = px.histogram(s38, x="ge", nbins=3400, color = "glabel")
fig.update_xaxes(range=[100, 3500])
fig.show()





# In[ ]:
