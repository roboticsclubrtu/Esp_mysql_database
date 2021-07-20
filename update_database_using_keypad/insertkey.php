<?php
// error_reporting(0);
$servername = "localhost";		//example = localhost or 192.168.0.0
    $username = "root";		//example = root
    $password = "";	
    $dbname = "test";

    $penalty = "";
    $charge = "" ; 

  $conn = mysqli_connect($servername, $username, $password, $dbname);
  if ($conn->connect_error) {
      die("Database Connection failed: " . $conn->connect_error);
  }
  if($conn){ 
  echo"connected";}
 
 if (isset($_GET['abc'])){

$key = $_GET['abc'];

echo $key;

if ($key=='1'){
      $penalty = "200";
      $charge = "Not_wearing_Helmet" ;
    }
    else if ($key=='2'){
      $penalty = "1000";
      $charge = "lack of Documents" ;
    }
    else if ($key=='3'){
      $penalty = "1500";
      $charge = "Rash Driving" ;
    }
    else if ($key=='4'){
      $penalty = "500";
      $charge = "Not having Insurance" ;
    }
    else if ($key=='5'){
      $penalty = "1000";
      $charge = "Overspeeding" ;
    }
    else if ($key=='6'){
      $penalty = "5000";
      $charge = "Drunk and Drive" ;
    }
    else if ($key=='7'){
      $penalty = "800";
      $charge = "Not wearing Seat Belt" ;
    }
    else if ($key=='8'){
      $penalty = "250";
      $charge = "Unauthorised parking" ;
    }
    else if ($key=='9'){
      $penalty = "500";
      $charge = "Obstructing Traffic" ;
    }
    else if ($key=='A'){
      $penalty = "1500";
      $charge = "Breaking Signal" ;
    }
    else if ($key=='B'){
      $penalty = "5000";
      $charge = "Hit and Run" ;
    }
    else if ($key=='C'){
      $penalty = "5000";
      $charge = "Driving at wrong side" ;
    }

$id = mysqli_query($conn, "SELECT id FROM esp_data");
while($rows = mysqli_fetch_assoc($id))
{
  $id1 = $rows['id'];
}
echo $id1;
$result = mysqli_query($conn, " UPDATE esp_data SET `amount_charged`=$penalty WHERE `id`= $id1 ");

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