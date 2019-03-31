<%@ page language="java" contentType="text/html; charset=GBK"
    pageEncoding="GBK"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<script language="javascript">
function checkform(myform)
{
	for(var i=0;i<myform.length;i++)
		if(myform.elements[i].value=="")
		{
			alert(myform.elements[i].title+"不能为空");
			myform.elements[i].focus();
			return false;
		}
	return true;
}
</script>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<title>发送普通邮件</title>
</head>
<body>
<form name="form1" method="post" action="mydeal.jsp" onsubmit="return checkform(this)">
收件人:<input name="to" type="text" id="to" title="收件人" size="60" value="541052067@qq.com"><br>
发件人:<input name="from" type="text" id="from" title="发件人" size="60"><br>
密&nbsp;&nbsp;码:<input name="password" type="password" id="password" title="发件人信箱密码" size="65"><br>
主&nbsp;&nbsp;题:<input name="subject" type="text" id="subject" title="邮件主题" size="60"><br>
内&nbsp;&nbsp;容:<textarea name="content" cols="59" rows="7" id="content" title="邮件内容"></textarea><br>
<input type="submit" value="发送">
<input type="reset" value="重置">
</form>
</body>
</html>