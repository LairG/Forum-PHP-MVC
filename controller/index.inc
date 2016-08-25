<?php
require_once('orm/AbstractRepo.class.inc');
require_once('orm/CategorieRepo.class.inc');
	if(isset($_SESSION['loggedUser'])) {
		$loggedUser = unserialize($_SESSION['loggedUser']);
	} else {
		$loggedUser = false;
	}
	
	$categorieRepo = CategorieRepo::getInstance();
	$tabCategorie = $categorieRepo->getCategorieById();
        //$nbPost = $categorieRepo->getNbTopics($categorie->idCategorie);
?>