<?php

// Initialize session for save the destination language value for text-to-speech.
session_start();

// Verify if there is a previous speech file.
if (glob('./speech_file/*.mp3'))
{
    $file = glob('speech_file/'.'*.mp3',GLOB_MARK);
    foreach ($file as $file)
    {
        if (is_dir($file))
        {
            self::deleteDir($file);
        }
        else
        {
            unlink($file);
        }
    }
}

include 'HttpTranslator.php';
include 'AccessTokenAuthentication.php';
require 'Credentials.php';

if (isset($_POST['traduci_sub']))
{
    // Session variable for keep the languages selected
    // Sets session variable for source_lang
    if (isset($_POST['source_lang']))
    {
        $_SESSION['source_lang'] = $_POST['source_lang'];
    }
    
    // Sets session variable for dest_lang.
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
        $paramst = "text=".urlencode($inputStr)."&to=".$toLanguage."&from=".$fromLanguage;
        // URL to translate the text
        $translateUrl = "http://api.microsofttranslator.com/v2/Http.svc/Translate?$paramst";
    
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

        $translatedText = urlencode($translatedStr);
        $out = 'audio/mp3';
        $params = "text=$translatedText&language=$toLanguage&format=$out";

        //HTTP Speak method URL.
        $url = "http://api.microsofttranslator.com/V2/Http.svc/Speak?$params";

        $translatorObj = new HTTPTranslator();

        $strResponse = $translatorObj -> curlRequest($url, $authHeader);
        
        //Create a fold to insert a speech file generated if not exists.
        if (!is_dir('speech_file'))
        {
            mkdir('speech_file');
        }
        
        //Create the name of speech file.
        $var = uniqid('SPC_').".mp3";

        //Save file into server directory.
        file_put_contents('./speech_file/'.$var, $strResponse);


    } catch (Exception $e) 
      {
          echo "Exception: " . $e->getMessage() . PHP_EOL;
      }
}

?>



<!DOCTYPE html>
<html lang = "it">

<head>
    <meta charset="utf-8" />
    <title>Microsoft Translator</title>
    <link rel = "stylesheet" href = "css.css" />
    <script type = "text/javascript" src = "functions_js.js"></script>
</head>


<body>

    <!-- Declaration and sorting of the array that contains the source and target language for translation. --> 
    <?php
        $languages = array("a"=>"Select language", "it"=>"Italian", "en"=>"English", "ja"=>"Japanese", "pt"=>"Portuguese", "es"=>"Spanish", "tr"=>"Turkish",
        "zh-CHS"=>"Simplified Chinese", "zh-CHT"=>"Traditional Chinese", "de"=>"German", "fr"=>"French",);
        
        // Sorts array by key without changing them.
        Ksort($languages);        
    ?>
    
    <div class = "body">

        <div class = "intestazione">
           <img class = "logo" src = "image/logo.png" width = "300" height = "47" alt = "logo"/>
        </div>

        <!-- The name of web page. -->
        <p class = "titolo">Translator</p>

        <!-- All content is send in POST request. -->
        <form id ="trad" name = 'trad' action = "index.php" method = "POST">

            <!-- Select of the source language. -->
            <select class = "source_lang" name = "source_lang">
                
                <!-- PHP function to view the languages available for translation -->
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
           
            <!-- Enter text to translate. -->
           	<textarea id = "source_text" class = "source_text" name = "source_text" onclick = "javascript:select(source_text)" onkeypress = "javascript:send('traduci_sub', event);"><?php if (isset($inputStr)== true){echo $inputStr;}else{echo '';} ?></textarea>
           
            <!-- Select destination language. -->
            <select id = "dest_lang" class = "dest_lang" name = "dest_lang">

                <!-- PHP foreach to view the languages available for translate. -->
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
            
            
            <!-- Translate button. -->  
            <input id = "traduci_sub" class = "traduci_sub" name ="traduci_sub" type = "submit" value = "Translate">
        
        </form>

            
        <!-- View the text translated. -->
        <textarea id = "transl_text" class = "transl_text" name = "transl_text" onclick = "javascript:select(transl_text)"><?php if (isset($inputStr)== true){echo $translatedStr;}else{echo '';} ?></textarea>
           
        
        
        <!-- Reset button. -->   
        <button class = "reset" onclick = "javascript:trad.source_text.value = ''; javascript:transl_text.value = ''">Reset</button>



        <!-- PHP's script for read the name of the speech file. -->
        <?php foreach(glob('./speech_file/*.*') as $filename)
              {
                  $speech = $filename;
              }
        ?>

        <!-- Player for listen the text-to-speech. -->
        <audio id = "t2s" controls = "controls" >
            <source src = "<?php echo $speech; ?>" type = "audio/mpeg" />
        </audio>



        <!-- Page footer. -->
        <div class = "pagef">
            <img class = "credit" src = "image/credit.png" width = "200" height = "25" alt = "credit"/>     
        </div>
           
    </div>

</body>
</html>