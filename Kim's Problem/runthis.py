import os

dir="C:\\cpp\\tests\\"

in_0=""
in_1=".in"

out_0=".a"
out_1=".sol"

zero_prefix = False;


def play(str):
      i=0
      while(i<len(str) and str[i]=='0'): i=i+1
      if(i==len(str)): return ""
      return str[i:];

for subdir, __, files in os.walk(dir):
    for file in files:
        if((len(in_0)==0 and file.find('.')==-1) or (len(in_0)>0 and len(file)>len(in_0) and file[-len(in_0):]==in_0)):
                f0=open(os.path.join(subdir,file),'r');
                f1=open((os.path.join(subdir,play(file)[:len(file) if len(in_0)==0 else -len(in_0)]+in_1)),'w')
                f1.write(f0.read())
                f0.close()
                os.remove(os.path.join(subdir,file))
        if((len(out_0)==0 and file.find('.')==-1) or (len(out_0)>0 and len(file)>len(out_0) and file[-len(out_0):]==out_0)):
                f0=open(os.path.join(subdir,file),'r');
                f1=open((os.path.join(subdir,play(file)[:len(file) if len(out_0)==0 else -len(out_0)]+out_1)),'w')
                f1.write(f0.read())
                f0.close()
                os.remove(os.path.join(subdir,file))
                
                
