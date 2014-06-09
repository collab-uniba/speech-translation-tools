
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/html">
    <head>
        <title>Reconhecedor de Voz</title>

        <script type="text/javascript" src="javascript/jquery-1.11.0.js"></script>
        <script type="text/javascript" src="javascript/chroma.js"></script>
        <link type="text/css" rel="stylesheet" href="css/style.css"></link>
    </head>

    <body>
       
        <h2>Reconhecimento de Voz, Transcricao e Fala</h2>

        <div id="instructions"></div>

        <input type="button" id="EscolherIngles" value="Speak in English" onclick="mudarLinguaParaInglesUS();">
        <input type="button" id="EscolherPortugues" value="Speak in Brazilian Portuguese" onclick="mudarLinguaParaPortugues();">
        <input type="button" id="EscolherItaliano" value="Reproduzir Italian" onclick="mudarLinguaParaItaliano();">
        
        <p id="controls">
            <button id="start_button">Iniciar</button>
        </p>

        <canvas id="canvas" width="800" height="120" ></canvas>

        <h3>Texto gerado a partir do reconhecimento da voz.</h3>

        <div id="transcript" style="height: 100px"></div>

        <input type="button" id="traduzir" value="Traduzir" onclick="enviarDadosParaTraducaoEN_PT();">
        <input type="button" id="traduzir" value="Traduzir" onclick="enviarDadosParaTraducaoEN_IT();">
        
        
        <div id="translation" style="height: 100px; border: solid 1px"></div>

        <input type="button" id="ReproduzirIngles" value="Reproduzir Inglês">
        <input type="button" id="ReproduzirPortugues" value="Reproduzir Português">
        <input type="button" id="ReproduzirItaliano" value="Reproduzir Italiano">
        
        <script type="text/javascript">

            $("#teste3").click(function() {
                alert("Verificando se o jquery esta instalado");
            });
            
            window.requestAnimFrame = (function() {
                return window.requestAnimationFrame ||
                        window.webkitRequestAnimationFrame ||
                        window.mozRequestAnimationFrame ||
                        window.oRequestAnimationFrame ||
                        window.msRequestAnimationFrame ||
                        function(callback, element) {
                            window.setTimeout(callback, 1000 / 60);
                        };
            })();

            /* Variaveis globais para o audio */
            var audio_context;
            var source_node;
            var analyser;
            var javascript_node;
            var audio_stream;
            var array = [];

            /* Variaveis globais para o desenho do spectro */
            var x = 0;
            var canvas_width = 800;
            var canvas_height = 256;
            var ctx;

            /* Usa a biblioteca do chroma. */
            var hot = new chroma.ColorScale({
                // colors: ['#000000', '#ff0000', '#ffff00', '#ffffff'],
                colors: ['#000080', '#157780', '#78d38d', '#ffffe0'],
                //positions: [0, .25, .75, 1],
                positions: [0, .25, .75, 1],
                mode: 'rgb',
                limits: [0, 256]
            });

            /* Variaveis globais do reconhecedor de voz */
            var final_transcript = '';
            var recognizing = false;
            /* Linguagem do reconhecedor, altere para a de sua preferencia. */
            var language = 'en-US';
            //var language = 'pt-BR';

            var recognition = new webkitSpeechRecognition();
            recognition.continuous = true; // keep processing input until stopped
            recognition.interimResults = true; // show interim results
            recognition.lang = language;// specify the language

            $(document).ready(function() {

                /* Verifica o suporte do browser para a API. */
                if (!('webkitSpeechRecognition' in window)) {
                    alert("Your Browser does not support the Speech API");
                } else {
                    /* Recupera o contexto do canvas para desenhar. */
                    ctx = $("#canvas").get()[0].getContext("2d");
                    clearCanvas();
                    /* Instancia o container de audio, que eh o nodo principal de todos os elementos de audio. */
                    try {
                        audio_context = new webkitAudioContext();
                    }
                    catch (e) {
                        alert('Web Audio API is not supported in this browser');
                    }

                    try {
                        navigator.webkitGetUserMedia({audio: true}, setupAudioNodes, onError);
                    } catch (e) {
                        alert('webkitGetUserMedia threw exception :' + e);
                    }

                    // Create the recognition object and define four event handlers (onstart, onerror, onend, onresult)
                    /*var recognition = new webkitSpeechRecognition();
                    recognition.continuous = true; // keep processing input until stopped
                    recognition.interimResults = true; // show interim results
                    recognition.lang = language;*/// specify the language

                    recognition.onstart = function() {

                        recognition.lang = language;
                        
                        //alert(recognition.lang);
                        recognizing = true;
                        $('#instructions').html('Fale calmamente e em voz alta.');
                        $('#start_button').html('Parar');
                        clearCanvas();
                        // setup the event handler that is triggered every time enough samples have been collected
                        // trigger the audio analysis and draw one column in the display based on the results
                        javascript_node.onaudioprocess = function() {
                            analyser.getByteFrequencyData(array);
                            requestAnimFrame(drawSpectrogram);
                        };

                    };
                    recognition.onerror = function(event) {
                        console.log("There was a recognition error...");
                    };
                    recognition.onend = function() {
                        recognizing = false;
                        $('#instructions').html('Completo');
                    };
                    recognition.onresult = function(event) {
                        var interim_transcript = '';
                        // Assemble the transcript from the array of results
                        for (var i = event.resultIndex; i < event.results.length; ++i) {
                            if (event.results[i].isFinal) {
                                final_transcript += event.results[i][0].transcript;
                                console.log("final:    " + final_transcript);
                            } else {
                                interim_transcript += event.results[i][0].transcript;
                                console.log("interim:  " + interim_transcript);
                            }
                        }

                        // update the web page
                        if (final_transcript.length > 0) {
                            $('#transcript').html(final_transcript);
                        }
                    };
                    $("#start_button").click(function(e) {
                        
                        if(language === '') {
                            alert("You must pick a language first");
                            return;
                        }
                        //alert(recognition.lang);
                        e.preventDefault();
                        if (recognizing) {
                            // button currently shows 'click to stop'
                            recognition.stop();
                            javascript_node.onaudioprocess = null;
                            $('#start_button').html('Click to Start Again');
                            recognizing = false;
                        } else {
                            // button currently shows 'click to start' 
                            final_transcript = '';
                            // Request access to the User's microphone and Start recognizing voice input
                            recognition.start();
                            $('#instructions').html('Allow the browser to use your Microphone');
                            $('#start_button').html('waiting');
                            $('#transcript').html('&nbsp;');
                        }
                    });
                }
            });
            function onError(e) {
                console.log(e);
            }








            
            function setupAudioNodes(stream) {
                var sample_size = 1024; // number of samples to collect before analyzing FFT
                // descreasing this gives a faster sonogram, increasing it slows it down

                audio_stream = stream;
                // create an audio buffer source node
                source_node = audio_context.createMediaStreamSource(audio_stream);
                // Set up the javascript node
                javascript_node = audio_context.createJavaScriptNode(sample_size, 1, 1);
                // setup the analyzer node
                analyser = audio_context.createAnalyser();
                analyser.smoothingTimeConstant = 0.0;
                analyser.fftSize = 1024; // must be power of two
                // connect the nodes together
                source_node.connect(analyser);
                analyser.connect(javascript_node);
                javascript_node.connect(audio_context.destination);
                // optional - connect input to audio output (speaker) - not necessary here
                // source_node.connect(audio_context.destination);

                // allocate the freq data array
                array = new Uint8Array(analyser.frequencyBinCount);
            }

            // Draw the Spectrogram from the frequency array
            function drawSpectrogram() {

                var step = 1;
                for (var i = 0; i < array.length; i += step) {
                    // Get the color for each pixel from a color map
                    var value = array[i];
                    ctx.beginPath();
                    ctx.strokeStyle = hot.getColor(value).hex();
                    // draw a 1 pixel line on the canvas
                    var y = canvas_height - i / step;
                    ctx.moveTo(x, y);
                    ctx.lineTo(x + 1, y);
                    ctx.closePath(); // needs close path as we are drawing tiny rectangles ?
                    ctx.stroke();
                }

                // loop around the canvas when we reach the end
                x = x + 1;
                if (x >= canvas_width) {
                    x = 0;
                    clearCanvas();
                }
            }
            function clearCanvas() {
                ctx.clearRect(0, 0, canvas_width, canvas_height);
                x = 0;
            }
/*
            var langs =
                    [
                        ['English', 
                            ['en-GB', 'United Kingdom'],
                            ['en-US', 'United States']],
                        /*['Español', ['es-AR', 'Argentina'],
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
                         ['Français', ['fr-FR']],*/
                      /*  ['Italiano', ['it-IT', 'Italia'],
                            ['it-CH', 'Svizzera']],
                        ['Português', ['pt-BR', 'Brasil'],
                            ['pt-PT', 'Portugal']]
                    ];

            for (var i = 0; i < langs.length; i++) {
                select_language.options[i] = new Option(langs[i][0], i);
            }
            select_language.selectedIndex = 1;
            updateCountry();
            select_dialect.selectedIndex = 2;

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
*/


        </script>

        <script>
            /* Componente que reproduz o som, ou seja, fala o que estava escrito na div transcript. */
            var voices = [];
            $(document).ready(function() {

                // var ischrome = navigator.userAgent.match(/chrome/i);
                // if(ischrome) {

                // var u2 = new SpeechSynthesisUtterance();
                // var u3 = new SpeechSynthesisUtterance();
                // voices = window.speechSynthesis.getVoices();
                voices = window.speechSynthesis.getVoices();
                
                console.log('Get voices ' + voices.length.toString());
                
                for (var i = 0; i < voices.length; i++) {
                    
                    console.log("Voice " + i.toString() + ' ' + voices[i].name);
                    
                }
                


                $("#ReproduzirIngles").on('click', function(e) {
                    var textoAux = document.getElementById('translation').innerHTML;
                    //alert(textoAux);
                    var texto = textoAux;
                    var u1 = new SpeechSynthesisUtterance(texto);
                    u1.lang = 'en-US';
                    u1.pitch = 1;
                    u1.rate = 1;
                    u1.voice = voices[10];
                    u1.voiceURI = 'native';
                    u1.volume = 1;
                    speechSynthesis.speak(u1);
                    console.log("Voice " + u1.voice.name);
                });
                
                $("#ReproduzirPortugues").on('click', function(e) {
                    /*var textoAux = document.getElementById('translation').innerHTML;
                    var texto = textoAux;
                    var u1 = new SpeechSynthesisUtterance(texto);
                    u1.lang = 'pt-BR';
                    u1.pitch = 1;
                    u1.rate = 1;
                    u1.voice = voices[10];
                    //u1.voiceURI = 'native';
                    u1.volume = 1;
                    speechSynthesis.speak(u1);
                    console.log("Voice " + u1.voice.name);*/
        
                    chrome.tts.speak('Hello, world.', {'rate': 2.0});
                });
                
                $("#ReproduzirItaliano").on('click', function(e) {
                    var textoAux = document.getElementById('translation').innerHTML;
                    //alert(textoAux);
                    var texto = textoAux;
                    alert(texto);
                    var u1 = new SpeechSynthesisUtterance(texto);
                    u1.lang = 'it-IT';
                    u1.pitch = 1;
                    u1.rate = 1;
                    u1.voice = voices[10];
                    //u1.voiceURI = 'native';
                    u1.volume = 1;
                    speechSynthesis.speak(u1);
                    console.log("Voice " + u1.voice.name);
                });
            });

        </script>

    <script>
        function translateText(response) {
            document.getElementById("translation").innerHTML += "" + response.data.translations[0].translatedText;
        }
    </script>
    <script>
        
        function enviarDadosParaTraducaoEN_PT() {
            var newScript = document.createElement('script');
            newScript.type = 'text/javascript';
            var sourceText = escape(document.getElementById("transcript").innerHTML);
            //alert(sourceText);
            // WARNING: be aware that YOUR-API-KEY inside html is viewable by all your users.
            // Restrict your key to designated domains or use a proxy to hide your key
            // to avoid misuage by other party.
            var source = 'https://www.googleapis.com/language/translate/v2?key=AIzaSyCq1JQCESjgNTc4iM1tXMzEo9d2uVf3IP8&source=en&target=pt&callback=translateText&q=' + sourceText;
            
            //alert(source);    
            newScript.src = source;

            // When we add this script to the head, the request is sent off.
            document.getElementsByTagName('head')[0].appendChild(newScript);
        }
        
        function enviarDadosParaTraducaoEN_IT() {
            var newScript = document.createElement('script');
            newScript.type = 'text/javascript';
            var sourceText = escape(document.getElementById("transcript").innerHTML);
            //alert(sourceText);
            // WARNING: be aware that YOUR-API-KEY inside html is viewable by all your users.
            // Restrict your key to designated domains or use a proxy to hide your key
            // to avoid misuage by other party.
            var source = 'https://www.googleapis.com/language/translate/v2?key=AIzaSyCq1JQCESjgNTc4iM1tXMzEo9d2uVf3IP8&source=en&target=it&callback=translateText&q=' + sourceText;
            
            //alert(source);    
            newScript.src = source;

            // When we add this script to the head, the request is sent off.
            document.getElementsByTagName('head')[0].appendChild(newScript);
        }
        
        function mudarLinguaParaPortugues() {
            language = 'pt-BR';
            recognition.lang = language;
        }
        
        function mudarLinguaParaItaliano() {
            language = 'it-IT';
            recognition.lang = language;
        }
        
        function mudarLinguaParaInglesUS() {
            language = 'en-US';
            recognition.lang = language;
        }
    </script>
    </body>
</html>
