<!DOCTYPE html>
<html>
<head>
<title>Pilelining Demo</title>
</head>
<link rel="stylesheet" href="style.css" type="text/css" media="all" />
<body class="yui3-skin-sam">

<!-- This is the skeleton in which pagelets will be loaded -->

<div class='container'>
	<div class="grid-g main-container left padded" id="main-container">
		<div class="menu" id="menu"><a href="pipe_home.php" pipe="pipe_home.php">Home</a> | <a href="pipe_news.php" pipe="pipe_news.php">News</a> | <a href="pipe_flickr.php" pipe="pipe_flickr.php">Flickr</a></div>
		<div class="title">Pipelining Demo</div>
		<div class="grid-u-1" id="row-top">Loading...</div>
		<div id="row-bottom">
		</div>
	</div>
</div>

<div id='progress' class='progress hidden'><div class='ball'></div></div>

<div class='footer'>Copyright 2014 Yahoo! Inc.</div>

<script type="text/javascript" src="../js/pipe.js"></script>
<script src="http://yui.yahooapis.com/3.5.0/build/yui/yui-min.js"></script>
<script src="app.js"></script>
<script type="text/javascript">
	var page = "<?php print @$_GET['page']?>";

	if(!window.Y) { window.Y = YUI(); }
	Y.use('node', 'event', 'yql', function (Y) {	
		Y.on('domready', function(){
			window.TestApp.onLoad(page);
		});
	});
</script>
</body>
</html>