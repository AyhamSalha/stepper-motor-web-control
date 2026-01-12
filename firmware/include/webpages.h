#ifndef WEBPAGES_H
#define WEBPAGES_H

#include <Arduino.h>

// Start Page - Main landing page with start button
const String startPage = R"rawliteral(
<!DOCTYPE html><html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body {font-family: Arial, sans-serif; background:#f0f0f0; display:flex; justify-content:center; align-items:center; height:100vh; margin:0;}
.container {background:#fff; padding:30px; border-radius:15px; box-shadow:0 5px 15px rgba(0,0,0,0.1); text-align:center; width:90%; max-width:400px;}
button {font-size:1.5em; padding:20px 50px; border:none; border-radius:10px; background:#007bff; color:white; cursor:pointer;}
p.signature {font-size:12px; color:gray; margin-top:40px;}
</style>
</head>
<body>
<div class="container">
  <h2>Schrittmotor Steuerung</h2>
  <form action="/input">
    <button type="submit">Start</button>
  </form>
  <p class="signature">Ayham Salha</p>
</div>
</body>
</html>
)rawliteral";

// Input Page - Parameter input form
const String inputPage = R"rawliteral(
<!DOCTYPE html><html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body {font-family: Arial, sans-serif; background:#f0f0f0; display:flex; justify-content:center; align-items:center; height:100vh; margin:0;}
.container {background:#fff; padding:30px; border-radius:15px; box-shadow:0 5px 15px rgba(0,0,0,0.1); text-align:center; width:90%; max-width:400px;}
label {display:block; margin-top:20px; margin-bottom:5px; font-weight:bold;}
input[type=range] {width:100%;}
button {margin-top:30px; padding:15px 30px; font-size:1.2em; background:#007bff; color:white; border:none; border-radius:10px; cursor:pointer;}
p.signature {margin-top:40px; font-size:0.8em; color:gray;}
</style>
</head>
<body>
<div class="container">
  <h2>Parameter eingeben</h2>
  <form action="/submit">
    <label for="distance">Strecke (max 30cm): <span id="distanceVal">10</span> cm</label>
    <input type="range" id="distance" name="distance" min="1" max="30" value="10" oninput="distanceVal.innerText=this.value">
    <label for="runden">Runden (max 10): <span id="rundenVal">2</span></label>
    <input type="range" id="runden" name="runden" min="1" max="10" value="1" oninput="rundenVal.innerText=this.value">
    <label for="speed">Geschwindigkeit: <span id="speedVal">5</span></label>
    <input type="range" id="speed" name="speed" min="1" max="10" value="5" oninput="speedVal.innerText=this.value">
    <button type="submit">Senden</butaton>
  </form>
  <p class="signature">Ayham Salha</p>
</div>
<script>
  document.getElementById('distanceVal').innerText = document.getElementById('distance').value;
  document.getElementById('rundenVal').innerText   = document.getElementById('runden').value;
  document.getElementById('speedVal').innerText    = document.getElementById('speed').value;
</script>
</body>
</html>
)rawliteral";

// Stop Page - Shows when motor is running
const String stopPage = R"rawliteral(
<!DOCTYPE html><html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body {font-family: Arial, sans-serif; background:#f0f0f0; display:flex; justify-content:center; align-items:center; height:100vh; margin:0;}
.container {background:#fff; padding:30px; border-radius:15px; box-shadow:0 5px 15px rgba(0,0,0,0.1); text-align:center; width:90%; max-width:400px;}
button {font-size:1.5em; padding:20px 50px; border:none; border-radius:10px; background:#dc3545; color:white; cursor:pointer;}
p.signature {font-size:12px; color:gray; margin-top:40px;}
</style>
</head>
<body>
<div class="container">
  <h2>Motor laeuft...</h2>
  <form action="/stop">
    <button type="submit">STOP</button>
  </form>
  <p class="signature">Ayham Salha</p>
</div>
</body>
</html>
)rawliteral";

#endif // WEBPAGES_H
