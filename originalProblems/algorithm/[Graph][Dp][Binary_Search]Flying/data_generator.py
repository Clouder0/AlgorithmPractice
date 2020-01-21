from cyaron import *

def init():
    global mindis,maxdis,minweight,maxweight,minn,maxn,minm,maxm
    mindis = 0
    maxdis = 1e9
    minweight = 0
    maxweight = 1e9
    minn = 0
    maxn = 1e5
    minm = 0
    maxm = 1e6
     

def op(x):
    return "%d %d %d %d" %(x.start,x.end,x.weight[0],x.weight[1])

def wg():
    global mindis,maxdis,minweight,maxweight
    return [randint(mindis,maxdis),randint(minweight,maxweight)]

weights1 = ati([1e9,1e8,1e7,1e6,1e5,1e4,12354])
rw1 = 6
def wg_1():
    global mindis,maxdis
    return [randint(mindis,maxdis),weights1[randint(0,6)]]

weights = []
rg = 0
def iwg2(x):
    global minweight,maxweight,rg
    weights.clear()
    rg = x-1
    for i in range(0,x):
        weights.append(randint(minweight,maxweight))

def wg_2():
    global mindis,maxdis,rg
    return [randint(mindis,maxdis),weights[randint(0,rg)]]

def out():
    global n,m,k,s,t,test_data,graph
    test_data.input_writeln(n,m,k,s,t)
    for j in range(0,k):
        test_data.input_write(randint(1,n))
    test_data.input_writeln()
    test_data.input_writeln(graph.to_str(shuffle=True,output=op))
    test_data.output_gen("code.exe")

def getm():
    global m,graph
    m = 0
    for edge in graph.iterate_edges():
        m += 1

global mindis,maxdis,minweight,maxweight,minn,maxn,minm,maxm,n,m,s,t,k,graph,test_data
"""
test_data = IO(file_prefix = "Flying",data_id = 11)
init()
n = 65612
m = 153212
k = 8
s = randint(1,n)
t = randint(1,n)
minweight = 1e6
maxweight = 1e9
mindis = 1e6
maxdis = 1e9
graph = Graph.graph(n,m,weight_gen = wg)
out()

test_data = IO(file_prefix = "Flying",data_id = 12)
init()
n = 94567
m = 874231
k = 10
s = randint(1,n)
t = randint(1,n)
graph = Graph.graph(n,m,weight_gen = wg)
out()

test_data = IO(file_prefix = "Flying",data_id = 13)
init()
n = 100000
k = 10
s = randint(1,n)
t = randint(1,n)
graph = Graph.hack_spfa(n,weight_gen = wg_1)
getm()
out()

test_data = IO(file_prefix = "Flying",data_id = 14)
init()
n = 100000
k = 10
s = randint(1,n)
t = randint(1,n)
graph = Graph.flower(n,weight_gen = wg_1)
getm()
out()

test_data = IO(file_prefix = "Flying",data_id = 14)
init()
n = 100000
m = 1000000
k = 10
s = randint(1,n)
t = randint(1,n)
graph = Graph.graph(n,m,weight_gen = wg)
out()

test_data = IO(file_prefix = "Flying",data_id = 15)
init()
n = 100000
m = 1000000
k = 10
s = randint(1,n)
t = randint(1,n)
graph = Graph.graph(n,m,weight_gen = wg_1)
out()

test_data = IO(file_prefix = "Flying",data_id = 16)
init()
n = 100000
m = 1000000
k = 10
s = randint(1,n)
t = randint(1,n)
mindis = 1e8
maxdis = 1e9
minweight = 1e8
maxweight = 1e9
graph = Graph.graph(n,m,weight_gen = wg)
out()

test_data = IO(file_prefix = "Flying",data_id = 17)
init()
n = 100000
k = 10
s = randint(1,n)
t = randint(1,n)
graph = Graph.tree(n,0.3,0.7,weight_gen = wg)
getm()
out()
"""
test_data = IO(file_prefix = "Flying",data_id = 18)
init()
n = 75642
m = 656323
k = 10
s = randint(1,n)
t = randint(1,n)
iwg2(18)
graph = Graph.graph(n,m,weight_gen = wg_2)
out()

test_data = IO(file_prefix = "Flying",data_id = 19)
init()
n = 100000
k = 10
s = randint(1,n)
t = randint(1,n)
graph = Graph.hack_spfa(n,weight_gen = wg)
getm()
out()

test_data = IO(file_prefix = "Flying",data_id = 20)
init()
n = 100000
m = 1000000
k = 10
s = randint(1,n)
t = randint(1,n)
graph = Graph.graph(n,m,weight_gen = wg)
out()