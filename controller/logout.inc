<?php
	if(isset($_SESSION['loggedUser'])) {
		$loggedUser = unserialize($_SESSION['loggedUser']);
	} else {
		$loggedUser = false;
	}
	
	if(!$loggedUser) {
		header('Location: index.php');
	}
	
	session_unset();
	session_destroy();
	
	header('Location: index.php');
?>