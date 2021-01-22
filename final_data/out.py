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
data_type=1 #1 is old (F), 0 in new (Q)
if (data_type==1):
    data_in = rnp.root2array("pyTreeAverageFatF_train.root","pytree",
                             branches=['e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','gid','glabel'])
    assert_equal(data_in.dtype.names, ('e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','gid','glabel'))
    num_data_columns=14.0
else:
    data_in = rnp.root2array("pyTreeAverageFatQ.root","pytree",
                             branches=['e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','ga','gid','glabel',
                                      'cre','ix','iy','iz'])
    assert_equal(data_in.dtype.names, ('e0','e1','e2','e3','e4','e5','e6','x','m','dt','gmult','ge','ga','gid','glabel',
                                      'cre','ix','iy','iz'))
    num_data_columns=19.0
#print(data_in.dtype)

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

mlr = []
tp = []
fp = []
tn = []
fn = []
tp_tot = len(result_df[(result_df['gid']==1)])
tn_tot = len(result_df[(result_df['gid']==0)])
print('tp_tot:%d tn_tot:%d' % (tp_tot,tn_tot))
for cut_val in range(20):
    cut_low=cut_val*0.05
    mlr.append(cut_low)
    tp.append(len(result_df[(result_df['A'] > cut_low) & (result_df['gid']==1)])/tp_tot)
    fn.append(len(result_df[(result_df['A'] > cut_low) & (result_df['gid']==0)])/tn_tot)
    tn.append(len(result_df[(result_df['A'] < cut_low) & (result_df['gid']==0)])/tn_tot)
    fp.append(len(result_df[(result_df['A'] < cut_low) & (result_df['gid']==1)])/tp_tot)

df_cm=pd.DataFrame(mlr, columns=['mlr'])
df_tp=pd.DataFrame(tp, columns=['tp'])
df_fp=pd.DataFrame(fp, columns=['fp'])
df_tn=pd.DataFrame(tn, columns=['tn'])
df_fn=pd.DataFrame(fn, columns=['fn'])

#df_cm=pd.concat([df_cm, df_mlr], axis=1)
df_cm=pd.concat([df_cm, df_tp], axis=1)
df_cm=pd.concat([df_cm, df_fp], axis=1)
df_cm=pd.concat([df_cm, df_tn], axis=1)
df_cm=pd.concat([df_cm, df_fn], axis=1)
#print(df_cm)

fig = px.scatter(df_cm, x="fp",y="tn",color="mlr",opacity=1)
#fig = px.line(df_cm, x="fp",y="tn")
fig.show()

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
print(metrics.roc_auc_score(y, scores))

#metrics that need binary so using >0.5
print(scores)
scores_round=np.round_(scores,0)
print(scores_round)
print(metrics.classification_report(y, scores_round))
confusion_matrix=metrics.confusion_matrix(y, scores_round)
confusion_matrix_norm=metrics.confusion_matrix(y, scores_round,normalize='true')
print(confusion_matrix)
print(confusion_matrix_norm)
disp = ConfusionMatrixDisplay(confusion_matrix_norm)
disp = disp.plot()
plt.show()

lw = 2
plt.plot(fpr, tpr, color='darkorange', marker='.',
         lw=lw, label='ROC curve (area = %0.2f)' % roc_auc)
plt.plot([0, 1], [0, 1], color='navy', lw=lw, linestyle='--')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('')
plt.legend(loc="lower right")
plt.show()


# plot the roc curve for the model
# plt.plot(ns_fpr, ns_tpr, linestyle='--', label='No Skill')
plt.plot(fpr, tpr, marker='.', label='Logistic')
# axis labels
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
# show the legend
plt.legend()
# show the plot
plt.show()
