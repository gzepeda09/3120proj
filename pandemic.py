import matplotlib.pyplot as plt
import numpy as np
import random

flights = { 'San Francisco': ['Los Angeles', 'Phoenix', 'Las Vegas', 'Portland', 'Seattle', 'Salt Lake City'],
 'Los Angeles': ['San Francisco','Phoenix','Las Vegas','Houston','Miami','New York City','Atlanta','Portland','Chicago','Nashville'],
 'Phoenix': ['San Francisco','Los Angeles','Las Vegas','Houston','Salt Lake City'],
 'Las Vegas': ['San Francisco','Los Angeles','Phoenix','Houston','Miami','New York City','Atlanta'],
 'Houston': ['Los Angeles','Phoenix','Las Vegas','Miami','New York City','Atlanta','Chicago','Nashville','Philedelphia','Salt Lake City','Kansas City'],
 'Miami': ['Los Angeles','Phoenix','Las Vegas','Houston','New York City','Atlanta','Chicago','Philedelphia','Milwaukee','Kansas City'],
 'New York City': ['Los Angeles','Las Vegas','Houston','Miami','Atlanta','Chicago','Nashville','Boston','Philedelphia','Detroit','Milwaukee'],
 'Atlanta': ['Los Angeles','Las Vegas','Houston','Miami','New York City','Philedelphia'],
 'Portland': ['San Francisco','Los Angeles','Seattle','Salt Lake City'],
 'Seattle': ['San Francisco','Portland','Salt Lake City'],
 'Chicago': ['Los Angeles','Houston','Miami','New York City'],
 'Nashville': ['Los Angeles','Houston','New York City','Philedelphia'],
 'Boston': ['New York City','Detroit'],
 'Philedelphia': ['Houston','Miami','New York City','Atlanta','Nashville','Detroit'],
 'Detroit': ['New York City','Boston','Philedelphia'],
 'Milwaukee': ['Miami','New York City'],
 'Salt Lake City': ['San Francisco','Phoenix','Houston','Portland','Seattle','Kansas City'],
 'Kansas City': ['Houston','New York City','Salt Lake City']}

flightpath = []
count = 0

IR = 0.7
nIR = 0.3
passengers = random.randrange(330,380)
E = int(passengers * IR)
V = int(E * nIR)
LB = int(E - V)
UB = int(E + V)
infected = random.randrange(LB, UB)
population = 0

cities = list(flights.keys())
Rcity = random.choice(cities)

Pstart = random.choice(cities)
flightpath.append(Pstart)

if Pstart == 'San Francisco':
  nxtcity = str(random.choices(flights[Pstart], weights=(40,5,20,15,15,5), k=1))
  population = 3318000
elif Pstart == 'Los Angeles':
  nxtcity = str(random.choices(flights[Pstart], weights=(8,5,12,15,15,20,12,3,5,5), k=1))
  population = 12488000
elif Pstart == 'Phoenix':
  nxtcity = str(random.choices(flights[Pstart], weights=(15,30,20,30,5), k=1))
  population = 4652000
elif Pstart == 'Las Vegas':
  nxtcity = str(random.choices(flights[Pstart], weights=(10,25,10,15,12,20,8), k=1))
  population = 2839000
elif Pstart == 'Houston':
  nxtcity = str(random.choices(flights[Pstart], weights=(15,6,10,15,15,10,4,10,5,5,5), k=1))
  population = 6603000
elif Pstart == 'Miami':
  nxtcity = str(random.choices(flights[Pstart], weights=(15,5,15,15,20,10,5,5,5,5), k=1))
  population = 6215000
elif Pstart == 'New York City':
  nxtcity = str(random.choices(flights[Pstart], weights=(15,10,15,10,10,7,10,7,6,5,5), k=1))
  population = 18867000
elif Pstart == 'Atlanta':
  nxtcity = str(random.choices(flights[Pstart], weights=(15,15,20,15,30,5), k=1))
  population = 5100000
elif Pstart == 'Portland':
  nxtcity = str(random.choices(flights[Pstart], weights=(30,20,30,20), k=1))
  population = 2197000
elif Pstart == 'Seattle':
  nxtcity = str(random.choices(flights[Pstart], weights=(50,30,20), k=1))
  population = 3489000
elif Pstart == 'Chicago':
  nxtcity = str(random.choices(flights[Pstart], weights=(20,30,20,30), k=1))
  population = 8901000
elif Pstart == 'Nashville':
  nxtcity = str(random.choices(flights[Pstart], weights=(15,35,35,15), k=1))
  population = 1294000
elif Pstart == 'Boston':
  nxtcity = str(random.choices(flights[Pstart], weights=(80,20), k=1))
  population = 4327000
elif Pstart == 'Philedelphia':
  nxtcity = str(random.choices(flights[Pstart], weights=(20,15,30,20,10,5), k=1))
  population = 5756000
elif Pstart == 'Detroit':
  nxtcity = str(random.choices(flights[Pstart], weights=(70,10,20), k=1))
  population = 3521000
elif Pstart == 'Milwaukee':
  nxtcity = str(random.choices(flights[Pstart], weights=(40,60), k=1))
  population = 1448000
elif Pstart == 'Salt Lake City':
  nxtcity = str(random.choices(flights[Pstart], weights=(20,10,30,15,15,10), k=1))
  population = 1192000
elif Pstart == 'Kansas City':
  nxtcity = str(random.choices(flights[Pstart], weights=(40,40,20), k=1))
  population = 1711000
else:
  nxtcity = str(random.choice(flights[Pstart]))
flightpath.append(nxtcity.strip("['']"))

popfrac = infected/population

ndays = 100
dt = 1                           #time step in days
beta = (7.0/10.0)                 #infection rate
gamma = (2.25/10.0)               #recovery rate  

S = np.zeros(ndays)             #susceptible population
I = np.zeros(ndays)             #infected population
R = np.zeros(ndays)             #removed population
t = np.arange(ndays)*dt

I[0] = infected/population                  #initial infective proportion
S[0] = 1.0 - I[0]               #initial susceptible proportion
R[0] = 0.0                      #initial removed proportion

for i in range(ndays-1):
    S[i+1] = S[i] - beta*(S[i]*I[i])*dt
    I[i+1] = I[i] + (beta*S[i]*I[i]-gamma*I[i])*dt
    R[i+1] = R[i] + (gamma*I[i])*dt
    
fig = plt.figure(1); fig.clf()
plt.plot(t,S,'r',lw=3, label='Suceptible')
plt.plot(t,I,'g',lw=3, label='Infected')
plt.plot(t,R,'b',lw=3, label='Recovered')
fig.legend(); plt.xlabel('Days'); plt.ylabel('Fraction of Population'); fig.suptitle(Pstart)
print(I.max())
print("The initial number of infected is")
print(infected)
print( "The number of infected is ")
print(int(I.max() * population))
print(I[0])
print(flightpath)