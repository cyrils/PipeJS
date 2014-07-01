## PipeJS - Minimalistic webpage pipelining framework for PHP

PipeJS lets you create a single-page webapps using YUI and PHP with minimum effort. The framework uses JavaScript to transport webpages in the background and render it on a skeleton page. This is modelled after the Facebook Bigpipe architecture and is suited for small scale projects. If you are not sure what is webpage pipelining, please read <a href="http://www.facebook.com/note.php?note_id=389414033919" target="_blank">Bigpipe</a>.

The basic idea is to decompose web pages into small re-usable chunks called Pagelets and pipeline them through several execution stages inside web servers and browsers. This allows progressive rendering at the front-end and results in exceptional front-end performance.

### Getting started

**On your webpage**

```html
<script src="http://yui.yahooapis.com/3.5.0/build/yui/yui-min.js"></script>
<script type="text/javascript" src="pipejs/js/pipe.js"></script>
<script type="text/javascript">
	window.Y = YUI();
	Y.use('node', 'event', function (Y) {	
		Y.on('domready', function(){
			Pipe.init();
		});
	});
</script>
```

**On your php files**

Keep this at the very beginning of your php (only on pipe files).
```php
<?php
	require_once("pipejs/inc/Pipe.php.inc");
	$pipe = new Pipe();
	$pipe->init();
?>
```

### Sending a pagelet
Now you are all set. Once you have loaded the Pipe libray, sending a pagelet is as simple as:
```php
<?php
	$pipe->newPagelet(string $target_node, string $html, [boolean $append], [array $scripts], [string $url]);
?>
```
**Requesting a url through pipe**

```html
<a href="pipe_home.php" pipe="pipe_home.php">Home</a> 
```
'pipe' attribute on a anchor tag indicates it will be loaded using PipeJS. Anchor tags marked like this will be automatically picked up for pipelining (even from the html dynamically inserted using pipe).

### Invoking a JavaScript class

You can optionally invoke a JavaScript class upon a pagelet load.

```php
<?php
	$scripts = array(array('url'=> 'app.js', 'name'=>'TestApp'));
	$pipe->newPagelet("main-container", $html, true, $scripts, 'example.php');
?>
```
In this example 'TestApp.onPageletArrive' will be invoked after the pagelet load. Dependency file 'app.js' will be automatically loaded - if not already. TestApp should have a default method 'onPageletArrive' to receive the callback.

```javascript
var TestApp = {
	onPageletArrive: function(dom){
		//TODO: do somethin on the pagelet ('dom' is a YUI Node object)
		dom.addClass('zoomin');
	}
}
```

### FAQ

 1. **Can I generate the pagelets parallely?**

 Unfortunately PHP doesn't support multi-threading. If you use a thread-safe language like java/nodejs you can generate the pagelets  parallely. Visit <a href="https://github.com/bigpipe/bigpipe" target="_blank">Bigpipe</a> for a Node.js implementation.
 
 2. **Piplelining isn't working/ I'm not seeing progressive rendering**

 If you think pipelining is not working, thats probably because the server/proxy is buffering the output. Try changing the following configurations in your php.ini file.

 ```
 output_buffering = Off 
 zlib.output_compression = Off 
 ```

 If its still not working, try disabling gzip encoding and/or proxy buffering in your apache/nginx config.
 
### License
PipeJs is released under the MIT License