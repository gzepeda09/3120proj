
""" 
Create a Disease
mortality rate: 20%
lifetime of the virus: 2 days
duration of the infection: 1 week
transmission rate: 70%
"""

import random
import numpy as np

# passenger = random.randrange(300,350,1)
mrate = 0.20
ltime: 2
dinf = 7
trate = 0.70
  
# Creating a name list
name_lst = ['350', '275', '312',
            '200', '150', '320']
  
print(random.choices(name_lst, weights=(
    70, 70, 70, 70, 70, 70), k=1))

flights = np.loadtxt("2dm.txt", dtype=int)
print(flights[0])



exit()

