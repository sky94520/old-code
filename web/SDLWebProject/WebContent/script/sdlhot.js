function writeText(imgSrc,text)
{
	document.getElementById("desc").innerHTML=text;
	document.getElementById("detail").src = imgSrc;
}
function compare(a,b)
{
	return a-b;
}