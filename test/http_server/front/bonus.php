#!/usr/bin/env php
<?php

$body = "Hello, world!\nCurrent time: " . date("Y-m-d H:i:s");

$response =
    "HTTP/1.1 200 OK\r\n" .
    "Content-Type: text/plain; charset=UTF-8\r\n" .
    "Content-Length: " . strlen($body) . "\r\n" .
    "Connection: close\r\n" .
    "\r\n" .
    $body;

echo $response;