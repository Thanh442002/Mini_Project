# Bending Moment and Shear Force
import math 
import numpy as np
import plotly as py
import plotly.graph_objs as go

from functionLoads import *
from functionDistributedLoads import *
from functionMoment import *
from functionTraingularLoads import *


pointMoment =np.array([[]])
pointLoads = np.array([[]])
distributedLoads =np.array([[]])
traingularLoads = np.array([[]])


#Input 
# Chieu duong huong len, Moment cung chieu kim dong ho duong
LoB = 6 # Length of beam
A = 0    # Distance to left support pillow
B = 6  # Distance to right .....

#Force and Moment data
pointLoads = np.array([[1,0,2.5]]) #(x,fx,fy)
pointMoment = np.array([[2,1]]) #(x,M)
distributedLoads = np.array([[3,6,-1]]) #(x_start, x_end, Load)
# traingularLoads = np.array([[0,4,0,-50]])


divs = 10000
delta = LoB/divs # divide small beam
X = np.arange(0, LoB + delta, delta)
nPL = len(pointLoads[0]) # number of point load
nPM= len(pointMoment[0]) # number of moment 
nDL=len(distributedLoads[0]) # number of distributed Load
nTL=len(traingularLoads[0]) # number of traingular Load

reactions = np.array([0.0, 0, 0]) 
shearForce = np.empty([0, len(X)]) #Shearforce at each point
bendingMoment = np.empty([0,len(X)]) # Moment at each point



#Load
PL_record = np.empty([0,3])

if (nPL > 0):
    for n, p in enumerate(pointLoads): #The enumerate return 2 var is count i and value of n
        Va, Vb, Ha = reactions_PL(n, pointLoads, A, B)
        PL_record = np.append(PL_record, [np.array([Va, Vb, Ha])], 0)
        
        reactions[0]= reactions[0]+Va
        reactions[1]= reactions[1]+Vb
        reactions[2]= reactions[2]+Ha
        

#Moment
PM_record = np.empty([0,2])

if(nPM >0):
    for n, p in enumerate(pointMoment): #The enumerate return 2 var is count i and value of n
        Va, Vb = reactions_PM(n, pointMoment, A, B)
        PM_record = np.append(PM_record, [np.array([Va, Vb])], 0)
        
        reactions[0]= reactions[0]+Va
        reactions[1]= reactions[1]+Vb


#DistributedLoads
DL_record = np.empty([0,2])

if(nDL>0):
    for n, p in enumerate (distributedLoads):
        Va, Vb = reactions_DL(n, distributedLoads, A, B)
        DL_record = np.append(DL_record, [np.array([Va, Vb])], 0)
        
        reactions[0]= reactions[0]+Va
        reactions[1]= reactions[1]+Vb
        


#TraingularLoads
TL_record = np.empty([0,2])

if(nTL>0):
    for n, p in enumerate (traingularLoads):
        Va, Vb = reactions_TL(n, traingularLoads, A, B)
        TL_record = np.append(TL_record, [np.array([Va, Vb])], 0)
        
        reactions[0]= reactions[0]+Va
        reactions[1]= reactions[1]+Vb



if (nPL> 0):
    for n, p in enumerate(pointLoads):
        Shear, Moment = shear_moment_PL(n, pointLoads, A, B, PL_record, X)
        shearForce = np.append(shearForce, [Shear], 0)       
        bendingMoment = np.append(bendingMoment, [Moment], 0)



if (nPM> 0):
    for n, p in enumerate(pointMoment):
        Shear, Moment = shear_moment_PM(n, pointMoment, A, B, PM_record, X)
        shearForce = np.append(shearForce, [Shear], 0)       
        bendingMoment = np.append(bendingMoment, [Moment], 0)



if (nDL> 0):
    for n, p in enumerate(distributedLoads):
        Shear, Moment = shear_moment_DL(n, distributedLoads, A, B, DL_record, X)
        shearForce = np.append(shearForce, [Shear], 0)       
        bendingMoment = np.append(bendingMoment, [Moment], 0)



if (nTL> 0):
    for n, p in enumerate(traingularLoads):
        Shear, Moment = shear_moment_TL(n, traingularLoads, A, B, TL_record, X)
        shearForce = np.append(shearForce, [Shear], 0)       
        bendingMoment = np.append(bendingMoment, [Moment], 0)



layout = go.Layout(
    title = {'text' : 'Shear Force Diagram',
            'y':.9,
            'x':0.5,
            'xanchor':'center',
            'yanchor':'top',
            },
    
    yaxis = dict(
        title= 'ShearForce (kN)'
    ),
    xaxis = dict(
        title='Length (m)',
        range = [-1, LoB+1]
    ),
    showlegend=False,
)

line = go.Scatter(
    x=X,
    y = sum(shearForce),
    mode='lines',
    name='Shear Force',
    fill='tonexty',
    line_color='green',
    fillcolor='rgba(51, 187, 47, 0.9)'
)

axis = go.Scatter(
    x=[0,LoB],
    y=[0,0],
    mode='lines',
    line_color='black'
)

fig=go.Figure(data=[line,axis],layout=layout)

fig.show()



layout = go.Layout(
    title = {'text' : 'Moment Diagram',
            'y':.9,
            'x':0.5,
            'xanchor':'center',
            'yanchor':'top',
            },
    
    yaxis = dict(
        title= 'Moment (kN.m)',
        autorange='reversed'
    ),
    xaxis = dict(
        title='Length (m)',
        range = [-1, LoB+1]
    ),
    showlegend=False,
)

line = go.Scatter(
    x=X,
    y = -sum(bendingMoment),
    mode='lines',
    name='Moment',
    fill='tonexty',
    line_color='blue',
    fillcolor='rgba(133, 85, 179, 0.9)'
)

axis = go.Scatter(
    x=[0,LoB],
    y=[0,0],
    mode='lines',
    line_color='black'
)

fig=go.Figure(data=[line,axis],layout=layout)

fig.show()

