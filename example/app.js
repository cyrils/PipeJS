(function(w, d){

var TestApp = function(){
	var self = this;
	
	this.onLoad = function(page){
		Pipe.init();
		Pipe.attachOnPipeStart(self.onStartLoad);
		Pipe.attachOnPipeEnd(self.onEndLoad);
		Pipe.loadPage(page || "pipe_home.php");
	};

	this.onStartLoad = function(){
		console.log(">> starting new pipe");
		self.showLoading();
	};

	this.onEndLoad = function(){
		console.log("[ok]");
		self.hideLoading();
	};

	this.onPageletArrive = function(dom){
		//TODO: do somethin on the dom
		dom.addClass('zoomin');
	};

	this.showLoading = function(){
		self.loader = self.loader || Y.one('#progress');
		self.loader.removeClass('hidden').addClass('loading');

	}

	this.hideLoading = function(){
		self.loader.removeClass('loading').addClass('hidden');		
	}

};


window.TestApp = new TestApp();

})(window, document);
