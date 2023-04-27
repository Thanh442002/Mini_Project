import numpy as np
import math
from anastruct import SystemElements
from functionTruss import *


print("--------Input Material parameters-------")
A = float(input('A: '))
E = float(input('E: '))
ss = SystemElements(EA=A*E)

# A=0.01
# E=2e11

# -------------------------------
print("---------Input NoN and NoE-----------")
NoN = int(input('Number of nodes: '))
NoE =  int(input('Number of elements: '))
DOFs = 2*NoN
# ------------------------------

NL= []
print("--------Input coordinates each Node---------")
for i in range(NoN):
    addNL = [float (input('x-co'+str(i+1)+ ': ')),float (input('y-co'+str(i+1)+ ': '))]
    NL.append(addNL)
NL = np.asarray(NL)

# print(NL)
EL = []
print("-------Input  node start and node end of Element----------")
for i in range(int(NoE)):
    addEL = [ int(input('Node start of Element'+str(i+1)+ ': ')), int(input('Node end of Element'+str(i+1)+ ': '))]
    EL.append(addEL)
EL = np.asarray(EL)

# ------------------PLOt---------------------

for i, n in enumerate(EL):
    n1 = EL[i,0]
    n2 = EL[i,1]
    location1=NL[n1-1].tolist()
    location2=NL[n2-1].tolist()
    # print([location1,location2])
    ss.add_truss_element(location=[location1,location2])
ss.show_structure()

#---------------BC-------------------

BC = np.zeros((DOFs,1))
print("-------Number of bound nodes-------")
sonut=int(input())               
print("-----Input 1 if bound, otherwise enter 0------")
if(sonut>1):
    for i in range(sonut):
        print("BC in the x y direction at node")
        BC_tainut = int(input())
        BCx_nut= int(input('BC(x)' +str(BC_tainut)+':'))
        BCy_nut= int(input('BC(y)' +str(BC_tainut)+':'))
        BC[(2*BC_tainut-2)]=BC[(2*BC_tainut-2)]+BCx_nut
        BC[(2*BC_tainut-1)]=BC[(2*BC_tainut-1)]+BCy_nut
        
        if(BCx_nut==0):
            ss.add_support_roll(node_id=BC_tainut, direction=2)
        if(BCy_nut==0):
            ss.add_support_roll(node_id=BC_tainut, direction=1)
        if(BCx_nut !=0 and BCy_nut != 0):
            ss.add_support_hinged(node_id=BC_tainut) 
if(sonut==1):    
    print("BC in the x y direction at node")
    BC_tainut = int(input())
    BCx_nut= int(input('BC(x)' +str(BC_tainut)+':'))
    BCy_nut= int(input('BC(y)' +str(BC_tainut)+':'))
    BC[(2*BC_tainut-2)]=BC[(2*BC_tainut-2)]+BCx_nut
    BC[(2*BC_tainut-1)]=BC[(2*BC_tainut-1)]+BCy_nut
        
    if(BCx_nut==0):
        ss.add_support_roll(node_id=BC_tainut, direction=2)
    if(BCy_nut==0):
        ss.add_support_roll(node_id=BC_tainut, direction=1)
    if(BCx_nut !=0 and BCy_nut != 0):
        ss.add_support_hinged(node_id=BC_tainut) 


#-------------------Force-----------------
Fu = np.zeros((DOFs,1))

print("-----Number of nodes have force------")
sonut=int(input())
if(sonut>1):
    for i in range(sonut):
        print("-----Force in the x y direction at node-----")
        F_tainut = int(input())
        Fx_nut= int(input('F(x)' +str(F_tainut)+':'))
        Fy_nut= int(input('F(y)' +str(F_tainut)+':'))
        
        Fu[(2*F_tainut-2)]=Fu[(2*F_tainut-2)]+Fx_nut
        Fu[(2*F_tainut-1)]=Fu[(2*F_tainut-1)]+Fy_nut
        ss.point_load(node_id=F_tainut,Fx=Fx_nut,Fy=Fy_nut)

if(sonut==1):    
    print("-----Force in the x y direction at node------")
    F_tainut = int(input())

    Fx_nut= int(input('F(x)' +str(F_tainut)+':'))
    Fy_nut= int(input('F(y)' +str(F_tainut)+':'))

    Fu[(2*F_tainut-2)]=Fu[(2*F_tainut-2)]+Fx_nut
    Fu[(2*F_tainut-1)]=Fu[(2*F_tainut-1)]+Fy_nut

    ss.point_load(node_id=F_tainut,Fx=Fx_nut,Fy=Fy_nut)
#-----------------------------------------------------

K = np.zeros([DOFs,DOFs])
L = np.zeros((NoE,1))
c = np.zeros((NoE,1))
s = np.zeros((NoE,1))

#-----------------Stiffness---------------------------
K=stiffNess2DTruss(NoE,EL,NL,L,c,s,K,E,A)


#---------------------Nhập tải dọc phần tử----------------------
loadE=[]#Luu phan tu co tai
giatri_Loads=[]

print("-------Number of elements have axial load--------")
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

ss.show_structure()


#-----------------Tải dọc phân tử--------------
q = axialforce(loadE,giatri_Loads,c,s,L,DOFs,EL)


#-------------------Displacement-----------------
print("---------Displacement-----------")
dis=displacementCal(q,Fu,K,DOFs,BC)
print(dis)#Chuyen vi

#-----------------Reactions---------------- 
print("---------Reactions-----------")
displacement = np.zeros((DOFs,1))
j=0
for i in range(DOFs):
    if(BC[i]==0):
        displacement[i]=displacement[i]+dis[j]
        j=j+1

reaction=np.dot(K,displacement)-Fu-q
print(np.round(reaction,1))

#---------------Noiluc---------------------
print("-----------Noiluc------------")
NoilucE=[]
for i in range(NoE):
    us=np.zeros((4,1))

    nn1 = int(EL[i,0]) #1
    nn2 = int(EL[i,1]) #2
    cc1= c[i]
    ss1= s[i]
    Ll1= L[i]

    us[0]=us[0]+displacement[2*nn1-2]
    us[1]=us[1]+displacement[2*nn1-1]
    us[2]=us[2]+displacement[2*nn2-2]
    us[3]=us[3]+displacement[2*nn2-1]
    S=np.matrix([-cc1,-ss1,cc1,ss1])

    Noiluc= (E*A/Ll1) *np.matmul(S.flatten(),us)
    print('---Phần tử ' + str(i+1) + '---')
    print(Noiluc)
    NoilucE.append(Noiluc)
NoilucE=np.asarray(NoilucE)
# print(NoilucE.flatten())

print("--------------Stress---------------)")
stress=NoilucE/A
print(stress.flatten())


ss.solve()
 
ss.show_axial_force()

ss.show_reaction_force()

ss.show_displacement(scale=0.03)