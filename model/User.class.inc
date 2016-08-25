<?php
class User {
	private $idUser;
	private $pseudo;
	private $mdpHash;
	private $nom;
	private $prenom;
	private $nais;
	private $tel;
	private $email;
	private $profil;
	
	const PROFIL_ADMIN = 3;
	const PROFIL_SUPER_MODERATEUR = 2;
	const PROFIL_MODERATEUR = 1;
	const PROFIL_USER = 0;
	
	public function __construct($idUser, $pseudo, $mdpHash, $nom, $prenom, $nais, $tel, 
			$email, $profil) {
		$this->setIdUser($idUser);
		$this->setPseudo($pseudo);
		$this->setMdpHash($mdpHash);
		$this->setNom($nom);
		$this->setPrenom($prenom);
		$this->setNais($nais);
		$this->setTel($tel);
		$this->setEmail($email);
		$this->setProfil($profil);
	}
	
	public function __toString() {
		return "ID({$this->getIdUser()}), Pseudo({$this->getPseudo()}), Nom({$this->getNom()}), "
			. "Prenom({$this->getPrenom()}), Nais({$this->getNais()}), Tel({$this->getTel()}), "
			. "Email({$this->getEmail()}), Profil({$this->getProfilString()})";
	}
	
	public function getIdUser() {
		return $this->idUser;
	}
	
	private function setIdUser($idUser) {
		if(is_int($idUser)) {
			$this->idUser = $idUser;
		} else {
			throw new Exception('L\'id doit être un entier !');
		}
	}
	
	public function getPseudo() {
		return $this->pseudo;
	}
	
	public function setPseudo($pseudo) {
		$pseudo = trim($pseudo);
		$pseudo = strip_tags($pseudo);
		if(is_string($pseudo) && $pseudo != '' && strlen($pseudo) < 50) {
			$this->pseudo = $pseudo;
		} else {
			throw new Exception('Le pseudo doit être une chaine non vide de 50 caractères au plus !');
		}
	}
	
	public function getMdpHash() {
		return $this->mdpHash;
	}
	
	public function setMdpHash($mdpHash) {
		if(is_string($mdpHash) && strlen($mdpHash) == 64) {
			$this->mdpHash = $mdpHash;
		} else {
			throw new Exception('Problème lors de l\'enregistrement du mot de passe !');
		}
	}
	
	public function getNom() {
		return $this->nom;
	}
	
	public function setNom($nom) {
		$pseudo = trim($nom);
		$pseudo = strip_tags($nom);
		if(is_string($nom) && $nom != '') {
			$this->nom = substr($nom, 0, 49);
		} else {
			throw new Exception('Le nom doit être une chaine non vide !');
		}
	}
	
	public function getPrenom() {
		return $this->prenom;
	}
	
	public function setPrenom($prenom) {
		$pseudo = trim($prenom);
		$pseudo = strip_tags($prenom);
		if(is_string($prenom) && $prenom != '') {
			$this->prenom = substr($prenom, 0, 49);
		} else {
			throw new Exception('Le prénom doit être une chaine non vide !');
		}
	}
	
	public function getNais($lang='fr') {
		switch($lang) {
			case 'iso':
				return $this->nais;
				break;
			case 'fr':
			default:
				return date_format(date_create($this->nais), 'd/m/Y');
		}
	}
	
	public function setNais($nais) {
		$nais = trim($nais);
		$nais = $this->dateFR2ISO($nais);
		if($nais) {
			$this->nais = $nais;
		} else {
			throw new Exception('La date de naissance ' . $nais . ' n\'est pas correcte !');
		}
	}
	
	private function checkDateISO($dateISO) {
		$motif = '#^([0-9]{4})-([01]?[0-9])-([0-2]?[0-9]|3[01])$#';
		
		if(preg_match($motif, $dateISO)) {
			$tabDate = explode('-', $dateISO);
			return checkdate($tabDate[1], $tabDate[2], $tabDate[0]);
		} else {
			return false;
		}
	}
	
	private function dateFR2ISO($dateFR) {
		if(strpos($dateFR, ' ')) {
			$dateFR = substr($dateFR, 0, strpos($dateFR, ' '));
		}
		$motif = '#^([0-2]?[0-9]|3[01])/([01]?[0-9])/([0-9]{4})$#';
		$replace = '$3-$2-$1';
		
		$dateISO = preg_replace($motif, $replace, $dateFR);
		
		if(!$this->checkDateISO($dateISO)) {
			return false;
		} else {
			return $dateISO;
		}
	}
	
	public function getTel() {
		return $this->tel;
	}
	
	public function setTel($tel) {
		$tel = trim($tel);
		if($this->checkTel($tel)) {
			$this->tel = $this->formatTel($tel);
		} else {
			throw new Exception('Le numéro de tel ' . $tel . ' n\'est pas correct !');
		}
	}
	
	private function checkTel($tel) {
		$motif = '/^(0|\+33 *)[1-9][. \/-]*([0-9]{2}[. \/-]*){3}[0-9]{2}$/';
		
		return !!preg_match($motif, $tel);
	}
	
	private function formatTel($tel) {
		return preg_replace('/[. \/-]/', '', $tel);
	}
	
	public function getEmail() {
		return $this->email;
	}
	
	public function setEmail($email) {
		$email = trim($email);
		if($this->checkEmail($email)) {
			$this->email = $email;
		} else {
			throw new Exception('L\'email ' . $email . ' n\'est pas correct !');
		}
	}
	
	private function checkEmail($email) {
		$motif = '/^[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+\.[a-zA-Z]{2,}$/';
		
		return !!preg_match($motif, $email);
	}
	
	public function hasProfil($profil) {
		return $this->profil === $profil;
	}
	
	public function isAdmin() {
		return $this->profil === self::PROFIL_ADMIN;
	}
	
	public function isSuperModerateur() {
		return $this->profil === self::PROFIL_SUPER_MODERATEUR;
	}
	
	public function isModerateur() {
		return $this->profil === self::PROFIL_MODERATEUR;
	}
	
	public function getProfil() {
		return $this->profil;
	}
	
	public function getProfilString() {
		switch($this->profil) {
			case self::PROFIL_ADMIN:
				return 'Admin';
				break;
			case self::PROFIL_SUPER_MODERATEUR:
				return 'Super-moderateur';
				break;
			case self::PROFIL_MODERATEUR:
				return 'Moderateur';
				break;
			case self::PROFIL_USER:
				return 'Utilisateur';
				break;
			default:
				return 'Indéfini';
		}
	}
	
	public function setProfil($profil) {
		if($profil === self::PROFIL_ADMIN 
		|| $profil === self::PROFIL_SUPER_MODERATEUR 
		|| $profil === self::PROFIL_MODERATEUR 
		|| $profil === self::PROFIL_USER) {
			$this->profil = $profil;
		} else {
			throw new Exception('Le profil ne peut être que User::PROFIL_ADMIN, '
				. 'User::PROFIL_SUPER_MODERATEUR, ou User::PROFIL_MODERATEUR, ou User::PROFIL_USER !');
		}
	}
	
	public function getFullName() {
		return $this->getPrenom() . ' ' . $this->getNom();
	}
}
?>