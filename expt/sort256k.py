import struct

from mergecommon import mergecommonsubseq

PAGE = 256*1024
SEQSIZE = 4

def compress(page):

    data = []

    pagelen = len(page)

    pagedata = [ page[i:min(i+SEQSIZE,pagelen)] for i in range(0, pagelen, SEQSIZE)]

    # 10% larger file
    #pagedata = mergecommonsubseq(pagedata)

    offset = 0
    for i in range(len(pagedata)):
        data.append((pagedata[i], offset/4))
        offset += len(pagedata[i])

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

def writedict(outdat, datadict):
            for dat in datadict:
                outdat.write(dat[0])

                length = len(dat[1])
                outdat.write(struct.pack('H', length))
                try:
                    outdat.write(struct.pack('%sH' % len(dat[1]), *dat[1]))
                except (struct.error):                    
                    print dat[1]

with open('../doc/ebat.csv', 'r') as batdat:
    with open('out.batz', 'wb') as outdat:
        buffer = batdat.read(PAGE)
        while buffer:
            datadict = compress(buffer)
            writedict(outdat, datadict)
            buffer = batdat.read(PAGE)
