# -*- coding:utf-8 -*-
#--------------------------------------------------------------#
#                                                              #
# Ce fichier permet d'utiliser simplement le programme POL.py  #
# Les parametres à modifier sont situés au début du programme  #
#                                                              #
#--------------------------------------------------------------#


nbrValeurs = 0    # 0 pour un nombre infini de valeurs
intervalTemps = 0.25

circle = 1   #1 ou 2

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
    valeur_Max = 0
    valeur_Min = 0
    while 1:
        os.system('python pol.py -p ' + port + ' -o ' + macadress + ' -w ' + macadress)
        f = open("TMP~", "r")
        print(float(f.read()))
        time.sleep(intervalTemps)
            
else :
    for i in range(nbrValeurs) :
        a = os.system('python pol.py -p ' + port + ' -o ' + macadress + ' -w ' + macadress)
        print(a)
        time.sleep(intervalTemps)