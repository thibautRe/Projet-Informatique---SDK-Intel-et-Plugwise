# -*- coding:utf-8 -*-
#--------------------------------------------------------------#
#                                                              #
# Ce fichier permet d'utiliser simplement le programme POL.py  #
# Les parametres à modifier sont situés au début du programme  #
#                                                              #
#--------------------------------------------------------------#


nbrValeurs = 0    # 0 pour un nombre infini de valeurs
intervalTemps = 1.

circle = 2   #1 ou 2

#--------------------------------------------------------------#


import os
import time



port = "/dev/ttyUSB0"
if circle == 1 :
    macadress = "000D6F0000998BF3"
else :
    macadress = "000D6F000098FDF2"

origineTemps = time.time()

if nbrValeurs <= 0 :
    while 1:
        os.system('python pol.py -p ' + port + ' -o ' + macadress + ' -w ' + macadress)
        time.sleep(intervalTemps)
            
else :
    for i in range(nbrValeurs) :
        os.system('python pol.py -p ' + port + ' -o ' + macadress + ' -w ' + macadress)
        time.sleep(intervalTemps)