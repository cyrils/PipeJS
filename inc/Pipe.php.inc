<?php
/**
	@author Cyril Sebastian

	Copyrights for code authored by Yahoo! Inc. is licensed under the following
	terms:
	MIT License
	Copyright 2014 Yahoo! Inc.

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
	of the Software, and to permit persons to whom the Software is furnished to do
	so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
	*/
	
class Pipe
{
	private $count = 0;
	public $pipeOn = true;
	public $fromHistory = false;

	public function __construct() {
		$pipeOn =  @$_GET['pipe'];
		$this->pipeOn = ($pipeOn) ? true : false;
	}
	
	public function init(){
		if(!$this->pipeOn){
			header("location: index.php?page=".urlencode($_SERVER['PHP_SELF']));
			//print ("index.php?page=".urlencode($_SERVER['PHP_SELF']));
			exit();
		}

		@apache_setenv('no-gzip', 1);
	    @ini_set('zlib.output_compression', 0);
	    @ini_set('implicit_flush', 1);
	    
	    print str_pad('',1024); 
		flush();
		ob_start();
	}
	
	public function newPagelet($target, $html, $append = false, $scripts = array(), $url = ""){
		$append = ($append) ? 'true' : 'false';
		$script_list = is_array($scripts) ? json_encode($scripts) : "\"\"";
		
		if($html) print($html);
		$html = ob_get_clean();

		print "
		<script>
			var pagelet$this->count = {
				target: \"$target\",
				html: \"".str_replace("\n", "", addslashes($html)) ."\",
				append: $append,
				url: \"$url\",
				scripts: $script_list,
				pipe: \"".$_SERVER['PHP_SELF']."\"
			};
			parent.Pipe.pageletLoaded(pagelet$this->count);
		</script>
		";

		print "\r\n";

		ob_flush();
		flush();
    	
    	ob_start();

		$this->count++;
	}
}

?>
