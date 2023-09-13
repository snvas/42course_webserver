#!/usr/bin/php

<?php

$method = $_SERVER['REQUEST_METHOD'];
$query = $_SERVER['QUERY_STRING'];
$con_type = $_SERVER['CONTENT_TYPE'];
$length = $_SERVER['CONTENT_LENGTH'];
$server = $_SERVER['SERVER_NAME'];

echo "<html>";
echo "<head>";
echo "<title>Request Details</title>";
echo "</head>";
echo "<body>";
echo "<h1>Request Details in PHP</h1>";
echo "<pre>$method</pre>";
echo "<pre>$query</pre>";
echo "<pre>$con_type</pre>";
echo "<pre>$length</pre>";
echo "</body>";
echo "</html>";

?>
