<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns="http://www.w3.org/1999/xhtml" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:xs="http://www.w3.org/2001/XMLSchema">

<xsl:template match="root">
  <html>
  
  <head>
	<meta charset="utf-8" />
	<title><xsl:value-of select="//root/head/title" /></title>
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0-rc.2/css/materialize.min.css" />
	

  </head>
  
  <body class="container">
	
	
	
	
	<div class = "row">
         <div class = "col s12 m12 l12" >
            <nav>
    <div class="nav-wrapper">
      <a href="#!" class="brand-logo">Logo</a>
      <a href="#" data-target="mobile-demo" class="sidenav-trigger">Test</a>
      <ul class="right hide-on-med-and-down">
        <li><a href="sass.html">Sass</a></li>
        <li><a href="badges.html">Components</a></li>
        <li><a href="collapsible.html">Javascript</a></li>
        <li><a href="mobile.html">Mobile</a></li>
      </ul>
    </div>
  </nav>

  <ul class="sidenav" id="mobile-demo">
    <li><a href="sass.html">Sass</a></li>
    <li><a href="badges.html">Components</a></li>
    <li><a href="collapsible.html">Javascript</a></li>
    <li><a href="mobile.html">Mobile</a></li>
  </ul>
         </div>
      </div>
	
	
		
  
          

	<xsl:apply-templates select="settings"/>
	
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0-rc.2/js/materialize.min.js"></script>
	
		<script>
	 
			document.addEventListener('DOMContentLoaded', function() {
    var elems = document.querySelectorAll('.sidenav');
    var instances = M.Sidenav.init(elems, options);
  });
	 
		</script>
  </body>
  </html>
</xsl:template> 


<xsl:template match="settings">
  
	
		<div class="row">
			
			<div class="col m8 s12">
				<h3>ESP 8266 - Test</h3>
				<form>
					<div class="form-group">
						<label for="wid">WiFi SSID</label>
						<input type="text" name="wid" class="form-control" placeholder="WiFi SSID" value="{//root/settings/wid}" />
					</div>
					<div class="form-group">
						<label for="wpw">WiFi PWD</label>
						<input type="text" name="wpw" class="form-control" placeholder="WiFi Password" value="{//root/settings/wpw}" />
					</div>
					<div class="form-group">
						<label for="hostname">Hostname</label>
						<input type="text" name="hostname" class="form-control" placeholder="Hostname" value="{//root/settings/hostname}" />
					</div>
					<div class="form-group">
						<input type="submit" class="btn btn-default btn-lg btn-block" value="speichern" />
					</div>
				</form>
			
			</div>
			<div class="col m4 s12">
			
				<p>
				Wird kein WLAN Passwort eingegeben -> wird trotzdem versucht sich mit dem WLAN zuverbinden. Das WLAN Netzwerk wird als frei angesehen. 
				</p>
			
			</div>
		</div>

</xsl:template>

</xsl:stylesheet>