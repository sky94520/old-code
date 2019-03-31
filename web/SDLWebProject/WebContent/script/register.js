/**
 * 
 */
/*检测邮箱格式是否正确*/
//全局变量
var wait=60*1000;
var seconds = 1000;
var interval;
//
var http_request = null;
//验证码
var verify = "";
//是否已经注册
var bExisted = "";
function check(form)
{
	if(!checkRegisterFrom(form))
		return false;
	if(form.verify.value != verify)
		return false;
	return true;
}
function checkRegisterForm(form)
{
	//检测用户名
	if(form.username.value=="")
	{
		alert("用户名不能为空");
		form.username.focus();
		return false;
	}
	//检测密码
	if(form.password1.value == form.password2.value)
	{
		if(form.password1.value=="")
		{
			alert("密码不能为空");
			form.password1.focus();
			return false;
		}
	}
	else
	{
		alert("两次密码出入不一致");
		form.password2.focus();
		return false;
	}
	//检测邮箱
	if(!checkAddress(form.mail))
		return false;
	return true
}
function checkAddress(object)
{
	var reg=/^([a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(\.[a-zA-Z0-9_-])+/;
	var msg = document.getElementById("mailError");
	if(!reg.test(object.value))
	{
		//alert("请填写正确的邮箱格式");
		msg.innerHTML = "请输入正确的邮箱格式";
		object.value="";
		object.focus();
		return false;
	}
	else
		msg.innerHTML = "";
	return true;
}
//检测邮箱是否已经注册过了
function checkMailRegistered(mail)
{
	var bRet = false;
	var msg = document.getElementById("mailError");
	//先检测是否合格
	var reg=/^([a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(\.[a-zA-Z0-9_-])+/;
	
	if(!reg.test(mail.value))
	{
		msg.innerHTML = "请输入正确的邮箱格式";
		//mail.value="";
	}
	else
	{
		msg.innerHTML = "";
		bRet = true;
	}
	if(bRet)
	{
		//访问数据库，检测是否存在此数据项
		//该mail是否注册
		//var bExisted = 0;
		AjaxResponse(getMailExisted,"./DataBaseServlet?mail="+mail.value,false)
		if(bExisted != "1")
			msg.innerHTML = "";
		else
			msg.innerHTML ="该邮箱已经被注册";
		return true;
	}
	return false;
}
//发送验证码 验证码只能保持60s
function sendVerify(form)
{
	//邮箱已经被注册
	if(bExisted != "0")
		return;
	//获取邮箱
	var mailAddress = form.mail;
	//发送邮件，并且获得验证码
	AjaxResponse(getResult,"./SendMail?mail="+mailAddress.value,true);
	
	//设置不可点击
	var btn = document.getElementById("verifyBtn");
	btn.disabled=true;
	interval = setInterval(
			"document.getElementById('verifyBtn').value='重新发送'+(wait-seconds)/1000;" +
			"seconds+=1000;",1000);
	setTimeout("var btn=document.getElementById('verifyBtn');" +
			"btn.disabled=false;clearInterval(interval);" +
			"btn.value='获取验证码';" +
			"seconds=1000;",wait);
}
function createRequest()
{
	//保证只有一个HttpRequest
	if(http_request == null)
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
	}
	if(!http_request)
	{
		alert("不能创建XMLHttpRequest对象实例");
		return false;
	}
	return true;
}
/*Ajax 响应*/
/*参数 响应函数 调用的url 是否为同步*/
function AjaxResponse(onreadystatechangeFunction,url,asyncFlag)
{
	//如果http_request未赋值，赋值
	if(http_request == null)
		createRequest();
	//调用
	http_request.onreadystatechange = onreadystatechangeFunction;
	http_request.open('POST',url,asyncFlag);
	//这个方法必须在open之后调用
	http_request.setRequestHeader("Content-Type","text/html;charset=UTF-8");
	http_request.send();
}
//private
function getResult()
{
	if(http_request.readyState == 4)
	{
		if(http_request.status == 200)
		{
			verify = http_request.responseText;
		}
		else
			alert("您请求的页面有错误,status"+http_request.status+" readyState"+http_request.readyState);
	}
}
function getMailExisted()
{
	if(http_request.readyState == 4)
	{
		if(http_request.status == 200)
		{
			bExisted = http_request.responseText;
		}
		else
			alert("您请求的页面有错误,status"+http_request.status+" readyState"+http_request.readyState);
	}
}