<?php

	include("connect.php"); 	
	
	$link=Connection();

	$result=mysql_query("SELECT * FROM `tempLog` ORDER BY `timeStamp` DESC",$link);
?>

<html>
   <head>
      <title>Sensor Data</title>
      <meta http-equiv="refresh" content="30">  
   </head>
<body>
   <h1>Temperature / Humidity Sensor Readings</h1>

   <table border="1" cellspacing="1" cellpadding="1">
		<tr>
			<td>&nbsp;Timestamp&nbsp;</td>
			<td>&nbsp;Temperature 1&nbsp;</td>
			<td>&nbsp;Humidity 1&nbsp;</td>
		</tr>

      <?php 
		  if($result!==FALSE){
		     while($row = mysql_fetch_array($result)) {
		        printf("<tr><td> &nbsp;%s </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td></tr>", 
		           $row["timeStamp"], $row["temperature"], $row["humidity"]);
		     }
		     mysql_free_result($result);
		     mysql_close();
		  }
      ?>

   </table>
</body>
</html>
