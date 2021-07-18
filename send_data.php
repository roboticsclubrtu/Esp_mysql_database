<?php
// error_reporting(0);
$servername = "localhost";		//example = localhost or 192.168.0.0
    $username = "root";		//example = root
    $password = "";	
    $dbname = "test";

 
  $conn = mysqli_connect($servername, $username, $password, $dbname);
  if ($conn->connect_error) {
      die("Database Connection failed: " . $conn->connect_error);
  }
  if($conn){ 
  echo"connected";}
 
 if (isset($_GET['name'])){

$name = $_GET['name'];

echo $name;

$result = mysqli_query($conn, "INSERT INTO `esp_data`(`name`) VALUES ('$name')");

if ($result) {

$response["success"] = 1;
$response["message"] = "data successfully created.";

echo json_encode($response);
} else {

$response["success"] = 0;
$response["message"] = "Something has been wrong";

echo json_encode($response);
}
} else {

$response["success"] = 0;
$response["message"] = "Parameter(s) are missing. Please check the request";

echo json_encode($response);
}
?>