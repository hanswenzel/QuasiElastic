#!/usr/bin/env python

import re
import sys
import json

filename = sys.argv[1]
f=  open(filename, 'r')
lines = map(lambda x : x.strip(), f.readlines())

if 'ela' in filename:
  yaxis = "\sigma_{el}, mb"
elif 'inl' in filename:
  yaxis = '\sigma_{in}, mb'
elif 'tot' in filename:
  yaxis = '\sigma_{tot}, mb'

if '-n' in filename:
  beamparticle = 'neutron'
elif '-p' in filename:
  beamparticle = 'proton'


f.close()
tablename = "Nonename" if len(sys.argv) <= 2 else sys.argv[2]
tables = []

tmp = []
for l in lines:
  if 'hline' not in l:
    tmp.append(l)
  else:
    tables.append(tmp)
    tmp = []

tables = filter(lambda x: 'Nucleus' not in x[0], tables)
tables = filter(lambda x: 'cite' in ' '.join(x), tables)

def parseXY(xraw, coeff = 1):
  if '\pm' in xraw:
    xval = xraw.split('\pm')[0].strip()
    xerrp = xraw.split('\pm')[1].strip()
    xerrm = xerrp
  elif len(re.findall('(.*)\^{(.+)}_{(.+)}',xraw)) != 0:
    r = re.findall('(.*)\^{(.+)}_{(.+)}',xraw)
    xval = r[0][0]
    xerrp = r[0][1]
    xerrm = str(abs(float(r[0][2])))
  elif len(re.findall('(.*)\^{(.+)}.*',xraw)) != 0:
    r = re.findall('(.*)\^{.*}.*',xraw)
    xval = r[0]
    xerrp = 0
    xerrm = 0
  else:
    xval = 0 if xraw.strip() == "" else xraw.strip()
    xval = xval
    xerrp = 0
    xerrm = 0
  def post(s):
    s = str(s)
    s = re.sub('[<>]|\\[gl]eq?|\\cong|\\\\sim', '', s)
    if len(re.findall('(.*)\^{.+\)}.*',s)) != 0:
      r = re.findall('(.*)\^{.*\)}.*',s)
      s = r[0]
    if '\geq' in s:
      s = s.replace('\geq', '')
    if '\ge' in s:
      s = s.replace('\ge', '')
    if '\eq' in s:
      s = s.replace('\eq', '')
    if '\e' in s:
      s = s.replace('\e', '')
    if '\sim' in s:
      s = s.replace('\sim', '')
    if '\cong' in s:
      s = s.replace('\cong', '')
    if '\cdot' in s:
      s = s.replace('\cdot', '')
    if '^' in s:
      x, y = s.split('^')
      s = str(float(x) ** float(re.sub('[{}]', '', y)))
    return s
  xval = post(xval)
  xerrp = post(xerrp)
  xerrm = post(xerrm)
  xval = float(xval) * coeff
  xerrp = float(xerrp) * coeff
  xerrm = float(xerrm) * coeff
  return (xval, xerrp, xerrm)

tabledata = []
for table in tables:
#  print "="*80
#  coeff = 1
  points = []
  for line in table:
    cells = line.split('&') 
    if cells[0] != "":
      r = re.findall('.*\^{?(.+)}?\$(.+).*', cells[0].strip())
      if len(r) != 0:
        mat = r[0][1].strip()
        mass =  re.sub('[{}]', '', r[0][0].strip())
        target = "{0}{1}".format(mat, mass).strip()
    if len(filter(lambda x: 'MeV' in x, cells)) != 0:
      coeff = 1
    if len(filter(lambda x: 'GeV' in x, cells)) != 0:
      coeff = 1000
    if len(filter(lambda x: 'TeV' in x, cells)) != 0:
      coeff = 1000 * 1000
    try:
      # parse x
      if '$' in cells[1]:
        xraw = cells[1].split('$')[1]
      else:
        xraw = cells[1].split()[0]
      if '$' in cells[2]:
        yraw = cells[2].split('$')[1]
      else:
        yraw = cells[2].split()[0]
      if ")}" in xraw or ")}" in yraw:
        xraw = re.sub("\^{[0-9]+\)}", "", xraw)
        yraw = re.sub("\^{[0-9]+\)}", "", yraw)
      xraw = xraw.replace('(','').replace(')','')
      x = parseXY(xraw, coeff)
      yraw = yraw.replace('(','').replace(')','')
      y = parseXY(yraw) 
      if x[0] == 0 or y[0] == 0:
        continue
      if 'cite' in cells[-1]:
        cite_id = re.findall('.*{(.+)}', cells[-1])[0]
        cite_id = cite_id.split(',')
  #    print target, cite_id
      points.append((x,y, cite_id))
    except Exception as e:
      sys.stderr.write("# cannot parse line:\n {0} \n ERROR: {1} \n".format(line, str(e)))
  tabledata.append((target, points))

# join tables with the same target
newtd = []
for t in sorted(set(map(lambda x: x[0], tabledata))):
  newd = []
  [newd.extend(x[1]) for x in tabledata if x[0] == t]
  newtd.append( (t, newd )
  )
tabledata = newtd

type = 'total'
particle = 'n'


# YODA TEMPLATE
def toYODA(target, beamparticle, yaxis, tabledata):
  fmt = """
BEGIN YODA_SCATTER2D {path}
Path={path}
Title="{title}"
Type=Scatter2D
Observable="{observable}"
Reaction="{reaction}"
Target="{target}"
BeamParticle="{beamparticle}"
XAxis="{xaxis}"
YAxis="{yaxis}"
# MeV
# xval   xerr-   xerr+   yval    yerr-   yerr+
{data}
END YODA_SCATTER2D"""
  datastr = ""
  for r in tabledata:
    datastr += "{0} {1} {2} {3} {4} {5}\n".format(r[0][0], r[0][1], r[0][2], r[1][0], r[1][1], r[1][2])
  path = "Barashenkov_{0}_{1}+{2}".format(yaxis, beamparticle, target)
  title = "cross sections for nucleon induced reactions, total, {0}, {1}".format(beamparticle, target)
  xaxis = "T, MeV"
  observable=0
  if 'el' in yaxis:
    observable += "elastic cross section"
  elif "in" in yaxis:
    observable += "inelastic cross section"
  elif "tot" in yaxis:
    observable += "total cross section"
  reaction="Myreaction"
  return fmt.format(path=path, title=title, observable=observable,
    reaction=reaction, target=target, beamparticle=beamparticle, xaxis=xaxis, yaxis=yaxis, data=datastr)


# Interchange format
def toIFormat(target, beamparticle, yaxis, tabledat):
  fmt = """
{
  "reactionlnk": 4,
  "referencelnk": 70,
  "observablelnk": null,
  "secondarylnk": 0,
  "testlnk": null,
  "accesslnk": 1,
  "beamlnk": "",
  "mcdetaillnk": 1,
  "imageblobslnk": null,
  "scoreslnk": 2,
  "datatable": {
    "nbins": [
      
    ],
    "val": [
      
    ],
    "binMin": [
      
    ],
    "datatypeslnk": null,
    "errSysMinus": [
      
    ],
    "errStatMinus": [
      
    ],
    "axisTitle": [
      
    ],
    "binMax": [
      
    ],
    "npoints": null,
    "title": "",
    "errStatPlus": [
      
    ],
    "errSysPlus": [
      
    ]
  },
  "targetlnk": ""
}"""

  Targetdict = dict({'Ag107.9':47, 
      'Al27':13, 
      'B10.8':5, 
      'Be9':4, 
      'Bi209':83, 
      'C12':6, 
      'Ca40.1':20, 
      'Cd112.4':48, 
      'Co58.9':27, 
      'Cu63.5':29, 
      'Fe55.8':26, 
      'H3':289, 
      'He3':290, 
      'He4':2, 
      'Li6':285, 
      'Li6.9':3, 
      'Mg24.3':12, 
      'N14':7, 
      'Ni58.7':28, 
      'O16':8, 
      'Pb207.2':82, 
      'Pb208':288, 
      'S32.1':16, 
      'Sn118.7':50, 
      'Th232':90, 
      'Ti47.9':22, 
      'U238':92,
      'Be7':291,
      'Au197':79,
      'Air15_7.2':104,
      'Ar39.9':18,
      'Cl35.5':17,
      'Li7':286,
      'B10.2':291,
      'Ar40':18,
      'As75':33,
      'Fe55.9':26,
      'Si28.1':14,
      'Ba137.2':294,
      'Ba137.3':56,
      'B10':293,
      'Ne20.2':10,
      'Ca40':20,
      'Ca44':295,
      'B11':5,
      'Zr90':296,
      'Ce140':58,
      'Ca48':297,
      'Br79.1':298,
      'Cr52':24,
      'Co59':27,
      'Br79.9':35,
      'F19':9,
      'Cu63':29,
      'C13':299,
      'Hg200.6':80,
      'Cu65':301,
      'Ce140.1':58,
      'I126.9':53,
      'Dy162.5':66,
      'Ce142':302,
      'P31':15,
      'Er167.3':68,
      'Ga69.7':31,
      'S32':16,
      'Eu152':63,
      'Ge72.6':32,
      'Sb121.8':51,
      'Fe54':303,
      'Se79':34,
      'Fe56':304,
      'K39.1':19,
      'In114.8':49,
      'Ta180.9':73,
      'Fe57':305,
      'Kr83.8':36,
      'W183.9':74,
      'Fe58':306,
      'La138.9':57,
      'Zr91.2':40,
      'Gd157.3':64,
      'La139':57,
      'Hf178.5':72,
      'Mn54.9':25,
      'Ho164.9':67,
      'Mo95.8':42,
      'Ir192.2':77,
      'Nb92.9':41,
      'Mg24':12,
      'Ne23':307,
      'Mo95.9':42,
      'Na23':11,
      'Ni60':309,
      'Ni58':308,
      'Nd144.3':60,
      'Pb206':310,
      'Ne22':311,
      'Pd106.4':46,
      'Ni62':312,
      'Ni64':313,            
      'Pr140.9':59,
      'Pr141':59,
      'Re186.2':75,
      'Pu239':314,
      'Pu242':315,
      'Rh102.9':45,  
      'Pt195.1':78,
      'Sc45':21,
      'Sm150.4':62,
      'Te127.6':52,
      'Sn116':316,
      'Sn117':317,
      'Sn118':319,
      'Sn119':320,
      'Sn120':287,                     
      'Y88.9':39,             
      'U235':318,
      'U233':326,          
      'Tb158.9':65,              
      'V50.9':23,
      'Ti46':323,
      'Ti48':324,
      'Ti49':326,
      'Ti50':327,
      'V51':23,         
      'Tl204.4':81,              
      'Tl203.5':81,
      'Tm168.9':69,
      'Xe131.3':54,
      'Yb173':70,
      'Zn64':329,
      'Zn65':330,
      'Zn66':331,
      'Zn68':332,
      'Zr91':333,
      'Zr92':334,
      'Zr94':335,
      'Zr96':336,              
      'Zn65.4':30})
  Beamdict = dict({'neutron':81,'proton':80}) 
  j = json.loads(fmt)
  j['datatable']['title'] = "cross sections for nucleon induced reactions, total, {0}, {1}".format(beamparticle, target)
  j['datatable']['npoints'] = len(tabledat)
  j['datatable']['val'] = map(lambda x: x[0][0], tabledat) + map(lambda x: x[1][0], tabledat)
  j['datatable']['errStatPlus'] = map(lambda x: x[0][2], tabledat) + map(lambda x: x[1][2], tabledat)
  j['datatable']['errStatMinus'] = map(lambda x: x[0][1], tabledat) + map(lambda x: x[1][1], tabledat)

  xaxis = "T, MeV"
  observable=0
  if 'el' in yaxis:
    observable = 11
  elif "in" in yaxis:
    observable = 12
  elif "tot" in yaxis:
    observable = 10
  j['observablelnk'] = observable
'val'  j['datatable']['axisTitle'] = [xaxis, yaxis]
  j['targetlnk'] = Targetdict[target]
  j['beamlnk'] = Beamdict[beamparticle]
  
  #reaction="Myreaction"
  #j['reaction']['rname'] = reaction
  j['datatable']['datatypeslnk'] = 1001  # why?
  #j['beam']['ParticleIds'] = [beamparticle]
  return j


if len(sys.argv) >= 3:
  mode = sys.argv[2]
else:
  mode = "iformat" 

if mode.lower() == "iformat":
  jj = []
  for t in tabledata:
    jj.append(toIFormat(t[0], beamparticle, yaxis, t[1]))
  print json.dumps({"ResultList": jj}, indent=2)
else:
  for t in tabledata:
    print toYODA(t[0], beamparticle, yaxis, t[1])
