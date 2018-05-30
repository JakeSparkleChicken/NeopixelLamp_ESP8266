<?php

$color=$_POST['color'];
$myfile = fopen("color.txt", "w");
fwrite($myfile, $color);
fclose($myfile);
?>
<html
<body>
<head>
    <title>Redirecting...</title>
    <meta http-equiv="refresh" content="0;URL=/color/index.php">
</head>
<body>
    You are being automatically redirected to a new location.<br />
    If your browser does not redirect you in few seconds, or you do
    not wish to wait, <a href="/color/index.php">click here</a>.
</body>
</html>
