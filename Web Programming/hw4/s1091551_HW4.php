<?php
    if ($_POST["minx"] == 'null') {
        $_POST["minx"] = NULL; 
    }
    $minx = $_POST["minx"]; 
    if ($_POST["miny"] == 'null') {
        $_POST["miny"] = NULL; 
    } 
    $miny = $_POST["miny"]; 
    if ($_POST["maxx"] == 'null') {
        $_POST["maxx"] = NULL; 
    }
    $maxx = $_POST["maxx"];  
    if ($_POST["maxy"] == 'null') {
        $_POST["maxy"] = NULL; 
    }
    $maxy = $_POST["maxy"];
    $picturee = $_POST["picturee"];
    $name = $_POST["name"];
    if ($_POST["valid"] == 'null') {
        $_POST["valid"] = NULL; 
    }
    $valid = $_POST["valid"];

    

    $servername = "localhost";  //ipv4位址
    $username = "peiting";
    $password = "950217";
    $dbname = "hw4";

    $conn = new mysqli($servername, $username, $password, $dbname);
    $conn->query("SET NAMES 'utf8'");
    $sql = "UPDATE `hw4` SET `name` = '$name', `xmin` = '$minx', `ymin` = '$miny', `xmax` = '$maxx', `ymax` = '$maxy', `valid` = '$valid' WHERE filename = '$picturee'";  
    $conn->query($sql);
    $conn->close();
    
   //print VOC format
    print("<p>&lt;annotation&gt;</p> 
    <p>&lt;folder&gt;pic&lt;/folder&gt;</p> 
    <p>&lt;filename&gt;$picturee&lt;/filename&gt;</p> 
    <p>&lt;object&gt;</p> <p>&lt;name&gt;$name&lt;/name&gt;</p> 
    <p>&lt;bndbox&gt;</p> <p>&lt;xmin&gt;$minx&lt;/xmin&gt;</p> 
    <p>&lt;ymin&gt;$miny&lt;/ymin&gt;<p> <p>&lt;xmax&gt;$maxx&lt;/xmax&gt;</p> 
    <p>&lt;ymax&gt;$maxy&lt;/ymax&gt;</p> <p>&lt;/bndbox&gt;</p> <p>&lt;/object&gt;</p> 
    <p>&lt;/annotation&gt;</p>");  
?>
