#!/usr/bin/python3
print("Content-Type: text/html")
print()

import cgi
import cgitb
import os
cgitb.enable()

# Diretório de trabalho atual
print("Diretório de trabalho atual:", os.getcwd())

form = cgi.FieldStorage()

if 'image' not in form:
    print("Falha no envio da imagem!")
    exit()

fileitem = form['image']

# Teste se o arquivo foi enviado
if fileitem.filename:
    # strip leading path from file name to avoid directory traversal attacks
    filename = os.path.basename(fileitem.filename)
    upload_dir = './www/cgi-bin/uploads/'  # assegure-se que este diretório existe e tem permissões de escrita
    
    # Limpando o nome do arquivo
    clean_filename = ''.join(e for e in filename if e.isalnum() or e in ['.', '-']).rstrip()
    file_path = os.path.join(upload_dir, clean_filename)

    # Evite sobrescrever arquivos existentes
    counter = 1
    while os.path.exists(file_path):
        filename, file_extension = os.path.splitext(clean_filename)
        file_path = os.path.join(upload_dir, f"{filename}_{counter}{file_extension}")
        counter += 1

    # Recuperando dados do arquivo e salvando
    file_data = fileitem.file.read()
    with open(file_path, 'xb') as f:
        f.write(file_data)

    print("Arquivo '" + filename + "' foi enviado e salvo como '" + os.path.basename(file_path) + "'!")
else:
    print("Falha no envio da imagem!")
