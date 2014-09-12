<?php
define('IS_AJAX_REQUEST', isset($_SERVER['HTTP_X_REQUESTED_WITH']) && strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) == 'xmlhttprequest');
if (IS_AJAX_REQUEST) {
    ar_custom_dictionary();
}
function ar_custom_dictionary() {
    $success = false;
    $word = $_GET['word'];
    if ($word) {
        require_once('ARClient.inc');
    $apiHost = 'http://api.score.atomicreach.com';
    $key = variable_get('atomicreach_consumer', '');
    $secret = variable_get('atomicreach_secret', '');
    

        $apiClient = New AR_Client($apiHost, $key, $secret);
        $apiClient->init();
        $result = $apiClient->addDictionary($word);

        if ($result->status == AR_Client::STATUS_OK) {
            $success = true;
        }
    }
    
    echo $key;
    
   // echo $success ? 'OK' : 'ERROR';
    exit();
}