<?php

/* Initialize session for save the destination language value for text-to-speech */ 
session_start();

if (isset($_POST["dest_lang"]))
{
    $_SESSION["speech_lang"] = $_POST["dest_lang"];
    
}

include 'HttpTranslator.php';
include 'AccessTokenAuthentication.php';
require 'credential.php';

if('POST' == $_SERVER['REQUEST_METHOD'])
{
    /* Session variable for keep the languages selected */
    /* Sets session variable for source_lang */
    if (isset($_POST['source_lang']))
    {
        $_SESSION['source_lang'] = $_POST['source_lang'];
    }
    
    /* Sets session variable for dest_lang */
    if (isset($_POST['dest_lang']))
    {
        $_SESSION['dest_lang'] = $_POST['dest_lang'];
    }
  
    
    try 
    {
        // Create the AccessTokenAuthentication object.
        $authObj = new AccessTokenAuthentication();
        // Get the Access token.
        $accessToken = $authObj -> getTokens($grantType, $scopeUrl, $clientID, $clientSecret, $authUrl);
        // Create the authorization Header string.
        $authHeader = "Authorization: Bearer ". $accessToken;

        // Set the parameters.
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
        $curlResponse = $translatorObj -> curlRequest($translateUrl, $authHeader);
    
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
elseif ('GET' == $_SERVER['REQUEST_METHOD'])
{
    try 
    {
        //Create the AccessTokenAuthentication object.
        $authObj = new AccessTokenAuthentication();
        //Get the Access token.
        $accessToken  = $authObj->getTokens($grantType, $scopeUrl, $clientID, $clientSecret, $authUrl);
        //Create the authorization Header string.
        $authHeader = "Authorization: Bearer ". $accessToken;
        
        //Set the params.
        $speechStr = urlencode($_GET["transl_text"]);
        $language = $_SESSION["speech_lang"];
        $out = 'audio/mp3';
        $params = "text=$speechStr&language=$language&format=$out";
        
        //HTTP Speak method URL.
        $url = "http://api.microsofttranslator.com/V2/Http.svc/Speak?$params";
        
        //Set the Header Content Type.
        header('Content-Type: audio/mp3');
        header('Content-Disposition: attachment; filename = '.uniqid('SPC_').'.mp3');
        
        //Create the Translator Object.
        $translatorObj = new HTTPTranslator();
    
        //Call the curlRequest.
        $strResponse = $translatorObj -> curlRequest($url, $authHeader);
        echo $strResponse;
     
        //echo ('<audio autoplay = "autoplay" >  <source src = "'.$strResponse.'" type = "audio/mp3" /> </audio> ');
        

} catch (Exception $e) 
  {
      echo "Exception: " . $e->getMessage() . PHP_EOL;
  }
}

//session_destroy();

?>



<!DOCTYPE html>
<html lang = "it">

<head>
    <meta charset="utf-8" />
    <title>Microsoft Translator</title>
    <link rel = "stylesheet" href = "css.css" />
    <script type = "text/javascript" src="functions_js.js"></script>
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

        <div class = "intestazione">
           <img class = "logo" src = "image/logo.png" width = "300" height = "47" alt = "logo"/>
        </div>

        <!-- The name of web page -->
        <p class = "titolo">Traduttore</p>

        <!-- All content is send in POST request -->
        <form id ="trad" name = 'trad' action = "translate.php" method = "POST">

            <!-- Select of the source language -->
            <select class = "source_lang" name = "source_lang">
                
                <!-- PHP's function to view the languages aviable for translate -->
                <?php if ($_SESSION['source_lang'] == NULL) 
                      {
                          foreach($languages as $code => $lang) 
                          { ?>
                              <option value = "<?php echo $code; ?>"> <?php echo $lang; ?> </option>
                    <?php }
                      } 
                      else 
                      {
                          foreach($languages as $code => $lang) 
                          { if ($code == $_SESSION['source_lang'])
                            {?>
                                <option value = "<?php echo $code; ?>"> <?php echo $lang; ?> </option>
                      <?php }
        
                          }
                          foreach($languages as $code => $lang) 
                          {?>
                              <option value = "<?php echo $code; ?>"> <?php echo $lang; ?> </option>
                    <?php }
                      } ?>           
     
            </select>
           
            <!-- Insert text to translate -->
           	<textarea id = "source_text" class = "source_text" name = "source_text" onclick = "javascript:select(source_text)" onkeypress = "javascript:send(this, event);"><?php echo($inputStr); ?></textarea>
           
            <!-- Select destination language -->
            <select id = "dest_lang" class = "dest_lang" name = "dest_lang">

                <!-- PHP's foreach to view the languages aviable for translate -->
                <?php if ($_SESSION['source_lang'] == NULL) 
                      {
                          foreach($languages as $code => $lang) 
                          { ?>
                              <option value = "<?php echo $code; ?>"> <?php echo $lang; ?> </option>
                    <?php }
                      } 
                      else 
                      {
                          foreach($languages as $code => $lang) 
                          { if ($code == $_SESSION['dest_lang'])
                            { ?>
                                <option value = "<?php echo $code; ?>"> <?php echo $lang; ?> </option>
                      <?php }
        
                          }
                          foreach($languages as $code => $lang) 
                          { ?>
                              <option value = "<?php echo $code; ?>"> <?php echo $lang; ?> </option>
                    <?php }
                      }?>    

            </select>
              
            <input class = "traduci_sub" type = "submit" value = "Traduci">
        
        </form>


        <!-- All content is send in GET request -->
        <form id = "speech" name = "speech" action = "translate.php" method = "GET">

            <!-- View the text translated -->
            <textarea id = "transl_text" class = "transl_text" name = "transl_text" onclick = "javascript:select(transl_text)"><?php echo($translatedStr); ?></textarea>
            
            <input class = "ascolta_sub" type = "submit" value="">

        </form>
            
        <button class = "reset" onclick = "javascript:trad.source_text.value = ''; javascript:speech.transl_text.value = ''">Reset</button>

        <!--<audio autoplay="autoplay" controls="controls">
        <source src="<?php $strResponse?>" type="audio/mp3" />
        </audio>-->

        <div class="pagef">
            <img class="credit" src="image/credit.png" width="200" height="25" alt="credit"/>     
        </div>
           
    </div>

</body>

</html>