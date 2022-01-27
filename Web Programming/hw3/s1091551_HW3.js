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
	var symbol_str1 = new Array(len1);
	var symbol_str2 = new Array(len2);
	var symbol_plus1 = new Array(len1);
	var symbol_plus2 = new Array(len2);
	var symbol_cuts1 = new Array(len1);
	var symbol_cuts2 = new Array(len2);
	var index_plus1 = str1.indexOf('+');
	var index_plus2 = str2.indexOf('+');
	var index_cuts1 = str1.indexOf('-');
	var index_cuts2 = str2.indexOf('-');
	
	str1 += 'n' + 'n';
	str2 += 'n' + 'n';
	
	while(index_plus1 != -1)
	{
		symbol_plus1[index_plus1] = 1;
		index_plus1 = str1.indexOf('+',index_plus1+1); //string1的加號位置
	}
	
	while(index_plus2 != -1)
	{
		symbol_plus2[index_plus2] = 1;
		index_plus2 = str2.indexOf('+',index_plus2+1); //string2的加號位置
	}
	
	while(index_cuts1 != -1)
	{
		symbol_cuts1[index_cuts1] = 1;
		index_cuts1 = str1.indexOf('-',index_cuts1+1); //string1的減號位置
	}
	
	while(index_cuts2 != -1)
	{
		symbol_cuts2[index_cuts2] = 1;
		index_cuts2 = str2.indexOf('-',index_cuts2+1); //string2的減號位置
	}
	
	for(var i = 0; i < len1; i++)
		symbol_str1[i] = 0; //string1每一項都放入0
	for(var i = 0; i < len2; i++)
		symbol_str2[i] = 0; //string2每一項都放入0
	
	for(var i = 0; i < len1; i++)
	{//===:嚴格相等
		if(symbol_plus1[i] === 1) //string1加號標記
		{
			symbol_str1[i] = 1;
		}
		else if(symbol_cuts1[i] === 1) //string1減號標記
		{
			symbol_str1[i] = 1;
		}
	}
	
	for(var i = 0; i < len2; i++) 
	{
		if(symbol_plus2[i] === 1) //string2加號標記
		{
			symbol_str2[i] = 1;
		}
		else if(symbol_cuts2[i] === 1) //string2減號標記
		{
			symbol_str2[i] = 1;
		}
	}
	
	var str1_data = new Array(len1); //[7];
	for(var i = 0; i < str1_data.length; i++) str1_data[i] = new Array(7);
	var str2_data = new Array(len2); //[7];
	for(var i = 0; i < str2_data.length; i++) str2_data[i] = new Array(7);
	//小心二維陣列
	var count_data1 = 0;
	var count_data2 = 0;
	
/*第一個多項式*/
	for(var i = 0; i < len1; i++)
	{
		if(i == 0)//如果字元第一項==0
		{
			if(symbol_str1[i] == 1)//有符號 因為第一位 所以必為減號
			{
				var coef = i+1;
				for(++i; i < len1+1; i++)
				{//isFinite:檢查string1參數是否為無窮大
					if(!isFinite(parseInt(str1[i]))) //如果string1參數不是無窮大
					{
						if(coef === i) 
						{
							str1_data[count_data1][0] = 1;
							break;
						}
						else 
						{
							str1_data[count_data1][0] = 0;
							for(var j = coef; j < i; j++)
								str1_data[count_data1][0] += parseInt(parseInt(str1[j]) * Math.pow(10, i - j - 1));
							break;
						}
					}
					else //如果string1參數是無窮大
						continue;
				}
				str1_data[count_data1][0] *= -1;
			}
			else if(isFinite(parseInt(str1[i]))) //如果string1參數是無窮大
			{//isFinite:檢查string1參數是否為無窮大
				var coef = i;
				for(++i; i < len1+1; i++)
				{
					if(!isFinite(parseInt(str1[i]))) //如果string1參數不是無窮大
					{
						if(coef === i)
						{
							str1_data[count_data1][0] = 1;
							break;
						}
						else
						{
							str1_data[count_data1][0] = 0;
							for(var j = coef; j < i; j++)
								str1_data[count_data1][0] += parseInt(parseInt(str1[j]) * Math.pow(10, i - j - 1));
							break;
						}
					}
					else //如果string1參數是無窮大
						continue;
				}
			}
			else str1_data[count_data1][0] = 1;
			
			str1_data[count_data1][1] = 'x';
			str1_data[count_data1][2] = 0;
			str1_data[count_data1][3] = 'y';
			str1_data[count_data1][4] = 0;
			str1_data[count_data1][5] = 'z';
			str1_data[count_data1][6] = 0;
			for(; i < len1 && symbol_str1[i] != 1; i++)//這裡就是為什麼要塞空字元的地方
				if(str1[i] == 'x')
				{
					if(str1[i+1] == '^')
					{
						str1_data[count_data1][2] = parseInt(str1[i+2]);
					}
					else
					{
						str1_data[count_data1][2] = 1;
					}
				}
				else if(str1[i] == 'y')
				{
					if(str1[i+1] == '^')
					{
						str1_data[count_data1][4] = parseInt(str1[i+2]);
					}
					else
					{
						str1_data[count_data1][4] = 1;
					}
				}
				else if(str1[i] == 'z')
				{
					if(str1[i+1] == '^')
					{
						str1_data[count_data1][6] = parseInt(str1[i+2]);
					}
					else
					{
						str1_data[count_data1][6] = 1;
					}
				}//重要
			count_data1++;
		}
		else//如果字元第一項!=0
		{
			i--;
			if(str1[i] == '-')//有減號
			{
				var coef = i+1;
				for(++i; i < len1+1; i++)
				{//isFinite:檢查string1參數是否為無窮大
					if(!isFinite(parseInt(str1[i]))) //如果string1參數不是無窮大
					{
						if(coef === i)
						{
							str1_data[count_data1][0] = 1;
							break;
						}
						else
						{
							str1_data[count_data1][0] = 0;
							for(var j = coef; j < i; j++)
								str1_data[count_data1][0] += parseInt(parseInt(str1[j]) * Math.pow(10, i - j - 1));
							break;
						}
					}
					else //如果string1參數是無窮大
						continue;
				}
				str1_data[count_data1][0] *= -1;
			}
			else if(str1[i] == '+')//有加號
			{
				var coef = i+1;
				for(++i; i < len1+1; i++)
				{//isFinite:檢查string1參數是否為無窮大
					if(!isFinite(parseInt(str1[i]))) //如果string1參數不是無窮大
					{
						if(coef === i)
						{
							str1_data[count_data1][0] = 1;
							break;
						}
						else
						{
							str1_data[count_data1][0] = 0;
							for(var j = coef; j < i; j++)
								str1_data[count_data1][0] += parseInt(parseInt(str1[j]) * Math.pow(10, i - j - 1));
							break;
						}
					}
					else //如果string1參數是無窮大
						continue;
				}
			}
			
			str1_data[count_data1][1] = 'x';
			str1_data[count_data1][2] = 0;
			str1_data[count_data1][3] = 'y';
			str1_data[count_data1][4] = 0;
			str1_data[count_data1][5] = 'z';
			str1_data[count_data1][6] = 0;
			for(; i < len1 && symbol_str1[i] != 1; i++)//塞空字元:因為1次方不會顯示
				if(str1[i] == 'x')
				{
					if(str1[i+1] == '^')
					{
						str1_data[count_data1][2] = parseInt(str1[i+2]);
					}
					else
					{
						str1_data[count_data1][2] = 1;//x的1次方
					}
				}
				else if(str1[i] == 'y')
				{
					if(str1[i+1] == '^')
					{
						str1_data[count_data1][4] = parseInt(str1[i+2]);
					}
					else
					{
						str1_data[count_data1][4] = 1;//y的1次方
					}
				}
				else if(str1[i] == 'z')
				{
					if(str1[i+1] == '^')
					{
						str1_data[count_data1][6] = parseInt(str1[i+2]);
					}
					else
					{
						str1_data[count_data1][6] = 1;//z的1次方
					}
				}

			count_data1++;
		}
		if(i == len1) break;
	}
	
/*第二個多項式*/
	for(var i = 0; i < len2; i++)
	{
		if(i == 0)//如果字元第一項==0
		{
			if(symbol_str2[i] == 1)//有符號 因為第一位 所以必為減號
			{
				var coef = i+1;
				for(++i; i < len2+1; i++)
				{//isFinite:檢查string2參數是否為無窮大
					if(!isFinite(parseInt(str2[i]))) //如果string2參數不是無窮大
					{
						if(coef === i)
						{
							str2_data[count_data2][0] = 1;
							break;
						}
						else
						{
							str2_data[count_data2][0] = 0;
							for(var j = coef; j < i; j++)
								str2_data[count_data2][0] += parseInt(parseInt(str2[j]) * Math.pow(10, i - j - 1));
							break;
						}
					}
					else //如果string2參數是無窮大
						continue;
				}
				str2_data[count_data2][0] *= -1;
			}
			else if(isFinite(parseInt(str2[i]))) //如果string2參數是無窮大
			{
				var coef = i;
				for(++i; i < len2+1; i++)
				{
					if(!isFinite(parseInt(str2[i]))) //如果string2參數不是無窮大
					{
						if(coef === i)
						{
							str2_data[count_data2][0] = 1;
							break;
						}
						else
						{
							str2_data[count_data2][0] = 0;
							for(var j = coef; j < i; j++)
								str2_data[count_data2][0] += parseInt(parseInt(str2[j]) * Math.pow(10, i - j - 1));
							break;
						}
					}
					else //如果string2參數是無窮大
						continue;
				}
			}
			else str2_data[count_data2][0] = 1;
			
			str2_data[count_data2][1] = 'x';
			str2_data[count_data2][2] = 0;
			str2_data[count_data2][3] = 'y';
			str2_data[count_data2][4] = 0;
			str2_data[count_data2][5] = 'z';
			str2_data[count_data2][6] = 0;
			for(; i < len2 && symbol_str2[i] != 1; i++)//塞空字元:因為1次方不會顯示
				if(str2[i] == 'x')
				{
					if(str2[i+1] == '^')
					{
						str2_data[count_data2][2] = parseInt(str2[i+2]);
					}
					else
					{
						str2_data[count_data2][2] = 1;//x的1次方
					}
				}
				else if(str2[i] == 'y')
				{
					if(str2[i+1] == '^')
					{
						str2_data[count_data2][4] = parseInt(str2[i+2]);
					}
					else
					{
						str2_data[count_data2][4] = 1;//y的1次方
					}
				}
				else if(str2[i] == 'z')
				{
					if(str2[i+1] == '^')
					{
						str2_data[count_data2][6] = parseInt(str2[i+2]);
					}
					else
					{
						str2_data[count_data2][6] = 1;//z的1次方
					}
				}//重要
			count_data2++;
		}
		else//如果字元第一項!=0
		{
			i--;
			if(str2[i] == '-')//有減號
			{
				var coef = i+1;
				for(++i; i < len2+1; i++)
				{//isFinite:檢查string2參數是否為無窮大
					if(!isFinite(parseInt(str2[i]))) //如果string2參數不是無窮大
					{
						if(coef === i)
						{
							str2_data[count_data2][0] = 1;
							break;
						}
						else
						{
							str2_data[count_data2][0] = 0;
							for(var j = coef; j < i; j++)
								str2_data[count_data2][0] += parseInt(parseInt(str2[j]) * Math.pow(10, i - j - 1));
							break;
						}
					}
					else //如果string2參數是無窮大
						continue;
				}
				str2_data[count_data2][0] *= -1;
			}
			else if(str2[i] == '+')//有加號
			{
				var coef = i+1;
				for(++i; i < len2+1; i++)
				{//isFinite:檢查string2參數是否為無窮大
					if(!isFinite(parseInt(str2[i]))) //如果string2參數不是無窮大
					{
						if(coef === i)
						{
							str2_data[count_data2][0] = 1;
							break;
						}
						else
						{
							str2_data[count_data2][0] = 0;
							for(var j = coef; j < i; j++)
								str2_data[count_data2][0] += parseInt(parseInt(str2[j]) * Math.pow(10, i - j - 1));
							break;
						}
					}
					else //如果string2參數是無窮大
						continue;
				}
			}
			
			str2_data[count_data2][1] = 'x';
			str2_data[count_data2][2] = 0;
			str2_data[count_data2][3] = 'y';
			str2_data[count_data2][4] = 0;
			str2_data[count_data2][5] = 'z';
			str2_data[count_data2][6] = 0;
			for(; i < len2 && symbol_str2[i] != 1; i++)//這裡就是為什麼要塞空字元的地方
				if(str2[i] == 'x')
				{
					if(str2[i+1] == '^')
					{
						str2_data[count_data2][2] = parseInt(str2[i+2]);
					}
					else
					{
						str2_data[count_data2][2] = 1;
					}
				}
				else if(str2[i] == 'y')
				{
					if(str2[i+1] == '^')
					{
						str2_data[count_data2][4] = parseInt(str2[i+2]);
					}
					else
					{
						str2_data[count_data2][4] = 1;
					}
				}
				else if(str2[i] == 'z')
				{
					if(str2[i+1] == '^')
					{
						str2_data[count_data2][6] = parseInt(str2[i+2]);
					}
					else
					{
						str2_data[count_data2][6] = 1;
					}
				}
			count_data2++;
		}
		if(i == len2) break;
	}
	
/*計算環節*/
	var buffer = new Array(count_data1 * count_data2);//[7] = {};	
	for(var i = 0; i < buffer.length; i++) buffer[i] = new Array(7);
	var buffer_count = 0;

	for(var i = 0; i < count_data1; i++)
	{
		for(var j = 0; j < count_data2; j++)
		{
			buffer[buffer_count][0] = str1_data[i][0] * str2_data[j][0]; //係數
			buffer[buffer_count][2] = str1_data[i][2] + str2_data[j][2]; //x^
			buffer[buffer_count][4] = str1_data[i][4] + str2_data[j][4]; //y^
			buffer[buffer_count][6] = str1_data[i][6] + str2_data[j][6]; //z^
			buffer_count++;
		}
	}
	
	var prefix = new Array(count_data1 * count_data2);	//[7] = {};	
	for(var i = 0; i < prefix.length; i++) prefix[i] = new Array(7);
	var pre_count = 0;
	
	for(var i = 0; i < buffer_count; i++)
	{
		if(pre_count == 0)
		{
			prefix[pre_count][0] = buffer[i][0];
			prefix[pre_count][1] = 'x';
			prefix[pre_count][2] = buffer[i][2];
			prefix[pre_count][3] = 'y';
			prefix[pre_count][4] = buffer[i][4];
			prefix[pre_count][5] = 'z';
			prefix[pre_count][6] = buffer[i][6];
			pre_count++;
		}
		else
		{
			var testfor = 0;
			for(var j = 0; j < i; j++)
			{
				if(buffer[i][2] == prefix[j][2] && buffer[i][4] == prefix[j][4] && buffer[i][6] == prefix[j][6])
				{
					prefix[j][0] += parseInt(buffer[i][0]);
					prefix[j][1] = 'x';
					prefix[j][2] = buffer[i][2];
					prefix[j][3] = 'y';
					prefix[j][4] = buffer[i][4];
					prefix[j][5] = 'z';
					prefix[j][6] = buffer[i][6];
					
					testfor = 1;
					break;
				}
			}
			if(testfor == 1) continue;
			else
			{
				prefix[pre_count][0] = buffer[i][0];
				prefix[pre_count][1] = 'x';
				prefix[pre_count][2] = buffer[i][2];
				prefix[pre_count][3] = 'y';
				prefix[pre_count][4] = buffer[i][4];
				prefix[pre_count][5] = 'z';
				prefix[pre_count][6] = buffer[i][6];
				pre_count++;
			}
		}
	}
/*排序*/
	var buffer1 = new Array(7);
	var buffer2 = new Array(7);
	
	for(var i = 0; i < pre_count; i++)//x排序
	{
		for(var j = 0; j < pre_count; j++)
		{
			if(prefix[i][2] > prefix[j][2])
			{
				for(var k = 0; k < 7; k++)
				{
					buffer1[k] = prefix[i][k];
					buffer2[k] = prefix[j][k];
					prefix[i][k] = buffer2[k];
					prefix[j][k] = buffer1[k];
				}
			}
		}
	}
	
	for(var i = 0; i < pre_count; i++)//y排序
	{
		for(var j = 0; j < pre_count; j++)
		{
			if(prefix[i][2] == prefix[j][2])
			{
				if(prefix[i][4] > prefix[j][4])
				{
					for(var k = 0; k < 7; k++)
					{
						buffer1[k] = prefix[i][k];
						buffer2[k] = prefix[j][k];
						prefix[i][k] = buffer2[k];
						prefix[j][k] = buffer1[k];
					}
				}
			}
		}
	}
	
	for(var i = 0; i < pre_count; i++)//z排序
	{
		for(var j = 0; j < pre_count; j++)
		{
			if(prefix[i][2] == prefix[j][2] && prefix[i][4] == prefix[j][4])
			{
				if(prefix[i][6] > prefix[j][6])
				{
					for(var k = 0; k < 7; k++)
					{
						buffer1[k] = prefix[i][k];
						buffer2[k] = prefix[j][k];
						prefix[i][k] = buffer2[k];
						prefix[j][k] = buffer1[k];
					}
				}
			}
		}
	}
	
	
	answer = String(answer);
	for(var i = 0; i < pre_count; i++)
	{
		if(prefix[i][0] != 0)
		{
			if(i == 0)//放入係數
			{	if(	prefix[i][0] != 1)
				{
					if( prefix[i][0] != -1)
					{
						answer += prefix[i][0];
					}
					else
					{
						answer += String("-");
					}
				}
			}
			else
			{
				if(prefix[i][0] == 1)
				{
					if(prefix[i][2] == 0 && prefix[i][4] == 0 && prefix[i][6] == 0)
					{
						answer += String("+") + prefix[i][0];
					}
					else
					{
						answer += String("+");
					}
				}
				else if(prefix[i][0] > 0)
				{
					answer += String("+") + prefix[i][0];
				}
				else if(prefix[i][0] == -1)
				{
					if(prefix[i][2] == 0 && prefix[i][4] == 0 && prefix[i][6] == 0)
					{
						answer += prefix[i][0];
					}
					else
					{
						answer += String("-");
					}
					
				}
				else
				{
					answer += prefix[i][0];
				}
			}
			
			if(prefix[i][2] != 0)//放x
			{
				if(prefix[i][2] == 1)
				{
					answer += 'x';
				}
				else
				{
					answer +=  'x^' + prefix[i][2];
				}
			}
			
			if(prefix[i][4] != 0)//放y
			{
				if(prefix[i][4] == 1)
				{
					answer += 'y';
				}
				else
				{
					answer +=  'y^' + prefix[i][4];
				}
			}
			
			if(prefix[i][6] != 0)//放z
			{
				if(prefix[i][6] == 1)
				{
					answer += 'z';
				}
				else
				{
					answer +=  'z^' + prefix[i][6];
				}
			}
		}
	}

    /*----------------- Your Code End --------------*/
	return answer;
}
