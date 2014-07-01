<?php

class Helper
{
	private $path = "pictures";
	private $imgUrl = null;
	public $file = null;
	
	public function __construct() {
		
	}

	public function fetchFile($url){	//only fetches, not saved
		$ch = curl_init($url);
		curl_setopt($ch, CURLOPT_TIMEOUT, 50);
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

		$result = curl_exec($ch);
		curl_close($ch);

		return $result;
	}

	public function loadWhether(){
		$url = "http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%3D2502265&format=json&diagnostics=true";
		$result = $this->fetchFile($url);
		$result = json_decode($result);
		return "<div class='subtitle'><div class='icon weather'></div>".$result->query->results->channel->description."</div>".$result->query->results->channel->item->description;
	}

	public function loadFlickr($count = 8){
		//$url = "http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20flickr.photos.recent%20where%20(api_key%20%3D%20%221895311ec0d2e23431a6407f3e8dffcc%22)&format=json&env=http%3A%2F%2Fdatatables.org%2Falltables.env";
		$url = "https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20flickr.photos.search%20where%20has_geo%3D%22true%22%20and%20text%3D%22Golden%20Gate%20Bridge%22%20and%20api_key%3D%2292bd0de55a63046155c09f1a06876875%22%3B&format=json&diagnostics=true";
		$result = $this->fetchFile($url);	//print $result;
		$result = json_decode($result);
		$photos = $result->query->results->photo;

		$html = "";
		for($i = 0; $i< count($photos) && $i< $count; $i++){
			$photo = $photos[$i];
			$thumbUrl = $this->constructMediumUrl($photo);
			$html .= "<img src='$thumbUrl' class='grid-u-1-4'>";
		}
		return $html;
	}

	public function loadNews($count =  1){
		$url = "http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20rss%20where%20url%3D%22http%3A%2F%2Frss.news.yahoo.com%2Frss%2Ftopstories%22%20limit%20".($count+1)."&format=json&diagnostics=true";
		$result = $this->fetchFile($url);
		$result = json_decode($result);
		
		$html = [];
		for ($i=0; $i < $count && $i< count($result->query->results->item); $i++) { 
			$html[] = "<div class='subtitle'><div class='icon news'></div>".$result->query->results->item[$i]->title."</div>".$result->query->results->item[$i]->description;
		}

		if(count($html) < 2) $html = $html[0];
		return $html;
	}

	public function loadAnswer(){
		$url = "http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20answers.getbycategory%20where%20category_id%3D2115500137%20and%20type%3D%22resolved%22&format=json&diagnostics=true";
		$result = $this->fetchFile($url); //print $result;
		$result = json_decode($result); 
		return "<div class='subtitle'><div class='icon answer'></div>".$result->query->results->Question[0]->Subject."</div>".$result->query->results->Question[0]->Content."<p><b>Answer: </b>".$result->query->results->Question[0]->ChosenAnswer."</p>";
	}

	public function loadFinance(){
		$url = "http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20html%20where%20url%3D%22http%3A%2F%2Ffinance.yahoo.com%2Fq%3Fs%3Dyhoo%22%20and%0A%20%20%20%20%20%20xpath%3D'%2F%2Fdiv%5B%40id%3D%22yfi_headlines%22%5D%2Fdiv%5B2%5D%2Ful%2Fli%2Fa'&format=json&diagnostics=true";
		$result = $this->fetchFile($url);
		$result = json_decode($result);
		
		return "<div class='icon finance'></div><b>Top news on Yahoo Finance: </b>".$result->query->results->a[0]->content;
		
	}

	public function constructThumbUrl($photo){
		return "http://farm{$photo->farm}.staticflickr.com/{$photo->server}/{$photo->id}_{$photo->secret}_t.jpg";
	}

	public function constructMediumUrl($photo){
		return "http://farm{$photo->farm}.staticflickr.com/{$photo->server}/{$photo->id}_{$photo->secret}_q.jpg";
	}
	
}

?>
