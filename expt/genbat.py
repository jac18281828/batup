import sys, random

nlines = 1000

if sys.argv > 1:
    nlines = int(sys.argv[1])

syms = [ ]

for a in range(ord('A'), ord('Z')):
    for b in range(ord('A'), ord('Z')):
        for c in range(ord('A'), ord('Z')):
            syms.append(random.choice(["USD", "EUR", "AUD", "GBP", "CAD"]) + "." + chr(a) + chr(b) + chr(c))


time = 6311300000
reptime = 6311300770
price = 97.96
for n in range(nlines):
    sym = random.choice(syms)
    ex  = random.choice(['c','d','e','F','K','m','r','R','S','u','w','x'])
    sd  = random.choice(['B', 'A', 'T'])
    cond = '0'
    time += long(random.random()*4e6)
    reptime += long(random.random()*4e6)
    price += (random.random()-.5)*40.0
    if price < 0.01:
        price += 100
    qty = random.choice([10, 20, 40, 60, 80, 100, 500, 1000, 10000])

    print str(sym) + "," + str(ex) + "," + str(sd) + "," + str(cond) + "," + str(time) + "," + str(reptime) + "," + str(long(price*100.0)/100.0) + "," + str(qty)
    
