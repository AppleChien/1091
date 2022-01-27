function progress(){
	var txt = document.form.txt.value;
	var seq = txt.split("\n");
	var output=""
	for (var i = 0; i<20;i+=2)
	{
	    var result=calc(seq[i],seq[i+1]); //第i筆測資
		output=output+"<br>"+result;
	}
    document.getElementById('out').innerHTML= output;
}
function calc(str1,str2)
{
    /* 
       str1 : first polynomial
	   str2 : second polynomial
    */
    var len1 = str1.length;
    var len2 = str2.length;

	var answer = "";
    /*----------------- Your Code Start-------------*/

    /* Hint: 
       var s = str1.substr(x,1) // the character s in the position x of str
    */

    /*----------------- Your Code End --------------*/
	return answer;
}
