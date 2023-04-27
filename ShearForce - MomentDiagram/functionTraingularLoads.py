import math 
import numpy as np


def reactions_TL(n, traingularLoads, A, B):
    x_start = traingularLoads[n,0]
    x_end = traingularLoads[n,1]
    l_tl = x_end - x_start
    
    if(traingularLoads[n,2] != 0):
        x_tl = x_start + (1/3)*l_tl
        F_tl = 0.5*traingularLoads[n,2]*l_tl
        
        arm_A = A - x_tl
        moment = F_tl*arm_A
    
        arm_B = B-A
        V_B = moment/arm_B
        V_A = -F_tl - V_B
    elif (traingularLoads[n,2] == 0):
        x_tl = x_start + (2/3)*l_tl
        F_tl = 0.5*traingularLoads[n,3]*l_tl
        
        arm_A = A - x_tl
        moment = F_tl*arm_A
    
        arm_B = B-A
        V_B = moment/arm_B
        V_A = -F_tl - V_B
    return V_A, V_B



def shear_moment_TL(n, traingularLoads, A, B, TL_record, X):    

    Va = TL_record[n,0]
    Vb = TL_record[n,1]
    x_start = traingularLoads[n,0]
    x_end = traingularLoads[n,1]
    l_tl = x_end - x_start
    f_start = traingularLoads[n,2]
    f_end = traingularLoads[n,3]
    x_tl = x_start + (1/3)*l_tl
    F_tl_start = 0.5*traingularLoads[n,2]*l_tl
    F_tl_end = 0.5*traingularLoads[n,3]*l_tl
    
    if(traingularLoads[n,2] != 0):
        
## Create container to save shear and momment, the length equal to len(X)
        Shear = np.zeros(len(X))  
        Moment = np.zeros(len(X)) 
        for i, x in enumerate(X):    
            shear = 0  
            moment = 0 

            if x > A :
                shear = shear + Va
                moment = moment - Va*(x-A)

            if x > B:
                shear = shear + Vb
                moment = moment - Vb*(x-B)

            if (x > x_start and x <= x_end):
                x_cut= (x - x_start)
                f_cut = f_start - x_cut*(f_start/l_tl)
                
                f1 = 0.5*(f_start - f_cut)*x_cut
                x1 = (2/3)*x_cut
                
                f2 = f_cut * x_cut
                x2 = 0.5*x_cut
                
                shear = shear + f1 + f2
                moment = moment - f1*x1 - f2*x2

            if x > x_end:
                shear = shear + F_tl_start
                moment = moment - F_tl_start*(x-x_tl)

            #Store shear and moment
            Shear[i] = shear
            Moment[i] = moment
            
    if(traingularLoads[n,2] == 0):
        Shear = np.zeros(len(X))  
        Moment = np.zeros(len(X)) 
        for i, x in enumerate(X):    
            shear = 0  
            moment = 0 

            if x > A :
                shear = shear + Va
                moment = moment - Va*(x-A)

            if x > B:
                shear = shear + Vb
                moment = moment - Vb*(x-B)

            if (x > x_start and x <= x_end):
                x_cut= (x - x_start)
                f_cut = f_end * (x_cut/l_tl)
                
                f1=0.5*f_cut*x_cut
                x1=(1/3)*x_cut
                
                shear = shear + f1
                moment = moment - f1*x1
                
            if x > x_end:
                shear = shear + F_tl_end
                moment = moment - F_tl_end*(x-(x_start+(2/3)*l_tl))
            
            #Store shear and moment
            Shear[i] = shear
            Moment[i] = moment

    return Shear, Moment

