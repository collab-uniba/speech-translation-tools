<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<!--https://www.google.com/intl/pt/chrome/demos/speech.html-->

<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <title>Web Speech Recognition and Translation</title>
        <meta name="description" content="Google Tanslator API V2" />

        <script src="https://www.google.com/jsapi" type="text/javascript"></script>
        <script language="javascript" type="text/javascript" src="Scripts/jquery-1.7.1.min.js"></script>
        <script language="javascript" type="text/javascript" src="Scripts/jquery.blockUI.js"></script>
        <link media="screen" type="text/css" rel="stylesheet" href="CSS/StyleSheet.css"/>
        <script language="javascript" type="text/javascript">

            google.load("language", "1");
            var apiKey = "AIzaSyCq1JQCESjgNTc4iM1tXMzEo9d2uVf3IP8";

            $(document).ready(function () {
                if ($('#selSourceLanguage option').size() == 0) {
                    loadLanguages();
                    if ($("#divBranding").innerHTML == "") {
                        google.language.getBranding('divBranding');
                    }
                }

                $('#btnDetect').click(function (e) {
                    e.preventDefault();
                    $.blockUI({ css: {
                            border: 'none',
                            padding: '15px',
                            backgroundColor: '#000',
                            '-webkit-border-radius': '10px',
                            '-moz-border-radius': '10px',
                            opacity: .5,
                            color: '#fff'
                        }
                    });
                    detectLanguage();
                    $.unblockUI();
                });

                $('#btnTranslate').click(function (e) {
                    e.preventDefault();
                    
                    //var text = $.trim($('#txtOrgText').val());
                    var text = $.trim($('#final_span').html());
                   
                    $('#divTranslated').html("");
                    if (text.length > 0) {
                        var langSource = $('#selSourceLanguage').val();
                        var langTarget = $('#selTargetLanguage').val();

                        if (langSource === "" || langTarget === "") {
                            alert("Select Source Language and Target Language");
                        }
                        else if (langSource === langTarget) {
                            alert("Source Language and Target Language cannot be same");
                        }
                        else {
                            $.blockUI({ css: {
                                    border: 'none',
                                    padding: '15px',
                                    backgroundColor: '#000',
                                    '-webkit-border-radius': '10px',
                                    '-moz-border-radius': '10px',
                                    opacity: .5,
                                    color: '#fff'
                                }
                            });
                            var apiurl = "https://www.googleapis.com/language/translate/v2?key=" + apiKey + "&source=" + langSource + "&target=" + langTarget + "&q=";

                            $.ajax({
                                url: apiurl + encodeURIComponent(text),
                                dataType: 'jsonp',
                                async: false,
                                success: function (data) {
                                    if (langSource === langTarget) {
                                        $('#divTranslated').html(text);
                                    }
                                    else if (langSource != "") {
                                        try {
                                            $('#divTranslated').html(data.data.translations[0].translatedText);
                                        }
                                        catch (e) {
                                            $('#divTranslated').html(text);
                                        }
                                    }
                                    $('#divTranslated').css({ "border": "1px solid #7F9DB9" });
                                    $('#divTranslated').css({ "padding": "4 4 4 4" });

                                    $('#lblTranslation').css({ "color": "black" });
                                    $.unblockUI();
                                },
                                error: function (x, e) {
                                    alert('Error occured while translating the text');
                                    $.unblockUI();
                                }
                            });
                        }
                    }
                    else {
                        alert("Nothing was entered to translate");
                        $.unblockUI();
                    }
                });
                $.unblockUI();
            });

            function loadLanguages() {
                var apiurl = "https://www.googleapis.com/language/translate/v2/languages?key=" + apiKey + "&target=en";

                $.ajax({
                    url: apiurl,
                    dataType: 'jsonp',
                    success: function (data) {
                        var languages = data.data.languages;
                        $.each(languages, function (index, language) {
                            $('#selSourceLanguage').append('<option value="' + language.language + '">' + language.name + '</option>');
                            $('#selTargetLanguage').append('<option value="' + language.language + '">' + language.name + '</option>');
                        });
                        $("select#selSourceLanguage").val('en');
                        $("select#selTargetLanguage").val('en');
                    },
                    error: function (x, e) {
                        alert('Error occured while loading the Google Supported Languages');
                    }
                });
            }

            function detectLanguage() {
                //var text = $.trim($('#final_span').val());
                var text = $.trim($('#final_span').html());
                if (text.length > 0) {
                    var apiurl = "https://www.googleapis.com/language/translate/v2/detect?key=" + apiKey + "&q=";

                    $.ajax({
                        url: apiurl + encodeURIComponent(text),
                        dataType: 'jsonp',
                        async: false,
                        success: function (data) {
                            var obj = data.data.detections[0];
                            $('#selSourceLanguage').val(obj[0].language);
                            langSource = obj[0].language;
                            $('#divDetectedLanguage').html("The automatically detected language is: " + $('#selSourceLanguage option:selected').text());
                            $.unblockUI();
                        },
                        error: function (x, e) {
                            $('#divDetectedLanguage').html("Error occured while detecting the current text language");
                            $.unblockUI();
                        }
                    });
                }
                else {
                    $('#divDetectedLanguage').html("No Text for Translation was provided");
                    $.unblockUI();
                }
            }
        </script>

        <style>
            #info {
                font-size: 20px;
            }
            #div_start {
                float: right;
            }
            #headline {
                text-decoration: none
            }
            #results {
                font-size: 14px;
                font-weight: bold;
                border: 1px solid #ddd;
                padding: 15px;
                text-align: left;
                min-height: 150px;
            }
            #start_button {
                border: 0;
                background-color:transparent;
                padding: 0;
            }
            .interim {
                color: gray;
            }
            .final {
                color: black;
                padding-right: 3px;
            }
            .button {
                display: none;
            }
            .marquee {
                margin: 20px auto;
            }

            #buttons {
                margin: 10px 0;
                position: relative;
                top: -50px;
            }

            #copy {
                margin-top: 20px;
            }

            #copy > div {
                display: none;
                margin: 0 70px;
            }
        </style>
    </head>
    <body>
        <div style="width: 800px; margin-left: auto; margin-right: auto;">
            <div class="container">
                <div class="header">
                    <h1 class="headertitle">
                        <span id="lblPodcastHeader">Google Speech Recognition and Translation</span>
                    </h1>
                </div>

                <div class="browser-landing" id="main">

                    <div class="compact marquee">
                        <div id="info">
                            <p id="info_start">
                                Click on the microphone icon and begin speaking for as long as you like.
                            </p>
                            <p id="info_speak_now" style="display:none">
                                Speak now.
                            </p>
                            <p id="info_no_speech" style="display:none">
                                No speech was detected. You may need to adjust your microphone settings
                            </p>
                            <p id="info_no_microphone" style="display:none">
                                No microphone was found. Ensure that a microphone is installed and that microphone settings are configured correctly.
                            </p>
                            <p id="info_allow" style="display:none">
                                Click the "Allow" button above to enable your microphone.
                            </p>
                            <p id="info_denied" style="display:none">
                                Permission to use microphone was denied.
                            </p>
                            <p id="info_blocked" style="display:none">
                                Permission to use microphone is blocked. To change, go to
                                chrome://settings/contentExceptions#media-stream
                            </p>
                            <p id="info_upgrade" style="display:none">
                                Web Speech API is not supported by this browser. Upgrade to <a href="//www.google.com/chrome">Chrome</a> version 25 or later.
                            </p>
                        </div>
                        <div id="div_start">
                            <button id="start_button" onclick="startButton(event)"><img alt="Start" id="start_img"
                                                                                        src="Images/mic.gif"></button>
                        </div>

                        <div id="results">
                            <span class="final" id="final_span"></span> <span class="interim" id=
                                                                              "interim_span"></span>
                        </div>
                        <table>
                            <tr>
                                <td>
                                    Select the language to recognize.
                                </td>
                                <td>
                                    <div class="compact marquee" id="div_language">
                                        <select id="select_language" onchange="updateCountry()">
                                        </select>&nbsp;&nbsp; <select id="select_dialect">
                                        </select>
                                    </div>
                                </td>
                            </tr>
                            </td
                        </table>
                    </div>


                </div>

                <script src="/intl/en/chrome/assets/common/js/chrome.min.js"></script> 
                <script>
                    var langs =
                        [['Afrikaans',       ['af-ZA']],
                        ['Bahasa Indonesia',['id-ID']],
                        ['Bahasa Melayu',   ['ms-MY']],
                        ['Català',          ['ca-ES']],
                        ['Čeština',         ['cs-CZ']],
                        ['Deutsch',         ['de-DE']],
                        ['English',         ['en-AU', 'Australia'],
                            ['en-CA', 'Canada'],
                            ['en-IN', 'India'],
                            ['en-NZ', 'New Zealand'],
                            ['en-ZA', 'South Africa'],
                            ['en-GB', 'United Kingdom'],
                            ['en-US', 'United States']],
                        ['Español',         ['es-AR', 'Argentina'],
                            ['es-BO', 'Bolivia'],
                            ['es-CL', 'Chile'],
                            ['es-CO', 'Colombia'],
                            ['es-CR', 'Costa Rica'],
                            ['es-EC', 'Ecuador'],
                            ['es-SV', 'El Salvador'],
                            ['es-ES', 'España'],
                            ['es-US', 'Estados Unidos'],
                            ['es-GT', 'Guatemala'],
                            ['es-HN', 'Honduras'],
                            ['es-MX', 'México'],
                            ['es-NI', 'Nicaragua'],
                            ['es-PA', 'Panamá'],
                            ['es-PY', 'Paraguay'],
                            ['es-PE', 'Perú'],
                            ['es-PR', 'Puerto Rico'],
                            ['es-DO', 'República Dominicana'],
                            ['es-UY', 'Uruguay'],
                            ['es-VE', 'Venezuela']],
                        ['Euskara',         ['eu-ES']],
                        ['Français',        ['fr-FR']],
                        ['Galego',          ['gl-ES']],
                        ['Hrvatski',        ['hr_HR']],
                        ['IsiZulu',         ['zu-ZA']],
                        ['Íslenska',        ['is-IS']],
                        ['Italiano',        ['it-IT', 'Italia'],
                            ['it-CH', 'Svizzera']],
                        ['Magyar',          ['hu-HU']],
                        ['Nederlands',      ['nl-NL']],
                        ['Norsk bokmål',    ['nb-NO']],
                        ['Polski',          ['pl-PL']],
                        ['Português',       ['pt-BR', 'Brasil'],
                            ['pt-PT', 'Portugal']],
                        ['Română',          ['ro-RO']],
                        ['Slovenčina',      ['sk-SK']],
                        ['Suomi',           ['fi-FI']],
                        ['Svenska',         ['sv-SE']],
                        ['Türkçe',          ['tr-TR']],
                        ['български',       ['bg-BG']],
                        ['Pусский',         ['ru-RU']],
                        ['Српски',          ['sr-RS']],
                        ['한국어',            ['ko-KR']],
                        ['中文',             ['cmn-Hans-CN', '普通话 (中国大陆)'],
                            ['cmn-Hans-HK', '普通话 (香港)'],
                            ['cmn-Hant-TW', '中文 (台灣)'],
                            ['yue-Hant-HK', '粵語 (香港)']],
                        ['日本語',           ['ja-JP']],
                        ['Lingua latīna',   ['la']]];

                    for (var i = 0; i < langs.length; i++) {
                        select_language.options[i] = new Option(langs[i][0], i);
                    }
                    select_language.selectedIndex = 6;
                    updateCountry();
                    select_dialect.selectedIndex = 6;
                    showInfo('info_start');

                    function updateCountry() {
                        for (var i = select_dialect.options.length - 1; i >= 0; i--) {
                            select_dialect.remove(i);
                        }
                        var list = langs[select_language.selectedIndex];
                        for (var i = 1; i < list.length; i++) {
                            select_dialect.options.add(new Option(list[i][1], list[i][0]));
                        }
                        select_dialect.style.visibility = list[1].length == 1 ? 'hidden' : 'visible';
                    }

                    var create_email = false;
                    var final_transcript = '';
                    var recognizing = false;
                    var ignore_onend;
                    var start_timestamp;
                    if (!('webkitSpeechRecognition' in window)) {
                        upgrade();
                    } else {
                        start_button.style.display = 'inline-block';
                        var recognition = new webkitSpeechRecognition();
                        recognition.continuous = true;
                        recognition.interimResults = true;

                        recognition.onstart = function() {
                            recognizing = true;
                            showInfo('info_speak_now');
                            start_img.src = 'Images/mic-animate.gif';
                        };

                        recognition.onerror = function(event) {
                            if (event.error == 'no-speech') {
                                start_img.src = 'Images/mic.gif';
                                showInfo('info_no_speech');
                                ignore_onend = true;
                            }
                            if (event.error == 'audio-capture') {
                                start_img.src = 'Images/mic.gif';
                                showInfo('info_no_microphone');
                                ignore_onend = true;
                            }
                            if (event.error == 'not-allowed') {
                                if (event.timeStamp - start_timestamp < 100) {
                                    showInfo('info_blocked');
                                } else {
                                    showInfo('info_denied');
                                }
                                ignore_onend = true;
                            }
                        };

                        recognition.onend = function() {
                            recognizing = false;
                            if (ignore_onend) {
                                return;
                            }
                            start_img.src = 'Images/mic.gif';
                            if (!final_transcript) {
                                showInfo('info_start');
                                return;
                            }
                            showInfo('');
                            if (window.getSelection) {
                                window.getSelection().removeAllRanges();
                                var range = document.createRange();
                                range.selectNode(document.getElementById('final_span'));
                                //range.selectNode(document.getElementById('txtOrgText'));
                                window.getSelection().addRange(range);
                            }
                            if (create_email) {
                                create_email = false;
                                createEmail();
                            }
                        };

                        recognition.onresult = function(event) {
                            var interim_transcript = '';
                            if (typeof(event.results) == 'undefined') {
                                recognition.onend = null;
                                recognition.stop();
                                upgrade();
                                return;
                            }
                            for (var i = event.resultIndex; i < event.results.length; ++i) {
                                if (event.results[i].isFinal) {
                                    final_transcript += event.results[i][0].transcript;
                                } else {
                                    interim_transcript += event.results[i][0].transcript;
                                }
                            }
                            final_transcript = capitalize(final_transcript);
                            final_span.innerHTML = linebreak(final_transcript);
                            txtOrgText.innerHTML = linebreak(final_transcript);
                            interim_span.innerHTML = linebreak(interim_transcript);
                            if (final_transcript || interim_transcript) {
                                showButtons('inline-block');
                            }
                        };
                    }

                    function upgrade() {
                        start_button.style.visibility = 'hidden';
                        showInfo('info_upgrade');
                    }

                    var two_line = /\n\n/g;
                    var one_line = /\n/g;
                    function linebreak(s) {
                        return s.replace(two_line, '<p></p>').replace(one_line, '<br>');
                    }

                    var first_char = /\S/;
                    function capitalize(s) {
                        return s.replace(first_char, function(m) { return m.toUpperCase(); });
                    }
            
                    function startButton(event) {
                        if (recognizing) {
                            recognition.stop();
                            return;
                        }
                        final_transcript = '';
                        recognition.lang = select_dialect.value;
                        recognition.start();
                        ignore_onend = false;
                        final_span.innerHTML = '';
                        interim_span.innerHTML = '';
                        start_img.src = 'Images/mic.gif';
                        showInfo('info_allow');
                        showButtons('none');
                        start_timestamp = event.timeStamp;
                    }

                    function showInfo(s) {
                        if (s) {
                            for (var child = info.firstChild; child; child = child.nextSibling) {
                                if (child.style) {
                                    child.style.display = child.id == s ? 'inline' : 'none';
                                }
                            }
                            info.style.visibility = 'visible';
                        } else {
                            info.style.visibility = 'hidden';
                        }
                    }

                    function reset() {
                        if (recognizing) {
                            recognition.stop();
                        }
                        document.getElementById("final_span").innerHTML = "";
                    }
                </script>

                <div class="main">
                    <table style="width: 720px; padding-top: 20px;" align="center">
                        <tr>
                            <td colspan="3" align="left" style="font-size:12px; color: Red;">
                                <!--   *Note : A Valid Google API Key is required-->
                            </td>
                            <td>
                                <div id="divBranding">
                                </div>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="4" class="filler">
                            </td>
                        </tr>
                        <tr>
                            <!--<td class="style1">
                                Origional Text :
                            </td>-->
                            <td class="style2" colspan="3">
                                <!-- <textarea id="txtOrgText" style="width: 398px; height: 60px; font-family: Calibri, verdana, arial, sans-serif;
                                           font-size: 12px;" name="txtOrgText" rows="8" cols="200"></textarea> -->
                            </td>
                        </tr>
                        <tr>
                            <td colspan="4" class="filler">
                            </td>
                        </tr>
                        <tr>
                            <td class="style1">
                            </td>
                            <td colspan="3">
                                <div id="divDetectedLanguage" style="font-size: 8pt; color: blue;">
                                </div>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="4" class="filler">
                            </td>
                        </tr>
                        <tr>
                            <td class="style1">
                                Source Language :
                            </td>
                            <td class="style4">
                                <select id="selSourceLanguage" name="selSourceLanguage" >
                                </select>
                            </td>
                            <td class="style3">
                                Target Language :
                            </td>
                            <td>
                                <select id="selTargetLanguage" name="selTargetLanguage" >
                                </select>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="4" class="filler">
                            </td>
                        </tr>
                        <tr>
                            <td class="style1">
                            </td>
                            <td align="center" class="style4">
                                <input id="btnDetect" type="button" value="Detect" name="btnDetect" style="width: 70px;" />
                            </td>
                            <td align="center">
                                <input id="btnTranslate" type="button" value="Translate" name="btnTranslate" style="width: 94px;" />
                            </td>
                            <td align="center">
                                <button type="button" id="reset" onclick="reset()">Reset</button>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="4" class="filler">
                            </td>
                        </tr>
                        <tr>
                            <td id="lblTranslation" style="color: white; padding-top: 4px;" valign="top" class="style1">
                                Translated Text:&nbsp;
                            </td>
                            <td colspan="3">
                                <div id="div1" style="font-size: 10pt">
                                </div>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="4" class="filler">
                            </td>
                        </tr>
                        <tr>
                            <td class="style1" colspan="4">
                                <div id="divTranslated" style="font-size: 10pt">
                                </div>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="4" class="filler">
                            </td>
                        </tr>
                    </table>
                </div>
            </div>
        </div>
    </body>
</html>
