<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns="http://www.w3.org/1999/xhtml" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema">

<xsl:template match="root">
<html>
  
	<head>
		<meta charset="UTF-8" />
		<meta name="viewport" content="width=device-width, initial-scale=1.0"/>
		<title><xsl:value-of select="//root/head/esptitle" /></title>
		<link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet" />
		<link type="text/css" rel="stylesheet" href="/materialize.min.css" />
		
		<style>
			body {display: flex;min-height: 100vh;flex-direction: column;}
			main {flex: 1 0 auto;}
			@media (min-width: 995px) and (max-width: 1100px) {#logo-container {font-size: 16px;}}
			@media (max-width: 500px) {#logo-container {font-size: 20px;}}
			@media (max-width: 380px) {#logo-container {font-size: 16px;}}
			@media (max-width: 300px) {#logo-container {font-size: 10px;}}
		</style>
	</head>
  
	<body>
		<header>
		<nav class="" role="navigation">
			<div class="nav-wrapper container small"><a id="logo-container" href="/" class="brand-logo small"><xsl:value-of select="//root/head/esptitle" /></a>
			  <ul class="right hide-on-med-and-down">
				<li><a href="/temperatur/">Temperatur</a></li>
				<li><a href="/vibrator/">Vibrator</a></li>
				<li><a href="/steckdose/">Steckdose</a></li>
				<li><a href="/settings/">Einstellungen</a></li>
				<li><a class="waves-effect waves-light btn" onclick="UserSetPlug()">Steckdose an / aus</a></li>
			  </ul>

			  <ul id="nav-mobile" class="sidenav">
				<li><a class="waves-effect waves-light btn sidenav-close" onclick="UserSetPlug()">Steckdose an / aus</a></li>
				<li><div class="divider"></div></li>
				<li><a href="#!"><i class="tiny material-icons left">info</i>Temperatur: 20,0 °C</a></li>
				<li><div class="divider"></div></li>
				<li><a href="/">Startseite</a></li>
				<li><a href="/temperatur/">Temperatur</a></li>
				<li><a href="/vibrator/">Vibrator</a></li>
				<li><a href="/steckdose/">Steckdose</a></li>
				<li><a href="/settings/">Einstellungen</a></li>
				<li><div class="divider"></div></li>
				<li><a class="sidenav-close" href="#!"><i class="tiny material-icons left">close</i>Menü schließen</a></li>
			  </ul>
			  <a href="#" data-target="nav-mobile" class="sidenav-trigger"><i class="material-icons">menu</i></a>
			</div>
		</nav>
		</header>
		
		<main>
			<div class="container">
			<xsl:apply-templates select="startpage"/>
			<xsl:apply-templates select="settings"/>
			<xsl:apply-templates select="temperatur"/>
			<xsl:apply-templates select="vibrator"/>
			<xsl:apply-templates select="steckdose"/>
			<xsl:apply-templates select="err"/>
			</div>
		</main>
		
		<footer class="page-footer">
		<div class="footer-copyright">
			<div class="container">
				© 2018 by <a class="grey-text text-lighten-4" href="https://github.com/KranzKrone/espwebserver/">KranzKrone</a>
				<a class="grey-text text-lighten-4 right" href="https://github.com/KranzKrone/espwebserver/">Code on GitHub.com</a>
			</div>
		</div>
		</footer>
		
		<script type="text/javascript" src="/materialize.min.js"></script>
		<script type="text/javascript">
			M.AutoInit();

			window.setInterval("time()", 1000);
			var now = new Date('2014-01-01 10:11:55');

			document.addEventListener('DOMContentLoaded', function() {
				var elems = document.querySelectorAll('.sidenav');
				var instances = M.Sidenav.init(elems, options);
			});
			function UserSetPlug() {
				var _url = window.location.origin + "/steckdose/?s20=s20"
				var xhttp = new XMLHttpRequest();
				xhttp.open("GET", _url, true);
				xhttp.send();
				console.log("Lichtschalter wurde gedrückt. " + _url);
			}
			function time() {
				now = new Date(d.getTime() + 1000);
				// element = document.getElementById("time");
				// element.innerHTML = thetime;
				console.log(now);
			}
			
		</script>
	</body>
</html>
</xsl:template> 

<xsl:template match="settings">
  
		<div class="row">
			<div class="col l12 m12 s12">
				<h4>Einstellungen</h4>
			</div>
			<form>
			<div class="col l6 m6 s12">				
				<h5>WiFi</h5>
				<h6>Network 1</h6>
				<div class="input-field col s12">
					<input type="text" name="wid1" class="form-control" value="{//root/settings/wid1}" />
					<label for="wid1">WiFi SSID</label>
				</div>
				<div class="input-field col s12">
					<input type="password" name="wpw1" class="form-control" value="{//root/settings/wpw1}" />
					<label for="wpw1">WiFi Password / User Password</label>
				</div>
				<h6>Network 2</h6>
				<div class="input-field col s12">
					<input type="text" name="wid2" class="form-control" value="{//root/settings/wid2}" />
					<label for="wid2">WiFi SSID</label>
				</div>
				<div class="input-field col s12">
					<input type="password" name="wpw2" class="form-control" value="{//root/settings/wpw2}" />
					<label for="wpw2">WiFi Password / User Password</label>
				</div>
				<h6>Hostname</h6>
				<div class="input-field col s12">
					<input type="text" name="hostname" class="form-control" value="{//root/settings/hostname}" />
					<label for="hostname">Hostname</label>
				</div>
				
			</div>
			<div class="col l6 m6 s12">
				<h5>Main Settings</h5>
				<div class="input-field col s12">
					<input type="text" name="esptitle" class="form-control" value="{//root/settings/esptitle}" maxlength="16" />
					<label for="esptitle">Main Title</label>
				</div>
			</div>
			<div class="col l6 m6 s12">
				<h5>MQTT Settings</h5>
				<div class="input-field col s12">
					<input type="text" name="mqtt_server" class="form-control" value="{//root/settings/mqtt_server}" />
					<label for="mqtt_server">MQTT Broker</label>
				</div>
				<div class="input-field col s12">
					<input type="text" name="mqtt_topic" class="form-control" value="{//root/settings/mqtt_topic}" />
					<label for="mqtt_topic">MQTT Topic</label>
				</div>
			</div>
			<div class="col l6 m6 s12">
				<h5>WebHook Settings</h5>
				<div class="input-field col s12">
					<input type="text" name="wh_url" class="form-control" value="{//root/settings/wh_url}" />
					<label for="wh_url">WebHook URL</label>
				</div>
				<div class="input-field col s12">
					<input type="text" name="wh_fp" class="form-control" value="{//root/settings/wh_fp}" />
					<label for="wh_fp">WebHook Fingerprint</label>
				</div>
			</div>
			<div class="col s12">
				<button class="btn waves-effect waves-light right" type="submit" name="save_eeprom" value="save"><i class="material-icons left">save</i>speichern</button>
			</div>
			</form>
			<div class="col s12">
				<h5>Hinweise</h5>
				<p>Für eine Verbindung mit einem freiem WLAN wird das Passwort-Feld freigelassen.</p>
				<p>Ein WiFi-User wird zum Beispiel in einem WLAN Netzwerk wie eduroam benötigt.</p> 
			</div>
		</div>
		<div class="row">
			<div class="col s12">
				<hr />
				<h4>Konfiguration löschen</h4>
				<p>Hier kann die Konfiguration gelöscht werden, im Anschluss muss der ESP8266 neu eingerichtet werden.</p>
				<form>
					<button type="submit" name="del_eeprom" class="btn red right" value="delete"><i class="material-icons left">delete</i>Konfiguration löschen</button>
				</form>
			</div>
		</div>

</xsl:template>

<xsl:template match="vibrator">
			
	<div class="row">
		<form>
			<div class="input-field col s12">
				<p class="range-field">
					<label for="range">Umdrehungen</label>
					<input type="range" class="range" name="range" id="range" min="0" max="100" value="{//root/vibrator/range}" />
				</p>
			</div>
			<div class="input-field col s12">
				<p class="range-field">
					<label for="rms">Pausen</label>
					<input type="range" class="range" name="rms" id="rms" min="0" max="100" value="{//root/vibrator/rms}" />
				</p>
			</div>
			<div class="col s12">
				<button class="btn waves-effect waves-light right" type="submit"><i class="material-icons left">save</i>setzen</button>
			</div>
		</form>
		
	</div>

</xsl:template>

<xsl:template match="temperatur">
  
		<div class="row">
			<div class="col s12">
				<h4>Temperatur</h4>
			</div>	
			<div class="col l6 m6 s12">
				<h5>Außentemperatur</h5>
				<div class="center-align" style="font-size: 78px; width: 100%;">
					<xsl:value-of select="//root/temperatur/aussentemperatur" /> °C
				</div>
			</div>				
			<div class="col l6 m6 s12">
				<h5>Innentemperatur</h5>
				<div class="center-align" style="font-size: 78px; width: 100%;">
					<xsl:value-of select="//root/temperatur/innentemperatur" /> °C
				</div>
			</div>
			<div class="col s12">
				<span>Messstation: Berlin Franz-Mehring-Platz</span>
			</div>
		</div>

</xsl:template>

<xsl:template match="startpage">
  
		<div class="row">
			<div class="col s12">
				<h1>ESP 8266</h1>
				<p>This is an programming example for ESP8266.</p>
			</div>
			<div class="col s12 m6">
				  <div class="card blue-grey darken-1">
					<div class="card-content white-text">
					  <span class="card-title">Temperature</span>
					  <p>I am a very simple card. I am good at containing small bits of information.
					  I am convenient because I require little markup to use effectively.</p>
					</div>
					<div class="card-action">
					  <a href="#">This is a link</a>
					</div>
				  </div>
			</div>
			<div class="col s12 m6">
				  <div class="card blue-grey darken-1">
					<div class="card-content white-text">
					  <span class="card-title">SONOFF S20</span>
					  <p>I am a very simple card. I am good at containing small bits of information.
					  I am convenient because I require little markup to use effectively.</p>
					</div>
					<div class="card-action">
					  <a href="#" class="waves-effect waves-light btn green">ON</a>
					  <a href="#" class="waves-effect waves-light btn red right">OFF</a>
					</div>
				  </div>
			</div>
			<div class="col s12 m6">
				  <div class="card blue-grey darken-1">
					<div class="card-content white-text">
					  <span class="card-title">Settings</span>
					  <p>I am a very simple card. I am good at containing small bits of information.
					  I am convenient because I require little markup to use effectively.</p>
					</div>
					<div class="card-action right-align">
					  <a href="/settings/" class="right-align btn">Go to Settings</a>
					</div>
				  </div>
			</div>
		</div>

</xsl:template>

<xsl:template match="steckdose">
  
		<div class="row">
			<div class="col s12">
				<h2>ESP 8266</h2>
				<p>This is an programming example for ESP8266.</p>
			</div>
			
			<div class="col s12 m6">
				<div class="card white">
				<div class="card-content">
				<span class="card-title">An | Aus</span>
				<div class="center">
				<span onclick="UserSetPlug()">
					<svg version="1.2" baseProfile="tiny" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:a="http://ns.adobe.com/AdobeSVGViewerExtensions/3.0/" x="0px" y="0px" width="177px" height="202px" viewBox="-0.8 0.5 177 202" xml:space="preserve" style="margin: 20px;">
					<defs></defs>
					<path fill="none" stroke="#000000" stroke-width="30" stroke-linecap="round" d="M33.7,64.3C22.1,77.2,15,94.3,15,113c0,40.1,32.5,72.7,72.7,72.7c40.1,0,72.7-32.5,72.7-72.7c0-18.7-7.1-35.8-18.7-48.7"/>
					<line fill="none" stroke="#000000" stroke-width="30" stroke-linecap="round" x1="87.8" y1="15" x2="87.8" y2="113"/>
					</svg>
				</span>
				</div>
				</div>
				</div>
			</div>
			<div class="col s12 m6">
				  <div class="card blue-grey darken-1">
					<div class="card-content white-text">
					  <span class="card-title">Timer</span>
					  <p>I am a very simple card. I am good at containing small bits of information.
					  I am convenient because I require little markup to use effectively.</p>
					</div>
					<div class="card-action">
					  <a href="#" class="waves-effect waves-light btn green">ON</a>
					  <a href="#" class="waves-effect waves-light btn red right">OFF</a>
					</div>
				  </div>
			</div>
		</div>

</xsl:template>

<xsl:template match="err">
  
		<div class="row">
			<div class="col s12">
				<h2>404</h2>
				<p>404: Page or content not found.</p>
				<a href="/">Hauptseite (Startseite)</a>
			</div>
		</div>

</xsl:template>



</xsl:stylesheet>