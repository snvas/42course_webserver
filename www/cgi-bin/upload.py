#!/usr/bin/python3
print("Content-Type: text/html")
print()

import cgi,cgitb
cgitb.enable()

form = cgi.FieldStorage()
file = form['image'].value

upload_dir = '/uploads/' # esse é o diretório onde vou salvar a imagem

f = open(file, mode = 'rb') #'rb' para ler arquivos binários 
f2 = open(upload_dir + file, 'wb')  #'wb' para gravar arquivos binários
f2.write(f.read())