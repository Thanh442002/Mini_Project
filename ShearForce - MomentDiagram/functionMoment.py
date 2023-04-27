import math 
import numpy as np

def reactions_PM(n, pointMoment, A, B):
    xm = pointMoment[n,0]
    M = pointMoment[n,1]
    
    arm_B=B-A
    V_B=M/arm_B
    
    V_A=-V_B
    
    return V_A, V_B




def shear_moment_PM(n, pointMoment, A, B, PM_record, X):    

    Va = PM_record[n,0]
    Vb = PM_record[n,1]
    xm = pointMoment[n,0]
    M = pointMoment[n,1]
## Create container to save shear and momment, the length equal to len(X)
    Shear = np.zeros(len(X))  
    Moment = np.zeros(len(X)) 
    for i, x in enumerate(X):    
        shear = 0  
        moment = 0 
 
        if x > A:
            shear = shear + Va
            moment = moment - Va*(x-A)
 
        if x > B:
            shear = shear + Vb
            moment = moment - Vb*(x-B)
 
        if x > xm:
            shear = shear + 0
            moment = moment - M
 
        #Store shear and moment
        Shear[i] = shear
        Moment[i] = moment
 
    return Shear, Moment


