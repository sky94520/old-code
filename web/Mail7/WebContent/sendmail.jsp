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
			alert(myform.elements[i].title+"����Ϊ��");
			myform.elements[i].focus();
			return false;
		}
	return true;
}
</script>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<title>������ͨ�ʼ�</title>
</head>
<body>
<form name="form1" method="post" action="mydeal.jsp" onsubmit="return checkform(this)">
�ռ���:<input name="to" type="text" id="to" title="�ռ���" size="60" value="541052067@qq.com"><br>
������:<input name="from" type="text" id="from" title="������" size="60"><br>
��&nbsp;&nbsp;��:<input name="password" type="password" id="password" title="��������������" size="65"><br>
��&nbsp;&nbsp;��:<input name="subject" type="text" id="subject" title="�ʼ�����" size="60"><br>
��&nbsp;&nbsp;��:<textarea name="content" cols="59" rows="7" id="content" title="�ʼ�����"></textarea><br>
<input type="submit" value="����">
<input type="reset" value="����">
</form>
</body>
</html>