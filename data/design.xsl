<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns="http://www.w3.org/1999/xhtml" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema">

<xsl:template match="root">
<html>
  
	<head>
		<meta charset="UTF-8" />
		<title><xsl:value-of select="//root/head/esptitle" /></title>
		<link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet" />
		<link type="text/css" rel="stylesheet" href="materialize.min.css"  media="screen,projection"/>
		<link type="text/css" rel="stylesheet" href="/materialize.min.css"  media="screen,projection"/>
		<meta name="viewport" content="width=device-width, initial-scale=1.0"/>
		<style>
			body {display: flex;min-height: 100vh;flex-direction: column;}
			main {flex: 1 0 auto;}
			@media (min-width: 995px) and (max-width: 1100px) {#logo-container {font-size: 16px;}}
			@media (max-width: 450px) {#logo-container {font-size: 20px;}}
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
				<li><a class="waves-effect waves-light btn" onclick="alert('Button wurde gedrückt.')">Steckdose an / aus</a></li>
			  </ul>

			  <ul id="nav-mobile" class="sidenav">
				<li><a class="waves-effect waves-light btn sidenav-close" onclick="console.log('Button Seitenmenü gedrückt.')">Steckdose an / aus</a></li>
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
		
		<script src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
		<script type="text/javascript" src="materialize.min.js"></script>
		<script type="text/javascript" src="/materialize.min.js"></script>
		<script type="text/javascript">(function($){$(function(){$('.sidenav').sidenav();});})(jQuery);</script>

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
				<div class="input-field col s12">
					<input type="text" name="wid" class="form-control" value="{//root/settings/wid}" />
					<label for="wid">WiFi SSID</label>
				</div>
				<div class="input-field col s12">
					<input type="text" name="wuser" class="form-control" value="{//root/settings/wuser}" />
					<label for="wuser">WiFi User</label>
				</div>
				<div class="input-field col s12">
					<input type="password" name="wpw" class="form-control" value="{//root/settings/wpw}" />
					<label for="wpw">WiFi Password / User Password</label>
				</div>
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
					<input type="range" name="range" id="range" min="0" max="100" value="{//root/vibrator/range}" />
				</p>
			</div>
			<div class="input-field col s12">
				<p class="range-field">
					<label for="rms">Pausen</label>
					<input type="range" name="rms" id="rms" min="0" max="100" value="{//root/vibrator/rms}" />
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
				<a href="/" onclick="alert('Status der Steckdose wurde geändert.');">
					<svg version="1.2" baseProfile="tiny" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:a="http://ns.adobe.com/AdobeSVGViewerExtensions/3.0/" x="0px" y="0px" width="177px" height="202px" viewBox="-0.8 0.5 177 202" xml:space="preserve" style="margin: 20px;">
					<defs></defs>
					<path fill="none" stroke="#000000" stroke-width="30" stroke-linecap="round" d="M33.7,64.3C22.1,77.2,15,94.3,15,113c0,40.1,32.5,72.7,72.7,72.7c40.1,0,72.7-32.5,72.7-72.7c0-18.7-7.1-35.8-18.7-48.7"/>
					<line fill="none" stroke="#000000" stroke-width="30" stroke-linecap="round" x1="87.8" y1="15" x2="87.8" y2="113"/>
					</svg>
				</a>
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



</xsl:stylesheet>