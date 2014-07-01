<?php
	require_once("../inc/Pipe.php.inc");
	$pipe = new Pipe();
	$pipe->init();
?>

<div class="grid-u-1-3" id="col-1"><p>Loading...</p></div>
<div class="grid-u-1-3" id="col-2"><p>Loading...</p></div>
<div class="grid-u-1-3" id="col-3"><p>Loading...</p></div>
<?php
	$pipe->newPagelet("row-bottom", "" , false, null);	//flush the above layout
	$pipe->newPagelet("row-top", "Loading..." , false, null);
?>

<?php
	require_once("Helper.php.inc");
	$helper = new Helper();

	$weather = $helper->loadWhether();
	$pipe->newPagelet("col-1", $weather , false, null, "./");	//load whether on col-1

	$news = $helper->loadNews();
	$pipe->newPagelet("col-2", $news , false, null);

	$answer = $helper->loadFlickr();
	$pipe->newPagelet("col-3", $answer , false, null);

	$finance = $helper->loadFinance();
	$pipe->newPagelet("row-top", $finance , false, null);
	
?>