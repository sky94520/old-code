/**
 * 
 */
function checkForm(theform)
{
	//check the user name
	if(theform.username.value == "")
		{
			check("userNameErr","用户名不能为空");
			return false;
		}
	else if(theform.username.value != "")
		check("userNameErr","");
	//check password
	if(theform.passwrd.value == "")
	{
		check("passwrdErr","密码不能为空");
		return false;
	}
	else if(theform.passwrd.value == "")
		check("userNameErr","");
	return true;
}
function check(id,text)
{
	var span = document.getElementById(id);
	span.innerHTML = text;
}
