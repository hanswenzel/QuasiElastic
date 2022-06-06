#!/usr/bin/env python

import re
import sys
import json
def hasNumbers(inputString):
    return any(char.isdigit() for char in inputString)

filename = sys.argv[1]
match = re.match(r"([a-z]+)([0-9]+)", filename, re.I)
if match:
    items = match.groups()    
    target=items[0]
f=  open(filename, 'r')
lines = map(lambda x : x.strip(), f.readlines())

f.close()
axis = ('Energy loss omega [MeV]', 'd 2 sigma/domega dw [mb/sr MeV]')
parname=[]
parname.append("q")
datatypeslnk=2
title = "{0}(pi,pi)".format(target)
omega=[]
errx=[]
cs1=[]
cs2=[]
cs3=[]
parvalue=[]
errstat1=[]
errstat2=[]
errstat3=[]
columns=0
Targetdict = dict({'Li':285, 
                   'C':6,
                   'Pb':288,
                   'Zr':40,
                   'D':337,
                   'Ca':20})
for l in lines:
    if  l.startswith("#") and "q=" in l: 
        q = l.split("q=")
        for i  in range (1,len(q)):
            parvalue.append(q[i].strip())

    if not l.startswith("#"):
        words = l.split()
        omega.append(float(words[0].strip()))
        errx.append(0.0)
        columns = (len(words)-1)/2
        
        if columns>0 and hasNumbers(words[1]):
            cs1.append(float(words[1].strip()))
            errstat1.append(float(words[2].strip()))
        if  columns>1 and hasNumbers(words[3]):
            cs2.append(float(words[3].strip()))
            errstat2.append(float(words[4].strip()))
        if columns>2 and hasNumbers(words[5]):
            cs3.append(float(words[5].strip()))
            errstat3.append(float(words[6].strip()))
if columns==3:
    data={'ResultList':(
        {
            'trid':1,'testlnk':0,'referencelnk':37,
            'mcdetaillnk':1,'beamlnk':34,
            'targetlnk': Targetdict[target],'observablelnk':21,
            'secondarylnk':0,'reactionlnk':4,
            'parnames':(parname),'parvalues':parvalue[0:1],
            'datatable':({'dtid':1,
                          'datatypeslnk':1000,
                          'title':title,'npoints':len(cs1),
                          'axisTitle':axis,
                          'val':omega[0:len(cs1)]+cs1,'errStatMinus':errx[0:len(cs1)]+errstat1,
                          'errStatPlus':errx[0:len(cs1)]+errstat1,
                          'imageblobslnk':None,'scoreslnk':2,'accesslnk':1           
                      })},
        {'trid':1,'testlnk':0,'referencelnk':37,
         'mcdetaillnk':1,'beamlnk':34,
         'targetlnk': Targetdict[target],'observablelnk':21,
         'secondarylnk':0,'reactionlnk':4,
         'parnames':(parname),'parvalues':parvalue[1:2],
         'datatable':({'dtid':1,
                       'datatypeslnk':1000,
                       'title':title,'npoints':len(cs2),
                       'axisTitle':axis,
                       'val':omega[0:len(cs2)]+cs2,'errStatMinus':errx[0:len(cs2)]+errstat2,
                       'errStatPlus':errx[0:len(cs2)]+errstat2,
                       'imageblobslnk':None,'scoreslnk':2,'accesslnk':1
                   })},
        {'trid':1,'testlnk':0,'referencelnk':37,
         'mcdetaillnk':1,'beamlnk':34,
         'targetlnk': Targetdict[target],'observablelnk':21,
         'secondarylnk':0,'reactionlnk':4,
         'parnames':(parname),'parvalues':parvalue[2:3],
         'datatable':({'dtid':1,
                       'datatypeslnk':1000,
                       'title':title,'npoints':len(cs3),
                       'axisTitle':axis,
                       'val':omega[0:len(cs3)]+cs3,'errStatMinus':errx[0:len(cs3)]+errstat3,
                       'errStatPlus':errx[0:len(cs3)]+errstat3,
                       'imageblobslnk':None,'scoreslnk':2,'accesslnk':1
                   })}
    )
      }

if columns==2:
    data={'ResultList':(
        {
            'trid':1,'testlnk':0,'referencelnk':37,
            'mcdetaillnk':1,'beamlnk':34,
            'targetlnk': Targetdict[target],'observablelnk':21,
            'secondarylnk':0,'reactionlnk':4,
            'parnames':(parname),'parvalues':parvalue[0:1],
            'datatable':({'dtid':1,
                          'datatypeslnk':1000,
                          'title':title,'npoints':len(cs1),
                          'axisTitle':axis,
                          'val':omega[0:len(cs1)]+cs1,'errStatMinus':errx[0:len(cs1)]+errstat1,
                          'errStatPlus':errx[0:len(cs1)]+errstat1,
                          'imageblobslnk':None,'scoreslnk':2,'accesslnk':1           
                      })},
        {'trid':1,'testlnk':0,'referencelnk':37,
         'mcdetaillnk':1,'beamlnk':34,
         'targetlnk': Targetdict[target],'observablelnk':21,
         'secondarylnk':0,'reactionlnk':4,
         'parnames':(parname),'parvalues':parvalue[1:2],
         'datatable':({'dtid':1,
                       'datatypeslnk':1000,
                       'title':title,'npoints':len(cs2),
                       'axisTitle':axis,
                       'val':omega[0:len(cs2)]+cs2,'errStatMinus':errx[0:len(cs2)]+errstat2,
                       'errStatPlus':errx[0:len(cs2)]+errstat2,
                       'imageblobslnk':None,'scoreslnk':2,'accesslnk':1
                   })}
    )
      }
if columns==1:
    data={'ResultList':(
        {
            'trid':1,'testlnk':0,'referencelnk':37,
            'mcdetaillnk':1,'beamlnk':34,
            'targetlnk': Targetdict[target],'observablelnk':21,
            'secondarylnk':0,'reactionlnk':4,
            'parnames':(parname),'parvalues':parvalue[0:1],
            'datatable':({'dtid':1,
                          'datatypeslnk':1000,
                          'title':title,'npoints':len(cs1),
                          'axisTitle':axis,
                          'val':omega[0:len(cs1)]+cs1,'errStatMinus':errx[0:len(cs1)]+errstat1,
                          'errStatPlus':errx[0:len(cs1)]+errstat1,
                          'imageblobslnk':None,'scoreslnk':2,'accesslnk':1           
                      })},
    )
      }

print(json.dumps(data,indent=1))
