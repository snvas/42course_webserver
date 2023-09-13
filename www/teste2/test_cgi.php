#!/usr/bin/php

<?php
echo "<h1>Teste CGI PHP</h1>";

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
	$post_data = file_get_contents("php://stdin");
	echo "<h2>Infos POST via stdin:</h2>";
	echo "<pre>";
	print_r($post_data);
	echo "</pre>";
// Lista de variáveis de ambiente esperadas pelo php-cgi
$expected_env_vars = [
    'GATEWAY_INTERFACE', 'HTTP_ACCEPT',
    'HTTP_HOST', 'HTTP_USER_AGENT', 'PATH_INFO', 
	'PATH_TRANSLATED', 'QUERY_STRING',
    'REDIRECT_STATUS', 'REMOTE_ADDR', 'REMOTE_PORT',
    'REQUEST_METHOD', 'REQUEST_URI', 'SCRIPT_FILENAME',
    'SCRIPT_NAME', 'SERVER_NAME', 'SERVER_PORT',
    'SERVER_PROTOCOL', 'SERVER_SOFTWARE', 'CONTENT_LENGTH',
    'CONTENT_TYPE'
];

echo "<h2>Teste de variáveis de ambiente para php-cgi</h2>";

	foreach ($expected_env_vars as $var) {
		if (isset($_SERVER[$var])) {
			echo "<b>$var:</b> " . $_SERVER[$var] . "<br />";
		} else {
			echo "<b>$var:</b> <span style='color:red'>Não definido</span><br />";
		}
	}
} else {
    echo "Envie uma solicitação POST para visualizar as informações.";
}
?>