def mergecommonsubseq(pagedata):
    """Given an array of page sequences, find and merge common subsequences"""

    commonsubseq = {}
    
    pagedatalen = len(pagedata)
    for i in range(pagedatalen):
      if pagedata[i] not in commonsubseq.keys():
        for j in range(i+1, pagedatalen):
            offset = 0
            while offset < 3 and j+offset < pagedatalen and pagedata[i+offset] == pagedata[j+offset]:
                offset += 1
            if offset > 1:
                # this is a common subsequence
                cseq = ''.join(pagedata[i:i+offset])
                if pagedata[i] not in commonsubseq.keys():# or len(commonsubseq[pagedata[i]]) < len(cseq):
                    commonsubseq[pagedata[i]] = cseq
                break

    pagedatalen = len(pagedata)
    pagedataout = []
    soff = 0
    while soff < pagedatalen:
        offset=1
        if pagedata[soff] in commonsubseq.keys():
            while soff+offset < pagedatalen and commonsubseq[pagedata[soff]].startswith(''.join(pagedata[soff:soff+offset])):
                offset += 1
            if offset-1 > 1:
                offset -= 1
                pagedataout.append(''.join(pagedata[soff:soff+offset]))
            else:
                pagedataout.append(''.join(pagedata[soff:soff+offset]))                
        else:
            pagedataout.append(''.join(pagedata[soff:soff+offset]))
        soff += offset

    return pagedataout


#print mergecommonsubseq([ "abc", "def", "hij", "abc", "def"])
#print mergecommonsubseq([ "abc", "def", "hij", "abc", "def", "123", "abc", "def", "123"])


