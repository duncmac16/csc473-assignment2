system partSys dim 2
system partSys particle 0 1 0 1 0 0 0 0 
simulator partSim link partSys 1
simulator partSim spring 0 1 20 20 .5
#simulator partSim integration euler .01
simulator partSim integration symplectic .01
#simulator partSim integration verlet .000001
simulator partSim ground 1000 50
simulator partSim gravity -9.8
simulator partSim drag 0.99







