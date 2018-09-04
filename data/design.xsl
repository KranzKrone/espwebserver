<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns="http://www.w3.org/1999/xhtml" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema">

<xsl:template match="root">
<html>
  
	<head>
		<meta charset="UTF-8" />
		<title><xsl:value-of select="//root/head/title" /></title>
		<link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet" />
		<!-- <link type="text/css" rel="stylesheet" href="materialize.min.css"  media="screen,projection"/>-->
		<link type="text/css" rel="stylesheet" href="https://st-page.de/other/materialize.min.css"  media="screen,projection"/>
		<meta name="viewport" content="width=device-width, initial-scale=1.0"/>
	</head>
  
	<body>
	
		<nav class="" role="navigation">
			<div class="nav-wrapper container"><a id="logo-container" href="/" class="brand-logo">ESP 8266</a>
			  <ul class="right hide-on-med-and-down">
				<li><a href="/temperatur/">Temperatur</a></li>
				<li><a href="/vibrator/">Vibrator</a></li>
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
				<li><a href="/settings/">Einstellungen</a></li>
				<li><div class="divider"></div></li>
				<li><a class="sidenav-close" href="#!"><i class="tiny material-icons left">close</i>Menü schließen</a></li>
			  </ul>
			  <a href="#" data-target="nav-mobile" class="sidenav-trigger"><i class="material-icons">menu</i></a>
			</div>
		</nav>
		
		<div class="container">
		<xsl:apply-templates select="settings"/>
		<xsl:apply-templates select="temperatur"/>
		<xsl:apply-templates select="vibrator"/>
		</div>
		
		<script src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
		<!-- <script type="text/javascript" src="materialize.min.js"></script> -->
		<script type="text/javascript" src="https://st-page.de/other/materialize.min.js"></script>
		<script type="text/javascript">(function($){$(function(){$('.sidenav').sidenav();});})(jQuery);</script>

	</body>
</html>
</xsl:template> 

<xsl:template match="settings">
  
		<div class="row">
			
			<div class="col l6 m8 s12">
				<h4>Einstellungen</h4>
				
				<div class="row">
				<form>
					<div class="input-field col s12">
						<input type="text" name="wid" class="form-control" value="{//root/settings/wid}" />
						<label for="wid">WiFi SSID</label>
					</div>
					<div class="input-field col s12">
						<input type="text" name="wpw" class="form-control" value="{//root/settings/wpw}" />
						<label for="wpw">WiFi Passwort</label>
					</div>
					<div class="input-field col s12">
						<input type="text" name="hostname" class="form-control" value="{//root/settings/hostname}" />
						<label for="hostname">Hostname</label>
					</div>
					<div class="col s12">
						<button class="btn waves-effect waves-light right" type="submit"><i class="material-icons left">save</i>speichern</button>
					</div>
				</form>
				</div>
			
			</div>
			<div class="col l6 m4 s12">
				<h4>Hinweise</h4>
				<p>Wird kein WLAN Passwort eingegeben -> wird trotzdem versucht sich mit dem WLAN zuverbinden. Das WLAN Netzwerk wird als frei angesehen.</p>
			
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

</xsl:stylesheet>