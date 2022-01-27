<?php

require_once('../myhw2/TCPDF-main/tcpdf_import.php');

/*---------------- Sent Mail Start -----------------*/
/*$to      = 's#######@mail.yzu.edu.tw';
$subject = 'ShoppingLeleBaby';
$message='
<html>
<head>
<title>ShoppingLeleBaby</title>
</head>
<body>
<table border = "1" width=400 height= 250>  
<tr>
    <td colspan="2">用戶名:</td>
	<td colspan="2">$name</td>
	<td colspan="2">帳號:</td>
	<td colspan="2">$account</td>
</tr>
<tr>
    <td colspan="2">性別:</td>
	<td colspan="2">$sex</td>
	<td colspan="2">電話:</td>
	<td colspan="2">$phone</td>
</tr>
<tr>
    <td colspan="4">地址:</td>
	<td colspan="4">$address</td>
</tr>
<tr>
    <td colspan="4">為何會購買照片:</td>
	<td colspan="4">$interesting</td>
</tr>
<tr>
    <td colspan="4" rowspan="4" >購買項目:</td>
	<td colspan="4" rowspan="4" >$buy</td>
</tr>
<tr>
    <td colspan="2"  >價錢:</td>
	<td colspan="2"  >20*$number</td>
</tr>
</table>
</body>
</html>
'
mail($to,$subject, $message);*/
/*---------------- Sent Mail End -------------------*/

/*---------------- Print PDF Start -----------------*/
$pdf = new TCPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false);
$pdf->setPrintHeader(false);
$pdf->setPrintFooter(false);
$pdf->SetFont('cid0jp','', 18); 
$pdf->AddPage();


$name = $_POST['name'];
$account = $_POST['account'];
$sex = $_POST['sex'];
$phone = $_POST['phone'];
$address = $_POST['address'];
$interesting = $_POST['interesting'];
$buy = $_POST['buy'];
$number = $_POST['number'];

/*$itemNames = "";
foreach($interesting as $item){
$itemNames.=$item;
$itemNames.="<br>";
}*/

$html = <<<EOF
<table cellspaceing="0" cellpadding="1" border ="3" >
<tr>
	<td colspan="8"  style="color:deepskyblue;font-size:45px;"  align="center">LeleBaby</td>
</tr>
<tr>
	<td colspan="1">用戶名:</td>
	<td colspan="2">$name</td>
	<td colspan="1">帳號:</td>
	<td colspan="4">$account</td>
</tr>
<tr>
   <td colspan="2">性別:</td>
   <td colspan="2">$sex</td>
   <td colspan="2">電話:</td>
   <td colspan="2">$phone</td>
</tr>
<tr>
    <td colspan="2">地址:</td>
	<td colspan="6">$address</td>
</tr>
<tr>
    <td colspan="2">為何會購買照片:</td>
    <td colspan="6">$interesting</td>
</tr>
<tr>
    <td colspan="2" >購買項目:</td>
	<td colspan="6" >$buy</td>
</tr>
<tr>
    <td colspan="2"  >價錢:</td>
	<td colspan="6"  >20</td>
</tr>

</table>
EOF;

/*---------------- Print PDF End -------------------*/

$pdf->writeHTML($html);
$pdf->lastPage();
$pdf->Output('order.pdf', 'I');

?>