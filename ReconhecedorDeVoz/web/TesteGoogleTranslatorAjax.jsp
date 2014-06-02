
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8" />
<title>webkit speech test</title>

<style type="text/css">
body, input
{
	font-family: sans-serif;
	font-size: 100%;
	color: #333;
	background-color: #fff;
}

form
{
	margin: 2em 20%;
}

input, label
{
	font-family: sans-serif;
	font-size: 1.2em;
	border-radius: 5px;
}

h1
{
	font-size: 1.4em;
	font-weight: normal;
	margin: 0 0 0.2em 0;
}

p
{
	margin: 0 0 1em 0;
}

pre
{
	padding: 2px 4px;
	margin: 1em 0 1.5em 3em;
	background-color: #eee;
	border: 1px solid #ddd;
}

.nosupport
{
	display: none;
	color: #c00;
}
</style>

</head>
<body>

<h1>Webkit Speech Input Teste</h1>

<p class="nosupport">Your browser does not support webkit speech so a standard input box will be shown.</p>

<form action="index.html" method="get">
<div>
<label for="speech">Speech test:</label>
<input type="text" x-webkit-speech="x-webkit-speech" />
</div>
</form>

<p>Speech support can be implemented with the following code:</p>

<pre><code>&lt;input type=&quot;text&quot; x-webkit-speech /&gt;</code></pre>

<script>
if (document.createElement("input").webkitSpeech === undefined) {
	var ns = document.getElementsByClassName("nosupport");
	for (i = 0, il = ns.length; i < il; i++) ns[i].style.display = "block";
}
</script>
</body>
</html>