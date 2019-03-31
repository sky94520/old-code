/**
 * 
 */
var http_request = null;
function createRequest(url)
{
	//mozilla,safari
	if(window.XMLHttpRequest)
	{
		http_request = new XMLHttpRequest();
		if(http_request.overrideMimeType)
			http_request.overrideMimeType("text/xml");
	}
	else if(window.ActiveXObject)//IE
	{
		try
		{
			http_request = new ActiveXObject("Msxm12.XMLHTTP");
		}catch(e)
		{
			try
			{
				http_request = new ActiveXObject("Microsoft.XMLHTTP");
			}catch(e){}
		}
	}
	if(!http_request)
		alert("不能创建XMLHttpRequest对象实例");
	//
	http_request.onreadystatechange = getResult;
	http_request.open('POST',url,true);
	http_request.send();
}
function getResult()
{
	if(http_request.readyState == 4)
	{
		if(http_request.status == 200)
			answer.innerHTML = http_request.responseText;
		else
			alert("您请求的页面有错误,status"+http_request.status);
	}
}