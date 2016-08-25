<?php
require_once('orm/UserRepo.class.inc');


if(isset($_SESSION['loggedUser'])) {
    
	$loggedUser = unserialize($_SESSION['loggedUser']);
        
        var_dump($loggedUser);
} else {
	$loggedUser = false;
}

if($loggedUser) {
	//header('Location: index.php');
    
}

//$pseudo = (isset($loggedUser['pseudo']))?(trim($loggedUser['pseudo'])):('');
$mdp1 = (isset($_POST['mdp1']))?(trim($_POST['mdp1'])):('');
$mdp2 = (isset($_POST['mdp2']))?(trim($_POST['mdp2'])):('');
$nom = (isset($_POST['nom']))?(trim($_POST['nom'])):('');
$prenom = (isset($_POST['prenom']))?(trim($_POST['prenom'])):('');
$tel = (isset($_POST['tel']))?(trim($_POST['tel'])):('');
$nais = (isset($_POST['nais']))?(trim($_POST['nais'])):('');
$email = (isset($_POST['email']))?(trim($_POST['email'])):('');
$submit_ok = isset($_POST['submit']);

$form_ok = true;
$errorMsg = '';

if($submit_ok) {
	$userRepo = UserRepo::getInstance();
	
	
	if(!$mdp1 && !$mdp2) {
		$form_ok = false;
		$errorMsg .= 'Veuillez entrer un mot de passe<br/>';
	} else if($mdp1 != $mdp2) {
		$form_ok = false;
		$errorMsg .= 'Les mots de passe ne correspondent pas<br/>';
	} else {
		$mdp_hash = hash('sha256', $mdp1);
	}
	
	if($form_ok) {
		try {
			$newUser = new User($loggedUser->getIdUser(), $loggedUser->getPseudo(), $mdp_hash, $nom, $prenom, $nais, 
				$tel, $email, User::PROFIL_USER);
			
			$userRepo = UserRepo::getInstance();
			$userRepo->update($newUser);
			
			$_SESSION['loggedUser'] = serialize($newUser);
			header('Location: index.php');
		} catch(Exception $e) {
			$errorMsg .= $e->getMessage();
		}
	}
}
?>