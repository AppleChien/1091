<?php
$cityname = $_POST["city"];
$year = $_POST["pyear"];
$year = "death_".$year;
if(empty($cityname))
{
    echo ("空city");
    return "空city";
}
else if (empty($year))
{
    return "空year";
}
$database = mysqli_connect("localhost", "user_1" , "12345");
if(!$database)
    die("Could not connect to database <body></html>");
if(!mysqli_select_db($database,"city"))
    die("Could not open city table</body></html>");
$query = "SELECT * FROM `".$year."` WHERE `Cityname` LIKE '".$cityname."'";
$rs = mysqli_query($database,$query);
$output = mysqli_fetch_row($rs);
print($output[1]);
?>