<?php
function name($_Post){
	if(isset($_Post["name"])){
		$text = " Ваше имя: <b>".htmlspecialchars($_Post["name"])."<br></b>";
		return $text;
	}
	return "";
}

function sername($_Post){
	if(isset($_Post["sername"])){
		$text = " Ваша фамилия: <b>".htmlspecialchars($_Post["sername"])."<br></b>";
		return $text;
	}
	return "";
}

function age($_Post){
	if (isset($_Post["age"])){
		$text = " <b>".htmlspecialchars($_Post["age"])."<br></b>";
		return $text;
	}
	return "";
}

function salary($_Post){
	if(isset($_Post["salary"])){
		$text = " <b>".htmlspecialchars($_Post["salary"])."<br></b>";
		return $text;
	}
	return "";
}

function checkboxes($_Post){
	$text = ":<br><b>";
	if(isset($_Post["animals"])) $text. = "";
	if(isset($_Post["car"])) $text. = "";
	if(isset($_Post["study"])) $text. = "";
	if(isset($_Post["work"])) $text. = "";
	return $text.="</b><br>";
}

function living_place($_Post){
	if(isset($_Post["living_place"])){
		$text = " Место проживения: <b>".htmlspecialchars($_Post["living_place"])."<br></b>";
		return $text;
	}
	return "";
}

function status($_Post){
	if(isset($_Post["status"])){
		$text = " Семейное положение: <b>".$_Post["status"]."<br></b>";
		return $text.="<br>";
	}
	return "";
}

echo name($_POST);
echo sername($_POST);
echo age($_POST);
echo salary($_POST);
echo checkboxes($_POST);
echo leveng_place($_POST);
echo status($_POST);
?>