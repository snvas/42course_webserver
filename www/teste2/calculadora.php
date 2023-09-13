#!/usr/bin/php

<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
	$postData = file_get_contents("php://input");
	parse_str($postData, $_POST);

    $num1 = $_POST["num1"];
    $num2 = $_POST["num2"];
    $operation = $_POST["operation"];
    $result = 0;

    switch ($operation) {
        case "add":
            $result = $num1 + $num2;
            break;
        case "subtract":
            $result = $num1 - $num2;
            break;
        case "multiply":
            $result = $num1 * $num2;
            break;
        case "divide":
            if($num2 != 0){
                $result = $num1 / $num2;
            } else {
                echo "Divisão por zero não é permitida.";
                exit;
            }
            break;
        default:
            echo "Operação inválida.";
            exit;
    }

    echo "Resultado: " . $result;
}
?>