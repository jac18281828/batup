import csv, math

lasttrade = {}

N = 0

# for mean
totaltimedelta = 0.0
totalreptimedelta = 0.0
totalpricedelta = 0.0

# for variance
timedeltavar = 0.0
reptimedeltavar = 0.0
pricedeltavar = 0.0

TIMECOL = 4
REPTIMECOL = 5
PRICECOL = 6

with open('../doc/ebat.csv', 'r') as batcsv:
    reader = csv.reader(batcsv)
    for rows in reader:
        k = rows[0]
        v = rows[1:]
        time = rows[TIMECOL]
        reptime = rows[REPTIMECOL]
        price   = rows[PRICECOL]
        
        if k in lasttrade.keys():
            N += 1;

            timedelta = float(time) - float(lasttrade[k][TIMECOL-1])
            reptimedelta = float(reptime) - float(lasttrade[k][REPTIMECOL-1])
            pricedelta = float(price) - float(lasttrade[k][PRICECOL-1])
            
            totaltimedelta += timedelta
            totalreptimedelta += reptimedelta
            totalpricedelta += pricedelta

            meantimedelta = totaltimedelta/N
            meanreptimedelta = totalreptimedelta/N
            meanpricedelta = totalpricedelta/N
            
            timedeltavar += math.pow(timedelta - meantimedelta, 2.0)
            reptimedeltavar += math.pow(reptimedelta - meanreptimedelta, 2.0)
            pricedeltavar += math.pow(pricedelta - meanpricedelta, 2.0)
        
        lasttrade[k] = v

timedeltavar /= (N-1)
reptimedeltavar /= (N-1)
pricedeltavar /= (N-1)

timedeltasdev = math.sqrt(timedeltavar)
reptimedeltasdev = math.sqrt(reptimedeltavar)
pricedeltasdev = math.sqrt(pricedeltavar)

print "N = %d" % N
print "<dtime> = %f" % (totaltimedelta/N)
print "<dreptime> = %f" % (totalreptimedelta/N)
print "<dprice> = %f" % (totalpricedelta/N)

print "time sdev = %f" % (timedeltasdev)
print "reptime sdev = %f" % (reptimedeltasdev)
print "price sdev = %f" % (pricedeltasdev)
