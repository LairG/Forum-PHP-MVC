<?php
require_once('orm/AbstractRepo.class.inc');
require_once('model/User.class.inc');

class UserRepo extends AbstractRepo {
	private static $instance;
	
	public static function getInstance() {
		if(isset(self::$instance)) {
			return self::$instance;
		} else {
			self::$instance = new UserRepo();
			return self::$instance;
		}
	}
	
	protected function __construct() {
		parent::__construct();
	}
	
	public function getUserByPseudoAndMdpHash($pseudo, $mdpHash) {
		$pseudo = strip_tags($pseudo);
		$sql = 'SELECT * FROM user WHERE pseudo=:pseudo AND mdphash=:mdp_hash;';
	
		$st = $this->getDb()->prepare($sql);
		
		$params = array(
			'pseudo' => $pseudo,
			'mdp_hash' => $mdpHash,
		);
		
		$st->execute($params);
		
		$user = $st->fetch();
		var_dump($user);
		if($user) {
			return new User(intval($user['id_user']), $user['pseudo'], $user['mdphash'],
				$user['nom'], $user['prenom'], $user['nais'], $user['tel'], 
				$user['email'], intval($user['profil']));
		} else {
			return false;
		}
	}
	
	public function save($user) {
		$sql = 'INSERT INTO user(nom, prenom, pseudo, mdphash, nais, tel, email, profil)'
			. 'VALUES(:nom, :prenom, :pseudo, :mdphash, :nais, :tel, :email, :profil);';
			
		$params = array(
			'nom' => $user->getNom(),
			'prenom' => $user->getPrenom(),
			'pseudo' => $user->getPseudo(),
			'mdphash' => $user->getMdpHash(),
                        'nais' => $user->getNais('iso'),
			'tel' => $user->getTel(),
			'email' => $user->getEmail(),
			'profil' => $user->getProfil(),
		);
		
		$st = $this->getDb()->prepare($sql);
		$st->execute($params);
	}
	
        public function update($user) {
		$sql = "UPDATE user SET nom=:nom, prenom=:prenom, mdphash=:mdphash, nais=:nais, tel=:tel, email=:email WHERE id_user = :idUser";
			
		$params = array(
			'nom' => $user->getNom(),
			'prenom' => $user->getPrenom(),
			'mdphash' => $user->getMdpHash(),
                        'nais' => $user->getNais('iso'),
			'tel' => $user->getTel(),
			'email' => $user->getEmail(),
                        'idUser'=> $user->getIdUser(),
		);
		
		$st = $this->getDb()->prepare($sql);
		$st->execute($params);
	}
        
	public function checkIfPseudoExists($pseudo) {
		$pseudo = strip_tags($pseudo);
		$sql = 'SELECT * FROM user WHERE pseudo=:p;';
		$st = $this->getDb()->prepare($sql);
		$st->execute(array('p' => $pseudo));
		return !!$st->fetch();
	}
	
	// public function getAllUsersOrderedByPseudo(){
		// $sql='SELECT * FROM user ORDER BY pseudo ASC';
		// $result = $this->getDb()->query($sql);
		// $tabUserTmp = $result->fetchAll(PDO::FETCH_ASSOC);
		// $tabUsers = array();
		// foreach($tabUserTmp as $user){
			// $tabUsers[] = new User(intval($user['id_user']), $user['pseudo'], $user['mdp_hash'], 
			// $user['nom'], $user['prenom'], $user['nais'], $user['tel'], $user['email'],
			// intval($user['profil']) );
			
		// }
		// return $tabUsers;
	// }
}
?>