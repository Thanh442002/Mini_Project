import math 
import numpy as np



def reactions_DL(n, distributedLoads, A, B):
    x_start = distributedLoads[n,0]
    x_end = distributedLoads[n,1]
    l_dl = x_end - x_start
    
    x_dl = x_start + 0.5*l_dl
    
    F_dl = distributedLoads[n,2] * l_dl
    
    #Moment with Point A
    arm_A = A - x_dl
    moment = F_dl*arm_A
    
    arm_B = B-A
    V_B = moment/arm_B
    V_A = -F_dl - V_B
    
    return V_A, V_B




def shear_moment_DL(n, distributedLoads, A, B, DL_record, X):    

    Va = DL_record[n,0]
    Vb = DL_record[n,1]
    x_start = distributedLoads[n,0]
    x_end = distributedLoads[n,1]
    l_dl = x_end - x_start
    
    x_dl = x_start + 0.5*l_dl
    
    F_dl = distributedLoads[n,2] * l_dl
## Create container to save shear and momment, the length equal to len(X)
    Shear = np.zeros(len(X))  
    Moment = np.zeros(len(X)) 
    for i, x in enumerate(X):    
        shear = 0  
        moment = 0 
 
        if x > A :
            shear = shear + Va
            moment = moment - Va*(x-A)
        
        if x >B:
            shear = shear + Vb
            moment = moment - Vb*(x-B)
 
        if (x > x_start and x <= x_end):
            x1= (x - x_start)*0.5
            Fy = distributedLoads[n,2] * (x-x_start)
            
            shear = shear + Fy
            moment = moment - Fy*x1
 
        if x > x_end:
            shear = shear + F_dl
            moment = moment - F_dl*(x-x_dl)
 
        #Store shear and moment
        Shear[i] = shear
        Moment[i] = moment
 
    return Shear, Moment
