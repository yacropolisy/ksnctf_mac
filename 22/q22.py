# -*- coding: utf-8 -*-

for i in range(31):
  s = input()
  for c in s:
    if(c.isupper()):
      print('0,',end="")
    else:
      print('1,',end="")
  print("")
