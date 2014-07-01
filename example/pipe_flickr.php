<?php
	require_once("../inc/Pipe.php.inc");
	$pipe = new Pipe();
	$pipe->init();
?>

<?php
	$pipe->newPagelet("row-top", "<div class='icon flickr'></div><b>Flickr - Golden Gate Bridge</b>" , false, null);
	$pipe->newPagelet("row-bottom", "<div class='grid-u-1' id='flickr-grid'><p>Loading photos..</p></div>" , false, null);		

	require_once("Helper.php.inc");
	$helper = new Helper();

	$html = $helper->loadFlickr(8);
	$pipe->newPagelet("flickr-grid", $html , false, null, "pipe_flickr.php");		
?>