<?php

if('POST' == $_SERVER['REQUEST_METHOD'])
{
    include 'HttpTranslator.php';
    include 'AccessTokenAuthentication.php';

    try 
    {
        //Client ID of the application.
        $clientID = "DeAstisMicrosoftTraduttore2014";
        //Client Secret key of the application.
        $clientSecret = "Vfx6Ihf8PoK8OEFx0ZFPgChvTR+N5pD2BLqWSe+Fp7k=";
        //OAuth Url.
        $authUrl = "https://datamarket.accesscontrol.windows.net/v2/OAuth2-13/";
        //Application Scope Url
        $scopeUrl = "http://api.microsofttranslator.com";
        //Application grant type
        $grantType = "client_credentials";

        //Create the AccessTokenAuthentication object.
        $authObj = new AccessTokenAuthentication();
        //Get the Access token.
        $accessToken = $authObj->getTokens($grantType, $scopeUrl, $clientID, $clientSecret, $authUrl);
        //Create the authorization Header string.
        $authHeader = "Authorization: Bearer ". $accessToken;

        //Set the parameters.
        // Sets source language. $fromLanguage = variable, source_lang = name of textarea.
        $fromLanguage = $_POST["source_lang"];
        // Sets destination language. $toLanguage = variable, dest_lang = name of textarea.
        $toLanguage = $_POST["dest_lang"];
        // Sets text to translate. $inputStr = variable, source_text = content of thextarea.
        $inputStr = $_POST["source_text"];

        $contentType = 'text/plain';
        $category = 'general';
        
        // Variable that composes the string of parameters for the transaltion
        $params = "text=".urlencode($inputStr)."&to=".$toLanguage."&from=".$fromLanguage;
        // URL to translate the text
        $translateUrl = "http://api.microsofttranslator.com/v2/Http.svc/Translate?$params";
    
        //Create the Translator Object.
        $translatorObj = new HTTPTranslator();
    
        //Get the curlResponse.
        $curlResponse = $translatorObj->curlRequest($translateUrl, $authHeader);
    
        //Interprets a string of XML into an object.
        $xmlObj = simplexml_load_string($curlResponse);
        foreach((array)$xmlObj[0] as $val)
        {
            $translatedStr = $val;
        }

    } catch (Exception $e) 
      {
          echo "Exception: " . $e->getMessage() . PHP_EOL;
      }
}

?>



<!DOCTYPE html>
<html lang="it">

<head>
    <meta charset="utf-8" />
    <title>Microsoft Translator</title>
    <link rel="stylesheet" href="css.css" />
</head>


<body>


    <?php
        // Declaration of the array that contains the language of the translation.
        $languages = array("a"=>"Seleziona lingua", "it"=>"Italiano", "en"=>"Inglese", "ja"=>"Giapponese", "pt"=>"Portoghese", "es"=>"Spagnolo", "tr"=>"Turco",
        "zh-CHS"=>"Cinese Semplificato", "zh-CHT"=>"Cinese Tradizionale", "de"=>"Tedesco", "fr"=>"Francese",);
        // Sorts array by key without change them.
        Ksort($languages);        
    ?>
    
    <div class = "body">

        <div class="intestazione">
            <img class="logo" src="image/logo.png" width="300" height="47" alt="logo"/>        
        </div>

        <!-- The name of web page -->
        <p class = "titolo">Traduttore</p>

        <!-- All content iso send in POST request -->
        <form action = "translate.php" method = "POST">

            <!-- Select of the source language -->
            <select class = "source_lang" name = "source_lang">
                
                <!-- PHP's foreach to view the languages aviable for translate -->
                <?php foreach($languages as $code => $lang) { ?>
                <option value = "<?php echo $code; ?>"><?php echo $lang; ?></option>
                <?php } ?>
            
            </select>
            
           
            <!-- Insert text to translate -->
           	<textarea class = "source_text" name = "source_text" onclick = "javascript:source_text.value = ''"><?php echo($inputStr);?></textarea>
           
            <!-- Select destination language -->
            <select class = "dest_lang" name = "dest_lang">

                <!-- PHP's foreach to view the languages aviable for translate -->
                <?php foreach($languages as $code => $lang) { ?>
                <option value = "<?php echo $code; ?>"><?php echo $lang; ?></option>
                <?php } ?>

            </select>
            
                       
            <input class = "submit" type = "submit" value = "Traduci">
        
        </form>
           
            
        <!-- View the text translated -->
        <textarea id = "transl_text" class = "transl_text" name = "transl_text" onclick = "javascript:transl_text.value = '' "><?php echo $translatedStr; ?></textarea>
            
        <!--<button class = "reset" onclick = "javascript:source_text.value = '', transl_text.value = '' ">Reset</button>-->

        <div class="pagef">
            <img class="credit" src="image/credit.png" width="200" height="25" alt="credit"/>     
        </div>
           
    </div>

</body>

</html>