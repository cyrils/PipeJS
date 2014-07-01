<?php
	require_once("../inc/Pipe.php.inc");
	$pipe = new Pipe();
	$pipe->init();
?>

<?php
	$pipe->newPagelet("row-bottom", "<p>Loading...</p>" , false, null);
	$pipe->newPagelet("row-top", "<div class='icon news'></div><b>Latest Headlines</b>" , false, null);
?>

<?php
	require_once("Helper.php.inc");
	$helper = new Helper();

	$scripts = array(array('url'=> 'app.js', 'name'=>'TestApp'));		//js to be loaded and class to be invoked


	$html = $helper->loadNews(6);
	$pipe->newPagelet("row-bottom", "&nbsp;" , false, null, "pipe_news.php");

	for ($i=0; $i < count($html); $i++) { 
		$news = "<div class='grid-u-1-3'>".$html[$i]."</div>";	
		$pipe->newPagelet("row-bottom", $news , true, $scripts);
	}
?>



<div class='code'>
	This page shows how to append to existing content and also to invoke a javascript on pagelet arrive
	<code>
		$scripts = array(array('url'=> 'app.js', 'name'=>'TestApp'));		//js to be loaded and class to be invoked
		<br>$pipe->newPagelet("row-bottom", "html here", true, $scripts, "pipe_news.php");
	</code>

	In this example, <b>'app.js'</b> will be loaded to the DOM, <b>'TestApp.onPageletArrive'</b> will be invoked and URL in the browser will be set to <b>'url_to_be_set.php'</b>
</div>

<?php
	$pipe->newPagelet("row-bottom", "" , true, null);
?>
