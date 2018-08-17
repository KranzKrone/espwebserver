<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <html>
  
  <head>
	<meta charset="utf-8" />
	<title>ESP 8266</title>
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<link rel="stylesheet" href="bootstrap.min.css" />
  </head>
  
  <body>
  <div class="container">
	<h1>ESP 8266 - Test</h1>
	<hr />
		<div class="row">
			<div class="col-md-8">
			
				<form>
					<div class="form-group">
						<label for="wid">WiFi SSID</label>
						<input type="text" name="wid" class="form-control" placeholder="WiFi SSID" />
					</div>
					<div class="form-group">
						<label for="wpw">WiFi PWD</label>
						<input type="text" name="wpw" class="form-control" placeholder="WiFi Password" />
					</div>
					<div class="form-group">
						<label for="hostname">hostname</label>
						<input type="text" name="hostname" class="form-control" placeholder="Hostname" value="{$hostname}" />
					</div>
					<div class="form-group">
						<input type="submit" class="btn btn-default btn-lg btn-block" value="speichern" />
					</div>
				</form>
			
			</div>
			<div class="col-md-4">
			
				<p>
				Wird kein WLAN Passwort eingegeben -> wird trotzdem versucht sich mit dem WLAN zuverbinden. Das WLAN Netzwerk wird als frei angesehen. 
				</p>
			
			</div>
		</div>
	</div>
  </body>
  </html>
</xsl:template>

</xsl:stylesheet>