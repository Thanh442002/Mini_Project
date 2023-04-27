import numpy as np
import math
from anastruct import SystemElements
from functionBeam import *

print("--------Input Material parameters-------")
A = float(input('A: '))
E = float(input('E: '))
J = float(input('J: '))

ss = SystemElements(EA=E*A, EI=E*J)
#---------------------------
print("Input Number of Nodes and Number of Elements")
NoN = int(input())
NoE =  int(input())
DOFs = 3*NoN

#------------------------------------
NL= []
print("--------Input coordinates each Node--------")
for i in range(NoN):
    addNL = [float (input('x-co'+str(i+1)+ ': ')),float (input('y-co'+str(i+1)+ ': '))]
    NL.append(addNL)
NL = np.asarray(NL)

# print(NL)
EL = []
print("--------Input node start and node end of Element-------")
for i in range(int(NoE)):
    addEL = [ int(input('Node start of Element'+str(i+1)+ ': ')), int(input('Node end of Element'+str(i+1)+ ': '))]
    EL.append(addEL)
EL = np.asarray(EL)

#----------------Plot-------------------
for i, n in enumerate(EL):
    n1 = EL[i,0]
    n2 = EL[i,1]
    location1=NL[n1-1].tolist()
    location2=NL[n2-1].tolist()
    ss.add_element(location=[location1,location2])
ss.show_structure()
#------------------BC---------------------

BC = np.zeros((DOFs,1))
print("-------Number of bound nodes-------")
sonut=int(input())               
print("--------Input 1 if bound, otherwise enter 0-------")
if(sonut>1):
    for i in range(sonut):
        print("--------BC in the x y direction and rotate at node--------")
        BC_tainut = int(input())
        BCx_nut= int(input('BC(x)' +str(BC_tainut)+':'))
        BCy_nut= int(input('BC(y)' +str(BC_tainut)+':'))
        BC_xoay= int(input('BC(rotate)' +str(BC_tainut)+':'))
        BC[(3*BC_tainut-3)]=BC[(3*BC_tainut-3)]+BCx_nut
        BC[(3*BC_tainut-2)]=BC[(3*BC_tainut-2)]+BCy_nut
        BC[(3*BC_tainut-1)]=BC[(3*BC_tainut-1)]+BC_xoay
        
        if(BCx_nut==0):
            ss.add_support_roll(node_id = BC_tainut, direction=2)
        if(BCy_nut==0):
            ss.add_support_roll(node_id = BC_tainut, direction=1)
        if(BCx_nut !=0 and BCy_nut != 0 and BC_xoay==0):
            ss.add_support_hinged(node_id = BC_tainut) 
        if(BCx_nut !=0 and BCy_nut != 0 and BC_xoay !=0):
            ss.add_support_fixed(node_id = BC_tainut) 
if(sonut==1):    
    print("-------BC in the x y direction and rotate at node-------")
    BC_tainut = int(input())
    BCx_nut= int(input('BC(x)' +str(BC_tainut)+':'))
    BCy_nut= int(input('BC(y)' +str(BC_tainut)+':'))
    BC_xoay= int(input('BC(rotate)' +str(BC_tainut)+':'))
    BC[(3*BC_tainut-3)]=BC[(3*BC_tainut-3)]+BCx_nut
    BC[(3*BC_tainut-2)]=BC[(3*BC_tainut-2)]+BCy_nut
    BC[(3*BC_tainut-1)]=BC[(3*BC_tainut-1)]+BC_xoay
        
    if(BCx_nut==0):
        ss.add_support_roll(node_id=BC_tainut, direction=2)
    if(BCy_nut==0):
        ss.add_support_roll(node_id=BC_tainut, direction=1)
    if(BCx_nut !=0 and BCy_nut != 0 and BC_xoay == 0):
        ss.add_support_hinged(node_id=BC_tainut) 
    if(BCx_nut !=0 and BCy_nut != 0 and BC_xoay != 0):
        ss.add_support_fixed(node_id=BC_tainut)
# ss.show_structure()
#---------------------------------------------
#-------------------Lưc tập trung---------------------
Fu = np.zeros((DOFs,1))#%%%%%%%%%%%%%%
print("-------Number of nodes have force-------")
sonut=int(input())
if(sonut>1):
    for i in range(sonut):
        print("-------Force in the x y direction at node-------")
        F_tainut = int(input())
        Fx_nut= int(input('F(x)' +str(F_tainut)+':'))
        Fy_nut= int(input('F(y)' +str(F_tainut)+':'))
        
        Fu[(3*F_tainut-3)]=Fu[(3*F_tainut-3)]+Fx_nut
        Fu[(3*F_tainut-2)]=Fu[(3*F_tainut-2)]+Fy_nut
        ss.point_load(node_id=F_tainut,Fx=Fx_nut,Fy=Fy_nut)

if(sonut==1):    
    print("-------Force in the x y direction at node--------")
    F_tainut = int(input())

    Fx_nut= int(input('F(x)' +str(F_tainut)+':'))
    Fy_nut= int(input('F(y)' +str(F_tainut)+':'))

    Fu[(3*F_tainut-3)]=Fu[(3*F_tainut-3)]+Fx_nut
    Fu[(3*F_tainut-2)]=Fu[(3*F_tainut-2)]+Fy_nut

    ss.point_load(node_id=F_tainut,Fx=Fx_nut,Fy=Fy_nut)
ss.show_structure()
#-------------------Moment tập trung---------------------
Moment = np.zeros((DOFs,1)) #%%%%%%%%%
print("------Number of nodes have Moment-------")
sonut=int(input())
if(sonut>1):
    for i in range(sonut):
        print("Momnet at node")
        Moment_tainut = int(input())
        M_nut= int(input('Độ lớn M_nut' +str(Moment_tainut)+':'))
           
        Moment[(3*Moment_tainut-1)]=Moment[(3*Moment_tainut-1)]+M_nut

        ss.moment_load(node_id=Moment_tainut, Ty=M_nut)

if(sonut==1):    
    print("Momnet at node")
    Moment_tainut = int(input())
    M_nut= int(input('Độ lớn M_nut' +str(Moment_tainut)+':'))
    
    Moment[(3*Moment_tainut-1)]=Moment[(3*Moment_tainut-1)]+M_nut

    ss.moment_load(node_id=Moment_tainut, Ty=M_nut)

#-----------------------------------------------
L = np.zeros((NoE,1))
c = np.zeros((NoE,1))
s = np.zeros((NoE,1))
K = np.zeros([DOFs,DOFs])
#-----------------Stiffness---------------------------

K=stiffness2DFrame(EL,NoE,NL,L,c,s,A,E,J,K)

#---------------------Nhập tải dọc phần tử----------------------
loadE=[]#Luu phan tu co tai
giatri_Loads=[]
print("--------Number of elements have axial load---------")
EhL=int(input())
if(EhL>1):
    for i in range(EhL):
        print("Element: ")
        loads_taielement = int(input())
        loadE.append(loads_taielement)
        load = int(input('Gia tri q' +str(loads_taielement)+':'))
        giatri_Loads.append(load)
        ss.q_load(q=load, element_id=loads_taielement, direction='parallel')

if(EhL==1):
    print("Element: ")
    loads_taielement = int(input())
    loadE.append(loads_taielement)
    load = int(input('Gia tri q' +str(loads_taielement)+':'))
    giatri_Loads.append(load)
    ss.q_load(q=load, element_id=loads_taielement, direction='parallel')

F_doctruc = np.zeros((DOFs,1))#%%%%%%%%%%%%%
print("--------------------")

F_doctruc= axialforce(loadE, giatri_Loads, c, s, L, EL, F_doctruc)

#------------------------DistributedLoads---------------------------
distriElement=[]#Luu phan tu co tai
giatri_distributed_Loads=[]
print(" Number of elements have distributed loads")
numDisElenment=int(input())
if(numDisElenment>1):
    for i in range(numDisElenment):
        print("Element: ")
        distributeloads_taielement = int(input())
        distriElement.append(distributeloads_taielement)
        distributedL = int(input('Gia tri tai phan bo deu tai phan tu ' +str(distributeloads_taielement)+':'))
        giatri_distributed_Loads.append(distributedL)
        ss.q_load(q=distributedL, element_id=distributeloads_taielement, direction='element')

if(numDisElenment==1):
    print("Element: ")
    distributeloads_taielement = int(input())
    distriElement.append(distributeloads_taielement)
    distributedL = int(input('Gia tri tai phan bo deu tai phan tu ' +str(distributeloads_taielement)+':'))
    giatri_distributed_Loads.append(distributedL)
    ss.q_load(q=distributedL, element_id=distributeloads_taielement, direction='element')

#------------------------------------------------
F_phanbodeu = np.zeros((DOFs,1))#%%%%%%%%%%
print("--------------------")
F_phanbodeu = distributedLoads(distriElement, giatri_distributed_Loads, c, s, L, EL, F_phanbodeu)

ss.show_structure()
#-------------------Displacement-----------------
print("---------Displacement-----------")
F_tong=Fu+F_doctruc+F_phanbodeu+Moment
k_x=K
h=[]
fuu=[]
for i in range(DOFs):
    if(int(BC[i])==1):
        h.append(i)

kkk=np.delete(k_x, h, axis=0)
kkk1=np.delete(kkk, h, axis=1)

fuu1=np.delete(F_tong,h,axis=0)

kkk1=np.linalg.inv(kkk1)

dis=np.dot(kkk1,fuu1)
print(dis)#Chuyen vi

#------------------------------------------  
#-----------------Reactions---------------- 
print("---------Reactions-----------")
displacement = np.zeros((DOFs,1))
j=0
for i in range(DOFs):
    if(BC[i]==0):
        displacement[i]=displacement[i]+dis[j]
        j=j+1

phanluc=np.dot(K,displacement)-(Fu+F_doctruc+F_phanbodeu+Moment)
print(np.round(phanluc),-1)
#------------------------------------------
#---------------Moment---------------------
print("-----------Moment uon------------")

for i in range(NoE):
    S_e=np.zeros((2,6))
    q_e=np.zeros((6,1))

    nn1 = int(EL[i,0]) #1
    nn2 = int(EL[i,1]) #2
    cc1= c[i]
    ss1= s[i]
    Ll1= L[i]

    S_e[0][0]=S_e[0][0] + 6*Ll1*ss1
    S_e[0][1]=S_e[0][1] + -6*Ll1*cc1
    S_e[0][2]=S_e[0][2] + -4*Ll1**2
    S_e[0][3]=S_e[0][3] + -6*Ll1*ss1
    S_e[0][4]=S_e[0][4] + 6*Ll1*cc1
    S_e[0][5]=S_e[0][5] + -2*Ll1**2
    S_e[1][0]=S_e[1][0] + -6*Ll1*ss1
    S_e[1][1]=S_e[1][1] + 6*Ll1*cc1
    S_e[1][2]=S_e[1][2] + 2*Ll1**2
    S_e[1][3]=S_e[1][3] + 6*Ll1*ss1
    S_e[1][4]=S_e[1][4] + -6*Ll1*cc1
    S_e[1][5]=S_e[1][5] + 4*Ll1**2

    q_e[0]=q_e[0]+displacement[3*nn1-3]
    q_e[1]=q_e[1]+displacement[3*nn1-2]
    q_e[2]=q_e[2]+displacement[3*nn1-1]
    q_e[3]=q_e[3]+displacement[3*nn2-3]
    q_e[4]=q_e[4]+displacement[3*nn2-2]
    q_e[5]=q_e[5]+displacement[3*nn2-1]

    Moment_uon=(E*J/(Ll1**3)) * np.matmul(S_e,q_e)

    print('---Phần tử ' + str(i+1) + '---')
    print(Moment_uon)

ss.show_structure()





























































































































































































































































































































ss.solve()

ss.show_bending_moment()

ss.show_displacement(factor=500)  