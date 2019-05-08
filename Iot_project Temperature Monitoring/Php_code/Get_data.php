<?php







		//$email='kaif';
		//echo $name;
		$temp=$_GET['temperature'];
		//echo $email;
		$hum=$_GET['humidity'];

        $heatindex=$_GET['HeatIndex'];

		//echo "10";

		//echo $name;
		$connect=mysqli_connect("servername", "username", "password", "dbname");
		if (!$connect) {
	    die("Connection failed: " . mysqli_connect_error());
	      }

		$query="INSERT INTO your_table_name (temperature,humidity,heatindex) VALUES('$temp','$hum','$heatindex')";
		//echo ($query);
		//if data inserted succesfully
		if (mysqli_query($connect,$query)){
			$Message="inserted";

			echo "Data send successfully";
			//die();


		}
		else
		{
			echo "Fail";
		}


?>
