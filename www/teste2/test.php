#!/usr/bin/php

<?php
// arquivo teste.php

// Lista de variáveis de ambiente esperadas pelo php-cgi
$expected_env_vars = [
    'DOCUMENT_ROOT', 'GATEWAY_INTERFACE', 'HTTP_ACCEPT',
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
?>

<?php
echo "<h1>Teste CGI PHP</h1>";

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    echo "<h2>Informações POST:</h2>";
    echo "<pre>";
    print_r($_POST);
    echo "</pre>";

    echo "<h2>Variáveis de Ambiente:</h2>";
    echo "<pre>";
    echo "CONTENT_TYPE: " . getenv("CONTENT_TYPE") . "<br>";
    echo "CONTENT_LENGTH: " . getenv("CONTENT_LENGTH") . "<br>";
    echo "</pre>";
} else {
    echo "Envie uma solicitação POST para visualizar as informações.";
}
?>

<?php

$method = $_SERVER['REQUEST_METHOD'];
$query = $_SERVER['QUERY_STRING'];
$con_type = $_SERVER['CONTENT_TYPE'];
$length = $_SERVER['CONTENT_LENGTH'];
$server = $_SERVER['SERVER_NAME'];
$host = $_SERVER['HTTP_HOST'];
$auth = $_SERVER['AUTH_TYPE'];
$gate = $_SERVER['GATEWAY_INTERFACE'];
	/*envVec.push_back("REDIRECT_STATUS=200");
	envVec.push_back("GATEWAY_INTERFACE=CGI/1.1");
	envVec.push_back("SCRIPT_NAME=" + _req.cgi_path);
	envVec.push_back("SCRIPT_FILENAME=" + _req.cgi_path);
	envVec.push_back("REQUEST_METHOD=" + _req.method);
	envVec.push_back("CONTENT_LENGTH=" + _req.body);
	envVec.push_back("CONTENT_TYPE=" + _req.content_type);
	envVec.push_back("PATH_INFO=" + _req.cgi_path);
	envVec.push_back("PATH_TRANSLATED=" + _req.cgi_path);
	envVec.push_back("QUERY_STRING=" + _req.query);
	envVec.push_back("REMOTEaddr=" + _req.port);
	envVec.push_back("REMOTE_IDENT=" + _req.authorization);
	envVec.push_back("REMOTE_USER=" + _req.authorization);
	envVec.push_back("REQUEST_URI=" + _req.uri + "?" + _req.query);
	envVec.push_back("SERVER_NAME=" + _req.host);
	envVec.push_back("SERVER_PROTOCOL=HTTP/1.1");
	envVec.push_back("SERVER_SOFTWARE=Webserver/1.0");
	envVec.push_back("HTTP_USER_AGENT=" + _req.user_agent);
	envVec.push_back("HTTP_ACCEPT=" + _req.accept);*/

echo "<html>";
echo "<head>";
echo "<title>Request Details</title>";
echo "</head>";
echo "<body>";
echo "<h1>Request Details in PHP</h1>";
echo "<pre>Método: $method</pre>";
echo "<pre>Query: $query</pre>";
echo "<pre>Content-type: $con_type</pre>";
echo "<pre>Content-length: $length</pre>";
echo "<pre>Server: $server</pre>";
echo "<pre>Host: $host</pre>";
echo "<pre>Authorization: $auth</pre>";
echo "<pre>Gateway: $gate</pre>";
echo "</body>";
echo "</html>";

?>
