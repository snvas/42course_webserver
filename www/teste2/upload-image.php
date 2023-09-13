#!/usr/bin/php

<?php
if (isset($_FILES['pic'])) {
    $uploadDir = './uploads/';
    
    if ($_FILES['pic']['error'] === UPLOAD_ERR_OK) {
        $ext = strtolower(pathinfo($_FILES['pic']['name'], PATHINFO_EXTENSION));  // Obtém a extensão do arquivo
        $new_name = date("Y.m.d-H.i.s") . '.' . $ext;  // Define um novo nome para o arquivo
        
        if (move_uploaded_file($_FILES['pic']['tmp_name'], $uploadDir . $new_name)) {
            echo "Imagen enviada com sucesso!";
        } else {
            echo "Erro ao salvar a imagem no servidor!";
        }
    } else {
        // Captura e exibe mensagens de erro do PHP relacionadas ao upload
        switch ($_FILES['pic']['error']) {
            case UPLOAD_ERR_INI_SIZE:
                echo "A imagem excede o tamanho máximo definido em php.ini!";
                break;
            case UPLOAD_ERR_FORM_SIZE:
                echo "A imagem excede o tamanho máximo permitido pelo formulário!";
                break;
            case UPLOAD_ERR_PARTIAL:
                echo "O upload da imagem foi apenas parcialmente realizado!";
                break;
            case UPLOAD_ERR_NO_FILE:
                echo "Nenhum arquivo foi enviado!";
                break;
            case UPLOAD_ERR_NO_TMP_DIR:
                echo "Diretório temporário ausente!";
                break;
            case UPLOAD_ERR_CANT_WRITE:
                echo "Falha ao escrever o arquivo no disco!";
                break;
            case UPLOAD_ERR_EXTENSION:
                echo "Upload interrompido por causa de uma extensão PHP!";
                break;
            default:
                echo "Erro desconhecido!";
        }
    }
} else {
    echo "Nenhum arquivo enviado!";
}
?>
