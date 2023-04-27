import numpy as np
import math
from anastruct import SystemElements
import matplotlib.pyplot as plt

#-----------------Stiffness---------------------------
def stiffNess2DTruss(NoE,EL,NL,L,c,s,K,E,A):
    for i in range(NoE):
        n1 = EL[i,0]
        n2 = EL[i,1]

        x1=NL[n1-1,0]
        y1=NL[n1-1,1]
        x2=NL[n2-1,0]
        y2=NL[n2-1,1]

        L[i]=math.sqrt((x2-x1)**2+(y2-y1)**2)
        c[i]=(x2-x1)/L[i]
        s[i]=(y2-y1)/L[i]


        k1 = ((E*A)/(L[i])) * np.array([[c[i]*c[i],c[i]*s[i],-c[i]*c[i],-c[i]*s[i]],[c[i]*s[i],s[i]*s[i],-c[i]*s[i],-s[i]*s[i]],[-c[i]*c[i],-c[i]*s[i],c[i]*c[i],c[i]*s[i]],[-c[i]*s[i],-s[i]*s[i],c[i]*s[i],s[i]*s[i]]])
        k1 =np.asmatrix(k1)
        eDof=[n1*2-2, n1*2-1, n2*2-2, n2*2-1]
        indx=np.ix_(eDof,eDof)
        K[indx]=K[indx]+k1
    return K


# print("----------axialforce----------")
def axialforce(loadE,giatri_Loads,c,s,L,DOFs,EL):
    q = np.zeros((DOFs,1))
    for i,p in enumerate(loadE):
        q1 = (giatri_Loads[i])

        c1=(c[p-1])

        s1=(s[p-1])

        L1=(L[p-1])

        p1=int(EL[p-1,0])

        p2=int(EL[p-1,1])

        q[p1*2-2]=q[p1*2-2]+(q1*L1*0.5)*c1
        q[p1*2-1]=q[p1*2-1]+(q1*L1*0.5)*s1
        q[p2*2-2]=q[p2*2-2]+(q1*L1*0.5)*c1
        q[p2*2-1]=q[p2*2-1]+(q1*L1*0.5)*s1

    return q


#-------------------Displacement-----------------
def displacementCal(q,Fu,K,DOFs,BC):
    F_u=q+Fu
    k_x=K

    h=[]
    fuu=[]
    for i in range(DOFs):
        if(int(BC[i])==1):
            h.append(i)


    kkk=np.delete(k_x, h, axis=0)
    kkk1=np.delete(kkk, h, axis=1)


    fuu1=np.delete(F_u,h,axis=0)

    dis=np.dot(np.linalg.inv(kkk1),fuu1)

    return dis


