<?php
require_once('orm/UserRepo.class.inc');

if(isset($_SESSION['loggedUser'])) {
	$loggedUser = unserialize($_SESSION['loggedUser']);
} else {
	$loggedUser = false;
}

if($loggedUser) {
	header('Location: index.php');
}

$pseudo = (isset($_POST['pseudo']))?($_POST['pseudo']):('');
$mdp = (isset($_POST['mdp']))?($_POST['mdp']):('');
$submit_ok = isset($_POST['submit']);

$errorMsg = '';

if($submit_ok && $pseudo && $mdp) {
	$userRepo = UserRepo::getInstance();
	$user = $userRepo->getUserByPseudoAndMdpHash($pseudo, hash('sha256', $mdp));
	
	if($user) {
		// Procédure de connexion
		var_dump($_SESSION['loggedUser']);
		// A partir de maintenant, on considère que la présence d'une case 'loggedUser' non vide dans la session
		//  représente l'information de connexion, et contient les infos du user connecté
		$_SESSION['loggedUser'] = serialize($user);
		
		//header('Location: index.php');
	} else {
		$errorMsg = 'Erreur d\'authentification';
	}
}













?>