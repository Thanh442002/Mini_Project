import math 
import numpy as np


def reactions_PL(n, pointLoads, A, B):
    xp = pointLoads[n,0]
    fx = pointLoads[n,1]
    fy = pointLoads[n,2]
    
    arm_A = A - xp
    moment_p = fy*arm_A
    arm_B = B - A
    
    V_B = moment_p/arm_B
    V_A = -fy - V_B
    H_A = -fx
    
    return V_A, V_B, H_A



def shear_moment_PL(n, pointLoads, A, B, PL_record, X):    
    xp = pointLoads[n,0]
    fy = pointLoads[n,2]
    Va = PL_record[n,0]
    Vb = PL_record[n,1]
    
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
 
        if x > xp:
            shear = shear + fy
            moment = moment - fy*(x-xp)
 
        #Store shear and moment
        Shear[i] = shear
        Moment[i] = moment
 
    return Shear, Moment
