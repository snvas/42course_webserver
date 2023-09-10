#!/usr/local/bin/python

import time
import random
import math
#def atualizartela11() :
#    for linhas in range(0,30):
#        print('(',end = '')
#        for linha in range(0,60):
#            print('{}'.format(lista[linha + (60 * linhas)]) , end = '')
#        print(')')

def atualizartela() :
    for linhas in range(0,30):
        print(f'({lista[0 + (60 * linhas)]}{lista[1 + (60 * linhas)]}{lista[2 + (60 * linhas)]}{lista[3 + (60 * linhas)]}{lista[4 + (60 * linhas)]}{lista[5 + (60 * linhas)]}{lista[6 + (60 * linhas)]}{lista[7 + (60 * linhas)]}{lista[8 + (60 * linhas)]}{lista[9 + (60 * linhas)]}{lista[10 + (60 * linhas)]}{lista[11 + (60 * linhas)]}{lista[12 + (60 * linhas)]}{lista[13 + (60 * linhas)]}{lista[14 + (60 * linhas)]}{lista[15 + (60 * linhas)]}{lista[16 + (60 * linhas)]}{lista[17 + (60 * linhas)]}{lista[18 + (60 * linhas)]}{lista[19 + (60 * linhas)]}{lista[20 + (60 * linhas)]}{lista[21 + (60 * linhas)]}{lista[22 + (60 * linhas)]}{lista[23 + (60 * linhas)]}{lista[24 + (60 * linhas)]}{lista[25 + (60 * linhas)]}{lista[26 + (60 * linhas)]}{lista[27 + (60 * linhas)]}{lista[28 + (60 * linhas)]}{lista[29 + (60 * linhas)]}{lista[30 + (60 * linhas)]}{lista[31 + (60 * linhas)]}{lista[32 + (60 * linhas)]}{lista[33 + (60 * linhas)]}{lista[34 + (60 * linhas)]}{lista[35 + (60 * linhas)]}{lista[36 + (60 * linhas)]}{lista[37 + (60 * linhas)]}{lista[38 + (60 * linhas)]}{lista[39 + (60 * linhas)]}{lista[40 + (60 * linhas)]}{lista[41 + (60 * linhas)]}{lista[42 + (60 * linhas)]}{lista[43 + (60 * linhas)]}{lista[44 + (60 * linhas)]}{lista[45 + (60 * linhas)]}{lista[46 + (60 * linhas)]}{lista[47 + (60 * linhas)]}{lista[48 + (60 * linhas)]}{lista[49 + (60 * linhas)]}{lista[50 + (60 * linhas)]}{lista[51 + (60 * linhas)]}{lista[52 + (60 * linhas)]}{lista[53 + (60 * linhas)]}{lista[54 + (60 * linhas)]}{lista[55 + (60 * linhas)]}{lista[56 + (60 * linhas)]}{lista[57 + (60 * linhas)]}{lista[58 + (60 * linhas)]}{lista[59 + (60 * linhas)]})')


def muitaslinhas() :
    print('\n \n \n \n \n \n \n \n \n \n \n \n \n \n ')

def muitosiguais() :
    print('==============================================================')



novanova = 1
while (novanova == 1):

#    for iniciobug in range(0,3000):
#        muitaslinhas()

    lista = [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', 
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', 
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',  
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',                                            
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',                                            
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',                                            
    #2
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #3
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #4
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #5
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #6
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #7
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #8
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #9
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #10
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #11
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #12
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #13
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #14
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #15
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #16
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #17
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #18
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #19
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #20
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #21
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #22
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #23
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #24
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #25
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #26
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #27
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #28
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #29
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    #30
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',]
    posicaoinicial = random.randint(0,1799)
    lista[posicaoinicial] = 'O'
    for pontos in range(0,7):
        asd = random.randint(0,1799)
        lista[asd] = '$'
    def fazerabolinhasumir() :
        lista[lista.index('O')] = ' '
    acao = ' '
    pontos = 49 #############
    fase = ''
    contagemvalida = 'sim'
    while True:
        novanova = 2

        bombaantes = lista.count('Q')
        if(lista.count('$') < 7) :
            novamoedinha = random.randint(0,1799)
            if(lista[novamoedinha == ' ']) : lista[novamoedinha] = '$'
        muitaslinhas()
        moedinhasantes = lista.count('$')
        print(f'{pontos} PONTOS                {fase}')
        muitosiguais()
        atualizartela()
        muitosiguais()

    #############################################################
    #               Bloco de movimentaÃ§Ã£o                       #
    #############################################################


        
        repetirmovimento = acao
        acao = input('indique um movimento(wasd)')
        if(acao == ''): acao = repetirmovimento
        if(acao == 'a') or (acao == 'A'):
            if(lista.index('O') - 1 != 59) and (lista.index('O') - 1 != 119) and (lista.index('O') - 1 != 179) and (lista.index('O') - 1 != 239) and (lista.index('O') - 1 != 299) and (lista.index('O') - 1 != 359) and (lista.index('O') - 1 != 419) and (lista.index('O') - 1 != 479) and (lista.index('O') - 1 != 539) and (lista.index('O') - 1 != 599) and (lista.index('O') - 1 != 659) and (lista.index('O') - 1 != 719) and (lista.index('O') - 1 != 779) and (lista.index('O') - 1 != 839) and (lista.index('O') - 1 != 899) and (lista.index('O') - 1 != 959) and (lista.index('O') - 1 != 1019) and (lista.index('O') - 1 != 1079) and (lista.index('O') - 1 != 1139) and (lista.index('O') - 1 != 1199) and (lista.index('O') - 1 != 1259) and (lista.index('O') - 1 != 1319) and (lista.index('O') - 1 != 1379) and (lista.index('O') - 1 != 1439) and (lista.index('O') - 1 != 1499) and (lista.index('O') - 1 != 1559) and (lista.index('O') - 1 != 1619) and (lista.index('O') - 1 != 1679) and (lista.index('O') - 1 != 1739) and (lista.index('O') != 0 ) :
                antesdesumirabolinhaa = lista.index('O')
                fazerabolinhasumir()
                lista[antesdesumirabolinhaa - 1] = 'O'
        elif(acao == 's') or (acao == 'S'):
            if(lista.index('O') != 1740) and (lista.index('O') != 1741) and (lista.index('O') != 1742) and (lista.index('O') != 1743) and (lista.index('O') != 1744) and (lista.index('O') != 1745) and (lista.index('O') != 1746) and (lista.index('O') != 1747) and (lista.index('O') != 1748) and (lista.index('O') != 1749) and (lista.index('O') != 1750) and (lista.index('O') != 1751) and (lista.index('O') != 1752) and (lista.index('O') != 1753) and (lista.index('O') != 1754) and (lista.index('O') != 1755) and (lista.index('O') != 1756) and (lista.index('O') != 1757) and (lista.index('O') != 1758) and (lista.index('O') != 1759) and (lista.index('O') != 1760) and (lista.index('O') != 1761) and (lista.index('O') != 1762) and (lista.index('O') != 1763) and (lista.index('O') != 1764) and (lista.index('O') != 1765) and (lista.index('O') != 1766) and (lista.index('O') != 1767) and (lista.index('O') != 1768) and (lista.index('O') != 1769) and (lista.index('O') != 1770) and (lista.index('O') != 1771) and (lista.index('O') != 1772) and (lista.index('O') != 1773) and (lista.index('O') != 1774) and (lista.index('O') != 1775) and (lista.index('O') != 1776) and (lista.index('O') != 1777) and (lista.index('O') != 1778) and (lista.index('O') != 1779) and (lista.index('O') != 1780) and (lista.index('O') != 1781) and (lista.index('O') != 1782) and (lista.index('O') != 1783) and (lista.index('O') != 1784) and (lista.index('O') != 1785) and (lista.index('O') != 1786) and (lista.index('O') != 1787) and (lista.index('O') != 1788) and (lista.index('O') != 1789) and (lista.index('O') != 1790) and (lista.index('O') != 1791) and (lista.index('O') != 1792) and (lista.index('O') != 1793) and (lista.index('O') != 1794) and (lista.index('O') != 1795) and (lista.index('O') != 1796) and (lista.index('O') != 1797) and (lista.index('O') != 1798) and (lista.index('O') != 1799) :                                            
                antesdesumirabolinhaa = lista.index('O')
                fazerabolinhasumir()
                lista[antesdesumirabolinhaa + 60] = 'O'
        elif(acao == 'd') or (acao == 'D'):
            if(lista.index('O') + 1 != 60) and (lista.index('O') + 1 != 120) and  (lista.index('O') + 1 != 180) and (lista.index('O') + 1 != 240) and (lista.index('O') + 1 != 300) and (lista.index('O') + 1 != 360) and (lista.index('O') + 1 != 420) and (lista.index('O') + 1 != 480) and (lista.index('O') + 1 != 540) and (lista.index('O') + 1 != 600) and (lista.index('O') + 1 != 660) and (lista.index('O') + 1 != 720) and (lista.index('O') + 1 != 780) and (lista.index('O') + 1 != 840) and (lista.index('O') + 1 != 900) and (lista.index('O') + 1 != 960) and (lista.index('O') + 1 != 1020) and (lista.index('O') + 1 != 1080) and (lista.index('O') + 1 != 1140) and (lista.index('O') + 1 != 1200) and (lista.index('O') + 1 != 1260) and (lista.index('O') + 1 != 1320) and (lista.index('O') + 1 != 1380) and (lista.index('O') + 1 != 1440) and (lista.index('O') + 1 != 1500) and (lista.index('O') + 1 != 1560) and (lista.index('O') + 1 != 1620) and (lista.index('O') + 1 != 1680) and (lista.index('O') + 1 != 1740) and (lista.index('O') + 1 != 1800) :
                antesdesumirabolinhaa = lista.index('O')
                fazerabolinhasumir()
                lista[antesdesumirabolinhaa + 1] = 'O'
        elif(acao == 'w') or (acao == 'W'):
            if(lista.index('O') != 0) and (lista.index('O') != 1) and (lista.index('O') != 2) and  (lista.index('O') != 3) and  (lista.index('O') != 4) and  (lista.index('O') != 5) and (lista.index('O') != 6) and (lista.index('O') != 7) and (lista.index('O') != 8) and (lista.index('O') != 9) and (lista.index('O') != 10) and (lista.index('O') != 11) and (lista.index('O') != 12) and (lista.index('O') != 13) and (lista.index('O') != 14) and (lista.index('O') != 15) and (lista.index('O') != 16) and (lista.index('O') != 17) and (lista.index('O') != 18) and (lista.index('O') != 19) and (lista.index('O') != 20) and (lista.index('O') != 21) and (lista.index('O') != 22) and (lista.index('O') != 23) and (lista.index('O') != 24) and (lista.index('O') != 25) and (lista.index('O') != 26) and (lista.index('O') != 27) and (lista.index('O') != 28) and (lista.index('O') != 29) and (lista.index('O') != 30) and (lista.index('O') != 31) and (lista.index('O') != 32) and (lista.index('O') != 33) and (lista.index('O') != 34) and (lista.index('O') != 35) and (lista.index('O') != 36) and (lista.index('O') != 37) and (lista.index('O') != 38) and (lista.index('O') != 39) and (lista.index('O') != 40) and (lista.index('O') != 41) and (lista.index('O') != 42) and (lista.index('O') != 43) and (lista.index('O') != 44) and (lista.index('O') != 45) and (lista.index('O') != 46) and (lista.index('O') != 47) and (lista.index('O') != 48) and (lista.index('O') != 49) and (lista.index('O') != 50) and  (lista.index('O') != 51) and (lista.index('O') != 52) and (lista.index('O') != 53) and (lista.index('O') != 54) and (lista.index('O') != 55) and (lista.index('O') != 56) and (lista.index('O') != 57) and (lista.index('O') != 58) and (lista.index('O') != 59) :
                antesdesumirabolinhaa = lista.index('O')
                fazerabolinhasumir()
                lista[antesdesumirabolinhaa - 60] = 'O'
        else : print('nÃ£o vale, tente de novo')



    ####################################################
    #            Bloco de primeiro nÃ­vel               #
    ####################################################

        if(pontos >= 20) and (pontos < 40):
            fase = 'FASE UM - minas surpresa'                                                  # (marcador de limites do nÃ­vel) 
            bomba = random.randint(0,1799)                      # (seleÃ§Ã£o aleatÃ³ria de algum lugar)
            if(bombaantes == lista.count('Q') + 1) :            # (identifiador de corrompimento de uma bomba \ efeito explosivo grÃ¡fico \ final do jogo)
                if(lista.index('O') + 1 != 60) and (lista.index('O') + 1 != 120) and  (lista.index('O') + 1 != 180) and (lista.index('O') + 1 != 240) and (lista.index('O') + 1 != 300) and (lista.index('O') + 1 != 360) and (lista.index('O') + 1 != 420) and (lista.index('O') + 1 != 480) and (lista.index('O') + 1 != 540) and (lista.index('O') + 1 != 600) and (lista.index('O') + 1 != 660) and (lista.index('O') + 1 != 720) and (lista.index('O') + 1 != 780) and (lista.index('O') + 1 != 840) and (lista.index('O') + 1 != 900) and (lista.index('O') + 1 != 960) and (lista.index('O') + 1 != 1020) and (lista.index('O') + 1 != 1080) and (lista.index('O') + 1 != 1140) and (lista.index('O') + 1 != 1200) and (lista.index('O') + 1 != 1260) and (lista.index('O') + 1 != 1320) and (lista.index('O') + 1 != 1380) and (lista.index('O') + 1 != 1440) and (lista.index('O') + 1 != 1500) and (lista.index('O') + 1 != 1560) and (lista.index('O') + 1 != 1620) and (lista.index('O') + 1 != 1680) and (lista.index('O') + 1 != 1740) and (lista.index('O') + 1 != 1800) :
                    lista[lista.index('O') + 1] = '#'
                if(lista.index('O') - 1 != 59) and (lista.index('O') - 1 != 119) and (lista.index('O') - 1 != 179) and (lista.index('O') - 1 != 239) and (lista.index('O') - 1 != 299) and (lista.index('O') - 1 != 359) and (lista.index('O') - 1 != 419) and (lista.index('O') - 1 != 479) and (lista.index('O') - 1 != 539) and (lista.index('O') - 1 != 599) and (lista.index('O') - 1 != 659) and (lista.index('O') - 1 != 719) and (lista.index('O') - 1 != 779) and (lista.index('O') - 1 != 839) and (lista.index('O') - 1 != 899) and (lista.index('O') - 1 != 959) and (lista.index('O') - 1 != 1019) and (lista.index('O') - 1 != 1079) and (lista.index('O') - 1 != 1139) and (lista.index('O') - 1 != 1199) and (lista.index('O') - 1 != 1259) and (lista.index('O') - 1 != 1319) and (lista.index('O') - 1 != 1379) and (lista.index('O') - 1 != 1439) and (lista.index('O') - 1 != 1499) and (lista.index('O') - 1 != 1559) and (lista.index('O') - 1 != 1619) and (lista.index('O') - 1 != 1679) and (lista.index('O') - 1 != 1739) and (lista.index('O') != 0 ) :
                    lista[lista.index('O') - 1] = '#'
                if(lista.index('O') != 1739) and (lista.index('O') != 1740) and (lista.index('O') != 1741) and (lista.index('O') != 1742) and (lista.index('O') != 1743) and (lista.index('O') != 1744) and (lista.index('O') != 1745) and (lista.index('O') != 1746) and (lista.index('O') != 1747) and (lista.index('O') != 1748) and (lista.index('O') != 1749) and (lista.index('O') != 1750) and (lista.index('O') != 1751) and (lista.index('O') != 1752) and (lista.index('O') != 1753) and (lista.index('O') != 1754) and (lista.index('O') != 1755) and (lista.index('O') != 1756) and (lista.index('O') != 1757) and (lista.index('O') != 1758) and (lista.index('O') != 1759) and (lista.index('O') != 1760) and (lista.index('O') != 1761) and (lista.index('O') != 1762) and (lista.index('O') != 1763) and (lista.index('O') != 1764) and (lista.index('O') != 1765) and (lista.index('O') != 1766) and (lista.index('O') != 1767) and (lista.index('O') != 1768) and (lista.index('O') != 1769) and (lista.index('O') != 1770) and (lista.index('O') != 1771) and (lista.index('O') != 1772) and (lista.index('O') != 1773) and (lista.index('O') != 1774) and (lista.index('O') != 1775) and (lista.index('O') != 1776) and (lista.index('O') != 1777) and (lista.index('O') != 1778) and (lista.index('O') != 1779) and (lista.index('O') != 1780) and (lista.index('O') != 1781) and (lista.index('O') != 1782) and (lista.index('O') != 1783) and (lista.index('O') != 1784) and (lista.index('O') != 1785) and (lista.index('O') != 1786) and (lista.index('O') != 1787) and (lista.index('O') != 1788) and (lista.index('O') != 1789) and (lista.index('O') != 1790) and (lista.index('O') != 1791) and (lista.index('O') != 1792) and (lista.index('O') != 1793) and (lista.index('O') != 1794) and (lista.index('O') != 1795) and (lista.index('O') != 1796) and (lista.index('O') != 1797) and (lista.index('O') != 1798) and (lista.index('O') != 1799) :                                            
                    lista[lista.index('O') + 60] = '#'
                if(lista.index('O') != 0) and (lista.index('O') != 1) and (lista.index('O') != 2) and  (lista.index('O') != 3) and  (lista.index('O') != 4) and  (lista.index('O') != 5) and (lista.index('O') != 6) and (lista.index('O') != 7) and (lista.index('O') != 8) and (lista.index('O') != 9) and (lista.index('O') != 10) and (lista.index('O') != 11) and (lista.index('O') != 12) and (lista.index('O') != 13) and (lista.index('O') != 14) and (lista.index('O') != 15) and (lista.index('O') != 16) and (lista.index('O') != 17) and (lista.index('O') != 18) and (lista.index('O') != 19) and (lista.index('O') != 20) and (lista.index('O') != 21) and (lista.index('O') != 22) and (lista.index('O') != 23) and (lista.index('O') != 24) and (lista.index('O') != 25) and (lista.index('O') != 26) and (lista.index('O') != 27) and (lista.index('O') != 28) and (lista.index('O') != 29) and (lista.index('O') != 30) and (lista.index('O') != 31) and (lista.index('O') != 32) and (lista.index('O') != 33) and (lista.index('O') != 34) and (lista.index('O') != 35) and (lista.index('O') != 36) and (lista.index('O') != 37) and (lista.index('O') != 38) and (lista.index('O') != 39) and (lista.index('O') != 40) and (lista.index('O') != 41) and (lista.index('O') != 42) and (lista.index('O') != 43) and (lista.index('O') != 44) and (lista.index('O') != 45) and (lista.index('O') != 46) and (lista.index('O') != 47) and (lista.index('O') != 48) and (lista.index('O') != 49) and (lista.index('O') != 50) and  (lista.index('O') != 51) and (lista.index('O') != 52) and (lista.index('O') != 53) and (lista.index('O') != 54) and (lista.index('O') != 55) and (lista.index('O') != 56) and (lista.index('O') != 57) and (lista.index('O') != 58) and (lista.index('O') != 59) :
                    lista[lista.index('O') - 60] = '#'
                time.sleep(0.125)

                for estourofracionado in range(0,30) :

                    if(estourofracionado <= 5) : rang = 2000
                    if(estourofracionado <= 10) and (estourofracionado > 6) : rang = 125
                    if(estourofracionado <= 15) and (estourofracionado > 11) : rang = 75
                    if(estourofracionado <= 30) and (estourofracionado > 16) : rang = 50

                    for linhadeestouro in range(0,rang) :
                        explosao = random.randint(0,1799)

                        if(lista.index('O') != explosao) :
                            if(explosao != 59) and (explosao != 119) and (explosao != 179) and (explosao != 239) and (explosao != 299) and (explosao != 359) and (explosao != 419) and (explosao != 479) and (explosao != 539) and (explosao != 599) and (explosao != 659) and (explosao != 719) and (explosao != 779) and (explosao != 839) and (explosao != 899) and (explosao != 959) and (explosao != 1019) and (explosao != 1079) and (explosao != 1139) and (explosao != 1199) and (explosao != 1259) and (explosao != 1319) and (explosao != 1379) and (explosao != 1439) and (explosao != 1499) and (explosao != 1559) and (explosao != 1619) and (explosao != 1679) and (explosao != 1739) and (explosao != 1799) :
                                if(lista[explosao + 1] == '#') : lista[explosao] = '#'
                            if(explosao != 0) and (explosao != 60) and (explosao != 120) and (explosao != 180) and (explosao != 240) and (explosao != 300) and (explosao != 360) and (explosao != 420) and (explosao != 480) and (explosao != 540) and (explosao != 600) and (explosao != 660) and (explosao != 720) and (explosao != 780) and (explosao != 840) and (explosao != 900) and (explosao != 960) and (explosao != 1020) and (explosao != 1080) and (explosao != 1140) and (explosao != 1200) and (explosao != 1260) and (explosao != 1320) and (explosao != 1380) and (explosao != 1440) and (explosao != 1500) and (explosao != 1560) and (explosao != 1620) and (explosao != 1680) and (explosao != 1740) :  
                                if(lista[explosao - 1] == '#') : lista[explosao] = '#'
                            if(explosao != 1739) and (explosao != 1740) and (explosao != 1741) and (explosao != 1742) and (explosao != 1743) and (explosao != 1744) and (explosao != 1745) and (explosao != 1746) and (explosao != 1747) and (explosao != 1748) and (explosao != 1749) and  (explosao != 1750) and (explosao != 1751) and (explosao != 1752) and (explosao != 1753) and (explosao != 1754) and (explosao != 1755) and (explosao != 1756) and (explosao != 1757) and (explosao != 1758) and (explosao != 1759) and (explosao != 1760) and (explosao != 1761) and (explosao != 1762) and (explosao != 1763) and (explosao != 1764) and (explosao != 1765) and (explosao != 1766) and (explosao != 1767) and (explosao != 1768) and (explosao != 1769) and (explosao != 1770) and (explosao != 1771) and (explosao != 1772) and (explosao != 1773) and (explosao != 1774) and (explosao != 1775) and (explosao != 1776) and (explosao != 1777) and (explosao != 1778) and (explosao != 1779) and (explosao != 1780) and (explosao != 1781) and (explosao != 1782) and (explosao != 1783) and (explosao != 1784) and (explosao != 1785) and (explosao != 1786) and (explosao != 1787) and (explosao != 1788) and (explosao != 1789) and (explosao != 1790) and (explosao != 1791) and (explosao != 1792) and (explosao != 1793) and (explosao != 1794) and (explosao != 1795) and (explosao != 1796) and (explosao != 1797) and (explosao != 1798) and (explosao != 1799) :
                                if(lista[explosao + 60] == '#') : lista[explosao] = '#'
                            if(explosao != 0) and (explosao != 1) and (explosao != 2) and (explosao != 3) and (explosao != 4) and (explosao != 5) and (explosao != 6) and (explosao != 7) and (explosao != 8) and (explosao != 9) and (explosao != 10) and (explosao != 11) and (explosao != 12) and (explosao != 13) and (explosao != 14) and (explosao != 15) and (explosao != 16) and (explosao != 17) and (explosao != 18) and (explosao != 19) and (explosao != 20) and (explosao != 21) and (explosao != 22) and (explosao != 23) and (explosao != 24) and (explosao != 25) and (explosao != 26) and (explosao != 27) and (explosao != 28) and (explosao != 29) and (explosao != 30) and (explosao != 31) and (explosao != 32) and (explosao != 33) and (explosao != 34) and (explosao != 35) and (explosao != 36) and (explosao != 37) and (explosao != 38) and (explosao != 39) and (explosao != 40) and (explosao != 41) and (explosao != 42) and (explosao != 43) and (explosao != 44) and (explosao != 45) and (explosao != 46) and (explosao != 47) and (explosao != 48) and (explosao != 49) and (explosao != 50) and (explosao != 51) and (explosao != 52) and (explosao != 53) and (explosao != 54) and (explosao != 55) and (explosao != 56) and (explosao != 57) and (explosao != 58) and (explosao != 59) :
                                if(lista[explosao - 60] == '#') : lista[explosao] = '#'
                    muitaslinhas()
                    muitosiguais()
                    atualizartela()
                    muitosiguais()
                    time.sleep(0.04)
                time.sleep(4)

                for dissipandofracionado in range(0,20):

                    for dissipando in range(0,200):
                        explosao = random.randint(0,1799)
                        if(lista[explosao] == '#') :
                            if(explosao != 59) and (explosao != 119) and (explosao != 179) and (explosao != 239) and (explosao != 299) and (explosao != 359) and (explosao != 419) and (explosao != 479) and (explosao != 539) and (explosao != 599) and (explosao != 659) and (explosao != 719) and (explosao != 779) and (explosao != 839) and (explosao != 899) and (explosao != 959) and (explosao != 1019) and (explosao != 1079) and (explosao != 1139) and (explosao != 1199) and (explosao != 1259) and (explosao != 1319) and (explosao != 1379) and (explosao != 1439) and (explosao != 1499) and (explosao != 1559) and (explosao != 1619) and (explosao != 1679) and (explosao != 1739) and (explosao != 1799) :
                                if(lista[explosao + 1] == '#') : lista[explosao] = ' '
                            if(explosao != 0) and (explosao != 60) and (explosao != 120) and (explosao != 180) and (explosao != 240) and (explosao != 300) and (explosao != 360) and (explosao != 420) and (explosao != 480) and (explosao != 540) and (explosao != 600) and (explosao != 660) and (explosao != 720) and (explosao != 780) and (explosao != 840) and (explosao != 900) and (explosao != 960) and (explosao != 1020) and (explosao != 1080) and (explosao != 1140) and (explosao != 1200) and (explosao != 1260) and (explosao != 1320) and (explosao != 1380) and (explosao != 1440) and (explosao != 1500) and (explosao != 1560) and (explosao != 1620) and (explosao != 1680) and (explosao != 1740) :  
                                if(lista[explosao - 1] == '#') : lista[explosao] = ' '
                            if(explosao != 1739) and (explosao != 1740) and (explosao != 1741) and (explosao != 1742) and (explosao != 1743) and (explosao != 1744) and (explosao != 1745) and (explosao != 1746) and (explosao != 1747) and (explosao != 1748) and (explosao != 1749) and  (explosao != 1750) and (explosao != 1751) and (explosao != 1752) and (explosao != 1753) and (explosao != 1754) and (explosao != 1755) and (explosao != 1756) and (explosao != 1757) and (explosao != 1758) and (explosao != 1759) and (explosao != 1760) and (explosao != 1761) and (explosao != 1762) and (explosao != 1763) and (explosao != 1764) and (explosao != 1765) and (explosao != 1766) and (explosao != 1767) and (explosao != 1768) and (explosao != 1769) and (explosao != 1770) and (explosao != 1771) and (explosao != 1772) and (explosao != 1773) and (explosao != 1774) and (explosao != 1775) and (explosao != 1776) and (explosao != 1777) and (explosao != 1778) and (explosao != 1779) and (explosao != 1780) and (explosao != 1781) and (explosao != 1782) and (explosao != 1783) and (explosao != 1784) and (explosao != 1785) and (explosao != 1786) and (explosao != 1787) and (explosao != 1788) and (explosao != 1789) and (explosao != 1790) and (explosao != 1791) and (explosao != 1792) and (explosao != 1793) and (explosao != 1794) and (explosao != 1795) and (explosao != 1796) and (explosao != 1797) and (explosao != 1798) and (explosao != 1799) :
                                if(lista[explosao + 60] == '#') : lista[explosao] = ' '
                            if(explosao != 0) and (explosao != 1) and (explosao != 2) and (explosao != 3) and (explosao != 4) and (explosao != 5) and (explosao != 6) and (explosao != 7) and (explosao != 8) and (explosao != 9) and (explosao != 10) and (explosao != 11) and (explosao != 12) and (explosao != 13) and (explosao != 14) and (explosao != 15) and (explosao != 16) and (explosao != 17) and (explosao != 18) and (explosao != 19) and (explosao != 20) and (explosao != 21) and (explosao != 22) and (explosao != 23) and (explosao != 24) and (explosao != 25) and (explosao != 26) and (explosao != 27) and (explosao != 28) and (explosao != 29) and (explosao != 30) and (explosao != 31) and (explosao != 32) and (explosao != 33) and (explosao != 34) and (explosao != 35) and (explosao != 36) and (explosao != 37) and (explosao != 38) and (explosao != 39) and (explosao != 40) and (explosao != 41) and (explosao != 42) and (explosao != 43) and (explosao != 44) and (explosao != 45) and (explosao != 46) and (explosao != 47) and (explosao != 48) and (explosao != 49) and (explosao != 50) and (explosao != 51) and (explosao != 52) and (explosao != 53) and (explosao != 54) and (explosao != 55) and (explosao != 56) and (explosao != 57) and (explosao != 58) and (explosao != 59) :
                                if(lista[explosao - 60] == '#') : lista[explosao] = ' '                       

                    for espalhando in range(0,50):
                        explosao = random.randint(0,1799)
                        if(lista[explosao] == ' ') :
                            if(explosao != 59) and (explosao != 119) and (explosao != 179) and (explosao != 239) and (explosao != 299) and (explosao != 359) and (explosao != 419) and (explosao != 479) and (explosao != 539) and (explosao != 599) and (explosao != 659) and (explosao != 719) and (explosao != 779) and (explosao != 839) and (explosao != 899) and (explosao != 959) and (explosao != 1019) and (explosao != 1079) and (explosao != 1139) and (explosao != 1199) and (explosao != 1259) and (explosao != 1319) and (explosao != 1379) and (explosao != 1439) and (explosao != 1499) and (explosao != 1559) and (explosao != 1619) and (explosao != 1679) and (explosao != 1739) and (explosao != 1799) :
                                if(lista[explosao + 1] == '#') : lista[explosao] = '#'
                            if(explosao != 0) and (explosao != 60) and (explosao != 120) and (explosao != 180) and (explosao != 240) and (explosao != 300) and (explosao != 360) and (explosao != 420) and (explosao != 480) and (explosao != 540) and (explosao != 600) and (explosao != 660) and (explosao != 720) and (explosao != 780) and (explosao != 840) and (explosao != 900) and (explosao != 960) and (explosao != 1020) and (explosao != 1080) and (explosao != 1140) and (explosao != 1200) and (explosao != 1260) and (explosao != 1320) and (explosao != 1380) and (explosao != 1440) and (explosao != 1500) and (explosao != 1560) and (explosao != 1620) and (explosao != 1680) and (explosao != 1740) :  
                                if(lista[explosao - 1] == '#') : lista[explosao] = '#'
                            if(explosao != 1739) and (explosao != 1740) and (explosao != 1741) and (explosao != 1742) and (explosao != 1743) and (explosao != 1744) and (explosao != 1745) and (explosao != 1746) and (explosao != 1747) and (explosao != 1748) and (explosao != 1749) and  (explosao != 1750) and (explosao != 1751) and (explosao != 1752) and (explosao != 1753) and (explosao != 1754) and (explosao != 1755) and (explosao != 1756) and (explosao != 1757) and (explosao != 1758) and (explosao != 1759) and (explosao != 1760) and (explosao != 1761) and (explosao != 1762) and (explosao != 1763) and (explosao != 1764) and (explosao != 1765) and (explosao != 1766) and (explosao != 1767) and (explosao != 1768) and (explosao != 1769) and (explosao != 1770) and (explosao != 1771) and (explosao != 1772) and (explosao != 1773) and (explosao != 1774) and (explosao != 1775) and (explosao != 1776) and (explosao != 1777) and (explosao != 1778) and (explosao != 1779) and (explosao != 1780) and (explosao != 1781) and (explosao != 1782) and (explosao != 1783) and (explosao != 1784) and (explosao != 1785) and (explosao != 1786) and (explosao != 1787) and (explosao != 1788) and (explosao != 1789) and (explosao != 1790) and (explosao != 1791) and (explosao != 1792) and (explosao != 1793) and (explosao != 1794) and (explosao != 1795) and (explosao != 1796) and (explosao != 1797) and (explosao != 1798) and (explosao != 1799) :
                                if(lista[explosao + 60] == '#') : lista[explosao] = '#'
                            if(explosao != 0) and (explosao != 1) and (explosao != 2) and (explosao != 3) and (explosao != 4) and (explosao != 5) and (explosao != 6) and (explosao != 7) and (explosao != 8) and (explosao != 9) and (explosao != 10) and (explosao != 11) and (explosao != 12) and (explosao != 13) and (explosao != 14) and (explosao != 15) and (explosao != 16) and (explosao != 17) and (explosao != 18) and (explosao != 19) and (explosao != 20) and (explosao != 21) and (explosao != 22) and (explosao != 23) and (explosao != 24) and (explosao != 25) and (explosao != 26) and (explosao != 27) and (explosao != 28) and (explosao != 29) and (explosao != 30) and (explosao != 31) and (explosao != 32) and (explosao != 33) and (explosao != 34) and (explosao != 35) and (explosao != 36) and (explosao != 37) and (explosao != 38) and (explosao != 39) and (explosao != 40) and (explosao != 41) and (explosao != 42) and (explosao != 43) and (explosao != 44) and (explosao != 45) and (explosao != 46) and (explosao != 47) and (explosao != 48) and (explosao != 49) and (explosao != 50) and (explosao != 51) and (explosao != 52) and (explosao != 53) and (explosao != 54) and (explosao != 55) and (explosao != 56) and (explosao != 57) and (explosao != 58) and (explosao != 59) :
                                if(lista[explosao - 60] == '#') : lista[explosao] = '#'                       
                    muitaslinhas()
                    muitosiguais()
                    atualizartela()
                    muitosiguais()
                    time.sleep(1)
                for sumindocomafumaÃ§a in range(0,5):
                    for simiremfases in range(0,2000):
                        sumir = random.randint(0,1799)
                        if(lista[sumir] == '#') : lista[sumir] = ' '
                    muitaslinhas()
                    muitosiguais()
                    atualizartela()
                    muitosiguais()
                    time.sleep(1)
                break
            if(lista[bomba] == ' ') : lista[bomba] = 'Q'        # (isso serve para colocar as bombas na posiÃ§Ã£o sorteada caso ela seja adequada)
        if(pontos == 40) :                                      # (identificador de vitÃ³ria sobre o nÃ­vel do jogo E remoÃ§Ã£o com detalhes visuais das bombas)
            while(lista.count('Q') > 0) :
                lista[lista.index('Q')] = ' '
                time.sleep(0.01)
                muitaslinhas()
                muitosiguais()
                atualizartela()
                muitosiguais()
            fase = ''
        if(lista.count('$') == moedinhasantes - 1):            #(contagem das moedinhas que ja foram apanhadas)
            pontos = pontos + 1


########################################################
#               BLOCO SEGUNDO NÃVEL                    #
########################################################
            
        if(pontos >= 50) and (pontos < 70):
            fase = 'FASE 2 - pega pega'
            if(pontos == 50) and (lista.count('X') == 0):
                while True:
                    posX = random.randint(0,1799)
                    if(lista[posX] == ' ') :
                        lista[posX] = 'X'
                        break
                
            if((lista.index('X') - lista.index('O')) >= 60) :
                comedorantes = lista.index('X')
                lista[lista.index('X')] = ' '
                lista[comedorantes - 60] = 'X'
            elif((lista.index('X') - lista.index('O')) <= -60) :
                comedorantes = lista.index('X')
                lista[lista.index('X')] = ' '
                lista[comedorantes + 60] = 'X'
            if((lista.index('X') < lista.index('O'))) :
                comedorantes = lista.index('X')
                lista[lista.index('X')] = ' '
                lista[comedorantes + 1] = 'X'
            elif((lista.index('X') > lista.index('O'))) :
                comedorantes = lista.index('X')
                lista[lista.index('X')] = ' '
                lista[comedorantes - 1] = 'X'
            if(lista.index('O') == lista.index('X') + 1) or (lista.index('O') == lista.index('X') - 1) or (lista.index('O') == lista.index('X') + 60) or (lista.index('O') == lista.index('X') - 60):
                muitaslinhas()
                muitosiguais()
                atualizartela()
                muitosiguais()
                break