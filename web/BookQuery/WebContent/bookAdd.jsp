<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>新增图书</title>
</head>
<script language="javascript">
function check(form)
{
	if(form.bookID.value=="")
	{
		alert("图书编号不能为空！");
		form.bookID.focus();
		return false;
	}
	else if(isNaN(form.bookID.value))
	{
		alert("图书编号必须为数字");
		form.bookID.focus();
		return false;
	}
	var price = form.bookPrice;
	if(price.value==""||isNaN(price.value))
	{
		alert("请输入数字");
		price.value="";
		price.focus();
		return false;
	}
	return true;
}

</script>
<body>
<form action="bookAddDo.jsp" method="get" onsubmit="return check(this);">
<table align="center" border="1">
<tr><td>图书编号：</td><td height="22"><input type="text" name="bookID">(必填项)</td></tr>
<tr><td>书名：</td><td><input type="text" name="bookName"></td></tr>
<tr><td>作者：</td><td><input type="text" name="bookAuth"></td></tr>
<tr><td>出版社：</td><td><input type="text" name="bookPub"></td></tr>
<tr><td>单价：</td><td><input type="text" name="bookPrice"></td></tr>
<tr><td>内容介绍：</td><td><textarea name="bookInter" rows="6" cols="25"></textarea></td></tr>
<tr ><td colspan="2" align="center">
	<input type="submit" value="提交">&nbsp;&nbsp;&nbsp;&nbsp;
	<input type="reset" value="重置"></td></tr>
</table>
</form>
</body>
</html>