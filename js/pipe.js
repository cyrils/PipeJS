(function(w, d){

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

var Pipe = function(args){
	var self = this;
	this.pipeBase = "pipe.php";
	this.jsMap = {};	// js register
	this.cssMap = {};	// css map
	this.maxHooks = 20;		//for performance reasons
	
	this.init = function(){
		self.hookAnchorTags(document);

		self.iframe = self.createEl("iframe", {allowtransparency: "true", frameborder: "0", hspace: "0", marginheight: "0", marginwidth: "0", scrolling: "no", tabindex: "0", vspace: "0"});
		self.iframe.style.cssText="width: 10px; height: 10px; position: absolute; left: -100px;";
		document.body.appendChild(self.iframe);
	};

	this.hookAnchorTags = function(dom){
		var anchors = Y.one(dom).all("a")._nodes;
		for (var i = anchors.length - 1; i >= 0; i--) {
			if(!anchors[i].getAttribute("pipe")) continue;

			self.on(anchors[i], "click", (function(a){ return function(e){
				var pipeUrl = a.getAttribute("pipe");
				self.loadPage(pipeUrl, a);
				self.cancelEvent(e);
			}})(anchors[i]));
		}
	};

	this.destroy = function(className){
		//this.jsMap = [];
		//TODO:
	};

	this.loadPage = function(url, a, callBack){
		self.onPipeStart && self.onPipeStart(a);
		var q = (url.indexOf("?") > 0) ? '&' : '?';
		self.iframe.src = url+q+"pipe=true&rand="+parseInt(Math.random()*1000);//self.pipeBase + "?url=" + encodeURIComponent(url);
		self.iframe.onload = function(){
			callBack && callBack(a);
			self.onPipeEnd & self.onPipeEnd(a);
		}
		self.hooksSoFar = 0;
	};

	this.pageletLoaded = function(data){
		var dom = Y.Node.create(data.html);
		var targetDiv = self.one(data.target);

		self.hooksSoFar++;
		if(self.hooksSoFar < self.maxHooks) self.hookAnchorTags(dom);
		
		if(!data.append) Y.one(targetDiv).empty();
		Y.one(targetDiv).append(dom);
		if(data.url){
			history.replaceState({page: data.url, pipe: data.pipe}, null, data.url);
		}
		if(data.scripts && data.scripts.length){
			for (var i = data.scripts.length - 1; i >= 0; i--) {
				self.loadJS(data.scripts[i].url, data.scripts[i].name, dom);
			};
		}
	};

	this.loadJS = function(url, name, node){
		if(self.jsMap[url] || window[name]){
			if(window[name] && window[name].onPageletArrive) window[name].onPageletArrive(node);
			return;		//js already loaded, call and return
		}

		var script = document.createElement("script");
		script.type = "text/javascript";
		script.onload = function(){		//script loaded, call onLoad
			self.jsMap[url] = true;
			var obj = window[name];
			if(obj && typeof obj.onPageletArrive === 'function') {
			    obj.onPageletArrive(node);
			}
		};
		script.src = url;
		document.getElementsByTagName("head")[0].appendChild(script);
	};

	this.loadCSS = function(url){
		//TODO: css register
		//if(self.cssMap[url]) return;

		var myStyle = document.createElement("link");
			myStyle.type = 'text/css';
			myStyle.rel = "stylesheet";
			myStyle.href = url;
		document.body.appendChild(myStyle);
	};

	this.attachOnPipeStart = function(callBack){
		self.onPipeStart = callBack;
	};

	this.attachOnPipeEnd = function(callBack){
		self.onPipeEnd = callBack;
	};

	this.on = function(target, eventName, handlerName){
		if ( target.addEventListener ){
			target.addEventListener(eventName, handlerName, false);
		} else if ( target.attachEvent ){
			target.attachEvent("on" + eventName, handlerName);
		}
	};

	this.cancelEvent = function(e) {
		var e = window.event || e;
	    if (typeof e.preventDefault == "function") e.preventDefault();
	    else e.returnValue = false;
	};

	this.createEl = function(tag, props){
		var node = document.createElement(tag);
		if(props){
			for(var p in props){
				if(props.hasOwnProperty(p)){
					if(p == "className"){
						node[p] = props[p];
					}else{
						node.setAttribute(p, props[p]);
					}
				}
			}
		}
		return node;
	};

	this.one = function(id){
		return document.getElementById(id);
	};
	
};


window.Pipe = new Pipe();

})(window, document);
