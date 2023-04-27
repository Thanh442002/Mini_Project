import numpy as np
import math
from anastruct import SystemElements
ss = SystemElements()

#-----------------Stiffness--------------------
def stiffness2DFrame(EL,NoE,NL,L,c,s,A,E,J,K):
    for i in range(NoE):
        n1 = EL[i,0] #1

        n2 = EL[i,1]#2

        x1=NL[n1-1,0]
        y1=NL[n1-1,1]
        x2=NL[n2-1,0]
        y2=NL[n2-1,1]
        L[i]=math.sqrt((x2-x1)**2+(y2-y1)**2)
        c[i]=(x2-x1)/L[i]
        s[i]=(y2-y1)/L[i]

        B=12*J/(L[i]**2)

        z1=float(A*c[i]*c[i]+B*s[i]*s[i])

        z2=float((A-B)*c[i]*s[i])

        z3=float(B*L[i]*s[i]*0.5)

        z4=float(A*s[i]*s[i]+B*c[i]*c[i])

        z5=float(B*L[i]*c[i]*0.5)

        k1 = ((E/L[i])*np.array([[z1,z2,-z3,-z1,-z2,-z3],[z2,z4,z5,-z2,-z4,z5],[-z3,z5,4*J,z3,-z5,2*J],[-z1,-z2,z3,z1,z2,z3],[-z2,-z4,-z5,z2,z4,-z5],[-z3,z5,2*J,z3,-z5,4*J]]))

        k1 =np.asmatrix(k1)
        eDof=[n1*3-3, n1*3-2, n1*3-1, n2*3-3, n2*3-2, n2*3-1]
        indx=np.ix_(eDof,eDof)
        K[indx]=K[indx]+k1

    return K


# ----------axialforce----------
def axialforce(loadE, giatri_Loads, c, s, L, EL, F_doctruc):
    for i,p in enumerate(loadE):
        luc_doc = (giatri_Loads[i])

        c1=(c[p-1])
        # print(c1)
        s1=(s[p-1])
        # print(s1)
        L1=(L[p-1])
        # print(L1)
        p1=int(EL[p-1,0])
        # print(p1)
        p2=int(EL[p-1,1])
        # print(p2)
        F_doctruc[p1*3-3]=F_doctruc[p1*3-3]+(luc_doc*L1*c1*0.5)
        F_doctruc[p1*3-2]=F_doctruc[p1*3-2]+(luc_doc*L1*s1*0.5)
        F_doctruc[p1*3-1]=F_doctruc[p1*3-1]+0
        F_doctruc[p2*3-3]=F_doctruc[p2*3-3]+(luc_doc*L1*c1*0.5)
        F_doctruc[p2*3-2]=F_doctruc[p2*3-2]+(luc_doc*L1*s1*0.5)
        F_doctruc[p2*3-1]=F_doctruc[p2*3-1]+0
        
    return F_doctruc



#------------------------DistributedLoads---------------------------
def distributedLoads(distriElement, giatri_distributed_Loads, c, s, L, EL, F_phanbodeu):
    for i,p in enumerate(distriElement):
        luc_phanbo = (giatri_distributed_Loads[i])

        c1=(c[p-1])
        # print(c1)
        s1=(s[p-1])
        # print(s1)
        L1=(L[p-1])
        # print(L1)
        p1=int(EL[p-1,0])
        # print(p1)
        p2=int(EL[p-1,1])
        # print(p2)
        F_phanbodeu[p1*3-3]=F_phanbodeu[p1*3-3]+(-luc_phanbo*L1*s1*0.5)
        F_phanbodeu[p1*3-2]=F_phanbodeu[p1*3-2]+(luc_phanbo*L1*c1*0.5)
        F_phanbodeu[p1*3-1]=F_phanbodeu[p1*3-1]+(luc_phanbo*L1*L1/12)
        F_phanbodeu[p2*3-3]=F_phanbodeu[p2*3-3]+(-luc_phanbo*L1*s1*0.5)
        F_phanbodeu[p2*3-2]=F_phanbodeu[p2*3-2]+(luc_phanbo*L1*c1*0.5)
        F_phanbodeu[p2*3-1]=F_phanbodeu[p2*3-1]+(-luc_phanbo*L1*L1/12)
        
 
    return F_phanbodeu



# momentE=[]#Luu phan tu co tai
# giatri_moments=[]
# print(" Số phần tu co moment giữa phần tử tải")
# EhM=int(input())
# if(EhM>1):
#     for i in range(EhM):
#         print("Element: ")
#         moments_taielement = int(input())
#         momentE.append(moments_taielement)
#         moment = int(input('Gia tri q' +str(moments_taielement)+':'))
#         giatri_moments.append(moment)
#         # ss.q_moment(q=moment, element_id=moments_taielement, direction='parallel')

# if(EhM==1):
#     print("Element: ")
#     moments_taielement = int(input())
#     momentE.append(moments_taielement)
#     moment = int(input('Gia tri q' +str(moments_taielement)+':'))
#     giatri_moments.append(moment)
#     # ss.q_moment(q=moment, element_id=moments_taielement, direction='parallel')

# def Moment_giuaphantu(Moment,)