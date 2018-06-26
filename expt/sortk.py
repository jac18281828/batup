import struct

PAGE = 1024


##
## Must handle dangling bytes!
##

def compress(page):

    data = []

    pagedata = struct.unpack('%sI' % (len(page)/4), page[:len(page)/4*4])

    for i in range(len(pagedata)):
        data.append((pagedata[i], i))


    data = sorted(data, key=lambda x: x[0])

    # merge down to single sequences
    datadict = [(data[0][0], [data[0][1]])]
    
    for d in data[1:]:
        lastent = datadict[-1]
        if d[0] == lastent[0]:
            lastent[1].append(d[1])
        else:
            datadict.append((d[0], [d[1]]))

    return datadict

with open('../doc/ebat.csv', 'r') as batdat:
    with open('out.batz', 'wb') as outdat:
        buffer = batdat.read(PAGE)
        while buffer:
            datadict = compress(buffer)

            for dat in datadict:
                outdat.write(struct.pack('I', dat[0]))
                outdat.write(struct.pack('B', len(dat[1])))

                outdat.write(struct.pack('%sB' % len(dat[1]), *dat[1]))
            
            buffer = batdat.read(PAGE)

